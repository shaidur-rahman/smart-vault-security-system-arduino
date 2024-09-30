#ifndef LED_SERVICE_H
#define LED_SERVICE_H

class LedService {
private:
  int greenPin, yellowPin, redPin;

public:
  LedService(int green, int yellow, int red) {
    greenPin = green;
    yellowPin = yellow;
    redPin = red;
  }

  void begin() {
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
  }

  void turnOnGreen() {
    digitalWrite(greenPin, HIGH);
  }

  void turnOffGreen() {
    digitalWrite(greenPin, LOW);
  }

  void turnOnYellow() {
    digitalWrite(yellowPin, HIGH);
  }

  void turnOffYellow() {
    digitalWrite(yellowPin, LOW);
  }

  void turnOnRed() {
    digitalWrite(redPin, HIGH);
  }

  void turnOffRed() {
    digitalWrite(redPin, LOW);
  }
};

#endif
