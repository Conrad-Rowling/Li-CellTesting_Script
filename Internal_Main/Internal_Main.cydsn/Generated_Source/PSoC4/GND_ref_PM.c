/*******************************************************************************
* File Name: GND_ref.c  
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
#include "GND_ref.h"

static GND_ref_BACKUP_STRUCT  GND_ref_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GND_ref_Sleep
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
*  \snippet GND_ref_SUT.c usage_GND_ref_Sleep_Wakeup
*******************************************************************************/
void GND_ref_Sleep(void)
{
    #if defined(GND_ref__PC)
        GND_ref_backup.pcState = GND_ref_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GND_ref_backup.usbState = GND_ref_CR1_REG;
            GND_ref_USB_POWER_REG |= GND_ref_USBIO_ENTER_SLEEP;
            GND_ref_CR1_REG &= GND_ref_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GND_ref__SIO)
        GND_ref_backup.sioState = GND_ref_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GND_ref_SIO_REG &= (uint32)(~GND_ref_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GND_ref_Wakeup
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
*  Refer to GND_ref_Sleep() for an example usage.
*******************************************************************************/
void GND_ref_Wakeup(void)
{
    #if defined(GND_ref__PC)
        GND_ref_PC = GND_ref_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GND_ref_USB_POWER_REG &= GND_ref_USBIO_EXIT_SLEEP_PH1;
            GND_ref_CR1_REG = GND_ref_backup.usbState;
            GND_ref_USB_POWER_REG &= GND_ref_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GND_ref__SIO)
        GND_ref_SIO_REG = GND_ref_backup.sioState;
    #endif
}


/* [] END OF FILE */
