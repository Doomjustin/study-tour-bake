#include "ST/Exercise.h"


void daemonize(const char* cmd)
{
  umask(0);

  struct rlimit rl;
  if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    err_quit("%s: can't get file limit", cmd);

  pid_t pid;
  if ((pid = fork()) < 0)
    err_quit("%s: can't fork", cmd);
  else if (pid != 0)
    exit(EXIT_SUCCESS);
  setsid();

  struct sigaction sa;
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGHUP, &sa, nullptr) < 0)
    err_quit("%s: can't ignore SIGHUP", cmd);

  if ((pid = fork()) < 0)
    err_quit("%s: can't fork", cmd);
  else if (pid == 0)
    exit(EXIT_SUCCESS);

  if (chdir("/") < 0)
    err_quit("%s: can't change directory to /", cmd);

  if (rl.rlim_max == RLIM_INFINITY)
    rl.rlim_max = 1024;
  for (int i = 0; i < rl.rlim_max; ++i)
    close(i);

  auto fd0 = open("/dev/null", O_RDWR);
  auto fd1 = dup(0);
  auto fd2 = dup(0);

  openlog(cmd, LOG_CONS, LOG_DAEMON);
  if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
    syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
    exit(EXIT_FAILURE);
  }
}

ssize_t readn(int fd, char* buf, size_t nbytes)
{
  auto nleft = nbytes;
  ssize_t nread;
  while (nleft > 0) {
    if ((nread = read(fd, buf, nleft)) < 0) {
      if (nleft == nbytes)
        return -1;
      else
        break;
    }
    else if (nread == 0) {
      break;
    }

    nleft -= nread;
    buf += nread;
  }

  return nbytes - nleft;
}

ssize_t writen(int fd, char* buf, size_t nbytes)
{
  auto nleft = nbytes;
  ssize_t nwritten;
  while (nleft > 0) {
    if ((nwritten = write(fd, buf, nleft)) < 0) {
      if (nleft == nbytes)
        return -1;
      else
        break;
    }
    else if (nwritten == 0) {
      break;
    }

    nleft -= nwritten;
    buf += nwritten;
  }

  return nbytes - nleft;
}

ssize_t read_line(int fd, void* buffer, size_t max_line)
{
  char* ptr = (char*) buffer;
  ssize_t n;
  ssize_t read_bytes;
  char c;
  for (n = 1; n < max_line; ++n) {
  again:
    if ((read_bytes = read(fd, &c, 1)) == 1) {
      *ptr++ = c;
      if (c == '\n')
        break;
    }
    else if (read_bytes == 0) {
      *ptr = 0;
      return n - 1;
    }
    else {
      if (errno == EINTR)
        goto again;
      return -1;
    }
  }

  *ptr = 0;
  return n;
}

static void err_doit(int errno_flag, int error_no, const char* fmt, va_list ap)
{
  char buffer[MAX_LINE];

  vsnprintf(buffer, MAX_LINE - 1, fmt, ap);
  if (errno_flag)
    snprintf(buffer + strlen(buffer), MAX_LINE - strlen(buffer) - 1,
          ": %s", strerror(error_no));

  strcat(buffer, "\n");
  fflush(stdout);
  fputs(buffer, stderr);
  fflush(nullptr);
}

void err_ret(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}

void err_sys(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

void err_cont(int error_no, const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error_no, fmt, ap);
  va_end(ap);
}

void err_exit(int error_no, const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error_no, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

void err_dump(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort();
  exit(EXIT_FAILURE);
}

void err_msg(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}

void err_quit(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

int log_to_stderr = -1;

static void log_doit(int errno_flag, int error_no, int priority, const char* fmt, va_list ap)
{
  char buffer[MAX_LINE];

  vsnprintf(buffer, MAX_LINE - 1, fmt, ap);
  if (errno_flag)
    snprintf(buffer + strlen(buffer), MAX_LINE - strlen(buffer) - 1,
          ": %s", strerror(error_no));

  strcat(buffer, "\n");
  if (log_to_stderr) {
    fflush(stdout);
    fputs(buffer, stderr);
    fflush(nullptr);
  }
  else {
    syslog(priority, "%s", buffer);
  }
}

void log_open(const char* ident, int option, int facility)
{
  if (log_to_stderr == 0)
    openlog(ident, option, facility);
}

void log_ret(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
}

void log_sys(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

void log_msg(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(0, 0, LOG_ERR, fmt, ap);
  va_end(ap);
}

void log_quit(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(0, 0, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

void log_exit(int error_no, const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, error_no, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}
