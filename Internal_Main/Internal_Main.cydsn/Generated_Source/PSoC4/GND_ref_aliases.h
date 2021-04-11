/*******************************************************************************
* File Name: GND_ref.h  
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

#if !defined(CY_PINS_GND_ref_ALIASES_H) /* Pins GND_ref_ALIASES_H */
#define CY_PINS_GND_ref_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GND_ref_0			(GND_ref__0__PC)
#define GND_ref_0_PS		(GND_ref__0__PS)
#define GND_ref_0_PC		(GND_ref__0__PC)
#define GND_ref_0_DR		(GND_ref__0__DR)
#define GND_ref_0_SHIFT	(GND_ref__0__SHIFT)
#define GND_ref_0_INTR	((uint16)((uint16)0x0003u << (GND_ref__0__SHIFT*2u)))

#define GND_ref_INTR_ALL	 ((uint16)(GND_ref_0_INTR))


#endif /* End Pins GND_ref_ALIASES_H */


/* [] END OF FILE */
