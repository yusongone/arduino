#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor{
  public:
    Motor(int stp,int dir,int en);
    void back(float en);
    void powerToggle(boolean cmd);
    void run();
    void setValue(float en);
  private:
    void changeDir(int dir);
    int pin_stp;
    int pin_dir;
    int pin_en;
    int power;
    boolean pause;
    uint32_t currentTime ;
    boolean runStatus;
};

#endif
/*
int a = 0;     //  gen counter

 pinMode(stp, OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(dir, OUTPUT);
  digitalWrite(EN,LOW);  
  pinMode(stp2, OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(dir2, OUTPUT);
  digitalWrite(EN2,LOW); 
  
 pinMode(stp3, OUTPUT);
  pinMode(EN3,OUTPUT);
  pinMode(dir3, OUTPUT);
  digitalWrite(EN3,LOW); 
  
 pinMode(stp4, OUTPUT);
  pinMode(EN4,OUTPUT);
  pinMode(dir4, OUTPUT);
  digitalWrite(EN4,LOW);  
  
  
      digitalWrite(dir, LOW);
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, HIGH);
    digitalWrite(dir4, HIGH);
    digitalWrite(stp, HIGH);  
    digitalWrite(stp2, HIGH);
     digitalWrite(stp3, HIGH);  
    digitalWrite(stp4, HIGH);
    delayMicroseconds(100);              
    digitalWrite(stp, LOW); 
   digitalWrite(stp2, LOW); 
   digitalWrite(stp3, LOW); 
   digitalWrite(stp4, LOW);
    delayMicroseconds(100);
    */
