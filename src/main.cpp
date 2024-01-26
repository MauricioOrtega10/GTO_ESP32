#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void setup() 
{
  //Serial initialization
  Serial.begin(115200);  
}

  
void loop()
{
  Serial.println("I'm dying of boredom. This example is very simple :/");
  Serial.println("I suggest trying any of the examples from the repository by copying and pasting their contents into this file instead.");
  delay(5000);
}