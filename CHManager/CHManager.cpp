// ARManager.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CHManager.h"
#include "CHManagerApp.h"

CHManagerApp gManagerApp;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);	

	return gManagerApp.run(hInstance);
}
