/* ========================================
 * Version: 2.9
 * Last Modified: 5.12.2021 
 * Formula Racing @ UC Davis, Electrical Senior Design, & the Electricool gang, 2021
 * ========================================
*/

// ToDo =======================================
// 1) Test this code on the new battery read set up. Battery reading uses the currently 
//    made breadboard voltage divider that we used for Shunt testing
// 2) May have to adjust the res1 and res2 values to more accurately reflect breadboard resistances

#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define SOC_FULL  10.2 //Ahr
#define BATTERY_HIGH_TEMP 60 //deg C   
#define RESISTOR_HIGH_TEMP 180 //deg C

#define NUM_R_THERMISTORS 5 // excluding the thermistor at Position 1
#define NUM_BAT_THERMISTORS 7 // excluding the thermistor at Position 1

#define SHUNT_CONDUCTANCE 1.2 // (1.2 for High Current, .133 for Low Current)

#define LOW_CURRENT 1
#define HIGH_CURRENT 20

#define V_REF_RELATIVE 39.7

int startFlag;
int printFlag;


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
void Print_Headers(uint length_a, uint length_b)
{
    char hstr[300];      //Made this very large
    sprintf(hstr,"\r\n");
    UART_1_UartPutString(hstr);
    sprintf(hstr,"Time(s), VbatVal(mV), VbatHigh(mV), VbatLow(mV), VShunt(mV), VShuntGND(mV), VRef(mV), Gain, ShuntG,  ");  //"Time, % SOC, Shunt(A), Bat(V), ");
    UART_1_UartPutString(hstr);
    
    for (uint i = 0; i < length_a; i++){
        sprintf(hstr,"Battery Temp %d, ", i);
        UART_1_UartPutString(hstr);
        CyDelay(10);
        }
        for (uint i = 0; i < length_b; i++){
        sprintf(hstr,"Resistor Temp %d, ", i);
        UART_1_UartPutString(hstr);
        CyDelay(10);
        }   
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
    
    I2C_1_Start();
    AMux_1_Start();
    Opamp_1_Start();
    PGA_1_Start(); 
    ADC_1_Start();
    UART_1_Start();
    PVref_1_Start();
    PVref_1_Enable();
    TCPWM_1_Start();
    Print_Headers(NUM_BAT_THERMISTORS,NUM_R_THERMISTORS);
}


/*******************************************************************************
* Function Name: HaltTest()
****************************************************************************//**
* 
* Turns off stuff (placeholder when more equipment is used)
*
*******************************************************************************/
void HaltTest(int stopCode){
    char string[50];
    Timer_1_Stop();
    TCPWM_1_Stop();
    RELAY_EN_Write(0);
    switch (stopCode) { 
    case 1: 
        sprintf(string, "\n\r!!! Test halted because of Cell is completely discharged !!!\n\r"); 
        break; 
    case 2: 
        sprintf(string, "\n\r!!! Test halted because of cell Overheating !!!\n\r"); 
        break; 
        
    case 3: 
        sprintf(string, "\n\r!!! Test halted beacuase of power resistor overheating !!!\n\r"); 
        break; 
        
    case 4: 
        sprintf(string, "\n\r"); 
        break;
    default: 
        sprintf(string, "\n\r!!! Test Halted for Unknown Reason !!!\n\r"); 
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
	static int32 filteredValue[5] = {0,0};
	
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


CY_ISR_PROTO(MyCustomISR);
CY_ISR(MyCustomISR)
{
    TCPWM_1_ClearInterrupt(TCPWM_1_INTR_MASK_TC);
    startFlag = 1;
}

/*CY_ISR_PROTO(print_UART);
CY_ISR(print_UART){
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
    printFlag = 1;
}*/



// ======================================
// Main Function
// ======================================
int main(void)
{
    // Variable Creation
    
    int32 vtestCount;           // Test voltage adc counts
    float vtestVal;             // Test voltage (mV)
    
    int32 vrgndCount;           // Virtual gnd voltage adc counts
    float vrgndVal;             // Virtual gnd voltage (mV)
    
    int32 vrefCount;            // Reference voltage adc counts
    float vrefVal;              // Reference voltage (mV)    
    
    int32 vbatHCount;
    float vbatHVal;
    
    int32 vbatLCount;
    float vbatLVal;
    
    float vbatVal;
    float shuntAmps; 
    
    uint32 printCount;
    uint32 time;
    float timeDec;
    float gainReal;             // Calculated gain of the amplifier
    
    char string[100];            // For printing over UART
    
    int32 userInput;            // Reading UART input
    int8 stopFlag = 0;          // Boolean flag to stop the test
    int8 stopCode = 0;          // Code for determining the reason why test was stopped
    
    int32 res1 = 828000;        //The first resistor in the battery voltage divider circuit
    int32 res2 = 10000;         //Seconds resistor in ^this^ divider
    
    uint8 batteryArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8 resistorArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    uint32 rxData;
    
    uint8 r_therm_toRead = (NUM_R_THERMISTORS*2) + 1;
    uint8 b_therm_toRead = (NUM_BAT_THERMISTORS*2) + 1;
    
    CyGlobalIntEnable;
        
    //Initialization
    
    CellTestStart();
    
    //UART INFO PRINTING    
    isr_1_StartEx(MyCustomISR);
    //isr_print_StartEx(print_UART);
    
    // Main For Loop
    for(;;)
    {
        // ------------------------ new --------------------------
        BLUE_LED_Write(1);
        CyDelay(100);
        BLUE_LED_Write(0);
        CyDelay(100);
        // -------------------------------------------------------
        
        userInput = UART_1_UartGetChar();
        if (userInput == 71)  //Type Capital G into Putty
        {         
            // ----------------------new --------------------------
            BLUE_LED_Write(0);
            RELAY_EN_Write(1);
            // ----------------------------------------------------
            TCPWM_1_Start();
            Timer_1_Start();
            stopFlag = 0;
            stopCode = 0;
            printCount = 0;
            
            // Continue Executing While the no test errors are evident
            while(!stopFlag){
                while(startFlag == 1){
                    startFlag = 0;
                    
                    //================================
                    // Reference Voltage Reading (vref)(or Cal_In)
                    //================================
                    AMux_1_Select(0);
                    ADC_1_StartConvert();                           // Start the Read the ADC
                    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                    vrefCount = ADC_1_GetResult32(0);               // vref in unitless counts   
                    vrefCount = FilterSignal(vrefCount, 0);         // Channel 3 because ...
                    vrefVal = ADC_1_CountsTo_mVolts(0, vrefCount);  // vref in mV     
                    
                    //================================
                    // Virtual Ground Reading (vrgnd)
                    //================================
                    AMux_1_Select(2);
                    ADC_1_StartConvert();                           // Start the Read the ADC
                    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                    vrgndCount = ADC_1_GetResult32(0);              // vrgnd in unitless counts                            
                    vrgndCount = FilterSignal(vrgndCount, 2);       // Channel 3 because...
                    vrgndVal = ADC_1_CountsTo_mVolts(0, vrgndCount);// vrgnd in mV                
                    
                    //================================
                    // Test Voltage Reading (vtest) (or Shunt_In) 
                    //================================
                    AMux_1_Select(1); 
                    ADC_1_StartConvert();                           // Start the Read the ADC
                    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);               
                    vtestCount = ADC_1_GetResult32(0);              // vtest in unitless counts
                    vtestCount = FilterSignal(vtestCount, 1);
                    vtestVal = ADC_1_CountsTo_mVolts(0, vtestCount);// vtest in mV                
                                                    
                    //================================
                    // Battery Voltage Divider (+) (vbatHigh)
                    //================================
                    AMux_1_Select(3);
                    ADC_1_StartConvert();                           // Start the Read the ADC
                    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                    vbatHCount = ADC_1_GetResult32(0);               // vref in unitless counts   
                    vbatHCount = FilterSignal(vbatHCount, 3);         // Channel 3 because ...
                    vbatHVal = ADC_1_CountsTo_mVolts(0, vbatHCount);  // vref in mV                
                    
                    //================================
                    // Battery Voltage Divider (-) (vbatLow)
                    //================================
                    AMux_1_Select(4);
                    ADC_1_StartConvert();                           // Start the Read the ADC
                    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                    vbatLCount = ADC_1_GetResult32(0);               // vref in unitless counts   
                    vbatLCount = FilterSignal(vbatLCount, 4);         // Channel 3 because ...
                    vbatLVal = ADC_1_CountsTo_mVolts(0, vbatLCount);  // vref in mV   
                    
                    gainReal = (vrefVal - vrgndVal)/V_REF_RELATIVE;     // The actual op-amp gain
                    
                    vrgndVal = vrgndVal/gainReal;                       // Find the virtual ground value
                    vrefVal = vrefVal / gainReal; 
                    vtestVal = vtestVal/gainReal;                       // Find the test point value
                   
                    vtestVal = vtestVal - vrgndVal;                     // Take the difference to negate op-amp offset
                    shuntAmps = vtestVal*SHUNT_CONDUCTANCE;                    
                    
                    vbatHVal = vbatHVal/gainReal;                         // The actual second divider battery voltage 
                    vbatLVal = vbatLVal/gainReal;
                    //vbatVal = (vbatHVal - vbatLVal);                      //The input voltage in VOLTS
                    //vbatVal = vbatVal * 838000/3000 + shuntAmps*.00417;       
                    vbatVal = (vbatHVal - vrgndVal + 9.9) * 839013.6 / 5972 + shuntAmps * .0044 * 1000; 
                    printCount += 1;
                    
                    // Stop the Test.... 
                    userInput = UART_1_UartGetChar();
                    if (userInput == 83) {
                        stopFlag = 1;
                        HaltTest(4);
                    }       
                    
                    if (printCount > 1000){
                        printCount = 0;
                        // ----------------new --------------------- // 
                        time = Timer_1_ReadCounter();
                        timeDec = time/128.0;     
                        // ----------------------------------------- // 

                        // sprintf(string, "\r\n Shunt: %f, Gain: %f, CalIn: %f, ShuntGND: %f, Batt mV: %f", vtestVal, gainReal, vrefVal, vrgndVal, vbatVal);              
                        sprintf(string, "\r\n %f, %f, %f, %f, %f, %f, %f, %f, %f, ", timeDec, vbatVal, vbatHVal, vbatLVal, vtestVal, vrgndVal, vrefVal, gainReal, SHUNT_CONDUCTANCE);
                        UART_1_UartPutString(string);
                        
                        I2C_1_I2CMasterReadBuf(0x08, batteryArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                        for(uint i = 2; i < b_therm_toRead; i=i+2){
                            sprintf(string, "%d.%d, ", batteryArray[i], batteryArray[i+1]);
                            UART_1_UartPutString(string);    
                        }
                        
                        CyDelay(10);
                        
                        I2C_1_I2CMasterReadBuf(0x09, resistorArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                        for(uint i = 2; i < r_therm_toRead; i=i+2){
                            sprintf(string, "%d.%d, ", resistorArray[i], resistorArray[i+1]);
                            UART_1_UartPutString(string);    
                        } 
                        
                        // Battery Voltage Detection
                        
                        if(vbatVal < 2900) {
                            stopFlag = 1;
                            HaltTest(1);
                            sprintf(string, "\r\n ERROR - Cell Discharged: %f \r\n", vbatVal); 
                            UART_1_UartPutString(string); 
                        }
                        // ---------------------------------------------------------------------------------------------------------------------------------------------//
                    }
                    
                    // ----------------------------------------------- all new code --------------------------------------------------------------------//
                    for(uint i = 2; i < 12; i=i+2){
                        if (batteryArray[i] > BATTERY_HIGH_TEMP){
                            stopFlag = 1;
                            HaltTest(2);
                            sprintf(string, "\r\n ERROR - High Temperature on Battery: %d.%d, on Thermistor %d \r\n", batteryArray[i], batteryArray[i+1], i);
                            UART_1_UartPutString(string); 
                        }
                        if (resistorArray[i] > RESISTOR_HIGH_TEMP){ 
                            stopFlag = 1; 
                            HaltTest(3);
                            sprintf(string, "\r\n ERROR - High Temperature on Resistor: %d.%d, on Thermistor %d \r\n", resistorArray[i], resistorArray[i+1], i);
                            UART_1_UartPutString(string);   
                        }  
                    }
                }                               
            }
        }
    }
}

/* [] END OF FILE */
