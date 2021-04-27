/*******************************************************************************
* File Name: VrGnd.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VrGnd_H) /* Pins VrGnd_H */
#define CY_PINS_VrGnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VrGnd_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} VrGnd_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VrGnd_Read(void);
void    VrGnd_Write(uint8 value);
uint8   VrGnd_ReadDataReg(void);
#if defined(VrGnd__PC) || (CY_PSOC4_4200L) 
    void    VrGnd_SetDriveMode(uint8 mode);
#endif
void    VrGnd_SetInterruptMode(uint16 position, uint16 mode);
uint8   VrGnd_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VrGnd_Sleep(void); 
void VrGnd_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VrGnd__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VrGnd_DRIVE_MODE_BITS        (3)
    #define VrGnd_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VrGnd_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VrGnd_SetDriveMode() function.
         *  @{
         */
        #define VrGnd_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VrGnd_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VrGnd_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VrGnd_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VrGnd_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VrGnd_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VrGnd_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VrGnd_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VrGnd_MASK               VrGnd__MASK
#define VrGnd_SHIFT              VrGnd__SHIFT
#define VrGnd_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VrGnd_SetInterruptMode() function.
     *  @{
     */
        #define VrGnd_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VrGnd_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VrGnd_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VrGnd_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VrGnd__SIO)
    #define VrGnd_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VrGnd__PC) && (CY_PSOC4_4200L)
    #define VrGnd_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VrGnd_USBIO_DISABLE              ((uint32)(~VrGnd_USBIO_ENABLE))
    #define VrGnd_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VrGnd_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VrGnd_USBIO_ENTER_SLEEP          ((uint32)((1u << VrGnd_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VrGnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define VrGnd_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VrGnd_USBIO_SUSPEND_SHIFT)))
    #define VrGnd_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VrGnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define VrGnd_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VrGnd__PC)
    /* Port Configuration */
    #define VrGnd_PC                 (* (reg32 *) VrGnd__PC)
#endif
/* Pin State */
#define VrGnd_PS                     (* (reg32 *) VrGnd__PS)
/* Data Register */
#define VrGnd_DR                     (* (reg32 *) VrGnd__DR)
/* Input Buffer Disable Override */
#define VrGnd_INP_DIS                (* (reg32 *) VrGnd__PC2)

/* Interrupt configuration Registers */
#define VrGnd_INTCFG                 (* (reg32 *) VrGnd__INTCFG)
#define VrGnd_INTSTAT                (* (reg32 *) VrGnd__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VrGnd_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VrGnd__SIO)
    #define VrGnd_SIO_REG            (* (reg32 *) VrGnd__SIO)
#endif /* (VrGnd__SIO_CFG) */

/* USBIO registers */
#if !defined(VrGnd__PC) && (CY_PSOC4_4200L)
    #define VrGnd_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VrGnd_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VrGnd_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VrGnd_DRIVE_MODE_SHIFT       (0x00u)
#define VrGnd_DRIVE_MODE_MASK        (0x07u << VrGnd_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VrGnd_H */


/* [] END OF FILE */
