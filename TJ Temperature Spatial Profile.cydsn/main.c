	/* ========================================
 *
 * Christian Gonzalez, UC Davis, 2020
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

/* Initialize string for UART data transmission */
//char string[16];

int main(void)
{  

    
    /* Temperature Array */
    int32 vmeas;
    
    int32 vmeasV;
    int32 decV;
    int32 fracV;
    
    /* I2C Read Buffer */
    uint8 rdBuf[2];
    int8 bVoltage[2];
    
    /* Enable global interrupts. */
    CyGlobalIntEnable;
    
    /* Initialize I2C Buffer */
    I2C_1_I2CSlaveInitReadBuf(rdBuf, 2);
    I2C_1_I2CSlaveClearReadBuf();
    I2C_1_I2CSlaveClearReadStatus();
    
    /* Initialize all PSoC components */

    PGA_1_Start();
    ADC_1_Start();
    I2C_1_Start();
    UART_1_Start(); 
    
    // Read ADC offset voltage (CDS)  
    char string[30];
        
    for(;;)
    {
                        
        /* Scan through MUX channels, get temperature and send data */
                      
        ADC_1_StartConvert();
        ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
        vmeas = ADC_1_GetResult32(0);
        ADC_1_StopConvert();
        vmeasV = ADC_1_CountsTo_mVolts(0, vmeas);
        
                   
	    //Determine decimal portion of temperature by dividing temperature by 100
        decV = vmeasV/1000;
        
        // Determine fraction portion of temperature by subtracting decimal portion from result 
        fracV = vmeasV - (decV * 100);
        
        // If fractional temperature is negative make it positive 
        if(fracV < 0) {
            fracV *= -1;
        }
        /* Put temperature parts into an array */
        bVoltage[0] = decV;
        bVoltage[1] = fracV;
        
        // Get thermistor number
        // i = (chan/2) + 1;
        // UART Transmission for Debug
        
         sprintf(string, "Voltage = %ld.%.2ld", decV, fracV); 
         UART_1_UartPutString(string);
         UART_1_UartPutString("\n\r");
        
                /* Copy temperature data to I2C read buffer */
        memcpy(rdBuf, bVoltage, 2);
        /* Clear I2C read buffer and any previous status */
        I2C_1_I2CSlaveClearReadBuf();
        I2C_1_I2CSlaveClearReadStatus(); 
            
        } 
       
}


/* [] END OF FILE */
