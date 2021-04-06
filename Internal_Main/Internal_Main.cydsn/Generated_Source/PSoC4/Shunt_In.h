/*******************************************************************************
* File Name: Shunt_In.h  
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

#if !defined(CY_PINS_Shunt_In_H) /* Pins Shunt_In_H */
#define CY_PINS_Shunt_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Shunt_In_aliases.h"


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
} Shunt_In_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Shunt_In_Read(void);
void    Shunt_In_Write(uint8 value);
uint8   Shunt_In_ReadDataReg(void);
#if defined(Shunt_In__PC) || (CY_PSOC4_4200L) 
    void    Shunt_In_SetDriveMode(uint8 mode);
#endif
void    Shunt_In_SetInterruptMode(uint16 position, uint16 mode);
uint8   Shunt_In_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Shunt_In_Sleep(void); 
void Shunt_In_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Shunt_In__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Shunt_In_DRIVE_MODE_BITS        (3)
    #define Shunt_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Shunt_In_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Shunt_In_SetDriveMode() function.
         *  @{
         */
        #define Shunt_In_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Shunt_In_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Shunt_In_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Shunt_In_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Shunt_In_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Shunt_In_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Shunt_In_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Shunt_In_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Shunt_In_MASK               Shunt_In__MASK
#define Shunt_In_SHIFT              Shunt_In__SHIFT
#define Shunt_In_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Shunt_In_SetInterruptMode() function.
     *  @{
     */
        #define Shunt_In_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Shunt_In_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Shunt_In_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Shunt_In_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Shunt_In__SIO)
    #define Shunt_In_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Shunt_In__PC) && (CY_PSOC4_4200L)
    #define Shunt_In_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Shunt_In_USBIO_DISABLE              ((uint32)(~Shunt_In_USBIO_ENABLE))
    #define Shunt_In_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Shunt_In_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Shunt_In_USBIO_ENTER_SLEEP          ((uint32)((1u << Shunt_In_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Shunt_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define Shunt_In_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Shunt_In_USBIO_SUSPEND_SHIFT)))
    #define Shunt_In_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Shunt_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define Shunt_In_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Shunt_In__PC)
    /* Port Configuration */
    #define Shunt_In_PC                 (* (reg32 *) Shunt_In__PC)
#endif
/* Pin State */
#define Shunt_In_PS                     (* (reg32 *) Shunt_In__PS)
/* Data Register */
#define Shunt_In_DR                     (* (reg32 *) Shunt_In__DR)
/* Input Buffer Disable Override */
#define Shunt_In_INP_DIS                (* (reg32 *) Shunt_In__PC2)

/* Interrupt configuration Registers */
#define Shunt_In_INTCFG                 (* (reg32 *) Shunt_In__INTCFG)
#define Shunt_In_INTSTAT                (* (reg32 *) Shunt_In__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Shunt_In_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Shunt_In__SIO)
    #define Shunt_In_SIO_REG            (* (reg32 *) Shunt_In__SIO)
#endif /* (Shunt_In__SIO_CFG) */

/* USBIO registers */
#if !defined(Shunt_In__PC) && (CY_PSOC4_4200L)
    #define Shunt_In_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Shunt_In_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Shunt_In_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Shunt_In_DRIVE_MODE_SHIFT       (0x00u)
#define Shunt_In_DRIVE_MODE_MASK        (0x07u << Shunt_In_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Shunt_In_H */


/* [] END OF FILE */
