#ifndef __CCUPARAMS_H__
#define __CCUPARAMS_H__

struct CCUParams
{
  bool balancing_enabled = false; //tells ACU whether balancing is allowed or not
  const float target_voltage = 3.1; //per cell
  const float max_voltage = 0; //need data for this
  const float max_cell_temp = 0; //need data for this
  const float max_current = 0; //need data for this
  bool start_button_pressed = false; //when pressed, tells CCU to start charging
};
#endif

//don't know if we still need this - const float ideal_cell_temp = 40;