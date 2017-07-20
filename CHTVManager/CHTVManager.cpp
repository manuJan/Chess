/*************************************************************************************
*	© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARTVManager.h
*	Description	: 
*
*	Author		: Javier Juste
*	Date created: 28 Jan 2010
* 	Project		: ARTVManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHTVManager.h"
#include "CHTVApp.h"

CHTVApp gTVManagerApp;

int APIENTRY _tWinMain( HINSTANCE hInstance,
            		    HINSTANCE hPrevInstance,
						LPTSTR    lpCmdLine,
                  		int       nCmdShow)
{
			UNREFERENCED_PARAMETER(hPrevInstance);
			UNREFERENCED_PARAMETER(lpCmdLine);
			UNREFERENCED_PARAMETER(nCmdShow);	

			return gTVManagerApp.run(hInstance);
}
