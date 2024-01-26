#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Microphone library
#include <Microphone.h>

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    //Print microphone values
    Serial.println(microphone.read()); //values 0-4095 
}