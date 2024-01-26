#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Color ssensor library
#include "VEML3328.h"

void setup() 
{
  Serial.begin(115200);

  //I2C protocol
  Wire.begin(); 

  //Begin color sensor with default values
  colorsensor.begin();
}

void loop() 
{
  Serial.print("Blue:");
  Serial.print(colorsensor.getBlue());   //read blue channel
  Serial.print(','); 
  Serial.print("Red:");
  Serial.print(colorsensor.getRed());    //read red channel
  Serial.print(',');  
  Serial.print("Green:");
  Serial.print(colorsensor.getGreen());  //read green channel
  Serial.print(',');  
  Serial.print("Clear:");
  Serial.print(colorsensor.getClear());  //read clear channel
  Serial.print(',');          
  Serial.print("IR:");
  Serial.println(colorsensor.getIR());   //read IR channel
  delay(200);
}