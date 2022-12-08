# include <OneWire.h>
# include <DallasTemperature.h>
# include <LiquidCrystal_I2C.h>

# define ONE_WIRE_PIN D7
# define ROJO D5
# define AMARILLO D6 


LiquidCrystal_I2C lcd(0x27 , 16 ,2 );
OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
int sensorTempConnected=0;

int q=0;

void setup(){
  lcd.init();
  lcd.backlight();
  sensors.begin();
  Serial.begin(9600);
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
}

void loop()
{

sensors.requestTemperatures();

lcd.setCursor(1,0);

float temperatura = sensors.getTempCByIndex(0);
Serial.println (temperatura);

  if (temperatura < 20){
  analogWrite(ROJO,255);
  analogWrite(AMARILLO,0);
  lcd.print("menor que 20");
  lcd.setCursor(1,1);
  lcd.print(temperatura);

 }
 else if (temperatura >= 20 && temperatura <= 30){
  analogWrite(ROJO,12);
  analogWrite(AMARILLO,0);
  lcd.print("entre 20 y 30");
  lcd.setCursor(1,1);
  lcd.print(temperatura);
}
else{
  analogWrite(ROJO,0);
 /* for(int i = 1; i<6; i++){
 analogWrite(AMARILLO,255);
  lcd.print("mayor 30");
  lcd.setCursor(1,1);
  lcd.print(temperatura);
    delay(500);
  analogWrite(AMARILLO,0);
  lcd.print("mayor 30");
  lcd.setCursor(1,1);
  lcd.print(temperatura);
    delay(500);  
*/

  analogWrite(AMARILLO,255);
  lcd.print("mayor 30");
  lcd.setCursor(1,1);
  lcd.print(temperatura);

}
}


 
