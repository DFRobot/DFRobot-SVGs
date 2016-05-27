/****************************************************
 * HuntingLineBlack
 *****************************************************
 * This example is aimed to set up the hunting black line
 * function of DFMobile
 * Created 2015-3-3
 * By Gavin
 ******************************************************/
#include <DFMobile.h>
DFMobile Robot (4,5,7,6); 
int RightValue;    //Right line tractor sensor on Pin 8
int MiddleValue;   //Middle line tractor sensor on Pin 9
int LeftValue;     //Left line tractor sensor on Pin 10

void setup () {
  Robot.Direction (LOW, HIGH);
  Serial.begin(9600);
}

void loop () {
  //reading 3 pins values of Line Tracking Sensor
  RightValue=digitalRead(8);  
  MiddleValue=digitalRead(9);
  LeftValue=digitalRead(10);

  //print out the value you read:
  Serial.print(LeftValue);
  Serial.print(MiddleValue);
  Serial.println(RightValue);
  delay(100);

  //check if the robot is located in the middle of line 
  // if it is, the robot go straight. 
  if (MiddleValue==LOW) {   //line in the middle
    Robot.Speed (100,100);  //go straight
    delay(10);
  }
  else if ((LeftValue==HIGH) && (RightValue==HIGH)) {     
    Robot.Speed (100,100);  //go straight
    delay(10);
  }

  //check if the robot is located in the left of line 
  // if it is, the robot turn left. 
  else if ((LeftValue==LOW)&&(RightValue==HIGH)){          //line on left 
    Robot.Speed (-100,100);  //turn left
    delay(10);
  }

  //check if the robot is located in the right of line 
  // if it is, the robot turn right. 
  else if ((LeftValue==HIGH)&&(RightValue==LOW)){          //line on the right
    Robot.Speed (100,-100);  //turn right
    delay(10);
  }

  //other conditions
  else {
    Robot.Speed (0, 0);     //stop
    delay (100);
  }
}













