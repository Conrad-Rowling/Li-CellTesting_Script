/*******************************************************************************
* File Name: VRef.h  
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

#if !defined(CY_PINS_VRef_H) /* Pins VRef_H */
#define CY_PINS_VRef_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VRef_aliases.h"


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
} VRef_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VRef_Read(void);
void    VRef_Write(uint8 value);
uint8   VRef_ReadDataReg(void);
#if defined(VRef__PC) || (CY_PSOC4_4200L) 
    void    VRef_SetDriveMode(uint8 mode);
#endif
void    VRef_SetInterruptMode(uint16 position, uint16 mode);
uint8   VRef_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VRef_Sleep(void); 
void VRef_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VRef__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VRef_DRIVE_MODE_BITS        (3)
    #define VRef_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VRef_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VRef_SetDriveMode() function.
         *  @{
         */
        #define VRef_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VRef_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VRef_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VRef_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VRef_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VRef_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VRef_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VRef_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VRef_MASK               VRef__MASK
#define VRef_SHIFT              VRef__SHIFT
#define VRef_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VRef_SetInterruptMode() function.
     *  @{
     */
        #define VRef_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VRef_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VRef_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VRef_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VRef__SIO)
    #define VRef_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VRef__PC) && (CY_PSOC4_4200L)
    #define VRef_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VRef_USBIO_DISABLE              ((uint32)(~VRef_USBIO_ENABLE))
    #define VRef_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VRef_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VRef_USBIO_ENTER_SLEEP          ((uint32)((1u << VRef_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VRef_USBIO_SUSPEND_DEL_SHIFT)))
    #define VRef_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VRef_USBIO_SUSPEND_SHIFT)))
    #define VRef_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VRef_USBIO_SUSPEND_DEL_SHIFT)))
    #define VRef_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VRef__PC)
    /* Port Configuration */
    #define VRef_PC                 (* (reg32 *) VRef__PC)
#endif
/* Pin State */
#define VRef_PS                     (* (reg32 *) VRef__PS)
/* Data Register */
#define VRef_DR                     (* (reg32 *) VRef__DR)
/* Input Buffer Disable Override */
#define VRef_INP_DIS                (* (reg32 *) VRef__PC2)

/* Interrupt configuration Registers */
#define VRef_INTCFG                 (* (reg32 *) VRef__INTCFG)
#define VRef_INTSTAT                (* (reg32 *) VRef__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VRef_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VRef__SIO)
    #define VRef_SIO_REG            (* (reg32 *) VRef__SIO)
#endif /* (VRef__SIO_CFG) */

/* USBIO registers */
#if !defined(VRef__PC) && (CY_PSOC4_4200L)
    #define VRef_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VRef_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VRef_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VRef_DRIVE_MODE_SHIFT       (0x00u)
#define VRef_DRIVE_MODE_MASK        (0x07u << VRef_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VRef_H */


/* [] END OF FILE */
