/**************************************************************************/
/*!
 	CO2 library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
class CO2Sensor {
private:
  int _AnalogPin;
public:
  int Read (int AnalogPin);
};

