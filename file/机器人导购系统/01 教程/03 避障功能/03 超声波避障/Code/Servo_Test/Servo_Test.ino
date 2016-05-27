// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

void setup() { 
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() {                    
   myservo.write(90);              // tell servo to go to position in 90 
   delay(15);                      // waits 15ms for the servo to reach the position 
} 
