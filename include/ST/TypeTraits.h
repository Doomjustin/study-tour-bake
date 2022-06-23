#ifndef STUDY_TOUR_TYPE_TRAITS_H
#define STUDY_TOUR_TYPE_TRAITS_H

#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <chrono>


namespace ST {

// 是否能单例化
template<typename T, typename... Args>
using is_singletonable = std::enable_if_t<
      !std::is_copy_assignable_v<T> &&
      !std::is_copy_constructible_v<T> &&
      std::is_constructible_v<T, Args...>, bool>;


// 仅做标识
struct net {};
// 仅做标识
struct host {};

template<typename End>
using is_end = std::enable_if_t<std::is_same_v<End, ST::net> ||
      std::is_same_v<End, ST::host>, bool>;


// 辅助说明类：IPv4
struct IPv4 {};
// 辅助说明类：IPv6
struct IPv6 {};

template<typename FamilyType>
using is_ipv4 = std::enable_if_t<std::is_same_v<FamilyType, IPv4>, bool>;

template<typename FamilyType>
using is_ipv6 = std::enable_if_t<std::is_same_v<FamilyType, IPv6>, bool>;

// 辅助说明类：TCP
struct TCP {};
// 辅助说明类：UDP
struct UDP {};

template<typename Type>
using is_tcp = std::enable_if_t<std::is_same_v<Type, TCP>, bool>;

template<typename Type>
using is_udp = std::enable_if_t<std::is_same_v<Type, UDP>, bool>;

// 任何小于等于32位的整数值
template<typename T>
struct is_less_than_32bit_integer: std::false_type {};

template<>
struct is_less_than_32bit_integer<char>: std::true_type {};

template<>
struct is_less_than_32bit_integer<short>: std::true_type {};

template<>
struct is_less_than_32bit_integer<int>: std::true_type {};

template<>
struct is_less_than_32bit_integer<std::uint8_t>: std::true_type {};

template<>
struct is_less_than_32bit_integer<std::uint16_t>: std::true_type {};

template<>
struct is_less_than_32bit_integer<std::uint32_t>: std::true_type {};

template<typename T>
inline constexpr bool is_less_than_32bit_integer_v = is_less_than_32bit_integer<T>::value;

// 任何小于等于32位的整数值都可以作为fd
template<typename T>
inline constexpr bool is_fd_type_v = is_less_than_32bit_integer_v<T>;


template<typename Clock>
struct is_steady_clock: std::false_type {};

template<>
struct is_steady_clock<std::chrono::steady_clock>: std::true_type {};

template<typename Clock>
static constexpr bool is_steady_clock_v = is_steady_clock<Clock>::value;

template<typename Clock>
struct is_system_clock: std::false_type {};

template<>
struct is_system_clock<std::chrono::system_clock>: std::true_type {};

template<typename Clock>
static constexpr bool is_system_clock_v = is_system_clock<Clock>::value;

} // namespace ST

#endif // STUDY_TOUR_TYPE_TRAITS_H