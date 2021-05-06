/***************************************************************************//**
* \file     PGA_2_PVT.h
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

#if !defined(CY_PGA_P4_PGA_2_PVT_H) 
#define CY_PGA_P4_PGA_2_PVT_H

#include "PGA_2.h"


/***************************************
*         Internal Constants
***************************************/
    
#define PGA_2_POWER                  ((uint32)3u)
#define PGA_2_GAIN                   ((uint32)0u)
    
#define PGA_2_POWER_MAX              (PGA_2_HIGH)
#define PGA_2_GAIN_MAX               (PGA_2_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define PGA_2_COMP_TAB_HEIGHT        ((PGA_2_GAIN_MAX >> 1u) + 1u)
#define PGA_2_COMP_TAB_WIDTH         (PGA_2_POWER_MAX)
#define PGA_2_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define PGA_2_VREF_INTERNAL          (0u)
#define PGA_2_OUTPUT_MODE_10x        (1u)

#define PGA_2_DEFAULT_POWER          ((uint32)PGA_2_POWER << PGA_2_OA_PWR_MODE_SHIFT)
#define PGA_2_DEFAULT_GAIN           ((uint32)PGA_2_GAIN << PGA_2_RES_TAP_SHIFT)
#define PGA_2_DEFAULT_GAIN_POWER     (PGA_2_DEFAULT_GAIN | PGA_2_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 PGA_2_internalGainPower;
extern const uint32 PGA_2_compTab[PGA_2_COMP_TAB_HEIGHT][PGA_2_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define PGA_2_CHECK_DEEPSLEEP_SUPPORT (PGA_2_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define PGA_2_CHECK_OUTPUT_MODE      (PGA_2_OUTPUT_MODE == PGA_2_OUTPUT_MODE_10x)
#define PGA_2_GET_DEEPSLEEP_ON       ((PGA_2_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (PGA_2_DEEPSLEEP_ON) : (0u))
#define PGA_2_GET_OA_DRIVE_STR       ((PGA_2_CHECK_OUTPUT_MODE) ? \
                                                    (PGA_2_OA_DRIVE_STR_SEL_10X) : \
                                                        (PGA_2_OA_DRIVE_STR_SEL_1X))
#define PGA_2_GET_POWER              (PGA_2_internalGainPower & \
                                                    PGA_2_OA_PWR_MODE_MASK)
#define PGA_2_DEFAULT_CTB_CTRL       (PGA_2_GET_DEEPSLEEP_ON | PGA_2_ENABLED)
#define PGA_2_DEFAULT_OA_RES_CTRL    (PGA_2_GET_OA_DRIVE_STR | PGA_2_OA_PUMP_EN)
#define PGA_2_DEFAULT_OA_RES_CTRL_MASK (PGA_2_OA_DRIVE_STR_SEL_MASK | PGA_2_OA_PUMP_EN)
#define PGA_2_GET_COMP_TAB_GAIN      ((PGA_2_internalGainPower >> \
                                                    (PGA_2_RES_TAP_SHIFT + 1u)) & \
                                                        PGA_2_GET_COMP_TAB_GAIN_MASK)
#define PGA_2_GET_COMP_TAB           (PGA_2_compTab[PGA_2_GET_COMP_TAB_GAIN] \
                                                                         [PGA_2_GET_POWER - 1u])
#define PGA_2_GET_C_FB               (PGA_2_GET_COMP_TAB & PGA_2_C_FB_MASK)
#define PGA_2_GET_OA_COMP_TRIM       (PGA_2_GET_COMP_TAB & PGA_2_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_PGA_2_PVT_H */

/* [] END OF FILE */
