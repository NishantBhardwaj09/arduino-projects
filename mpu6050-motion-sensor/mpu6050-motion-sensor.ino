#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
 
/*  for (int addr = 0 ; addr < 128; addr ++){  //I2C SCANNER SKETCH
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if(error == 0 ){
      Serial.print("Device found at 0x"); Serial.println(addr,HEX);
    }
  }
*/
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);  //register address of PWR_MGMT_1
    Wire.write(0x00);
    byte error = Wire.endTransmission();
    if(error == 0 ){
      Serial.println("MPU-6050 Waked up !");
    }
    else{
      Serial.println("FAILED TO WAKE UP !"); Serial.print("error code :"); Serial.println(error);
    }

}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //register address of ACCEL_XOUT_H
  Wire.endTransmission(false);
  uint8_t bytesReceived = Wire.requestFrom(0x68,6);
  if(bytesReceived == 6 ){
    int16_t ax = Wire.read() << 8 | Wire.read() ; 
    int16_t ay = Wire.read() << 8 | Wire.read() ; 
    int16_t az = Wire.read() << 8 | Wire.read() ; 
    Serial.println("acceleration :");
    Serial.print("X : ") ; Serial.print((float)ax/16384);
    Serial.print(" Y : ") ; Serial.print((float)ay/16384);
    Serial.print(" Z : ") ; Serial.println((float)az/16384);
  }
  else{
    Serial.println("failed to read acceleration");
    return ;
  }
  Wire.beginTransmission(0x68);
  Wire.write(0x43);  //register address of GYRO_XOUT_H
  Wire.endTransmission(false);
  byte gyroBytes = Wire.requestFrom(0x68,6);
  if(gyroBytes == 6){
    int16_t gx = Wire.read() << 8 | Wire.read() ;
    int16_t gy = Wire.read() << 8 | Wire.read() ;
    int16_t gz = Wire.read() << 8 | Wire.read() ;
    Serial.println("Rotation :");
    Serial.print("X : ") ; Serial.print((float)gx/131);
    Serial.print(" Y : ") ; Serial.print((float)gy/131);
    Serial.print(" Z : ") ; Serial.println((float)gz/131);
  }
  else{
    Serial.println("failed to read rotation");
    return;
  }

  delay(500);
}
