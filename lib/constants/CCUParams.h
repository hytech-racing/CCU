#include <Arduino.h>

struct CCUParams{
  double target_voltage = 3.1; //per cell
  int max_AC_current = 15; //need to add the DC current setpoint probably 30 amps
  float ideal_cell_temp = 40;
};