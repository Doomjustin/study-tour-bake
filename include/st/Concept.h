/**
 * @file Concept.h
 * @author doom (1075101233doom@gmail.com)
 * @brief 概念相关定义
 * @version 0.1
 * @date 2022-06-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STUDY_TOUR_CONCEPT_H
#define STUDY_TOUR_CONCEPT_H

#include <type_traits>
#include <concepts>

#include "TypeTraits.h"


namespace st {
// 从cppreference照抄的
namespace detail {
namespace { // 避免 ODR 违规
template<class T>
auto test_sizable(int) -> decltype(sizeof(T), std::true_type{});
template<class>
auto test_sizable(...) -> std::false_type;

template<class T>
auto test_nonconvertible_to_int(int)
    -> decltype(static_cast<std::false_type (*)(int)>(nullptr)(std::declval<T>()));
template<class>
auto test_nonconvertible_to_int(...) -> std::true_type;

template<class T>
constexpr bool is_scoped_enum_impl = std::conjunction_v<
    decltype(test_sizable<T>(0)),
    decltype(test_nonconvertible_to_int<T>(0))
>;
}
} // namespace detail


// enum / enum class
template<typename T>
concept enum_type = std::is_enum_v<T>;

// 从cppreference照抄的
template<class>
struct is_scoped_enum : std::false_type {};
// enum class only
template<enum_type E>
struct is_scoped_enum<E> : std::bool_constant<detail::is_scoped_enum_impl<E>> {};

template<typename T>
concept scoped_enum_type = is_scoped_enum<T>::value;

// 从cppreference照抄的
template<scoped_enum_type Enum>
constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept
{
  return static_cast<std::underlying_type_t<Enum>>(e);
}

template<typename T, typename... Args>
concept singletonizable = !std::is_copy_assignable_v<T> &&
                          !std::is_copy_constructible_v<T> &&
                           std::is_constructible_v<T, Args...>;

template<typename T>
concept net_end = std::is_same_v<T, Net> ||
                  std::is_same_v<T, Host>;


template<typename T>
concept ipv4 = std::is_same_v<T, IPv4>;

template<typename T>
concept ipv6 = std::is_same_v<T, IPv6>;

template<typename T>
concept tcp = std::is_same_v<T, TCP>;

template<typename T>
concept udp = std::is_same_v<T, UDP>;

template<typename T>
concept less_than_32bit_integer = is_less_than_32bit_integer_v<T>;


template<typename T>
concept steady_clock = is_steady_clock_v<T>;

template<typename T>
concept system_clock = is_system_clock_v<T>;

template<typename T>
concept clock = steady_clock<T> && system_clock<T>;

} // namespace st

#endif // STUDY_TOUR_CONCEPT_H