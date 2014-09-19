#include <Arduino.h>
#include "wheel_2.h"

Wheel2::Wheel2(){
   
}

void Wheel2::initPin(int en_pin,int pin1,int pin2){
  _en_pin=en_pin;
  _pin1=pin1;
  _pin2=pin2;
  
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(en_pin,OUTPUT);
}

void Wheel2::setEnergy(int en){
  _en=en;
 
  analogWrite(_en_pin,abs(en)+70);
  Wheel2::setDir(en);
}

void Wheel2::setDir(int en){
  if(en>0){  //forward
      digitalWrite(_pin1,HIGH);
      digitalWrite(_pin2,LOW);
  }else if(en<0){  //back up
      digitalWrite(_pin2,HIGH);
      digitalWrite(_pin1,LOW);
  }else{  //stop
      digitalWrite(_pin1,LOW);
      digitalWrite(_pin2,LOW);
  }
   Serial.print("{{");
  Serial.print(_pin1);
  Serial.print(",");
  Serial.print(_pin2);
    Serial.print(",");
  Serial.print(en);
   Serial.print(",");
  Serial.print(_en_pin);
  Serial.print("}}");
}
