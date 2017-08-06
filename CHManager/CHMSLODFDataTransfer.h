/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMSLODFDataTransfer.h
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
#include <ovr\gui\MSLIPCTHTransfer\MSLIPCTHDataTransfer.h>

class CHMSLODFDataTransfer : public MSLIPCTHDataTransferModule
{
public:
	CHMSLODFDataTransfer(long id);
	~CHMSLODFDataTransfer();

protected:
		
	ODFLoadRegister*		onNewODFLoadRegister	(GRegister* pRegister);
	ODFLoadInscription*		onNewODFLoadInscription	(GInscription * pInscription);	
	void					onCreateInscription		(GInscription* pInscription);
	void					onCreateEventResult		(GEventResult * pEvResult);

	
};

