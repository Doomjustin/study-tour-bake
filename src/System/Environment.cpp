#include "ST/System/Environment.h"

#include <stdlib.h>

#include <spdlog/spdlog.h>


namespace ST::System {

char* Environment::get(const char* key)
{
  return ::getenv(key);
}

void Environment::put(const char* key_value)
{
  SPDLOG_INFO("puting key_value {} to environment", key_value);

  auto res = ::putenv(const_cast<char*>(key_value));
  if (res == -1) {
    SPDLOG_ERROR("can't put key_value {} to environment: {}", key_value, strerror(errno));
    throw std::system_error{ errno,
          std::generic_category(),
          "can't put key_value to environment" };
  }

  SPDLOG_INFO("put key_value {} to environment", key_value);
}

void Environment::put(const char* key, const char* value)
{
  SPDLOG_INFO("puting {} = {} to environment", key, value);

  auto res = ::setenv(key, value, 1);
  if (res == -1) {
    SPDLOG_ERROR("can't put {} = {} to environment: {}", key, value, strerror(errno));
    throw std::system_error{ errno,
          std::generic_category(),
          "can't put key_value to environment" };
  }

  SPDLOG_INFO("put {} = {} to environment", key, value);
}

void Environment::try_put(const char* key, const char* value)
{
  SPDLOG_INFO("try puting {} = {} to environment", key, value);

    auto res = ::setenv(key, value, 0);
  if (res == -1) {
    SPDLOG_ERROR("can't put {} = {} to environment: {}", key, value, strerror(errno));
    throw std::system_error{ errno,
          std::generic_category(),
          "can't put key_value to environment" };
  }

  SPDLOG_INFO("try put {} = {} to environment", key, value);
}

void Environment::remove(const char* key)
{
  SPDLOG_INFO("removing {} from environment", key);

  auto res = ::unsetenv(key);
  if (res == -1) {
    SPDLOG_ERROR("can't remove {} from environment: {}", key, strerror(errno));
    throw std::system_error{ errno,
          std::generic_category(),
          "can't remove from environment" };
  }

  SPDLOG_INFO("remove {} from environment", key);
}

} // namespace ST::System