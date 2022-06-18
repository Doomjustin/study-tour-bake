#ifndef STUDY_TOUR_NET_IPV6_ADDRESS_H
#define STUDY_TOUR_NET_IPV6_ADDRESS_H

#include <netinet/in.h>

#include <string>
#include <memory>

#include "Address.h"
#include "ST/TypeTraits.h"


namespace ST::Net {

/**
 * @brief IPv6用地址
 *
 */
class IPv6Address: public Address {
public:
  IPv6Address();
  IPv6Address(const std::string& address, in_port_t port);

  /**
   * @brief address有系统自动分配
   *
   * @param port
   */
  IPv6Address(in_port_t port);

  ~IPv6Address() {}

  sockaddr* address() const noexcept override { return (struct sockaddr*) &address_; }

  in_port_t port() const noexcept override { return address_.sin6_port; }

  Family family() const noexcept override { return Family::IPv6; }

  socklen_t length() const noexcept override { return sizeof(address_); }

  std::string to_string() const noexcept override;

private:
  sockaddr_in6 address_;
};

} // namespace ST::Net

#endif // STUDY_TOUR_NET_IPV6_ADDRESS_H