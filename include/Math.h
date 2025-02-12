#ifndef __PID_H__
#define __PID_H__

class PID {
public:
    PID(float kp = 1, float ki = 0, float kd = 0) : Kp(kp), Ki(ki), Kd(kd), prev_error(0), integral(0) {}
    
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

float min(float v1, float v2){
    if (v1 < v2){
        return v1;
    }
    else{
        return v2;
    }
};

#endif