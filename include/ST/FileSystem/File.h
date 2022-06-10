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

/**
 * @brief 重复打开文件错误
 *
 */
class ReopenFileException: std::logic_error {
public:
  ReopenFileException(const std::string& msg)
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


private:
  int fd_;
  // TODO: 考虑换成path
  std::string file_name_;
};

} // namespace ST::FileSystem

#endif // STUDY_TOUR_FILE_SYSTEM_FILE_H