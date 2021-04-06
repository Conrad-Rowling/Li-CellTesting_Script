/***************************************************************************//**
* \file     PGA_1_PVT.h
* \version  1.10
*
* \brief
*  This file contains the private constants and macros used in
*  the PGA_P4 Component code.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_PGA_1_PVT_H) 
#define CY_PGA_P4_PGA_1_PVT_H

#include "PGA_1.h"


/***************************************
*         Internal Constants
***************************************/
    
#define PGA_1_POWER                  ((uint32)3u)
#define PGA_1_GAIN                   ((uint32)0u)
    
#define PGA_1_POWER_MAX              (PGA_1_HIGH)
#define PGA_1_GAIN_MAX               (PGA_1_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define PGA_1_COMP_TAB_HEIGHT        ((PGA_1_GAIN_MAX >> 1u) + 1u)
#define PGA_1_COMP_TAB_WIDTH         (PGA_1_POWER_MAX)
#define PGA_1_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define PGA_1_VREF_INTERNAL          (0u)
#define PGA_1_OUTPUT_MODE_10x        (1u)

#define PGA_1_DEFAULT_POWER          ((uint32)PGA_1_POWER << PGA_1_OA_PWR_MODE_SHIFT)
#define PGA_1_DEFAULT_GAIN           ((uint32)PGA_1_GAIN << PGA_1_RES_TAP_SHIFT)
#define PGA_1_DEFAULT_GAIN_POWER     (PGA_1_DEFAULT_GAIN | PGA_1_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 PGA_1_internalGainPower;
extern const uint32 PGA_1_compTab[PGA_1_COMP_TAB_HEIGHT][PGA_1_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define PGA_1_CHECK_DEEPSLEEP_SUPPORT (PGA_1_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define PGA_1_CHECK_OUTPUT_MODE      (PGA_1_OUTPUT_MODE == PGA_1_OUTPUT_MODE_10x)
#define PGA_1_GET_DEEPSLEEP_ON       ((PGA_1_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (PGA_1_DEEPSLEEP_ON) : (0u))
#define PGA_1_GET_OA_DRIVE_STR       ((PGA_1_CHECK_OUTPUT_MODE) ? \
                                                    (PGA_1_OA_DRIVE_STR_SEL_10X) : \
                                                        (PGA_1_OA_DRIVE_STR_SEL_1X))
#define PGA_1_GET_POWER              (PGA_1_internalGainPower & \
                                                    PGA_1_OA_PWR_MODE_MASK)
#define PGA_1_DEFAULT_CTB_CTRL       (PGA_1_GET_DEEPSLEEP_ON | PGA_1_ENABLED)
#define PGA_1_DEFAULT_OA_RES_CTRL    (PGA_1_GET_OA_DRIVE_STR | PGA_1_OA_PUMP_EN)
#define PGA_1_DEFAULT_OA_RES_CTRL_MASK (PGA_1_OA_DRIVE_STR_SEL_MASK | PGA_1_OA_PUMP_EN)
#define PGA_1_GET_COMP_TAB_GAIN      ((PGA_1_internalGainPower >> \
                                                    (PGA_1_RES_TAP_SHIFT + 1u)) & \
                                                        PGA_1_GET_COMP_TAB_GAIN_MASK)
#define PGA_1_GET_COMP_TAB           (PGA_1_compTab[PGA_1_GET_COMP_TAB_GAIN] \
                                                                         [PGA_1_GET_POWER - 1u])
#define PGA_1_GET_C_FB               (PGA_1_GET_COMP_TAB & PGA_1_C_FB_MASK)
#define PGA_1_GET_OA_COMP_TRIM       (PGA_1_GET_COMP_TAB & PGA_1_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_PGA_1_PVT_H */

/* [] END OF FILE */
