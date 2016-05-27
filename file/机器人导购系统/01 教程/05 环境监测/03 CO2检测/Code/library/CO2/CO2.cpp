/**************************************************************************/
/*!
 	CO2 library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
#include "CO2.h"

int CO2Sensor::Read(int AnalogPin) {
  _AnalogPin=AnalogPin;
  float v=0;
  for (int i=0;i<3;i++) {
    v=v+analogRead(AnalogPin);
    
  }
  float volts = (v/3) *5/1024 ;
  if ((volts/8.5 )>=0.324) {
    return -1;
  } 
  else { 
    return pow(10, ((volts/8.5)-0.324)/(0.020/(2.602-3))+2.602);
  }
}









