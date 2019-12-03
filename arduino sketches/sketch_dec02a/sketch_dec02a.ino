#include <ESP32_Servo.h>


Servo servo;

int pos = 0;
int connectedState = 0;


void setup() {
  servo.attach(13);
  Serial.begin(115200);

  pinMode(23, INPUT);
  pinMode(4, INPUT);
 
//
}

void loop() {
  int val = digitalRead(23);
  int shouldMove = digitalRead(4);

  if (shouldMove) {
    servo.write(0);
  }

  if (val && !connectedState) {
    connectedState = 1;
    
    pos += 1;

    if (pos == 4) {
      pos = 0;
    }

    Serial.println(pos);
  }

  if (pos == 3) {
    servo.write(90);
  }

  if (!val) {
    connectedState = 0;
  }
  

  delay(500);
}
