#ifndef STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H
#define STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H

#include <sys/types.h>
#include <sys/stat.h>

#include <string>

#include "File.h"


namespace ST::FileSystem {


class FileStatus {
public:
  explicit FileStatus(const std::string& file_name)
    : file_name_{ file_name }, status_{}
  {
    auto res = ::lstat(file_name.c_str(), &status_);
  }
  explicit FileStatus(const File& file)
    : FileStatus{ file.file_name() }
  {}

  bool is_regular() const { return S_ISREG(status_.st_mode); }
  bool is_directory() const { return S_ISDIR(status_.st_mode); }
  bool is_character_special() const { return S_ISCHR(status_.st_mode); }
  bool is_block_special() const { return S_ISBLK(status_.st_mode); }
  bool is_FIFO() const { return S_ISFIFO(status_.st_mode); }
  bool is_socket() const { return S_ISSOCK(status_.st_mode); }
  bool is_symbolic_link() const { return S_ISLNK(status_.st_mode); }

  bool is_message_queue() const { return S_TYPEISMQ(&status_); }
  bool is_semaphore() const { return S_TYPEISSEM(&status_); }
  bool is_shared_memory() const { return S_TYPEISSHM(&status_); }

  std::string file_name() const { return file_name_; }

private:
  std::string file_name_;
  struct stat status_;
};

} // namespace ST::FileSystem

#endif // STUDY_TOUR_FILE_SYSTEM_FILE_STATUS_H