#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Buttons library
#include "Buttons.h"

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if (buttons.read(1) == LOW) 
  {
    Serial.println("Button 1 has been pressed");
    delay(200);
  }

  if (buttons.read(2) == LOW) 
  {
    Serial.println("Button 2 has been pressed");
    delay(200);
  }

  if (buttons.read(3) == LOW) 
  {
    Serial.println("Button 3 has been pressed");
    delay(200);
  }

  if (buttons.read(4) == LOW) 
  {
    Serial.println("Button 4 has been pressed");
    delay(200);
  }

  if (buttons.read(5) == LOW) 
  {
    Serial.println("Button 5 has been pressed");
    delay(200);
  }
  
}