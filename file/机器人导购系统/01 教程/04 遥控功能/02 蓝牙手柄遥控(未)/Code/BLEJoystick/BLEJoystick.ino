/****************************************************
 * DFMobile BLE Joystick Control
 *****************************************************
 * This example is aimed to control DFMobile basic motion
 * Created 2015-3-10
 * By Gavin
 ******************************************************/
#include "DFMobile.h"
/*pin 4: enable left wheel
 pin 5: enable right wheel
 pin 6: pwm speed of left wheel
 pin 7: pwm speed of right wheel
 */
DFMobile Robot (4,5,7,6);

// Speed is modified by mapping vlaue of GamePad Stick
int LeftWheelSpeed;
int RightWheelSpeed;

// BleGamepad library facilitates user read the received signal of BleGamepad 
#include "BleGamepad.h"
BleGamepad ble;                    //BLE library
//Data String is used to store BLE data
//create array to store the command
int stick_state[4];                //"0" means the stick is in the original place, "1" means the stick is moved.
int stick[4];
int button[3];                     //show the name of the buttons that being pressed.(See the button_name[14])
int button_state[14];              //show the state of the 14 buttons.
//set the class ble

int databuffer[10]={};                //databuffer is created for storing Ble data
int i;

void setup () {
  Robot.Direction (false, true);// (left direction,right direction); 
  pinMode (13, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  if (ble.check_buffer()){         //check_buffer() = 1 means there is signal received. check_buffer() must be runned once before other function.   
    ble.get_stick_state(stick_state);             //store the stick state information in the arry stick_state.
    ble.get_button(button);                       //store the button information in the arry button.
    ble.check_button(button_state);               //store the button state information in the arry button_state. 
    ble.get_stick(stick);   
    //show GamePad display information
    Serial.print("Stick state: ");                //showing state information of  control stick
    for (i = 2;i < 4;i++){                         //stick_state[3] shows state of left stick X-axis motion                                                  
      Serial.print(stick_state[i]);               //stick_state[2] shows state of left stick Y-axis motion
      Serial.print(" ");                          //0: stick not touched; 1:stick touched
    }
    Serial.print("Stick: ");                      //stick_state[3] stores value of left stick X-axis motion 
    for (i = 2;i < 4;i++){                         //stick_state[2] stores value of left stick Y-axis motion
      Serial.print(stick[i]);                     //values from (-255,255)
      Serial.print(" ");
    }
     //When X-axis is touched, while Y-axis isn't.
     //Moving forward or going back is determined by the value of stick_state[3] 
     if (stick_state[3]==HIGH && stick_state[2]==LOW){
          if (stick[3]>0){                          //when stick[3]>0, this phenomenon represents stick is pushed up
            LeftWheelSpeed=stick[3];                //Both wheels move forward
            RightWheelSpeed=stick[3];
            Serial.print(stick[3]);
            Robot.Speed (LeftWheelSpeed,RightWheelSpeed);
          }         
          else{                                     //when stick[3]<0, this phenomenon represents stick is pushed down
          LeftWheelSpeed=stick[3];                  //Both wheels go back
          RightWheelSpeed=stick[3];
          Serial.print(stick[3]);
          Robot.Speed (LeftWheelSpeed,RightWheelSpeed);
          }
        }
     //When X-axis is touched, while Y-axis isn't.
     //Moving forward or going back is determined by the value of stick_state[3]
     else if (stick_state[2]==HIGH && stick_state[3]==LOW){
          if (stick[2]>0){                             //when stick[3]>0, this phenomenon represents stick is pushed left
          RightWheelSpeed=stick[2];                    // RightWheelSpeed>0
          Robot.Speed(-RightWheelSpeed,RightWheelSpeed);//turning left: Robot.Speed(-RightWheelSpeed,RightWheelSpeed);
          }
          else {                                       
          LeftWheelSpeed=stick[2];                     // RightWheelSpeed<0
          Robot.Speed(-LeftWheelSpeed,LeftWheelSpeed); //turning right: Robot.Speed(-LeftWheelSpeed,LeftWheelSpeed);
          }
         }
     else if(databuffer[3]==LOW){                       //if databuffer[3]=0, means no signal the Gamepad has been received
     Robot.Speed (0,0);
     }     
    }    
}

