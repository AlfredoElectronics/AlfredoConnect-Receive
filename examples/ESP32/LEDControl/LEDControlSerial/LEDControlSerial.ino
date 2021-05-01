/**
 * Lights the ESP32's built-in LED when the "W" key is pressed in AlfredoConnect while
 * connected to the ESP32's hardware serial (typically over USB).
 * 
 * Detailed library instruction can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/
 */

#include <AlfredoConnect.h>

static const int LED_BUILTIN = 2;

void setup() {
    Serial.begin(115200);
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
