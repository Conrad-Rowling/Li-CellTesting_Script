/*******************************************************************************
* File Name: Amp_Out.c  
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
#include "Amp_Out.h"

static Amp_Out_BACKUP_STRUCT  Amp_Out_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Amp_Out_Sleep
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
*  \snippet Amp_Out_SUT.c usage_Amp_Out_Sleep_Wakeup
*******************************************************************************/
void Amp_Out_Sleep(void)
{
    #if defined(Amp_Out__PC)
        Amp_Out_backup.pcState = Amp_Out_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Amp_Out_backup.usbState = Amp_Out_CR1_REG;
            Amp_Out_USB_POWER_REG |= Amp_Out_USBIO_ENTER_SLEEP;
            Amp_Out_CR1_REG &= Amp_Out_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Amp_Out__SIO)
        Amp_Out_backup.sioState = Amp_Out_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Amp_Out_SIO_REG &= (uint32)(~Amp_Out_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Amp_Out_Wakeup
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
*  Refer to Amp_Out_Sleep() for an example usage.
*******************************************************************************/
void Amp_Out_Wakeup(void)
{
    #if defined(Amp_Out__PC)
        Amp_Out_PC = Amp_Out_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Amp_Out_USB_POWER_REG &= Amp_Out_USBIO_EXIT_SLEEP_PH1;
            Amp_Out_CR1_REG = Amp_Out_backup.usbState;
            Amp_Out_USB_POWER_REG &= Amp_Out_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Amp_Out__SIO)
        Amp_Out_SIO_REG = Amp_Out_backup.sioState;
    #endif
}


/* [] END OF FILE */
