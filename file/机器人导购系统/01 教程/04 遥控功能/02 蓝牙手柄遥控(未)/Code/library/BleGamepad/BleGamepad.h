/* 
   BleGamepad.h - Library for BleGamepad (DFR0304). 
   Created by Gary Lu, February 2, 2015. 
   e-mail: luguanyu.sjtu@gmail.com
   motified by Lisper
 */ 
#ifndef BleGamepad_h
#define BleGamepad_h
#include "Arduino.h"

extern char *buttion_name_table[14];
extern int button_name[14];

class BleGamepad
{
	public:
		BleGamepad();

		int get_buffer();
		int check_buffer();
		int button_number();
		void get_stick_state(int *stick_state);
		void get_stick(int *stick);
		void get_button(int *button);
		void check_button(int *button_state);
	private:
		uint8_t _databuffer[15];
		int _i;
		int stick_state[4];
		int stick[4];
		int button[3];
		int button_state[14];

	        uint32_t _newtime;
	       uint32_t _oldtime;
};


#endif

