/*
 * HumiditySensor.inc
 *
 *  Created: 1/23/2022 4:07:40 PM
 *   Author: Aryana
 */ 
 

SoilHumidityStatus: //   Dout/4 <51 (==20%) -> dry (r21=0)(r22=1 (pump on))       Dout/4 >76 (30%) -> wet(r21=2) (r22=0 (pump off))    else-> normal(r21=1)(r22=0 (pump off))  
	cpi r20,51
	brlo dry
	cpi r20,76
	brsh wet
	rjmp normal ;else (rjmp normal)

	dry:
		ldi r21,0
		ldi r22,1 ;pump on
		ret
	normal:
		ldi r21,1
		ldi r22,0
		ret
	wet:
		ldi r21,2
		ldi r22,0
		ret
	


HumidityAction:
	HumidityAction_display:
		//config:[	
			;Go to Line2 ,ddram 0x4a  -> 0xca
		ldi r16,0xCA 
		call LCD_CMD

		cpi r21,0
		breq dryAction
		cpi r21,1
		breq normalAction
		rjmp wetAction ;else (rjmp normal)

		dryAction:
			//Print(DRY)

			ldi r16,'D'
			call LCD_DAT
			ldi r16,'R'
			call LCD_DAT
			ldi r16,'Y'
			call LCD_DAT
			
			rjmp HumidityAction_Pump
		
		normalAction:
			//Print(Normal)
			ldi r16,'N'
			call LCD_DAT
			ldi r16,'o'
			call LCD_DAT
			ldi r16,'r'
			call LCD_DAT
			ldi r16,'m'
			call LCD_DAT
			ldi r16,'a'
			call LCD_DAT
			ldi r16,'l'
			call LCD_DAT
			
			rjmp HumidityAction_Pump
		wetAction:
			//Print(Normal)
			ldi r16,'W'
			call LCD_DAT
			ldi r16,'E'
			call LCD_DAT
			ldi r16,'T'
			call LCD_DAT

			rjmp HumidityAction_Pump

	HumidityAction_Pump:
		//Lcd config:[	
			;line 1 ddram 0x11 -> 0x91
			ldi r16,0x91 
			call LCD_CMD

		
		cpi r22,0
		breq HumidityAction_Pump_Off ;if r22==0 -> off
		;else on
		HumidityAction_Pump_On:
			;turn on
			sbi portb,0
			/*ldi r16,0b00000001
			out portb,r16*/

			;print(ON)
			ldi r16,'O'
			call LCD_DAT
			ldi r16,'N'
			call LCD_DAT
		ret
		HumidityAction_Pump_Off:
			;turn off
			cbi portb,0
			/*
			
			ldi r16,0b00000000
			out portb,r16 */
			;print(off)
			ldi r16,'O'
			call LCD_DAT
			ldi r16,'F'
			call LCD_DAT
			ldi r16,'F'
			call LCD_DAT

		ret



