#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define trigPin D7
#define echoPin D8
#define ledRed D2
#define ledYellow D5
#define ledGreen D6
#define buzzer D3

hd44780_I2Cexp lcd;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  pinMode(ledRed, OUTPUT); 
  pinMode(ledYellow, OUTPUT); 
  pinMode(ledGreen, OUTPUT); 

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
  //send trigger
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (distance as centimeter)
  // Displays the distance on the Serial Monitor & LCD
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print(distance);
  Serial.println(distance);

  if(distance > 100)
  {
    digitalWrite(ledGreen, HIGH);
    noTone(buzzer); 
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
  }
  if(distance >= 50 && distance <=100)
  {
    digitalWrite(ledYellow, HIGH);
    noTone(buzzer);
    //set default led
    digitalWrite(ledGreen, LOW); 
    digitalWrite(ledRed, LOW);
  }
  if(distance < 50)
  {
    digitalWrite(ledRed, HIGH);
    tone(buzzer, 500);
    //set default led
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW); 
  } 
}