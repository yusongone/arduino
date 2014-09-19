#ifndef wheel2_h
#define wheel2_h

#include "Arduino.h"

class Wheel2{
  public:
    Wheel2();
    void initPin(int en_pin,int pin1,int pin2);
    void setEnergy(int en);
    
   private:
     void setDir(int en);
     int _en_pin;
     int _pin1;
     int _pin2;
     
     int _en;
     
};

#endif
