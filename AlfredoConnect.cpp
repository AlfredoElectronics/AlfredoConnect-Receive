// TODO: for both keyboard keys and gamepad buttons, really want
// keyPressed, buttonPressed - true only on the frame of the press
// keyHeld, buttonHeld - true for the entire duration of the press
// this means we need to save previous state, doubling memory use
// TODO: could we implement gamepads as a dynamically allocated linked list?
// this would help alleviate memory use from storing both current and
// previous button states.

#include "AlfredoConnect.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_ALFREDOCONNECT)
AlfredoConnectParser AlfredoConnect;
#endif

void AlfredoConnectParser::begin() {
    begin(Serial);
}

void AlfredoConnectParser::begin(Stream& inputStream) {
    this->inputStream = &inputStream;
}

/**
 * @param suppressErrors suppresses writing error output to the inputStream
 */
void AlfredoConnectParser::begin(Stream& inputStream, bool suppressErrors) {
    this->suppressErrors = suppressErrors;
    begin(inputStream);
}

// TODO: error codes and perror
uint8_t AlfredoConnectParser::update() {
    if (inputStream == NULL) return 1; // error code
    uint8_t keysPressed[NUM_KEYS];
    uint8_t keysPressedSize = 0;
    Gamepad gamepadsTemp[MAX_GAMEPADS];
    uint8_t gamepadsSizeTemp = 0;
    bool keyboardStateCleared = false; // We want to clear the keyboard state at most once per update
    while (inputStream->available()) {
        if (inputStream->peek() == '#') {
            inputStream->read(); // read the hash
            if (inputStream->readBytes(&keysPressedSize, 1) != 1) return 1; // timeout error code
            if (keysPressedSize > NUM_KEYS) return 1; // error code
            if (inputStream->readBytes(keysPressed, keysPressedSize) != keysPressedSize) return 1; // timeout error code
            if (inputStream->readBytes(&gamepadsSizeTemp, 1) != 1) return 1; // timeout error code
            if (gamepadsSizeTemp > MAX_GAMEPADS) return 1; // error code
            for (int i = 0; i < gamepadsSizeTemp; i++) {
                if (inputStream->readBytes(&(gamepadsTemp[i].axesSize), 1) != 1) return 1; // timeout error code
                if (gamepadsTemp[i].axesSize > MAX_AXES) return 1; // error code
                if (inputStream->readBytes(gamepadsTemp[i].axes, gamepadsTemp[i].axesSize) != gamepadsTemp[i].axesSize) return 1; // timeout error code
                if (inputStream->readBytes(&(gamepadsTemp[i].buttonsSize), 1) != 1) return 1; // timeout error code
                if (gamepadsTemp[i].buttonsSize > MAX_BUTTONS * 8) return 1; // error code
                uint8_t buttonsBytes = (gamepadsTemp[i].buttonsSize / 8) + (gamepadsTemp[i].buttonsSize % 8 == 0 ? 0 : 1);
                if (inputStream->readBytes(gamepadsTemp[i].buttons, buttonsBytes) != buttonsBytes) return 1; // timeout error code
            }
            uint8_t endChar;
            if (inputStream->readBytes(&endChar, 1) != 1) return 1;
            if (endChar != '$') return 1;
            if (!keyboardStateCleared) {
                keyboardStateCleared = true;
                memset(keyboardState, 0, NUM_KEYS);
            }
            for (int i = 0; i < keysPressedSize; i++) keyboardState[keysPressed[i] / 8] |= 1 << (keysPressed[i] % 8);
            memcpy(gamepads, gamepadsTemp, sizeof(Gamepad) * gamepadsSizeTemp);
            gamepadsSize = gamepadsSizeTemp;
        } else inputStream->read();
    }
    return 0;
}

bool AlfredoConnectParser::keyHeld(Key key) {
    return keyboardState[(uint8_t)key / 8] & (1 << ((uint8_t)key % 8));
}

uint8_t AlfredoConnectParser::getGamepadCount() {
    return gamepadsSize;
}

uint8_t AlfredoConnectParser::getAxisCount(uint8_t gamepad) {
    if (gamepad >= gamepadsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getAxisCount] Gamepad ");
            inputStream->print(gamepad);
            inputStream->println(" is not connected.");
        }
        return 0;
    }
    return gamepads[gamepad].axesSize;
}

uint8_t AlfredoConnectParser::getButtonCount(uint8_t gamepad) {
    if (gamepad >= gamepadsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getButtonCount] Gamepad ");
            inputStream->print(gamepad);
            inputStream->println(" is not connected.");
        }
        return 0;
    }
    return gamepads[gamepad].buttonsSize;
}

float AlfredoConnectParser::getAxis(uint8_t gamepad, uint8_t axis) {
    if (gamepad >= gamepadsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getAxis] Gamepad ");
            inputStream->print(gamepad);
            inputStream->println(" is not connected.");
        }
        return 0;
    }
    if (axis >= gamepads[gamepad].axesSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getAxis] Gamepad ");
            inputStream->print(gamepad);
            inputStream->print(" has no axis ");
            inputStream->print(axis);
            inputStream->println(".");
        }
        return 0;
    }
    return ((float)(gamepads[gamepad].axes[axis]) / 127.5) - 1;
}

uint8_t AlfredoConnectParser::getRawAxis(uint8_t gamepad, uint8_t axis) {
    if (gamepad >= gamepadsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getRawAxis] Gamepad ");
            inputStream->print(gamepad);
            inputStream->println(" is not connected.");
        }
        return 0;
    }
    if (axis >= gamepads[gamepad].axesSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::getRawAxis] Gamepad ");
            inputStream->print(gamepad);
            inputStream->print(" has no axis ");
            inputStream->print(axis);
            inputStream->println(".");
        }
        return 0;
    }
    return gamepads[gamepad].axes[axis];
}

bool AlfredoConnectParser::buttonHeld(uint8_t gamepad, uint8_t button) {
    if (gamepad >= gamepadsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::buttonHeld] Gamepad ");
            inputStream->print(gamepad);
            inputStream->println(" is not connected.");
        }
        return false;
    }
    if (button >= gamepads[gamepad].buttonsSize) {
        if (!suppressErrors) {
            inputStream->print("[ERROR - AlfredoConnectParser::buttonHeld] Gamepad ");
            inputStream->print(gamepad);
            inputStream->print(" has no button ");
            inputStream->print(button);
            inputStream->println(".");
        }
        return false;
    }
    return gamepads[gamepad].buttons[button / 8] & (1 << (button % 8));
}