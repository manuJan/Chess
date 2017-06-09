/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHPhaseGUIEx.cpp
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHPhaseGUIEx.h"
#include <OVR\core\th\gthmsgdefines.h>
#include "..\CHMngtModel\CHPhase.h"


CHPhaseGUIEx::CHPhaseGUIEx(long id, GEvent* pEvent, GPhaseGUIEx::TypeControl tCtrl,GPhaseGUIEx::TypeTitlePosition tPos,const wchar_t * title,const wchar_t * comboAdd/*=0*/, int phaseOrder/*=-1*/)
:GTHPhaseGUIEx(id,pEvent,tCtrl,tPos,title,comboAdd,phaseOrder)
{
}

CHPhaseGUIEx::~CHPhaseGUIEx()
{
}

void CHPhaseGUIEx::createGridPhase()
{
	GTHPhaseGUIEx::createGridPhase();

	if (m_typeCtrl==eGrid)
	{
		m_gui.grid_setCellW	(GR_PHASE,1,150);
		m_gui.grid_setCellW	(GR_PHASE,2,80);
		m_gui.grid_addColumn(GR_PHASE,"Type Phase"			,GUI_JUST_CENTER, 60, C_PHASE_TYPE	);
		
		// TT
		m_gui.grid_setCellTT(GR_PHASE,m_gui.grid_findCol(GR_PHASE,C_PHASE_TYPE),-1,"Type phase");		
	}	
}
	
bool CHPhaseGUIEx::paintGridPhase(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	CHPhase * pPhase=(CHPhase*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
		case C_PHASE_TYPE:
			cell->txt=pPhase->getTypePhaseDescription();
			break;		
	}

	return GTHPhaseGUIEx::paintGridPhase(cell);
}

