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
        triggerAlarm(5);
      }
    }
  }

  void triggerAlarm(int dlySec = 30) {
    buzzerService->playError();
    ledService->turnOnRed();
    delay(dlySec * 1000);  // Error mode for default 30/dly seconds
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
      if (invalidAttempts >= 5) {
        triggerAlarm(3);
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
