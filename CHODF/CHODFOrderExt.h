/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFOrderExt.h
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
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHOrderExt.h>
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHParamsExt.h>
#include <OVR/GUI/ODF2/ODFMngr/ODFDataSend.h>

class CHODFOrderExt : public ODFTHOrderExt
{
public:
	CHODFOrderExt(long id,ODFGUI * pGUI);
	virtual ~CHODFOrderExt();

	//virtual from ODFOrderExt
	ODFParamsExt * onNewODFParams();

	bool	isFullResultsMessage();
	bool	processNoParamMessages();
	bool	processManualOrder(ODFOrder& aOrder);
	void	fillDocCodeOrder(ODFOrder& aOrder);
	void	processReportDistributed(const char * fileName,const wchar_t * comment);

	bool	processTransactions(MSLTransaction &pt);
	void	processItem(long idTrn,ODFOrder::TypeAction action,GData *pData,long index,ODFDataComms * pDataComms=0);
	void	processEndTransaction(long idTrn);

	void	commsRegister(ODFOrder::TypeAction action,GRegister * pRegister,ODFDataComms * pDataComms=0);
	

	MSLString getRTMatchStatus(long idTrn, GTHMatch * pMatch, MSLSortedVector vChanges);
	bool	poolStandingsChanged(GData *pData, ODFDataComms * pDataComms, long idTrn, ODFOrder::TypeAction action);

		
private:
	GData *	getParamByRSC(const char* oris, const char* rsc, const char* params);
		

};

