/*******************************************************************************
* File Name: Shunt_gnd.h  
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

#if !defined(CY_PINS_Shunt_gnd_ALIASES_H) /* Pins Shunt_gnd_ALIASES_H */
#define CY_PINS_Shunt_gnd_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Shunt_gnd_0			(Shunt_gnd__0__PC)
#define Shunt_gnd_0_PS		(Shunt_gnd__0__PS)
#define Shunt_gnd_0_PC		(Shunt_gnd__0__PC)
#define Shunt_gnd_0_DR		(Shunt_gnd__0__DR)
#define Shunt_gnd_0_SHIFT	(Shunt_gnd__0__SHIFT)
#define Shunt_gnd_0_INTR	((uint16)((uint16)0x0003u << (Shunt_gnd__0__SHIFT*2u)))

#define Shunt_gnd_INTR_ALL	 ((uint16)(Shunt_gnd_0_INTR))


#endif /* End Pins Shunt_gnd_ALIASES_H */


/* [] END OF FILE */
