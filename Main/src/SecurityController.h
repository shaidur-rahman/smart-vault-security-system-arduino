#ifndef SECURITY_CONTROLLER_H
#define SECURITY_CONTROLLER_H

#include "LedService.h"
#include "BuzzerService.h"
#include "SensorService.h"

class SecurityController {
private:
  LedService* ledService;
  BuzzerService* buzzerService;
  SensorService* sensorService;
  bool securityModeActive;
  int invalidAttempts;

public:
  SecurityController(LedService* led, BuzzerService* buzzer, SensorService* sensor) {
    ledService = led;
    buzzerService = buzzer;
    sensorService = sensor;
    securityModeActive = true;
    invalidAttempts = 0;
  }

  void begin() {
    ledService->begin();
    buzzerService->begin();
    sensorService->begin();
  }

  void monitorSensors() {
    if (securityModeActive) {
      if (sensorService->isPirDetected() && sensorService->isUltrasonicDetected()) {
        triggerAlarm();
      }
    }
  }

  void triggerAlarm() {
    buzzerService->playError();
    ledService->turnOnRed();
    delay(30000);  // Error mode for 30 seconds
    ledService->turnOffRed();
    buzzerService->stop();
  }

  void validatePasskey(bool isValid) {
    if (isValid) {
      securityModeActive = false;
      ledService->turnOnGreen();
      buzzerService->playSuccess();
      delay(500);
      buzzerService->stop();
    } else {
      invalidAttempts++;
      if (invalidAttempts >= 3) {
        triggerAlarm();
        invalidAttempts = 0;
      } else {
        ledService->turnOnYellow();
        buzzerService->playWarning();
        delay(1000);  // Warning mode
        ledService->turnOffYellow();
        buzzerService->stop();
      }
    }
  }

  void resetToSecurityMode() {
    securityModeActive = true;
    ledService->turnOffGreen();
  }
};

#endif
