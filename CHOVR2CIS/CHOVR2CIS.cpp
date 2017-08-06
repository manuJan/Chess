// BKOVR2CIS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CHOVR2CIS.h"
#include "CHCISApp.h"

CHCISApp gOVR2CISApp;

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	return gOVR2CISApp.run(hInstance);
}