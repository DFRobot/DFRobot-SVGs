/**************************************************************************/
/*!
 	BMP180 barometric pressure Sensor library
 	Copyright (C) DFRobot - www.dfrobot.com
        Created by Gavin
 */
/**************************************************************************/

#ifndef _BMP180_h
#define _BMP180_h

#include <Arduino.h>
#include <Wire.h>

#define BMP180ADD 0xEE>>1  // I2C address of BMP180  

//write is (0xEE)     read is (0xEF)       

class BMP180 {
	private:
		unsigned char OSS;                            
		/**********************MSB      LSB******/
		int ac1;           // 0xAA     0xAB
		int ac2;           // 0xAC     0xAD
		int ac3;           // 0xAE     0xAE
		unsigned int ac4;  // 0xB0     0xB1
		unsigned int ac5;  // 0xB2     0xB3
		unsigned int ac6;  // 0xB4     0xB5
		int b1;            // 0xB6     0xB7
		int b2;            // 0xB8     0xB9
		int mb;            // 0xBA     0xBB
		int mc;            // 0xBC     0xBD
		int md;            // 0xBE     0xBF
		float temperature;  
		double pressure;   
		double pressure2;
		long b5;          
		double altitude;  

		/*** Read 1 bytes from the BMP180  ***/
		int16_t read (unsigned char address); 
	public:
		/** calculate centure **/
		void calculate(); 

		/**BMP180 satrt program**/
		void init (int theOss);

		/***BMP180 temperature Calculate***/
		int16_t ReadTemperature_1 (unsigned int ut);
		int16_t ReadTemperature();

		/***BMP180 pressure Calculate***/

		int32_t ReadPressure_1 (unsigned long up);
		int32_t ReadPressure ();

		double ReadAltitude ();
		/*** Read 2 bytes from the BMP180 ***/
		int16_t readDate(unsigned char address); 

		/*** read uncompensated temperature value ***/
		uint32_t readUT(); 

		/*** Read uncompensated pressure value from BMP180 ***/
		uint32_t readUP(); 

};

#endif
