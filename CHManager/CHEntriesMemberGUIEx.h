/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesMemberGUIEx.h
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

#pragma once
#include "CHManagerDefs.h"
#include <OVR\GUI\GUIMANAGER\GEntriesMemberGUIEx.h>

class CHEntriesMemberGUIEx : public GEntriesMemberGUIEx
{
public:
	CHEntriesMemberGUIEx(long id);
	virtual ~CHEntriesMemberGUIEx();



protected:

	virtual void createGridMember			(int yPos=46);
	virtual bool paintGridMember			(gui_grid_cell* cell);

	virtual int getTeamMembers				();

	void dblClickGridMemberMember			(long x, long y);

	virtual void editRating					(CHMember* pMember);	
	virtual void editKConst					(CHMember* pMember);	
};
