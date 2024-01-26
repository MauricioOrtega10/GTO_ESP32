#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//SeervoMotor library
#include <ESP32Servo.h> 

int pos = 0;

void setup()
{

}


void loop() 
{
  //Cycle that will position the servo from 0 to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) 
  {
    servo.write(pos);
    delay(15);
  }
  
  //Cycle that will position the servo from 180 to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) 
  {
    servo.write(pos);
    delay(15);
  }
  
}
