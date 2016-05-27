#include <Wire.h>

//LCD I2C library helps user to initiate the LCD status and print the info on the LCD screen 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//This library helps user to read and setup dust sensor
#include "SharpDustSensor.h"
airsensor Dust ;
int dustDigitalPin = 12;
int dustAnalogPin = A0;

//Millis function returns the number of milliseconds since the Arduino board began running the current program
long currentMillis=0 ;                  
long previousMillis;
long Interval=4000;
int count=0;       //counting numbers 
int touchPin = 13;

void setup(){
  pinMode(touchPin,INPUT);               // touch sensor
  lcd.init();                      // initialize the lcd 
  lcd.backlight();  
  delay(100);
  lcd.setBacklight(0); 
  
  Dust.Init(dustAnalogPin,dustDigitalPin);                //initialize the dust sensor 
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
      lcd.backlight();
      DustShow();
      count=0;
    }
    currentMillis = millis();
  }
  else{
    lcd.setBacklight(0);             // when there is a long period no usage, the syetem auto runs into sleep mode 
  } 
}     

void DustShow(){
  double DustValue = Dust.Read ();
  lcd.setCursor(0,0);
  lcd.print("Dust(mg/m3)=");
  lcd.print(DustValue); 
  lcd.print("      "); 
  lcd.setCursor(0,1);
  lcd.print("                ");   
  delay(100);    
}


