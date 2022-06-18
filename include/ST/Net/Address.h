#ifndef STUDY_TOUR_NET_ADDRESS_H
#define STUDY_TOUR_NET_ADDRESS_H

#include <string>

#include <sys/types.h>
#include <netinet/in.h>

#include "ST/Global.h"


namespace ST::Net {

/**
 * @brief 网络地址抽象接口
 *
 */
class Address {
public:
  ~Address() {}

  virtual sockaddr* address() const noexcept = 0;

  virtual in_port_t port() const noexcept = 0;

  virtual Family family() const noexcept = 0;

  virtual socklen_t length() const noexcept = 0;

  virtual std::string to_string() const noexcept = 0;
};

} // namespace ST::Net

#endif // STUDY_TOUR_NET_ADDRESS_H