/**
 * Lights an Arduino or clone board's built-in LED when the "W" key is pressed in
 * AlfredoConnect while connected to the ESP32's Bluetooth.
 * 
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
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
    bluetooth.begin(9600);
    AlfredoConnect.begin(bluetooth);
    bluetooth.println("LEDControlBluetooth started");

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    if (AlfredoConnect.keyHeld(Key::W)) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }

    AlfredoConnect.update();
}
