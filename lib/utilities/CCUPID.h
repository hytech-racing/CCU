#ifndef __CCUPID_H__
#define __CCUPID_H__


class PID {
//PID calculation class
public:
    PID(float kp, float ki, float kd) : Kp(kp), Ki(ki), Kd(kd), prev_error(0), integral(0) {}
    
    float compute(double setpoint, double measured_value) {
        float error = setpoint - measured_value;
        integral += error;
        float derivative = error - prev_error;
        prev_error = error;
        return (Kp * error) + (Ki * integral) + (Kd * derivative);
    }

    void set_tunings(double kp, double ki, double kd) {
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