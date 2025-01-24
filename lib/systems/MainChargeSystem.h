/* Imports */
#include <Arduino.h> 
//#include "EthernetInterface.h" // this is not created yet but will take info from acu and give out usable values 
#include "DerateFactorSystem.h" // not made yet need to decide the scaling based on temp of cells
//#include "Charger_data.h"


/* TO-DO 
Taking in the message from ACU protobuf recieving 
_sys becomes System
*/
/* Constants */

double target_voltage = 12.4; //currently arbitrary
bool current_flow = false;
int max_AC_current = 5;

/* Class Instance Creation */


/* Function Init */

int set_charge_current();

/* Logic */

void charge_cycle() {
  double max_cell_V = 1; // ethernet_message.get_max_cell_V(); returns the max cell Voltage to allow for decision whether or not to continue charging or not (not yet created) the code for individual cell temps is in the AMS code that already exists

  if (max_cell_V >= target_voltage) { //checks whether or not any of the cells are charged yet
      current_flow = false; //this should be a function that actually turns on/off current flow 
  }
  else { 
      set_charge_current(); //sets the charge current to the PID adjusted value
      current_flow = true; //same as line 32
  }
}


int set_charge_current() { //returns an int value for current
  int current_setpoint = max_AC_current * 1; //derateCalculation(); derate calculation actually needs to be thought of
  return current_setpoint;
}
