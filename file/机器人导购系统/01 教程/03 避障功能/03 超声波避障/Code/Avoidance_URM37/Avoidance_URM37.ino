/****************************************************
 * DFMobileAvoidanceInfrared
 *****************************************************
 * This example is aimed to enable DFMobile to avoid 
 * obstaclesby using digital infrared sensor
 * Created 2015-3-9
 * By Gavin
 ******************************************************/
#include <DFMobile.h>
DFMobile Robot (4,5,7,6);//initiate to enable DFMobile motion 

//The library in this project facilitates the implementation of servo angle control
#include<Servo.h> 
Servo myservo;  // create servo object to control a servo 

// URM37 ultrasound distance sensor library, assist player to read distance
#include <URM37.h>
ultrasonic URM37;
double distance;//prarmeters of infrared distance measurement

int i=0;
int distanceBuffer[3];

void setup(){
  myservo.attach(10);
  Robot.Direction(LOW,HIGH);// (left direction,right direction); 
  Serial.begin (115200);
  URM37.Init(8,9);   //connect UrmEchoPIN on PIN 8, UrmPWMTrigPIN onPIN9
}

void loop(){
  myservo.write(90);    //initiate servo position
  Robot.Speed(80,80);   //forward
  Measurement();
  
  if(distance < 35){
    Robot.Speed (0,0);  // stop
    myservo.write(0);
    Measurement();
    delay(200);
    double degree_0 = distance;
    delay(50);
    myservo.write(180);
    Measurement();
    delay(200);
    double degree_180 = distance;
    delay(50);
    
    if(degree_0 > degree_180){
      Robot.Speed(-200,-200);//back off 
      delay(50);
      Robot.Speed(200,-200);//turn right
      delay(200);
    }
    else{
      Robot.Speed(-200,-200);//back off 
      delay(50);
      Robot.Speed(-200,200);//turn left
      delay(200);
    }
  }
  else{
    myservo.write(90);
    Robot.Speed (100,100);  //forward
  }
}

void Measurement(){
  distanceBuffer[i] = URM37.Distance();   //max=a>b&&a>c?a:(b>c?b:c); 
  i++;
  if(i>2){
    i=0;
  }
  distance = distanceBuffer[0]>distanceBuffer[1] && distanceBuffer[0]>distanceBuffer[2]?distanceBuffer[0]:(distanceBuffer[1]>distanceBuffer[2]?distanceBuffer[1]:distanceBuffer[2]);
  Serial.print(distance);
  Serial.println (" cm");
  delay (100);  
}




