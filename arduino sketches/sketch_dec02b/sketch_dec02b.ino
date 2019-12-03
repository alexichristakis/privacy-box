#include <ESP32_Servo.h>


Servo servo;
int pos = 0;

void setup() {
  servo.attach(13, 5, 2500);
  Serial.begin(115200);

}

void loop() {
//  servo.writeMicroseconds(5);
//  servo.writeMicroseconds(2500);

  while(true) {
    servo.writeMicroseconds(pos);
    

    pos += 100;

    if (pos >= 2600) {
      pos = 0;
      delay(300);
    } else {
      delay(100);
    }
  }



//  servo.write(-30);
//  delay(1000);
//
//
//  servo.write(0);
//  delay(1000);
//
//  servo.write(90);
//
//  delay(1000);
//
//  servo.write(180);
//
//  delay(1000);
//
//  servo.write(270);
//
//  delay(1000);
//
//  servo.write(360);
}
