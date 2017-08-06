/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFLoadInscription.h
*	Description	:
*
*	Author		: 
*	Date created: 
* 	Project		: ARManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <ovr\gui\mslipctransfer\ODFLoadInscription.h>

class CHODFLoadInscription : public ODFLoadInscription
{
public:
	CHODFLoadInscription(GInscription* pInsc, MSLIPCDataTransferModule* module);
	virtual ~CHODFLoadInscription();

	void onEventEntry(XMLElement * pElEventEntry, bool isTeam);
	void onMemberEventEntry(XMLElement * pElEventEntry, GMember* pMember);
	short getMasterTypeCode		(MSLString value);
};

