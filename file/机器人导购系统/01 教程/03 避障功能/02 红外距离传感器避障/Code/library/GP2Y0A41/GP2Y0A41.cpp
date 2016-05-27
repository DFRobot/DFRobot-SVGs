/**************************************************************************/
/*!
 	GP2Y0A41SKOF library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
#include "GP2Y0A41.h"

double  InfraredSensor::Distance(int Pin){
  _Pin=Pin;
  pinMode(_Pin,INPUT);
  int Temp = analogRead (Pin);
  if (Temp < 16) {
    return 16;
  }
  else {
    uint16_t dist = (2076.0 / (Temp - 11.0));
    return (dist);
  }
  return 0;
}



 













