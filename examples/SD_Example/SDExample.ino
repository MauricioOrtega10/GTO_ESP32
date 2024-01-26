#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//SD library
#include <SD.h>

//Timer variables
unsigned long previousMillis = 0;
const long interval = 5000;  // 5 Seconds

//File type object is created
File dataFile;

//Variables
int randomValue;

void setup() 
{
  //Serial initialization
  Serial.begin(115200);

  //SD communication initialization
  if (!SD.begin()) 
  {
    Serial.println("Failed to initialize SD");
    while(true);
  }
  Serial.println("SD initialized.");
}

void loop() 
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;

    //Random value is obtained
    randomValue = random(1000);

    //Open the file in write mode
    dataFile = SD.open("/data.txt", FILE_WRITE);

    //If the file opens correctly, write the data
    if (dataFile) 
    {   
      dataFile.seek(dataFile.size());  //Change location at the end of the file
      dataFile.println(randomValue);
      dataFile.close();
      Serial.println("Data saved correctly.");
    } 
    else 
    {
      Serial.println("Error opening file.");
    }

    //Open the file in read mode
    dataFile = SD.open("/data.txt");
    if (dataFile) 
    {
      Serial.print("data.txt: \n");
      while (dataFile.available()) 
      {
        Serial.write(dataFile.read()); //Read all the data from the file and then print it to the serial monitor.
      }
      dataFile.close();
    } 
    else 
    {
      Serial.println("error opening file.");
    }
  }
}

  