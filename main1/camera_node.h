#ifndef camera_h
#define camera_h


#include "Arduino.h"
#include "Servo.h"


class CameraNode{
  public:
    CameraNode();
    void initServoPin(int pin);
    void setAngleInterval(int minAngle,int maxAngle);
    void setChangeAngle(int Angle);
  private:
    Servo servo;
    
    int nowAngle;
    
    int minAngle;
    int maxAngle;
};

#endif
