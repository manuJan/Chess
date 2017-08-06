#pragma once
#include <OVR/CORE/G/GData.h>

class CHPoolResult;

#include <ovr/core/G/GScore.h>

class CHTVGroupInfo : public GData
{
public:
	CHTVGroupInfo			(CHPoolResult * pPR);
	virtual ~CHTVGroupInfo	();

	void setKey				();

	void addGP				();
	void addW				();
	void addL				();
	void addD				();
	
public:
	CHPoolResult * m_pResult;
	MSLString m_group;
	int m_rank;
	int m_GP;
	int m_W;
	int m_D;
	int m_L;	
	int m_displayPos;
	//MSLString m_IRM;
	MSLString m_advanceTo;
	MSLString m_advanceTo_Game;
};
