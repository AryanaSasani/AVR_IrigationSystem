
 // Dout= 4*Temp  Temp=Dout/4 ==adch
 

TempDisplay:
	 		//config:[	
			;Go to Line4 ddrlcd: 0x59 => 0xd9
		ldi r16,0xd9 
		call LCD_CMD
	
	call BCD
	call  adcToAssci
	  mov r16,Yl
	  call LCD_DAT
	  mov r16,xh
	 call LCD_DAT
	 mov r16,xl
	 call LCD_DAT
	
	ret