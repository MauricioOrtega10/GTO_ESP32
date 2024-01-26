#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//IMU library
#include "kxtj3-1057.h"

void setup()
{
  Serial.begin(115200);
  delay(500); // wait until serial is open...

  if (imu.begin() == IMU_SUCCESS) 
  {
    Serial.println("IMU initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize IMU.");
    while(true);
  }
}

void loop()
{
  // Take IMU out of standby
  imu.standby(false);

  // Read accelerometer data in mg as Float
  Serial.print(" Acceleration X float = ");
  Serial.println(imu.axisAccel(X), 4);

  // Read accelerometer data in mg as Float
  Serial.print(" Acceleration Y float = ");
  Serial.println(imu.axisAccel(Y), 4);

  // Read accelerometer data in mg as Float
  Serial.print(" Acceleration Z float = ");
  Serial.println(imu.axisAccel(Z), 4);

  // Put IMU back into standby
  imu.standby(true);

  delay(1000);
}