#include "gyro.h"
#include "Wire.h"

#define BMPaddress 0x77  // I2C BMP085_ADDRESS address of BMP085  
#define HMCaddress (0x1E)//HMC5883L cichang
#define L3Gaddress (0xD2>>1)//L3G4200D tuoluoyi
#define ADXaddress (0x53)//ADXL345 jiasu

Gyro::Gyro(){
  Wire.begin();
}

void Gyro::test(){

}
void Gyro::getBMPData(int* data){
  Gyro::readData(BMPaddress,0xF6,data);
}
void Gyro::getHMCData(int* data){
  Gyro::readData(HMCaddress,0x03,data);
}

void Gyro::getL3GData(int* data){
  Gyro::readData(L3Gaddress,0x28,data);
}

void Gyro::getADXData(int* data){
  Gyro::readData(ADXaddress,0x32,data);
}
void Gyro::readData(byte address,byte reg,int* data){
  //int data[3]={0,0,0};
  Wire.beginTransmission(address);
  Wire.write(reg| (1 << 7));
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)6);
  while (Wire.available() < 6){};
  
  uint8_t xlow=Wire.read();
  uint8_t xhig=Wire.read();
  uint8_t ylow=Wire.read();
  uint8_t yhig=Wire.read();
  uint8_t zlow=Wire.read();
  uint8_t zhig=Wire.read();

  data[0]=xhig<<8|xlow;
  data[1]=yhig<<8|ylow;
  data[2]=zhig<<8|zlow;
  //return data;
}
void Gyro::initGy80(){
   Gyro::writeRegd(HMCaddress,0x02,0x00);
   
   Gyro::writeRegd(BMPaddress,0xF4,0x2E);
   
   Gyro::writeRegd(L3Gaddress,0x20,0x0F);
   Gyro::writeRegd(L3Gaddress, 0x20, 0b00001111);    // 设置睡眠模式、x, y, z轴使能
   Gyro::writeRegd(L3Gaddress, 0x21, 0b00000000);    // 选择高通滤波模式和高通截止频率 
   Gyro::writeRegd(L3Gaddress, 0x22, 0b00000000);    // 设置中断模式
   Gyro::writeRegd(L3Gaddress, 0x23, 0b00110000);    // 设置量程(2000dps)、自检状态、SPI模式
   Gyro::writeRegd(L3Gaddress, 0x24, 0b00000000);
   
   Gyro::writeRegd(ADXaddress,0x2D,0b00001000);
}

void Gyro::writeRegd(byte address,byte reg,byte value){
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
};
