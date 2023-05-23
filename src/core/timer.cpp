#include <chrono>
#include <core/engine.hpp>
#include <core/timer.hpp>
#include <thread>

namespace Engine {
Timer::Timer() {
  start_time = 0;
  pause_time = 0;
  prev_tick_time = 0;
}
void Timer::start() { start_time = glfwGetTime(); }
void Timer::stop() {
  start_time = 0;
  pause_time = 0;
}
double Timer::get_time() {
  if (paused) {
    return glfwGetTime() - pause_time;
  }
  return glfwGetTime() - start_time;
}
void Timer::pause() {
  if (paused) {
    return;
  }
  pause_time = glfwGetTime() - start_time;
}
double Timer::get_tick_time() {
  auto tick_time = prev_tick_time;
  prev_tick_time = glfwGetTime();
  return prev_tick_time - tick_time;
}
double Timer::get_fps() { return 1 / get_tick_time(); }

} // namespace Engine