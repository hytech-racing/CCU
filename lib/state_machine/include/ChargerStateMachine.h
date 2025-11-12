#ifndef CHARGERSTATEMACHINE_H
#define CHARGERSTATEMACHINE_H

#include <etl/delegate.h>
#include "CCUData.h"
#include "ACUInterface.h"
#include "ChargerInterface.h"

enum class ChargingState_e { //NOLINT
    NOT_CHARGING = 0, //not charging
    CHARGING = 1, //charging
    DONE_CHARGING = 2, //done charging
};

class ChargerStateMachine
{
    public:

        ChargerStateMachine(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

        ChargingState_e tick_state_machine(unsigned long current_millis); //need to put these parameters in a struct?
        ChargingState_e get_state() {return _current_state;}

    private:

        void set_state(ChargingState_e new_state, unsigned long current_millis);
        
        //handle exit/entry logic make sure that each state is properly reset when the state machine leaves it
        void handle_exit_logic(ChargingState_e prev_state, unsigned long current_millis);

        void handle_entry_logic(ChargingState_e new_state, unsigned long current_millis);
        
        ChargingState_e _current_state;

        CCUData &_ccu_data;


};

using ChargerStateMachineInstance = etl::singleton<ChargerStateMachine>;


#endif 
