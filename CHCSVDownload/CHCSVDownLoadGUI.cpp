#include "StdAfx.h"
#include "CHCSVDownLoadGUI.h"
#include "CHCSVRegisterProcess.h"

#define COL_BIB			GRID_REGISTER_MEM+20

CHCSVDownLoadGUI::CHCSVDownLoadGUI(long id)
:CSVDownLoadGUI(id)
{
}

CHCSVDownLoadGUI::~CHCSVDownLoadGUI()
{
}

CSVRegisterProcess *CHCSVDownLoadGUI::onNewRegisterProcess()
{
	return new CHCSVRegisterProcess();
}

bool CHCSVDownLoadGUI::onInit()
{
	CSVDownLoadGUI::onInit();

	//m_gui.grid_addColumn(GRID_REGISTER_MEM,"Bib",GUI_JUST_LEFT,80,COL_BIB);

	return true;
}

bool CHCSVDownLoadGUI::paintGridRegisterMem(gui_grid_cell* cell)
{
	/*
	if(cell->y==-1 || !cell->lParamLine)
		return false;
	
	GRegister * pRegister=(GRegister*)cell->lParamLine;
	switch(cell->lParamColumn)
	{

	}
	*/
	return CSVDownLoadGUI::paintGridRegisterMem(cell);
}
