#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Bluetooth Library
#include "BluetoothSerial.h"

//Libraries
#include "Buttons.h"
#include "Adafruit_SSD1306.h"
#include "LedRGB.h"
#include "Potentiometer.h"
#include "ESP32Servo.h" 

//Variables
BluetoothSerial SerialBT;
String bluetoothData = "";
int red = 0;
int green = 0;
int blue = 0;

//Definition of functions to process commands
void processRGBCommand(String command);
void processSRVCommand(String command);
void processDSPCommand(String command);
void processPTMCommand(String command);
void processBTNCommand(String command);

void setup() 
{
  //Serial initialization
  Serial.begin(15200);

  //Display initialization
  if (display.begin()) 
  {
    Serial.println("Display initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize Display.");
    while(true);
  }
  
  //Bluetooth initialization
  SerialBT.begin("BT_Control");
  Serial.println("BT Control");
}

void loop() 
{
  //Read the input values and execute the function corresponding to the command
  if (SerialBT.available()) 
  {
    char incomingByte = SerialBT.read();
    if (incomingByte == '\n') 
    {
      if (bluetoothData.startsWith("RGB:")) 
      {
        processRGBCommand(bluetoothData);
      }
      else if (bluetoothData.startsWith("SRV:"))
      {
        processSRVCommand(bluetoothData);
      }
      else if (bluetoothData.startsWith("DSP:"))
      {
        processDSPCommand(bluetoothData);
      }
      else if (bluetoothData.startsWith("PTM"))
      {
        processPTMCommand(bluetoothData);
      }
      else if (bluetoothData.startsWith("BTN"))
      {
        processBTNCommand(bluetoothData);
      }

      bluetoothData = "";
    } 
    else 
    {
      bluetoothData += incomingByte;
    }
  }
}

//Implementation of functions to process commands
void processRGBCommand(String command) 
{
  char color = command.charAt(4);
  int value = command.substring(5).toInt();
  value = constrain(value, 0, 255);

  switch (color) 
  {
    case 'R':
      red = value;
      break;
    case 'G':
      green = value;
      break;
    case 'B':
      blue = value;
      break;
    default:
      return;
  }
  led_rgb.setColor(red, green, blue);
  
}

void processSRVCommand(String command) 
{
  int value = command.substring(4).toInt();
  value = constrain(value, 0, 255);
  servo.write(value);
}

void processDSPCommand(String command) 
{
  int value = command.substring(4).toInt();
  value = constrain(value, 0, 1);
  if (value == 1)
  {
    display.clearDisplay();
    display.drawBitmap(
      (display.width() - 128) / 2, 
      (display.height() - 64) / 2,
      national_byte, 128, 64, 1);
    display.display();
  }
  else
  {
    display.clearDisplay();
    display.display();
  }

}

void processPTMCommand(String command) 
{
  String return_msg = String(potentiometer.read());
  for (char caracter : return_msg)
  {
    SerialBT.write(caracter);
  }
}

void processBTNCommand(String command) 
{
  int value = 0;
  value |= buttons.read(1); 
  value |= buttons.read(2)<<1;
  value |= buttons.read(3)<<2;
  value |= buttons.read(4)<<3;
  value |= buttons.read(5)<<4;
  String return_msg = String(value);
  for (char caracter : return_msg)
  {
    SerialBT.write(caracter);
  }
}
