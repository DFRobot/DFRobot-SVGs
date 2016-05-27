#ifndef GOBLE_H_
#define GOBLE_H_

#include <Arduino.h>
#include "QueueArray.h"

/**************** Debugger Configuration ******************/

#define DEBUGDATARECEIVER	false
#define DEBUGDATARAW     	false
#define DEBUGPARSER      	false
#define DEBUGCHECKSUM           false
#define DEBUGUPDATEBUTTON	false

const byte SWITCH_1       = 1;
const byte SWITCH_2       = 2;
const byte SWITCH_3       = 3;
const byte SWITCH_4       = 4;
const byte SWITCH_5       = 5;
const byte SWITCH_6       = 6;

const byte SWITCH_UP    	= SWITCH_1;
const byte SWITCH_RIGHT 	= SWITCH_2;
const byte SWITCH_DOWN  	= SWITCH_3;
const byte SWITCH_LEFT 		= SWITCH_4;

const byte SWITCH_SELECT 	= SWITCH_5;
const byte SWITCH_START 	= SWITCH_6;

/*
 * These constants can be use for comparison with the value returned
 * by the readButton() method.
 */
const boolean PRESSED   = LOW;
const boolean RELEASED  = HIGH;



/* 
 * Data structure for the command buffer 
 *
 */
 
// Package protocol configuration
#define PACKHEADER	        1
#define PACKHEADER2		2
#define PACKADDRESS		3
#define PACKBUTTONSIGN		4
#define PACKJOYSTICKSIGN	5
#define PACKPAYLOAD             6


#define DEFAULTHEADER1          0x55
#define DEFAULTHEADER2          0xAA
#define DEFAULTADDRESS          0x11
#define DEFAULTPACKLENGTH	10

#define MAXBUTTONNUMBER         6 
#define MAXBUTTONID             7

#define PARSESUCCESS            0x10
 
//DL package
#pragma pack(1)
typedef struct
{
  byte  header1;          // 0x55
  byte  header2;          // 0xAA
  byte  address;          // 0x11
  
  byte  latestDigitalButtonNumber;
  byte  digitalButtonNumber;
  
  byte  joystickPosition;
  byte	buttonPayload[MAXBUTTONNUMBER];
  byte	joystickPayload[4];
  byte  checkSum;

  byte  commandLength;
  byte  parseState;
  boolean commandFlag;
} sDataLink;
#pragma pack()

class _GoBLE {
    
public:
  _GoBLE();
  
  void begin();
  void begin(unsigned int baudrate);
  
  boolean available();

  int readJoystickX();
  int readJoystickY();
  /*
   * Reads the current state of a button. It will return
   * LOW if the button is pressed, and HIGH otherwise.
   */
  boolean readSwitchUp();
  boolean readSwitchDown();
  boolean readSwitchLeft();
  boolean readSwitchRight();
  boolean readSwitchSelect();
  boolean readSwitchStart();
  
private:

  sDataLink rDataPack;
  // create a queue of characters.
  QueueArray <byte> bleQueue;
  
  int _joystickX,_joystickY;
  int _button[MAXBUTTONID];

  void updateJoystickVal();
  void updateButtonState();

  void initRecvDataPack();
  int bleDataPackageParser();
  void bleDataReceiver();

};

extern _GoBLE Goble;

#endif // GOBLE_H_
