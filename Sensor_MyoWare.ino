
#include <WiFiNINA.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
void setup() 
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.setCursor(30, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Sensor");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(3000);
}
 
void loop() 
{
  float sensorValue = analogRead(A1);
  float millivolt = (sensorValue/1023)*5;
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  Serial.print("Voltage: ");
  Serial.print(millivolt*1000);
  Serial.println(" mV");
  Serial.println("");
 
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Sensor Value: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println(sensorValue,0);
  
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Voltage: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(millivolt*1000);
  display.println(" mv");
 
  display.display();
  
  delay(1);       
}
