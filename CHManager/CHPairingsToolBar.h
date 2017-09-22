
#pragma once
#include <ovr\gui\GUIMANAGER\GToolbar.h>

class CHPairingsToolBar  : public GToolBar
{
public:
	CHPairingsToolBar(long id, CHPool* pPool, short selRound);
	virtual ~CHPairingsToolBar();
	
protected:
	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc							(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool onInit								();	
	void fillComboRounds					();
	void onClick							(long id,LPARAM lParam);

	virtual LRESULT onRedrawControl			(WPARAM wParam=0, LPARAM lParam=0);
	//Comms
	virtual LRESULT onCommsPackTrn				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onCommsData					(WPARAM wParam=0, LPARAM lParam=0);


	/***** Virtual From GToolBar  *****/
	virtual HINSTANCE getHInstance			(int idCtrl,UINT idRes);
		
private:
		
	CHPool* m_pPool;
	short m_selRound;
};
