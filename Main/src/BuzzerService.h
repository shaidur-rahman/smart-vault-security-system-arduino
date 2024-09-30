#ifndef BUZZER_SERVICE_H
#define BUZZER_SERVICE_H

class BuzzerService {
private:
  int buzzerPin;

public:
  BuzzerService(int buzzer) {
    buzzerPin = buzzer;
    high();
  }

  void begin() {
    pinMode(buzzerPin, OUTPUT);
  }

  void playError() {
    tone(buzzerPin, 1000);  // Error sound
  }

  void playWarning() {
    tone(buzzerPin, 500);  // Warning sound
  }

  void playSuccess() {
    tone(buzzerPin, 2000);  // Success sound
  }

  void stop() {
    noTone(buzzerPin);
    high();
  }
  void high() {
    digitalWrite(buzzerPin, HIGH);
  }
};

#endif
