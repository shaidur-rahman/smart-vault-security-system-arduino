#ifndef KEYPAD_SERVICE_H
#define KEYPAD_SERVICE_H

#include <Keypad.h>

class KeypadService {
private:
  const byte ROWS = 4;  // Four rows
  const byte COLS = 4;  // Four columns
  char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
  byte rowPins[4];
  byte colPins[4];
  Keypad keypad;

public:
  KeypadService(byte rowP[], byte colP[]) : keypad(makeKeymap(keys), rowP, colP, ROWS, COLS) {
    memcpy(rowPins, rowP, sizeof(rowPins));
    memcpy(colPins, colP, sizeof(colPins));
  }

  void begin() {
    // Nothing required here for the Keypad library initialization
  }

  char getKey() {
    return keypad.getKey();
  }
};

#endif
