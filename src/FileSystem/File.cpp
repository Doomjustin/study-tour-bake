#include "ST/FileSystem/File.h"

#include <error.h>
#include <string.h>
#include <fcntl.h>

#include <stdexcept>

#include <spdlog/spdlog.h>

#include "ST/Common.h"


namespace ST::FileSystem {

File::File(const std::string& file_name, int fd)
  : fd_{ fd }, file_name_{ file_name }
{}

/**
 * @details 复制语义自动调用dup，也就是说每个File对象都保存的不同fd<br/>
 * 如果你不想要复制的开销，则应该移动语义
 *
 */
File::File(const File& other)
  : fd_{ -1 },
    file_name_{ other.file_name_ }
{
  fd_ = ::dup(other.fd_);
  if (fd_ == -1)
    throw std::system_error{ errno, std::generic_category(), "can't dup file" };
}

/**
 * @details
 * @warning 如果当前file是打开的，则应该先close再复制，否则资源泄露
 */
File& File::operator=(const File& other)
{
  fd_ = ::dup(other.fd_);
  if (fd_ == -1)
    throw std::system_error{ errno, std::generic_category(), "can't dup file" };

  file_name_ = other.file_name_;

  return *this;
}

File::File(File&& other) noexcept
  : fd_{ other.fd_ },
    file_name_{ std::move(other.file_name_) }
{
  other.fd_ = -1;
}

/**
 * @warning 如果此时file是打开的，则应该先close，否则资源泄露
 *
 */
File& File::operator=(File&& other) noexcept
{
  std::swap(*this, other);
  return *this;
}


File File::create(const char* file_name, mode_t mode)
{
  SPDLOG_INFO("creating file {} on mode {}", file_name, mode);

  File file{ file_name };
  file.open(ST::CREATE_FILE_FLAG, mode);

  SPDLOG_INFO("created file {} on mode {}", file_name, mode);
  return file;
}

void File::change_mode(const char* path, mode_t mode)
{
  SPDLOG_INFO("changing file {} mode to {}", path, mode);

  auto res = ::chmod(path, mode);
  if (res == -1) {
    SPDLOG_ERROR("can't change file {} mode to {}", path, mode);
    throw std::system_error{ errno, std::generic_category(), "can't change mode" };
  }

  SPDLOG_INFO("changed file {} mode to {}", path, mode);
}

void File::change_owner(const char* path, uid_t owner, gid_t group)
{
  SPDLOG_INFO("changing owner to {}, group to {}", owner, group);

  auto res = ::chown(path, owner, group);
  if (res == -1) {
    SPDLOG_ERROR("can't change owner to {}, group to {}", owner, group);
    throw std::system_error{ errno, std::generic_category(), "can't change owner or/and group" };
  }

  SPDLOG_INFO("changed owner to {}, group to {}", owner, group);
}

void File::resize(const char* path, off_t size)
{
  SPDLOG_INFO("resizing file {} size to {}", path, size);

  auto res = ::truncate(path, size);
  if (res == -1) {
    SPDLOG_ERROR("can't resize file {} size to {}", path, size);
    throw std::system_error{ errno, std::generic_category(), "can't resize file" };
  }

  SPDLOG_INFO("resized file {} size to {}", path, size);
}

File File::tmpfile(const char* file_name, int flags, mode_t mode)
{
  SPDLOG_INFO("creating temporary file {} with flags {} and mode {}", file_name, flags, mode);

  File tmp_file{ file_name };
  tmp_file.open(flags, mode);
  tmp_file.as_tmpfile();

  SPDLOG_INFO("created temporary file {} with flags {} and mode {}", file_name, flags, mode);
  return tmp_file;
}

void File::commit()
{
  SPDLOG_INFO("try commiting cached writes to persistent storage");
  ::sync();
}

/**
 * @details 此操作仅仅只是减少文件表项的连接数，只有当连接数减少到0后，文件才会真正的从磁盘删除
 *
 */
void File::remove(const char* file_name)
{
  SPDLOG_INFO("removing file {}", file_name);

  auto res = ::unlink(file_name);
  if (res == -1) {
    SPDLOG_ERROR("removing {}", file_name);
    throw std::system_error{ errno, std::generic_category(), "can't remove file" };
  }

  SPDLOG_INFO("removed file {}", file_name);
}

mode_t File::global_mode(mode_t mode)
{
  SPDLOG_INFO("change mask {}", mode);

  return ::umask(mode);
}

/**
 * @details 调用rename修改对应文件的名字
 *
 */
void File::file_name(const std::string& new_name)
{
  SPDLOG_INFO("file name will change from {} to {}", file_name_, new_name);
  auto res = ::rename(file_name_.c_str(), new_name.c_str());

  if (res == -1) {
    SPDLOG_ERROR("can't rename: {}", strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't rename file" };
  }

  file_name_ = new_name;
  SPDLOG_INFO("file name changed to {} now", file_name_);
}

void File::open(int flags)
{
  if (opened()) {
    SPDLOG_ERROR("file[{}, {}] has been opened, you shouldn't reopen it", fd_, file_name_);
    throw ReopenFileException{ "you shouldn't reopen a file" };
  }

  SPDLOG_INFO("opening file {} with flag {}", file_name_, flags);

  fd_ = ::open(file_name_.c_str(), flags);

  if (fd_ == -1) {
    SPDLOG_ERROR("can't open {} with flag {}: {}", file_name_, flags, strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't open file" };
  }

  SPDLOG_INFO("opened file[{}, {}] with flag {}", fd_, file_name_, flags);
}

/**
 * @todo 只有几种特定用法需要用到mode参数，以后可能会删除此函数，然后添加对应的函数
 *
 */
void File::open(int flags, mode_t mode)
{
  if (opened()) {
    SPDLOG_ERROR("file[{}, {}] has been opened, you shouldn't reopen it", fd_, file_name_);
    throw ReopenFileException{ "you shouldn't reopen a file" };
  }

  SPDLOG_INFO("opening file {} with flag {}, mode {}", file_name_, flags, mode);

  fd_ = ::open(file_name_.c_str(), flags, mode);

  if (fd_ == -1) {
    SPDLOG_ERROR("can't open {} with flag {}, mode {}: {}", file_name_, flags, mode, strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't open file" };
  }

  SPDLOG_INFO("opened file[{}, {}] with flag {}, mode {}", fd_, file_name_, flags, mode);
}

void File::close()
{
  if (fd_ == -1) {
    SPDLOG_ERROR("can't close before calling open");
    throw std::logic_error{ "can't close before calling open" };
  }

  SPDLOG_INFO("closing file[{}, {}]", fd_, file_name_);

  auto res = ::close(fd_);
  if (res == -1) {
    SPDLOG_ERROR("can't close file[{}, {}]: {}", fd_, file_name_, strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't close file" };
  }

  fd_ = -1;
  SPDLOG_INFO("closed file[{}, {}]", fd_, file_name_);
}

void File::as_tmpfile()
{
  SPDLOG_INFO("try converting as a tmpfile");

  auto res = ::unlink(file_name_.c_str());
  if (res == -1) {
    SPDLOG_ERROR("can't unlink file {}", file_name_);
    throw std::system_error{ errno, std::generic_category(), "can't open file" };
  }

  SPDLOG_INFO("converted as a tmpfile");
}

} // namespace ST::FileSystem