#ifndef CPP_STUDY_TOUR_SYSTEM_USER_INFO_H
#define CPP_STUDY_TOUR_SYSTEM_USER_INFO_H

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


namespace CST::System {

/**
 * @brief User相关信息
 *
 */
class UserInfo {
public:
  static char* name() { return user_info_->pw_name; }
  static char* password() { return user_info_->pw_passwd; }
  static uid_t user_id() { return user_info_->pw_uid; }
  static gid_t group_id() { return user_info_->pw_gid; }
  static char* comment() { return user_info_->pw_gecos; }
  static char* init_dir() { return user_info_->pw_dir; }
  static char* init_shell() { return user_info_->pw_shell; }

  static void user_id(uid_t uid) { ::setuid(uid); }
  static void group_id(gid_t gid) { ::setgid(gid); }

private:
  static struct passwd* user_info_;
};


} // namespace CST::System

#endif // CPP_STUDY_TOUR_SYSTEM_USER_INFO_H