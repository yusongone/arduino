#include "Protocol.h"

Protocol p;

void setup(){
  Serial.begin(115200);
}

void loop(){
  
   Serial.print(p.geta());
delay(100);
}
