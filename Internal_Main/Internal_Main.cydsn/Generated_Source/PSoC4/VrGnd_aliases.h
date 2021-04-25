/*******************************************************************************
* File Name: VrGnd.h  
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

#if !defined(CY_PINS_VrGnd_ALIASES_H) /* Pins VrGnd_ALIASES_H */
#define CY_PINS_VrGnd_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VrGnd_0			(VrGnd__0__PC)
#define VrGnd_0_PS		(VrGnd__0__PS)
#define VrGnd_0_PC		(VrGnd__0__PC)
#define VrGnd_0_DR		(VrGnd__0__DR)
#define VrGnd_0_SHIFT	(VrGnd__0__SHIFT)
#define VrGnd_0_INTR	((uint16)((uint16)0x0003u << (VrGnd__0__SHIFT*2u)))

#define VrGnd_INTR_ALL	 ((uint16)(VrGnd_0_INTR))


#endif /* End Pins VrGnd_ALIASES_H */


/* [] END OF FILE */
