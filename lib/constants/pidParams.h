#include <Arduino.h>

struct PIDParams {
  uint32_t PIDrunInterval = 12;
  float Kp = 1;
  float Ki = 1;
  float Kd = 1;
};