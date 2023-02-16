/*
 * App.c
 *
 * Created: 2/16/2023 6:22:10 PM
 *  Author: Ahmed
 */ 
#include "lcd.h"
#include "keypad.h"
#include "keypad_cnfg.h"
#include "std_macro.h"


void main(){
	LCD_INIT();
	KEYPAD_INIT();
	_delay_ms(10);
	safe_pass_check();
	
	
	
}