/**
 * @file File.h
 * @author doom (1075101233doom@gmail.com)
 * @brief Unix文件相关操作封装，基本只是归类和打上相应的log即throw exception
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STUDY_TOUR_FILE_SYSTEM_FILE_H
#define STUDY_TOUR_FILE_SYSTEM_FILE_H

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <stdexcept>


namespace ST::FileSystem {

// forward statement
class FileStatus;


/**
 * @brief 重复打开文件错误
 *
 */
class ReopenFileException: public std::logic_error {
public:
  ReopenFileException(const std::string& msg)
    : std::logic_error{ msg }
  {}
};

/**
 * @brief 文件未打开错误
 *
 */
class FileNotOpenedException: public std::logic_error {
public:
  FileNotOpenedException(const std::string& msg)
    : std::logic_error{ msg }
  {}
};

/**
 * @brief 封装Unix中和file相关的操作
 *
 * @warning 并不是RAII的类，所以不会自动close
 */
class File {
public:
  File(const std::string& file_name, int fd = -1);

  File(const File& other);
  File& operator=(const File& other);

  File(File&& other) noexcept;
  File& operator=(File&& other) noexcept;

  ~File();

  /**
   * @brief 将所有修改过的快缓冲区排入写队列，不等待结果便返回
   *
   */
  static void commit();

  /**
   * @brief 创建新文件
   *
   * @param file_name 文件名
   * @param mode      访问权限
   * @return File     创建的文件，已经open
   */
  static File create(const char* file_name, mode_t mode);

  /**
   * @brief 修改文件的访问权限
   *
   * @param path 目标文件
   * @param mode 新访问权限
   */
  static void change_mode(const char* path, mode_t mode);

  /**
   * @brief 更改owner或group
   *
   * @param path
   * @param owner
   * @param group
   */
  static void change_owner(const char* path, uid_t owner = 0, gid_t group = 0);

  /**
   * @brief 修改文件大小
   *
   * @param path    目标文件
   * @param length  修改后的大小
   */
  static void resize(const char* path, off_t size);

  /**
   * @brief 创建临时文件
   *
   * @param file_name 临时文件名
   * @param flags     打开标志
   * @param mode      访问权限
   * @return File     临时文件
   */
  static File tmpfile(const char* file_name, int flags, mode_t mode);

  /**
   * @brief 删除文件
   *
   * @param file_name 文件名
   */
  static void remove(const char* file_name);

  /**
   * @brief 全局的访问权限(mask)
   *
   * @param mode    访问权限
   * @return mode_t 旧的访问权限
   */
  static mode_t global_mode(mode_t mode);

  /**
   * @brief 当前是否已经打开了一个文件
   *
   * @return true     已打开一个文件
   * @return false    未打开文件
   */
  constexpr bool opened() const { return fd_ != -1; }

  /**
   * @brief 已打开/将要打开的文件的文件名
   *
   * @return std::string 文件名
   */
  std::string file_name() const { return file_name_; }

  /**
   * @brief 修改文件名
   *
   * @param new_name 将已有的文件名修改为new_name
   */
  void file_name(const std::string& new_name);

  /**
   * @brief 打开文件
   *
   * @param flags 打开标志，同Unix的open()
   */
  void open(int flags = O_RDWR);

  /**
   * @brief 打开文件
   *
   * @param flags 打开标志，同Unix的open
   * @param mode 创建时设置访问权限，同Unix的open
   */
  void open(int flags, mode_t mode);

  /**
   * @brief 关闭已打开文件
   *
   */
  void close();

  /**
   * @brief 此文件作为临时文件存在
   *
   */
  void as_tmpfile();

  /**
   * @brief 从打开的文件中读取数据
   *
   * @param buffer      读出数据所存储的buffer
   * @param n_bytes     最多读出n_bytes的数据
   * @return ssize_t    实际读出的数据
   */
  ssize_t read(void* buffer, size_t n_bytes) const;

  /**
   * @brief 向打开的文件中写入数据
   *
   * @param buffer      待写入的数据
   * @param n_bytes     最多写入n_bytes的数据
   * @return ssize_t    实际写入的数据
   */
  ssize_t write(const void* buffer, size_t n_bytes);

  /**
   * @brief 从offset的地方读出n_bytes的数据，写入到buffer中
   *
   * @param buffer      读出的数据写入的buffer
   * @param n_bytes     最多读出n_bytes的数据
   * @param offset
   * @return ssize_t    实际读出的数据
   */
  ssize_t pread(void* buffer, size_t n_bytes, off_t offset) const;

  /**
   * @brief 从打开文件的offset处写入n_bytes的数据，数据源为buffer
   *
   * @param buffer      待写入数据
   * @param n_bytes     最多写入n_bytes数据
   * @param offset
   * @return ssize_t    实际写入的数据
   */
  ssize_t pwrite(const void* buffer, size_t n_bytes, off_t offset);

  /**
   * @brief 将系统缓冲区的数据同步到实际的文件里
   *
   */
  void synchronize();

  /**
   * @brief 只同步文件数据的部分
   *
   */
  void data_synchronize();

  /**
   * @brief 新增flags
   *
   * @param flags
   */
  void add_flags(int flags);

  /**
   * @brief 移除flags
   *
   * @param flags
   */
  void remove_flags(int flags);

  /**
   * @brief 定位offset
   *
   * @param offset  偏移量
   * @param whence  标定点
   * @return off_t  从文件起始的offset
   */
  off_t seek(off_t offset, int whence = SEEK_SET);

  /**
   * @brief 文件信息
   *
   * @return FileStatus 文件信息
   */
  FileStatus status() const;

  /**
   * @brief 检查相应权限是否允许
   *
   * @param mode      权限
   * @return true
   * @return false
   */
  bool access(int mode) const;

  /**
   * @brief
   *
   * @param new_mode
   */
  void mode(int new_mode);

  /**
   * @brief 改变文件所有权
   *
   * @param new_owner
   * @param group
   */
  void owner(uid_t new_owner, gid_t group);

  /**
   * @brief 改变文件大小
   *
   * @param new_size
   */
  void resize(off_t new_size);

private:
  int fd_;
  // TODO: 考虑换成path
  std::string file_name_;
};

} // namespace ST::FileSystem

#endif // STUDY_TOUR_FILE_SYSTEM_FILE_H