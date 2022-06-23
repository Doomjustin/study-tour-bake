#ifndef STUDY_TOUR_SCHEDULER_H
#define STUDY_TOUR_SCHEDULER_H

#include <chrono>
#include <utility>

#include "TypeTraits.h"


namespace ST {

/**
 * @brief 提供循环的抽象
 *
 * @tparam typename
 */
template<typename>
class Scheduler;

/**
 * @brief
 *
 * @example Scheduler<void()> test{ [] () { cout << "1" << endl; } };
 *          test.run_for(20s);
 * @tparam R
 * @tparam Args
 */
template<typename R, typename... Args>
class Scheduler<R(Args...)> {
  // TODO: 能否换成using?
  typedef R (*InvokeFunctionType)(Args...);

public:
  template<typename F>
  explicit Scheduler(F&& task)
    : task_{ std::forward<F>(task) }
  {}

  /**
   * @brief 执行任务work_time，超时后停止
   *
   * @tparam Rep
   * @tparam Period
   * @param work_time
   * @param args
   */
  template<typename Rep, typename Period>
  void run_for(const std::chrono::duration<Rep, Period>& work_time, Args&&... args)
  {
    auto start = std::chrono::steady_clock::now();
    auto now = start;
    std::chrono::duration<Rep, Period> time_pass;
    while (start + work_time >= now) {
      task_(std::forward<Args>(args)...);
      now = std::chrono::steady_clock::now();
    }
  }

  /**
   * @brief 到stop_time之前一直循环执行任务，到时后停止
   *
   * @tparam Clock
   * @tparam Duration
   * @param stop_time
   * @param args
   */
  template<typename Clock, typename Duration, std::enable_if_t<is_steady_clock_v<Clock>, bool> = true>
  void run_until(const std::chrono::time_point<Clock, Duration>& stop_time, Args&&... args)
  {
    auto now = std::chrono::steady_clock::now();
    while (now <= stop_time) {
      task_(std::forward<Args>(args)...);
      now = std::chrono::steady_clock::now();
    }
  }

  /**
   * @brief 到stop_time之前一直循环执行任务，到时后停止
   *
   * @tparam Clock
   * @tparam Duration
   * @param stop_time
   * @param args
   */
  template<typename Clock, typename Duration, std::enable_if_t<is_system_clock_v<Clock>, bool> = true>
  void run_until(const std::chrono::time_point<Clock, Duration>& stop_time, Args&&... args)
  {
    auto now = std::chrono::system_clock::now();
    while (now <= stop_time) {
      task_(std::forward<Args>(args)...);
      now = std::chrono::system_clock::now();
    }
  }

private:
  InvokeFunctionType task_;
};

} // namespace ST

#endif // STUDY_TOUR_SCHEDULER_H