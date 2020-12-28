// arduino sketch to do what the library should eventually handle

// SRAM use:
// 8 gamepads * 18 bytes = 144 bytes
// 128 keys = 128 bytes
// for keys, keysSize, gamepads, gamepadsSize: 274 bytes = 13.3% of 2kb (arduino uno sram)

#include <Alfredo_NoU2.h>
#include <BluetoothSerial.h>

#define NUM_KEYS 106
#define MAX_GAMEPADS 8
#define MAX_AXES 8
#define MAX_BUTTONS 8 // multiply by 8 for max buttons

NoU_Motor leftMotor(1);
NoU_Motor rightMotor(2);

NoU_Drivetrain drivetrain(&leftMotor, &rightMotor);

BluetoothSerial bluetooth;

void setup() {
    bluetooth.begin("GoldBot");
    RSL::initialize();
    RSL::setState(RSL_ENABLED);
    leftMotor.setInverted(true);
}

typedef struct {
    byte axes[MAX_AXES];
    byte axesSize;
    byte buttons[MAX_BUTTONS];
    byte buttonsSize;
} Gamepad;

// We store the full state of the keyboard, instead of just the pressed keys, because
// it lets us efficiently create an aggregate state of all the keys that were pressed
// since the last time packets were processed.
byte keyboardState[NUM_KEYS]; // TODO: bits instead of bytes
Gamepad gamepads[MAX_GAMEPADS];
byte gamepadsSize = 0;

// TODO: should return different error code for all failures for problem diagnosis

// PROBLEM: if a key is pressed and then released while the buffer is overflowed, the
// press is lost. doesn't seem like there's any way to recover it.

void loop() {
    bool keyboardStateCleared = false;

    byte keysPressed[NUM_KEYS];
    byte keysPressedSize = 0;
    Gamepad gamepadsTemp[MAX_GAMEPADS];
    byte gamepadsSizeTemp = 0;

    while (bluetooth.available()) {
        if (bluetooth.peek() == '#') {
            bluetooth.read(); // read the hash
            if (bluetooth.readBytes(&keysPressedSize, 1) != 1) return; // timeout error code
            if (keysPressedSize > NUM_KEYS) return; // error code
            if (bluetooth.readBytes(keysPressed, keysPressedSize) != keysPressedSize) return; // timeout error code
            if (bluetooth.readBytes(&gamepadsSizeTemp, 1) != 1) return; // timeout error code
            if (gamepadsSizeTemp > MAX_GAMEPADS) return; // error code
            for (int i = 0; i < gamepadsSizeTemp; i++) {
                if (bluetooth.readBytes(&(gamepadsTemp[i].axesSize), 1) != 1) return; // timeout error code
                if (gamepadsTemp[i].axesSize > MAX_AXES) return; // error code
                if (bluetooth.readBytes(gamepadsTemp[i].axes, gamepadsTemp[i].axesSize) != gamepadsTemp[i].axesSize) return; // timeout error code
                if (bluetooth.readBytes(&(gamepadsTemp[i].buttonsSize), 1) != 1) return; // timeout error code
                if (gamepadsTemp[i].buttonsSize > MAX_BUTTONS * 8) return; // error code
                byte buttonsBytes = (gamepadsTemp[i].buttonsSize / 8) + (gamepadsTemp[i].buttonsSize % 8 == 0 ? 0 : 1);
                if (bluetooth.readBytes(gamepadsTemp[i].buttons, buttonsBytes) != buttonsBytes) return; // timeout error code
            }
            byte endChar;
            if (bluetooth.readBytes(&endChar, 1) != 1) return;
            if (endChar != '$') return;
            // packet validated, now we can change state
            if (!keyboardStateCleared) {
                keyboardStateCleared = true;
                memset(keyboardState, 0, NUM_KEYS); // TODO: size needs to change when keyboardState changes to bits
            }
            for (int i = 0; i < keysPressedSize; i++) keyboardState[keysPressed[i]] = 1;
            memcpy(gamepads, gamepadsTemp, sizeof(Gamepad) * gamepadsSizeTemp);
            gamepadsSize = gamepadsSizeTemp;
        } else bluetooth.read();
    }
    if (gamepadsSize == 0) {
        if (keyboardState[41]) {
            drivetrain.arcadeDrive(1, 0);
            bluetooth.println("forward");
        } else if (keyboardState[37]) {
            drivetrain.arcadeDrive(-1, 0);
            bluetooth.println("backward");
        } else drivetrain.arcadeDrive(0, 0);
    } else {
        drivetrain.arcadeDrive(-getAxis(0, 1), getAxis(0, 0));
    }
    RSL::update();
}

float getAxis(byte gamepadIndex, byte axisIndex) {
    if (gamepads[gamepadIndex].axes[axisIndex] == 127) return 0;
    else return ((float)(gamepads[gamepadIndex].axes[axisIndex]) / 127.5) - 1;
}