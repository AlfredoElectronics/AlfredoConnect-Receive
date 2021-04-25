#ifndef ALFREDOCONNECT_H
#define ALFREDOCONNECT_H

#include "Arduino.h"
#include "Keys.h"
#include <inttypes.h>

class AlfredoConnectParser {
    public:
        void begin();
        void begin(Stream& inputStream);
        void begin(Stream& inputStream, bool readOnly);
        uint8_t update();
        bool keyHeld(Key key);
        uint8_t getGamepadCount();
        uint8_t getAxisCount(uint8_t gamepad);
        uint8_t getButtonCount(uint8_t gamepad);
        float getAxis(uint8_t gamepad, uint8_t axis);
        uint8_t getRawAxis(uint8_t gamepad, uint8_t axis);
        bool buttonHeld(uint8_t gamepad, uint8_t button);
    private:
        static constexpr uint8_t NUM_KEYS = 14; // 14 bytes = 112 bits for 106 keys, with 6 left over
        static constexpr uint8_t MAX_GAMEPADS = 8;
        static constexpr uint8_t MAX_AXES = 8;
        static constexpr uint8_t MAX_BUTTONS = 8; // 8 bytes = 64 bits for max of 64 buttons
        Stream* inputStream;
        bool suppressErrors = false;
        typedef struct {
            uint8_t axes[MAX_AXES];
            uint8_t axesSize;
            uint8_t buttons[MAX_BUTTONS];
            uint8_t buttonsSize;
        } Gamepad;
        uint8_t keyboardState[NUM_KEYS]; // TODO: bits instead of bytes
        Gamepad gamepads[MAX_GAMEPADS];
        uint8_t gamepadsSize = 0;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_ALFREDOCONNECT)
extern AlfredoConnectParser AlfredoConnect;
#endif

#endif