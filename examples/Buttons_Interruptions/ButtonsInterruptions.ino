#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>


//Buttons library
#include "Buttons.h"

void buttonInterrupt_1() 
{
  Serial.println("Button 1 has been pressed");  
}

void buttonInterrupt_2() 
{
  Serial.println("Button 2 has been pressed");  
}

void buttonInterrupt_3() 
{
  Serial.println("Button 3 has been pressed");  
}

void buttonInterrupt_4() 
{
  Serial.println("Button 4 has been pressed");  
}

void buttonInterrupt_5() 
{
  Serial.println("Button 5 has been pressed");  
}

void setup() 
{
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), buttonInterrupt_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), buttonInterrupt_2, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_3_PIN), buttonInterrupt_3, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_4_PIN), buttonInterrupt_4, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_5_PIN), buttonInterrupt_5, FALLING);
}

void loop() 
{

}
