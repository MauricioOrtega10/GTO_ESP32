#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Buzzer library
#include "EasyBuzzer.h"

unsigned int frequency = 1000;

void setup() 
{
}

void loop() 
{
  buzzer.beep(frequency);
  delay(1000);
  buzzer.stopBeep();
  delay(1000);
}