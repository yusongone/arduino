#include <Arduino.h>
#include "wheel.h"

Wheel::Wheel(){
  _var_k=0.7;
  _en=0;
   
}

void Wheel::initLeftWheel(int l_en_pin,int l_a_pin,int l_b_pin){
  _left_en_pin=l_en_pin;
  _left_A_pin=l_a_pin;
  _left_B_pin=l_b_pin;
  
  pinMode(l_en_pin,OUTPUT);
  pinMode(l_a_pin,OUTPUT);
  pinMode(l_b_pin,OUTPUT);
       
}

void Wheel::initRightWheel(int r_en_pin,int r_a_pin,int r_b_pin){
  _right_en_pin=r_en_pin;
  _right_A_pin=r_a_pin;
  _right_B_pin=r_b_pin;
  
  pinMode(r_en_pin,OUTPUT);
  pinMode(r_a_pin,OUTPUT);
  pinMode(r_b_pin,OUTPUT);
}

void Wheel::setEnergy(String wheel,int en){
  //_en=en;
  if(wheel=="left"){
    _l_en=en;
    //Wheel::refresh("left");
   Wheel::setDir("left",_l_en);
  }else if(wheel=="right"){
    _r_en=en;
   // Wheel::refresh("right");
    Wheel::setDir("right",_r_en);
  }
  
 // Wheel::refresh();
}

void Wheel::setCut(int var){
    _var_value=(int)var*_var_k;
     //Wheel::refresh();
}

void Wheel::refresh(String wheel){

    /*
        Serial.print("{{");
        Serial.print("l:");
        Serial.print(_l_en);
        Serial.print(",r:");
        Serial.print(_r_en);
        Serial.print("}}");
    */
    
    analogWrite(_right_en_pin,abs(_r_en)+70);
    analogWrite(_left_en_pin,abs(_l_en)+70);
}

void Wheel::setDir(String wheel,int dir){
   
  if(wheel=="left"){
    if(dir>0){
      digitalWrite(_left_A_pin,HIGH);
      digitalWrite(_left_B_pin,LOW);
    }else if(dir<0){
      digitalWrite(_left_A_pin,LOW);
      digitalWrite(_left_B_pin,HIGH);
    }else{
      digitalWrite(_left_A_pin,LOW);
      digitalWrite(_left_B_pin,LOW);
    }
    
  }else if(wheel="right"){
    if(dir>0){
      digitalWrite(_right_A_pin,HIGH);
      digitalWrite(_right_B_pin,LOW);
    }else if(dir<0){
      digitalWrite(_right_A_pin,LOW);
      digitalWrite(_right_B_pin,HIGH);
    }else{
      digitalWrite(_right_A_pin,LOW);
      digitalWrite(_right_B_pin,LOW);
    }
  }
  analogWrite(_right_en_pin,abs(_r_en)+70);
    analogWrite(_left_en_pin,abs(_l_en)+70);
}
