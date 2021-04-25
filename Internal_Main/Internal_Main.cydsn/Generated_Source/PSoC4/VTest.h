/*******************************************************************************
* File Name: VTest.h  
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

#if !defined(CY_PINS_VTest_H) /* Pins VTest_H */
#define CY_PINS_VTest_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VTest_aliases.h"


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
} VTest_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VTest_Read(void);
void    VTest_Write(uint8 value);
uint8   VTest_ReadDataReg(void);
#if defined(VTest__PC) || (CY_PSOC4_4200L) 
    void    VTest_SetDriveMode(uint8 mode);
#endif
void    VTest_SetInterruptMode(uint16 position, uint16 mode);
uint8   VTest_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VTest_Sleep(void); 
void VTest_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VTest__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VTest_DRIVE_MODE_BITS        (3)
    #define VTest_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VTest_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VTest_SetDriveMode() function.
         *  @{
         */
        #define VTest_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VTest_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VTest_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VTest_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VTest_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VTest_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VTest_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VTest_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VTest_MASK               VTest__MASK
#define VTest_SHIFT              VTest__SHIFT
#define VTest_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VTest_SetInterruptMode() function.
     *  @{
     */
        #define VTest_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VTest_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VTest_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VTest_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VTest__SIO)
    #define VTest_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VTest__PC) && (CY_PSOC4_4200L)
    #define VTest_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VTest_USBIO_DISABLE              ((uint32)(~VTest_USBIO_ENABLE))
    #define VTest_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VTest_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VTest_USBIO_ENTER_SLEEP          ((uint32)((1u << VTest_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VTest_USBIO_SUSPEND_DEL_SHIFT)))
    #define VTest_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VTest_USBIO_SUSPEND_SHIFT)))
    #define VTest_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VTest_USBIO_SUSPEND_DEL_SHIFT)))
    #define VTest_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VTest__PC)
    /* Port Configuration */
    #define VTest_PC                 (* (reg32 *) VTest__PC)
#endif
/* Pin State */
#define VTest_PS                     (* (reg32 *) VTest__PS)
/* Data Register */
#define VTest_DR                     (* (reg32 *) VTest__DR)
/* Input Buffer Disable Override */
#define VTest_INP_DIS                (* (reg32 *) VTest__PC2)

/* Interrupt configuration Registers */
#define VTest_INTCFG                 (* (reg32 *) VTest__INTCFG)
#define VTest_INTSTAT                (* (reg32 *) VTest__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VTest_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VTest__SIO)
    #define VTest_SIO_REG            (* (reg32 *) VTest__SIO)
#endif /* (VTest__SIO_CFG) */

/* USBIO registers */
#if !defined(VTest__PC) && (CY_PSOC4_4200L)
    #define VTest_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VTest_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VTest_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VTest_DRIVE_MODE_SHIFT       (0x00u)
#define VTest_DRIVE_MODE_MASK        (0x07u << VTest_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VTest_H */


/* [] END OF FILE */
