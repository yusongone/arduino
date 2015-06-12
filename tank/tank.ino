#include "rc.h"



void setup(){
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);

  pinMode(2,INPUT);
  digitalWrite(2,HIGH);

  pinMode(3,INPUT);
  digitalWrite(3,HIGH);
  initRC();

  Serial.begin(9600);
}

void loop(){
  getRC();
}
