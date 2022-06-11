#ifndef CPP_STUDY_TOUR_SYSTEM_GROUP_INFO_H
#define CPP_STUDY_TOUR_SYSTEM_GROUP_INFO_H

#include <sys/types.h>
#include <grp.h>


namespace CST::System {

/**
 * @brief 访问组相关信息
 *
 */
class GroupInfo {
public:
  static char* name() { return group_info_->gr_name; }
  static char* password() { return group_info_->gr_passwd; }
  static int gid() { return group_info_->gr_gid; }
  static char** members() { return group_info_->gr_mem; }

private:
  static struct group* group_info_;
};

} // namespace CST::System

#endif // CPP_STUDY_TOUR_SYSTEM_GROUP_INFO_H