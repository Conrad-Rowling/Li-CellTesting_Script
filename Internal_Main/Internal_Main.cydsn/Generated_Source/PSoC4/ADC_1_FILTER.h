/***************************************************************************//**
* \file     ADC_1_FILTER.c
* \version  3.10
*
* \brief
* Provides filter defines to the API for the ADC_1 Component.
*
********************************************************************************
* \copyright
* (c) 2015-2018, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(CY_ADC_1_FILTER_H)
    #define CY_ADC_1_FILTER_H


#define ADC_1_FILTER_CFG0_FILTER_PRESENT          (0uL)
#define ADC_1_FILTER_CFG1_FILTER_PRESENT          (0uL)
#define ADC_1_FILTER_CFG2_FILTER_PRESENT          (0uL)
#define ADC_1_FILTER_CFG3_FILTER_PRESENT          (0uL)

#define ADC_1_FILTER_ANY_CONFIG_USES_FILTER       ( ADC_1_FILTER_CFG0_FILTER_PRESENT \
                                                             | ADC_1_FILTER_CFG1_FILTER_PRESENT \
                                                             | ADC_1_FILTER_CFG2_FILTER_PRESENT \
                                                             | ADC_1_FILTER_CFG3_FILTER_PRESENT \
                                                             )


#if(ADC_1_FILTER_ANY_CONFIG_USES_FILTER  != 0u)

#include "ADC_1_UABH_A_CyUAB_types.h"
#include "ADC_1_UABH_A_CyUAB_regs.h"
#include "ADC_1_UABH_A_CyUAB.h"
#include "ADC_1_UABH_A_param.h"
#include "ADC_1_UABH_B_param.h"
#include "ADC_1_UABH_A_regs.h"
#include "ADC_1_UABH_B_regs.h"
#include "ADC_1_UABH_A.h"
#include "ADC_1_UABH_B.h"

/*******************************************************************************
* Filter function prototypes
*******************************************************************************/
void ADC_1_TrimFilterVos(void);
void ADC_1_filterInit(uint32 configNum);

/*******************************************************************************
* Filter trim constants and macros
*******************************************************************************/
#define ADC_1_OPAMP_TRIM_POS_BASE     (0x00uL)
#define ADC_1_OPAMP_TRIM_POS_LIMIT    (0x08uL)
#define ADC_1_OPAMP_TRIM_NEG_BASE     (ADC_1_OPAMP_TRIM_POS_LIMIT)
#define ADC_1_OPAMP_TRIM_NEG_LIMIT    (0x10uL)
#define ADC_1_OPAMP_TRIM_MASK         (0x0fuL)

#define ADC_1_AGND_TRIM_POS_BASE      (0x00uL)
#define ADC_1_AGND_TRIM_POS_LIMIT     (0x10uL)
#define ADC_1_AGND_TRIM_NEG_BASE      (ADC_1_AGND_TRIM_POS_LIMIT)
#define ADC_1_AGND_TRIM_NEG_LIMIT     (0x20uL)
#define ADC_1_AGND_TRIM_MASK          (0x1fuL)

/*******************************************************************************
* Filter Parameters
*******************************************************************************/
#define ADC_1_FILTER_ADC_CHANNEL     (0UL)
#define ADC_1_FILTER_AMUX_CHANNEL    (4U)

#define ADC_1_FILTERTOPOLOGY_HIGH_Q  (0u)
#define ADC_1_FILTERTOPOLOGY_LOW_Q   (1u)

#define ADC_1_TRANSFERTYPE_LOW_PASS (0u)
#define ADC_1_TRANSFERTYPE_HIGH_PASS (1u)
#define ADC_1_TRANSFERTYPE_BAND_PASS (2u)
#define ADC_1_TRANSFERTYPE_BAND_STOP (3u)


#define ADC_1_UABH_A_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT) \
                                                    |  (uint32)((uint32)3u << CyUAB_LAST_STEP_SHIFT))
#define ADC_1_UABH_B_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT) \
                                                    |  (uint32)((uint32)3u << CyUAB_LAST_STEP_SHIFT))
#define ADC_1_UABH_A_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))
#define ADC_1_UABH_B_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))

#define ADC_1_UABH_ALL_OPEN_CC_IN0   (uint32)((CyUAB_CLK_PHI4 << CyUAB_SW_C0_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_C1_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_C2_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_C3_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_CP_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_CQ_SHIFT))

#define ADC_1_UABH_ALL_OPEN_CB_IN0   (uint32)((CyUAB_CLK_PHI4 << CyUAB_SW_B0_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_B1_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_B2_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_B3_MODBIT_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_BP_SHIFT) \
                                                    |       (CyUAB_CLK_PHI4 << CyUAB_SW_BQ_SHIFT))

/*******************************************************************************
* Low-Q definitions
*******************************************************************************/

#define ADC_1_UABH_A_LOWQSTAT_SW_CA_IN0 ((CyUAB_CLK_PHI5 << CyUAB_SW_AP_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AQ_SHIFT))

#define ADC_1_UABH_A_LOWQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SA_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VA_MODBIT_SHIFT))

#define ADC_1_UABH_A_LOWQSTAT_SW_CC_IN0 ((CyUAB_CLK_PHI1 << CyUAB_SW_CQ_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_C0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_C1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_C2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_C3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CP_SHIFT))

#define ADC_1_UABH_A_LOWQSTAT_SW_CC_IN1 ((CyUAB_CLK_PHI2 << CyUAB_SW_CG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CC_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CR_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CV_MODBIT_SHIFT))

#define ADC_1_UABH_A_LOWQSTAT_SW_CF_BOT ((CyUAB_CLK_PHI5 << CyUAB_SW_PF_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GF_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_PS_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_PO_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CA_IN0 ((CyUAB_CLK_PHI2 << CyUAB_SW_AP_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AQ_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CA_IN1 ((CyUAB_CLK_PHI1 << CyUAB_SW_AG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AA_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AR_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AV_MODBIT_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI2 << CyUAB_SW_SA_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI1 << CyUAB_SW_GA_MODBIT_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CB_IN0 ((CyUAB_CLK_PHI1 << CyUAB_SW_BQ_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BP_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CB_IN1 ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CB_TOP ((CyUAB_CLK_PHI2 << CyUAB_SW_SB_SHIFT) \
                                                 | (CyUAB_CLK_PHI1 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                 | (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                 | (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                 | (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT))


#define ADC_1_UABH_B_LOWQSTAT_SW_CC_IN0 ((ADC_1_UABH_ALL_OPEN_CC_IN0 \
                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_B_halfuab__X0 << 2u))) \
                                                |   ((uint32)CyUAB_CLK_PHI5 << (ADC_1_UABH_B_halfuab__X0 << 2u)))

#define ADC_1_UABH_B_LOWQSTAT_SW_CC_IN1 ((CyUAB_CLK_PHI4 << CyUAB_SW_CG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CR_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CV_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CC_SHIFT))

#define ADC_1_UABH_B_LOWQSTAT_SW_CF_BOT ((CyUAB_CLK_PHI5 << CyUAB_SW_PF_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GF_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_PS_SHIFT) \
                                                |   (CyUAB_CLK_PHI3 << CyUAB_SW_PO_SHIFT))


/*******************************************************************************
* High-Q definitions
*******************************************************************************/

#define ADC_1_UABH_A_HIGHQSTAT_SW_CA_IN0 ((CyUAB_CLK_PHI5 << CyUAB_SW_AQ_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_A3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AP_SHIFT))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SA_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GA_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VA_MODBIT_SHIFT))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CB_IN0 ((CyUAB_CLK_PHI1 << CyUAB_SW_BQ_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B0_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B1_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B2_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_B3_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BP_SHIFT))


#define ADC_1_UABH_A_HIGHQSTAT_SW_CB_IN1 ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CC_IN0 ((ADC_1_UABH_ALL_OPEN_CC_IN0 \
                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                |   (uint32)CyUAB_CLK_PHI5 << (ADC_1_UABH_A_halfuab__X0 << 2u))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CC_IN1 ((CyUAB_CLK_PHI4 << CyUAB_SW_CG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CR_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CV_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_CC_SHIFT))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CC_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_TC_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                |    (CyUAB_CLK_PHI5 << CyUAB_SW_SC_SHIFT))

#define ADC_1_UABH_A_HIGHQSTAT_SW_CF_BOT ((CyUAB_CLK_PHI5 << CyUAB_SW_PF_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_GF_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_PS_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_PO_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CA_IN0 ((CyUAB_CLK_PHI1 << CyUAB_SW_AQ_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_A0_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_A1_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_A2_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_A3_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_AP_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CA_IN1 ((CyUAB_CLK_PHI2 << CyUAB_SW_AG_MODBIT_SHIFT) \
                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_AA_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_AR_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_AV_MODBIT_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_GA_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_RA_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_VA_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI2 << CyUAB_SW_SA_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CB_IN0 ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_B_halfuab__X0 << 2u))) \
                                                |   CyUAB_CLK_PHI5 << (ADC_1_UABH_B_halfuab__X0 << 2u))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CB_IN1 ((CyUAB_CLK_PHI4 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CC_IN0 ((ADC_1_UABH_ALL_OPEN_CC_IN0 \
                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_B_halfuab__X0 << 2u))) \
                                                |   (uint32)CyUAB_CLK_PHI1 << (ADC_1_UABH_B_halfuab__X0 << 2u))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CC_IN1 ((CyUAB_CLK_PHI2 << CyUAB_SW_CG_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_CR_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_CV_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_CC_SHIFT))

#define ADC_1_UABH_B_HIGHQSTAT_SW_CF_BOT ((CyUAB_CLK_PHI5 << CyUAB_SW_PF_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_GF_SHIFT) \
                                                |    (CyUAB_CLK_PHI4 << CyUAB_SW_PS_SHIFT) \
                                                |    (CyUAB_CLK_PHI3 << CyUAB_SW_PO_SHIFT))


/*******************************************************************************
* CFG0 definitions
*******************************************************************************/
#if (0u != ADC_1_FILTER_CFG0_FILTER_PRESENT)

    #define ADC_1_CFG0_FILTERTYPE_USED   ADC_1_FILTERTOPOLOGY_LOW_Q
    #define ADC_1_CFG0_TRANSFERTYPE      ADC_1_TRANSFERTYPE_LOW_PASS
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL    (0ul)
    #define ADC_1_CFG0_FILTER_GT_C1_DENOMINATOR_VAL  (1ul)
    #define ADC_1_CFG0_FILTER_GT_C2_NUMERATOR_VAL    (0ul)
    #define ADC_1_CFG0_FILTER_GT_C2_DENOMINATOR_VAL  (1ul)
    #define ADC_1_CFG0_FILTER_GT_C3_VAL              (0ul)
    #define ADC_1_CFG0_FILTER_GT_C4_VAL              (0ul)
    #define ADC_1_CFG0_FILTER_GT_Cp_VAL              (0ul)
    #define ADC_1_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL   (0ul)
    #define ADC_1_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL (1ul)
    #define ADC_1_CFG0_FILTER_GT_CA_VAL              (0ul)
    #define ADC_1_CFG0_FILTER_GT_CB_VAL              (0ul)

    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_NUM0      (0)
    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_NUM1      (0)
    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_NUM2      (0)
    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_DEN0      (0)
    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_DEN1      (0)
    #define ADC_1_CFG0_FILTER_IDEAL_BIQUAD_DEN2      (0)

    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_NUM0        (0)
    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_NUM1        (0)
    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_NUM2        (0)
    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_DEN0        (0)
    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_DEN1        (0)
    #define ADC_1_CFG0_FILTER_UAB_BIQUAD_DEN2        (0)

    #define ADC_1_CFG0_UABH_A_STARTUP_DELAY    ((uint32)((uint32)0u << CyUAB_STARTUP_DELAY_SHIFT))
    #define ADC_1_CFG0_UABH_B_STARTUP_DELAY    ((uint32)((uint32)0u << CyUAB_STARTUP_DELAY_SHIFT))

    #if (ADC_1_CFG0_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == ADC_1_CFG0_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG0_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(ADC_1_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE (ADC_1_CFG0_FILTER_GT_CA_VAL/4u)
        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(ADC_1_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((ADC_1_CFG0_FILTER_GT_CA_VAL - (2u * (ADC_1_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_ABCF_VAL ((ADC_1_CFG0_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (ADC_1_CFG0_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (ADC_1_CFG0_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (ADC_1_CFG0_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG0_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG0_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(ADC_1_CFG0_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (uint32)(ADC_1_CFG0_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (uint32)(ADC_1_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | (uint32)((uint32)((ADC_1_CFG0_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG0_UABH_A_LOWQDYN_CAP_CTRL ((((ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) \
                                                           && (ADC_1_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                         | ((ADC_1_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))
        #if (ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   ((uint32)CyUAB_CLK_PHI1 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                              | (((ADC_1_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u) \
                                                                  ? CyUAB_CLK_PHI2 \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_IN0  ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   (CyUAB_CLK_PHI5 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_IN1  ((CyUAB_CLK_PHI4 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CB_TOP  ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT))
        #endif /* (ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define ADC_1_CFG0_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                           | (((ADC_1_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2 \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define ADC_1_CFG0_UABH_B_LOWQDYN_CAP_CTRL     ((ADC_1_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u)
        #define ADC_1_CFG0_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SC_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                            | (((ADC_1_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_CLK_PHI4 \
                                                            : CyUAB_CLK_PHI5 ) << CyUAB_SW_TC_SHIFT))

    /*******************************************************************************
    * CFG0 High-Q definitions
    *******************************************************************************/

    #elif (ADC_1_CFG0_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define ADC_1_CFG0_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG0_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (ADC_1_CFG0_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT) \
                                                            | (ADC_1_CFG0_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                            | ((uint32)((ADC_1_CFG0_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG0_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (ADC_1_CFG0_FILTER_GT_C3_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (ADC_1_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | ((uint32)((ADC_1_CFG0_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG0_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG0_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI4 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))
        #define ADC_1_CFG0_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_SC_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT)) \
                                                        |  ((1u < ADC_1_CFG0_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TC_SHIFT)))

        #define ADC_1_CFG0_UABH_A_HIGHQDYN_CAP_CTRL ((1u < ADC_1_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u )

        #define ADC_1_CFG0_UABH_B_HIGHQDYN_CAP_CTRL (((1u < ADC_1_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                        | ((1u < ADC_1_CFG0_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))

    #endif /*(ADC_1_CFG0_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != ADC_1_FILTER_CFG0_FILTER_PRESENT) */
/*******************************************************************************
* CFG1 definitions
*******************************************************************************/
#if (0u != ADC_1_FILTER_CFG1_FILTER_PRESENT)

    #define ADC_1_CFG1_FILTERTYPE_USED   ADC_1_FILTERTOPOLOGY_
    #define ADC_1_CFG1_TRANSFERTYPE      ADC_1_TRANSFERTYPE_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG1_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG1_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG1_FILTER_GT_C2_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG1_FILTER_GT_C3_VAL              (ul)
    #define ADC_1_CFG1_FILTER_GT_C4_VAL              (ul)
    #define ADC_1_CFG1_FILTER_GT_Cp_VAL              (ul)
    #define ADC_1_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)
    #define ADC_1_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)
    #define ADC_1_CFG1_FILTER_GT_CA_VAL              (ul)
    #define ADC_1_CFG1_FILTER_GT_CB_VAL              (ul)

    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define ADC_1_CFG1_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_NUM0        ()
    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_NUM1        ()
    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_NUM2        ()
    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_DEN0        ()
    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_DEN1        ()
    #define ADC_1_CFG1_FILTER_UAB_BIQUAD_DEN2        ()

    #define ADC_1_CFG1_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define ADC_1_CFG1_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))

    #if (ADC_1_CFG1_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == ADC_1_CFG1_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG1_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(ADC_1_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE (ADC_1_CFG1_FILTER_GT_CA_VAL/4u)
        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(ADC_1_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((ADC_1_CFG1_FILTER_GT_CA_VAL - (2u * (ADC_1_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_ABCF_VAL ((ADC_1_CFG1_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (ADC_1_CFG1_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (ADC_1_CFG1_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (ADC_1_CFG1_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG1_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG1_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(ADC_1_CFG1_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (uint32)(ADC_1_CFG1_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (uint32)(ADC_1_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | (uint32)((uint32)((ADC_1_CFG1_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG1_UABH_A_LOWQDYN_CAP_CTRL ((((ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) \
                                                           && (ADC_1_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                         | ((ADC_1_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))
        #if (ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   ((uint32)CyUAB_CLK_PHI1 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                              | (((ADC_1_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u) \
                                                                  ? CyUAB_CLK_PHI2 \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   (CyUAB_CLK_PHI5 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI4 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                                | (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT))
        #endif /* (ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define ADC_1_CFG1_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                           | (((ADC_1_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2 \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define ADC_1_CFG1_UABH_B_LOWQDYN_CAP_CTRL     ((ADC_1_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u)
        #define ADC_1_CFG1_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SC_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                            | (((ADC_1_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_CLK_PHI4 \
                                                            : CyUAB_CLK_PHI5 ) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG1 High-Q definitions
    *******************************************************************************/

    #elif (ADC_1_CFG1_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define ADC_1_CFG1_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG1_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (ADC_1_CFG1_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT) \
                                                            | (ADC_1_CFG1_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                            | ((uint32)((ADC_1_CFG1_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG1_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (ADC_1_CFG1_FILTER_GT_C3_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (ADC_1_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | ((uint32)((ADC_1_CFG1_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG1_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG1_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI4 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))
        #define ADC_1_CFG1_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_SC_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT)) \
                                                        |  ((1u < ADC_1_CFG1_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TC_SHIFT)))

        #define ADC_1_CFG1_UABH_A_HIGHQDYN_CAP_CTRL ((1u < ADC_1_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u )

        #define ADC_1_CFG1_UABH_B_HIGHQDYN_CAP_CTRL (((1u < ADC_1_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                        | ((1u < ADC_1_CFG1_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))

    #endif /*(ADC_1_CFG1_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != ADC_1_FILTER_CFG1_FILTER_PRESENT) */

/*******************************************************************************
* CFG2 definitions
*******************************************************************************/
#if (0u != ADC_1_FILTER_CFG2_FILTER_PRESENT)

    #define ADC_1_CFG2_FILTERTYPE_USED   ADC_1_FILTERTOPOLOGY_
    #define ADC_1_CFG2_TRANSFERTYPE      ADC_1_TRANSFERTYPE_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG2_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG2_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG2_FILTER_GT_C2_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG2_FILTER_GT_C3_VAL              (ul)
    #define ADC_1_CFG2_FILTER_GT_C4_VAL              (ul)
    #define ADC_1_CFG2_FILTER_GT_Cp_VAL              (ul)
    #define ADC_1_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)
    #define ADC_1_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)
    #define ADC_1_CFG2_FILTER_GT_CA_VAL              (ul)
    #define ADC_1_CFG2_FILTER_GT_CB_VAL              (ul)

    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define ADC_1_CFG2_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_NUM0        ()
    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_NUM1        ()
    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_NUM2        ()
    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_DEN0        ()
    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_DEN1        ()
    #define ADC_1_CFG2_FILTER_UAB_BIQUAD_DEN2        ()

    #define ADC_1_CFG2_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define ADC_1_CFG2_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))

    #if (ADC_1_CFG2_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == ADC_1_CFG2_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG2_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(ADC_1_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE (ADC_1_CFG2_FILTER_GT_CA_VAL/4u)
        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(ADC_1_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((ADC_1_CFG2_FILTER_GT_CA_VAL - (2u * (ADC_1_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_ABCF_VAL ((ADC_1_CFG2_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (ADC_1_CFG2_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (ADC_1_CFG2_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (ADC_1_CFG2_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG2_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG2_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(ADC_1_CFG2_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (uint32)(ADC_1_CFG2_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (uint32)(ADC_1_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | (uint32)((uint32)((ADC_1_CFG2_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG2_UABH_A_LOWQDYN_CAP_CTRL ((((ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) \
                                                           && (ADC_1_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                         | ((ADC_1_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))
        #if (ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   ((uint32)CyUAB_CLK_PHI1 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                              | (((ADC_1_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u) \
                                                                  ? CyUAB_CLK_PHI2 \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   (CyUAB_CLK_PHI5 << (ADC_1_UABH_A_halfuab__X0 << 2u))

            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI4 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT))
        #endif /* (ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define ADC_1_CFG2_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                           |  (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                           | (((ADC_1_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2 \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))

        #define ADC_1_CFG2_UABH_B_LOWQDYN_CAP_CTRL     ((ADC_1_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u)

        #define ADC_1_CFG2_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SC_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                            | (((ADC_1_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_CLK_PHI4 \
                                                            : CyUAB_CLK_PHI5 ) << CyUAB_SW_TC_SHIFT))

    /*******************************************************************************
    * CFG2 High-Q definitions
    *******************************************************************************/

    #elif (ADC_1_CFG2_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define ADC_1_CFG2_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG2_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (ADC_1_CFG2_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT) \
                                                            | (ADC_1_CFG2_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                            | ((uint32)((ADC_1_CFG2_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG2_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (ADC_1_CFG2_FILTER_GT_C3_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (ADC_1_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | ((uint32)((ADC_1_CFG2_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG2_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG2_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI4 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG2_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_SC_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT)) \
                                                        |  ((1u < ADC_1_CFG2_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TC_SHIFT)))

        #define ADC_1_CFG2_UABH_A_HIGHQDYN_CAP_CTRL ((1u < ADC_1_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u )

        #define ADC_1_CFG2_UABH_B_HIGHQDYN_CAP_CTRL (((1u < ADC_1_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                        | ((1u < ADC_1_CFG2_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))

    #endif /*(ADC_1_CFG2_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != ADC_1_FILTER_CFG2_FILTER_PRESENT) */

/*******************************************************************************
* CFG3 definitions
*******************************************************************************/
#if (0u != ADC_1_FILTER_CFG3_FILTER_PRESENT)

    #define ADC_1_CFG3_FILTERTYPE_USED   ADC_1_FILTERTOPOLOGY_
    #define ADC_1_CFG3_TRANSFERTYPE      ADC_1_TRANSFERTYPE_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG3_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG3_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define ADC_1_CFG3_FILTER_GT_C2_DENOMINATOR_VAL  (ul)
    #define ADC_1_CFG3_FILTER_GT_C3_VAL              (ul)
    #define ADC_1_CFG3_FILTER_GT_C4_VAL              (ul)
    #define ADC_1_CFG3_FILTER_GT_Cp_VAL              (ul)
    #define ADC_1_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)
    #define ADC_1_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)
    #define ADC_1_CFG3_FILTER_GT_CA_VAL              (ul)
    #define ADC_1_CFG3_FILTER_GT_CB_VAL              (ul)

    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define ADC_1_CFG3_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_NUM0        ()
    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_NUM1        ()
    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_NUM2        ()
    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_DEN0        ()
    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_DEN1        ()
    #define ADC_1_CFG3_FILTER_UAB_BIQUAD_DEN2        ()

    #define ADC_1_CFG3_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define ADC_1_CFG3_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))

    #if (ADC_1_CFG3_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == ADC_1_CFG3_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(ADC_1_CFG3_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(ADC_1_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE (ADC_1_CFG3_FILTER_GT_CA_VAL/4u)
        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(ADC_1_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((ADC_1_CFG3_FILTER_GT_CA_VAL - (2u * (ADC_1_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_ABCF_VAL ((ADC_1_CFG3_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (ADC_1_CFG3_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (ADC_1_CFG3_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (ADC_1_CFG3_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG3_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG3_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(ADC_1_CFG3_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (uint32)(ADC_1_CFG3_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (uint32)(ADC_1_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | (uint32)((uint32)((ADC_1_CFG3_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG3_UABH_A_LOWQDYN_CAP_CTRL ((((ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) \
                                                           && (ADC_1_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                         | ((ADC_1_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))
        #if (ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   ((uint32)CyUAB_CLK_PHI1 << (ADC_1_UABH_A_halfuab__X0 << 2u)))

            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                              |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                              | (((ADC_1_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u) \
                                                                  ? CyUAB_CLK_PHI2 \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    ((ADC_1_UABH_ALL_OPEN_CB_IN0 \
                                                                &   ~((uint32)CyUAB_CLOCK_MASK << (ADC_1_UABH_A_halfuab__X0 << 2u))) \
                                                                |   (CyUAB_CLK_PHI5 << (ADC_1_UABH_A_halfuab__X0 << 2u))

            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    ((CyUAB_CLK_PHI4 << CyUAB_SW_BG_MODBIT_SHIFT) \
                                                                |       (CyUAB_CLK_PHI4 << CyUAB_SW_BR_MODBIT_SHIFT) \
                                                                |       (CyUAB_CLK_PHI4 << CyUAB_SW_BV_MODBIT_SHIFT) \
                                                                |       (CyUAB_CLK_PHI4 << CyUAB_SW_BB_SHIFT))

            #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                                |   (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                                | (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT))
        #endif /* (ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define ADC_1_CFG3_UABH_A_LOWQDYN_SW_CC_TOP     ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT) \
                                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                                |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                                |  (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                                | (((ADC_1_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                                ? CyUAB_CLK_PHI2 \
                                                                : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define ADC_1_CFG3_UABH_B_LOWQDYN_CAP_CTRL     ((ADC_1_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u)
        #define ADC_1_CFG3_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI5 << CyUAB_SW_SC_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_GC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT) \
                                                            | (CyUAB_CLK_PHI4 << CyUAB_SW_ZC_SHIFT) \
                                                            | (((ADC_1_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_CLK_PHI4 \
                                                            : CyUAB_CLK_PHI5 ) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG3 High-Q definitions
    *******************************************************************************/

    #elif (ADC_1_CFG3_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define ADC_1_CFG3_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG3_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (ADC_1_CFG3_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT) \
                                                            | (ADC_1_CFG3_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT) \
                                                            | ((uint32)((ADC_1_CFG3_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define ADC_1_CFG3_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == ADC_1_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (ADC_1_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (ADC_1_CFG3_FILTER_GT_C3_VAL << CyUAB_CA_VAL_SHIFT) \
                                                       | (ADC_1_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT) \
                                                       | ((uint32)((ADC_1_CFG3_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define ADC_1_CFG3_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG3_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI5 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_RB_MODBIT_SHIFT) \
                                                        |  (CyUAB_CLK_PHI4 << CyUAB_SW_VB_MODBIT_SHIFT) \
                                                        |  ((1u < ADC_1_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI4 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TB_SHIFT)))

        #define ADC_1_CFG3_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_SC_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_RC_MODBIT_SHIFT)) \
                                                        |  ((CyUAB_CLK_PHI4 << CyUAB_SW_VC_MODBIT_SHIFT)) \
                                                        |  ((1u < ADC_1_CFG3_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_CLK_PHI5 << CyUAB_SW_TC_SHIFT)))

        #define ADC_1_CFG3_UABH_A_HIGHQDYN_CAP_CTRL ((1u < ADC_1_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u )

        #define ADC_1_CFG3_UABH_B_HIGHQDYN_CAP_CTRL (((1u < ADC_1_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT) \
                                                            : 0u) \
                                                        | ((1u < ADC_1_CFG3_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT) \
                                                            : 0u))

    #endif /*(ADC_1_CFG3_FILTERTYPE_USED == ADC_1_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != ADC_1_FILTER_CFG3_FILTER_PRESENT) */


#endif /* (ADC_1_ANY_CONFIG_USES_FILTER  != 0u)   */
#endif /* !defined(CY_ADC_1_FILTER_H) */
/* [] END OF FILE */
