/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHDiscipline.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:05-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_CHDISCIPLINE_H__7271DFD7_09FC_4D70_ADA4_0137BFB397DD__INCLUDED_)
#define AFX_CHDISCIPLINE_H__7271DFD7_09FC_4D70_ADA4_0137BFB397DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHDiscipline_H
#define _CHDiscipline_H
#endif 

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE\TH\GTHDiscipline.h>

class GVenue;

class CHModelExport CHDiscipline : public GTHDiscipline  
{
	RWDECLARE_COLLECTABLE(CHDiscipline)

public:
	CHDiscipline();
	CHDiscipline(const CHDiscipline & copy);
	CHDiscipline(CPack & aPack);
	virtual ~CHDiscipline();

	CHDiscipline & operator  =(const CHDiscipline & copy);
	RWBoolean      operator !=(const CHDiscipline & copy);
	RWBoolean      operator ==(const CHDiscipline & copy);

	RWBoolean uSQL(RWDBConnection & pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char * language) const;
	CPack &   pack(CPack & aPack);
	CPack & unpack(CPack & aPack);

	//sets
	void setAutoProg(RWBoolean value);

	//gets
	RWBoolean getAutoProg();

	//Venue methods
	GVenue *getVenue() const;
	RWCString getVenueCode() const;
	RWWString getVenueSDescription(const char *language=DBApplication::getAppLanguage()) const;
	RWWString getVenueLDescription(const char *language=DBApplication::getAppLanguage()) const;

private:
	RWBoolean autoProg;

};

#endif // !defined(AFX_CHDISCIPLINE_H__7271DFD7_09FC_4D70_ADA4_0137BFB397DD__INCLUDED_)
