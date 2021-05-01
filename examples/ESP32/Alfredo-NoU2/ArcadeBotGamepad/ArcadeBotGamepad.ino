/**
 * Example code for a robot using an ESP32 and NoU2 controlled with a gamepad from AlfredoConnect.
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
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
    bluetooth.println("ArcadeBotGamepad started");

    RSL::initialize();
    RSL::setState(RSL_DISABLED);
}

void loop() {
    AlfredoConnect.update();
    if (AlfredoConnect.getGamepadCount() >= 1) {
        drivetrain.arcadeDrive(-AlfredoConnect.getAxis(0, 1), AlfredoConnect.getAxis(0, 0));
        RSL::setState(RSL_ENABLED);
    } else RSL::setState(RSL_DISABLED);
    RSL::update();
}