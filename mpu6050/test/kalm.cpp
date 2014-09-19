/*
 * KalmanFilter.cpp
 * Non-original
 * Author: x2d 
 * Copyright (c) 2012 China
 *
 */
 
 #include "kalm.h"
 
 KalmanFilter::KalmanFilter()
 {
   C_0 = 1.0f;
   Q_angle = 0.001f;
   Q_gyro = 0.003f;
   R_angle = 0.5f;
   q_bias = angle_err = PCt_0 = PCt_1 = E = K_0 = K_1 = t_0 = t_1 = 0.0f;
   angle = angle_dot = 0.0f;
   P[0][0] = 1.0f;
   P[0][1] = 0.0f;
   P[1][0] = 0.0f;
   P[1][1] = 1.0f;
   Pdot[0] = 0.0f;
   Pdot[1] = 0.0f;
   Pdot[2] = 0.0f;
   Pdot[3] = 0.0f;
 }
 
void  KalmanFilter::getValue(double angle_m, double gyro_m, double dt, double &outAngle, double &outAngleDot)
{
/*
  Serial.print("angle_m = ");
  Serial.print(angle_m);
  Serial.print(";");
  Serial.print("gyro_m = ");
  Serial.print(gyro_m);
  Serial.print(";");
*/

  angle+=(gyro_m-q_bias) * dt;
  angle_err = angle_m - angle;
  Pdot[0] = Q_angle - P[0][1] - P[1][0];
  Pdot[1] = -P[1][1];
  Pdot[2] = -P[1][1];
  Pdot[3] = Q_gyro;
  P[0][0] += Pdot[0] * dt;
  P[0][1] += Pdot[1] * dt;
  P[1][0] += Pdot[2] * dt;
  P[1][1] += Pdot[3] * dt;
  PCt_0 = C_0 * P[0][0];
  PCt_1 = C_0 * P[1][0];
  E = R_angle + C_0 * PCt_0;
  K_0 = PCt_0 / E;
  K_1 = PCt_1 / E;
  t_0 = PCt_0;
  t_1 = C_0 * P[0][1];
  P[0][0] -= K_0 * t_0;
  P[0][1] -= K_0 * t_1;
  P[1][0] -= K_1 * t_0;
  P[1][1] -= K_1 * t_1;
  angle += K_0 * angle_err;
  q_bias += K_1 * angle_err;
  angle_dot = gyro_m-q_bias;
  
  outAngle = angle;
  outAngleDot = angle_dot;
/*
  Serial.print("angle = ");
  Serial.print(angle);
  Serial.print(";");
  Serial.print("angle_dot = ");
  Serial.print(angle_dot);
  Serial.print(";");
*/
}
