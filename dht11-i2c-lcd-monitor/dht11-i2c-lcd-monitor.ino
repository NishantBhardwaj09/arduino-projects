#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <Wire.h>
#define DataPin 2
unsigned long prevMillis = 0;
const unsigned long interval = 2000;
dht DHT;
LiquidCrystal_I2C lcd (0x27,16,2);
void setup() {
  Wire.begin();
  Serial.begin(9600);               
/* // I2C SCANNER SKETCH 
  for(byte addr = 0 ; addr < 128 ; addr++){ 
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if(error == 0 ){
      Serial.print("address is 0x"); Serial.println(addr,HEX);
    }
  }
*/
  lcd.init();
  lcd.backlight();
}

void loop() {
  unsigned long currentMillis = millis();

  if( currentMillis - prevMillis >= interval ){
    prevMillis = currentMillis ;
    int status = DHT.read11(DataPin);

    if (status == DHTLIB_OK){
      int temp = DHT.temperature;
      int humid = DHT.humidity;
        if(temp > 29 ){
        lcd.setCursor(0, 0);
        lcd.print("ALERT !         ");
        lcd.setCursor(0, 1);
        lcd.print("Temp : "); lcd.print(temp); lcd.print((char)223); lcd.print("C       ");  //degree symbol 223
        }
        else{
          lcd.setCursor(0, 0);
          lcd.print("Temp : "); lcd.print(temp); lcd.print((char)223); lcd.print("C      ");  
          lcd.setCursor(0, 1);
          lcd.print("Hum  : "); lcd.print(humid); lcd.print("%         ");  
        }
  }

    else{
      lcd.setCursor(0, 0);
      lcd.print("Error !");
      lcd.setCursor(0, 1);
      lcd.print("status = "); lcd.print(status);
    }
  }
}