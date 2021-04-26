/*******************************************************************************
* File Name: VBatLow.h  
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

#if !defined(CY_PINS_VBatLow_H) /* Pins VBatLow_H */
#define CY_PINS_VBatLow_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VBatLow_aliases.h"


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
} VBatLow_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VBatLow_Read(void);
void    VBatLow_Write(uint8 value);
uint8   VBatLow_ReadDataReg(void);
#if defined(VBatLow__PC) || (CY_PSOC4_4200L) 
    void    VBatLow_SetDriveMode(uint8 mode);
#endif
void    VBatLow_SetInterruptMode(uint16 position, uint16 mode);
uint8   VBatLow_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VBatLow_Sleep(void); 
void VBatLow_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VBatLow__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VBatLow_DRIVE_MODE_BITS        (3)
    #define VBatLow_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VBatLow_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VBatLow_SetDriveMode() function.
         *  @{
         */
        #define VBatLow_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VBatLow_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VBatLow_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VBatLow_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VBatLow_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VBatLow_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VBatLow_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VBatLow_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VBatLow_MASK               VBatLow__MASK
#define VBatLow_SHIFT              VBatLow__SHIFT
#define VBatLow_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VBatLow_SetInterruptMode() function.
     *  @{
     */
        #define VBatLow_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VBatLow_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VBatLow_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VBatLow_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VBatLow__SIO)
    #define VBatLow_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VBatLow__PC) && (CY_PSOC4_4200L)
    #define VBatLow_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VBatLow_USBIO_DISABLE              ((uint32)(~VBatLow_USBIO_ENABLE))
    #define VBatLow_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VBatLow_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VBatLow_USBIO_ENTER_SLEEP          ((uint32)((1u << VBatLow_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VBatLow_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatLow_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VBatLow_USBIO_SUSPEND_SHIFT)))
    #define VBatLow_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VBatLow_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatLow_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VBatLow__PC)
    /* Port Configuration */
    #define VBatLow_PC                 (* (reg32 *) VBatLow__PC)
#endif
/* Pin State */
#define VBatLow_PS                     (* (reg32 *) VBatLow__PS)
/* Data Register */
#define VBatLow_DR                     (* (reg32 *) VBatLow__DR)
/* Input Buffer Disable Override */
#define VBatLow_INP_DIS                (* (reg32 *) VBatLow__PC2)

/* Interrupt configuration Registers */
#define VBatLow_INTCFG                 (* (reg32 *) VBatLow__INTCFG)
#define VBatLow_INTSTAT                (* (reg32 *) VBatLow__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VBatLow_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VBatLow__SIO)
    #define VBatLow_SIO_REG            (* (reg32 *) VBatLow__SIO)
#endif /* (VBatLow__SIO_CFG) */

/* USBIO registers */
#if !defined(VBatLow__PC) && (CY_PSOC4_4200L)
    #define VBatLow_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VBatLow_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VBatLow_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VBatLow_DRIVE_MODE_SHIFT       (0x00u)
#define VBatLow_DRIVE_MODE_MASK        (0x07u << VBatLow_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VBatLow_H */


/* [] END OF FILE */
