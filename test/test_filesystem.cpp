#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "ST/FileSystem.h"


int main()
{
  auto console_logger = spdlog::stdout_color_mt("ST console logger");
  spdlog::set_default_logger(console_logger);

  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %n [%^%l%$][%@ %!][%P %t] %v");
  spdlog::set_level(spdlog::level::debug);
  ST::FileSystem::File file{ "test.file" };

  file.open(O_RDONLY);

  SPDLOG_INFO("opened(): {}", file.opened());
  // file.open(O_WRONLY);

  file.close();

  return EXIT_SUCCESS;
}