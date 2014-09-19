#include <Servo.h>

#include <Wire.h>
#include "mpu6050.h"
#include "kalm.h"

/* IMU Data */
int16_t accX, accY, accZ;
int16_t tempRaw;
int16_t gyroX, gyroY, gyroZ;
KalmanFilter kalmanFilter;

double temp; // Temperature

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
Mpu6050 mpu;
double angle;
Servo myservo;
long oldTime=0;
void setup() { 
 Serial.begin(9600); 
 myservo.attach(9);
 mpu.init();
}
float i=0;
void loop() {
  /* Update all the values */  
 
  int Array[14];
  mpu.getMpuData(Array);
  accX=Array[0];
  accY=Array[1];
  accZ=Array[2];
  
  tempRaw = Array[3];  
  gyroX = Array[4];
  gyroY = Array[5];
  gyroZ = Array[6];
  /*
  while(i2cRead(0x3B,i2cData,14));
  accX = ((i2cData[0] << 8) | i2cData[1]);
  accY = ((i2cData[2] << 8) | i2cData[3]);
  accZ = ((i2cData[4] << 8) | i2cData[5]);
  tempRaw = ((i2cData[6] << 8) | i2cData[7]);  
  gyroX = ((i2cData[8] << 8) | i2cData[9]);
  gyroY = ((i2cData[10] << 8) | i2cData[11]);
  gyroZ = ((i2cData[12] << 8) | i2cData[13]);
  */
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We then convert it to 0 to 2π and then from radians to degrees
  // Note: if we only consider the angle, we don't need transform the raw acceleration to its physical meaning
  // The formulation transforming to its physical meaning (Unit: g): accX = accX/16384.00;

  int Ax=-int(atan(float(accX)/float(accZ))*RAD_TO_DEG);//x方向角度
  //double omegaX=(gyroY)*0.00763358;
  double omegaX=(double)gyroY/131.0;
  double a;
  double b;
   long now=millis();
  float dt=float(now-oldTime)/1000;
   kalmanFilter.getValue(double(Ax),omegaX,double(dt),a,b);
  temp = ((double)tempRaw + 12412.0) / 340.0;
  
   myservo.write(fmap(a,-90,90,0,180));
 // myservo.write(map());
  
  /* Print Data */
  Serial.print("{{Rocker:[");
  Serial.print(fmap(a,-90.0,90.0,0,180.0));
  Serial.print(",");
  Serial.print(omegaX);
  //Serial.print(L3G_data[1]);
  Serial.print(",");
  Serial.print(a);
  Serial.print("]}}");
  /*
  Serial.print(accX);Serial.print(",");
  Serial.print(accY);Serial.print(",");
  Serial.print(accZ);Serial.print(",");
  
  //Serial.print(gyroX);Serial.print(",");
  //Serial.print(gyroY);Serial.print(",");
  //Serial.print(gyroZ);Serial.print(",");
  Serial.print(gyroXrate);Serial.print(",");
  Serial.print(gyroYrate); Serial.print(",");
  
  Serial.print(accXangle);Serial.print(",");
  Serial.print(gyroXangle);Serial.print(",");
  //Serial.print(compAngleX);Serial.print(",");
  //Serial.print(kalAngleX);Serial.print(",");
  
  //Serial.print(",");
  
  Serial.print(accYangle);Serial.print(",");
  Serial.print(gyroYangle);Serial.print(",");
  //Serial.print(compAngleY); Serial.print(",");
  //Serial.print(kalAngleY); //Serial.print(",");
  
  //Serial.print(temp);Serial.print(",");
  
  Serial.print("\r\n");
  */
  oldTime=now;
  delay(1);
}
float fmap(long x, float in_min, float in_max, float out_min, float out_max)
 {
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 }






