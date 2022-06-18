#ifndef STUDY_TOUR_NET_IPV4_ADDRESS_H
#define STUDY_TOUR_NET_IPV4_ADDRESS_H

#include <netinet/in.h>

#include <string>
#include <memory>

#include "Address.h"
#include "ST/TypeTraits.h"
#include "ST/Global.h"


namespace ST::Net {

/**
 * @brief IPv4用地址
 *
 */
class IPv4Address: public Address {
public:
  IPv4Address();
  IPv4Address(const std::string& address, in_port_t port);

  /**
   * @brief address由系统自动分配
   *
   * @param port
   */
  IPv4Address(in_port_t port);

  ~IPv4Address() {}

  sockaddr* address() const noexcept override { return (struct sockaddr*) &address_; }

  in_port_t port() const noexcept override { return address_.sin_port; }

  Family family() const noexcept override { return Family::IPv4; }

  socklen_t length() const noexcept override { return sizeof(address_); }

  std::string to_string() const noexcept override;

private:
  sockaddr_in address_;
};

} // namespace ST::Net

#endif // STUDY_TOUR_NET_IPV4_ADDRESS_H