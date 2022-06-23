#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "ST/Scheduler.h"
#include "ST/Timer.h"

using namespace std::literals;

void print(int i, float f)
{
  std::cout << "test only " << i << ", " << f << std::endl;
  std::this_thread::sleep_for(2s);
}

int main()
{
  ST::Scheduler<void(int, float)> test1{ print };

  test1.run_for(10s, 2, 3);

  auto now_time = std::chrono::high_resolution_clock::now();

  test1.run_until(now_time + 10s, 1, 2);

  ST::Timer<void()> timer{ [] () { std::cout << "timer executing" << std::endl; } };
  timer.run_after(20s);

  return EXIT_SUCCESS;
}