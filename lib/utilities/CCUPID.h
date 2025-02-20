#ifndef __CCUPID_H__
#define __CCUPID_H__


#include "PIDParams.h"
class PID {
public:
    PID(float kp = PidParams::Kp, float ki = PidParams::Ki, float kd = PidParams::Kd) : Kp(kp), Ki(ki), Kd(kd), prev_error(0), integral(0) {}
    
    float compute(double setpoint, double measured_value) {
        float error = setpoint - measured_value;
        integral += error;
        float derivative = error - prev_error;
        prev_error = error;
        return (Kp * error) + (Ki * integral) + (Kd * derivative);
    }

    void setTunings(double kp, double ki, double kd) {
        Kp = kp;
        Ki = ki;
        Kd = kd;
    }

private:
    float Kp, Ki, Kd;
    float prev_error;
    float integral;
};


#endif