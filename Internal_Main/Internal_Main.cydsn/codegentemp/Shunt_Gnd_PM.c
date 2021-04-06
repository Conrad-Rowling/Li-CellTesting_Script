/*******************************************************************************
* File Name: Shunt_Gnd.c  
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
#include "Shunt_Gnd.h"

static Shunt_Gnd_BACKUP_STRUCT  Shunt_Gnd_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Shunt_Gnd_Sleep
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
*  \snippet Shunt_Gnd_SUT.c usage_Shunt_Gnd_Sleep_Wakeup
*******************************************************************************/
void Shunt_Gnd_Sleep(void)
{
    #if defined(Shunt_Gnd__PC)
        Shunt_Gnd_backup.pcState = Shunt_Gnd_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Shunt_Gnd_backup.usbState = Shunt_Gnd_CR1_REG;
            Shunt_Gnd_USB_POWER_REG |= Shunt_Gnd_USBIO_ENTER_SLEEP;
            Shunt_Gnd_CR1_REG &= Shunt_Gnd_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Shunt_Gnd__SIO)
        Shunt_Gnd_backup.sioState = Shunt_Gnd_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Shunt_Gnd_SIO_REG &= (uint32)(~Shunt_Gnd_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Shunt_Gnd_Wakeup
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
*  Refer to Shunt_Gnd_Sleep() for an example usage.
*******************************************************************************/
void Shunt_Gnd_Wakeup(void)
{
    #if defined(Shunt_Gnd__PC)
        Shunt_Gnd_PC = Shunt_Gnd_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Shunt_Gnd_USB_POWER_REG &= Shunt_Gnd_USBIO_EXIT_SLEEP_PH1;
            Shunt_Gnd_CR1_REG = Shunt_Gnd_backup.usbState;
            Shunt_Gnd_USB_POWER_REG &= Shunt_Gnd_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Shunt_Gnd__SIO)
        Shunt_Gnd_SIO_REG = Shunt_Gnd_backup.sioState;
    #endif
}


/* [] END OF FILE */
