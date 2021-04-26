/*******************************************************************************
* File Name: VBatUp.h  
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

#if !defined(CY_PINS_VBatUp_H) /* Pins VBatUp_H */
#define CY_PINS_VBatUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VBatUp_aliases.h"


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
} VBatUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VBatUp_Read(void);
void    VBatUp_Write(uint8 value);
uint8   VBatUp_ReadDataReg(void);
#if defined(VBatUp__PC) || (CY_PSOC4_4200L) 
    void    VBatUp_SetDriveMode(uint8 mode);
#endif
void    VBatUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   VBatUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VBatUp_Sleep(void); 
void VBatUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VBatUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VBatUp_DRIVE_MODE_BITS        (3)
    #define VBatUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VBatUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VBatUp_SetDriveMode() function.
         *  @{
         */
        #define VBatUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VBatUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VBatUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VBatUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VBatUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VBatUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VBatUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VBatUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VBatUp_MASK               VBatUp__MASK
#define VBatUp_SHIFT              VBatUp__SHIFT
#define VBatUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VBatUp_SetInterruptMode() function.
     *  @{
     */
        #define VBatUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VBatUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VBatUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VBatUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VBatUp__SIO)
    #define VBatUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VBatUp__PC) && (CY_PSOC4_4200L)
    #define VBatUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VBatUp_USBIO_DISABLE              ((uint32)(~VBatUp_USBIO_ENABLE))
    #define VBatUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VBatUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VBatUp_USBIO_ENTER_SLEEP          ((uint32)((1u << VBatUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VBatUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VBatUp_USBIO_SUSPEND_SHIFT)))
    #define VBatUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VBatUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VBatUp__PC)
    /* Port Configuration */
    #define VBatUp_PC                 (* (reg32 *) VBatUp__PC)
#endif
/* Pin State */
#define VBatUp_PS                     (* (reg32 *) VBatUp__PS)
/* Data Register */
#define VBatUp_DR                     (* (reg32 *) VBatUp__DR)
/* Input Buffer Disable Override */
#define VBatUp_INP_DIS                (* (reg32 *) VBatUp__PC2)

/* Interrupt configuration Registers */
#define VBatUp_INTCFG                 (* (reg32 *) VBatUp__INTCFG)
#define VBatUp_INTSTAT                (* (reg32 *) VBatUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VBatUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VBatUp__SIO)
    #define VBatUp_SIO_REG            (* (reg32 *) VBatUp__SIO)
#endif /* (VBatUp__SIO_CFG) */

/* USBIO registers */
#if !defined(VBatUp__PC) && (CY_PSOC4_4200L)
    #define VBatUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VBatUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VBatUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VBatUp_DRIVE_MODE_SHIFT       (0x00u)
#define VBatUp_DRIVE_MODE_MASK        (0x07u << VBatUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VBatUp_H */


/* [] END OF FILE */
