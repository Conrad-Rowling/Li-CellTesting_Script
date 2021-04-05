/***************************************************************************//**
* \file     PGA_1.h
* \version  1.10
*
* \brief
*  This file contains the public API function prototypes and constants used in
*  the PGA_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_PGA_1_H) 
#define CY_PGA_P4_PGA_1_H 

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define PGA_1_VREF_MODE              (0u)
#define PGA_1_OUTPUT_MODE            (1u)
#define PGA_1_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 PGA_1_initVar;
/** @} globals */


/***************************************
*        Function Prototypes 
***************************************/

/**
* \addtogroup group_general
* @{
*/
void PGA_1_Init(void);
void PGA_1_Enable(void);
void PGA_1_Start(void);
void PGA_1_Stop(void);
void PGA_1_SetPower(uint32 powerLevel);
void PGA_1_SetGain(uint32 gainLevel);
void PGA_1_PumpControl(uint32 onOff);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PGA_1_Sleep(void);
void PGA_1_Wakeup(void);
void PGA_1_SaveConfig(void);
void PGA_1_RestoreConfig(void);
/** @} power */


/**************************************
*           API Constants
**************************************/

/* Gain setting constants */
#define PGA_1__GAIN_1 0
#define PGA_1__GAIN_1_4 1
#define PGA_1__GAIN_2 2
#define PGA_1__GAIN_2_8 3
#define PGA_1__GAIN_4 4
#define PGA_1__GAIN_5_8 5
#define PGA_1__GAIN_10_7 7
#define PGA_1__GAIN_8 6
#define PGA_1__GAIN_21_3 9
#define PGA_1__GAIN_32 10
#define PGA_1__GAIN_16 8


/* Power setting constants */
#define PGA_1__LOW 1
#define PGA_1__MED 2
#define PGA_1__HIGH 3


/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup group_powerLevel
     * \brief Definitions for PGA_1_SetPower() function.
     *  @{
     */
    #define PGA_1_LOW                ((uint32)PGA_1__LOW)
    #define PGA_1_MED                ((uint32)PGA_1__MED)
    #define PGA_1_HIGH               ((uint32)PGA_1__HIGH)
    /** @} powerLevel */

    /** \addtogroup group_boostPump
     * \brief Definitions for PGA_1_PumpControl() function.
     *  @{
     */
    #define PGA_1_BOOST_ON           ((uint32)1u)
    #define PGA_1_BOOST_OFF          ((uint32)0u)
    /** @} boostPump */

    /** \addtogroup group_gain
     * \brief Definitions for PGA_1_SetGain() function.
     *  @{
     */
    #define PGA_1_GAIN_1_00          ((uint32)PGA_1__GAIN_1)
    #define PGA_1_GAIN_1_42          ((uint32)PGA_1__GAIN_1_4)
    #define PGA_1_GAIN_2_00          ((uint32)PGA_1__GAIN_2)
    #define PGA_1_GAIN_2_78          ((uint32)PGA_1__GAIN_2_8)
    #define PGA_1_GAIN_4_00          ((uint32)PGA_1__GAIN_4)
    #define PGA_1_GAIN_5_82          ((uint32)PGA_1__GAIN_5_8)
    #define PGA_1_GAIN_8_00          ((uint32)PGA_1__GAIN_8)
    #define PGA_1_GAIN_10_7          ((uint32)PGA_1__GAIN_10_7)
    #define PGA_1_GAIN_16_0          ((uint32)PGA_1__GAIN_16)
    #define PGA_1_GAIN_21_3          ((uint32)PGA_1__GAIN_21_3)
    #define PGA_1_GAIN_32_0          ((uint32)PGA_1__GAIN_32)
    /** @} gain */
/** @} group_constants */

/* The next gain constants are not recommended to use in new projects,
   they are legacy provided for backward compatibility */
    #define PGA_1_GAIN_1             (PGA_1_GAIN_1_00)
    #define PGA_1_GAIN_1_4           (PGA_1_GAIN_1_42)
    #define PGA_1_GAIN_2             (PGA_1_GAIN_2_00)
    #define PGA_1_GAIN_2_8           (PGA_1_GAIN_2_78)
    #define PGA_1_GAIN_4             (PGA_1_GAIN_4_00)
    #define PGA_1_GAIN_5_8           (PGA_1_GAIN_5_82)
    #define PGA_1_GAIN_8             (PGA_1_GAIN_8_00)    
    #define PGA_1_GAIN_16            (PGA_1_GAIN_16_0)    
    #define PGA_1_GAIN_32            (PGA_1_GAIN_32_0)

/***************************************
* Registers
***************************************/

#define PGA_1_CTB_CTRL_REG           (*(reg32 *) PGA_1_cy_psoc4_abuf__CTB_CTB_CTRL)
#define PGA_1_CTB_CTRL_PTR           ( (reg32 *) PGA_1_cy_psoc4_abuf__CTB_CTB_CTRL)
#define PGA_1_OA_RES_CTRL_REG        (*(reg32 *) PGA_1_cy_psoc4_abuf__OA_RES_CTRL)
#define PGA_1_OA_RES_CTRL_PTR        ( (reg32 *) PGA_1_cy_psoc4_abuf__OA_RES_CTRL)
#define PGA_1_OA_SW_REG              (*(reg32 *) PGA_1_cy_psoc4_abuf__OA_SW)
#define PGA_1_OA_SW_PTR              ( (reg32 *) PGA_1_cy_psoc4_abuf__OA_SW)
#define PGA_1_OA_SW_CLEAR_REG        (*(reg32 *) PGA_1_cy_psoc4_abuf__OA_SW_CLEAR)
#define PGA_1_OA_SW_CLEAR_PTR        ( (reg32 *) PGA_1_cy_psoc4_abuf__OA_SW_CLEAR)
#define PGA_1_OA_COMP_TRIM_REG       (*(reg32 *) PGA_1_cy_psoc4_abuf__OA_COMP_TRIM)
#define PGA_1_OA_COMP_TRIM_PTR       ( (reg32 *) PGA_1_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
* Register Constants
***************************************/

/* PGA_1_CTB_CTRL_REG */
#define PGA_1_DEEPSLEEP_ON_SHIFT     (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define PGA_1_ENABLED_SHIFT          (31u)   /* [31] Enable of the CTB IP */

#define PGA_1_DEEPSLEEP_ON           ((uint32)0x01u << PGA_1_DEEPSLEEP_ON_SHIFT)
#define PGA_1_ENABLED                ((uint32)0x01u << PGA_1_ENABLED_SHIFT)

/* PGA_1_OA_RES_CTRL_REG */
#define PGA_1_OA_PWR_MODE_SHIFT      (0u)    /* [1:0]    Power level */
#define PGA_1_OA_DRIVE_STR_SEL_SHIFT (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define PGA_1_OA_PUMP_EN_SHIFT       (11u)   /* [11]     Pump enable */
#define PGA_1_RES_TAP_SHIFT          (16u)   /* [19:16]  PGA gain (resistor tap point) */
#define PGA_1_C_FB_SHIFT             (24u)   /* [27:24]  Feedback Capacitor */

#define PGA_1_OA_PWR_MODE_MASK       ((uint32)0x03u << PGA_1_OA_PWR_MODE_SHIFT)
#define PGA_1_OA_DRIVE_STR_SEL_1X    ((uint32)0x00u << PGA_1_OA_DRIVE_STR_SEL_SHIFT)
#define PGA_1_OA_DRIVE_STR_SEL_10X   ((uint32)0x01u << PGA_1_OA_DRIVE_STR_SEL_SHIFT)
#define PGA_1_OA_DRIVE_STR_SEL_MASK  ((uint32)0x01u << PGA_1_OA_DRIVE_STR_SEL_SHIFT)
#define PGA_1_OA_PUMP_EN             ((uint32)0x01u << PGA_1_OA_PUMP_EN_SHIFT)
#define PGA_1_RES_TAP_MASK           ((uint32)0x0Fu << PGA_1_RES_TAP_SHIFT)
#define PGA_1_C_FB_MASK              ((uint32)0x0Fu << PGA_1_C_FB_SHIFT)

/** PGA_1_OA_COMP_TRIM_REG */
#define PGA_1_OA_COMP_TRIM_SHIFT     (0u)    /* [1:0]    Opamp Compensation Capacitor Trim */
#define PGA_1_OA_COMP_TRIM_MASK      ((uint32)0x03u << PGA_1_OA_COMP_TRIM_SHIFT)

/** PGA_1_OA_SW_REG */
#define PGA_1_RBOT_TO_VSSA_SHIFT     (28u)   /* Resistor bottom  to VSSA */
#define PGA_1_RBOT_TO_VSSA           ((uint32)0x01u << PGA_1_RBOT_TO_VSSA_SHIFT)

#define PGA_1_RES_SWAP_SHIFT         (20u)   /* Resistor ladder swap (top <-> bottom) */
#define PGA_1_RES_SWAP               ((uint32)0x01u << PGA_1_RES_SWAP_SHIFT)

#endif /* CY_PGA_P4_PGA_1_H */


/* [] END OF FILE */
