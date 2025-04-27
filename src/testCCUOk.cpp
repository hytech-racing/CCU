#include <Arduino.h>

bool kick = 1; // NOLINT

void setup() {
    pinMode(26, OUTPUT); // NOLINT watchdog
    pinMode(27, OUTPUT); //NOLINT sw shutdown
    Serial.begin(115200); // NOLINT
}

void loop() {
    digitalWrite(26, kick); // NOLINT
    digitalWrite(27, HIGH); // NOLINT
    kick = !kick;
    delay(10); // NOLINT
    Serial.println(kick);
}
