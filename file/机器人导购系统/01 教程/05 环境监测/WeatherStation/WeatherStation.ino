#include <Wire.h> 

//LCD I2C library helps user to initiate the LCD status and print the info on the LCD screen 
#include <LiquidCrystal_I2C.h>    //LCD i2c
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//This library helps user to read and setup dht11 sensor
#include <dht11.h>
dht11 DHT;
int DHT11Pin = 3; //  define dht11 pin

//This library helps user to read and setup dust sensor
#include "SharpDustSensor.h"
airsensor Dust ;
int dustDigitalPin = 12;
int dustAnalogPin = A0;

//This library helps user to read and setup CO2 sensor
#include "CO2.h"
CO2Sensor CO2ppm;
int CO2Pin = A1;

//UV library helps user to setup UV sensor and read the value.
#include "UV.h"
ultraviolet UV ;
int UVPin = A2;

int lightPin = A3;  // LX1972 Sensor Pin

//BMP180 library assists player to setup and read the barometric and relative altitude 
#include "BMP180.h"
BMP180 bmp;        //    i2c

int MQ5Pin = A6;  // LX1972 Sensor Pin

//Millis function returns the number of milliseconds since the Arduino board began running the current program
long currentMillis=0 ;                  
long previousMillis;
long Interval=4000;
int count=0;       //counting numbers 
int touchPin = 13;

void setup(){
  pinMode(touchPin,INPUT);         // touch sensor
  lcd.init();                      // initialize the lcd 
  lcd.backlight();  
  delay(100);
  lcd.setBacklight(0); 

  Dust.Init(dustAnalogPin,dustDigitalPin);                //initialize the dust sensor 
  UV.Init(UVPin);                  // initialize the UV Sensor
  Wire.begin();
  bmp.init (2);       //bmp i2c    oss=2 times
}

void loop(){
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
      DHT11Show();
      lcd.backlight();
    }
    else if(count==3){          //Dust Sensor
      DustShow();
      lcd.backlight();
    }
    else if(count==4){         //CO2 Sensor   
      CO2Show();    
      lcd.backlight();        
    }
    else if(count==5){         //UV Sensor   
      UVShow();  
      lcd.backlight();
    }
    else if(count==6){        //LX1972 Sensor
      LX1972Show();
      lcd.backlight();  
    }
    else if(count==7){        //BMP180 Sensor  
      BMP180Show();
      lcd.backlight(); 
    }
    else if(count==8){        //MQ5 Sensor
      MQ5Show();
      lcd.backlight();  
      count=0;
    }
    currentMillis = millis();
  }
  else{
    lcd.setBacklight(0);
  }
}

void DHT11Show(){
  int value = DHT.read(DHT11Pin);    // READ DATA
  lcd.setCursor(0,0);
  lcd.print("Humidity(%)=");
  lcd.print(DHT.humidity,1);
  lcd.print("  ");
  lcd.setCursor(0,1);
  lcd.print("Temp(C)=");
  lcd.print(DHT.temperature,1);
  lcd.print("      ");   
  delay(50);
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

void LX1972Show(){
  int lightValue = analogRead(lightPin);      //connect sensor pin
  lcd.clear();  
  lcd.setCursor(0,0);        //set first colomn and first row display    
  lcd.print("lightValue=");  
  lcd.print(lightValue);    //print the value to serial 
  lcd.print("      ");     
  lcd.setCursor(0,1);
  lcd.print("                ");      
  delay(100);  
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




