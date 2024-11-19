/*
MICROCONTROLLERS LAB X - FINAL PROJECT
Vanessa, Andrew, and RJ
Using flex sensors to measure hand movement and motors to move fingers to 
replicate the hand's movement.
*/

const int flexPIN = A0; // output from flex sensor voltage divider

const float VCC = 5.00; // voltage
const float R_DIV = 10000.0; // resistance of resistor

const float straightResist = 26000.0; // resistance when straight
const float bentResist = 51000.0; // resistance at 90 deg

void setup() {
  Serial.begin(9600);
  pinMode(flexPIN, INPUT);
}

void loop() {
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(flexPIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, straightResist, bentResist, 0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();

  delay(2000);
}
