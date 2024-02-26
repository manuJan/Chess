#pragma once
#include <OVR/GUI/CSVDownLoad/CSVDownLoadGUI.h>

class CHCSVDownLoadGUI : public CSVDownLoadGUI
{
public:
	CHCSVDownLoadGUI(long id);
	virtual ~CHCSVDownLoadGUI();

	virtual CSVRegisterProcess * onNewRegisterProcess();

	virtual bool onInit						();

	virtual bool paintGridRegisterMem		(gui_grid_cell* cell);
};

