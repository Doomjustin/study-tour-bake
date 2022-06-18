#include "ST/Net/IPv4Address.h"

#include <string.h>
#include <arpa/inet.h>

#include <system_error>

#include <spdlog/spdlog.h>


namespace ST::Net {

IPv4Address::IPv4Address()
  : address_{}
{
  bzero(&address_, sizeof(address_));
}

IPv4Address::IPv4Address(const std::string& address, in_port_t port)
  : address_{}
{
  bzero(&address_, sizeof(address_));
  address_.sin_family = AF_INET;
  address_.sin_port = htons(port);
  auto res = inet_pton(AF_INET, address.c_str(), &address_.sin_addr);
  if (res == -1) {
    SPDLOG_ERROR("can't convert address[{}] from text to binary form", address);
    throw std::system_error{ errno, std::generic_category(),
          "can't convert address from text to binary form" };
  }
}

IPv4Address::IPv4Address(in_port_t port)
  : address_{}
{
  bzero(&address_, sizeof(address_));
  address_.sin_family = AF_INET;
  address_.sin_port = htons(port);
  address_.sin_addr.s_addr = htonl(INADDR_ANY);
}


std::string IPv4Address::to_string() const noexcept
{
  char buffer[MAX_BUFFER];

  inet_ntop(AF_INET, &address_.sin_addr, buffer, MAX_BUFFER);

  return fmt::format("type: IPv4, address: {}, port: {}", buffer, address_.sin_port);
}

} // namespace ST::Net