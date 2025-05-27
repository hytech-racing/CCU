#ifndef MOCKARDUINO_H
#define MOCKARDUINO_H

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

inline void pinMode(int pin, int mode) {}
inline void digitalWrite(int pin, int value) {}
inline int digitalRead(int pin) {return HIGH;}



#endif