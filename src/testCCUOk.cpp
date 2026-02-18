#include <Arduino.h>

bool kick = 1; // NOLINT

void setup() {
    pinMode(35, OUTPUT); // NOLINT watchdog
    pinMode(34, OUTPUT); //NOLINT sw shutdown
    Serial.begin(115200); // NOLINT
}

void loop() {
    digitalWrite(35, kick); // NOLINT
    digitalWrite(34, HIGH); // NOLINT
    kick = !kick;
    delay(10); // NOLINT
    Serial.println(kick);
}
