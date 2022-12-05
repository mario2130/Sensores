#include <OneWire.h>
#include <DallasTemperature.h> 
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define ONE_WIRE_PIN D7 

OneWire OneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&OneWire);
int sensorTempConnected = 0; 
hd44780_I2Cexp lcd; 

 
  // put your setup code here, to run once:
void setup() { 
  lcd.begin(16,2);     
  lcd.setCursor(0, 0); 
  Serial.begin(115200);

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
  Serial.println(sensorTempValue);

  delay(1000);
   
}
