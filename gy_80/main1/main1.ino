#include <PID_v1.h>

#include "gyro.h"
#include "SerialData.h"


void setup(){
 
  Serial.begin(9600);
  initGy80();
}

void loop(){
/*
  int ADX_data[3];//x,y,z;
  getADXData(ADX_data);
  
  int L3G_data[3];//x,y,z;
  getL3GData(L3G_data);
  
  int HMC_data[3];
  getBMPData(HMC_data);
*/
int c=getPressure();
  Serial.print("------------");
  Serial.println(c);

  delay(1000);
}

