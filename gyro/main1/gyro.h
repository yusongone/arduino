
#include <Arduino.h>

#ifndef gyro_h
#define gyro_h

class Gyro{
  public:
    Gyro();
    void initGy80();
    void getADXData(int* data);
    void getL3GData(int* data);
    void getHMCData(int* data);
    void getBMPData(int* data);
    
    void test();
  private:
    void readData(byte address,byte reg,int* data);
    void writeRegd(byte address,byte reg,byte value);
    int a;
};
#endif
