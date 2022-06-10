#ifndef STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H
#define STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H

#include <sys/types.h>
#include <sys/stat.h>

#include <string>
#include <stdexcept>

#include <spdlog/spdlog.h>

#include "File.h"


namespace ST::FileSystem {

class InvalidFileStatus: std::logic_error {
public:
  InvalidFileStatus(const std::string& msg)
    : std::logic_error{ msg }
  {}
};


class FileStatus {
public:
  explicit FileStatus(const std::string& file_name)
    : file_name_{ file_name }, status_{}
  {
    SPDLOG_INFO("getting file[{}] status", file_name);

    auto res = ::lstat(file_name.c_str(), &status_);
    if (res == -1) {
      SPDLOG_ERROR("can't get file[{}] status", file_name);
      throw InvalidFileStatus{ "can't get file status" };
    }

    SPDLOG_INFO("got file[{}] status", file_name);
  }

  explicit FileStatus(const File& file)
    : FileStatus{ file.file_name() }
  {}

  /**
   * @brief 是否是普通文件
   *
   * @return true
   * @return false
   */
  bool is_regular() const { return S_ISREG(status_.st_mode); }

  /**
   * @brief 是否是文件夹
   *
   * @return true
   * @return false
   */
  bool is_directory() const { return S_ISDIR(status_.st_mode); }

  /**
   * @brief 是否是字符特殊文件
   *
   * @return true
   * @return false
   */
  bool is_character_special() const { return S_ISCHR(status_.st_mode); }

  /**
   * @brief 是否是块特殊文件
   *
   * @return true
   * @return false
   */
  bool is_block_special() const { return S_ISBLK(status_.st_mode); }

  /**
   * @brief 是否是fifo(管道)
   *
   * @return true
   * @return false
   */
  bool is_FIFO() const { return S_ISFIFO(status_.st_mode); }

  /**
   * @brief 是否是socket(套接字)
   *
   * @return true
   * @return false
   */
  bool is_socket() const { return S_ISSOCK(status_.st_mode); }

  /**
   * @brief 是否是符号链接
   *
   * @return true
   * @return false
   */
  bool is_symbolic_link() const { return S_ISLNK(status_.st_mode); }

  bool is_message_queue() const { return S_TYPEISMQ(&status_); }
  bool is_semaphore() const { return S_TYPEISSEM(&status_); }
  bool is_shared_memory() const { return S_TYPEISSHM(&status_); }

  /**
   * @brief 文件名
   *
   * @return std::string 文件名
   */
  std::string file_name() const { return file_name_; }

private:
  std::string file_name_;
  struct stat status_;
};

} // namespace ST::FileSystem

#endif // STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H