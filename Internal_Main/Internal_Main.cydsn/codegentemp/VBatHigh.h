/*******************************************************************************
* File Name: VBatHigh.h  
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

#if !defined(CY_PINS_VBatHigh_H) /* Pins VBatHigh_H */
#define CY_PINS_VBatHigh_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VBatHigh_aliases.h"


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
} VBatHigh_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VBatHigh_Read(void);
void    VBatHigh_Write(uint8 value);
uint8   VBatHigh_ReadDataReg(void);
#if defined(VBatHigh__PC) || (CY_PSOC4_4200L) 
    void    VBatHigh_SetDriveMode(uint8 mode);
#endif
void    VBatHigh_SetInterruptMode(uint16 position, uint16 mode);
uint8   VBatHigh_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VBatHigh_Sleep(void); 
void VBatHigh_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VBatHigh__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VBatHigh_DRIVE_MODE_BITS        (3)
    #define VBatHigh_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VBatHigh_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VBatHigh_SetDriveMode() function.
         *  @{
         */
        #define VBatHigh_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VBatHigh_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VBatHigh_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VBatHigh_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VBatHigh_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VBatHigh_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VBatHigh_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VBatHigh_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VBatHigh_MASK               VBatHigh__MASK
#define VBatHigh_SHIFT              VBatHigh__SHIFT
#define VBatHigh_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VBatHigh_SetInterruptMode() function.
     *  @{
     */
        #define VBatHigh_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VBatHigh_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VBatHigh_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VBatHigh_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VBatHigh__SIO)
    #define VBatHigh_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VBatHigh__PC) && (CY_PSOC4_4200L)
    #define VBatHigh_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VBatHigh_USBIO_DISABLE              ((uint32)(~VBatHigh_USBIO_ENABLE))
    #define VBatHigh_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VBatHigh_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VBatHigh_USBIO_ENTER_SLEEP          ((uint32)((1u << VBatHigh_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VBatHigh_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatHigh_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VBatHigh_USBIO_SUSPEND_SHIFT)))
    #define VBatHigh_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VBatHigh_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatHigh_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VBatHigh__PC)
    /* Port Configuration */
    #define VBatHigh_PC                 (* (reg32 *) VBatHigh__PC)
#endif
/* Pin State */
#define VBatHigh_PS                     (* (reg32 *) VBatHigh__PS)
/* Data Register */
#define VBatHigh_DR                     (* (reg32 *) VBatHigh__DR)
/* Input Buffer Disable Override */
#define VBatHigh_INP_DIS                (* (reg32 *) VBatHigh__PC2)

/* Interrupt configuration Registers */
#define VBatHigh_INTCFG                 (* (reg32 *) VBatHigh__INTCFG)
#define VBatHigh_INTSTAT                (* (reg32 *) VBatHigh__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VBatHigh_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VBatHigh__SIO)
    #define VBatHigh_SIO_REG            (* (reg32 *) VBatHigh__SIO)
#endif /* (VBatHigh__SIO_CFG) */

/* USBIO registers */
#if !defined(VBatHigh__PC) && (CY_PSOC4_4200L)
    #define VBatHigh_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VBatHigh_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VBatHigh_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VBatHigh_DRIVE_MODE_SHIFT       (0x00u)
#define VBatHigh_DRIVE_MODE_MASK        (0x07u << VBatHigh_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VBatHigh_H */


/* [] END OF FILE */
