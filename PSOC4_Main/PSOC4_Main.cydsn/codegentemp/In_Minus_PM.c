/*******************************************************************************
* File Name: In_Minus.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "In_Minus.h"

static In_Minus_BACKUP_STRUCT  In_Minus_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: In_Minus_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet In_Minus_SUT.c usage_In_Minus_Sleep_Wakeup
*******************************************************************************/
void In_Minus_Sleep(void)
{
    #if defined(In_Minus__PC)
        In_Minus_backup.pcState = In_Minus_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            In_Minus_backup.usbState = In_Minus_CR1_REG;
            In_Minus_USB_POWER_REG |= In_Minus_USBIO_ENTER_SLEEP;
            In_Minus_CR1_REG &= In_Minus_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(In_Minus__SIO)
        In_Minus_backup.sioState = In_Minus_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        In_Minus_SIO_REG &= (uint32)(~In_Minus_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: In_Minus_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to In_Minus_Sleep() for an example usage.
*******************************************************************************/
void In_Minus_Wakeup(void)
{
    #if defined(In_Minus__PC)
        In_Minus_PC = In_Minus_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            In_Minus_USB_POWER_REG &= In_Minus_USBIO_EXIT_SLEEP_PH1;
            In_Minus_CR1_REG = In_Minus_backup.usbState;
            In_Minus_USB_POWER_REG &= In_Minus_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(In_Minus__SIO)
        In_Minus_SIO_REG = In_Minus_backup.sioState;
    #endif
}


/* [] END OF FILE */
