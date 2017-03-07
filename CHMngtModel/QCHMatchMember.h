/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHMatchMember.h
*	Description	:Query Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#if !defined(AFX_QCHMATCHMEMBER_H__253E10D8_75C5_4A94_8D30_0097057E998A__INCLUDED_)
#define AFX_QCHMATCHMEMBER_H__253E10D8_75C5_4A94_8D30_0097057E998A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/TH/QGTHMatchMember.h>
#include "CHMatchMember.h"

class QCHMatchMember : public QGTHMatchMember  
{
public:
	QCHMatchMember(RWDBConnection *pNewConnection)
	:QGTHMatchMember(pNewConnection) 
	{ ; }
	virtual ~QCHMatchMember()
	{ ; }

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tMatchMember);
	void OnReader(RWDBReader& aReader,GTHMatchMember *pMatchMember);

	GTHMatchMember * OnNewMatchMember()
		{ return new CHMatchMember(); }
};

#endif // !defined(AFX_QCHMATCHMEMBER_H__253E10D8_75C5_4A94_8D30_0097057E998A__INCLUDED_)
