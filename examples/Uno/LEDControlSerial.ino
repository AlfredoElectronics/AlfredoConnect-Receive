/**
 * Lights an Arduino or clone board's built-in LED when the "W" key is pressed in AlfredoConnect
 * while connected to the board's hardware serial (e.g. USB).
 * 
 * TODO: Link basic setup here (board files, how to upload, how to pair Bluetooth, how to find and open port)
 */

#include <AlfredoConnect.h>

void setup() {
    Serial.begin(9600);
    AlfredoConnect.begin(Serial);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    AlfredoConnect.update();
    if (AlfredoConnect.keyHeld(Key::W)) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);
}