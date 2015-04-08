#include "gyro.h"
#include "Wire.h"

#define BMPaddress 0x77  // I2C BMP085_ADDRESS address of BMP085  
#define HMCaddress 0x1E//HMC5883L cichang
#define L3Gaddress 0xD2>>1//L3G4200D tuoluoyi
#define ADXaddress 0x53//ADXL345 jiasu //0x1D

const unsigned char oversampling_setting = 3;
const unsigned char pressure_conversiontime[4] = { 5, 8, 14, 26 };


void getBMPData(int* data){
  readData(BMPaddress,0xF6,data);
}
void getHMCData(int* data){
  readData(HMCaddress,0x03,data);
}

void getL3GData(int* data){
  readData(L3Gaddress,0x28,data);
}

void getADXData(int* data){
  readData(ADXaddress,0x32,data);
}
void readData(byte address,byte reg,int* data){
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

void initGy80(){
   Wire.begin();
  
   writeRegd(HMCaddress,0x02,0x00);
   
   writeRegd(BMPaddress,0xF4,0x2E);
   
   writeRegd(L3Gaddress,0x20,0x0F);
   writeRegd(L3Gaddress, 0x20, 0b00001111);    // 设置睡眠模式、x, y, z轴使能
   writeRegd(L3Gaddress, 0x21, 0b00000000);    // 选择高通滤波模式和高通截止频率 
   writeRegd(L3Gaddress, 0x22, 0b00000000);    // 设置中断模式
   writeRegd(L3Gaddress, 0x23, 0b00110000);    // 设置量程(2000dps)、自检状态、SPI模式
   writeRegd(L3Gaddress, 0x24, 0b00000000);
   
   writeRegd(ADXaddress,0x2D,0b00001000);
}









long x1, x2, x3, b3,b5,  b6, p,ut,up;
uint32_t b7,b4;
int getTemperature(){
 //calculate true temperature
  int32_t  ut= readUT();
  uint16_t ac5=readIntRegister(BMPaddress,0xB2);
  uint16_t ac6=readIntRegister(BMPaddress,0xB4);
  int16_t md= readIntRegister(BMPaddress,0xBE);
  int16_t mc = readIntRegister(BMPaddress,0xBC);

/*
  x1 = ((long)ut - ac6) * ac5 >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
*/
  x1 = (ut - (int32_t)ac6) * ((int32_t)ac5) >> 15;
  x2 = ((int32_t)mc << 11) / (x1+(int32_t)md);
  b5 = x1 + x2;
  return (b5 + 8) >> 4;
}

long getPressure(){
  getTemperature();
  up= readUP();
  Serial.print("**up");
  Serial.println(up);

  int16_t ac1 = readIntRegister(BMPaddress,0xAA);
  int16_t ac2 = readIntRegister(BMPaddress,0xAC);
  int16_t ac3 = readIntRegister(BMPaddress,0xAE);
  uint16_t ac4 = readIntRegister(BMPaddress,0xB0);

  int16_t b1 = readIntRegister(BMPaddress,0xB6);
  int16_t b2 = readIntRegister(BMPaddress,0xB8);

  b6 = b5 - 4000;

  x1 = ((int32_t)b2 * ( (b6 * b6)>>12 )) >> 11;
  x2 = ((int32_t)ac2 * b6) >> 11;
  x3 = x1 + x2;
  b3 = ((((int32_t)ac1*4 + x3) << oversampling_setting) + 2) / 4;

  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = ((uint32_t)ac4 * (uint32_t)(x3 + 32768)) >> 15;

  b7 = ((uint32_t)up - b3) * (uint32_t)( 50000UL >> oversampling_setting);

  p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;

  p = p + ((x1 + x2 + (int32_t)3791)>>4);
  return p;
}


unsigned int readUT() {
  writeRegd(BMPaddress,0xf4,0x2e);
  delay(5); // the datasheet suggests 4.5 ms
  return readIntRegister(BMPaddress,0xf6);
};

long readUP() {
  writeRegd(BMPaddress,0xf4,0x34+(oversampling_setting<<6));
  delay(pressure_conversiontime[oversampling_setting]);

  unsigned char msb, lsb, xlsb;
  Wire.beginTransmission(BMPaddress);
  Wire.write(0xf6);  // register to read
  Wire.endTransmission();

  Wire.requestFrom(BMPaddress, 3); // request three bytes
  while(!Wire.available()); // wait until data available
  msb = Wire.read();
  while(!Wire.available()); // wait until data available
  lsb |= Wire.read();
  while(!Wire.available()); // wait until data available
  xlsb |= Wire.read();
  long final=(((long)msb<<16) | ((long)lsb<<8) | ((long)xlsb));
  Serial.print("msb=");
  Serial.print(final);
  final>>=(8-oversampling_setting);
  return final;
}

void writeRegd(byte address,byte reg,byte value){
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
};

int readIntRegister(unsigned char address,unsigned char r){
  unsigned char msb, lsb;
  Wire.beginTransmission(address);
  Wire.write(r);  // register to read
  Wire.endTransmission();

  Wire.requestFrom((int)address, 2); // request two bytes
  while(!Wire.available()); // wait until data available
  msb = Wire.read();
  while(!Wire.available()); // wait until data available
  lsb = Wire.read();
  return (((int)msb<<8) | ((int)lsb));
};
