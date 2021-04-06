/*******************************************************************************
* File Name: bgRef.c  
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
#include "bgRef.h"

static bgRef_BACKUP_STRUCT  bgRef_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: bgRef_Sleep
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
*  \snippet bgRef_SUT.c usage_bgRef_Sleep_Wakeup
*******************************************************************************/
void bgRef_Sleep(void)
{
    #if defined(bgRef__PC)
        bgRef_backup.pcState = bgRef_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            bgRef_backup.usbState = bgRef_CR1_REG;
            bgRef_USB_POWER_REG |= bgRef_USBIO_ENTER_SLEEP;
            bgRef_CR1_REG &= bgRef_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(bgRef__SIO)
        bgRef_backup.sioState = bgRef_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        bgRef_SIO_REG &= (uint32)(~bgRef_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: bgRef_Wakeup
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
*  Refer to bgRef_Sleep() for an example usage.
*******************************************************************************/
void bgRef_Wakeup(void)
{
    #if defined(bgRef__PC)
        bgRef_PC = bgRef_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            bgRef_USB_POWER_REG &= bgRef_USBIO_EXIT_SLEEP_PH1;
            bgRef_CR1_REG = bgRef_backup.usbState;
            bgRef_USB_POWER_REG &= bgRef_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(bgRef__SIO)
        bgRef_SIO_REG = bgRef_backup.sioState;
    #endif
}


/* [] END OF FILE */
