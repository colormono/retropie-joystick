// Arduino Retropie Joystick v0.3
// -------------------------------
// Based on https://github.com/MHeironimus/ArduinoJoystickLibrary
// Keyboard Modifiers: https://www.arduino.cc/en/Reference/KeyboardModifiers
//
// NOTE: This sketch file is for use with Arduino Leonardo and Arduino Micro only.
//
// by COLORMONO
// 2017-05-31
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   8, 0,                  // Button Count, Hat Switch Count
                   true, true, false,     // X and Y, but no Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP); // UP
  pinMode(3, INPUT_PULLUP); // DOWN
  pinMode(4, INPUT_PULLUP); // LEFT
  pinMode(5, INPUT_PULLUP); // RIGHT

  pinMode(6, INPUT_PULLUP); // A
  pinMode(7, INPUT_PULLUP); // B
  pinMode(8, INPUT_PULLUP); // X
  pinMode(9, INPUT_PULLUP); // Y
  pinMode(10, INPUT_PULLUP); // L SHOULDER
  pinMode(A0, INPUT_PULLUP); // R SHOULDER

  pinMode(A1, INPUT_PULLUP); // SELECT
  pinMode(A2, INPUT_PULLUP); // START

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons (4 + 6 + 2)
int lastButtonState[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void loop() {

  // Read pin values
  for (int index = 0; index < 12; index++)
  {
      int currentButtonState;
    if (index == 9) {
      currentButtonState = !digitalRead(A0);
    } else if (index == 10) {
      currentButtonState = !digitalRead(A1);
    } else if (index == 11) {
      currentButtonState = !digitalRead(A2);
    } else {
      currentButtonState = !digitalRead(index + 2);
    }

    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 2: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 3: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // A
          Joystick.setButton(0, currentButtonState);
          break;
        case 5: // B
          Joystick.setButton(1, currentButtonState);
          break;
        case 6: // X
          Joystick.setButton(2, currentButtonState);
          break;
        case 7: // Y
          Joystick.setButton(3, currentButtonState);
          break;
        case 8: // LS
          Joystick.setButton(4, currentButtonState);
          break;
        case 9: // RS
          Joystick.setButton(5, currentButtonState);
          break;
        case 10: // SELECT
          Joystick.setButton(6, currentButtonState);
          break;
        case 11: // START
          Joystick.setButton(7, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(10);
}

