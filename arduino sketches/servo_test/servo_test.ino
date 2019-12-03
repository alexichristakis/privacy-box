#include <ESP32_Servo.h>


Servo servo;
int pos = 0;

void setup() {
  servo.attach(13, 5, 2500);
  Serial.begin(115200);

}

void loop() {
  servo.writeMicroseconds(pos);
  
  pos += 100;

  if (pos >= 2600) {
    pos = 0;
    delay(300);
  } else {
    delay(100);
  }


}
