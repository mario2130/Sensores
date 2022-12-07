

#define TriggerUSonic D6
#define EchoUSonic D5
#define Humedity D4
#define Buzzer D2
#define LEDYellow D7
#define LEDRed D8
#define LEDGreen D1


void setup() {
  // put your setup code here, to run once:
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDYellow, HIGH);
  delay(500);
  digitalWrite(LEDYellow, LOW);
  delay(500);
}
