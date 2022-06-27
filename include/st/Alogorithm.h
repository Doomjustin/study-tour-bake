#ifndef STUDY_TOUR_ALGORITHM_H
#define STUDY_TOUR_ALGORITHM_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>


namespace st {
namespace detail {

template<typename T, typename Comparator>
void bubble(T arr[], size_t N)
{
  Comparator comparator{};
  for (size_t i = 0; i < N; ++i)
    if (!comparator(arr[i], arr[i + 1]))
      std::swap(arr[i], arr[i + 1]);
}

} // namespace detail


template<typename T, typename Comparator = std::less<T>>
void bubble_sort(T arr[], size_t N)
{
  for (auto rest = N; rest > 1; --rest)
    bubble_sort<T, Comparator>(arr, rest);
}

} // namespace st

#endif // STUDY_TOUR_ALGORITHM_H