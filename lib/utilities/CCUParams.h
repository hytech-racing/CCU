#ifndef __CCUPARAMS_H__
#define __CCUPARAMS_H__

struct CCUParams
{
  bool balancing_enabled = false; //tells ACU whether balancing is allowed or not
  float target_voltage = 3.1; //per cell
  float max_allowable_cell_voltage; //need data for this
  float max_allowable_cell_temp; //need data for this
  float max_allowable_current; //need data for this
};
#endif

//don't know if we still need this - const float ideal_cell_temp = 40;