/*
 * Display.inc
 *
 *  Created: 1/23/2022 4:35:18 PM
 *   Author: Aryana
 */ 
 
RefreshDisplay:
	ldi r16,0x01 ;clear scrn
	call LCD_CMD

	;Print Structure
	;Line 1 ( Plant:******|Pmp:***)
	ldi r16,0x80 ;line 1
	call LCD_CMD
	call printPlant
	ldi r16,0x8c ;ddram set to 0c 
	call LCD_CMD
	call printPump 
	;line 2
	ldi r16,0xC0
	call LCD_CMD
	call printHumidity
	;line 3
	ldi r16,0x94
	call LCD_CMD
	call printLight
	;line 4
	ldi r16,0xD4
	call LCD_CMD
	call printTemp
	ret
	
printTemp:
	ldi r16,'T'
	 call LCD_DAT
	 ldi r16,'E'
	 call LCD_DAT
	 ldi r16,'M'
	 call LCD_DAT
	 ldi r16,'P'
	 call LCD_DAT
	 ldi r16,':'
	 call LCD_DAT

	 ret
printLight:
	 ldi r16,'L'
	 call LCD_DAT
	 ldi r16,'I'
	 call LCD_DAT
	 ldi r16,'G'
	 call LCD_DAT
	 ldi r16,'H'
	 call LCD_DAT
	 ldi r16,'T'
	 call LCD_DAT
	 ldi r16,':'
	 	call LCD_DAT
	 ret
printHumidity:
	 ldi r16,'M'
	 call LCD_DAT
	 ldi r16,'O'
	 call LCD_DAT
	 ldi r16,'I'
	 call LCD_DAT
	 ldi r16,'S'
	 call LCD_DAT
	 ldi r16,'T'
	 call LCD_DAT
	 ldi r16,'U'
	 call LCD_DAT
	  ldi r16,'R'
	 call LCD_DAT
	 ldi r16,'E'
	 call LCD_DAT
	 ldi r16,':'
	 call LCD_DAT
	ret
printPlant:
 ldi r16,'P'
 call LCD_DAT
 ldi r16,'L'
 call LCD_DAT
 ldi r16,'A'
 call LCD_DAT
 ldi r16,'N'
 call LCD_DAT
 ldi r16,'T'
 call LCD_DAT
 ldi r16,':'
 call LCD_DAT
ret
printPump:
 ldi r16,'|'
 call LCD_DAT
 ldi r16,'P'
 call LCD_DAT
 ldi r16,'M'
 call LCD_DAT
 ldi r16,'P'
 call LCD_DAT
 ldi r16,':'
 call LCD_DAT	
ret

printCactus:
 ldi r16,'C'
 call LCD_DAT
 ldi r16,'a'
 call LCD_DAT
 ldi r16,'c'
 call LCD_DAT
 ldi r16,'t'
 call LCD_DAT
 ldi r16,'u'
 call LCD_DAT
 ldi r16,'s'
 call LCD_DAT
ret
printRose:
 ldi r16,'R'
 call LCD_DAT
 ldi r16,'o'
 call LCD_DAT
 ldi r16,'s'
 call LCD_DAT
 ldi r16,'e'
 call LCD_DAT
ret

printHigh:
	 ldi r16,'H'
	 call LCD_DAT
	 ldi r16,'i'
	 call LCD_DAT
	 ldi r16,'g'
	 call LCD_DAT
	 ldi r16,'h'
	 call LCD_DAT
	ret
printGood:
	 ldi r16,'G'
	 call LCD_DAT
	 ldi r16,'o'
	 call LCD_DAT
	 ldi r16,'o'
	 call LCD_DAT
	 ldi r16,'d'
	 call LCD_DAT
ret
printLow:
	 ldi r16,'L'
	 call LCD_DAT
	 ldi r16,'o'
	 call LCD_DAT
	 ldi r16,'w'
	 call LCD_DAT
ret

Bcd:
	//joda kardan Yekan va Dahgan, tabdil be bcd
	mov r16,r20  ;xl==r26	
	ldi xl,0 ; 1 kan
	ldi xh,0 ; 10 gan
	ldi yl,0 ;100 gan
	cpi r16,100
	brlo dahgan  ;if sadgan nadare -> dahgan ro chek kon 
	subi r16,100
	inc yl
	 
	dahgan:
		cpi r16,10
		brlo yekan  ;if sadgan nadare -> dahgan ro chek kon 
		subi r16,10
		inc xh
		rjmp dahgan
	yekan:
		mov xl,r16

	ret

adcToAssci:
	ldi yh,48
	add xl,yh
	add xh,yh
	add yl,yh
	ret


