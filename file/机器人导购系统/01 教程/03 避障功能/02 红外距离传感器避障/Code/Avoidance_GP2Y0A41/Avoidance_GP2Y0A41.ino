/****************************************************
 * Avoidance_GP2Y0A41
 *****************************************************
 * This example is aimed to enable DFMobile to avoid 
 * obstaclesby using digital infrared sensor
 * Created 2015-3-5
 * By Gavin
 ******************************************************/
#include <DFMobile.h>
DFMobile Robot(4,5,7,6);//initiate to enable DFMobile motion 

//The library in this project facilitates the implementation of servo angle control
#include<Servo.h> 
Servo myservo;           // create servo object to control a servo 

//GP2Y0A41SKOF infrared distance sensor library, assist player to read distance
#include <GP2Y0A41.h>
InfraredSensor GP2Y0A41;
long distance;           //prarmeters of infrared distance measurement


void setup () {
  myservo.attach(10);
  Serial.begin(9600);
  Robot.Direction (LOW, HIGH);     // initiate the positive direction  
  Robot.Speed (100,100);       //the default is forward
}

void loop () {
  myservo.write(90);      //initiate servo position
  Robot.Speed (80,80); 

  distance = GP2Y0A41.Distance(A5);       //read the distance on analog pin 5    
  Serial.print(distance);   //print out the value you read
  Serial.println (" cm");
  
  // check if the obstacle is in front of the robot within 13cm
  if(distance < 13){
    Robot.Speed (0,0);   // stop
    myservo.write(0);    // tell servo to go to position in 0 degree
    double degree_0 = GP2Y0A41.Distance(A5);    // read the distance in 0 degree  
    delay(200);
    myservo.write(180);  // tell servo to go to position in 1800 degree
    double degree_180 = GP2Y0A41.Distance(A5);  // read the distance in 0 degree  
    delay(200);

    //compare the distance in 0 degree with it in 180 degree 
    if(degree_0 > degree_180){
      Robot.Speed (-200,-200);  //back off 
      delay(50);
      Robot.Speed (200,-200);   //turn right
      delay(200);
    }
    else{
      Robot.Speed (-200,-200);   //back off 
      delay(50);
      Robot.Speed (-200,200);    //turn left
      delay(200);
    }
  }
  else{
    myservo.write(90);  
    Robot.Speed (100,100);  //forward
  }
}




