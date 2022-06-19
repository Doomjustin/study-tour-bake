#ifndef STUDY_TOUR_NET_SELECTOR_H
#define STUDY_TOUR_NET_SELECTOR_H

#include <sys/select.h>
#include <sys/time.h>

#include <type_traits>
#include <algorithm>
#include <unordered_set>

#include <spdlog/spdlog.h>

#include "ST/Exception.h"
#include "ST/TypeTraits.h"


namespace ST::Net {

/**
 * @brief select函数的封装
 *
 */
class Selector {
public:
  Selector();

  // 设置的fd不能超过这个值
  static constexpr int max_size() { return FD_SETSIZE; }

  template<typename... FdType>
  void add_read_set(FdType... fd)
  {
    add_read_set_aux(fd...);
  }

  template<typename... FdType>
  void remove_read_set(FdType... fd)
  {
    remove_read_set_aux(fd...);
  }

  template<typename... FdType>
  void add_write_set(FdType... fd)
  {
    add_write_set_aux(fd...);
  }

  template<typename... FdType>
  void remove_write_set(FdType... fd)
  {
    remove_write_set_aux(fd...);
  }

  template<typename... FdType>
  void add_exception_set(FdType... fd)
  {
    add_exception_set_aux(fd...);
  }

  template<typename... FdType>
  void remove_exception_set(FdType... fd)
  {
    remove_exception_set_aux(fd...);
  }

  std::unordered_set<int> readable_sets() const { return readable_sets_; }
  std::unordered_set<int> writable_sets() const { return writable_sets_; }
  std::unordered_set<int> has_exception_sets() const { return has_exception_sets_; }

  // 拿到的是上一次wait_for的结果
  std::unordered_set<int> read_sets() const { return existing_read_sets_; }
  std::unordered_set<int> write_sets() const { return existing_write_sets_; }
  std::unordered_set<int> exception_sets() const { return existing_exception_sets_; }

  void clear();
  void clear_read_sets();
  void clear_write_sets();
  void clear_exception_sets();

  // 等待一定时间，当有可用的fd时，会提前结束
  timeval wait_for(long seconds, long micro_seconds);

private:
  fd_set write_sets_;
  fd_set read_sets_;
  fd_set exception_sets_;
  int max_fd_;
  struct timeval wait_for_;
  std::unordered_set<int> existing_write_sets_;
  std::unordered_set<int> existing_read_sets_;
  std::unordered_set<int> existing_exception_sets_;
  std::unordered_set<int> readable_sets_;
  std::unordered_set<int> writable_sets_;
  std::unordered_set<int> has_exception_sets_;

  // 维护已经放入的所有fd
  void update();

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void add_read_set_aux(FdType fd, Tail... tail)
  {
    if (FD_ISSET(fd, &read_sets_))
      SPDLOG_WARN("you're setting same fd[{}] to read sets", fd);

    FD_SET(fd, &read_sets_);
    max_fd_ = std::max(fd + 1, max_fd_);
    existing_read_sets_.emplace(fd);

    SPDLOG_INFO("set fd[{}] to read sets", fd);
    add_read_set_aux(tail...);
  }

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void remove_read_set_aux(FdType fd, Tail... tail)
  {
    if (!FD_ISSET(fd, &read_sets_))
      SPDLOG_WARN("you're removing unseted fd[{}] from read sets", fd);

    FD_CLR(fd, &read_sets_);
    existing_read_sets_.erase(fd);

    SPDLOG_INFO("removed fd[{}] from read sets", fd);
    remove_read_set_aux(tail...);
  }

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void add_write_set_aux(FdType fd, Tail... tail)
  {
    if (FD_ISSET(fd, &write_sets_))
      SPDLOG_WARN("you're setting same fd[{}] to write sets", fd);

    FD_SET(fd, &write_sets_);
    max_fd_ = std::max(fd + 1, max_fd_);
    existing_write_sets_.emplace(fd);

    SPDLOG_INFO("set fd[{}] to write sets", fd);
    add_write_set_aux(tail...);
  }

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void remove_write_set_aux(FdType fd, Tail... tail)
  {
    if (!FD_ISSET(fd, &write_sets_))
      SPDLOG_WARN("you're removing unseted fd[{}] from write sets", fd);

    FD_CLR(fd, &write_sets_);
    existing_write_sets_.erase(fd);

    SPDLOG_INFO("removed fd[{}] from write sets", fd);
    remove_write_set_aux(tail...);
  }

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void add_exception_set_aux(FdType fd, Tail... tail)
  {
    if (FD_ISSET(fd, &exception_sets_))
      SPDLOG_WARN("you're setting same fd[{}] to exception sets", fd);

    FD_SET(fd, &exception_sets_);
    max_fd_ = std::max(fd + 1, max_fd_);
    existing_exception_sets_.emplace(fd);

    SPDLOG_INFO("set fd[{}] to exception sets", fd);
    add_exception_set_aux(tail...);
  }

  template<typename FdType, typename... Tail,
        std::enable_if_t<is_fd_type_v<FdType>, bool> = true>
  void remove_exception_set_aux(FdType fd, Tail... tail)
  {
    if (!FD_ISSET(fd, &exception_sets_))
      SPDLOG_WARN("you're removing unseted fd[{}] from exception sets", fd);

    FD_CLR(fd, &exception_sets_);
    existing_exception_sets_.erase(fd);

    SPDLOG_INFO("removed fd[{}] from exception sets", fd);
    remove_exception_set_aux(tail...);
  }

  void add_read_set_aux() {}
  void remove_read_set_aux() {}
  void add_write_set_aux() {}
  void remove_write_set_aux() {}
  void add_exception_set_aux() {}
  void remove_exception_set_aux() {}
};

} // namespace ST

#endif // STUDY_TOUR_NET_SELECTOR_H