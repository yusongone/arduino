
#include <Arduino.h>

#ifndef gyro_h
#define gyro_h

unsigned int readUT();
long readUP();
int readIntRegister(unsigned char address,unsigned char r);
int getTemperature();
int getPressure();
void initGy80();
void getADXData(int* data);
void getL3GData(int* data);
void getHMCData(int* data);
void getBMPData(int* data);

void readData(byte address,byte reg,int* data);
void writeRegd(byte address,byte reg,byte value);


#endif
