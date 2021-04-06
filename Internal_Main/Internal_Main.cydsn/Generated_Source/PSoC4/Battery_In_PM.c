/*******************************************************************************
* File Name: Battery_in.c  
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
#include "Battery_in.h"

static Battery_in_BACKUP_STRUCT  Battery_in_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Battery_in_Sleep
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
*  \snippet Battery_in_SUT.c usage_Battery_in_Sleep_Wakeup
*******************************************************************************/
void Battery_in_Sleep(void)
{
    #if defined(Battery_in__PC)
        Battery_in_backup.pcState = Battery_in_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Battery_in_backup.usbState = Battery_in_CR1_REG;
            Battery_in_USB_POWER_REG |= Battery_in_USBIO_ENTER_SLEEP;
            Battery_in_CR1_REG &= Battery_in_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Battery_in__SIO)
        Battery_in_backup.sioState = Battery_in_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Battery_in_SIO_REG &= (uint32)(~Battery_in_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Battery_in_Wakeup
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
*  Refer to Battery_in_Sleep() for an example usage.
*******************************************************************************/
void Battery_in_Wakeup(void)
{
    #if defined(Battery_in__PC)
        Battery_in_PC = Battery_in_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Battery_in_USB_POWER_REG &= Battery_in_USBIO_EXIT_SLEEP_PH1;
            Battery_in_CR1_REG = Battery_in_backup.usbState;
            Battery_in_USB_POWER_REG &= Battery_in_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Battery_in__SIO)
        Battery_in_SIO_REG = Battery_in_backup.sioState;
    #endif
}


/* [] END OF FILE */
