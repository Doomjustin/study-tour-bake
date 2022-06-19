#ifndef STUDY_TOUR_CAST_H
#define STUDY_TOUR_CAST_H

#include <endian.h>
#include <netinet/in.h>

#include <type_traits>

#include "Global.h"
#include "TypeTraits.h"


namespace ST::detail {

template<typename End, typename Integer,
      std::enable_if_t<std::is_integral_v<Integer>, bool> = true,
      ST::is_end<End> = true>
struct ByteOrderCast {
  /**
   * @brief 8bit的整数无需转换
   *
   * @param integer
   * @return Integer
   */
  Integer operator()(Integer integer)
  {
    return integer;
  }
};

template<>
struct ByteOrderCast<net, uint16_t> {
  uint16_t operator()(uint16_t integer)
  {
    // 网络字节序为Big Endian
    return htobe16(integer);
  }
};

template<>
struct ByteOrderCast<net, uint32_t> {
  uint32_t operator()(uint32_t integer)
  {
    // 网络字节序为Big Endian
    return htobe32(integer);
  }
};

template<>
struct ByteOrderCast<net, uint64_t> {
  uint64_t operator()(uint64_t integer)
  {
    // 网络字节序为Big Endian
    return htobe64(integer);
  }
};

template<>
struct ByteOrderCast<host, uint16_t> {
  uint16_t operator()(uint16_t integer)
  {
    // 网络字节序为Big Endian
    return be16toh(integer);
  }
};

template<>
struct ByteOrderCast<host, uint32_t> {
  uint32_t operator()(uint32_t integer)
  {
    // 网络字节序为Big Endian
    return be32toh(integer);
  }
};

template<>
struct ByteOrderCast<host, uint64_t> {
  uint64_t operator()(uint64_t integer)
  {
    // 网络字节序为Big Endian
    return be64toh(integer);
  }
};

} // namespace ST::detail

namespace ST {

/**
 * @brief 原生C风格强制指针类型转换
 *
 * @tparam To
 * @tparam From
 * @param from
 * @return To*
 */
template<typename To, typename From>
To* c_ptr_cast(From* from)
{
  return (To*) from;
}

/**
 * @brief 字节序转换(网络序 <-> 本地序)
 * @example auto net_order_data = byte_order_cast<net>(host_order_data);  // 数据转化为Net序
 *
 * @tparam End
 * @tparam Integer
 * @param integer
 * @return Integer
 */
template<typename End, typename Integer,
      std::enable_if_t<std::is_integral_v<Integer>, bool> = true,
      is_end<End> = true>
Integer byte_order_cast(Integer integer)
{
  return detail::ByteOrderCast<End, Integer>{}(integer);
}

} // namespace ST

#endif // STUDY_TOUR_CAST_H