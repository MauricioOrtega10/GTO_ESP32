#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Sonar library
#include <NewPing.h>

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  Serial.print("Distance: ");
  Serial.print(sonar.ping_cm()); //read distance in cm
  Serial.println("cm");
  delay(250);
}
