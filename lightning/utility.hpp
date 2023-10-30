#pragma once
#include <iostream>
#include <random>

namespace Utility {
int genRandomInt(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

float genRandomFloat(float min, float max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<float> distrib(min, max);
  return distrib(gen);
}

template <typename T>
void message(T message) {
  std::cout << message << std::endl;
}

class FPSCounter {
 private:
  float currentTime = 0.0f;
  int frameCount = 0;

 public:
  void update(float elapsedTime) {
    currentTime += elapsedTime;
    frameCount++;
    if (currentTime >= 1.0f) {
      std::cout << "FPS: " << frameCount << std::endl;
      frameCount = 0;
      currentTime -= 1.0f;
    }
  }
};

}  // namespace Utility

