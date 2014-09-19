#include <PID_v1.h>

#include "gyro.h"
#include "SerialData.h"
#include "kalm.h"

Gyro gyro;
long oldTime=0;
double to;
SerialData serialdata;
Rocker rocker;
KalmanFilter kalmanFilter;
double Setpoint,Input,Output;
double P=3.6,I=0.01,D=0.01;
PID myPID(&Input, &Output, &Setpoint,P,I,D, DIRECT);

void setup(){
 
  Serial.begin(9600);
  
  gyro.initGy80();
  Setpoint=9.5;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255); 
  myPID.SetSampleTime(1);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
 
  
  typedef void (*Fun)(String s);
  Fun rockerfun=rockerFun;
  rocker.setRockerFun(rockerfun);
}
void rockerFun(String s){
  RockerData rd=rocker.parseAry(s);
  switch(rd.Ary[0].toInt()){
    case 0:
    P=double(rd.Ary[1].toInt())/100;
    myPID.SetTunings(P,I,D);
    break;  
     case 1:
    I=double(rd.Ary[1].toInt())/100;
    myPID.SetTunings(P,I,D);
    break;
     case 2:
    D=double(rd.Ary[1].toInt())/100;
    myPID.SetTunings(P,I,D);
    break;
}
}

void loop(){
  String c=serialdata.readData();  
  if(c!=""){
    rocker.toCommand(c); //s.sendData(c);
  }
  long now=millis();
  float dt=float(now-oldTime)/1000;
  
  int ADX_data[3];//x,y,z;
  gyro.getADXData(ADX_data);
  int Ax=-int(atan(float(ADX_data[0])/float(ADX_data[2]))*180/3.1415926);//x方向角度
  
  int L3G_data[3];//x,y,z;
  gyro.getL3GData(L3G_data);
  
  int HMC_data[3];
  gyro.getHMCData(HMC_data);
  
  float omegaX=(L3G_data[1]+17)*0.0763358;
  //getValue(double angle_m, double gyro_m, double dt, double &outAngle, double &outAngleDot)
  double a;
  double b;
  kalmanFilter.getValue(double(Ax),double(omegaX),double(dt),a,b);
  Input = a;
  myPID.Compute();
  to+=b;
  
  //Serial.println("aa");
  Output=Output*(1+abs(Output)*0.005);
  double Out1=Output+0;
  double Out2=Output-0;
  if(Out1>0){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }else if(Output<0){
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
  }
  if(Out2>0){
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
  }else if(Output<0){
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
  }
 

  analogWrite(3,abs(Out1));
  analogWrite(9,abs(Out2));
  
  Serial.print("{{Rocker:[");
  Serial.print(Ax);
  Serial.print(",");
  Serial.print(omegaX);
  //Serial.print(L3G_data[1]);
  Serial.print(",");
  Serial.print(a);
  Serial.print("]}}");
  oldTime=now;
  delay(1);
}

