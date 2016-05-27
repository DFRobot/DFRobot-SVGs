#include <Wire.h>

//LCD I2C library helps user to initiate the LCD status and print the info on the LCD screen 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int MQ5Pin = A6;  // LX1972 Sensor Pin

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
}

void loop(){
  int touchState =digitalRead(touchPin);        
  if (touchState == HIGH){
    count++;
    previousMillis= millis();
  }
  if(currentMillis - previousMillis < Interval) {
    if (count==1){                      //startup black screen
      lcd.setBacklight(0); 
    }
    else if (count==2){                // when button is touched by two times
      lcd.backlight();               // CO2 shows info on screen 
      MQ5Show();
      count=0;
    }
    currentMillis = millis();
  }
  else{
    lcd.setBacklight(0);             // when there is a long period no usage, the syetem auto runs into sleep mode 
  }   
}

void MQ5Show(){
  int MQ5Value = analogRead(MQ5Pin);      //connect sensor pin
  lcd.setCursor(0,0);        //set first colomn and first row display
  lcd.print("gasValue=");   
  lcd.print(MQ5Value);    //print the value to serial    
  lcd.print("      ");     
  lcd.setCursor(0,1);
  lcd.print("                ");    
  delay(100);  
}

