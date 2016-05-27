/****************************************************
 * MotorTest2
 *****************************************************
 * This example is aimed to control DFMobile basic motion
 * Created 2015-3-2
 * By Gavin
 ******************************************************/
#include <DFMobile.h>
DFMobile Robot (4,5,7,6);

void setup () {
  Robot.Direction (LOW,HIGH); // (left direction,right direction); 
  pinMode (13, OUTPUT);
}

void loop () {
  Robot.Speed (0,-255);  //left wheel back
  digitalWrite (13, HIGH);
  delay (1000);

  Robot.Speed (-255,0);  //right wheel back
  digitalWrite (13, HIGH);
  delay (1000);

  Robot.Speed (0,255);  //left wheel forward
  digitalWrite (13, HIGH);
  delay (1000);

  Robot.Speed (255,0);  //right wheel forward
  digitalWrite (13, HIGH);
  delay (1000);

  Robot.Speed (255,255);  //forward
  digitalWrite (13, HIGH);
  delay (1000);

  Robot.Speed (0, 0);
  delay (2000);
}








