#pragma once

namespace Engine {
class Timer {
public:
  Timer();
  double get_time();
  double get_tick_time();
  double get_fps();
  void start();
  void stop();
  void pause();

private:
  double pause_time;
  double start_time;
  double prev_tick_time;
  bool paused;
};
} // namespace Engine