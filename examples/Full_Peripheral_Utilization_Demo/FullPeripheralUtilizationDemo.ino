/*
In this example, we utilize all the peripherals on the board as follows:

The potentiometer controls the servo.
Button 1 toggles the buzzer.
Button 2 changes the color of the RGB LED.
Button 3 displays the color sensor data on the screen.
Button 4 displays the microphone data on the screen.
Button 5 displays the IMU data on the screen.
The LED bar indicates the distance measured by the sonar.
All the displayed data is saved in the SD memory.

Note:
Since the RGB LED and the LED bar share some pins, their operation may be affected when used simultaneously. 
Due to this, I recommend the following actions:

To enable the LED bar, set the RGB LED to white using button 1.
To use the RGB LED, ensure that the LEDs in the LED bar do not illuminate. This can be achieved by avoiding any obstruction to the sonar signal.
*/
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Libraries
#include "Adafruit_SSD1306.h"
#include "Buttons.h"
#include "EasyBuzzer.h"
#include "kxtj3-1057.h"
#include "LedBar.h"
#include "LedRGB.h"
#include "Microphone.h"
#include "Potentiometer.h"
#include "VEML3328.h"
#include "ESP32Servo.h" 
#include "NewPing.h"
#include "SD.h"

//Variables
bool buzzer_flag = false;
int display_data = 1;
String color = "";
int angulo = 0;
int distance = 0;
uint16_t red;
uint16_t green;
uint16_t blue;
uint16_t clear;
uint16_t ir;
uint16_t mic;
float x;
float y;
float z;
File dataFile;

//Timers variables
unsigned long currentMillis;
unsigned long previousMillis_display = 0;
unsigned long previousMillis_data_refresh = 0;
unsigned long previousMillis_actuators_refresh = 0;
const long interval_display = 1000;
const long interval_data_refresh = 100;
const long interval_actuators_refresh = 100;

//Functions
void color_sensor_data(uint16_t r, uint16_t g, uint16_t b, uint16_t clear, uint16_t ir);
void microphone_data(uint16_t mic);
void imu_data(float x, float y, float z);

//Interrupt functions
void buttonInterrupt_buzzer();
void buttonInterrupt_set_color();
void buttonInterrupt_color_sensor_display();
void buttonInterrupt_microphone_display();
void buttonInterrupt_imu_display();



void setup() 
{
  //Serial initialization
  Serial.begin(115200);
  
  //I2C protocol
  Wire.begin(); 

  //IMU initialization
  if (imu.begin() == IMU_SUCCESS) 
  {
    Serial.println("IMU initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize IMU.");
    while(true);
  }

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

  //Color sensor initialization
  if(colorsensor.begin())
  {
    Serial.println("Color Sensor initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize Color Sensor.");
    while(true);
  }

  //Color sensor initialization
  if(SD.begin())
  {
    Serial.println("SD initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize SD.");
    while(true);
  }

  //Interrupts initialization
  attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), buttonInterrupt_buzzer, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), buttonInterrupt_set_color, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_3_PIN), buttonInterrupt_color_sensor_display, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_4_PIN), buttonInterrupt_microphone_display, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_5_PIN), buttonInterrupt_imu_display, FALLING);

}

void loop() 
{
  currentMillis = millis();

  //Data refresh timer
  if (currentMillis - previousMillis_data_refresh >= interval_data_refresh) 
  {
    previousMillis_data_refresh = currentMillis;

    distance = sonar.ping_cm();
    angulo = map(potentiometer.read(), 0, 4095, 0, 180);
    red = colorsensor.getRed();
    green = colorsensor.getGreen();
    blue = colorsensor.getBlue();
    clear = colorsensor.getClear();
    ir = colorsensor.getIR();
    mic = microphone.read();
    imu.standby(false);
    x = imu.axisAccel(X);
    y = imu.axisAccel(Y);
    z = imu.axisAccel(Z);
    imu.standby(true);

    //Open the file in write mode
    dataFile = SD.open("/data.txt", FILE_WRITE);

    //If the file opens correctly, write the data
    if (dataFile) 
    {   
      dataFile.seek(dataFile.size());  //Change location at the end of the file
      dataFile.print(red);
      dataFile.print(",");
      dataFile.print(green);
      dataFile.print(",");
      dataFile.print(blue);
      dataFile.print(",");
      dataFile.print(clear);
      dataFile.print(",");
      dataFile.print(ir);
      dataFile.print(",");
      dataFile.print(mic);
      dataFile.print(",");
      dataFile.print(x);
      dataFile.print(",");
      dataFile.print(y);
      dataFile.print(",");
      dataFile.println(z);
      dataFile.close();
      Serial.println("Data saved correctly.");
    } 
    else 
    {
      Serial.println("Error opening file.");
    }
  }

  //Display timer
  if (currentMillis - previousMillis_display >= interval_display) 
  {
    previousMillis_display = currentMillis;
    switch (display_data)
    {
      case 1:
        color_sensor_data(red,green,blue,clear,ir);
      break;

      case 2:
        microphone_data(mic);  
      break;

      case 3:
        imu_data(x, y, z); 
      break;
    }
  }

  //Actuators refresh timer
  if (currentMillis - previousMillis_actuators_refresh >= interval_actuators_refresh) 
  {
    previousMillis_actuators_refresh = currentMillis;

    servo.write(angulo);

    led_rgb.setColor(color);

    if(buzzer_flag)
    {
      buzzer.beep(500);
    }
    else
    {
      buzzer.stopBeep();
    }

    if (distance >= 5) {
      ledbar.tunrOn(1);
    } 
    else 
    {
      ledbar.tunrOff(1);
    }
    if (distance > 10) 
    {
      ledbar.tunrOn(2);
    } 
    else 
    {
      ledbar.tunrOff(2);
    }
    if (distance > 15) 
    {
      ledbar.tunrOn(3);
    } 
    else 
    {
      ledbar.tunrOff(3);
    }
    if (distance > 20) 
    {
      ledbar.tunrOn(4);
    } 
    else 
    {
      ledbar.tunrOff(4);
    }
    if (distance > 25) 
    {
      ledbar.tunrOn(5);
    } 
    else 
    {
      ledbar.tunrOff(5);
    }
    if (distance > 30) 
    {
      ledbar.tunrOn(6);
    } 
    else 
    {
      ledbar.tunrOff(6);
    }
  }

}

void color_sensor_data(uint16_t r, uint16_t g, uint16_t b, uint16_t clear, uint16_t ir) 
{
  display.clearDisplay();
  display.setTextSize(1);            
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0);           
  display.println(F("Sensor Color Channels\n"));
  display.print(F("Red: "));
  display.println(r);
  display.print(F("Green: "));
  display.println(g);
  display.print(F("Blue: "));
  display.println(b);
  display.print(F("Clear: "));
  display.println(clear);
  display.print(F("IR: "));
  display.println(ir);
  display.display();
}

void microphone_data(uint16_t mic) 
{
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0);        
  display.println(F("     Microphone\n\n\n"));
  display.print(F("Value: "));
  display.println(mic);
  display.display();
}

void imu_data(float x, float y, float z) 
{
  display.clearDisplay();
  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);       
  display.setCursor(0,0);       
  display.println(F("         IMU\n\n"));
  display.print(F("X axis: "));
  display.println(x);
  display.print(F("Y axis: "));
  display.println(y);
  display.print(F("Z axis: "));
  display.println(z);
  display.display();
}

void buttonInterrupt_buzzer()
{
  buzzer_flag = !buzzer_flag;
}

void buttonInterrupt_set_color()
{
  if (color == "") 
  {
    color = "white";
  } 
  else if (color == "white") 
  {
    color = "red";
  } 
  else if (color == "red") 
  {
    color = "green";
  } 
  else if (color == "green") 
  {
    color = "blue";
  } 
  else if (color == "blue") 
  {
    color = "yellow";
  } 
  else if (color == "yellow") 
  {
    color = "orange";
  } 
  else if (color == "orange") 
  {
    color = "violet";
  } 
  else if (color == "violet") 
  {
    color = "turquoise";
  } 
  else if (color == "turquoise") 
  {
    color = "grey";
  }
  else if (color == "grey") 
  {
    color = "maroon";
  } 
  else if (color == "maroon") 
  {
    color = "fuchsia";
  } 
  else if (color == "fuchsia") 
  {
    color = "";
  }
}

void buttonInterrupt_color_sensor_display()
{
  display_data = 1;
}

void buttonInterrupt_microphone_display()
{
  display_data = 2;
}

void buttonInterrupt_imu_display()
{
  display_data = 3;
}