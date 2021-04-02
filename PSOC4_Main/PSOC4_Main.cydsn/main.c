/* ========================================
 * Version: 1.0
 * Last Modified: 3.31.2021 
 * Conrad Rowling, Osama Abualsoud, Milad Mehr, Tucker Zischka, Formula Racing @ UC Davis, 2021
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Formula Racing @ UC Davis company.
 *
 * ========================================
*/

// =============================
// Delcarations and Includes
// =============================
#include <project.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1u
#define false 0u
#define SOC_FULL  10.2 //Ahr
#define BATTERY_HIGH_TEMP 60 //deg C   
#define RESISTOR_HIGH_TEMP 180 //deg C

#define NUM_R_THERMISTORS 5 // excluding the thermistor at Position 1
#define NUM_BAT_THERMISTORS 6 // excluding the thermistor at Position 1

#define SHUNT_CONDUCTANCE 1.2 // (1.2 for High Current, 7.5 for Low Current)
#define AMP_GAIN 32.0 // (from Amp Blocks)

#define LOW_CURRENT 1
#define HIGH_CURRENT 20

// =============================
// Function Definitions
// =============================

/*******************************************************************************
* Function Name: Shutdown_Test
****************************************************************************//**
* 
* Opens the current path, and turns off the on board LED, and prints
*
*******************************************************************************/
void Shutdown_Test()
{
    char string[10];
    RED_LED_Write(1);
    RELAY_Write(0);
    sprintf(string,"\r\n  -- Test Stopped -- \r\n");
    UART_1_UartPutString(string);
    
}

/*******************************************************************************
* Function Name: Print_Headers
****************************************************************************//**
*
* Formats the headers for exporting the UART terminal to a comma delimited Excel file
*
*******************************************************************************/
void Print_Headers(uint length_a, uint length_b)
{
    char hstr[60]; 
    sprintf(hstr,"\r\n");
    UART_1_UartPutString(hstr);
    sprintf(hstr,"Time(s), SOC(percent), Bat(V), Shunt(A), ");//"Time, % SOC, Shunt(A), Bat(V), ");
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
}

/*******************************************************************************
* Function Name: Move_Window
****************************************************************************//**
*
* Increments a moving window average array , pass the array to increment, the value to include, and the length of the array
*
*******************************************************************************/
float Move_Window(float *array, float reading, uint len){
    float average = 0;
    for (uint i = 1; i < len; i++){
        array[i-1] = array[i];
    }
    array[len -1] = reading;
    for (uint i = 0; i < 10; i++){
        average  += array[i];
    }
    average = average/10.0;
    return average;
}

// ======================================
// Main Function
// ======================================
int main (void)
{
    int lowTemp = true;
    int goodCurrent = true;
    int stopPlease = false;
    uint8 r_therm_toRead = (NUM_R_THERMISTORS*2) + 1;
    uint8 b_therm_toRead = (NUM_BAT_THERMISTORS*2) + 1;
    
    uint32 time;
    uint32 timeOld;
    float soc;
    uint32 vmShunt; //Voltage measured from shunt in 12-bit res
    uint32 adcOffset; // adcOffset in 12-bit resolution
    float adcOff;
    float ShmV;
    float ShA;
    float windowArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32 vmBat;
    float vmBatmV;
    
    uint8 batteryArray[32];
    uint8 resistorArray[32];
    char string1[20];
    uint32 rxData;
    
    AMux_1_Start();
    Opamp_1_Start();
    PGA_1_Start();
    PGA_2_Start();
    UART_1_Start();
    RED_LED_Write(0);
    RELAY_Write(0);
    ADC_1_Start();
    I2C_1_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
     
    sprintf(string1,"\r\n Enter G to Start Test, Enter S to Stop \r\n");
    UART_1_UartPutString(string1);

    soc = SOC_FULL;
    // If test starts at another point than full SOC, need to enter it here
    
    for(;;)
    {
        
        RED_LED_Write(1);
        CyDelay(1000);
        RELAY_Write(0);
        rxData = UART_1_UartGetChar();
        
        if (rxData == 71)  //Type Capital G into Putty
        {
            sprintf(string1,"\r\n Beginning the Test... \r\n");
            UART_1_UartPutString(string1);
            PVref_1_Start();
            RED_LED_Write(1);
            RELAY_Write(1);
            Timer_1_Start();
            Print_Headers(NUM_BAT_THERMISTORS, NUM_R_THERMISTORS);
            
            lowTemp = true;
            goodCurrent = true;
            stopPlease = false;
            
            //ADC Offset 
            AMux_1_Select(0);                               // Mux Select
            ADC_1_StartConvert();                           // Start the Read the ADC
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);   // Wait
            adcOffset = ADC_1_GetResult32(0);               // Get the ADC reading
            adcOff = ADC_1_CountsTo_mVolts(0, adcOffset);   // Convert to milivolts
            adcOff = adcOff - 1200.0;                       // Proper offset of the offest (What is 1200 for? )
            ADC_1_StopConvert();                            // Stop ADC Conversino 
            PVref_1_Stop();                                 // 
            
            timeOld = Timer_1_ReadCounter();     // just to avoid the first readcounter
            
            while(lowTemp && goodCurrent && !stopPlease){   
                
                time = Timer_1_ReadCounter(); //Read Counter for the time
                
                sprintf(string1,"\r\n %lu, ", time); //print time
                UART_1_UartPutString(string1);
                                
                // SoC Calculator
                if (time > timeOld){
                    soc = soc -  ShA*(time-timeOld)/3600;
                    timeOld = time;
                }
                
                sprintf(string1,"\r\n %3.5f, ", soc*100.0/SOC_FULL);
                UART_1_UartPutString(string1);
                                                     
                //Battery Voltage Reading & Conversion
                AMux_1_Select(2);                               // Select Battery Voltage 
                ADC_1_StartConvert();                           // Start the ADC
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);   // Wait for the ADC
                vmBat = ADC_1_GetResult32(0);                   // Get the Results
                ADC_1_StopConvert();                            // Stop the ADC
                vmBatmV = ADC_1_CountsTo_mVolts(0, vmBat);      // Convert the ADC Value to mV
                vmBatmV = vmBatmV - adcOff;                     // Apply Offset
                vmBatmV = 3.0*vmBatmV/1000.0;                   // Convert the Value
                sprintf(string1, "%3.3f, ", vmBatmV);           // Place in the Display string
                UART_1_UartPutString(string1);                  // Print the Display String
               
                //Shunt Voltage Reading & Conversion
                AMux_1_Select(1);                               // Select the Shunt Voltage
                ADC_1_StartConvert();                           // Start the Conversion 
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);   // End the Conversion
                vmShunt = ADC_1_GetResult32(0);                 // Get the Results
                ADC_1_StopConvert();                            // Stop Conversion
                
                ShmV = ADC_1_CountsTo_mVolts(0, vmShunt);       // Convert to mV
                ShmV = ShmV - adcOff;                           // Apply Offset
                ShA = ShmV*SHUNT_CONDUCTANCE/(AMP_GAIN);                 // Convert the Value
                
                // Moving Average Code
                if (windowArray[9] == 0){   
                    int i = 0;
                    windowArray[i] = ShA;
                    i += 1;
                }
                else{
                    ShA = Move_Window(windowArray, ShA, 10);
                }
                
                sprintf(string1, "%3.3f, ", ShA);
                UART_1_UartPutString(string1);

                
                // Read Battery Temperature Array via I2C and append to print string
                I2C_1_I2CMasterReadBuf(0x08, batteryArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                for(uint i = 2; i < b_therm_toRead; i=i+2){
                    sprintf(string1, "%d.%d, ", batteryArray[i], batteryArray[i+1]);
                    UART_1_UartPutString(string1);    
                }
                
                // Ready Power Resistors Temperature Array via I2C and append to print string
                I2C_1_I2CMasterReadBuf(0x09, resistorArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                for(uint i = 2; i < r_therm_toRead; i=i+2){
                    sprintf(string1, "%d.%d, ", resistorArray[i], resistorArray[i+1]);
                    UART_1_UartPutString(string1);    
                }
                
                sprintf(string1, "\r\n");
                UART_1_UartPutString(string1);  //Push print string to terminal
                rxData = UART_1_UartGetChar();  // Terminal Serial Input??? 
                CyDelay(500);
                                
                if (rxData == 83){
                    stopPlease = true;
                    Shutdown_Test();
                }
                
                
                for(uint i = 2; i < 12; i=i+2){
                    if (batteryArray[i] > BATTERY_HIGH_TEMP){
                        lowTemp = false;
                        sprintf(string1, "\r\n ERROR - High Temperature on Battery: %d.%d, on Thermistor %d \r\n", batteryArray[i], batteryArray[i+1], i);
                        UART_1_UartPutString(string1);  
                    }
                    if (resistorArray[i] > RESISTOR_HIGH_TEMP){ 
                        lowTemp = false;
                        sprintf(string1, "\r\n ERROR - High Temperature on Resistor: %d.%d, on Thermistor %d \r\n", resistorArray[i], resistorArray[i+1], i);
                        UART_1_UartPutString(string1);  
                    }
                }
                
                if ((ShA < LOW_CURRENT) ||(ShA > HIGH_CURRENT)){
                    goodCurrent = false;
                    sprintf(string1, "\r\n ERROR - High Temperature on Resistor: %f \r\n", ShA);
                    UART_1_UartPutString(string1); 
                }
                
            }
            UART_1_UartPutString("\r\n TEST HALTED - Enter 'G' to Resume \r\n");
            Timer_1_Stop();
        }
        
    }
}

/* [] END OF FILE */
