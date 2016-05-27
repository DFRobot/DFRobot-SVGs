/**************************************************************************/
/*!
 	Sharp Dust library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
#include "SharpDustSensor.h"

void  airsensor::Init(int AnalogPin,int DigitalPin){
  _AnalogPin=AnalogPin;
  _DigitalPin=DigitalPin;
  pinMode(_AnalogPin,INPUT);
  pinMode(_DigitalPin,OUTPUT);
};

double airsensor::Read(){
  digitalWrite(_DigitalPin,LOW);
  delayMicroseconds(280);
  double voMeasured= analogRead(_AnalogPin);
  delayMicroseconds (40);
  digitalWrite(_DigitalPin,HIGH);
  delayMicroseconds (9680);
  double calcVoltage = voMeasured * (5.0 / 1024.0);
  double dustDensity = 0.17 * calcVoltage - 0.1;
  return (dustDensity);
};





