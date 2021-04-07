
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_R_THERMISTORS 5 // excluding the thermistor at Position 1
#define NUM_BAT_THERMISTORS 6 // excluding the thermistor at Position 1
#define SHUNT_CONDUCTANCE 1.2 
#define AMP_GAIN 21.3
#define V_REF 40.0

void CellTestStart(){
    AMux_1_Start();
    AMux_2_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    ADC_1_Start();
    UART_1_Start();
    BLUE_LED_Write(0);
    RELAY_EN_Write(1);
}

void CellTestStop(){
    PVref_1_Stop();
}
int32 FilterSignal(int32 ADCSample){
    
    // MOVING AVERAGE
	static int32 filteredValue = {0};
	
	/* Filtered value rounded-off to 20-bits */
	int32 filValueRounded;
	
	/* Left shift input by MAX_FILTER_COEFF_SHIFT to allow divisions up to MAX_FILTER_COEFF_SHIFT */
	ADCSample <<= 8;
	   
	/* Pass the filter input as it is for fast changes in input  - if the least significant bits change by a factor of 100*/
    if((ADCSample > (filteredValue + (100*256))) || (ADCSample < (filteredValue - (100*256)))){
        filteredValue = ADCSample;     
    }
    
    /* If not the first sample then based on filter coefficient, filter the input signal */
    else{
        /* IIR filter */
		filteredValue = filteredValue + ((ADCSample - filteredValue) >> 4);		 
	}
    
	/* Compensate filter result for  left shift of 8 and round off */
	filValueRounded = (filteredValue >> 8) + ((filteredValue & 0x00000080) >> 7);
    return filValueRounded;
}
int32 PointerTest(int32 array){
    array <<= 8;
    static int32 pointer = {0};
    int32 result;
    if (array > pointer){
        printf("\r\n pointer %ld \r\n", pointer);
        printf("\r\n array %ld\r\n", array);
        pointer = array;
    }
    
    else{
        printf("\r\n POINTER %ld\r\n", pointer);
        printf("\r\n array %ld\r\n", array);
        pointer = pointer + ((array - pointer ) >> 4);
    }
    result = (pointer >> 8) + ((pointer & 0x00000080) >> 7);
    return result;      
}

int main(void)
{
    uint32 shuntCount; //Voltage measured from shunt in 12-bit res
    float shuntVal;
    uint32 vrgndCount;
    uint32 vrefCount;
    float vrefVal;
    char string[30];
    
    uint32 userInput;
    int8 stopFlag = 0;      
    
    CellTestStart();
    CyGlobalIntEnable;
    
    for(;;)
    {
        BLUE_LED_Write(1);
        CyDelay(1000);
        userInput = UART_1_UartGetChar();
        
        if (userInput == 71)  //Type Capital G into Putty
        {
            Timer_1_Start();
            stopFlag = 0;
            PVref_1_Start();
            PVref_1_Enable();
            
            while(!stopFlag){
                
                AMux_2_Select(1);
                
                AMux_1_Select(0);                              
                ADC_1_StartConvert();                           
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrefCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vrefVal = FilterSignal(vrefCount);
                
                AMux_1_Select(1);                               // Mux Select
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                shuntCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                shuntCount = FilterSignal(shuntCount);
                
                AMux_1_Select(2);                               // Mux Select
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrgndCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vrgndCount = FilterSignal(shuntCount);
                
                shuntCount = shuntCount - vrgndCount;
                shuntVal = ADC_1_CountsTo_mVolts(shuntCount, 0);
                shuntVal = (shuntVal*SHUNT_CONDUCTANCE)/(vrefVal/V_REF);
                
                // 83 is ASCII for STOP 
                if (userInput == 83){              
                    stopFlag = 1;
                    Timer_1_Stop();
                    CellTestStop();
                }
                
                CyDelayUs(250);
                
                if (Timer_1_ReadCounter() > 4){
                    sprintf(string, "Shunt Value: %f", shuntVal); 
                    UART_1_UartPutString(string);
                    UART_1_UartPutString("\n\r");
                    Timer_1_WriteCounter(0);
                }
            }
        }
    }
}

/* [] END OF FILE */
