/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISPaint.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <ovr\gui\thovr2cis\GTHCISPaint.h>

#define CHPAINT CHCISPaint::chPaint

class CHMatchResult;

class CHCISPaint : public GTHCISPaint
{
public:
	CHCISPaint();
	virtual ~CHCISPaint();

public:

	virtual void paintRegister					 (long idScreen, long idLayer, long column, long line, const wchar_t * text, GRegister * pRegister, GData* pData=0 );
	virtual void paintStartList					 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintMatchStartList					 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintRoundResults				 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintMatchResults				 (long idScreen, long idLayer, CHMatch* pMatch);

	virtual void paintStartListHeader			 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintMatchStartList			 (long idScreen, long idLayer, short y, CHMatch *pMatch);
	virtual void paintSubMatchStartList			 (long idScreen, long idLayer, short y, CHMatch *pMatch);

	virtual void paintResultsHeader				 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintRoundMatchResults			 (long idScreen, long idLayer, short y, CHMatch *pMatch);
	virtual void paintRoundSubMatchResults		 (long idScreen, long idLayer, short y, CHMatch *pSubMatch);

	virtual void paintResultsHeader1			 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintResultsHeader2			 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintResultsTotal				 (long idScreen, long idLayer, CHMatch* pMatch);
	virtual void paintSubMatchesResults			 (long idScreen, long idLayer,  CHMatch* pMatch);
	virtual void paintSubMatchResults			 (long idScreen, long idLayer, short y, CHMatch *pSubMatch);
	virtual void paintSubMatchesResultsHeader	 (long idScreen, long idLayer, CHMatch *pMatch);

	// Pool Result
	virtual void paintPoolHeader				(long idScreen, long idLayer, long y, GTHPool* pPool );
	virtual void paintPoolResultHeader			(long idScreen, long idLayer, long y, GTHPool* pPool );
	virtual void paintPoolResultTableHeader		(long idScreen, long idLayer, long y, GTHPool* pPool );
	virtual void paintPoolResultTeamsHeader		(long idScreen, long idLayer, long y, GTHPool* pPool );
	virtual void paintPoolResult				(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult );
	virtual void paintPoolResultTable			(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult );
	virtual void paintPoolResultMatches			(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult );
	virtual short getIniColTeamsHeader			(long idScreen, long idLayer, GTHPool* pPool);

	virtual void onLook							(long idScreen, GData * pData);

	virtual void paintListButtons				(GCISScreen* pScreen, GData* pData);

public:
	// Static variables
	static CHCISPaint * chPaint;
};
