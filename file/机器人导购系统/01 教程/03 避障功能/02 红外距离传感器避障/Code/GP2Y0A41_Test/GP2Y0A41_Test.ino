//GP2Y0A41SKOF infrared distance sensor library, assist player to read distance
#include <GP2Y0A41.h>
long distance;           //prarmeters of infrared distance measurement
InfraredSensor GP2Y0A41;

void setup () {
  Serial.begin(9600);
}

void loop () {
  distance = GP2Y0A41.Distance(A5);       //read the distance on analog pin 5    
  Serial.print(distance);   //print out the value you read
}
