/***************************************************************************//**
* \file     PGA_2_PM.c  
* \version  1.10
*
* \brief
*  This file provides the power management source code to the API for PGA_P4 
*  Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PGA_2_PVT.h"


/*******************************************************************************
* Function Name: PGA_2_SaveConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void PGA_2_SaveConfig(void)
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: PGA_2_RestoreConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void PGA_2_RestoreConfig(void)
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: PGA_2_Sleep
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function disables 
*  component's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Deep Sleep state.
*
*  \internal
*   The PGA_2_backup.enableState is modified 
*   depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void PGA_2_Sleep(void)
{
    #if(!PGA_2_CHECK_DEEPSLEEP_SUPPORT)
        if((PGA_2_OA_RES_CTRL_REG & PGA_2_OA_PWR_MODE_MASK) != 0u)
        {
            PGA_2_internalGainPower |= PGA_2_ENABLED;
            PGA_2_Stop();
        }
        else /* The component is disabled */
        {
            PGA_2_internalGainPower &= (uint32) ~PGA_2_ENABLED;
        }
        /* Save the configuration */
        PGA_2_SaveConfig();
    #endif /* (PGA_2_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: PGA_2_Wakeup
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function enables
*  block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Active state.
*
*  \internal
*   The PGA_2_backup.enableState is used to 
*   restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void PGA_2_Wakeup(void)
{
    #if(!PGA_2_CHECK_DEEPSLEEP_SUPPORT)
        /* Restore the configurations */
        PGA_2_RestoreConfig();
        /* Enables the component operation */
        if((PGA_2_internalGainPower & PGA_2_ENABLED) != 0u)
        {
            PGA_2_Enable();
        } /* Do nothing if component was disabled before */
    #endif /* (PGA_2_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
