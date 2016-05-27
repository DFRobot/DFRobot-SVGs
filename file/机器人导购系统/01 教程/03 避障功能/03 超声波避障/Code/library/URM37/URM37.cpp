/**************************************************************************/
/*!
  @file     urm37.cpp
  urm37 library
  Copyright (C) DFRobot - www.dfrobot.com
 */
/**************************************************************************/


#include <Arduino.h>
#include "URM37.h"


double ultrasonic::Init (int echoPin, int trigPin){
	_echoPin = echoPin;
	_trigPin = trigPin;
	pinMode (_echoPin, INPUT);
	pinMode (_trigPin, OUTPUT);
}

double ultrasonic::Distance (){

	digitalWrite(_trigPin, LOW);
	digitalWrite(_trigPin, HIGH);               // reading Pin PWM will output pulses    

	double distance=pulseIn(_echoPin, LOW);    
	if(distance>=45000)                 // the reading is invalid.
	{
		distance=45000/50;
		return distance;
	}
	else{
		distance=(distance/50);         // every 50us low level stands for 1cm

		return distance;
	}
}

