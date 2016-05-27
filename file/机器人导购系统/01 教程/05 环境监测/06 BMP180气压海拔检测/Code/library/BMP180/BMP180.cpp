/**************************************************************************/
/*!
 	BMP180 barometric pressure Sensor library
 	Copyright (C) DFRobot - www.dfrobot.com
        Created by Gavin
 */
/**************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include "BMP180.h"

/** calculate centure **/
void BMP180::calculate() {
	temperature = ReadTemperature_1 (readUT());
	temperature = temperature*0.1;
	pressure = ReadPressure_1 (readUP());
	pressure2 = pressure/101325;
	pressure2 = pow(pressure2,0.19029496);
	altitude = 44330*(1-pressure2);                            //altitude = 44330*(1-(pressure/101325)^0.19029496);
}

//
double BMP180::ReadAltitude () {
	return altitude;
}

/**BMP180 satrt program**/
void BMP180::init (int theOss)
{                     /*MSB*/
	OSS = theOss;                              //oversampling
	ac1 = readDate(0xAA);                      //get full data
	ac2 = readDate(0xAC);  
	ac3 = readDate(0xAE);  
	ac4 = readDate(0xB0);  
	ac5 = readDate(0xB2);  
	ac6 = readDate(0xB4);  
	b1  = readDate(0xB6);  
	b2  = readDate(0xB8);  
	mb  = readDate(0xBA);  
	mc  = readDate(0xBC);  
	md  = readDate(0xBE);
}

/***BMP180 temperature Calculate***/
int16_t BMP180::ReadTemperature_1 (unsigned int ut)
{
	long x1, x2;
	x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;  //x1=((ut-ac6)*ac5)/(2^15)
	x2 = ((long)mc << 11)/(x1 + md);                //x2=(mc*2^11)/(x1+md)
	b5 = x1 + x2;                                   //b5=x1+x2
	return ((b5 + 8)>>4);                           //t=(b5+8)/(2^4)
}

int16_t BMP180::ReadTemperature () {
	return ReadTemperature_1 (readUT())*0.1;
}

/***BMP180 pressure Calculate***/

int32_t BMP180::ReadPressure_1 (unsigned long up) {
	long x1, x2, x3, b3, b6, p;
	unsigned long b4, b7;

	b6 = b5 - 4000;

	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;

	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;

	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
		p = (b7<<1)/b4;
	else
		p = (b7/b4)<<1;

	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;

	return p;
}

int32_t BMP180::ReadPressure ( ) {
	return pressure;
}

/*** Read 1 bytes from the BMP180  ***/

int16_t BMP180::read(unsigned char address) {
	unsigned char data;

	Wire.beginTransmission(BMP180ADD);
	Wire.write(address);
	Wire.endTransmission();

	Wire.requestFrom(BMP180ADD, 1);
	while(!Wire.available());

	return Wire.read();
}

/*** Read 2 bytes from the BMP180 ***/
int16_t BMP180::readDate(unsigned char address) {
	unsigned char msb, lsb;
	Wire.beginTransmission(BMP180ADD);
	Wire.write(address);
	Wire.endTransmission();
	Wire.requestFrom(BMP180ADD, 2);
	while(Wire.available()<2);
	msb = Wire.read();
	lsb = Wire.read();
	return (int) msb<<8 | lsb;
}

/*** read uncompensated temperature value ***/
uint32_t BMP180::readUT() {
	uint16_t ut;
	Wire.beginTransmission(BMP180ADD);
	Wire.write(0xF4);                       // Write 0x2E into Register 0xF4
	Wire.write(0x2E);                       // This requests a temperature reading
	Wire.endTransmission();  
	delay(5);                               // Wait at least 4.5ms
	ut = readDate(0xF6);               // read MSB from 0xF6 read LSB from (16 bit)
	return ut;
}

/*** Read uncompensated pressure value from BMP180 ***/
uint32_t BMP180::readUP() {
	unsigned char msb, lsb, xlsb;
	unsigned long up = 0;

	Wire.beginTransmission(BMP180ADD);
	Wire.write(0xF4);                        // Write 0x34+(OSS<<6) into register 0xF4
	Wire.write(0x34 + (OSS<<6));             // 0x34+oss*64
	Wire.endTransmission(); 
	delay(2 + (3<<OSS));                     // Wait for conversion, delay time dependent on OSS

	Wire.beginTransmission(BMP180ADD);
	Wire.write(0xF6);                        // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	Wire.endTransmission();

	Wire.requestFrom(BMP180ADD, 3); 
	while(Wire.available() < 3);             // Wait for data to become available
	msb = Wire.read();
	lsb = Wire.read();
	xlsb = Wire.read();
	up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);//16 to 19 bit
	return up;
}

