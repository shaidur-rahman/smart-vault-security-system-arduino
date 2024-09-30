#ifndef START_H
#define START_H

#include "LedService.h"
#include "BuzzerService.h"
#include "SensorService.h"
#include "KeypadService.h"
#include "TestSuite.h"
#include "SecurityController.h"

LedService ledService(A0, A1, A2);       // Green, Yellow, Red LEDs Pins
BuzzerService buzzerService(A5);         // Buzzer Pins
SensorService sensorService(10, 11, 12);    // PIR, Ultrasonic Trigger, Ultrasonic Echo
byte rowPins[4] = {9, 8, 7, 6};          // Keypad Row Pins
byte colPins[4] = {5, 4, 3, 2};          // Keypad Column Pins
KeypadService keypadService(rowPins, colPins);

SecurityController securityController(&ledService, &buzzerService, &sensorService);
TestSuite testSuite(&ledService, &buzzerService, &sensorService, &keypadService);

class Start {
private:
  bool isTest;
public:
  Start(bool test = false) {
    isTest = test;
  }

  void test() {
    // Run individual tests
    testSuite.testLEDs();
    delay(1500);
    testSuite.testBuzzer();
    delay(1500);
    testSuite.testSensors();
    delay(1500);
    testSuite.testKeypad();
    delay(1500);
  }

  void setup() {
    // Initialize all services
    if (isTest) {
      testSuite.begin();
    } else {
      securityController.begin();
    }
  }

  void loop() {
    // Check for intruders
    securityController.monitorSensors();

    // Assume this is a keypress validation check (replace with keypad logic)
    char enteredKey = 'X';  // This would be replaced with actual keypad logic

    if (enteredKey == '1') {  // Example of a valid passkey
      securityController.validatePasskey(true);
    } else if (enteredKey == '0') {  // Example of an invalid passkey
      securityController.validatePasskey(false);
    }

    // Lock the system again
    if (enteredKey == '#') {
      securityController.resetToSecurityMode();
    }
  }
};

#endif
