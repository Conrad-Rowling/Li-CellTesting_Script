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
#include "stdio.h"

/***************************************
*        Function Prototypes
***************************************/

static void WaitForOperation();
static void WriteRegister(uint8 reg_addr, uint8 data);
static uint8 ReadRegister(uint8 reg_addr);
void InitInterrupts();
void DoubleTapHandler();
void MotionWakeHandler();
void SleepTimerHandler();
void EnableDoubleTap();
void EnableMotionWake();
void EnableTempRead();
int16_t TempRead();
int16_t GetAccelerationDataX();
int16_t GetAccelerationDataY();
int16_t GetAccelerationDataZ();


/***************************************
*   Variables and Registers Defined
****************************************/

#define STATUS_REG_AUX (0x07)
#define OUT_ADC1_L (0x08)
#define OUT_ADC1_H (0x09)
#define OUT_ADC2_L (0x0A)
#define OUT_ADC2_H (0x0B)
#define OUT_ADC3_L (0x0C)
#define OUT_ADC3_H (0x0D)
#define WHO_AM_I (0x0F)
#define CTRL_REG0 (0x1E)
#define TEMP_CFG_REG (0x1F)
#define CTRL_REG1 (0x20)
#define CTRL_REG2 (0x21)
#define CTRL_REG3 (0x22)
#define CTRL_REG4 (0x23)
#define CTRL_REG5 (0x24)
#define CTRL_REG6 (0x25)
#define REFERENCE (0x26)
#define STATUS_REG (0x27)
#define OUT_X_L (0)
#define OUT_X_H (16)
#define OUT_Y_L (12)
#define OUT_Y_H (31)
#define OUT_Z_L (0x2C)
#define OUT_Z_H (0x2D)
#define FIFO_CTRL_REG (0x2E)
#define FIFO_SRC_REG (0x2F)
#define INT1_CFG (0x30)
#define INT1_SRC (0x31)
#define INT1_THS (0x32)
#define INT1_DURATION (0x33)
#define INT2_CFG (0x34)
#define INT2_SRC (0x35)
#define INT2_THS (0x36)
#define INT2_DURATION (0x37)
#define CLICK_CFG (0x38)
#define CLICK_SRC (0x39)
#define CLICK_THS (0x3A)
#define TIME_LIMIT (0x3B)
#define TIME_LATENCY (0x3C)
#define TIME_WINDOW (0x3D)
#define ACT_THS (0x3E)
#define ACT_DUR (0x3F)

/* Structure for setting up the buffer in I2C transactions */
static cy_stc_scb_i2c_master_xfer_config_t register_setting;
static uint8 rbuff[2]; // Read Buffer
static uint8 wbuff[2]; // Write Buffer  


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: WaitForOperation
********************************************************************************
*
* Function that checks to make sure either a write or read function has completed
*
********************************************************************************/
static void WaitForOperation()
{
    while( 0 != (SensorBus_MasterGetStatus() & CY_SCB_I2C_MASTER_BUSY)){}
    {
        CyDelayUs(1); // Keep Waiting
    }
}


/*******************************************************************************
* Function Name: WriteRegister
********************************************************************************
*
* To write, you want to write 2 values: 
*     (1) The register address that you want to write to (Parameter 1) "register address"
*     (2) The value that you wish to write to the register (Parameter 2)
*
********************************************************************************/
static void WriteRegister(uint8 reg_addr, uint8 data)
{
    wbuff[0] = reg_addr; // Assign the first element to be the register you want to write to (Parameter 1) "register address"
    wbuff[1] = data;     // Assign the second element to be the value you wish to write to the register (Parameter 2)
    
    register_setting.buffer = wbuff;
    register_setting.bufferSize = 2;
    register_setting.xferPending = false;
    
    SensorBus_MasterWrite(&register_setting);
    WaitForOperation();
}


/*******************************************************************************
* Function Name: ReadRegister
********************************************************************************
*
* To read, you must:
*     (1) Write the register address you want to read from the slave address device (LIS3DH)
*     (2) Use MasterReadBuf to store what is contained in the register into the read buffer
*
********************************************************************************/
static uint8 ReadRegister(uint8 reg_addr)
{
    wbuff[0] = reg_addr;    // Buffer that will contain the register that will be read from
    
    register_setting.buffer = wbuff;
    register_setting.bufferSize = 1;
    register_setting.xferPending = true;
    
    SensorBus_MasterWrite(&register_setting);
    WaitForOperation();
    
    register_setting.buffer = rbuff;  // Buffer that will store the value read from the register
    register_setting.xferPending = false;
    
    SensorBus_MasterRead(&register_setting);
    WaitForOperation();
    
    return rbuff[0];    // Return what was read and stored in the read buffer
}

/*******************************************************************************
* Function Name: InitInterrupts
********************************************************************************
*
* Initializes the DoubleTap and InHand Interrupts
*
********************************************************************************/


/*******************************************************************************
* Function Name: DoubleTapHandler
********************************************************************************
*
* Interrupt service routine for DoubleTap_IRQ
* It is triggered by the INT1 pin of the LIS3DH
*
********************************************************************************/


/*******************************************************************************
* Function Name: InHandHandler
********************************************************************************
*
* Interrupt service routine for InHand_IRQ
* It is triggered by the INT2 pin of the LIS3DH
*
********************************************************************************/


/*******************************************************************************
* Function Name: EnableDoubleTap
********************************************************************************
*
* Writes to LIS3DH registers to configure setting for double tap feature
*
********************************************************************************/
void EnableDoubleTap()
{
    /* Write to CTRL_REG1 to set ODR (data rate) to 400Hz (recommended setting for double tap detection */
    WriteRegister(CTRL_REG1, 0x77);
    /* Write to register CTRL_REG3 to enable Click on interrupt 1 */
    WriteRegister(CTRL_REG3, 0x80);
    /* Write to INT1_CFG to enable double tap interrupt on this INT pin */
    WriteRegister(INT1_CFG, 0x3F);
    /* Write to register CLICK_CFG to enable double tap on XYZ axes */
    WriteRegister(CLICK_CFG, 0x2A);
    /* Write to register CLICK_THS to set click threshold */
    WriteRegister(CLICK_THS, 0x7F);
    /* Write to register TIME_LIMIT to set time limit to 127ms */
    WriteRegister(TIME_LIMIT, 0x33);
    /* Write to register TIME_LATENCY to set time latency to 20ms */
    WriteRegister(TIME_LATENCY, 0x20);
    /* Write to register TIME_WINDOW to set time window to 300ms */
    WriteRegister(TIME_WINDOW, 0x78);
}

/*******************************************************************************
* Function Name: EnableMotionWake
********************************************************************************
*
* Writes to LIS3DH registers to configure setting for motion wake feature
*
********************************************************************************/
void EnableMotionWake()
{
    /* Write to CTRL_REG6 to set enable interrupt 2 function on INT2 pin */
    WriteRegister(CTRL_REG6, 0x20);
    /* Write to INT2_CFG to enable 6D movement detection */
    WriteRegister(INT2_CFG, 0x7F);
    /* Write to INT2_THS to set threshold for INT2 */
    WriteRegister(INT2_THS, 0x22);
    /* Write to INT2_DURATION to set minimum duration for interrupt 2 to be recognized to 317ms */
    WriteRegister(INT2_DURATION, 0x7F);
}


/*******************************************************************************
* Function Name: EnableTempRead
********************************************************************************
*
* Writes to LIS3DH registers to configure setting for temperature reading
*
********************************************************************************/
void EnableTempRead()
{
    /* Write to TEMP_CFG_REG to enable temperature reading and ADC */
    WriteRegister(TEMP_CFG_REG, 0xC0);
    /* Write to CTRL_REG4 to enable BDU (block data update */
    WriteRegister(CTRL_REG4, 0x80);
}


/*******************************************************************************
* Function Name: TempRead
********************************************************************************
*
* Reads temperature of accelerometer
*
********************************************************************************/
int16_t TempRead()
{   
    int16_t temp_H;
    int16_t temp_L;
    int16_t temp;
    
    /* Read registers from accelerometer and format output */
    temp_H = ReadRegister(OUT_ADC3_H);        
    temp_H = temp_H << 8;
    temp_L = ReadRegister(OUT_ADC3_L);       
    temp = temp_H | temp_L;
    temp = (temp >> 6) + 25;
    CyDelay(250);
    
    /* Return the temperature value */
    return temp;
}


/*******************************************************************************
* Function Name: GetAccelerationDataX
********************************************************************************
*
* Reads x-axis acceleration data of accelerometer
*
********************************************************************************/
int16_t GetAccelerationDataX()
{   
    int16_t accel_H;
    int16_t accel_L;
    int16_t accel;
    
    /* Read registers from accelerometer and format output */
    accel_H = ReadRegister(OUT_X_H);        
    accel_H = accel_H << 8;
    accel_L = ReadRegister(OUT_X_L);       
    accel = accel_H | accel_L;
    accel = (accel >> 6) * (4*9.8/1000);
    //CyDelay(250);
    
    /* Return the x-axis acceleration value */
    return accel;
}


/*******************************************************************************
* Function Name: GetAccelerationDataY
********************************************************************************
*
* Reads y-axis acceleration data of accelerometer
*
********************************************************************************/
int16_t GetAccelerationDataY()
{   
    int16_t accel_H;
    int16_t accel_L;
    int16_t accel;
    
    /* Read registers from accelerometer and format output */
    accel_H = ReadRegister(OUT_Y_H);        
    accel_H = accel_H << 8;
    accel_L = ReadRegister(OUT_Y_L);       
    accel = accel_H | accel_L;
    accel = (accel >> 6) * (4*9.8/1000);
    //CyDelay(250);
    
    /* Return the y-axis acceleration value */
    return accel;
}


/*******************************************************************************
* Function Name: GetAccelerationDataZ
********************************************************************************
*
* Reads z-axis acceleration data of accelerometer
*
********************************************************************************/
int16_t GetAccelerationDataZ()
{   
    int16_t accel_H;
    int16_t accel_L;
    int16_t accel;
    
    /* Read registers from accelerometer and format output */
    accel_H = ReadRegister(OUT_Z_H);        
    accel_H = accel_H << 8;
    accel_L = ReadRegister(OUT_Z_L);       
    accel = accel_H | accel_L;
    accel = (accel >> 6) * (4*9.8/1000);
    //CyDelay(250);
    
    /* Return the z-axis acceleration value */
    return accel;
}
/* [] END OF FILE */
