#include "ST/System/GroupInfo.h"

#include <spdlog/spdlog.h>


namespace CST::System {

struct group* init()
{
  auto* group_info = getgrgid(getuid());
  if (group_info == nullptr) {
    SPDLOG_ERROR("UserInfo init error: {}", strerror(errno));
    throw std::system_error{ errno, std::generic_category(), "can't get group" };
  }

  return group_info;
}

struct group* GroupInfo::group_info_ = init();

} // namespace CST::System