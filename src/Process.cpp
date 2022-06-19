#include "ST/Process.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>

#include <stdexcept>
#include <iostream>

#include <spdlog/spdlog.h>

#include "ST/Signal.h"


namespace ST {

ProcessResult::ProcessResult(int status)
  : status_{ status }, initialized_{ true }
{}


ProcessResult Process::wait()
{
  if (pid_ == -1) {
    SPDLOG_ERROR("invalid process waiting because process is not runnnig");
    throw InvalidProcessWaitException{ "invalid process waiting because process is not runnnig" };
  }

  if (waited_ == true) {
    SPDLOG_ERROR("you can't wait for a process twice or more");
    throw InvalidProcessWaitException{ "you can't wait for a process twice or more" };
  }

  SPDLOG_INFO("waiting for process[{}]", pid_);

  int process_status;
  auto res = ::waitpid(pid_, &process_status, 0);
  if (res == -1) {
    SPDLOG_ERROR("wait for process[{}] error: {}", pid_, strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "wait for process error" };
  }

  waited_ = true;
  ProcessResult process_result{ process_status };

  SPDLOG_INFO("waited for process[{}]", pid_);
  return process_result;
}


void sig_child(int signo)
{
  int stat;
  pid_t pid;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    SPDLOG_INFO("child {} terminated", pid);

  return;
}

void Process::auto_remove()
{
  Signal(SIGCHLD, sig_child);
}


namespace ThisProcess {

pid_t process_id()
{
  return getpid();
}

pid_t parent_process_id()
{
  return getppid();
}

uid_t real_user_id()
{
  return getuid();
}

uid_t effective_user_id()
{
  return geteuid();
}

gid_t real_group_id()
{
  return getgid();
}

gid_t effective_group_id()
{
  return getegid();
}

} // namespace CST::ThisProcess
} // namespace CST