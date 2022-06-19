#ifndef STUDY_TOUR_TYPE_TRAITS_H
#define STUDY_TOUR_TYPE_TRAITS_H

#include <type_traits>


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

} // namespace ST

#endif // STUDY_TOUR_TYPE_TRAITS_H