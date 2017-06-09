
#pragma once
#include <ovr\gui\GUIMANAGER\GToolbar.h>

class CHMatchConfigToolBar  : public GToolBar
{
public:
	CHMatchConfigToolBar(long id);
	virtual ~CHMatchConfigToolBar();
		

protected:
	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc							(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool onInit								();
	void onLButDown							(long id,long x,long y);

	virtual LRESULT onRedrawControl			(WPARAM wParam=0, LPARAM lParam=0);
	//Comms
	virtual LRESULT onCommsPackTrn				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onCommsData					(WPARAM wParam=0, LPARAM lParam=0);


	/***** Virtual From GToolBar  *****/
	virtual HINSTANCE getHInstance			(int idCtrl,UINT idRes);
	
};
