#ifndef STUDY_TOUR_SYSTEM_ENVIRONMENT_H
#define STUDY_TOUR_SYSTEM_ENVIRONMENT_H

#include <sys/types.h>
#include <sys/resource.h>


namespace ST::System {

class Environment {
public:
  static char* get(const char* key);

  static void put(const char* key_value);

  /**
   * @brief 覆盖已有的key
   *
   * @param key
   * @param value
   */
  static void put(const char* key, const char* value);

  /**
   * @brief 不覆盖已有key
   *
   * @param key
   * @param value
   */
  static void try_put(const char* key, const char* value);
  static void remove(const char* key);
};

} // namespace ST::System

#endif // STUDY_TOUR_SYSTEM_ENVIRONMENT_H