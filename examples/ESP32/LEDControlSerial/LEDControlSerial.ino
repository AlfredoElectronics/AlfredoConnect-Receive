/**
 * Lights the ESP32's built-in LED when the "W" key is pressed in AlfredoConnect
 * connected to the ESP32's hardware serial.
 * 
 * TODO: Link basic setup here (board files, how to upload, how to pair Bluetooth, how to find and open port)
 */

#include <AlfredoConnect.h>

const int LED_BUILTIN = 2;

void setup() {
    Serial.begin(9600);
    AlfredoConnect.begin(Serial);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    AlfredoConnect.update();
    if (AlfredoConnect.keyHeld(Key::W)) digitalWrite(2, HIGH);
    else digitalWrite(2, LOW);
}