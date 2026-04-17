#pragma once
#include <chrono>
class Env {
public:
  int windowHeight, windowWidth;
  double desiredFPS;
  std::chrono::duration<double, std::milli> getFrameTime() const {
    return std::chrono::duration<double, std::milli>(1000.0 / desiredFPS);
  }
};
