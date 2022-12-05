#include <OneWire.h>
#include <DallasTemperature.h> 
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define ONE_WIRE_PIN D7
#define LED_RED D6
#define LED_AMARILLO D5

OneWire OneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&OneWire);
int sensorTempConnected = 0; 
hd44780_I2Cexp lcd;
unsigned long previusTimeTask1 = 0;
unsigned long previusTimeTask2 = 0;
unsigned long previusTimeTask3 = 0;
int ledAmarilloStado = LOW;

void setup() { 
  lcd.begin(16,2);     
  lcd.setCursor(0, 0);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);

  sensorTempConnected = sensors.getDeviceCount();
  lcd.print("Sensores connected: ");
  lcd.setCursor(0, 1);
  lcd.print(sensorTempConnected);
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp :");
}

void loop() {
  unsigned long currentTime = millis();
  lcd.setCursor(0, 1);


  sensors.requestTemperatures();
  float sensorTempValue = sensors.getTempCByIndex(sensorTempConnected);
  
  lcd.print(sensorTempValue); 

  if(sensorTempValue < 20)
  {
    digitalWrite(LED_AMARILLO, LOW);
    if(currentTime - previusTimeTask1 > 1000)
    { 
      digitalWrite(LED_RED, 255);
      previusTimeTask1 = currentTime;
    } 
  }
  if(sensorTempValue >= 20 && sensorTempValue < 30)
  {
    digitalWrite(LED_AMARILLO, LOW);
    if(currentTime - previusTimeTask2 > 1000)
    {
      digitalWrite(LED_RED, 255/2);
      previusTimeTask2 = currentTime;
    }
  }
  if(sensorTempValue > 30)
  {
    digitalWrite(LED_RED, LOW);    
    if(currentTime - previusTimeTask3 > 500)
    { 
      ledAmarilloStado = !ledAmarilloStado;
      digitalWrite(LED_AMARILLO, ledAmarilloStado);  
      previusTimeTask3 = currentTime;
    }
  }
   
}

 
