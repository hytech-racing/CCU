#ifndef __CHARGERSTATEMACHINE_H__
#define __CHARGERSTATEMACHINE_H__

enum class ChargerState_e {
    INITIAL, //not charging
    CHARGING_NO_BALANCING, //charging but no balancing
    CHARGING_WITH_BALANCING //charging with balancing
};

class ChargerStateMachine
{
    public:
    ChargerState_e evaluate_charger_state_machine(ChargerState_e& _current_state, bool balancing_enabled, int dial_position, bool start_button_pressed);


    private:
    void set_state(ChargerState_e new_state);
    
    //handle exit/entry logic make sure that each state is properly reset when the state machine leaves it
    void handle_exit_logic(ChargerState_e prev_state);

    void handle_entry_logic(ChargerState_e new_state);
    
    ChargerState_e _current_state;

};


#endif