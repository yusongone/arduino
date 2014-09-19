#include "mpu6050.h"
#include <Wire.h>


const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication

Mpu6050::Mpu6050(){
  /*
  gyroXoffset = -139;
  gyroYoffset = -74;
  gyroZoffset = -111;
   */
   gyroXoffset = 0;
  gyroYoffset = 0;
  gyroZoffset = 0;
  
}

void Mpu6050::init(){
  Wire.begin();
 Mpu6050::initMpu();
  Mpu6050::lookStatus();
}

void Mpu6050::getMpuData(int Array[7]){
  uint8_t i2cData[15];
  while(Mpu6050::i2cRead(0x3B,i2cData,14));
  Array[0] = ((i2cData[0] << 8) | i2cData[1]);//x
  Array[1] = ((i2cData[2] << 8) | i2cData[3]);//y
  Array[2] = ((i2cData[4] << 8) | i2cData[5]);//z
  Array[3] = ((i2cData[6] << 8) | i2cData[7]);  //tempRAW
  Array[4] = ((i2cData[8] << 8) | i2cData[9])+gyroXoffset;
  Array[5] = ((i2cData[10] << 8) | i2cData[11])+gyroYoffset;
  Array[6] = ((i2cData[12] << 8) | i2cData[13])+gyroZoffset;
}


void Mpu6050::lookStatus(){
  uint8_t i2cData[4];
  while(Mpu6050::i2cRead(0x75,i2cData,1));
    if(i2cData[0] != 0x68) { // Read "WHO_AM_I" register
      Serial.print(F("Error reading sensor"));
      while(1);
    }
}
void Mpu6050::initMpu(){
  uint8_t setData[4];
  setData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  setData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  setData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  setData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while(i2cWrite(0x19,setData,4,false)); // Write to all four registers at once
  while(i2cWrite(0x6B,0x01,true));
  Serial.print("init success");
}

int Mpu6050::i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop) {
  return i2cWrite(registerAddress,&data,1,sendStop); // Returns 0 on success
}

int Mpu6050::i2cWrite(uint8_t registerAddress, uint8_t* data, uint8_t length, bool sendStop) {
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data, length);
  return Wire.endTransmission(sendStop); // Returns 0 on success
}


int Mpu6050::i2cRead(uint8_t registerAddress, uint8_t* data, uint8_t nbytes) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  if(Wire.endTransmission(false)) // Don't release the bus
    return 1; // Error in communication
  Wire.requestFrom(IMUAddress, nbytes,(uint8_t)true); // Send a repeated start and then release the bus after reading
  for(uint8_t i = 0; i < nbytes; i++) {
    if(Wire.available())
      data[i] = Wire.read();
    else {
      timeOutTimer = micros();
     // while(((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
      if(Wire.available())
        data[i]= Wire.read();
      else
        return 2; // Error in c
    }
  }
  return 0; // Success
}
