;
; dsd2_project_irigation.asm
;
; Created: 1/13/2022 8:49:47 PM
; Author : Aryana
;


; Replace with your application code
/*
r16->  Variable holder  |  LCD dat_CMD
r17-> Current Mod   (0x00 Rose   0xff Cactus)
r20 -> ADCH (dout/4)
r21-> Soil humidity status  0 dry  1 normal 2 wet
r22 -> Pump   (if ==1 ->on    if ==0 -> off)
r23-> Light status  (0x00 ->low  0x01->good 0x02->high)

R30,R31  -> DELAY
*/
jmp start
.include "LightSens.inc"
.include "Display.inc"
.include "LCD.inc"
.include "HumiditySensor.inc"
.include "LM35.inc"
.include "adcConfig.inc"


start:
//stack
 ldi r16,0x08
 out sph,r16
 ldi r16,0x5f
 out spl,r16
 
//ports
	
	;display ports
		; portd-> d0-d7 ( words to display0
		; pc0->en   pc1->RW'  pc2->RS
	ldi r16,0xff
	out ddrc,r16
	out ddrd,r16
	
	;motor and sensors and buzzer and switches
	 sbi ddrb,0 ;output pb0 ( motor)
	 sbi ddrb,1 ;buzzer
	 cbi ddrb,2 ;switch input (mod selector) (5v == Cactus  0v == Rose)


	 cbi portb,0
	 cbi portb,1

	 cbi ddra,0 ;input pa0(Light)
	 cbi ddra,2 ;input pa2(thermal)
	 cbi ddra,1 ;input pa1(humidity)



	
 //display config
	

 ldi r16,0x38 	;Function Set: 8-bit
 call LCD_CMD
 ldi r16,0x0e ;display on,cursor(_) blinkk
 call LCD_CMD
 ldi r16,0x01 ;clear scrn
 call LCD_CMD

	
	
main:
	call RefreshDisplay
	

	;Mod Selector
	call SetMod
	

	;humidity
	call ADC_humidity_SetConfig
	call SoilMoistureADC ;save Dout/4 to R20
	call SoilHumidityStatus ;is soil  dry? normal ? wet ?
	call HumidityAction; do proper action to the soil status
	
	
	;LM35
	call ADC_LM35_SetConfig
	call LM35ADC ;get data to R20
	call TempDisplay
	
	//LDR light sensor
	call ADC_Light_SetConfig
	call LightADC
	call LightStatus
	call LightStateDisplay
	
	call Alarm;buzzer
	
   
	
	rjmp main

	
SetMod:;switch input (mod selector) (5v == Cactus  0v == Rose)   | r17-> Current Mod   (0x00 Rose   0xff Cactus)
	;lcd Cursor set pos
	ldi r16,0x80 
	;call LCD_CMD
	ldi r16,0x86 ;ddram set to 0c 
	call LCD_CMD
	;----------------------
	sbis pinb,2 ;check switch
	rjmp SetModeRose
	rjmp SetModeCactus
	;cursor pos: 0x06  -> instruction code: 0x06+0x80 == 0x86
	SetModeCactus:
	ldi r17,0xff
	call printCactus
	ret
	SetModeRose:	
	ldi r17,0x00
	call printRose
	ret


Alarm: ; (if Dry  and low light)
	cpi r21,0 ;dry
	breq doAlarm
	rjmp StopAlarm
	in r16,portb
	doAlarm:
	sbi portb,1
		/*
		sbr r16,0b00000010 ;ori (yek kardan bit 2 vom)
		out portb,r16*/
		ret

	StopAlarm:
	cbi portb,1
	/*
		cbr r16,0b00000010   ;ani rd,k' (sefr kardan bit 2 vom)
		out portb,r16*/
		ret

 delay: ;if f=16Mhz ->  delay=20ms
	ldi r30,200
	ldi r31,26
	l2:
		l1:
			nop
			nop
			nop
			dec r30
			brne l1
		dec r31
		brne l2
	ret
