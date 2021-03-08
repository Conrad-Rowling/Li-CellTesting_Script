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
#include "project.h"
#include "LIS3DH.h"
#include "stdio.h"
#include "stdlib.h"

bool lowTemp = true;
bool lowCurrent = true;
bool stopPlease = false;

void Shutdown_Test()
{
    Cy_GPIO_Write(RELAY_0_PORT, RELAY_0_NUM, 0);
    Cy_GPIO_Write(RED_LED_0_PORT, RED_LED_0_NUM,1);
}
void Print_headers(uint length)
{
    char hstr[60]; 
    sprintf(hstr,"\r\n");
    UART_PutString(hstr);
    
    for (uint i = 0; i < length; i++){
        sprintf(hstr,"T%d, T%d-1, ", i, i);
        UART_PutString(hstr);
        CyDelay(10);
        }
    sprintf(hstr,"batV, Current \r\n");
    UART_PutString(hstr);
    
}
int main(void)
{
    /* Enable global interrupts. */
    __enable_irq();
    
    Timer_Start();
    /* Start Communication Blocks */
    SensorBus_Start();
    UART_Start();
    uint32 vmShunt;
    uint32 vmShV;
    
    
    uint8 tempArray[14];
    int addr;
    /* String for temperature output to Putty */
    char string1[20];
    uint32 rxData;

    Cy_GPIO_Write(RED_LED_0_PORT, RED_LED_0_NUM,1);
    ADC_1_Start();
    sprintf(string1,"\r\n Enter G to Start Test, Enter S to Stop \r\n");
    UART_PutString(string1);
    
    for(;;)
    {          
        CyDelay(1000);
        rxData = Cy_SCB_UART_Get(UART_HW);
        if (rxData == 71)  //Type Capital G into Putty
        {
            sprintf(string1,"\r\n Beginning the Test... \r\n");
            Cy_GPIO_Write(RELAY_0_PORT, RELAY_0_NUM, 1);
            Cy_GPIO_Write(RED_LED_0_PORT, RED_LED_0_NUM,0);
            UART_PutString(string1);
            Timer_Start();
            Print_headers(14);
           
            while(lowTemp && lowCurrent && !stopPlease){
                ADC_1_StartConvert();
                ADC_1_IsEndConversion(CY_SAR_WAIT_FOR_RESULT);
                vmShunt = ADC_1_GetResult32(0);
                ADC_1_StopConvert();
                vmShV = ADC_1_CountsTo_mVolts(0, vmShunt);
                vmShV = 
                
                
                register_setting.slaveAddress = 0x08;
                addr = 0x00;
                for(uint i = 0; i < 14; i=i+2){
                    tempArray[i] = ReadRegister(addr);
                    tempArray[i+1] = ReadRegister(addr);
                    addr = addr + 2;
                    sprintf(string1, " %d.%d,", tempArray[i],tempArray[i+1]);
                    UART_PutString(string1);
                }
                register_setting.slaveAddress = 0x09;
                addr = 0x00;
                for(uint i = 0; i < 14; i=i+2){
                    tempArray[i] = ReadRegister(addr);
                    tempArray[i+1] = ReadRegister(addr);
                    addr = addr + 2;
                    sprintf(string1, " %d.%d,", tempArray[i],tempArray[i+1]);
                    UART_PutString(string1);
                }
                
                CyDelay(2000);
                
                rxData = Cy_SCB_UART_Get(UART_HW);
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
