#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_PIN D7
#define analogo A0
#define DSW_EPOCA D3
#define DSW_LCD D4
#define LED_VENTILADOR_A D5
#define LED_CALEFACTOR_R D6
#define LED_BOMBA_V D0
unsigned long period = 10000UL;
unsigned long lightTask;
int EstadoLed = LOW;
/*con el sensor de temperatura DS18B20, un sensor de humedad de suelo, una bomba (led
verde), un calefactor (led rojo) y un ventilador (led amarillo)
*/

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire (ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);


void setup() {

  
  //pinMode(FLOWER_TIME, INPUT_PULLUP);
  pinMode(DSW_EPOCA, INPUT);
  pinMode(DSW_LCD, INPUT);
  pinMode(LED_BOMBA_V, OUTPUT);
  pinMode(LED_VENTILADOR_A, OUTPUT);
  pinMode(LED_CALEFACTOR_R, OUTPUT);
  // Serial y LCD
  Serial.begin(9600);
  
  lcd.init();
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  sensors.begin();

  

}

void loop() {

  unsigned long currentTime = millis();
   unsigned long temp = 0; 
  
    /*DSW_EPOCA == 0 Floración
      DSW_EPOCA == 1 Temperatura*/
      
  //int DSW_EPOCA = 1;
  
  /*DSW_LCD == 0 Humedad
    DSW_LCD == 1 Temperatura*/
     
  //int DSW_LCD = 0;
  
  int HumedadAnaloga = analogRead(A0);
  // Calibramos entre 0 y 550 para que entregue 0 y 100 aprox
  float Humedad =  map(HumedadAnaloga, 0, 1023, 550, 0);
  float Temperature = sensors.getTempCByIndex(0);

  sensors.requestTemperatures();

  int lectura_dsw1 = digitalRead(DSW_EPOCA);
  //Serial.println(lectura_dsw1);
  int lectura_dsw2 = digitalRead(DSW_LCD);
  //Serial.println(lectura_dsw2);

    Serial.print("CT ");
    Serial.println(currentTime);
    Serial.print("LT ");
    Serial.println(lightTask);
  

// Rutina para M ostrar temperatura o humedad en LCD
 if (lectura_dsw2 == 0 && lectura_dsw1 == 0)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEM:");
    lcd.setCursor(5,0);
    lcd.print(Temperature);
    lcd.setCursor(0,1);
    lcd.print("FLORACION");
    }
 if (lectura_dsw2 == 0 && lectura_dsw1 == 1)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEM:");
    lcd.setCursor(5,0);
    lcd.print(Temperature);
    lcd.setCursor(0,1);
    lcd.print("DESARROLLO");
    }
    
 if (lectura_dsw2 == 1 && lectura_dsw1 == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humedad:");
    lcd.setCursor(9,0);
    lcd.print(Humedad);
    lcd.setCursor(0,1);
    lcd.print("FLORACION");
    }
  if (lectura_dsw2 == 1 && lectura_dsw1 == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humedad:");
    lcd.setCursor(9,0);
    lcd.print(Humedad);
    lcd.setCursor(0,1);
    lcd.print("DESARROLLO");
    }


  /*Si la humedad es inferior al 30% se debe prender una bomba y se debe apagar luego de 2
minutos
*/
  if (Humedad < 30)
   {
     digitalWrite(LED_BOMBA_V, HIGH);

     /*Se utiliza solo 5 seg 
        NOTA: no se pudo implementar con millis()
     */
     delay(5000);
   
   }
  else{digitalWrite(LED_BOMBA_V, LOW);}
      
   if(Temperature < 27 && lectura_dsw1 == 0) //&& DSW_EPOCA == FLORES)
     {
     digitalWrite(LED_CALEFACTOR_R, HIGH);
     digitalWrite(LED_VENTILADOR_A, LOW);    
      } 
   if(Temperature > 27 && lectura_dsw1 == 0)
    {
      digitalWrite(LED_CALEFACTOR_R, LOW);
      }

    /*
     * En época de desarrollo del tomate, la temperatura debe estar entre los 18 y 27°C.
     * si es Temp < 18 y está en esta época se encenderá Calefactor
     * se temp es > 27 se encenderá Ventilador
     */
   if(Temperature < 18 && lectura_dsw1 == 1) //DSW_EPOCA == TOMATES)
     {
     digitalWrite(LED_CALEFACTOR_R, HIGH);    
     } 
    if(Temperature > 18 && lectura_dsw1 == 1) //&& DSW_EPOCA == TOMATES)
     {
     digitalWrite(LED_CALEFACTOR_R, LOW);    
     } 

   if(Temperature > 27 && lectura_dsw1 == 1) //&& DSW_EPOCA == TOMATES)
    {
    digitalWrite(LED_VENTILADOR_A, HIGH);    
    } 
   if(Temperature < 27 && lectura_dsw1 == 1) //&& DSW_EPOCA == TOMATES)
    {
    digitalWrite(LED_VENTILADOR_A, LOW);    
    } 
  


}
