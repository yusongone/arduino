#include "Motor.h"

#define MAX_VALUE 100

Motor::Motor(int _stp,int _dir,int _en){
  pin_stp=_stp;
  pin_dir=_dir;
  pin_en=_en;
  pinMode(pin_stp,OUTPUT);
  pinMode(pin_dir,OUTPUT);
  pinMode(pin_en,OUTPUT);
  digitalWrite(pin_en,LOW);  
  pause=false;
  currentTime=0;
}

void Motor::powerToggle(boolean cmd){
  switch(cmd){
    case true:
      digitalWrite(pin_en,LOW);
    break;
    case false:
      digitalWrite(pin_en,HIGH);
    break;
  }
  
}

void Motor::changeDir(int dir){
  
}

void Motor::run(){
  if(pause){
    return;
  }
  digitalWrite(pin_stp,HIGH);//0.15 - 8
  if((micros()-currentTime)>(0.15+(1-power/100)*7.85)*1000){
    digitalWrite(pin_stp,LOW);
    currentTime=micros();
  }
}

void Motor::setValue(float _power){
  if(_power>0){
    changeDir(0);
    power=_power;
  }else if(_power<0){
    changeDir(1);
    power=-power;
  }else{
    pause=true;
  }
}
