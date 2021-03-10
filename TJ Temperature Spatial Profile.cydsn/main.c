/* ========================================
 *
 * Christian Gonzalez, UC Davis, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * Whoops
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

int32 FilterSignal(int32 ADCSample, uint8 channel){
    
	/* Running filtered value accumulator */
	static int32 filteredValue[32] = {0,0};
	
	/* Filtered value rounded-off to 20-bits */
	int32 filValueRounded;
	
	/* Left shift input by MAX_FILTER_COEFF_SHIFT to allow divisions up to MAX_FILTER_COEFF_SHIFT */
	ADCSample <<= 8;
	   
	/* Pass the filter input as it is for fast changes in input */
    if((ADCSample > (filteredValue[channel] + (100*256))) || (ADCSample < (filteredValue[channel] - (100*256)))){
        
        filteredValue[channel] = ADCSample;
        
    }
    
    /* If not the first sample then based on filter coefficient, filter the input signal */
    else{
		
        /* IIR filter */
		filteredValue[channel] = filteredValue[channel] + ((ADCSample - filteredValue[channel]) >> 4);			
        
	}
	
	/* Compensate filter result for  left shift of 8 and round off */
	filValueRounded = (filteredValue[channel] >> 8) + ((filteredValue[channel] & 0x00000080) >> 7);
	
    return filValueRounded;
}

/* Initialize string for UART data transmission */
char string[16];

int main(void)
{  
    /* Voltages across reference resistor and thermistor*/
	int32 vref;
    int32 vtherm;
    
    /* ADC offset voltage through Correlated Double Sampling */
    int32 adcOffset;
	
	/* Resistance of Thermistor */
	uint32 resT;
	
	/* Temperature value in 100ths of a degree C */
	int16 temp; 
	
    /*Decimal Temp */
    int32 decTemp;
    
    /*Fractional Temp */
    int32 fracTemp;
    
    /* Channel */
    int32 chan = 0;
    int32 i;
    
    /* Temperature Array */
    uint8 tempArr[32];
    
    /* I2C Read Buffer */
    uint8 rdBuf[32];
    
    /* Enable global interrupts. */
    CyGlobalIntEnable;
    
    /* Initialize I2C Buffer */
    I2C_1_I2CSlaveInitReadBuf(rdBuf, 32);
    I2C_1_I2CSlaveClearReadBuf();
    I2C_1_I2CSlaveClearReadStatus();
    
    /* Initialize all PSoC components */
    Opamp_1_Start();
    Opamp_2_Start();
    Opamp_3_Start();
    AMux_1_Start();
    ADC_1_Start();
    I2C_1_Start();
    UART_1_Start(); 
    
    // Read ADC offset voltage (CDS)   
    AMux_1_Select(32);
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    adcOffset = ADC_1_GetResult32(0);
    ADC_1_StopConvert();
        
    for(;;)
    {
        LED_Write(1);
        /* Initialize Voltage Reference component separately to reduce error from self-heating in thermistor*/
        PVref_1_Start();
        PVref_1_Enable();
                        
        /* Scan through MUX channels, get temperature and send data */
        for(chan=0; chan<32; chan=chan+2){
                      
            AMux_1_Select(chan);
            ADC_1_StartConvert();
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
            vtherm = ADC_1_GetResult32(0);
            ADC_1_StopConvert();
            vtherm = vtherm - adcOffset;
            
            /* IIR Filter for vtherm */
            vtherm = FilterSignal(vtherm, chan);
            
            AMux_1_Select(chan+1);
            ADC_1_StartConvert();
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
            vref = ADC_1_GetResult32(0);
            ADC_1_StopConvert();
            vref = vref - adcOffset;
            
            /* IIR Filter for vref */
            vref = FilterSignal(vref, chan+1);
            
            resT = Thermistor_1_GetResistance(vref, vtherm);
            temp = Thermistor_1_GetTemperature(resT);
                       
    	    //Determine decimal portion of temperature by dividing temperature by 100
            decTemp = temp/100;
            
            // Determine fraction portion of temperature by subtracting decimal portion from result 
            fracTemp = temp - (decTemp * 100);
            
            // If fractional temperature is negative make it positive 
            if(fracTemp < 0) {
                fracTemp *= -1;
            }
                       
            /* Put temperature parts into an array */
            tempArr[chan] = decTemp;
            tempArr[chan+1] = fracTemp;
            
            // Get thermistor number
             i = (chan/2) + 1;
             //UART Transmission for Debug
             sprintf(string, "Therm %ld = %ld.%.2ld", i, decTemp, fracTemp); 
             UART_1_UartPutString(string);
             UART_1_UartPutString("\n\r");
            
        }      
        
        /* Copy temperature data to I2C read buffer */
        memcpy(rdBuf, tempArr, 32);
                
        /* Clear I2C read buffer and any previous status */
        I2C_1_I2CSlaveClearReadBuf();
        I2C_1_I2CSlaveClearReadStatus(); 
                
        /* Dsiable Voltage Reference to help reduce error due to self-heating */
        PVref_1_Stop();
        
        /* Wait five seconds */
        CyDelay(5000);
    }
}


/* [] END OF FILE */
