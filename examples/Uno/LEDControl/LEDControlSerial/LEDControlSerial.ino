/**
 * Lights an Arduino or clone board's built-in LED when the "W" key is pressed in AlfredoConnect
 * while connected to the board's hardware serial (typically over USB).
 * 
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include <AlfredoConnect.h>

void setup() {
    Serial.begin(9600);
    AlfredoConnect.begin(Serial);
    Serial.println("LEDControlSerial started");

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
