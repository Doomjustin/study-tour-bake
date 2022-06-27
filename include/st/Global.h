#ifndef STUDY_TOUR_GLOBAL_H
#define STUDY_TOUR_GLOBAL_H

#include <netinet/in.h>
#include <sys/types.h>

#include <string>
#include <cstddef>
#include <cstdint>

#include "Concept.h"


namespace st {

// 网络相关
namespace net {

enum class Family {
  IPv4,
  IPv6
};

enum class Type {
  TCP,
  UDP
};

enum class Protocol {
  Undefined
};

enum Endian {
  LittileEndian,
  BigEndian
};

Endian get_endian();

} // namespace net


constexpr static int MAX_BUFFER = 4096;

constexpr static int MAX_LINE = 4096;

template<EnumType T>
int to_int(T enum_value);

template<EnumType T>
std::string to_string(T enum_value);


template<>
int to_int(net::Family family)
{
  switch (family) {
  case net::Family::IPv4:
    return AF_INET;
  case net::Family::IPv6:
    return AF_INET6;
  default:    // never happen
    return -1;
  }
}

template<>
int to_int(net::Type type)
{
  switch (type) {
  case net::Type::TCP:
    return SOCK_STREAM;
  case net::Type::UDP:
    return SOCK_DGRAM;
  default:    // never happen
    return -1;
  }
}

template<>
int to_int(net::Protocol protocol)
{
  switch (protocol) {
  case net::Protocol::Undefined:
  default:
    return 0;
  }
}

template<>
std::string to_string(net::Family family)
{
  switch (family) {
  case net::Family::IPv4:
    return "IPv4";
  case net::Family::IPv6:
    return "IPv6";
  default:    // never happen
    return "Unknown Family";
  }
}

template<>
std::string to_string(net::Type type)
{
  switch (type) {
  case net::Type::TCP:
    return "TCP";
  case net::Type::UDP:
    return "UDP";
  default:    // never happen
    return "Unknown Type";
  }
}

template<>
std::string to_string(net::Protocol protocol)
{
  switch (protocol) {
  case net::Protocol::Undefined:
  default:
    return "0";
  }
}

} // namespace st

#endif // STUDY_TOUR_GLOBAL_H