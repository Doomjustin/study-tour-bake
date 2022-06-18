/**
 * @file Singleton.h
 * @author doom (1075101233doom@gmail.com)
 * @brief 单例工厂
 * @version 0.1
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STUDY_TOUR_SINGLETON_H
#define STUDY_TOUR_SINGLETON_H

#include <utility>

#include "TypeTraits.h"


namespace ST {

/**
 * @brief 栈创建单例对象(单例工厂)
 *
 * @tparam T
 * @tparam Args
 * @return T*
 */
template<typename T, typename... Args,
      is_singletonable<T, Args...> = true>
T* static_singleton(Args&&... args)
{
  static T singleton { std::forward<Args>(args)... };

  return &singleton;
}

} // namespace ST

#endif // STUDY_TOUR_SINGLETON_H