#include "rc.h"

Wheel wheel_l(7,6);
Wheel wheel_r(8,5);

int mid=1508;

int ch1_val=mid;
int ch2_val=mid;

int old_ch1=ch1_val;
int old_ch2=ch2_val;

int speed_l=0;
int speed_r=0;

void parse(){
  if(abs(ch1_val-old_ch1)<6){
    ch1_val=old_ch1;
  }
  old_ch1=ch1_val;
  int val=ch1_val-mid;
  speed_l=abs((float)val/506)*254;
  speed_r=speed_l;

  if(abs(ch2_val-old_ch2)<6){
    ch2_val=old_ch2;
  }
  old_ch2=ch2_val;


  int val2=ch2_val-mid;
  speed_l+=(float)val2/600*254;
  speed_r-=(float)val2/600*254;

  speed_l=abs(speed_l)<254?speed_l:254*(speed_l>0);
  speed_r=abs(speed_r)<254?speed_r:254*(speed_r>0);
  
  int dir=val>10?1:-1;
  wheel_l.dir(speed_l*dir);
  wheel_l.speed(speed_l);
  wheel_r.dir(speed_r*dir);
  wheel_r.speed(speed_r);

  Serial.print(val);
  Serial.print("*");
  Serial.print(speed_l);
  Serial.print("*");
  Serial.println(speed_r);
}

void getRC(){
  ch1_val=pulseIn(2,HIGH,2100*10);  
  ch2_val=pulseIn(3,HIGH,2100*10);  

  ch1_val=ch1_val?ch1_val:1508;
  ch2_val=ch2_val?ch2_val:1508;

  parse();
}

void initRC(){
  wheel_l.init();
  wheel_r.init();
}
