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

int RightValue;   //Right infrared digital sensor on Pin 8
int MiddleValue;  //Middle infrared digital sensor on Pin 9
int LeftValue;    //Left infrared digital sensor on Pin 10

void setup () {
  Robot.Direction (LOW, HIGH);
  Serial.begin(9600);
}

void loop () {
  RightValue=digitalRead(8);
  Serial.print (RightValue);

  MiddleValue=digitalRead(9);
  Serial.print (MiddleValue);

  LeftValue=digitalRead(10);
  Serial.println (LeftValue);
  delay (15);
  delay(100);

  //If there is no obstacle in front of the robot, then robot move forward
  if(LeftValue == HIGH && MiddleValue == HIGH  && RightValue == HIGH ) {    // no obstacle
    Robot.Speed (150,150);           //move forward
  }

  //If there is some obstacle in front of the robot, then robot back off
  if(LeftValue == LOW && MiddleValue == LOW && RightValue == LOW ) {    //all obstacles
    Robot.Speed (-200,-200);         //back off
    delay(800);
    Robot.Speed (-200,200);          //turn left
    delay(400);
    Robot.Speed (100,100);           //move forward
  }

  if( MiddleValue == LOW){     //obstacle in middle
    Robot.Speed (-150,-150);     //back off
    delay(400);
    Robot.Speed (-200,200);      //turn left
    delay(300);
    Robot.Speed (100,100);    //move forward
  }

  //If there is some obstacle on the left of the robot, then robot back off and turn right.
  if(LeftValue == LOW) {    //obstacle on the left side
    Robot.Speed (-200,-200);    //back off
    delay(400);
    Robot.Speed (200,-200);    //turn right
    delay(250);
    Robot.Speed (100,100);    //move forward
  }

  //If there is some obstacle on the right of the robot, then robot back off and turn left.
  if(RightValue == LOW ){       //obstacle on the right side
    Robot.Speed (-200,-200);     //back off
    delay(400);
    Robot.Speed (-200,200);     //turn left
    delay(250);
    Robot.Speed (100,100);      //move forward
  }
}












