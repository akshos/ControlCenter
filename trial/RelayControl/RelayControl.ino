#include <Wire.h>

#define RELAY_1 14 //D5
#define RELAY_2 12 //D6

byte input;

void setup() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Relay 1 on");
  digitalWrite(RELAY_1, 1);

}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();
    if (input == (byte)'a') {
      digitalWrite(RELAY_1, 1);
    }
    else if (input == (byte)'b') {
      digitalWrite(RELAY_1, 0);
    }
  }

}
