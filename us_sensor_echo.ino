/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int trigPin1 = 12;    // Trigger
int echoPin1 = 13;    // Echo
int trigPin2 = 10;    // Trigger
int echoPin2 = 11;    // Echo
long duration1, duration2, cm1, cm2, inches1, inches2;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
 
  // Convert the time into a distance
  cm1 = (duration1/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches1 = (duration1/2) / 74;   // Divide by 74 or multiply by 0.0135
  cm2 = (duration2/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches2 = (duration2/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches1);
  Serial.print("in1, ");
  Serial.print(cm1);
  Serial.print("cm1");
  Serial.println();

  Serial.print(inches2);
  Serial.print("in2, ");
  Serial.print(cm2);
  Serial.print("cm2");
  Serial.println();
  
  delay(250);
}
