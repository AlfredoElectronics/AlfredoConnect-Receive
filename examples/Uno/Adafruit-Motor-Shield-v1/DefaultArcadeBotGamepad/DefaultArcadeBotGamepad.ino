/**
 * Example code for a robot using an Arduino and an Adafruit Motor Shield v1 controlled
 * with a gamepad from AlfredoConnect. The AFMotor library, for the Adafruit Motor Shield
 * v1 can be found at https://github.com/adafruit/Adafruit-Motor-Shield-library.
 */

#include <AlfredoConnect.h>
#include <SoftwareSerial.h>
#include <AFMotor.h>

/* These pins are labeled from the board's perspective, so the BLUETOOTH_RX
 * (receive) pin on the board connects to TX (transmit) on the Bluetooth
 * module, and vice versa. */
static const int BLUETOOTH_RX = A3;
static const int BLUETOOTH_TX = A2;

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);

void setup() {
    bluetooth.begin(115200);
    AlfredoConnect.begin(bluetooth);
}

void loop() {
    AlfredoConnect.update();

    if (AlfredoConnect.getGamepadCount() >= 1) {
        arcadeDrive(-AlfredoConnect.getAxis(0, 1), AlfredoConnect.getAxis(0, 0));
    }
}

void arcadeDrive(float throttle, float rotation) {
    float leftPower = 0;
    float rightPower = 0;
    float maxInput = (throttle > 0 ? 1 : -1) * max(fabs(throttle), fabs(rotation));
    if (throttle > 0) {
        if (rotation > 0) {
            leftPower = maxInput;
            rightPower = throttle - rotation;
        } else {
            leftPower = throttle + rotation;
            rightPower = maxInput;
        }
    } else {
        if (rotation > 0) {
            leftPower = throttle + rotation;
            rightPower = maxInput;
        } else {
            leftPower = maxInput;
            rightPower = throttle - rotation;
        }
    }
    setMotor(leftMotor, leftPower);
    setMotor(rightMotor, rightPower);
}

void setMotor(AF_DCMotor motor, float power) {
    motor.run(power > 0 ? FORWARD : BACKWARD);
    motor.setSpeed(fabs(power * 255));
}