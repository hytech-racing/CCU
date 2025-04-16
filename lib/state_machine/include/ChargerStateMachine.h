#ifndef CHARGERSTATEMACHINE_H
#define CHARGERSTATEMACHINE_H

enum class ChargerState_e { //NOLINT
    INITIAL = 0, //not charging
    CHARGING_NO_BALANCING = 1, //charging but no balancing
    CHARGING_WITH_BALANCING = 2, //charging with balancing
};

class ChargerStateMachine
{
public:

    void tick_state_machine(ChargerState_e& _current_state, bool balancing_enabled, int dial_position, bool start_button_pressed, unsigned long current_millis);

    ChargerState_e get_state() {return _current_state;}

private:

    void set_state(ChargerState_e new_state, unsigned long current_millis);
    
    //handle exit/entry logic make sure that each state is properly reset when the state machine leaves it
    void handle_exit_logic(ChargerState_e prev_state, unsigned long current_millis);

    void handle_entry_logic(ChargerState_e new_state, unsigned long current_millis);
    
    ChargerState_e _current_state;
};

using ChargerStateMachineInstance = etl::singleton<ChargerStateMachine>;

#endif 