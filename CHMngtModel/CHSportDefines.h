/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHSportDefines.h
*	Description	: CH Sport Defines.
*
*	Author		: Chess Team
*	Date created: 07-12-2002
* 	Project		: CH Model
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#ifndef _CHSPORTDEFINES_H_
#define _CHSPORTDEFINES_H_

// Sex
#define	MEN						 "0"
#define	WOMEN					 "1"
#define	MIXED					 "2"

// Qualitatives
#define	DSQ						 "d"
#define	FO						 "f"
#define	RET						 "r"
#define OK					     "0"

// Phases

// Points 
#define WIN_POINTS				  1
#define DRAW_POINTS				  0.5
#define LOST_POINTS				  0

#define WIN_POINTS_MEMBER		  2
#define DRAW_POINTS_MEMBER		  1
#define LOST_POINTS_MEMBER		  0


#define CH_RESULT_AWAY		1	// Away
#define CH_RESULT_HOME		0	// Home

#define	SWISS_SISTEM				 "1"


// Colores para los status.
#define COLORSTATUS_AVAILABLE	RGB(150,150,150)	// Gris Oscuro
#define COLORSTATUS_CONFIGURED	RGB(0,0,0)			// Negro
#define COLORSTATUS_SCHEDULLED	RGB(0,0,255)		// Azul
#define COLORSTATUS_STARTLIST	RGB(0,64,128)		// Azul Oscuro
#define COLORSTATUS_RUNNING		RGB(0,192,0)		// Verde
#define COLORSTATUS_UNOFFICIAL	RGB(255,128,128)	// Rosa
#define COLORSTATUS_FINISHED	RGB(255,0,0)		// Rojo
#define COLORSTATUS_REVISION	RGB(128,64,0)		// Marron
#define COLOR_NEGRO				RGB(  0,  0,  0)	// Negro
#define COLOR_BLANCO			RGB(255,255,255)	// Blanco



#endif // _CHSPORTDEFINES_H_