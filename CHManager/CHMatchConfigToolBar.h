
#pragma once
#include <ovr\gui\GUIMANAGER\GToolbar.h>

class CHMatchConfigToolBar  : public GToolBar
{
public:
	CHMatchConfigToolBar(long id, CHMatch* pMatch, bool autoFinish);
	virtual ~CHMatchConfigToolBar();
	
protected:
	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc							(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool onInit								();	
	void onClick							(long id,LPARAM lParam);

	virtual LRESULT onRedrawControl			(WPARAM wParam=0, LPARAM lParam=0);
	//Comms
	virtual LRESULT onCommsPackTrn				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onCommsData					(WPARAM wParam=0, LPARAM lParam=0);


	/***** Virtual From GToolBar  *****/
	virtual HINSTANCE getHInstance			(int idCtrl,UINT idRes);
	
private:

	bool m_autoFinish;
	CHMatch* m_pMatch;
};
