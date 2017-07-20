/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFParamsExt.h
*	Description	:
*
*	Author		: 
*	Date created: 07-05-2012
* 	Project		: Basket ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHParamsExt.h>
#include "CHODFGUI.h"

class CHODFParamsExt : public ODFTHParamsExt
{
public:
	
	CHODFParamsExt(long id,CHODFGUI * pGUI);
	virtual ~CHODFParamsExt();
	
	void fillParamsCollection(bool gridCall,MSLSet & col,TypeParam type);
	void fillVectorParams(ODFMessage * pMessage,MSLArray& vParams,bool gridCall);
	MSLWString getParamDescription(void * pParam);
	MSLWString getMatchDescription(GTHMatch * pMatch);

private:

	CHODFGUI * m_pGUI;
};
