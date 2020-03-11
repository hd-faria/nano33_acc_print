/*
  acc_print.ino
  based on: Simple Accelerometer example created by Riccardo Rizzo

  The circuit:
  - Arduino Nano 33 BLE Sense
*/

#include <Arduino_LSM9DS1.h>
#define TIME_DELAY_MILISECONDS 500
#define TIME_DELAY_COMM_SETUP 25
#define COMM_HARDWARE_ENABLE 12

#ifndef LED_BUILTIN
  #defini LED_BUILTIN D13
#endif //LED_BUILTIN

void setup() {
  // Configure D13 as output
  pinMode(COMM_HARDWARE_ENABLE, OUTPUT);
  digitalWrite(COMM_HARDWARE_ENABLE, LOW);
  // Visual feedback only
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  while (!Serial); // find out if it will compromise the test
  Serial.println("Arduino Nano 33 BLE Board Test\n");

  Serial.print("Initializing accelerometer... \r");
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("Accelerometer init returned 0 \r\n");

  Serial.print("Interval between readings: ");
  Serial.print(TIME_DELAY_MILISECONDS);
  Serial.println("ms\r\n");

  Serial.println("AccX[mG], AccY[mG], AccZ[mG]");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Turn on communication hardware
    digitalWrite(COMM_HARDWARE_ENABLE,HIGH);
    digitalWrite(LED_BUILTIN,HIGH); // Visual feedback only
    // Wait 25ms for hardware communication to be stable before send data
    delay(TIME_DELAY_COMM_SETUP); 

    Serial.print((x*1000));
    Serial.print(", ");
    Serial.print((y*1000));
    Serial.print(", ");
    Serial.println((z*1000));

    // Wait 25ms before shutdown of communication hardware
    delay(TIME_DELAY_COMM_SETUP);
    // Turn off communication hardware
    digitalWrite(COMM_HARDWARE_ENABLE,LOW); 
    digitalWrite(LED_BUILTIN,LOW); // Visual feedback only

    delay(TIME_DELAY_MILISECONDS - (2*TIME_DELAY_COMM_SETUP));
  }
}
