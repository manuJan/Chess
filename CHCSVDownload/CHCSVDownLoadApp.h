#pragma once
#include <OVR/GUI/CSVDownLoad/CSVDownLoadApp.h>

class CHCSVDownLoadApp : public CSVDownLoadApp
{
public:
	CHCSVDownLoadApp();
	virtual ~CHCSVDownLoadApp();

	GMemoryDataBase *onNewMemory	();
	MSLWString		onGetTitle		() const;

	// Virtual methods inherited from MSLAfterInitialLoadApp
	CSVDownLoadGUI*	onNewLoadGUI	() const;
};


