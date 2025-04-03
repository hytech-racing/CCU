#include "Arduino.h"

bool kick = 1;

void setup() {
    pinMode(26, OUTPUT); //watchdog
    pinMode(27, OUTPUT); //sw shutdown
    Serial.begin(115200);
}

void loop() {
    digitalWrite(26, kick);
    digitalWrite(27, HIGH);
    kick = !kick;
    delay(10);
    Serial.println(kick);
}