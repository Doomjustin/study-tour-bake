#ifndef STUDY_TOUR_FILE_DESCRIPTOR_H
#define STUDY_TOUR_FILE_DESCRIPTOR_H


namespace ST {

/**
 * @brief 对文件描述符的封装
 *
 */
class FileDescriptor {
friend class File;
friend class Socket;

public:
  explicit FileDescriptor(int fd = -1);

  FileDescriptor(const FileDescriptor&);
  FileDescriptor& operator=(const FileDescriptor& other);

  FileDescriptor(FileDescriptor&& other) noexcept;
  FileDescriptor& operator=(FileDescriptor&& other) noexcept;

  ~FileDescriptor();

  /**
   * @brief 当前的fd是否是一个有效的文件描述符
   *
   * @return true
   * @return false
   */
  constexpr bool is_valid() const { return fd_ != -1; }

private:
  int fd_;
};

} // namespace ST

#endif // STUDY_TOUR_FILE_DESCRIPTOR_H