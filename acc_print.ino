/*
  acc_print.ino
  based on: Simple Accelerometer example created by Riccardo Rizzo

  The circuit:
  - Arduino Nano 33 BLE Sense
*/

#include <Arduino_LSM9DS1.h>
#define TIME_DELAY_MILLISECONDS 500

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    delay(TIME_DELAY_MILLISECONDS);
  }
}
