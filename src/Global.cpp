#include "ST/Global.h"

#include <sys/types.h>
#include <sys/socket.h>

#include "ST/Exception.h"


namespace ST::Net {

int to_int(Family family)
{
  switch (family) {
  case Family::IPv4:
    return AF_INET;
  case Family::IPv6:
    return AF_INET6;
  default:    // never happen
    throw UndefinedFamilyException{ "undifiend family type" };
  }
}

int to_int(Type type)
{
  switch (type) {
  case Type::TCP:
    return SOCK_STREAM;
  case Type::UDP:
    return SOCK_DGRAM;
  default:    // never happen
    throw UndefinedTypeException{ "undifiend family type" };
  }
}

int to_int(Protocol protocol)
{
  switch (protocol) {
  case Protocol::Undefined:
  default:
    return 0;
  }
}

std::string to_string(Family family)
{
  switch (family) {
  case Family::IPv4:
    return "IPv4";
  case Family::IPv6:
    return "IPv6";
  default:    // never happen
    throw UndefinedFamilyException{ "undifiend family type" };
  }
}

std::string to_string(Type type)
{
  switch (type) {
  case Type::TCP:
    return "TCP";
  case Type::UDP:
    return "UDP";
  default:    // never happen
    throw UndefinedTypeException{ "undifiend family type" };
  }
}

std::string to_string(Protocol protocol)
{
  switch (protocol) {
  case Protocol::Undefined:
  default:
    return "0";
  }
}

Endian get_endian()
{
  static_assert(sizeof(short) == 2, "only support while sizeof(short) == 2");
  union
  {
    short s;
    char c[sizeof(short)];
  } un;
  un.s = 0x0102;

  if (un.c[0] == 1 && un.c[1] == 2)
    return Endian::BigEndian;

  return Endian::LittileEndian;
}

} // namespace ST::Net