/*******************************************************************************
* File Name: VBatHigh.c  
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
#include "VBatHigh.h"

static VBatHigh_BACKUP_STRUCT  VBatHigh_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: VBatHigh_Sleep
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
*  \snippet VBatHigh_SUT.c usage_VBatHigh_Sleep_Wakeup
*******************************************************************************/
void VBatHigh_Sleep(void)
{
    #if defined(VBatHigh__PC)
        VBatHigh_backup.pcState = VBatHigh_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            VBatHigh_backup.usbState = VBatHigh_CR1_REG;
            VBatHigh_USB_POWER_REG |= VBatHigh_USBIO_ENTER_SLEEP;
            VBatHigh_CR1_REG &= VBatHigh_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VBatHigh__SIO)
        VBatHigh_backup.sioState = VBatHigh_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        VBatHigh_SIO_REG &= (uint32)(~VBatHigh_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: VBatHigh_Wakeup
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
*  Refer to VBatHigh_Sleep() for an example usage.
*******************************************************************************/
void VBatHigh_Wakeup(void)
{
    #if defined(VBatHigh__PC)
        VBatHigh_PC = VBatHigh_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            VBatHigh_USB_POWER_REG &= VBatHigh_USBIO_EXIT_SLEEP_PH1;
            VBatHigh_CR1_REG = VBatHigh_backup.usbState;
            VBatHigh_USB_POWER_REG &= VBatHigh_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VBatHigh__SIO)
        VBatHigh_SIO_REG = VBatHigh_backup.sioState;
    #endif
}


/* [] END OF FILE */
