/*
 * EEPROM.c
 *
 * Created: 2/16/2023 6:28:13 PM
 *  Author: Ahmed
 */ 

#include "std_macro.h"

void EEPROM_Init(void){
	
	
	
}
void EEPROM_Write(uint8_t add, uint8_t data){
	
	while(READBIT(EECR,EEWE)==1);
	EEAR=add;
	EEDR=data;
	
	SETBIT(EECR,EEMWE);
	SETBIT(EECR,EEWE);
	
	
	
	
}
uint8_t EEPROM_Read(uint8_t add){
	
	while(READBIT(EECR,EEWE)==1);
	EEAR=add;
	SETBIT(EECR,EERE);
	
	return EEDR;
	
	
	
	
}


