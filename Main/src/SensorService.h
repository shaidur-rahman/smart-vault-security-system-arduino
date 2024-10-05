#ifndef SENSOR_SERVICE_H
#define SENSOR_SERVICE_H

class SensorService {
private:
  int pirPin, trigPin, echoPin;

public:
  SensorService(int pir, int trig, int echo) {
    pirPin = pir;
    trigPin = trig;
    echoPin = echo;
  }

  void begin() {
    pinMode(pirPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  bool isPirDetected() {
    return digitalRead(pirPin);
  }

  bool isUltrasonicDetected() {
    // Send pulse to ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = (duration * 0.034) / 2;

     if (distance < 11) { // Return true if the object is within 10cm
        Serial.print("Ultrasonic range: ");
        Serial.println(distance);
        return true;
     }

    return false;
  }
};

#endif
