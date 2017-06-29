/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC93.h
*	Description	:
*
*	Author		: M.
*	Date created: 19-10-2009
* 	Project		: AR(V) Dll
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHVMngtModelDefs.h"
#include <OVR/Reports/V/RC93.h>

class CHVMngtModelExport CHRC93 : public RC93
{
public:
	CHRC93(CReportManager& aRM,CReportConfig& aRC);
	virtual ~CHRC93(void);

	void	OnLisLoaded();		// Llamada para modificar variables y carteles del pBaseLis desde el .lis propio
	void	OnSortMedallist();
	void	OnGetMembers();		// para cada m_pCurrent carga en m_vMembers el nombre de los miembros del equipo en el orden requerido

	
};
