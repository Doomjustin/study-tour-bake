#include "ST/System/SystemInfo.h"

#include <spdlog/spdlog.h>


namespace CST::System {

SystemInfo::SystemInfo()
  : system_info_{}
{
  auto res = uname(&system_info_);
  if (res == -1) {
    SPDLOG_ERROR("init SystemInfo failed: {}", strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't get group" };
  }
}

} // namespace CST::System