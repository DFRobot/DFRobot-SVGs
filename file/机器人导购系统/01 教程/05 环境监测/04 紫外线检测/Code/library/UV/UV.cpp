/**************************************************************************/
/*!
 	UV Sensor library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
#include "UV.h"
 
void  ultraviolet::Init(int AnalogPin){
  _AnalogPin=AnalogPin;
  pinMode(_AnalogPin,INPUT);
};

double ultraviolet::Read(){
  int uvLevel = analogRead(_AnalogPin);
  float outputVoltage = 5.0 * uvLevel/1024;
  float uvIntensity = (outputVoltage - 0.99) * (15.0 - 0.0) / (2.9 - 0.99) + 0.0;
  return (uvIntensity);
};
















