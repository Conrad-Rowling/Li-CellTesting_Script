/*******************************************************************************
* File Name: VBatHigh.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VBatHigh_ALIASES_H) /* Pins VBatHigh_ALIASES_H */
#define CY_PINS_VBatHigh_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VBatHigh_0			(VBatHigh__0__PC)
#define VBatHigh_0_PS		(VBatHigh__0__PS)
#define VBatHigh_0_PC		(VBatHigh__0__PC)
#define VBatHigh_0_DR		(VBatHigh__0__DR)
#define VBatHigh_0_SHIFT	(VBatHigh__0__SHIFT)
#define VBatHigh_0_INTR	((uint16)((uint16)0x0003u << (VBatHigh__0__SHIFT*2u)))

#define VBatHigh_INTR_ALL	 ((uint16)(VBatHigh_0_INTR))


#endif /* End Pins VBatHigh_ALIASES_H */


/* [] END OF FILE */
