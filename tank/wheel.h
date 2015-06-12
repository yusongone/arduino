#ifndef WHEEL_H
#define WHEEL_H

#include "Arduino.h"

class Wheel{
  public :
    Wheel(int d_pin,int p_pin);
    void dir(int value);
    void init();
    void speed(int value);
  private:
    int d_pin;
    int p_pin;
    int old_pwm;
    int old_dir;
};
#endif
