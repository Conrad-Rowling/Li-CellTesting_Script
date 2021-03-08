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
    
    for (uint i = 0; i < length; i++){
        sprintf(hstr,"T%d, T%d-1, ", i, i);
        UART_1_UartPutString(hstr);
        CyDelay(10);
        }
    sprintf(hstr,"batV, Current \r\n");
    UART_1_UartPutString(hstr);
    
}

int main (void)
{
    int time;
    char string[20];
    Opamp_1_Start();
    PGA_1_Start();
    Timer_1_Start();
    UART_1_Start();
    RED_LED_Write(0);
    //RELAY_Write(0);
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        time = Timer_1_ReadCounter();
        sprintf(string, "Voltage = %d \r\n", time); 
        UART_1_UartPutString(string);
        UART_1_UartPutString("\n\r");
        RED_LED_Write(0);
        CyDelay(1000);
        RED_LED_Write(1);
        /* Place your application code here. */
        
        
        
    }
}

/* [] END OF FILE */
