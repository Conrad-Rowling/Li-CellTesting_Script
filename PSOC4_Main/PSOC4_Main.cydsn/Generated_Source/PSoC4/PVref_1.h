/***************************************************************************//**
* \file PVref_1.h
* \version 1.0
*
* \brief
*  This file provides constants and parameter values for the Programmable
*  Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PVref_P4_PVref_1_H)
#define CY_PVref_P4_PVref_1_H

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PVref_1_SEL_OUTPUT_VOLTAGE      (10u)
#define PVref_1_SEL_REFERENCE_SOURCE    (0u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} PVref_1_backup_struct;


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void PVref_1_Init(void);
void PVref_1_Enable(void);
void PVref_1_Start(void);
void PVref_1_Stop(void);
void PVref_1_SetTap(uint32 dividerTap);
void PVref_1_SetVRefSrc(uint32 reference);
/** @} group_general */
/**
* \addtogroup group_power
* @{
*/
void PVref_1_Sleep(void);
void PVref_1_Wakeup(void);
/** @} power */


/***************************************
*           Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 PVref_1_initVar;
/** @} globals */


/***************************************
*           API Constants
***************************************/

#define PVref_1_VDDA_MVOLTS             (3300u)
#define PVref_1_BANDGAP_MVOLTS          (1200u)

#define PVref_1_BANDGAP_REFERENCE       (0u)
#define PVref_1_VDDA_REFERENCE          (1u)

#define PVref_1_PRB_CTRL_REG_INIT       (PVref_1_PRB_IP_ENABLE | \
            (uint32) ((uint32) PVref_1_SEL_REFERENCE_SOURCE << PVref_1_VDDA_ENABLE_POS))
#define PVref_1_PRB_REF_REG_INIT        ( \
            (uint32) ((uint32) PVref_1_SEL_REFERENCE_SOURCE << PVref_1_VREF_SUPPLY_SEL_POS) | \
            (uint32) ((uint32) (PVref_1_SEL_OUTPUT_VOLTAGE - 1u) << PVref_1_VREF_LEVEL_SEL_MASK_POS))


/***************************************
*             Registers
***************************************/

/* Programmable Voltage Reference IP block registers */
#define PVref_1_PRB_CTRL_REG            (*(reg32*) CYREG_PASS_PRB_CTRL)
#define PVref_1_PRB_CTRL_PTR            ( (reg32*) CYREG_PASS_PRB_CTRL)
#define PVref_1_PRB_REF_REG             (*(reg32*) PVref_1_cy_psoc4_pref_PRB_REF)
#define PVref_1_PRB_REF_PTR             ( (reg32*) PVref_1_cy_psoc4_pref_PRB_REF)


/***************************************
*       Register Constants
***************************************/

/* Global Programmable Voltage Reference IP block register bits */
#define PVref_1_VBGR_BUF_GAIN_MASK_POS  (0u)
#define PVref_1_VDDA_ENABLE_POS         (4u)
#define PVref_1_DEEPSLEEP_ON_POS        (30u)
#define PVref_1_PRB_IP_ENABLE_POS       (31u)

#define PVref_1_VBGR_BUF_GAIN_MASK      ((uint32) ((uint32) 0x03u << PVref_1_VBGR_BUF_GAIN_MASK_POS))
#define PVref_1_VDDA_ENABLE             ((uint32) ((uint32) 0x01u << PVref_1_VDDA_ENABLE_POS))
#define PVref_1_DEEPSLEEP_ON            ((uint32) ((uint32) 0x01u << PVref_1_DEEPSLEEP_ON_POS))
#define PVref_1_PRB_IP_ENABLE           ((uint32) ((uint32) 0x01u << PVref_1_PRB_IP_ENABLE_POS))

/* VREF Control register bits */
#define PVref_1_VREF_ENABLE_POS         (0u)
#define PVref_1_VREF_SUPPLY_SEL_POS     (1u)
#define PVref_1_VREF_LEVEL_SEL_MASK_POS (4u)

#define PVref_1_VREF_ENABLE             ((uint32) ((uint32) 0x01u << PVref_1_VREF_ENABLE_POS))
#define PVref_1_VREF_SUPPLY_SEL         ((uint32) ((uint32) 0x01u << PVref_1_VREF_SUPPLY_SEL_POS))
#define PVref_1_VREF_LEVEL_SEL_MASK     ((uint32) ((uint32) 0x0Fu << PVref_1_VREF_LEVEL_SEL_MASK_POS))

#endif /* End CY_PVref_P4_PVref_1_H */


/* [] END OF FILE */
