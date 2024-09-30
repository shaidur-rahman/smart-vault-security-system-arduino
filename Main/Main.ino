#include "src/Start.h"

Start start(true);       // Initializing system


void setup() {
  Serial.begin(9600);
  // Initialize all services
  start.setup();
}

void loop() {
  start.test();
}
