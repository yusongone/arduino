#ifndef robot_h
#define robot_h

#include "Arduino.h"
#include "Motor.h"

#define STP1_PIN  A0 //connect pin 13 to step
#define DIR1  A1  // connect pin 12 to dir
#define EN1 38
#define STP2_PIN  26 
#define DIR2  28  
#define EN2 24
#define STP3_PIN  A6
#define DIR3  A7
#define EN3 A2
#define STP4_PIN  36
#define DIR4  34
#define EN4 30

#define MAX_RAW 2000
#define MIN_RAW 1000

void initRobot();
void robotRun();
void robotLoop();
void robotUpdateCMD(int ROLL,int PITCH,int YAW,int THROTTLE);

#endif
