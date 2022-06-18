#include "ST/Net/IPv6Address.h"

#include <string.h>
#include <arpa/inet.h>

#include <system_error>

#include <spdlog/spdlog.h>


namespace ST::Net {

IPv6Address::IPv6Address()
  : address_{}
{
  bzero(&address_, sizeof(address_));
}

IPv6Address::IPv6Address(const std::string& address, in_port_t port)
  : address_{}
{
  bzero(&address_, sizeof(address_));
  address_.sin6_family = AF_INET6;
  address_.sin6_port = htons(port);
  auto res = inet_pton(AF_INET6, address.c_str(), &address_.sin6_addr);
  if (res == -1) {
    SPDLOG_ERROR("can't convert address[{}] from text to binary form", address);
    throw std::system_error{ errno, std::generic_category(),
          "can't convert address from text to binary form" };
  }
}

IPv6Address::IPv6Address(in_port_t port)
  : address_{}
{
  bzero(&address_, sizeof(address_));
  address_.sin6_family = AF_INET6;
  address_.sin6_port = htons(port);
  address_.sin6_addr = IN6ADDR_ANY_INIT;
}


std::string IPv6Address::to_string() const noexcept
{
  char buffer[MAX_BUFFER];

  inet_ntop(AF_INET6, &address_.sin6_addr, buffer, MAX_BUFFER);

  return fmt::format("type: IPv6, address: {}, port: {}", buffer, address_.sin6_port);
}

} // namespace ST::Net