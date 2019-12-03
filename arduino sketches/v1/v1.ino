#include <ESP32_Servo.h>

// pins for the piezo sensors and the servo PWM
int[] piezoPins = { 20, 21, 22, 23 }
int[] servoPins = { 13, 14, 15, 16, 17, 18, 19 };

// the servos
Servo[] servos;

// mapping of servo index to the positions it takes for each
// side of the box
int[][] positions = { 
  { 0, 0, 0, 0 }, // check key for which servo
  { 0, 0, 0, 0 }, // L, T, R, B (index => side mapping)
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
};

int[] piezoVals = { 0, 0, 0, 0 }

void setup() {
  for (int i = 0; i < servos.length; i++) {
    servos[i].attach(servoPins[i], 5, 2500);
  }
  
  Serial.begin(115200);
}

void loop() {
  int max = 0;
  int activatedSide = 0;
  for (int i = 0; i < piezoVals.length; i++) {
    int val = analogRead(piezoPins[i]);
    if (val > max) {
      max = val;
      activatedSide = i;
    }

    piezoVals[i] = val;
  }

  for (int i = 0; i < servos.length; i++) {
    servos[i].writeMicroseconds(positions[i][activatedSide]);
  }

  delay(500);
}
