#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Led bar library
#include "LedBar.h"

void setup()
{

}

void loop()
{
  //test the 6 segments of the led bar
  for(int i = 1; i <= 6; i++)
  {
    ledbar.tunrOn(i);
    delay(100);
  }

  delay(200);

  for(int i = 6; i >= 1; i--)
  {
    ledbar.tunrOff(i);
    delay(100);
  }
  
  delay(200);
}