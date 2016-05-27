#include <Wire.h>

//LCD I2C library helps user to initiate the LCD status and print the info on the LCD screen 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//UV library helps user to setup UV sensor and read the value.
#include "UV.h"
ultraviolet UV ;
int UVPin = A2;

//Millis function returns the number of milliseconds since the Arduino board began running the current program
long currentMillis=0 ;                  
long previousMillis;
long Interval=4000;
int count=0;       //counting numbers
int touchPin = 13;

void setup(){
  pinMode(touchPin,INPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  delay(100);
  lcd.setBacklight(0); 
  
  UV.Init(UVPin);                  // initialize the UV Sensor
}

void loop(){
  int touchState =digitalRead(touchPin);        
  if (touchState == HIGH) {
    count++;
    previousMillis= millis();
  }
  if(currentMillis - previousMillis < Interval) {
    if (count==1){                      //startup black screen
      lcd.setBacklight(0); 
    }
    else if (count==2){                // when button is touched by two times
      lcd.backlight();               // CO2 shows info on screen 
      UVShow();
      count=0;
    }
    currentMillis = millis();
  }
  else{
    lcd.setBacklight(0);             // when there is a long period no usage, the syetem auto runs into sleep mode 
  }   
}

void UVShow(){
  double UVValue=UV.Read ();
  lcd.setCursor(0,0);            //set first colomn and first row display  
  lcd.print("UV(mW/cm^2)=");
  lcd.print(UVValue);
  lcd.print("      ");     
  lcd.setCursor(0,1);
  lcd.print("                ");      
  delay(100);  
}


