#include "SerialData.h"
#include "relayObj.h"
#include <dht.h>

SerialData s;
Rocker rocker;

#define relay1 4
#define relay2 2
int pinAry[10]={2,4};

void setup(){
  Serial.begin(115200);
	typedef void (*Fun)(String s);
	Fun buttonfun=buttonFun;
	rocker.setButtonFun(buttonfun);
	pinMode(relay1,OUTPUT);
	pinMode(relay2,OUTPUT);
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
		int relayPin=rd.Ary[1].toInt();
		int status=rd.Ary[2].toInt();
		setWrite(relayPin,status);
      break;
  }
}

void setWrite(int relay,int dd){
  digitalWrite(pinAry[relay],dd);
}
