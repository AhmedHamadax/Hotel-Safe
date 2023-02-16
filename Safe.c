/*
 * Safe.c
 *
 * Created: 2/16/2023 7:18:32 PM
 *  Author: Ahmed
 */ 
#include "std_macro.h"
#include "Safe.h"
#include "keypad.h"
#include "keypad_cnfg.h"
#include "EEPROM.h"
#include "lcd.h"
void safe_pass_init(void){ //function in case of setting a new password
	uint8_t x;
	LCD_write_command(0x01);
	LCD_write_string("Set a Password");
	
	for(x=10;x<14;x++){    //For loop 4 times in order to fill 4 addresses in the EEPROM
		while(KEYPAD_READ()<0);
		if(x==10) LCD_write_command(0x01); 
		EEPROM_Write(x,KEYPAD_READ());
		LCD_write_char(KEYPAD_READ());  //you can display '*' here instead
		SETBIT(PORTC,PC5); //Beep(optional)
		_delay_ms(100);
		CLRBIT(PORTC,PC5);
		
		
		_delay_ms(300);
	}
	LCD_write_command(0x01);
	LCD_write_string("Password Set");
	_delay_ms(1000);
	LCD_write_command(0x01);
}

void safe_pass_check(void){
	SETBIT(DDRC,PC6); //for Lights& Buzzer
	SETBIT(DDRC,PC5); //
	SETBIT(DDRC,PC0); //
	SETBIT(DDRC,PC1); //for Lights& Buzzer
	SETBIT(PORTC,PC0);//Turn Red Led on
	
	uint8_t EEPROM_Add=10,y,x[4],err=0,Pass_Re;
	
	while(1){
		LCD_write_command(0x01);
		LCD_write_string("Enter Password: ");
	for(EEPROM_Add=10,y=0,Pass_Re=0,err=0 ;   y<4  ;  y++,EEPROM_Add++ ){ //For loop that will loop 4 times for the 4 digits of password
		
		while(KEYPAD_READ()<0); //Polling Until Keypad is clicked 
		
		if(y==0) LCD_write_command(0x01);
		
		x[y]=KEYPAD_READ();  
		
		LCD_write_char(x[y]);
		
		SETBIT(PORTC,PC5); //Makes a Beep On keypad clicks (Optional)
		_delay_ms(100);
		CLRBIT(PORTC,PC5);
		
		if( x[y] != EEPROM_Read(EEPROM_Add) ) err=1; //Here we will compare each element entered with the corresponding element from the EEPROM to make sure password is entered correctly
		if( x[y]=='0' ) Pass_Re++ ; // I chose the reset password to be '0000' so if it is entered 4 times that is a flag that one wants to reset 
		_delay_ms(300);
		
	}
	//The following is the possible cases
	
/*Case 1: if the reset password is entered */	

if(Pass_Re==4)	safe_pass_init();

/*Case 2: if a wrong password is entered */	

else if(err==1) {LCD_write_command(0x01); LCD_write_string("Wrong Try Again:"); _delay_ms(1000);}
	
/*Case 1: if the correct password is entered */
else{
		LCD_write_command(0x01);
		 LCD_write_string("Door Opened");
		 CLRBIT(PORTC,PC0);
		 SETBIT(PORTC,PC1);// Green led(Optional)
		 SETBIT(PORTC,PC6);//A signal that runs the motor for 500 ms
		 _delay_ms(500);
		 CLRBIT(PORTC,PC6); 
		
		 LCD_write_command(0x01);
		 
		  while(1) {if(KEYPAD_READ()=='*') { //Polling while the door is  open until the close button(*) is pressed 
			  CLRBIT(PORTC,PC1); 
			  SETBIT(PORTC,PC0); //Red led 
			  LCD_write_string("Door Closed");
			  SETBIT(PORTC,PC6); //A signal that runs the motor for 500 ms
			  _delay_ms(500);
			  CLRBIT(PORTC,PC6);
			  
			  break;} //Break to restart the proccess and start asking again for the password after the door is closed
	}
			  _delay_ms(500);
		  }
		  	
		  
	
	
	}
	
	
	
	
	}
	
	
	



