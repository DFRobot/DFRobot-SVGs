/*
www.DFRobot.com
 last updated by Gary on 02/02/2015
 wiki doc http://www.dfrobot.com/wiki/index.php/BLE_Wireless_Gamepad_(SKU:DFR0304)
 Support Forum: http://www.dfrobot.com/forum/
 e-mail: luguanyu.sjtu@gmail.com
 motified by Lisper
 ibrary version:1.0
 */

#include "BleGamepad.h"


char *buttion_name_table[14]={"L1","L2","R1","R2","Ba","Bb","Bc","Bd","B1","B2","B3","B4","SL","SR"};
int button_name[14]={0x20,0x21,0x1E,0x1F,0x04,0x07,0x05,0x06,0x0A,0x09,0x0B,0x08,0x0F,0x13};

BleGamepad::BleGamepad()
{
}

//get buffer
int BleGamepad::get_buffer()
{
        if(Serial.available())
        {
                for(_i = 0; _i < 15;_i++)
                {
                        _databuffer[_i]=Serial.read();
                        delay(2);
                        _oldtime = millis();
                }
                return 1;
        }
        else
        
	  _newtime = millis();
	  if (_newtime - _oldtime > 200 && _newtime - _oldtime < 250)
	  {
		  _databuffer[0] = 0x55;
		  _databuffer[1] = 0xaa;
		  _databuffer[2] = 0x11;
		  _databuffer[3] = 0x00;
		  _databuffer[4] = 0x00;
		  return 1;
	  }
	  else
	  {
		  return 0;
      }
  }


//check the buffer
int BleGamepad::check_buffer()
{
        if (get_buffer())
        {
                if(_databuffer[0] == 0x55 || _databuffer[1] == 0xaa || _databuffer[2] == 0x11)
                {
                        return 1;
                }
                else
                {
                        return 0;
                }
        }
        else
        {
                return 0;
        }
}

//get the number of the buttons being pressed
int BleGamepad::button_number()
{
        return _databuffer[3];
}

//get the stick state
void BleGamepad::get_stick_state(int *stick_state)
{
        int val;
        for ( _i = 0;_i < 4;_i++)
        {
                val = _databuffer[4] >> _i;
                if (val&0x01 == 0x01)
                {
                        stick_state[_i] = 1;
                }
                else
                {
                        stick_state[_i] = 0;
                }
        }
}

//get the stick position
void BleGamepad::get_stick(int *stick)
{
        get_stick_state(stick_state);
        for(_i = 0;_i < 4;_i++ )
        {
                if (stick_state[_i])
                {
                        stick[_i] = _databuffer[5+button_number()+_i];
                        stick[_i] = 2*stick[_i]-255;
                }
                else
                {
                        stick[_i] = 0;
                }
        }
}

//get the name of the buttons
void BleGamepad::get_button(int *button)
{
        for (_i = 0;_i < 3;_i++)
        {
                button[_i] = 0;
        }
        for (_i = 0;_i < button_number();_i++)
        {
                button[_i] = _databuffer[5+_i];
        }
}

//get the state of every buttons
void BleGamepad::check_button(int *button_state)
{
        get_button(button);
        for (_i = 0;_i < 14;_i++)
        {
                button_state[_i] = 0;
        }
        for (_i = 0;_i < 14;_i++)
        {
                for (int j = 0;j < button_number();j++)
                {
                        if (button_name[_i] == button[j])
                        {
                                button_state[_i] = 1;
                        }
                }
        }
}


