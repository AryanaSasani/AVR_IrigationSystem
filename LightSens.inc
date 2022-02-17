/*
 * LightSens.inc
 *
 *  Created: 1/23/2022 8:22:36 PM
 *   Author: Aryana
 */ 
 LightStatus:
	//check mod:
	cpi r17,0x00
	breq LightMode_Rose
	rjmp LightMode_Cactus

	LightMode_Rose:
		cpi r20,43
		brsh LightStatus_Low
		cpi r20,38
		brlo LightStatus_High
		rjmp LightStatus_Good
	LightMode_Cactus:
		cpi r20,211
		brsh LightStatus_Low
		rjmp LightStatus_Good
	
	LightStatus_High:
		ldi r23,2
		ret
	LightStatus_Good:
		ldi r23,1
		ret
	LightStatus_Low:
		ldi r23,0
		ret

 LightStateDisplay:
	// set curser: ddrLCD = 0x1A  -> code : 0x9A
	ldi r16,0x9A
	call LCD_CMD
	
	cpi r23,0
	breq LightStateDisplay_Low
	cpi r23,1
	breq LightStateDisplay_Good
	cpi r23,2
	breq LightStateDisplay_High
	LightStateDisplay_Low:
		call printLow
		ret
	LightStateDisplay_Good:
		call printGood
		ret
	LightStateDisplay_High:
		call printHigh
	
	ret