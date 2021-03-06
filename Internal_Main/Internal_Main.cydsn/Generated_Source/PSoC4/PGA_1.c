/***************************************************************************//**
* \file     PGA_1.c
* \version  1.10
*
* \brief
*  This file provides the source code to the API for the PGA_P4 Component
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PGA_1_PVT.h"


uint8 PGA_1_initVar = 0u; /**< Describes the init state of the component */

uint32 PGA_1_internalGainPower = 0u; /**< Stores component Gain, Power and Enable values */

/***************************************************************************//**
* Compensation table 
*
* There is a feedback compensation capacitor recomended setting (for certain 
* gain and power setting) under the mask 0x0F000000u
* or (PGA_1_C_FB_MASK)
*
* Also there is an OpAmp compensation recomended setting (for certain 
* gain and power setting) under the mask 0x00000003u
* or (PGA_1_GET_OA_COMP_TRIM)
*
* There is only 6 values for whole gain range because the recommended 
* values are for each pair of adjacent gain values, e.g.:
* the first (index = 0) value is for gain = 1 and 1.4,
* the second (index = 1) value is for gain = 2 and 2.8,and so on,
* and the sixth (index = 5) value is for gain = 32 only.
*******************************************************************************/
const uint32 PGA_1_compTab[PGA_1_COMP_TAB_HEIGHT][PGA_1_COMP_TAB_WIDTH] =
{
#if (PGA_1_CHECK_OUTPUT_MODE) /* Class AB */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x07000002u, 0x09000002u, 0x09000002u},
    {0x04000002u, 0x04000002u, 0x04000002u},
    {0x03000001u, 0x02000002u, 0x03000002u},
    {0x01000001u, 0x00000002u, 0x00000002u},
    {0x01000001u, 0x01000001u, 0x02000001u}
#else /* Class A */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x08000002u, 0x09000002u, 0x09000002u},
    {0x03000001u, 0x05000002u, 0x04000002u},
    {0x00000001u, 0x02000002u, 0x03000002u},
    {0x00000001u, 0x00000002u, 0x01000002u},
    {0x00000001u, 0x00000001u, 0x00000001u}
#endif /* PGA_1_OUTPUT_MODE */
};


/*******************************************************************************   
* Function Name: PGA_1_Init
****************************************************************************//**
*
*  Initializes component's parameters to the values set by user in the 
*  customizer of the component placed onto schematic. Usually it is called in 
*  PGA_1_Start().
*
*******************************************************************************/
void PGA_1_Init(void)
{
    /* Set default internal variable value */
    PGA_1_internalGainPower = PGA_1_DEFAULT_GAIN_POWER;
    
    /* Set default register values */
    PGA_1_CTB_CTRL_REG |= PGA_1_DEFAULT_CTB_CTRL;
    PGA_1_OA_RES_CTRL_REG &= (uint32) ~PGA_1_DEFAULT_OA_RES_CTRL_MASK;
    PGA_1_OA_RES_CTRL_REG |= PGA_1_DEFAULT_OA_RES_CTRL;
    
    /* Check if component has been enabled */
    if((PGA_1_OA_RES_CTRL_REG & PGA_1_OA_PWR_MODE_MASK) != 0u)
    {
        /* Set the default power level */
        PGA_1_Enable();
    }
    
    /* Set default gain and correspondent Cfb and OA_trim values */
    PGA_1_SetGain(PGA_1_GAIN);
}


/*******************************************************************************   
* Function Name: PGA_1_Enable
****************************************************************************//**
*
*  Powers up amplifier (to default power level or restored after 
*  previous PGA_1_Stop() call).
*  Usually it is called in PGA_1_Start().
*  
*******************************************************************************/
void PGA_1_Enable(void)
{
    PGA_1_OA_RES_CTRL_REG |= PGA_1_GET_POWER;
}


/*******************************************************************************
* Function Name: PGA_1_Start
****************************************************************************//**
*
*  Enables the amplifier operation (calls PGA_1_Enable).
*  Also on the first call (after the system reset) initializes all the component
*  related registers with default values (calls PGA_1_Init).
*
*  \globalvars
*   The PGA_1_initVar variable is used to indicate initial
*   configuration of this component. The variable is initialized to zero (0u)
*   and set to one (1u) at the first time PGA_1_Start() is called.
*   This allows to enable the component without re-initialization in all
*   subsequent calls of the PGA_1_Start() routine.
*
*******************************************************************************/
void PGA_1_Start(void)
{
    if(PGA_1_initVar == 0u)
    {
        PGA_1_Init();
        PGA_1_initVar = 1u;
    }

    PGA_1_Enable();
}


/*******************************************************************************
* Function Name: PGA_1_Stop
****************************************************************************//**
*
*  Powers down the amplifier.
*
*******************************************************************************/
void PGA_1_Stop(void)
{ 
    PGA_1_OA_RES_CTRL_REG &= (uint32)~PGA_1_OA_PWR_MODE_MASK;
}


/*******************************************************************************
* Function Name: PGA_1_SetPower
****************************************************************************//**
*
*  Sets the power level of amplifier.
*
* \param powerLevel
*  The power level setting of amplifier. Possible values:
*   * PGA_1_LOW - The lowest power consumption.
*   * PGA_1_MED - The middle setting.
*   * PGA_1_HIGH - The highest amplifier bandwidth.
*
*  \internal
*   The PGA_1_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void PGA_1_SetPower(uint32 powerLevel)
{
    uint32 locTmp;
    
    /* Save the powerLevel */
    PGA_1_internalGainPower &= (uint32) ~PGA_1_OA_PWR_MODE_MASK;
    PGA_1_internalGainPower |= powerLevel & PGA_1_OA_PWR_MODE_MASK;
    
    /* Save the rest of register bitfields */
    locTmp = PGA_1_OA_RES_CTRL_REG &
        (uint32)~(PGA_1_OA_PWR_MODE_MASK | PGA_1_C_FB_MASK);
           
    /* Set the power and the feedback capacitor values into the control register */
    PGA_1_OA_RES_CTRL_REG  = locTmp | PGA_1_GET_POWER | PGA_1_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    PGA_1_OA_COMP_TRIM_REG = PGA_1_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: PGA_1_SetGain
****************************************************************************//**
*
*  Sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* \param gainLevel
*  The gain setting of amplifier. Possible values:
*   * PGA_1_GAIN_1_00 - gain 1.00.
*   * PGA_1_GAIN_1_42 - gain 1.42.
*   * PGA_1_GAIN_2_00 - gain 2.00.
*   * PGA_1_GAIN_2_78 - gain 2.78.
*   * PGA_1_GAIN_4_00 - gain 4.00.
*   * PGA_1_GAIN_5_82 - gain 5.82.
*   * PGA_1_GAIN_8_00 - gain 8.00.
*   * PGA_1_GAIN_10_7 - gain 10.7.
*   * PGA_1_GAIN_16_0 - gain 16.0.
*   * PGA_1_GAIN_21_3 - gain 21.3.
*   * PGA_1_GAIN_32_0 - gain 32.0.
*
*  \internal
*   The PGA_1_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void PGA_1_SetGain(uint32 gainLevel)
{
    uint32 locTmp;
    
    /* Save the gainLevel */
    PGA_1_internalGainPower &= (uint32) ~PGA_1_RES_TAP_MASK;
    PGA_1_internalGainPower |= ((uint32)(gainLevel << PGA_1_RES_TAP_SHIFT)) &
                                                                 PGA_1_RES_TAP_MASK;
    /* Save the rest of register bitfields */
    locTmp = PGA_1_OA_RES_CTRL_REG &
        (uint32)~(PGA_1_RES_TAP_MASK | PGA_1_C_FB_MASK);
    
    /* Set the gain and the feedback capacitor values into the control register */
    PGA_1_OA_RES_CTRL_REG = locTmp | (PGA_1_internalGainPower &
        PGA_1_RES_TAP_MASK) | PGA_1_GET_C_FB;
    
#if (PGA_1_VREF_MODE == PGA_1_VREF_INTERNAL)
    if(PGA_1_GAIN_1_00 == gainLevel)
    {
        /* Disconnect the resistor matrix bottom from the internal Vss */
        PGA_1_OA_SW_CLEAR_REG = PGA_1_RBOT_TO_VSSA;
    }
    else
    {
        /* Connect the resistor matrix bottom to the internal Vss */
        PGA_1_OA_SW_REG = PGA_1_RBOT_TO_VSSA;
    }
#endif /* Vref Internal */
    
    /* Set the OA compensation capacitor value */
    PGA_1_OA_COMP_TRIM_REG = PGA_1_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: PGA_1_PumpControl
****************************************************************************//**
*
*  Allows the user to turn the amplifier's boost pump on or off.
*  By Default the PGA_1_Init() function turns the pump on.
*  Charge-pump must be turned on to provide
*  rail-rail input common mode. Each op amp has a charge pump that can be
*  controlled individually. The pump can be turned off for low input range
*  levels. When the pump is turned off, the pump supply will be shorted to vdda.
*  Shutting down the charge pump allows the op-amp to achieve low power modes.
*  
* \param onOff
*  The boost pump setting. Possible values:
*   * PGA_1_BOOST_OFF - Turn off the pump.
*   * PGA_1_BOOST_ON  - Turn on the pump.
*
**********************************************************************************/
void PGA_1_PumpControl(uint32 onOff)
{
    if(onOff == PGA_1_BOOST_ON)
    {
        PGA_1_OA_RES_CTRL_REG |= PGA_1_OA_PUMP_EN;
    }
    else
    {
        PGA_1_OA_RES_CTRL_REG &= (uint32)~PGA_1_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
