/**
 * Lights the ESP32's built-in LED when the "W" key is pressed in AlfredoConnect
 * connected to the ESP32's Bluetooth.
 * 
 * TODO: Link basic setup here (board files, how to upload, how to pair Bluetooth, how to find and open port)
 */

#include <AlfredoConnect.h>
#include <BluetoothSerial.h>

const int LED_BUILTIN = 2;

BluetoothSerial bluetooth;

void setup() {
    bluetooth.begin("ESP32 Bluetooth");
    AlfredoConnect.begin(bluetooth);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    AlfredoConnect.update();
    
    if (AlfredoConnect.keyHeld(Key::W)) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}