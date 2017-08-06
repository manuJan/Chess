#include "StdAfx.h"
#include "CHTVGroupInfo.h"

#include "..\CHMngtModel\CHPoolResult.h"

CHTVGroupInfo::CHTVGroupInfo(CHPoolResult * pPR)
:m_pResult(pPR)
,m_rank(0)
,m_GP(0)
,m_W(0)
,m_L(0)
,m_displayPos(0)
//,m_IRM("")
,m_advanceTo("")
,m_advanceTo_Game("")
{
	setKey();
}

CHTVGroupInfo::~CHTVGroupInfo()
{
}

void CHTVGroupInfo::setKey()
{
	key=m_pResult?m_pResult->getKey():"";
}

void CHTVGroupInfo::addGP()
{
	m_GP++;
}

void CHTVGroupInfo::addW()
{
	m_W++;
}

void CHTVGroupInfo::addL()
{
	m_L++;
}

void CHTVGroupInfo::addD()
{
	m_D++;
}
