#ifndef STUDY_TOUR_EXCEPTION_H
#define STUDY_TOUR_EXCEPTION_H

#include <errno.h>
#include <string.h>

#include <stdexcept>
#include <system_error>

#include <fmt/core.h>

namespace ST {

/**
 * @brief 重复打开文件错误
 *
 */
class ReopenFileException: public std::logic_error {
public:
  template<typename... T>
  ReopenFileException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

/**
 * @brief 文件未打开错误
 *
 */
class FileNotOpenedException: public std::logic_error {
public:
  template<typename... T>
  FileNotOpenedException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

/**
 * @brief 未定义的family
 *
 */
class UndefinedFamilyException: std::logic_error {
public:
  template<typename... T>
  UndefinedFamilyException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

/**
 * @brief 未定义的Type
 *
 */
class UndefinedTypeException: std::logic_error {
public:
  template<typename... T>
  UndefinedTypeException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

/**
 * @brief 重复connect错误
 *
 */
class ReconnectedException: public std::logic_error {
public:
  template<typename... T>
  ReconnectedException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

/**
 * @brief 无效wait调用，当前进程未运行
 *
 */
class InvalidProcessWaitException: public std::logic_error {
public:
  template<typename... T>
  InvalidProcessWaitException(fmt::format_string<T...> fmt, T&&... args)
    : std::logic_error{ fmt::format(fmt, std::forward<T>(args)...) }
  {}
};

} // namespace ST

#endif // STUDY_TOUR_EXCEPTION_H
