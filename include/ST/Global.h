#ifndef STUDY_TOUR_GLOBAL_H
#define STUDY_TOUR_GLOBAL_H

#include <netinet/in.h>
#include <sys/types.h>

#include <string>
#include <cstddef>
#include <cstdint>

#include "Concept.h"


// 网络相关
namespace ST::Net {

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

} // namespace ST::Net

namespace ST {

constexpr static int MAX_BUFFER = 4096;

constexpr static int MAX_LINE = 4096;


template<EnumType T>
int to_int(T enum_value);

template<EnumType T>
std::string to_string(T enum_value);


template<>
int to_int(Net::Family family)
{
  switch (family) {
  case Net::Family::IPv4:
    return AF_INET;
  case Net::Family::IPv6:
    return AF_INET6;
  default:    // never happen
    return -1;
  }
}

template<>
int to_int(Net::Type type)
{
  switch (type) {
  case Net::Type::TCP:
    return SOCK_STREAM;
  case Net::Type::UDP:
    return SOCK_DGRAM;
  default:    // never happen
    return -1;
  }
}

template<>
int to_int(Net::Protocol protocol)
{
  switch (protocol) {
  case Net::Protocol::Undefined:
  default:
    return 0;
  }
}

template<>
std::string to_string(Net::Family family)
{
  switch (family) {
  case Net::Family::IPv4:
    return "IPv4";
  case Net::Family::IPv6:
    return "IPv6";
  default:    // never happen
    return "Unknown Family";
  }
}

template<>
std::string to_string(Net::Type type)
{
  switch (type) {
  case Net::Type::TCP:
    return "TCP";
  case Net::Type::UDP:
    return "UDP";
  default:    // never happen
    return "Unknown Type";
  }
}

template<>
std::string to_string(Net::Protocol protocol)
{
  switch (protocol) {
  case Net::Protocol::Undefined:
  default:
    return "0";
  }
}

} // namespace ST


#endif // STUDY_TOUR_GLOBAL_H