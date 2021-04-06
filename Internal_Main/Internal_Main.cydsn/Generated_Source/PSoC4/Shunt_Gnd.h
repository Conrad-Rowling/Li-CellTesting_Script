/*******************************************************************************
* File Name: Shunt_gnd.h  
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

#if !defined(CY_PINS_Shunt_gnd_H) /* Pins Shunt_gnd_H */
#define CY_PINS_Shunt_gnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Shunt_gnd_aliases.h"


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
} Shunt_gnd_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Shunt_gnd_Read(void);
void    Shunt_gnd_Write(uint8 value);
uint8   Shunt_gnd_ReadDataReg(void);
#if defined(Shunt_gnd__PC) || (CY_PSOC4_4200L) 
    void    Shunt_gnd_SetDriveMode(uint8 mode);
#endif
void    Shunt_gnd_SetInterruptMode(uint16 position, uint16 mode);
uint8   Shunt_gnd_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Shunt_gnd_Sleep(void); 
void Shunt_gnd_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Shunt_gnd__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Shunt_gnd_DRIVE_MODE_BITS        (3)
    #define Shunt_gnd_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Shunt_gnd_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Shunt_gnd_SetDriveMode() function.
         *  @{
         */
        #define Shunt_gnd_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Shunt_gnd_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Shunt_gnd_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Shunt_gnd_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Shunt_gnd_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Shunt_gnd_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Shunt_gnd_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Shunt_gnd_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Shunt_gnd_MASK               Shunt_gnd__MASK
#define Shunt_gnd_SHIFT              Shunt_gnd__SHIFT
#define Shunt_gnd_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Shunt_gnd_SetInterruptMode() function.
     *  @{
     */
        #define Shunt_gnd_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Shunt_gnd_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Shunt_gnd_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Shunt_gnd_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Shunt_gnd__SIO)
    #define Shunt_gnd_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Shunt_gnd__PC) && (CY_PSOC4_4200L)
    #define Shunt_gnd_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Shunt_gnd_USBIO_DISABLE              ((uint32)(~Shunt_gnd_USBIO_ENABLE))
    #define Shunt_gnd_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Shunt_gnd_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Shunt_gnd_USBIO_ENTER_SLEEP          ((uint32)((1u << Shunt_gnd_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Shunt_gnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define Shunt_gnd_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Shunt_gnd_USBIO_SUSPEND_SHIFT)))
    #define Shunt_gnd_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Shunt_gnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define Shunt_gnd_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Shunt_gnd__PC)
    /* Port Configuration */
    #define Shunt_gnd_PC                 (* (reg32 *) Shunt_gnd__PC)
#endif
/* Pin State */
#define Shunt_gnd_PS                     (* (reg32 *) Shunt_gnd__PS)
/* Data Register */
#define Shunt_gnd_DR                     (* (reg32 *) Shunt_gnd__DR)
/* Input Buffer Disable Override */
#define Shunt_gnd_INP_DIS                (* (reg32 *) Shunt_gnd__PC2)

/* Interrupt configuration Registers */
#define Shunt_gnd_INTCFG                 (* (reg32 *) Shunt_gnd__INTCFG)
#define Shunt_gnd_INTSTAT                (* (reg32 *) Shunt_gnd__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Shunt_gnd_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Shunt_gnd__SIO)
    #define Shunt_gnd_SIO_REG            (* (reg32 *) Shunt_gnd__SIO)
#endif /* (Shunt_gnd__SIO_CFG) */

/* USBIO registers */
#if !defined(Shunt_gnd__PC) && (CY_PSOC4_4200L)
    #define Shunt_gnd_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Shunt_gnd_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Shunt_gnd_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Shunt_gnd_DRIVE_MODE_SHIFT       (0x00u)
#define Shunt_gnd_DRIVE_MODE_MASK        (0x07u << Shunt_gnd_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Shunt_gnd_H */


/* [] END OF FILE */
