#include <UTFT.h>
UTFT myGLCD(ILI9325C,19,18,17,16);
//UTFT myGLCD(ILI9325C,A2,A3,A4,A5);
extern uint8_t SmallFont[];

void setup(){
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setColor(100,100,100);
  myGLCD.setBackColor(50,0,0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("hello word",10,10);
  //myGLCD.fillScr(50,50,50);
  
}
void loop(){
  //myGLCD.clrScr();
  
  delay(100);
}


