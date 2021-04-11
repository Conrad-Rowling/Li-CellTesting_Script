/* ========================================
 * Version: 1.1
 * Last Modified: 4.10.2021 
 * Formula Racing @ UC Davis, Electrical Senior Design, 2021
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Formula Racing @ UC Davis and the electricool gang.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_R_THERMISTORS 5 // excluding the thermistor at Position 1
#define NUM_BAT_THERMISTORS 6 // excluding the thermistor at Position 1
#define SHUNT_CONDUCTANCE 1.2 
#define AMP_GAIN 21.3
#define V_REF 50.0


// =============================
// Function Definitions
// =============================

/*******************************************************************************
* Function Name: CellTestStart()
****************************************************************************//**
* 
* Initialize all of the units and functionality
*
*******************************************************************************/
void CellTestStart(){
    //AMux_1_Start();
    //AMux_2_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    ADC_1_Start();
    UART_1_Start();
    BLUE_LED_Write(0);
    RELAY_EN_Write(0);
    PVref_1_Start(); 
    PVref_1_Enable();
}


/*******************************************************************************
* Function Name: CellTestStop()
****************************************************************************//**
* 
* Stop all of the units and functionality
*
*******************************************************************************/
void CellTestStop(){
    PVref_1_Stop();
}


/*******************************************************************************
* Function Name: FilterSignal()
****************************************************************************//**
* 
* Filter the incomming singal using a moving average and ....
*
*******************************************************************************/
int32 FilterSignal(int32 ADCSample, uint8 channel){
    
    // MOVING AVERAGE
	static int32 filteredValue[3] = {0,0};
	
	/* Filtered value rounded-off to 20-bits */
	int32 filValueRounded;
	
	/* Left shift input by MAX_FILTER_COEFF_SHIFT to allow divisions up to MAX_FILTER_COEFF_SHIFT */
	ADCSample <<= 8;
	   
	/* Pass the filter input as it is for fast changes in input  - if the least significant bits change by a factor of 100*/
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


/*******************************************************************************
* Function Name: PointerTest()
****************************************************************************//**
* 
* God if I know what this does.... 
*
*******************************************************************************/
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




// ======================================
// Main Function
// ======================================
int main(void)
{
    // Variable Creation
    int32 shuntCount; //Voltage measured from shunt in 12-bit res
    float shuntVal;
    int32 vrgndCount;
    int32 vrefCount;
    float vrefVal;
    float vrgndVal; 
    char string[30];
    
    int32 userInput;
    int8 stopFlag = 0;      
    
    //Initialization
    CellTestStart();
    CyGlobalIntEnable;
    
    sprintf(string, "\r\nEnter G to start Test: \r\n"); 
    UART_1_UartPutString(string);
    
    // Main For Loop
    for(;;)
    {
        BLUE_LED_Write(1);
        CyDelay(1000);
        userInput = UART_1_UartGetChar();
        
        // Start the Test Commmand
        if (userInput == 71)  //Type Capital G into Putty
        {
            Timer_1_Start();
            stopFlag = 0;
            PVref_1_Start(); 
            PVref_1_Enable();
            
            // Continue Executing While the no test errors are evident
            while(!stopFlag){
                
                // Select the Shunt voltage Reading 
                //AMux_2_Select(1);
                
                // Shunt Calibarte In 
                /*
                AMux_1_Select(0);                              
                ADC_1_StartConvert();                           
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrefCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                //vrefCount = FilterSignal(vrefCount, 0);
                vrefVal = ADC_1_CountsTo_Volts(0, vrefCount);
                */
                
                // Shunt In
                //AMux_1_Select(1);                               // Mux Select
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                shuntCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                shuntVal = ADC_1_CountsTo_mVolts(0, shuntCount);
                //shuntCount = FilterSignal(shuntCount, 1);
                
                // Shunt Ground Reading
                /*
                AMux_1_Select(2);                               // Mux Select
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrgndCount = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vrgndVal = ADC_1_CountsTo_mVolts(0, vrgndCount);
                //vrgndCount = FilterSignal(shuntCount, 2);
                */
                
                // Shunt Calcuation...
                //shuntCount = shuntCount - vrgndCount; 
                //shuntVal = ADC_1_CountsTo_mVolts(0, shuntCount);
                //shuntVal = (shuntVal*SHUNT_CONDUCTANCE)/(vrefVal/V_REF);
                
                // Stop the Test.... 
                if (userInput == 83){ // 83 is ASCII for STOP t     
                    stopFlag = 1;
                    Timer_1_Stop();
                    CellTestStop();
                    sprintf(string, "\r\n Test Halted \r\n"); 
                    UART_1_UartPutString(string);
                    sprintf(string, "\r\n Enter G to Resume Test: \r\n"); 
                    UART_1_UartPutString(string);
                }
                
                CyDelayUs(250);
                
                // Print the Shunt Value
                if (Timer_1_ReadCounter() > 1){
                    sprintf(string, "Shunt Value: %3.3f", shuntVal); 
                    UART_1_UartPutString(string);
                    UART_1_UartPutString("\n\r");
                    Timer_1_WriteCounter(0);
                }
            }
        }
    }
}

/* [] END OF FILE */
