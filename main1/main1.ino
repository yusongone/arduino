#include "SerialData.h"
#include "wheel_2.h"
#include "camera_node.h"

SerialData s;
Rocker rocker;
Wheel2 wheelL;
Wheel2 wheelR;
CameraNode cn_level;
CameraNode cn_vertical;

int Drive_power_pin=12;

int Left_EN=3,  LeftA_pin=2,  LeftB_pin=4;
int Right_EN=6,   RightA_pin=7,  RightB_pin=5;
int ledA_pin=8;
int CameraA_pin=10,CameraB_pin=9;

boolean ledA_status=false;

void setup(){
  Serial.begin(57600);
  wheelL.initPin(Left_EN,LeftA_pin,LeftB_pin);
  wheelR.initPin(Right_EN,RightA_pin,RightB_pin);
  
  cn_level.initServoPin(CameraA_pin);
  cn_level.setAngleInterval(10,250);
  
  cn_vertical.initServoPin(CameraB_pin);
  cn_vertical.setAngleInterval(10,250);
  
  pinMode(Drive_power_pin,OUTPUT);
  digitalWrite(Drive_power_pin,HIGH);
  
  s.setSendLimitString("{{","}}");
  s.setReadLimitString("{{","}}");
  
  typedef void (*Fun)(String s);
  Fun rockerfun=rockerFun;
  rocker.setRockerFun(rockerfun);
  
  Fun buttonfun=buttonFun;
  rocker.setButtonFun(buttonfun);
}
  
void loop(){
  String c=s.readData();  
  if(c!=""){
    rocker.toCommand(c);
    //s.sendData(c);
  }
}

void buttonFun(String s){
  RockerData rd=rocker.parseAry(s);
  switch(rd.Ary[0].toInt()){
    case 1://button A
        triggerLed();        
      break;
  }
}

void triggerLed(){
  if(ledA_status){
    digitalWrite(ledA_pin,LOW);
    s.sendData("ledA closed");
    ledA_status=false;
  }else{
    digitalWrite(ledA_pin,HIGH);
    s.sendData("ledA opend");
    ledA_status=true;
  }
}

void rockerFun(String s){
  RockerData rd=rocker.parseAry(s);
  
  switch(rd.Ary[0].toInt()){
    case 1:// rockerA
      leftRocker(rd);
      break;
    case 2:
      rightRocker(rd);
      break;
    case 3:
      cameraRocker(rd);
      break;
  }
}

void leftRocker(RockerData rd){
   String str=rd.Ary[2];
      int en=str.toInt();
        wheelL.setEnergy(en);
}

void rightRocker(RockerData rd){
   String str=rd.Ary[2];
      int en=str.toInt();
      wheelR.setEnergy(en);
}

void cameraRocker(RockerData rd){
    int x_differ=rd.Ary[1].toInt();
    int y_differ=rd.Ary[2].toInt();
    
    cn_level.setChangeAngle(x_differ);
    cn_vertical.setChangeAngle(y_differ);
};




