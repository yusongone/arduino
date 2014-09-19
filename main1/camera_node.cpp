#include <Arduino.h>
#include "camera_node.h"

CameraNode::CameraNode(){
  nowAngle=10;
  minAngle=0;
  maxAngle=200;
}

void CameraNode::initServoPin(int pin){
  servo.attach(pin);
}

void CameraNode::setAngleInterval(int _minAngle,int _maxAngle){
    minAngle=_minAngle;
    maxAngle=_maxAngle;
}

void CameraNode::setChangeAngle(int angle){
    int tempAngle;
    int toSetAngle=nowAngle+angle;
    if(toSetAngle>maxAngle){
      tempAngle=maxAngle;
    }else if(toSetAngle<minAngle){
      tempAngle=minAngle;
    }else{
      tempAngle=toSetAngle;
    }
    Serial.print("{{");
    Serial.print(angle);
    Serial.print(",");
    Serial.print(tempAngle);
    Serial.print("}}");
    nowAngle=tempAngle;
    servo.write(tempAngle);
}
