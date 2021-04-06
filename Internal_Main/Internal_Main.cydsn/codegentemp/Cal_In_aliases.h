/*******************************************************************************
* File Name: Cal_in.h  
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

#if !defined(CY_PINS_Cal_in_ALIASES_H) /* Pins Cal_in_ALIASES_H */
#define CY_PINS_Cal_in_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Cal_in_0			(Cal_in__0__PC)
#define Cal_in_0_PS		(Cal_in__0__PS)
#define Cal_in_0_PC		(Cal_in__0__PC)
#define Cal_in_0_DR		(Cal_in__0__DR)
#define Cal_in_0_SHIFT	(Cal_in__0__SHIFT)
#define Cal_in_0_INTR	((uint16)((uint16)0x0003u << (Cal_in__0__SHIFT*2u)))

#define Cal_in_INTR_ALL	 ((uint16)(Cal_in_0_INTR))


#endif /* End Pins Cal_in_ALIASES_H */


/* [] END OF FILE */
