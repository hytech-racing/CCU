#ifndef CCUPARAMS_H
#define CCUPARAMS_H

struct CCUParams
{
  bool balancing_enabled = false; //tells ACU whether balancing is allowed or not
  float target_voltage_per_cell = 3.1; //per cell
  float max_allowable_cell_temperature = 70; //need data for this
};
#endif