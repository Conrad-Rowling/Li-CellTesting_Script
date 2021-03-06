/*******************************************************************************
* File Name: GND_ref.h  
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

#if !defined(CY_PINS_GND_ref_H) /* Pins GND_ref_H */
#define CY_PINS_GND_ref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GND_ref_aliases.h"


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
} GND_ref_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GND_ref_Read(void);
void    GND_ref_Write(uint8 value);
uint8   GND_ref_ReadDataReg(void);
#if defined(GND_ref__PC) || (CY_PSOC4_4200L) 
    void    GND_ref_SetDriveMode(uint8 mode);
#endif
void    GND_ref_SetInterruptMode(uint16 position, uint16 mode);
uint8   GND_ref_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GND_ref_Sleep(void); 
void GND_ref_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GND_ref__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GND_ref_DRIVE_MODE_BITS        (3)
    #define GND_ref_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GND_ref_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GND_ref_SetDriveMode() function.
         *  @{
         */
        #define GND_ref_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GND_ref_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GND_ref_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GND_ref_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GND_ref_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GND_ref_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GND_ref_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GND_ref_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GND_ref_MASK               GND_ref__MASK
#define GND_ref_SHIFT              GND_ref__SHIFT
#define GND_ref_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GND_ref_SetInterruptMode() function.
     *  @{
     */
        #define GND_ref_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GND_ref_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GND_ref_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GND_ref_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GND_ref__SIO)
    #define GND_ref_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GND_ref__PC) && (CY_PSOC4_4200L)
    #define GND_ref_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GND_ref_USBIO_DISABLE              ((uint32)(~GND_ref_USBIO_ENABLE))
    #define GND_ref_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GND_ref_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GND_ref_USBIO_ENTER_SLEEP          ((uint32)((1u << GND_ref_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GND_ref_USBIO_SUSPEND_DEL_SHIFT)))
    #define GND_ref_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GND_ref_USBIO_SUSPEND_SHIFT)))
    #define GND_ref_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GND_ref_USBIO_SUSPEND_DEL_SHIFT)))
    #define GND_ref_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GND_ref__PC)
    /* Port Configuration */
    #define GND_ref_PC                 (* (reg32 *) GND_ref__PC)
#endif
/* Pin State */
#define GND_ref_PS                     (* (reg32 *) GND_ref__PS)
/* Data Register */
#define GND_ref_DR                     (* (reg32 *) GND_ref__DR)
/* Input Buffer Disable Override */
#define GND_ref_INP_DIS                (* (reg32 *) GND_ref__PC2)

/* Interrupt configuration Registers */
#define GND_ref_INTCFG                 (* (reg32 *) GND_ref__INTCFG)
#define GND_ref_INTSTAT                (* (reg32 *) GND_ref__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GND_ref_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GND_ref__SIO)
    #define GND_ref_SIO_REG            (* (reg32 *) GND_ref__SIO)
#endif /* (GND_ref__SIO_CFG) */

/* USBIO registers */
#if !defined(GND_ref__PC) && (CY_PSOC4_4200L)
    #define GND_ref_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GND_ref_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GND_ref_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GND_ref_DRIVE_MODE_SHIFT       (0x00u)
#define GND_ref_DRIVE_MODE_MASK        (0x07u << GND_ref_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GND_ref_H */


/* [] END OF FILE */
