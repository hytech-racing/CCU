#ifndef CHARGERSTATEMACHINE_H
#define CHARGERSTATEMACHINE_H

#include <etl/delegate.h>
#include "CCUData.h"
#include "ACUInterface.h"
#include "ChargerInterface.h"

enum class ChargerState_e { //NOLINT
    INITIAL = 0, //not charging
    CHARGING_NO_BALANCING = 1, //charging but no balancing
    CHARGING_WITH_BALANCING = 2, //charging with balancing
};

class ChargerStateMachine
{
    public:

        ChargerStateMachine(CCUData ccu_data) :  _ccu_data(ccu_data) {};

        ChargerState_e tick_state_machine(unsigned long current_millis); //need to put these parameters in a struct?
        ChargerState_e get_state() {return _current_state;}

    private:

        void set_state(ChargerState_e new_state, unsigned long current_millis);
        
        //handle exit/entry logic make sure that each state is properly reset when the state machine leaves it
        void handle_exit_logic(ChargerState_e prev_state, unsigned long current_millis);

        void handle_entry_logic(ChargerState_e new_state, unsigned long current_millis);
        
        ChargerState_e _current_state;

        CCUData _ccu_data;

        
};

using ChargerStateMachineInstance = etl::singleton<ChargerStateMachine>;


#endif 