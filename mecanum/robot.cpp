#include "robot.h"

Motor F_L(STP1_PIN,DIR1,EN1);

Motor F_R(STP2_PIN,DIR2,EN2);
Motor B_L(STP3_PIN,DIR3,EN3);
Motor B_R(STP4_PIN,DIR4,EN4);
void initRobot(){
  
  F_L.powerToggle(false);
  F_R.powerToggle(false);
  B_L.powerToggle(false);
  B_R.powerToggle(false);
  
}
void robotRun(){
  F_L.powerToggle(true);
  F_R.powerToggle(true);
  B_L.powerToggle(true);
  B_R.powerToggle(true);
}
void robotLoop(){
  B_L.run();
  B_R.run();
  F_L.run();
  F_R.run();
}
void robotUpdateCMD(int ROLL,int PITCH,int YAW,int THROTTLE){
    ROLL-MIN_RAW/(MAX_RAW)*100;
};
