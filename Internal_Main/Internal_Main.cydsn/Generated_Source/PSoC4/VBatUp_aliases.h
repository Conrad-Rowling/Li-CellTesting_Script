/*******************************************************************************
* File Name: VBatUp.h  
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

#if !defined(CY_PINS_VBatUp_ALIASES_H) /* Pins VBatUp_ALIASES_H */
#define CY_PINS_VBatUp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VBatUp_0			(VBatUp__0__PC)
#define VBatUp_0_PS		(VBatUp__0__PS)
#define VBatUp_0_PC		(VBatUp__0__PC)
#define VBatUp_0_DR		(VBatUp__0__DR)
#define VBatUp_0_SHIFT	(VBatUp__0__SHIFT)
#define VBatUp_0_INTR	((uint16)((uint16)0x0003u << (VBatUp__0__SHIFT*2u)))

#define VBatUp_INTR_ALL	 ((uint16)(VBatUp_0_INTR))


#endif /* End Pins VBatUp_ALIASES_H */


/* [] END OF FILE */
