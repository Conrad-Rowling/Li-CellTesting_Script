/*******************************************************************************
* File Name: Cal_In.h  
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

#if !defined(CY_PINS_Cal_In_ALIASES_H) /* Pins Cal_In_ALIASES_H */
#define CY_PINS_Cal_In_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Cal_In_0			(Cal_In__0__PC)
#define Cal_In_0_PS		(Cal_In__0__PS)
#define Cal_In_0_PC		(Cal_In__0__PC)
#define Cal_In_0_DR		(Cal_In__0__DR)
#define Cal_In_0_SHIFT	(Cal_In__0__SHIFT)
#define Cal_In_0_INTR	((uint16)((uint16)0x0003u << (Cal_In__0__SHIFT*2u)))

#define Cal_In_INTR_ALL	 ((uint16)(Cal_In_0_INTR))


#endif /* End Pins Cal_In_ALIASES_H */


/* [] END OF FILE */
