#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);
Encoder myEnc(2,3);

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(50);
  myMotor->run(FORWARD);
  myMotor2->setSpeed(50);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  // turn on motor
  myMotor2->run(RELEASE);
}

long oldPosition  = -999;

void loop() {
  uint8_t i;
  
  Serial.print("tick");

  myMotor->run(FORWARD);
  for (i=100; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=100; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  myMotor2->run(FORWARD);
  for (i=100; i<255; i++) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=100; i--) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  
  Serial.print("tock");

  myMotor->run(BACKWARD);
  for (i=100; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=100; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }
    myMotor2->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=100; i--) {
    myMotor->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }
  
  delay(1000);
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }

  Serial.print("tech");
  myMotor->run(RELEASE);
  delay(1000);
}
