/*******************************************************************************
* File Name: bgRef.h  
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

#if !defined(CY_PINS_bgRef_H) /* Pins bgRef_H */
#define CY_PINS_bgRef_H

#include "cytypes.h"
#include "cyfitter.h"
#include "bgRef_aliases.h"


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
} bgRef_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   bgRef_Read(void);
void    bgRef_Write(uint8 value);
uint8   bgRef_ReadDataReg(void);
#if defined(bgRef__PC) || (CY_PSOC4_4200L) 
    void    bgRef_SetDriveMode(uint8 mode);
#endif
void    bgRef_SetInterruptMode(uint16 position, uint16 mode);
uint8   bgRef_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void bgRef_Sleep(void); 
void bgRef_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(bgRef__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define bgRef_DRIVE_MODE_BITS        (3)
    #define bgRef_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - bgRef_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the bgRef_SetDriveMode() function.
         *  @{
         */
        #define bgRef_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define bgRef_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define bgRef_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define bgRef_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define bgRef_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define bgRef_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define bgRef_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define bgRef_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define bgRef_MASK               bgRef__MASK
#define bgRef_SHIFT              bgRef__SHIFT
#define bgRef_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bgRef_SetInterruptMode() function.
     *  @{
     */
        #define bgRef_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define bgRef_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define bgRef_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define bgRef_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(bgRef__SIO)
    #define bgRef_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(bgRef__PC) && (CY_PSOC4_4200L)
    #define bgRef_USBIO_ENABLE               ((uint32)0x80000000u)
    #define bgRef_USBIO_DISABLE              ((uint32)(~bgRef_USBIO_ENABLE))
    #define bgRef_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define bgRef_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define bgRef_USBIO_ENTER_SLEEP          ((uint32)((1u << bgRef_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << bgRef_USBIO_SUSPEND_DEL_SHIFT)))
    #define bgRef_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << bgRef_USBIO_SUSPEND_SHIFT)))
    #define bgRef_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << bgRef_USBIO_SUSPEND_DEL_SHIFT)))
    #define bgRef_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(bgRef__PC)
    /* Port Configuration */
    #define bgRef_PC                 (* (reg32 *) bgRef__PC)
#endif
/* Pin State */
#define bgRef_PS                     (* (reg32 *) bgRef__PS)
/* Data Register */
#define bgRef_DR                     (* (reg32 *) bgRef__DR)
/* Input Buffer Disable Override */
#define bgRef_INP_DIS                (* (reg32 *) bgRef__PC2)

/* Interrupt configuration Registers */
#define bgRef_INTCFG                 (* (reg32 *) bgRef__INTCFG)
#define bgRef_INTSTAT                (* (reg32 *) bgRef__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define bgRef_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(bgRef__SIO)
    #define bgRef_SIO_REG            (* (reg32 *) bgRef__SIO)
#endif /* (bgRef__SIO_CFG) */

/* USBIO registers */
#if !defined(bgRef__PC) && (CY_PSOC4_4200L)
    #define bgRef_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define bgRef_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define bgRef_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define bgRef_DRIVE_MODE_SHIFT       (0x00u)
#define bgRef_DRIVE_MODE_MASK        (0x07u << bgRef_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins bgRef_H */


/* [] END OF FILE */
