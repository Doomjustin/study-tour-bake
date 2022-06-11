#ifndef STUDY_TOUR_PROCESS_H
#define STUDY_TOUR_PROCESS_H

#include <unistd.h>

#include <utility>
#include <functional>
#include <stdexcept>
#include <string>


namespace ST {

/**
 * @brief 无效wait调用，当前进程未运行
 *
 */
class InvalidProcessWaitException: public std::logic_error {
public:
  InvalidProcessWaitException(const std::string& msg)
    : std::logic_error{ msg }
  {}
};


class ProcessResult {
public:
  explicit ProcessResult(int status);

  ProcessResult(const ProcessResult& other) = delete;
  ProcessResult& operator=(const ProcessResult& other) = delete;

  ProcessResult(ProcessResult&& other) noexcept = default;
  ProcessResult& operator=(ProcessResult&& other) noexcept = default;

  ~ProcessResult() = default;

  constexpr bool normal_exited() const { return WIFEXITED(status_); }
  constexpr int exit_status() const { return WEXITSTATUS(status_); }
  constexpr bool terminated() const { return WIFSIGNALED(status_); }
  constexpr int terminated_by() const { return WTERMSIG(status_); }
#ifdef WCOREDUMP
  constexpr bool core_dump() const { return status_ == 0 ? false : WCOREDUMP(status_); }
#endif
  constexpr bool stopped() const { return WIFSTOPPED(status_); }
  constexpr int stopped_by() const { return WSTOPSIG(status_); }
  // resumed by delivery of SIGCONT
  constexpr bool resumed() const { return WIFCONTINUED(status_); }

private:
  int status_;
  bool initialized_;
};


/**
 * @brief 进程控制相关
 *
 * @warning 进程的方案限制非常多，不好用
 */
class Process {
public:
  template<typename Function, typename... Args>
  explicit Process(Function&& f, Args&&... args)
    : pid_{ -1 }, waited_{ false }
  {
    pid_ = fork();
    if (pid_ == -1) {
      SPDLOG_ERROR("fork error: {}", strerror(errno));
      throw std::system_error{ errno,
            std::generic_category(),
            "fork error" };
    }

    // 只处理子进程
    if (pid_ == 0) {
      std::invoke(std::forward<Function>(f), std::forward<Args>(args)...);
      // 必须直接退出子进程
      exit(0);
    }
  }

  Process(const Process& other) = delete;
  Process& operator=(const Process& other) = delete;

  Process(Process&& other) noexcept = default;
  Process& operator=(Process&& other) noexcept = default;

  ~Process() = default;

  ProcessResult wait();

private:
  pid_t pid_;
  bool waited_;
};


namespace ThisProcess {

pid_t process_id();
pid_t parent_process_id();

uid_t real_user_id();
uid_t effective_user_id();

gid_t real_group_id();
gid_t effective_group_id();

} // namespace ST::ThisProcess
} // namespace ST

#endif // STUDY_TOUR_PROCESS_H