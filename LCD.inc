/*
 * LCD.inc
 *
 *  Created: 1/23/2022 4:09:25 PM
 *   Author: Aryana
 */ 
 
LCD_CMD:
	out portd,r16
	cbi portc,1 ;E/w
	cbi portc,2 ; Rs
	sbi portc,0 ;enb
	nop
	nop
	cbi portc,0
	call delay
	ret
 LCD_DAT:
	out portd,r16
	cbi portc,1
	sbi portc,2
	sbi portc,0
	nop
	nop
	cbi portc,0
	call delay
	ret
