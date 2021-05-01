/**
 * Lights an Arduino or clone board's built-in LED when the "W" key is pressed in
 * AlfredoConnect while connected to the ESP32's Bluetooth.
 * 
 * TODO: Link basic setup here (board files, how to upload, how to pair Bluetooth, how to find and open port)
 */

#include <AlfredoConnect.h>
#include <SoftwareSerial.h>

/* These pins are labeled from the board's perspective, so the BLUETOOTH_RX
 * (receive) pin on the board connects to TX (transmit) on the Bluetooth
 * module, and vice versa. */
static const int BLUETOOTH_RX = A3;
static const int BLUETOOTH_TX = A2;

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

void setup() {
    bluetooth.begin(115200);
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
