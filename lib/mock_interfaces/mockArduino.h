#ifndef MOCKARDUINO_H
#define MOCKARDUINO_H

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

inline void pinMode(int pin, int mode) {} //NOLINT (used as a mock for test_systems_env)
inline void digitalWrite(int pin, int value) {} //NOLINT (used as a mock for test_systems_env)
inline int digitalRead(int pin) {return HIGH;} //NOLINT (used as a mock for test_systems_env)



#endif