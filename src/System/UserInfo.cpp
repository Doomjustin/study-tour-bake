#include "ST/System/UserInfo.h"

#include <spdlog/spdlog.h>


namespace CST::System {

struct passwd* init()
{
  auto* user_info = getpwuid(getuid());
  if (user_info == nullptr) {
    SPDLOG_ERROR("UserInfo init error: {}", strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't get passwd" };
  }

  return user_info;
}

struct passwd* UserInfo::user_info_ = init();

} // namespace CST::System