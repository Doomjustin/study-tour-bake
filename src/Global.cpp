#include "ST/Global.h"

#include <sys/types.h>
#include <sys/socket.h>

#include "ST/Exception.h"


namespace ST::Net {

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