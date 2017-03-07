/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	QCHSession.h
*	Description	:
*
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_QCHSESSION_H__9E2266AB_AC25_4FF9_9A60_D07F8C66C32B__INCLUDED_)
#define AFX_QCHSESSION_H__9E2266AB_AC25_4FF9_9A60_D07F8C66C32B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <core\TH\QGTHSession.h>

class QCHSession : public QGTHSession  
{

public:
	QCHSession(RWDBConnection *pNewConnection)
		:QGTHSession(pNewConnection)
	{};

	virtual ~QCHSession()
	{};

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tSesstion);
	void OnReader(RWDBReader& aReader,GTHSession *pSession);
	
	GTHSession * OnNewSession();
};

#endif // !defined(AFX_QCHSESSION_H__9E2266AB_AC25_4FF9_9A60_D07F8C66C32B__INCLUDED_)
