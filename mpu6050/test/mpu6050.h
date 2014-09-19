#include <Wire.h>

#include <Arduino.h>

#ifndef MPU6050_H
#define MPU6050_H


class Mpu6050{
  public:
    Mpu6050();
    void getMpuData(int Array[7]);
    int test();
    void init();
   private:
     void initMpu();
     void lookStatus();
     int i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop);
     int i2cWrite(uint8_t registerAddress, uint8_t* data, uint8_t length, bool sendStop);
     int i2cRead(uint8_t registerAddress, uint8_t* data, uint8_t nbytes);
     int16_t gyroXoffset;
     int16_t gyroYoffset;
      int16_t gyroZoffset;
};

#endif
