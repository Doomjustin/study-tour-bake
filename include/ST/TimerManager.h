#ifndef STUDY_TOUR_TIMER_MANAGER_H
#define STUDY_TOUR_TIMER_MANAGER_H

#include <vector>

#include "Timer.h"


namespace ST {

template<typename>
class TimerManager;


template<typename R, typename... Args>
class TimerManager<R(Args...)> {
public:

  

private:
  std::vector<Timer<R(Args...)>> timers_;
};


} // namespace ST

#endif // STUDY_TOUR_TIMER_MANAGER_H