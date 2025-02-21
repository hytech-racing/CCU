#ifndef __CCUPARAMS_H__
#define __CCUPARAMS_H__

//This is a namespace that contains all of the future knob settable constants for CCu
namespace CCUParams{ 
  const double target_voltage = 3.1; //per cell
  const float max_AC_current = 15; //need to add the DC current setpoint probably 30 amps
  const float ideal_cell_temp = 40;
};
#endif