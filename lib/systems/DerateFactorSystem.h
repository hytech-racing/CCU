# include <PID_RT.h>

#define PIDrunInterval

float BMS_temps;

/*
float derateCalculation(){ //need to flesh out what the derate factor actually shoud be
        //make work using PID of cell temps and board temps - prioritize board temps
        //if PID rising a lot have max stop where derate goes to 0 / stop charging
        setInterval(PIDrunInterval);
        compute(BMS_temps);
        float factor = getOutput();
        double final_derate_factor = 1.0;
        return final_derate_factor; 
    };
    */