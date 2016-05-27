/**************************************************************************/
/*!
 	UV Sensor library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
class ultraviolet{
private:
  int _AnalogPin;
public:
  void Init (int AnalogPin);
  double Read ();
};
