#include "ST/Net/Selector.h"

#include <errno.h>
#include <string.h>

#include <system_error>

#include <spdlog/spdlog.h>


namespace ST::Net {

Selector::Selector()
  : max_fd_{ -1 }
{
  FD_ZERO(&write_sets_);
  FD_ZERO(&read_sets_);
  FD_ZERO(&exception_sets_);
  // 由于C++语言的初始化保障，这条语句是多余的
  bzero(&wait_for_, sizeof(wait_for_));
}

timeval Selector::wait_for(long seconds, long micro_seconds)
{
  wait_for_.tv_sec = seconds;
  wait_for_.tv_usec = micro_seconds;

  SPDLOG_INFO("waiting for selecting fd sets");

  auto res = ::select(max_fd_, &read_sets_, &write_sets_,
        &exception_sets_, &wait_for_);
  if (res == -1) {
    SPDLOG_ERROR("select error");
    throw std::system_error{ errno, std::generic_category(), "select error" };
  }
  update();

  SPDLOG_INFO("waited for selecting fd sets for {} s {} ms", wait_for_.tv_sec, wait_for_.tv_usec);
  return wait_for_;
}

void Selector::update()
{
  readable_sets_.clear();
  writable_sets_.clear();
  has_exception_sets_.clear();

  for (auto fd: existing_read_sets_) {
    // 已经可读的fd保存
    if (FD_ISSET(fd, &read_sets_))
      readable_sets_.emplace(fd);
    // 维护已设置的fd
    FD_SET(fd, &read_sets_);
  }

  for (auto fd: existing_write_sets_) {
    // 已经可读的fd保存
    if (FD_ISSET(fd, &write_sets_))
      writable_sets_.emplace(fd);
    // 维护已设置的fd
    FD_SET(fd, &write_sets_);
  }

  for (auto fd: existing_exception_sets_) {
    // 已经可读的fd保存
    if (FD_ISSET(fd, &exception_sets_))
      has_exception_sets_.emplace(fd);
    // 维护已设置的fd
    FD_SET(fd, &exception_sets_);
  }
}

void Selector::clear()
{
  clear_read_sets();
  clear_write_sets();
  clear_exception_sets();
}

void Selector::clear_read_sets()
{
  FD_ZERO(&read_sets_);
  existing_read_sets_.clear();
}

void Selector::clear_write_sets()
{
  FD_ZERO(&write_sets_);
  existing_write_sets_.clear();
}

void Selector::clear_exception_sets()
{
  FD_ZERO(&exception_sets_);
  existing_exception_sets_.clear();
}


} // namespace ST::Net {}