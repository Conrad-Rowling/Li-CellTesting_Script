
/*******************************************************************************
* File Name: cyfitter_cfg.c
* 
* PSoC Creator  4.4
*
* Description:
* This file contains device initialization code.
* Except for the user defined sections in CyClockStartupError(), this file should not be modified.
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "CyLFClk.h"
#include "cyfitter_cfg.h"
#include "cyapicallbacks.h"


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #ifndef CY_CFG_SECTION
        #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    #endif
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif

#ifndef CYCODE
    #define CYCODE
#endif
#ifndef CYDATA
    #define CYDATA
#endif
#ifndef CYFAR
    #define CYFAR
#endif
#ifndef CYXDATA
    #define CYXDATA
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}




/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u
#define CYCLOCKSTART_FLL_ERROR   4u
#define CYCLOCKSTART_WCO_ERROR   5u


#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

#ifdef CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK
    CY_CFG_Clock_Startup_ErrorCallback();
#else
    /*  If not using CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK, place your clock startup code here. */
    /* `#START CyClockStartupError` */



    /* `#END` */

    while(1) {}
#endif /* CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK */
}
#endif



/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*   Performs the initialization of all of the clocks in the device based on the
*   settings in the Clock tab of the DWR.  This includes enabling the requested
*   clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void ClockSetup(void);
CY_CFG_SECTION
static void ClockSetup(void)
{

	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0012u));
	/* Update IMO to new clock speed. */
	CySysClkWriteImoFreq(24u);

	/* Setup phase aligned clocks */
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL0, 0x00000100u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF40u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL1, 0x00000100u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF41u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_24_5_CTL, 0x02DC6B00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FFC0u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL2, 0x00000E00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF42u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL3, 0x00001000u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF43u);

	/* CYDEV_CLK_SELECT Starting address: CYDEV_CLK_SELECT */
	CY_SET_REG32((void *)(CYREG_CLK_SELECT), 0x00000020u);

	/* CYDEV_PERI_PCLK_CTL12 Starting address: CYDEV_PERI_PCLK_CTL12 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL12), 0x00000041u);

	/* CYDEV_PERI_PCLK_CTL4 Starting address: CYDEV_PERI_PCLK_CTL4 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL4), 0x000000C0u);

	/* CYDEV_PERI_PCLK_CTL2 Starting address: CYDEV_PERI_PCLK_CTL2 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL2), 0x00000042u);

	/* CYDEV_PERI_PCLK_CTL0 Starting address: CYDEV_PERI_PCLK_CTL0 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL0), 0x00000043u);

	(void)CyIntSetVector(11u, &CySysTimerIsr);
	CyIntEnable(11u);
	CY_SET_REG32((void *)(CYREG_WCO_WDT_CONFIG), 0x00000000u);
	CySysClkSetTimerSource(CY_SYS_CLK_TIMER_SRC_ILO);
	/* Set Flash Cycles based on newly configured 24.00MHz HFCLK. */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0011u));
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB0_CTB_CTRL, 0x80000000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB0_OA0_SW, 0x20000008u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB0_OA1_SW, 0x00080080u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB0_CTBBUS_SW, 0x00200100u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB1_CTB_CTRL, 0x80000000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTB1_OA0_SW, 0x00040010u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_ART_CTRL, 0x80000000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_ART_SARMUXVPLUS_SW, 0x01000000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_ART_CTB0VREF_SW, 0x00020000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_PASS_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_PRB_CTRL, 0x80000001u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_PRB_REF0, 0x000000F1u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_DSAB_DSAB_CTRL, 0x00000020u);
	SetAnalogRoutingPumps(1);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint32 regValue = CY_GET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL));
	if (enabled != 0u)
	{
		regValue |= 0x80000000u;
	}
	else
	{
		regValue &= ~0x80000000u;
	}
	CY_SET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL), regValue);
}


#define CY_AMUX_UNUSED CYREG_CM0P_ROM_DWT
/*******************************************************************************
* Function Name: AMux_2_Set
********************************************************************************
* Summary:
*  This function is used to set a particular channel as active on the AMux.
*
* Parameters:  
*   channel - The mux channel input to set as active
*
* Return:
*   void
*
*******************************************************************************/
void AMux_2_Set(uint8 channel)
{
	switch (channel) {
		case 0u:
			CY_SET_REG32((void CYXDATA *)CYREG_ART_SARMUXVPLUS_SW, (0x10u));
			break;
		case 1u:
			CY_SET_REG32((void CYXDATA *)CYREG_ART_SARMUXVPLUS_SW, (0x01u));
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name: AMux_2_Unset
********************************************************************************
* Summary:
*  This function is used to clear a particular channel from being active on the
*  AMux.
*
* Parameters:  
*   channel - The mux channel input to mark inactive
*
* Return:
*   void
*
*******************************************************************************/
void AMux_2_Unset(uint8 channel)
{
	switch (channel) {
		case 0u:
			CY_SET_REG32((void CYXDATA *)CYREG_ART_SARMUXVPLUS_SW_CLR, (0x10u));
			break;
		case 1u:
			CY_SET_REG32((void CYXDATA *)CYREG_ART_SARMUXVPLUS_SW_CLR, (0x01u));
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name: AMux_1_Set
********************************************************************************
* Summary:
*  This function is used to set a particular channel as active on the AMux.
*
* Parameters:  
*   channel - The mux channel input to set as active
*
* Return:
*   void
*
*******************************************************************************/
void AMux_1_Set(uint8 channel)
{
	switch (channel) {
		case 0u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_OA0_SW, (0x04u));
			break;
		case 1u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_CTBBUS_SW, (0x20u));
			break;
		case 2u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_CTBBUS_SW, (0x10u));
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name: AMux_1_Unset
********************************************************************************
* Summary:
*  This function is used to clear a particular channel from being active on the
*  AMux.
*
* Parameters:  
*   channel - The mux channel input to mark inactive
*
* Return:
*   void
*
*******************************************************************************/
void AMux_1_Unset(uint8 channel)
{
	switch (channel) {
		case 0u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_OA0_SW_CLEAR, (0x04u));
			break;
		case 1u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_CTBBUS_SW_CLEAR, (0x20u));
			break;
		case 2u:
			CY_SET_REG32((void CYXDATA *)CYREG_CTB0_CTBBUS_SW_CLEAR, (0x10u));
			break;
		default:
			break;
	}
}



/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_SECTION
void cyfitter_cfg(void)
{
	/* Disable interrupts by default. Let user enable if/when they want. */
	CyGlobalIntDisable;

	{
		/* HSIOM Starting address: CYDEV_HSIOM_BASE */
		CY_SET_REG32((void *)(CYDEV_HSIOM_BASE), 0x000000EEu);
		CY_SET_REG32((void *)(CYREG_HSIOM_PORT_SEL3), 0xEE000099u);

		/* PASS_SAR_TRIG_SEL Starting address: CYDEV_PASS_SAR_TRIG_SEL */
		CY_SET_REG32((void *)(CYREG_PASS_SAR_TRIG_SEL), 0x00000000u);

	}

	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	/* IOPINS0_0 Starting address: CYDEV_GPIO_PRT0_BASE */
	CY_SET_REG32((void *)(CYREG_GPIO_PRT0_PC), 0x00000DB6u);

	/* IOPINS0_2 Starting address: CYDEV_GPIO_PRT2_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT2_BASE), 0x000000BBu);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT2_PC2), 0x000000BBu);

	/* IOPINS0_3 Starting address: CYDEV_GPIO_PRT3_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT3_BASE), 0x000000C2u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT3_PC), 0x00900031u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT3_PC2), 0x00000002u);


	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

}
