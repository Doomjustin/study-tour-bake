#ifndef STUDY_TOUR_TEMPLATE_H
#define STUDY_TOUR_TEMPLATE_H

#include <sys/types.h>
#include <fcntl.h>

#include <cstddef>
#include <cstdint>


namespace ST {

// 默认新文件的访问权限
static constexpr auto FILE_MODE = S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH;
// 一行字符串最大字符数
static constexpr auto MAX_LINE = 4096;
// 默认打开文件flag
static constexpr int CREATE_FILE_FLAG = O_WRONLY | O_CREAT | O_TRUNC;

} // namespace ST

#endif // STUDY_TOUR_TEMPLATE_H

