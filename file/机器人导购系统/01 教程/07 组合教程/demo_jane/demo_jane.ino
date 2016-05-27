/****************************************************
 * Avoidance_IRSwitch
 *****************************************************
 * This example is aimed to enable DFMobile to avoid 
 * obstaclesby using digital infrared sensor
 * Created 2015-3-2
 * By Gavin
 ******************************************************/
#include <DFMobile.h>
DFMobile Robot (4,5,7,6); 

#include <Wire.h> 

//LCD I2C library helps user to initiate the LCD status and print the info on the LCD screen 
#include <LiquidCrystal_I2C.h>    //LCD i2c
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//This library helps user to read and setup CO2 sensor
#include "CO2.h"
CO2Sensor CO2ppm;
int CO2Pin = A1;

//BMP180 library assists player to setup and read the barometric and relative altitude 
#include "BMP180.h"
BMP180 bmp;        //    i2c

//Millis function returns the number of milliseconds since the Arduino board began running the current program
long currentMillis=0 ;                  
long previousMillis;
long Interval=6000;
int count=0;       //counting numbers 
int touchPin = 13;

int RightValue;   //Right infrared digital sensor on Pin 8
int MiddleValue;  //Middle infrared digital sensor on Pin 9
int LeftValue;    //Left infrared digital sensor on Pin 10

int LeftLEDPin = 11;
int RightLEDPin = 2;
int BuzzerPin = 3;

void setup () {
  Robot.Direction (LOW, HIGH);
  //  Serial.begin(9600);

  pinMode(touchPin,INPUT);         // touch sensor
  pinMode(LeftLEDPin,OUTPUT);
  pinMode(RightLEDPin,OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();  
  delay(100);
  lcd.setBacklight(0); 

  Wire.begin();
  bmp.init (2);       //bmp i2c    oss=2 times
  LEDState(HIGH,HIGH);  
  delay(1000);
  LEDState(LOW,LOW);

}

void loop () {
  int touchState = digitalRead(touchPin);   
  delay(50);

  if (touchState == HIGH){
    count++;
    previousMillis= millis();
  }
  if(currentMillis - previousMillis < Interval) {
    if (count==1){
      lcd.setBacklight(0); 
    }
    else if (count==2){         //DHT11 Sensor 
      CO2Show();
      lcd.backlight();
    }
    else if(count==3){          //Dust Sensor
      BMP180Show();
      lcd.backlight();
      count=0;
    }
    currentMillis = millis();
  }
  else{
    lcd.setBacklight(0);
  }

  RightValue=digitalRead(8);
  Serial.print (RightValue);

  MiddleValue=digitalRead(9);
  Serial.print (MiddleValue);

  LeftValue=digitalRead(10);
  Serial.println (LeftValue);
  delay(100);

  //If there is no obstacle in front of the robot, then robot move forward
  if(LeftValue == HIGH && MiddleValue == HIGH  && RightValue == HIGH ) {    // no obstacle
    Robot.Speed (150,150);           //move forward
    LEDState(HIGH,HIGH);    
  }

  //If there is some obstacle in front of the robot, then robot back off
  if(LeftValue == LOW && MiddleValue == LOW && RightValue == LOW ) {    //all obstacles
  for(int time=0;time<4;time++){
    TurnOnBuzzer();
  }
    LEDState(LOW,LOW);    
    Robot.Speed (-200,-200);         //back off
    delay(800);
    Robot.Speed (-200,200);          //turn left
    delay(400);
    Robot.Speed (100,100);           //move forward
    LEDState(HIGH,HIGH);  
  }

  if( MiddleValue == LOW){     //obstacle in middle
  for(int time=0;time<4;time++){
    TurnOnBuzzer();
  }
    LEDState(HIGH,HIGH);   
    Robot.Speed (-150,-150);     //back off
    delay(400);
    Robot.Speed (-200,200);      //turn left
    delay(300);
    Robot.Speed (100,100);    //move forward
    LEDState(LOW,LOW);  
  }

  //If there is some obstacle on the left of the robot, then robot back off and turn right.
  if(LeftValue == LOW) {    //obstacle on the left side
  for(int time=0;time<2;time++){
    TurnOnBuzzer();
  }
    LEDState(LOW,LOW); 
    Robot.Speed (-200,-200);    //back off
    delay(400);
    Robot.Speed (200,-200);    //turn right
    delay(250);
    Robot.Speed (100,100);    //move forward
    LEDState(LOW,HIGH);    
  }

  //If there is some obstacle on the right of the robot, then robot back off and turn left.
  if(RightValue == LOW ){       //obstacle on the right side
  for(int time=0;time<2;time++){
    TurnOnBuzzer();
  }
    LEDState(LOW,LOW);
    Robot.Speed (-200,-200);     //back off
    delay(400);
    Robot.Speed (-200,200);     //turn left
    delay(250);
    Robot.Speed (100,100);      //move forward
    LEDState(HIGH,LOW);    
  }
}

void BMP180Show(){
  bmp.calculate ();
  lcd.setCursor(0,0);
  lcd.print("Press(Pa)=");
  lcd.print(bmp.ReadPressure(),1);       //10 hexadecimal
  lcd.setCursor(0,1);
  lcd.print("Altitude(m)=");
  lcd.print(bmp.ReadAltitude(),0);
  delay(100);    
}

void CO2Show(){
  int CO2Value=CO2ppm.Read(CO2Pin); 
  lcd.setCursor(0,0);            //set first colomn and first row display
  lcd.print("CO2(ppm)=");
  if(CO2Value == -1) {
    lcd.print( "<400" );
  } 
  else {
    lcd.print(CO2Value);
  }
  lcd.print("      "); 
  lcd.setCursor(0,1);
  lcd.print("                "); 
  delay(50);    
}

void LEDState(int LeftLED, int RightLED){
  digitalWrite(LeftLEDPin, LeftLED);   
  digitalWrite(RightLEDPin, RightLED); 
}

void TurnOnBuzzer(){
  digitalWrite(BuzzerPin,HIGH); 
  delay(50);
  noTone(BuzzerPin);
  delay(100);

  digitalWrite(BuzzerPin,HIGH); 
  delay(50);
  noTone(BuzzerPin);
  delay(400);       
}











