#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Microphone - Dispaly libraries
#include <Microphone.h>
#include <Adafruit_SSD1306.h>

//Popcat bitmap
#include "Popcat.h"

int value;

void draw_popcat( const uint8_t bitmap[]);

void setup() 
{
  Serial.begin(115200);
  
  // initialize OLED
  if (!display.begin()) 
  {
    Serial.println(F("failed to start display"));
    while (1);
  }
}

void loop() 
{
  value = microphone.read();
  Serial.println(value);
  if(value < 2000)
  {
    draw_popcat(popcat_1);
  }
  else
  {
    draw_popcat(popcat_2);
  }
}

void draw_popcat( const uint8_t bitmap[]) 
{
  display.clearDisplay();

  display.drawBitmap(
    (display.width() - 128) / 2, 
    (display.height() - 64) / 2,
    bitmap, POP_CATS_WIDTH, POP_CATS_HEIGHT, 1);
  display.display();
}