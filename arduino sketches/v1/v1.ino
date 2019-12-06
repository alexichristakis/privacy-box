#include <ESP32_Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

const int NUM_SIDES = 4;
const int NUM_SERVOS = 7;

// the servos
Servo servos[NUM_SERVOS];
MPU6050 mpu6050(Wire);

// pins for the servo PWM
int servoPins[]  = { 13, 14, 25, 26, 27, 12, 33 };

// mapping of servo index to the positions it takes for each
// side of the box
const int sidePositions[][NUM_SIDES]  = {
  { 1305, 1800, 2505, 5 }, // check key for which servo
  { 2505, 5, 1000, 1700 }, // T, L, B, R (index => side mapping, where top has power in)
  { 2005, 2600, 5, 1100 },
  { 1800, 2500, 5, 1400 },
  { 5, 1600, 2200, 2600 },
  { 5, 1100, 1600, 2600 },
  { 1950, 2600, 5, 1400 },
};

// intial servo positions
int servoPositions[] = { 5, 5, 5, 5, 5, 5, 5 };

int activatedSide = 0;

// calibration for accelerometer
float calibration[] = { 0, 0 };

void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i], 5, 2500);
  }

  Wire.begin(2, 15);
  mpu6050.begin();

  calibration[0] = mpu6050.getAccX();
  calibration[1] = mpu6050.getAccY();
  
  Serial.begin(115200);
}

// sweep a servo through it's range
void sweepServo(int servo) {
   for (int pos = 5; pos < 2600; pos += 100) {
    servos[servo].writeMicroseconds(pos);
    Serial.println(pos);
    delay(500);
  }
}

// for calibrating positions of each servo
void rangeServo(int servo) {
   for (int side = 0; side < 4; side++) {
      servos[servo].writeMicroseconds(positions[servo][side]);
      Serial.print(side);
      Serial.print(", ");
      Serial.print(positions[servo][side]);
      Serial.print(", ");
      delay(500);
  }
  Serial.println();
}

void updateServos() {
  for (int servo = 0; servo < NUM_SERVOS; servo++) {
    servos[servo].writeMicroseconds(servoPositions[servo]);
  }
}

void randomStep(int servo) {
  int currentPosition = positions[servo];

  if (random() > 0.5) {
    // take a step
    int stepSize = (random() - 0.5) * 100;
    int newPosition = currentPosition + stepSize;
    
    positions[servo] = newPosition;
  }
}


void randomWalk() {
  for (int servo = 0; servo < NUM_SERVOS; servo++) {
    randomStep(servo);
  }
}

void writePositions(int side) {
  for (int servo = 0; servo < NUM_SERVOS; servo++) {
    servoPositions[servo] = positions[servo][side];
  }
}



void loop() {
  mpu6050.update();

  float accX = mpu6050.getAccX();
  float accY = mpu6050.getAccY();


  float diffX = accX - calibration[0];
  float diffY = accY - calibration[1];
  if (diffX * diffX > 0.1 || diffY * diffY > 0.1) {
    if (diffX > 0) activatedSide = 3;
    if (diffX < 0) activatedSide = 1;
    
    if (diffY > 0) activatedSide = 2;
    if (diffY < 0) activatedSide = 0;

    writePositions(activatedSide);
  } else {
    randomWalk();
  }
  
  updateServos();
  delay(200);
}
