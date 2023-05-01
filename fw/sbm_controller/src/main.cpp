#include <Arduino.h>


void setup() {
    Serial.begin(115200);
    pinMode(0, OUTPUT);
    // Perform other setup operations
}

void loop() {
    digitalWrite(0, HIGH);

}