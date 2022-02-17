/*adc  a0->light
			a1->soilMoisture 
			a2-lm35
*/
	
ADC_humidity_SetConfig:
	 LDI R16,0b00100001;Vref=Aref(3v)
	 OUT ADMUX,R16
	 LDI R16,0b10000000 ;adc enabel  & 
	  OUT ADCSRA,R16
	  ret
ADC_LM35_SetConfig:
	 LDI R16,0b11100010;& Vref=2.56
	 OUT ADMUX,R16
	 LDI R16,0b10000011 ;adc enabel  
	 OUT ADCSRA,R16
	 ret

ADC_Light_SetConfig:
	 LDI R16,0b01100000 ;& Vref=5v
	 OUT ADMUX,R16
	 LDI R16,0b10000011 ;adc enabel  
	 OUT ADCSRA,R16
	 ret

SoilMoistureADC:
	call delay
	SBI ADCSRA,ADSC ;start convertion
	wait_SoilMoistureADC: 
			SBIS ADCSRA,ADIF
			RJMP wait_SoilMoistureADC
	 SBI ADCSrA,ADIF
	 IN R20,ADCH
	 ret
LM35ADC:
	//r20 =tempHolder
	SBI ADCSRA,ADSC
	wait_LM35ADC: 
		SBIS ADCSRA,ADIF
		RJMP wait_LM35ADC
	SBI ADCSrA,ADIF
	IN R20,ADCH
	ret
LightADC:
	//r20==LightADCH
	call delay
	SBI ADCSRA,ADSC ;start convertion
	wait_LightADC: 
			SBIS ADCSRA,ADIF
			RJMP wait_LightADC
	 SBI ADCSrA,ADIF
	 IN R20,ADCH
	 ret
	