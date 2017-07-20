/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARODF2Config.h
*	Description	:
*
*	Author		: 
*	Date created: 29-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once

#include <OVR/GUI/ODF2/ODF2Base/ODF2ZZConfig.h>

class ARODF2Config : public ODF2ZZConfig
{
public:
	ARODF2Config(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData);
	virtual ~ARODF2Config(void);

	void fillSportConfig(MSLItem * pDataCfg,XMLElement * pEl_Config);
	void fillVectorConfigs(MSLArray& vConfigs);
	void fillExtendedConfig(MSLItem * pDataCfg,XMLElement * pEl_Config);
	void addSessionUnits(XMLElement *pEl, GSession* pSession);

private:

	GSession * m_pSession;
	
};

