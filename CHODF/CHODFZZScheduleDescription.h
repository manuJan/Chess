/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFZZScheduleDescription.h
*	Description	:
*
*	Author		: 
*	Date created: 19-11-2013
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHScheduleDescription.h>

class CHMatch;

class CHODFZZScheduleDescription : public ODFTHScheduleDescription
{
public:
	CHODFZZScheduleDescription(ODFBuildMessage * pBuild,XMLElement * pElement,ODFFile * pFile);
	~CHODFZZScheduleDescription(void);

	//From ODFTHScheduleDescription
	void createSchLines();
	ODFZZSchLine * createSchLine(GData * pData);
	void fillLevelPhase(XMLElement * pEl_Event,ODFZZSchLine * pSchPh);
	void fillPhaseDescriptionChess(XMLElement * pEl_PhaseDescription, GData * pData, MSLString lang);

	MSLWString getPhaseIDescription(GPhase * pPhase,MSLString lang);

	MSLWString getPhaseSDescription(GPhase * pPhase,MSLString lang);
	MSLWString getPhaseLDescription(GPhase * pPhase,MSLString lang);

	MSLWString getPhaseMatchILDescription(CHMatch *pMatch, MSLString lang);
	MSLWString getPhaseMatchIDescription(CHMatch *pMatch, MSLString lang);
	MSLWString getPhaseMatchLDescription(CHMatch *pMatch, MSLString lang);
	MSLWString getPhaseMatchSDescription(CHMatch *pMatch, MSLString lang);

	MSLWString getUnitIDescription(GData * pSchLineData,MSLString lang);
	MSLWString getUnitILDescription(GData * pSchLineData,MSLString lang);
	
private:
	CHMatch *m_pMatch;
};

