#ifndef CPP_STUDY_TOUR_SYSTEM_SYSTEM_INFO_H
#define CPP_STUDY_TOUR_SYSTEM_SYSTEM_INFO_H

#include <sys/types.h>
#include <sys/utsname.h>


namespace CST::System {

/**
 * @brief 访问System相关信息
 *
 */
class SystemInfo {
public:
  SystemInfo();

  char* name() { return system_info_.sysname; }
  char* node_name() { return system_info_.nodename; }
  char* release() { return system_info_.release; }
  char* version() { return system_info_.version; }
  char* machine() { return system_info_.machine; }

private:
  struct utsname system_info_;
};

} // namespace CST::System

#endif // CPP_STUDY_TOUR_SYSTEM_SYSTEM_INFO_H