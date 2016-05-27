#include "GoBLE.h"
#include <Arduino.h>

_GoBLE Goble;

/*
 * The following constants tell, for each accelerometer
 * axis, which values are returned when the axis measures
 * zero acceleration.
 */
 
_GoBLE::_GoBLE() {
}

void _GoBLE::begin() {
  Serial.begin(115200);
  initRecvDataPack();
  
  _joystickX = 127;
  _joystickY = 127;
  for (int i = 0; i < MAXBUTTONID; i++) {
    _button[i] = RELEASED;
  }
  
  for (int i = 0; i < 20; i++) bleQueue.push(0x00);
  for (int i = 0; i < 20; i++) bleQueue.pop();
  
  
}

void _GoBLE::begin(unsigned int baudrate) {
  Serial.begin(baudrate);
  initRecvDataPack();
  
  _joystickX = 127;
  _joystickY = 127;
  for (int i = 0; i < MAXBUTTONID; i++) {
    _button[i] = RELEASED;
  }
}

boolean _GoBLE::available() {
  /*
  function introduction:
  	* push the new valid data to the data buffer package
  	* throw away the invalid byte
  	* parse the data package when the command length is matching the protocol
  */

  if (Serial.available())  bleDataReceiver();

  if (DEBUGDATARAW) {
    Serial.println("GoBLE availalbe -> new data package!");
    for (int i = 0; i < rDataPack.commandLength; i++) {
      Serial.print(bleQueue.pop(), HEX);
    }
    Serial.println();
  }
  
  if (DEBUGPARSER) {
    Serial.print("GoBLE availalbe -> bleQueue Counter: ");
    Serial.print(bleQueue.count());
    Serial.println();
  }

  if (rDataPack.commandFlag && bleQueue.count() == rDataPack.commandLength) {
    
    rDataPack.parseState = bleDataPackageParser();
    
    if(rDataPack.parseState == PARSESUCCESS){
      updateJoystickVal();  
      updateButtonState();
      return true;
    }
  }
  
  return false;
}


int _GoBLE::readJoystickX() {
  return  _joystickX;
}
int _GoBLE::readJoystickY() {
  return  _joystickY;
}

boolean _GoBLE::readSwitchUp() {
  return _button[SWITCH_UP];
}

boolean _GoBLE::readSwitchDown() {
  return _button[SWITCH_DOWN];
}

boolean _GoBLE::readSwitchLeft() {
  return _button[SWITCH_LEFT];
}

boolean _GoBLE::readSwitchRight() {
  return _button[SWITCH_RIGHT];
}

boolean _GoBLE::readSwitchSelect() {
  return _button[SWITCH_SELECT];
}

boolean _GoBLE::readSwitchStart() {
  return _button[SWITCH_START];
}

// Private functions

int _GoBLE::bleDataPackageParser() {
  /*
    0x10  - Parse success
    0x11  - Wrong header charactors
    0x12  - Wrong button number
    0x13  - Check Sum Error
  */
  byte calculateSum = 0;

  rDataPack.header1 = bleQueue.pop(), calculateSum +=  rDataPack.header1;
  rDataPack.header2 = bleQueue.pop(), calculateSum +=  rDataPack.header2;
  
  if(rDataPack.header1 != DEFAULTHEADER1)     return 0x11;
  if(rDataPack.header2 != DEFAULTHEADER2)     return 0x11;
  
  rDataPack.address = bleQueue.pop(), calculateSum +=  rDataPack.address;
  
  rDataPack.latestDigitalButtonNumber = rDataPack.digitalButtonNumber;
  rDataPack.digitalButtonNumber = bleQueue.pop(), calculateSum +=  rDataPack.digitalButtonNumber;

  int digitalButtonLength = rDataPack.digitalButtonNumber;
  
  
  if (DEBUGCHECKSUM) {
    Serial.print("Parser -> digitalButtonLength: ");
    Serial.println(digitalButtonLength);
  }
  if(digitalButtonLength > MAXBUTTONNUMBER)   return 0x12;
  
  rDataPack.joystickPosition = bleQueue.pop(), calculateSum +=  rDataPack.joystickPosition;

  // read button data package - dynamic button payload length
  for (int buttonPayloadPointer = 0; buttonPayloadPointer < digitalButtonLength; buttonPayloadPointer++) {
    rDataPack.buttonPayload[buttonPayloadPointer] = bleQueue.pop();
    calculateSum +=  rDataPack.buttonPayload[buttonPayloadPointer];
  }
  // read 4 byte joystick data package
  for (int i = 0; i < 4; i++)  rDataPack.joystickPayload[i] = bleQueue.pop(), calculateSum +=  rDataPack.joystickPayload[i];

  rDataPack.checkSum = bleQueue.pop();

  if (DEBUGCHECKSUM) {
    Serial.print("Parser -> sum calculation: ");
    Serial.println(calculateSum);

    Serial.print("Parser -> checkSum byte value: ");
    Serial.println(rDataPack.checkSum);
  }

  // check sum and update the parse state value
  // if the checksum byte is not correct, return 0x12
  
  rDataPack.commandFlag = false;
  
  if (rDataPack.checkSum == calculateSum)     return PARSESUCCESS;
  else                                        return 0x13;
}

void  _GoBLE::bleDataReceiver() {

  byte inputByte = Serial.read();

  if (DEBUGDATARECEIVER) {
    Serial.print("bleDataReceiver -> new data:");
    Serial.println(inputByte, HEX);
  }

  // throw the trash data and restore the useful data to the queue buffer
  if (inputByte == DEFAULTHEADER1 || rDataPack.commandFlag == true) {
    bleQueue.push(inputByte);
    rDataPack.commandFlag = true;

    // auto adjust the command length based on the button command value
    if (bleQueue.count() == PACKBUTTONSIGN) {
      // max button input at one moment should less than 6 buttons
      if (inputByte > 0 && inputByte < MAXBUTTONNUMBER) {

        // default command length + button number
        rDataPack.commandLength = DEFAULTPACKLENGTH + inputByte;
        if (DEBUGDATARECEIVER)	Serial.print("bleDataReceiver -> Command Length:"), Serial.println(rDataPack.commandLength);
      }
      else	rDataPack.commandLength = DEFAULTPACKLENGTH;
    }
  }

}

void  _GoBLE::initRecvDataPack() {
  rDataPack.commandFlag         = false;
  rDataPack.commandLength       = DEFAULTPACKLENGTH;
  rDataPack.parseState          = PARSESUCCESS;
  
  rDataPack.digitalButtonNumber = 0;
  rDataPack.latestDigitalButtonNumber = 0;
}

void _GoBLE::updateJoystickVal(){
  _joystickX = rDataPack.joystickPayload[0];
  _joystickY = rDataPack.joystickPayload[1];
}

void _GoBLE::updateButtonState(){
  
  if (rDataPack.digitalButtonNumber == 0 && rDataPack.latestDigitalButtonNumber != 0) {
    for (int i = 0; i < MAXBUTTONID; i++) {
      if (_button[i] == PRESSED) {
        if (DEBUGUPDATEBUTTON) {
          Serial.print("updateButtonState -> clear Pressed button number: ");
          Serial.println(i);
        }
        _button[i] = RELEASED;
      }
    }
  }

  for (int i = 0; i < rDataPack.digitalButtonNumber; i++)   _button[rDataPack.buttonPayload[i]] = PRESSED;
}



/*
unsigned int _GoBLE::readChannel(byte channel) {

  digitalWrite(MUX_ADDR_PINS[0], (channel & 1) ? HIGH : LOW);
  digitalWrite(MUX_ADDR_PINS[1], (channel & 2) ? HIGH : LOW);
  digitalWrite(MUX_ADDR_PINS[2], (channel & 4) ? HIGH : LOW);
  digitalWrite(MUX_ADDR_PINS[3], (channel & 8) ? HIGH : LOW);
  // workaround to cope with lack of pullup resistor on joystick switch
  if (channel == CH_JOYSTICK_SW) {
    pinMode(MUX_COM_PIN, INPUT_PULLUP);
    unsigned int joystickSwitchState = (digitalRead(MUX_COM_PIN) == HIGH) ? 1023 : 0;
    digitalWrite(MUX_COM_PIN, LOW);
    return joystickSwitchState;
  }
  else
    return analogRead(MUX_COM_PIN);

}


boolean _GoBLE::readButton(byte ch) {
  if (ch >= SWITCH_1 && ch <= SWITCH_5) {
    ch;
  }

  switch(ch) {

  }

  unsigned int val = readChannel(ch);
  return (val > 512) ? HIGH : LOW;
}

boolean _GoBLE::readJoystickButton() {
 if (readChannel(CH_JOYSTICK_SW) == 1023) {
  return HIGH;
 } else if (readChannel(CH_JOYSTICK_SW) == 0) {
  return LOW;
 }
}

*/

