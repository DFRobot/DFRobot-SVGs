#include <Metro.h>
#include "GoBLE.h"

int joystickX, joystickY;
int buttonState[6];

void setup(){
  Goble.begin();
  Serial.begin(115200);
}

void loop() {  
  if(Goble.available()){
    joystickX = Goble.readJoystickX();
    joystickY = Goble.readJoystickY();
    
    buttonState[SWITCH_UP]     = Goble.readSwitchUp();
    buttonState[SWITCH_DOWN]   = Goble.readSwitchDown();
    buttonState[SWITCH_LEFT]   = Goble.readSwitchLeft();
    buttonState[SWITCH_RIGHT]  = Goble.readSwitchRight();
    buttonState[SWITCH_SELECT] = Goble.readSwitchSelect();
    buttonState[SWITCH_START]  = Goble.readSwitchStart();
    
    Serial.print("Joystick Value: ");
    Serial.print(joystickX);
    Serial.print("  ");
    Serial.println(joystickY);
    
    for (int i = 1; i < 7; i++) {
      Serial.print("Button ID: ");
      Serial.print(i);
      Serial.print("\t State: ");
      if (buttonState[i] == PRESSED)   Serial.println("Pressed!");
      if (buttonState[i] == RELEASED)  Serial.println("Released!");
    }
    
  }
}

