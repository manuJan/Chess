/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC38.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#if !defined(AFX_CHRC38_H__CE163348_0E68_4BDD_84AF_0F173C832F10__INCLUDED_)
#define AFX_CHRC38_H__CE163348_0E68_4BDD_84AF_0F173C832F10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include <REPORTS/V/ReportManager.h>
#include <REPORTS/V/RC38.h>

const int ENTRY_DATA_CHECK_LIST_C38=  6037;

class CHVMngtExport CHRC38 : public RC38  
{
public:
	CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig,const char *pGroup);
	CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC38();

protected:

	VCheckList * OnNewCheckList();	// return new XXCheckList(m_Group);
	RWBoolean	 OnLoadLis();		// Lectura de .lis propio	
	void		 OnLisLoaded();		// Llamada para modificar variables y carteles del pBaseLis
	int			 OnHeight(const GCheckList * pNext); // altura de la parte específica del deporte
	RWBoolean	 OnExtendedLis();	// Llamada para pintar datos propios para pCurrent
	RLegend *	 OnCreateLegend();	// Creación de leyendas

	
private:
	CLis		* pLis;
	short		typeReport;
};

#endif // !defined(AFX_CHRC38_H__CE163348_0E68_4BDD_84AF_0F173C832F10__INCLUDED_)
