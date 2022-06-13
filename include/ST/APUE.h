#ifndef STUDY_TOUR_APUE_H
#define STUDY_TOUR_APUE_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include <signal.h>


// 默认新文件的访问权限
static constexpr auto FILE_MODE = S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH;
// 一行字符串最大字符数
static constexpr auto MAX_LINE = 4096;
// 默认打开文件flag
static constexpr int CREATE_FILE_FLAG = O_WRONLY | O_CREAT | O_TRUNC;

/**
 * @brief 将进程变为守护进程
 *
 * @param cmd
 */
void daemonize(const char* cmd);

ssize_t readn(int fd, char* buf, size_t nbytes);

ssize_t writen(int fd, char* buf, size_t nbytes);

void err_ret(const char* fmt, ...);

void err_sys(const char* fmt, ...);

void err_cont(int error_no, const char* fmt, ...);

void err_exit(int error_no, const char* fmt, ...);

void err_dump(const char* fmt, ...);

void err_msg(const char* fmt, ...);

void err_quit(const char* fmt, ...);

extern int log_to_stderr;

void log_open(const char* ident, int option, int facility);

void log_ret(const char* fmt, ...);

void log_sys(const char* fmt, ...);

void log_msg(const char* fmt, ...);

void log_quit(const char* fmt, ...);

void log_exit(const char* fmt, ...);

#endif // STUDY_TOUR_APUE_H