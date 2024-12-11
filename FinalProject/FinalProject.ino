/*
MICROCONTROLLERS LAB X - FINAL PROJECT
Vanessa, Andrew, and RJ
Using flex sensors to measure hand movement and motors to move fingers to 
replicate the hand's movement.
*/

#include <Servo.h> // include the servo library

Servo myServo1; // servo for index
Servo myServo2; // servo for middle
Servo myServo3; // servo for ring
Servo myServo4; // servo for pinky
const int servoPIN1 = 8;
const int servoPIN2 = 9;
const int servoPIN3 = 10;
const int servoPIN4 = 11;

const int flexPIN1 = A0; // output from flex sensor voltage divider for index
const int flexPIN2 = A1; // output from flex sensor voltage divider for middle
const int flexPIN3 = A2; // output from flex sensor voltage divider for ring
const int flexPIN4 = A3; // output from flex sensor voltage divider for pinky

const float R_DIV = 10000.0; // resistance of resistor

const float straightR1 = 12885.90; // resistance when straight (index)
const float bentR1 = 19912.28; // resistance at 90 deg (index)
const float straightR2 = 12733.33; // resistance when straight (middle)
const float bentR2 = 28603.78; // resistance at 90 deg (middle)
const float straightR3 = 23651.32; // resistance when straight (ring)
const float bentR3 = 48457.14; // resistance at 90 deg (ring)
const float straightR4 = 13092.55; // resistance when straight (pinky)
const float bentR4 = 38483.41; // resistance at 90 deg (pinky)

//==========================================================================

void setup() {
  Serial.begin(9600);

  pinMode(flexPIN1, INPUT);
  pinMode(flexPIN2, INPUT);
  pinMode(flexPIN3, INPUT);
  pinMode(flexPIN4, INPUT);

  myServo1.attach(servoPIN1);
  myServo2.attach(servoPIN2);
  myServo3.attach(servoPIN3);
  myServo4.attach(servoPIN4);

  myServo1.write(110);
  myServo2.write(0);
  myServo3.write(90);
  myServo4.write(90);
}

//==========================================================================

// FINGER ANGLE FUNCTION
// takes bend angle data from flex sensor and moves the corresponding robot finger
void fingerAngle(int finger, int flexPIN, float straightResist, float bentResist) {
  // Read the ADC, and calculate voltage and resistance from it
  // based on Jim Lindblom Flex Sensor SparkFun tutorial
  int flexADC = analogRead(flexPIN);
  float flexV = flexADC * 5.0 / 1023.0;
  float flexR = R_DIV * (5.0 / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(flexR, straightResist, bentResist, 0, 90.0);
  Serial.println("Bend of finger " + String(finger) + ": " + String(angle) + " degrees");
  Serial.println();
  
  // move the servo to move the robot finger
  if (finger == 1) myServo1.write(110-1.2*angle);
  if (finger == 2) myServo2.write(angle*1.15);
  if (finger == 3) myServo3.write(90-angle*1.5);
  if (finger == 4) myServo4.write(90-angle*1.5);
  
}

//==========================================================================

void loop() {
  
  fingerAngle(1, flexPIN1, straightR1, bentR1);
  fingerAngle(2, flexPIN2, straightR2, bentR2);
  fingerAngle(3, flexPIN3, straightR3, bentR3);
  fingerAngle(4, flexPIN4, straightR4, bentR4);

  delay(5);


}
