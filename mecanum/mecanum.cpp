#include "mecanum.h"
#include "robot.h"


void setup() 
{     
  initSerial();
  initRobot();
}


void loop() 
{
  reciveCMD();
  robotLoop();
  //delay(1000);
}
