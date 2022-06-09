#include <iostream>
#include <string>

#include <spdlog/spdlog.h>
#include <fmt/chrono.h>
#include <boost/regex.hpp>


int main()
{
  using namespace std::literals::chrono_literals;
  fmt::print("Default format: {} {}\n", 42s, 100ms);
  fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);

  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed..");

  // change log pattern
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // Compile time log levels
  // define SPDLOG_ACTIVE_LEVEL to desired level
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");

  // test Boost
  std::string line;
  boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

  while (std::cin)
  {
      std::getline(std::cin, line);
      boost::smatch matches;
      if (boost::regex_match(line, matches, pat))
          std::cout << matches[2] << std::endl;
  }
}