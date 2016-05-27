int LeftLEDPin = 11;
int RightLEDPin = 2;
int BuzzerPin = 3;

void setup () {
  pinMode(LeftLEDPin,OUTPUT);
  pinMode(RightLEDPin,OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
}

void loop(){
  LEDState(HIGH,HIGH);  
  delay(1000);
  LEDState(LOW,LOW);
  delay(1000);
  TurnOnBuzzer();
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
