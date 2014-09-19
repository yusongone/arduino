/*
 * KalmanFilter.h
 * Non-original
 * Author: x2d 
 * Copyright (c) 2012 China
 *
 */
#include <Arduino.h>

#ifndef kalm_h
#define kalm_h

class KalmanFilter
{
  public:
  KalmanFilter();
  
  /*
    卡尔曼融合计算
    angle_m: 加速度计测量并通过atan2(ax,ay)方法计算得到的角度（弧度值）
    gyro_m:陀螺仪测量的角速度值（弧度值）
    dt:采样时间(s)
    outAngle:卡尔曼融合计算出的角度（弧度值）
    outAngleDot:卡尔曼融合计算出的角速度（弧度值）
  */
  void getValue(double angle_m, double gyro_m, double dt, double &outAngle, double &outAngleDot);
  
  private:
  double C_0, Q_angle, Q_gyro, R_angle;
  double q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
  double angle, angle_dot;
  double P[2][2];
  double Pdot[4];
};
#endif
