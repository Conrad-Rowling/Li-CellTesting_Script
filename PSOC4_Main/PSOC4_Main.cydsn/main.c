/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
//#include <LIS3DH.h>

#define true 1u
#define false 0u

void Shutdown_Test()
{
    RED_LED_Write(1);
    RELAY_Write(0);
}
void Print_headers(uint length)
{
    char hstr[60]; 
    sprintf(hstr,"\r\n");
    UART_1_UartPutString(hstr);
    sprintf(hstr,"Time, Shunt(A), Bat(V), ");
    UART_1_UartPutString(hstr);
    
    for (uint i = 0; i < length; i++){
        sprintf(hstr,"Battery Temp %d, ", i);
        UART_1_UartPutString(hstr);
        CyDelay(10);
        }
        for (uint i = 0; i < length; i++){
        sprintf(hstr,"Resistor Temp %d, ", i);
        UART_1_UartPutString(hstr);
        CyDelay(10);
        }   
}

int main (void)
{
    int lowTemp = true;
    int lowCurrent = true;
    int stopPlease = false;
    int time;
    char string[20];
    
    AMux_1_Start();
    Opamp_1_Start();
    PGA_1_Start();
    Timer_1_Start();
    UART_1_Start();
    RED_LED_Write(0);
    RELAY_Write(0);
    ADC_1_Start();
    I2C_1_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    uint32 vmShunt;
    float vmShmV;
    uint32 vmBat;
    float vmBatmV;
    
    
    uint8 batteryArray[32];
    uint8 resistorArray[32];
    int addr;
    char string1[20];
    uint32 rxData;
    
    
    sprintf(string1,"\r\n Enter G to Start Test, Enter S to Stop \r\n");
    UART_1_UartPutString(string1);

    for(;;)
    {
        time = Timer_1_ReadCounter();
        RED_LED_Write(1);
        CyDelay(1000);
        RELAY_Write(0);
        rxData = UART_1_UartGetChar();
        
        if (rxData == 71)  //Type Capital G into Putty
        {
            sprintf(string1,"\r\n Beginning the Test... \r\n");
            UART_1_UartPutString(string1);
            RED_LED_Write(1);
            RELAY_Write(1);
            Timer_1_Start();
            Print_headers(35);
           
            while(lowTemp && lowCurrent && !stopPlease){
                time = Timer_1_ReadCounter();
                sprintf(string1,"\r\n %d, ", time);
                
                UART_1_UartPutString(string1);  
                AMux_1_Select(1);
                ADC_1_StartConvert();
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vmShunt = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vmShmV = ADC_1_CountsTo_mVolts(0, vmShunt);
                //vmShmV = vmShmV*60.0/(32.0*50.0);
                sprintf(string1, "%3.3f, ", vmShmV);
                UART_1_UartPutString(string1);
                
                AMux_1_Select(0);
                ADC_1_StartConvert();
                ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
                vmShunt = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vmBatmV = ADC_1_CountsTo_mVolts(0, vmShunt);
                vmBatmV = vmBatmV/1000.0;
                sprintf(string1, "%3.3f, ", vmBatmV);
                UART_1_UartPutString(string1);
                
                I2C_1_I2CMasterReadBuf(0x08, batteryArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                for(uint i = 0; i < 32; i=i+2){
                    sprintf(string1, "%d.%d, ", batteryArray[i], batteryArray[i+1]);
                    UART_1_UartPutString(string1);    
                }
                I2C_1_I2CMasterReadBuf(0x09, resistorArray, 32, I2C_1_I2C_MODE_COMPLETE_XFER);
                for(uint i = 0; i < 32; i=i+2){
                    sprintf(string1, "%d.%d, ", resistorArray[i], resistorArray[i+1]);
                    UART_1_UartPutString(string1);    
                }
                sprintf(string1, "\r\n");
                UART_1_UartPutString(string1);
                rxData = UART_1_UartGetChar();
                CyDelay(500);
                                
                
                if (rxData == 83){
                    stopPlease = true;
                    Shutdown_Test();
                }
            }
        }
        CyDelay(10);
        
        
        
    }
}

/* [] END OF FILE */
