#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "LedService.h"
#include "BuzzerService.h"
#include "SensorService.h"
#include "KeypadService.h"

class TestSuite {
private:
  LedService* ledService;
  BuzzerService* buzzerService;
  SensorService* sensorService;
  KeypadService* keypadService;

public:
  TestSuite(LedService* led, BuzzerService* buzzer, SensorService* sensor, KeypadService* keypad) {
    ledService = led;
    buzzerService = buzzer;
    sensorService = sensor;
    keypadService = keypad;
  }

  void begin() {
    ledService->begin();
    buzzerService->begin();
    sensorService->begin();
  }

  // Test individual LEDs
  void  testLEDs() {
    Serial.println("Testing Green LED...");
    ledService->turnOnGreen();
    delay(1000);
    ledService->turnOffGreen();

    Serial.println("Testing Yellow LED...");
    ledService->turnOnYellow();
    delay(1000);
    ledService->turnOffYellow();

    Serial.println("Testing Red LED...");
    ledService->turnOnRed();
    delay(1000);
    ledService->turnOffRed();
  }

  // Test the buzzer
  void testBuzzer() {
    Serial.println("Testing Buzzer (Error sound)...");
    buzzerService->playError();
    delay(1000);
    buzzerService->stop();

    Serial.println("Testing Buzzer (Warning sound)...");
    buzzerService->playWarning();
    delay(1000);
    buzzerService->stop();

    Serial.println("Testing Buzzer (Success sound)...");
    buzzerService->playSuccess();
    delay(1000);
    buzzerService->stop();
  }

  // Test the PIR and Ultrasonic sensors
  void testSensors() {
    Serial.println("Testing PIR sensor...");
    if (sensorService->isPirDetected()) {
      Serial.println("PIR Sensor Detected Motion");
    } else {
      Serial.println("No Motion Detected by PIR Sensor");
    }

    Serial.println("Testing Ultrasonic sensor...");
    if (sensorService->isUltrasonicDetected()) {
      Serial.println("Object Detected by Ultrasonic Sensor");
    } else {
      Serial.println("No Object Detected by Ultrasonic Sensor");
    }
  }

  bool firstTime = true;
  // Test keypad input
  void testKeypad() {
    if (firstTime) Serial.println("Testing Keypad (Press any key)...");
    char key = keypadService->getKey();
    if (key) {
      Serial.print("Key Pressed: ");
      Serial.println(key);
    } else {
      if (firstTime)  Serial.println("No key pressed.");
    }
    if (firstTime) firstTime = false;
  }
};

#endif
