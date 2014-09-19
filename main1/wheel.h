#ifndef wheel_h
#define wheel_h

#include "Arduino.h"

class Wheel{
  public:
    Wheel();
    void setEnergy(String wheel,int en);
    void setDir(String wheel,int dir);
    void initLeftWheel(int enPin,int aPin,int bPin);
    void initRightWheel(int enPin,int aPin,int bPin);
    void setCut(int var);
    void refresh(String wheel);
   private:
     int _left_en_pin;
     int _right_en_pin;
     int _left_A_pin;
     int _left_B_pin;
     int _right_A_pin;
     int _right_B_pin;
     
     int _en;
     float _var_k;//
     int _var_value;
     
     int _l_en;
     int _r_en;
     
     //void refresh_left()
     
};

#endif
