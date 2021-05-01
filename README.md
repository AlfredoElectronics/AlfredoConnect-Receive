# AlfredoConnect-Receive
*v1.0.0*

This library for Arduino and ESP32 parses input from [AlfredoConnect](https://github.com/AlfredoElectronics/AlfredoConnect-Desktop), a desktop application for sending keyboard and gamepad input over serial.

## Installation

[Click here to download this library as a ZIP archive](https://github.com/AlfredoElectronics/Alfredo-NoU2/archive/refs/heads/master.zip).

To add this library to the [Arduino IDE](https://www.arduino.cc/en/software), click `Sketch` in the top menu bar, go to `Include Library`, and click `Add .ZIP Library...`. Browse to the directory where you downloaded the ZIP archive, and select the archive. Now, if you click `File` in the top menu bar, go to `Examples`, and scroll down through the list, you should see `AlfredoConnect-Receive` under `Examples from Custom Libraries`. There are several examples available:

 * For ESP32:
   * [`LEDControl/LEDControlSerial`](examples/ESP32/LEDControl/LEDControlSerial/LEDControlSerial.ino): Turn on the built-in LED when `W` is pressed in AlfredoConnect when connected over hardware serial (typically USB).
   * [`LEDControl/LEDControlBluetooth`](examples/ESP32/LEDControl/LEDControlBluetooth/LEDControlBluetooth.ino): Turn on the built-in LED when `W` is pressed in AlfredoConnect when connected over Bluetooth.
   * Using the [Alfredo NoU2](https://github.com/AlfredoElectronics/Alfredo-NoU2):
     * [`Alfredo-NoU2/ArcadeBotKeyboard`](examples/ESP32/Alfredo-NoU2/ArcadeBotKeyboard/ArcadeBotKeyboard.ino): Drives a robot from AlfredoConnect using `WASD` on the keyboard.
     * [`Alfredo-NoU2/ArcadeBotGamepad`](examples/ESP32/Alfredo-NoU2/ArcadeBotGamepad/ArcadeBotGamepad.ino): Drives a robot from AlfredoConnect using a gamepad.
* For Uno boards:
   * [`LEDControl/LEDControlSerial`](examples/Uno/LEDControl/LEDControlSerial/LEDControlSerial.ino): Turn on the built-in LED when `W` is pressed in AlfredoConnect when connected over hardware serial (typically USB).
   * [`LEDControl/LEDControlBluetooth`](examples/Uno/LEDControl/LEDControlBluetooth/LEDControlBluetooth.ino): Turn on the built-in LED when `W` is pressed in AlfredoConnect when connected over Bluetooth.
   * Using the [Adafruit Motor Shield v1](https://github.com/adafruit/Adafruit_Motor-Shield-v1):
     * [`Adafruit-Motor-Shield-v1/ArcadeBotKeyboard`](examples/Uno/Adafruit-Motor-Shield-v1/ArcadeBotKeyboard/ArcadeBotKeyboard.ino): Drives a robot from AlfredoConnect using `WASD` on the keyboard.
     * [`Adafruit-Motor-Shield-v1/ArcadeBotGamepad`](examples/Uno/Adafruit-Motor-Shield-v1/ArcadeBotGamepad/ArcadeBotGamepad.ino): Drives a robot from AlfredoConnect using a gamepad.