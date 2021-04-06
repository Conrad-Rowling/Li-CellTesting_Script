/*******************************************************************************
* File Name: Shunt_in.c  
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
#include "Shunt_in.h"

static Shunt_in_BACKUP_STRUCT  Shunt_in_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Shunt_in_Sleep
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
*  \snippet Shunt_in_SUT.c usage_Shunt_in_Sleep_Wakeup
*******************************************************************************/
void Shunt_in_Sleep(void)
{
    #if defined(Shunt_in__PC)
        Shunt_in_backup.pcState = Shunt_in_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Shunt_in_backup.usbState = Shunt_in_CR1_REG;
            Shunt_in_USB_POWER_REG |= Shunt_in_USBIO_ENTER_SLEEP;
            Shunt_in_CR1_REG &= Shunt_in_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Shunt_in__SIO)
        Shunt_in_backup.sioState = Shunt_in_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Shunt_in_SIO_REG &= (uint32)(~Shunt_in_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Shunt_in_Wakeup
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
*  Refer to Shunt_in_Sleep() for an example usage.
*******************************************************************************/
void Shunt_in_Wakeup(void)
{
    #if defined(Shunt_in__PC)
        Shunt_in_PC = Shunt_in_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Shunt_in_USB_POWER_REG &= Shunt_in_USBIO_EXIT_SLEEP_PH1;
            Shunt_in_CR1_REG = Shunt_in_backup.usbState;
            Shunt_in_USB_POWER_REG &= Shunt_in_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Shunt_in__SIO)
        Shunt_in_SIO_REG = Shunt_in_backup.sioState;
    #endif
}


/* [] END OF FILE */
