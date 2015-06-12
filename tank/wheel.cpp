#include "wheel.h"

Wheel::Wheel(int _d_pin,int _p_pin){
  d_pin=_d_pin;
  p_pin=_p_pin;
}

void Wheel::dir(int status){
  int dir=status>0;
  digitalWrite(d_pin,dir);
}


void Wheel::init(){
  pinMode(d_pin,OUTPUT);
  pinMode(p_pin,OUTPUT);
  digitalWrite(d_pin,HIGH);
  analogWrite(p_pin,0);
}


void Wheel::speed(int value){
  int pwm=abs(value);
  pwm<30?pwm=0:pwm=pwm;
  analogWrite(p_pin,pwm);
}
