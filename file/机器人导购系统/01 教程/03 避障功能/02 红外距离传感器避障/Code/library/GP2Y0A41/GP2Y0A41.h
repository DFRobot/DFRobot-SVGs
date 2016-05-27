/**************************************************************************/
/*!
 	GP2Y0A41SKOF library
 	Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/
#include <Arduino.h>
class InfraredSensor{
         private:
                 int _Pin;
         public:
                 double Distance (int Pin);
};
