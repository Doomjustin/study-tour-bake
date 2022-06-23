#ifndef STUDY_TOUR_TEMPLATE_H
#define STUDY_TOUR_TEMPLATE_H

#include <chrono>
#include <utility>
#include <future>
#include <thread>

#include "TypeTraits.h"


namespace ST {

/**
 * @brief 定时任务，到时间后开始执行
 *
 */
template<typename>
class Timer;


template<typename R, typename... Args>
class Timer<R(Args...)> {
  typedef R (*InvokeFunctionType)(Args...);

public:
  template<typename F>
  explicit Timer(F&& task)
    : task_{ std::forward<F>(task) }
  {}

  template<typename Rep, typename Period>
  void run_after(const std::chrono::duration<Rep, Period>& wait_time, Args&&... args)
  {
    std::this_thread::sleep_for(wait_time);
    task_(std::forward<Args>(args)...);
  }

  template<typename Clock, typename Duration, std::enable_if_t<is_steady_clock_v<Clock>, bool> = true>
  void run_at(const std::chrono::time_point<Clock, Duration>& start_time, Args&&... args)
  {
    std::this_thread::sleep_until(start_time);
    task_(std::forward<Args>(args)...);
  }

  template<typename Clock, typename Duration, std::enable_if_t<is_system_clock_v<Clock>, bool> = true>
  void run_at(const std::chrono::time_point<Clock, Duration>& start_time, Args&&... args)
  {
    std::this_thread::sleep_until(start_time);
    task_(std::forward<Args>(args)...);
  }

private:
  InvokeFunctionType task_;
};

} // namespace ST

#endif // STUDY_TOUR_TEMPLATE_H