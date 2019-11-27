
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 
Encoder knobLeft(2, 3);
Encoder knobRight(18, 19);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor and encoder test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  // turn on motor
  myMotor2->run(RELEASE);
}


long positionLeft  = -999;
long positionRight = -999;

void loop() {
  uint8_t i;

    long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
  Serial.print("tick");

  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  for (i=0; i<100; i++) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);  
    delay(5);
    newLeft = knobLeft.read();
    newRight = knobRight.read();
    delay(5);
    Serial.print("Left = ");
    Serial.println(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);    
  }
  for (i=100; i!=0; i--) {
    myMotor->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }
//  myMotor2->run(FORWARD);
//  for (i=0; i<255; i++) {
//    myMotor2->setSpeed(i);  
//    delay(10);
//  }
//  for (i=255; i!=0; i--) {
//    myMotor2->setSpeed(i);  
//    delay(10);
//  }
//  
//  Serial.print("tock");

  myMotor->run(BACKWARD);
  myMotor2->run(BACKWARD);
  for (i=0; i<100; i++) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);  
    delay(5);
    newLeft = knobLeft.read();
    newRight = knobRight.read();
    delay(5);
    Serial.print("Left = ");
    Serial.println(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);    
  }
  for (i=100; i!=0; i--) {
    myMotor->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }


  Serial.print("tech");
  myMotor->run(RELEASE);
  delay(1000);
}
