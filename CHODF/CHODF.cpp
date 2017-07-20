#include "stdafx.h"
#include "CHODF.h"
#include "CHODFApp.h"

CHODFApp gODFApp;

int APIENTRY _tWinMain(	HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPTSTR    lpCmdLine,
						int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);	
	return gODFApp.run(hInstance);
}

