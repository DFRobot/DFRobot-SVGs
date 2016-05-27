/**************************************************************************/
/*!
 	Sharp Dust Sensor library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
class airsensor{
private:
  int _AnalogPin;
  int _DigitalPin;
public:
  void Init (int AnalogPin,int DigitalPin);
  double Read ();
};


