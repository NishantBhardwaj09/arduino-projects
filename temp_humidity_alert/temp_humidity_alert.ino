#include <dht.h>
#define dataPin 2
dht DHT;
int led = 12;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int status = DHT.read11(dataPin);
  if(status != DHTLIB_OK){
    Serial.println("DHT ERROR !");
    Serial.print("status ="); Serial.println(status);
    delay(5000);
    return;
  }
  float temp = DHT.temperature;
  float humid = DHT.humidity;
  Serial.print("Temperature :"); Serial.print(temp); Serial.println("C");
  Serial.print("Humidity :");Serial.print(humid);Serial.println("%");
  if(temp > 25 ){
    digitalWrite(led,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
  }
  else{
    digitalWrite(led,LOW);
    digitalWrite(LED_BUILTIN , LOW);
  }
  delay(2000);
}