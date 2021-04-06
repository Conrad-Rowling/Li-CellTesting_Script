/*******************************************************************************
* File Name: bgRef.h  
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

#if !defined(CY_PINS_bgRef_ALIASES_H) /* Pins bgRef_ALIASES_H */
#define CY_PINS_bgRef_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define bgRef_0			(bgRef__0__PC)
#define bgRef_0_PS		(bgRef__0__PS)
#define bgRef_0_PC		(bgRef__0__PC)
#define bgRef_0_DR		(bgRef__0__DR)
#define bgRef_0_SHIFT	(bgRef__0__SHIFT)
#define bgRef_0_INTR	((uint16)((uint16)0x0003u << (bgRef__0__SHIFT*2u)))

#define bgRef_INTR_ALL	 ((uint16)(bgRef_0_INTR))


#endif /* End Pins bgRef_ALIASES_H */


/* [] END OF FILE */
