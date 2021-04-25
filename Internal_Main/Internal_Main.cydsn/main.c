/* ========================================
 * Version: 1.3
 * Last Modified: 4.24.2021 
 * Formula Racing @ UC Davis, Electrical Senior Design, & the Electricool gang, 2021
 * ========================================
*/

// ToDo =======================================
// 1) Figure out why the ADC jumps around alot to narrow down the error
// 1.1) Add in the Shunt_GND and CAL_in functionality into the code 
// 2) Add in the Muxes into the program
// 3) Correct the output of the serial terminal
// 4) Add in Safety features

#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define V_REF_RELATIVE  35          //know voltage of VRef - VRGnd (mV)           
#define V_TEST_START    0

// =============================
// Function Definitions
// =============================


/*******************************************************************************
* Function Name: Print_Headers
****************************************************************************//**
*
* Formats the headers for exporting the UART terminal to a comma delimited Excel file
*
*******************************************************************************/
void Print_Headers()
{
    char hstr[60]; 
    sprintf(hstr,"\r\n");
    UART_1_UartPutString(hstr);
    sprintf(hstr,"\r\n Voltage(Ideal) (mV), Voltage(Measured) (mV), VirtualGND (mV), VRef (mV), Calculated Gain \r\n");
    UART_1_UartPutString(hstr);
    sprintf(hstr,"\r\n");
    UART_1_UartPutString(hstr);
}
/*******************************************************************************
* Function Name: CellTestStart()
****************************************************************************//**
* 
* Initialize all of the units and functionality
*
*******************************************************************************/
void CellTestStart(){
    AMux_1_Start();
    PGA_1_Start(); 
    ADC_1_Start();
    UART_1_Start();
    PVref_1_Start();
    BLUE_LED_Write(0);
}


/*******************************************************************************
* Function Name: CellTestStop()
****************************************************************************//**
* 
* Turns off stuff (placeholder when more equipment is used)
*
*******************************************************************************/
void HaltTest(){
    char string[30];
    Timer_1_Stop();
    sprintf(string, "0, 0, 0, 0, 0\r\n"); 
    UART_1_UartPutString(string);
}


/*******************************************************************************
* Function Name: FilterSignal()
****************************************************************************//**
* 
* Moving window average (more or less) - takes input value, compares it to the last value on the given channel.
* If its much bigger, it takes the new value in. If not, it rounds the difference out.
*
*******************************************************************************/
int32 FilterSignal(int32 ADCSample, uint8 channel){
    
    // MOVING AVERAGE
	static int32 filteredValue[4] = {0,0};
	
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



// ======================================
// Main Function
// ======================================
int main(void)
{
    // Variable Creation
    
    int32 vtestIdeal = V_TEST_START;
    
    int32 vtestCount;           //test voltage adc counts
    float vtestVal;             //test voltage (mV)
    
    int32 vrgndCount;           //virtual gnd voltage adc counts
    float vrgndVal;             //virtual gnd voltage (mV)
    
    int32 vrefCount;            //reference voltage adc counts
    float vrefVal;              //reference voltage (mV)
    
    float gainReal;             //calculated gain of the amplifier
    char string[60];            //for printing over UART
    
    int32 userInput;            //reading UART input
    int8 stopFlag = 0;          //boolean flag to stop the test
    
    //Initialization
    
    CellTestStart();
    CyGlobalIntEnable;
    
    //UART INFO PRINTING
    sprintf(string, "At any point in the test to increment the Test Voltage: Enter 'S' \r\n"); 
    UART_1_UartPutString(string);
    sprintf(string, "The Test Voltage will increment by in 5 mV in the data logger \r\n");
    UART_1_UartPutString(string);
    sprintf(string, "\r\nEnter G to start Test: \r\n"); 
    UART_1_UartPutString(string);
    sprintf(string,"\r\n Voltage(Ideal) (mV), Voltage(Measured) (mV), VirtualGND (mV), VRef (mV), Calculated Gain \r\n");
    UART_1_UartPutString(string);
    
    // Main For Loop
    for(;;)
    {
        BLUE_LED_Write(1);
        CyDelay(10);
        userInput = UART_1_UartGetChar();
        
        // Start the Test Commmand
        
        if (userInput == 71)  //Type Capital G into Putty
        {            
            Timer_1_Start();
            stopFlag = 0;
            
            // Continue Executing While the no test errors are evident
            while(!stopFlag){
                
                // Start 1.2 V Reference
                
                void PVref_P4_Enable (void );
                
                // Test Voltage Reading
          
                AMux_1_Select(1); 
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);               
                vtestCount = ADC_1_GetResult32(0);              // vtest in unitless counts
                ADC_1_StopConvert();
                vtestCount = FilterSignal(vtestCount, 2);
                vtestVal = ADC_1_CountsTo_mVolts(0, vtestCount);// vtest in mV                
                
                // Virtual Ground Reading 
                
                AMux_1_Select(2);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrgndCount = ADC_1_GetResult32(0);              // vrgnd in unitless counts
                ADC_1_StopConvert();                            
                vrgndCount = FilterSignal(vrgndCount, 3);
                vrgndVal = ADC_1_CountsTo_mVolts(0, vrgndCount);// vrgnd in mV
                
                // Reference Voltage Reading
                
                AMux_1_Select(0);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrefCount = ADC_1_GetResult32(0);               // vref in unitless counts
                ADC_1_StopConvert();
                vrefCount = FilterSignal(vrefCount, 3);
                vrefVal = ADC_1_CountsTo_mVolts(0, vrefCount);  // vref in mV
                
                
                // After rapid samples - to ensure similar adc/amp conditions
                // Calculations are made
                
                gainReal = (vrefVal - vrgndVal)/V_REF_RELATIVE;     // The actual op-amp gain
                vrgndVal = vrgndVal/gainReal;                       // Find the virtual ground value
                vtestVal = vtestVal/gainReal;                       // Find the test point value
                vtestVal = vtestVal - vrgndVal;                     // Take the difference to negate op-amp offset
                
                // This is the test voltage relative to virtual gnd
                
                // Stop the Test.... 
                userInput = UART_1_UartGetChar();
                
                if (userInput == 83){ // 83 is ASCII for STOP t     
                    stopFlag = 1;
                    Timer_1_Stop();
                    vtestIdeal = vtestIdeal + 5;
                }                         
     
                CyDelayUs(250);
                
                // Print the values
                if (Timer_1_ReadCounter() > 1){
                    sprintf(string, "%ld, %3.3f, %3.3f, %3.3f, %3.3f \r\n", vtestIdeal, vtestVal, vrgndVal, vrefVal, gainReal); 
                    UART_1_UartPutString(string);
                    Timer_1_WriteCounter(0);
                }
            }
        }
    }
}

/* [] END OF FILE */
