#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define trigPin D7
#define echoPin D8

hd44780_I2Cexp lcd;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the
  Serial.begin(9600);
  Serial.println("Demo sensor HC-SR04 started");
  lcd.begin(16,2);     
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance: "); 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print(distance);
  Serial.println(distance);
  delay(1000);
}