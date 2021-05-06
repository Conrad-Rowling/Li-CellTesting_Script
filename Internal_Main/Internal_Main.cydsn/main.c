/* ========================================
 * Version: 2.2
 * Last Modified: 5.2.2021 
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

#define V_REF_RELATIVE  40          //know voltage of VRef - VRGnd (mV)           
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
    CyGlobalIntEnable;
    AMux_1_Start();
    AMux_2_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    PGA_1_Start(); 
    ADC_1_Start();
    UART_1_Start();
    PVref_1_Start();
    PVref_1_Enable();
    BLUE_LED_Write(0);
    TCPWM_1_Start();
}


/*******************************************************************************
* Function Name: CellTestStop()
****************************************************************************//**
* 
* Turns off stuff (placeholder when more equipment is used)
*
*******************************************************************************/
void HaltTest(int stopCode){
    char string[30];
    Timer_1_Stop();
    switch (stopCode) { 
    case 1: 
        sprintf(string, "!!! Test halted because of Cell is completely discharged !!!\n\r"); 
        break; 
    case 2: 
        sprintf(string, "!!! Test halted because of cell Overheating !!!\n\r"); 
        break; 
        
    case 3: 
        sprintf(string, "!!! Test halted beacuase of power resistor overheating !!!\n\r"); 
        break; 
        
    case 4: 
        sprintf(string, "!!! Test Halted by user !!!\n\r"); 
        break;
    default: 
        sprintf(string, "!!! Test Halted for Unknown Reason !!!\n\r"); 
    }
    
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
	static int32 filteredValue[9] = {0,0};
	
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


int startFlag;

CY_ISR_PROTO(MyCustomISR);
CY_ISR(MyCustomISR)
{
    //void _ClearPending(MyCustomISR.intrSrcS);
    TCPWM_1_ClearInterrupt(TCPWM_1_INTR_MASK_TC);
    //isr_1_ClearPending(); 
    startFlag = 1;
}



// ======================================
// Main Function
// ======================================
int main(void)
{
    // Variable Creation
    
    int32 vtestIdeal = V_TEST_START;
    
    int32 vtestCount;           // Test voltage adc counts
    float vtestVal;             // Test voltage (mV)
    
    int32 vrgndCount;           // Virtual gnd voltage adc counts
    float vrgndVal;             // Virtual gnd voltage (mV)
    
    int32 vrefCount;            // Reference voltage adc counts
    float vrefVal;              // Reference voltage (mV)
    
    int32 vbatUpCount;
    float vbatUpVal;
    
    int32 vbatLowCount;
    float vbatLowVal;
    
    int32 vbatCalCount;
    float vbatCalVal;
    
    int32 vbatGndCount;
    float vbatGndVal;
    
    float vbatVal;
    
    float gainReal;             // Calculated gain of the amplifier
    float gainReal2;
    char string[60];            // For printing over UART
    
    int32 userInput;            // Reading UART input
    int8 stopFlag = 0;          // Boolean flag to stop the test
    int8 stopCode = 0;          // Code for determining the reason why test was stopped
    
    CyGlobalIntEnable;
        
    //Initialization
    
    CellTestStart();
    
    //UART INFO PRINTING
    sprintf(string, "\r\n\r\nAt any point in the test to increment the Test Voltage: Enter 'S' \r\n"); 
    UART_1_UartPutString(string);
    sprintf(string, "The Test Voltage will increment by in 5 mV in the data logger \r\n");
    UART_1_UartPutString(string);
    sprintf(string, "\r\nEnter G to start Test: \r\n"); 
    UART_1_UartPutString(string);
    sprintf(string,"\r\n Voltage(Ideal) (mV), Voltage(Measured) (mV), VirtualGND (mV), VRef (mV), Calculated Gain \r\n");
    UART_1_UartPutString(string);
        
    isr_1_StartEx(MyCustomISR);
    
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
            stopCode = 0; 
            
            // Continue Executing While the no test errors are evident
            while(!stopFlag){
                while(startFlag == 1){
                startFlag = 0;
                
                //================================
                // Reference Voltage Reading (vref)
                //================================
                AMux_1_Select(0);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrefCount = ADC_1_GetResult32(1);               // vref in unitless counts   
                vrefCount = FilterSignal(vrefCount, 3);         // Channel 3 because ...
                vrefVal = ADC_1_CountsTo_mVolts(1, vrefCount);  // vref in mV     
                
                //================================
                // Virtual Ground Reading (vrgnd)
                //================================
                AMux_1_Select(2);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vrgndCount = ADC_1_GetResult32(1);              // vrgnd in unitless counts                            
                vrgndCount = FilterSignal(vrgndCount, 2);       // Channel 3 because...
                vrgndVal = ADC_1_CountsTo_mVolts(1, vrgndCount);// vrgnd in mV                
                
                //================================
                // Test Voltage Reading (vtest)
                //================================
                AMux_1_Select(1); 
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);               
                vtestCount = ADC_1_GetResult32(1);              // vtest in unitless counts
                vtestCount = FilterSignal(vtestCount, 1);
                vtestVal = ADC_1_CountsTo_mVolts(1, vtestCount);// vtest in mV                
                                                
                //================================
                // Battery Voltage Divider (+) (vbatUp)
                //================================
                AMux_2_Select(0);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vbatUpCount = ADC_1_GetResult32(0);               // vref in unitless counts   
                vbatUpCount = FilterSignal(vbatUpCount, 4);         // Channel 3 because ...
                vbatUpVal = ADC_1_CountsTo_mVolts(0, vbatUpCount);  // vref in mV                
                                
                //================================
                // Battery Voltage Divider (-) (vbatLow)
                //================================
                
                AMux_2_Select(1);
                ADC_1_StartConvert();                           // Start the Read the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vbatLowCount = ADC_1_GetResult32(0);               // vref in unitless counts   
                vbatLowCount = FilterSignal(vbatLowCount, 7);         // Channel 3 because ...
                vbatLowVal = ADC_1_CountsTo_mVolts(0, vbatLowCount);
                
                
                // After rapid samples - to ensure similar adc/amp conditions
                // Calculations are made
                
                gainReal = (vrefVal - vrgndVal)/V_REF_RELATIVE;     // The actual op-amp gain
                vrgndVal = vrgndVal/gainReal;                       // Find the virtual ground value
                vtestVal = vtestVal/gainReal;                       // Find the test point value
               
                vtestVal = vtestVal - vrgndVal;                     // Take the difference to negate op-amp offset
                gainReal2 = (vbatCalVal - vbatGndVal)/V_REF_RELATIVE;
                vbatVal = (vbatUpVal - vbatLowVal);                 //gainReal2;

                } //end of scan from startflag
                
                // Stop the Test.... 
                userInput = UART_1_UartGetChar();
                if (userInput == 83) {
                    stopFlag = 1;
                    stopCode = 4; 
                    Timer_1_Stop();
                    vtestIdeal = vtestIdeal + 5;
                }                         
                
                //CyDelayUs(250);
                
                // Print the values
                if (Timer_1_ReadCounter() > 1){ 
                    sprintf(string, "%ld, %3.3f, %3.3f, %3.3f, %3.3f, %3.3f, %3.3f, %3.3f, %3.3f \r\n", vtestIdeal, vtestVal, vrgndVal, vrefVal, gainReal, vbatVal, gainReal2, vbatUpVal, vbatLowVal); 
                    UART_1_UartPutString(string);
                    Timer_1_WriteCounter(0);
                }
                
                
                //==========================
                // Shutdown Features 
                //==========================
                
                /*
                // Over Heating Protection
                for(uint i = 2; i < 12; i=i+2){
                    if (batteryArray[i] > BATTERY_HIGH_TEMP){
                        stopFlag = 1; 
                        stopCode = 2; 
                        sprintf(string1, "\r\n ERROR - High Temperature on Battery: %d.%d, on Thermistor %d \r\n", batteryArray[i], batteryArray[i+1], i);
                        UART_1_UartPutString(string1); 
                    }
                    if (resistorArray[i] > RESISTOR_HIGH_TEMP){ 
                        stopFlag = 1; 
                        stopCode = 3; 
                        sprintf(string1, "\r\n ERROR - High Temperature on Resistor: %d.%d, on Thermistor %d \r\n", resistorArray[i], resistorArray[i+1], i);
                        UART_1_UartPutString(string1);   
                    }
                }
                
                // Battery Voltage Detection
                 if(vmBatmV < 2.5) {
                    stopFlag = 1; 
                    stopCode = 1;
                    sprintf(string1, "\r\n ERROR - Cell Discharged: %f \r\n", vmBatmV); 
                    UART_1_UartPutString(string1); 
                }                
                */
                
            }
        }
    }
}

/* [] END OF FILE */
