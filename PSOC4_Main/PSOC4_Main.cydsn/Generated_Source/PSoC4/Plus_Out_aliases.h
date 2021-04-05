/*******************************************************************************
* File Name: Plus_Out.h  
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

#if !defined(CY_PINS_Plus_Out_ALIASES_H) /* Pins Plus_Out_ALIASES_H */
#define CY_PINS_Plus_Out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Plus_Out_0			(Plus_Out__0__PC)
#define Plus_Out_0_PS		(Plus_Out__0__PS)
#define Plus_Out_0_PC		(Plus_Out__0__PC)
#define Plus_Out_0_DR		(Plus_Out__0__DR)
#define Plus_Out_0_SHIFT	(Plus_Out__0__SHIFT)
#define Plus_Out_0_INTR	((uint16)((uint16)0x0003u << (Plus_Out__0__SHIFT*2u)))

#define Plus_Out_INTR_ALL	 ((uint16)(Plus_Out_0_INTR))


#endif /* End Pins Plus_Out_ALIASES_H */


/* [] END OF FILE */
