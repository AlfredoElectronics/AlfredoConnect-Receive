/**
 * Example code for a robot using an ESP32 and NoU2 controlled with the keyboard from AlfredoConnect.
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed library instruction can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/
 */

#include <AlfredoConnect.h>
#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

BluetoothSerial bluetooth;

NoU_Motor leftMotor(1);
NoU_Motor rightMotor(2);

NoU_Drivetrain drivetrain(&leftMotor, &rightMotor);

void setup() {
    bluetooth.begin("ESP32 Bluetooth");
    AlfredoConnect.begin(bluetooth);
    bluetooth.println("ArcadeBotKeyboard started");

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
    int throttle = 0;
    int rotation = 0;

    if (AlfredoConnect.keyHeld(Key::W)) {
        throttle = 1;
    } else if (AlfredoConnect.keyHeld(Key::S)) {
        throttle = -1;
    }
    if (AlfredoConnect.keyHeld(Key::A)) {
        rotation = -1;
    } else if (AlfredoConnect.keyHeld(Key::D)) {
        rotation = 1;
    }

    drivetrain.arcadeDrive(throttle, rotation);

    AlfredoConnect.update();
    RSL::update();
}