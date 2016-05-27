/**************************************************************************/
/*!
  Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/


#include <Arduino.h>
class ultrasonic {
	private:
		int _echoPin;
		int _trigPin;
	public:
		double Init (int echoPin, int trigPin);
		double Distance ();
};
