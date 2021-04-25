/*******************************************************************************
* File Name: VTest.h  
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

#if !defined(CY_PINS_VTest_ALIASES_H) /* Pins VTest_ALIASES_H */
#define CY_PINS_VTest_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VTest_0			(VTest__0__PC)
#define VTest_0_PS		(VTest__0__PS)
#define VTest_0_PC		(VTest__0__PC)
#define VTest_0_DR		(VTest__0__DR)
#define VTest_0_SHIFT	(VTest__0__SHIFT)
#define VTest_0_INTR	((uint16)((uint16)0x0003u << (VTest__0__SHIFT*2u)))

#define VTest_INTR_ALL	 ((uint16)(VTest_0_INTR))


#endif /* End Pins VTest_ALIASES_H */


/* [] END OF FILE */
