/***************************************************************************//**
* \file     PGA_4_PVT.h
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

#if !defined(CY_PGA_P4_PGA_4_PVT_H) 
#define CY_PGA_P4_PGA_4_PVT_H

#include "PGA_4.h"


/***************************************
*         Internal Constants
***************************************/
    
#define PGA_4_POWER                  ((uint32)3u)
#define PGA_4_GAIN                   ((uint32)6u)
    
#define PGA_4_POWER_MAX              (PGA_4_HIGH)
#define PGA_4_GAIN_MAX               (PGA_4_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define PGA_4_COMP_TAB_HEIGHT        ((PGA_4_GAIN_MAX >> 1u) + 1u)
#define PGA_4_COMP_TAB_WIDTH         (PGA_4_POWER_MAX)
#define PGA_4_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define PGA_4_VREF_INTERNAL          (0u)
#define PGA_4_OUTPUT_MODE_10x        (1u)

#define PGA_4_DEFAULT_POWER          ((uint32)PGA_4_POWER << PGA_4_OA_PWR_MODE_SHIFT)
#define PGA_4_DEFAULT_GAIN           ((uint32)PGA_4_GAIN << PGA_4_RES_TAP_SHIFT)
#define PGA_4_DEFAULT_GAIN_POWER     (PGA_4_DEFAULT_GAIN | PGA_4_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 PGA_4_internalGainPower;
extern const uint32 PGA_4_compTab[PGA_4_COMP_TAB_HEIGHT][PGA_4_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define PGA_4_CHECK_DEEPSLEEP_SUPPORT (PGA_4_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define PGA_4_CHECK_OUTPUT_MODE      (PGA_4_OUTPUT_MODE == PGA_4_OUTPUT_MODE_10x)
#define PGA_4_GET_DEEPSLEEP_ON       ((PGA_4_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (PGA_4_DEEPSLEEP_ON) : (0u))
#define PGA_4_GET_OA_DRIVE_STR       ((PGA_4_CHECK_OUTPUT_MODE) ? \
                                                    (PGA_4_OA_DRIVE_STR_SEL_10X) : \
                                                        (PGA_4_OA_DRIVE_STR_SEL_1X))
#define PGA_4_GET_POWER              (PGA_4_internalGainPower & \
                                                    PGA_4_OA_PWR_MODE_MASK)
#define PGA_4_DEFAULT_CTB_CTRL       (PGA_4_GET_DEEPSLEEP_ON | PGA_4_ENABLED)
#define PGA_4_DEFAULT_OA_RES_CTRL    (PGA_4_GET_OA_DRIVE_STR | PGA_4_OA_PUMP_EN)
#define PGA_4_DEFAULT_OA_RES_CTRL_MASK (PGA_4_OA_DRIVE_STR_SEL_MASK | PGA_4_OA_PUMP_EN)
#define PGA_4_GET_COMP_TAB_GAIN      ((PGA_4_internalGainPower >> \
                                                    (PGA_4_RES_TAP_SHIFT + 1u)) & \
                                                        PGA_4_GET_COMP_TAB_GAIN_MASK)
#define PGA_4_GET_COMP_TAB           (PGA_4_compTab[PGA_4_GET_COMP_TAB_GAIN] \
                                                                         [PGA_4_GET_POWER - 1u])
#define PGA_4_GET_C_FB               (PGA_4_GET_COMP_TAB & PGA_4_C_FB_MASK)
#define PGA_4_GET_OA_COMP_TRIM       (PGA_4_GET_COMP_TAB & PGA_4_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_PGA_4_PVT_H */

/* [] END OF FILE */
