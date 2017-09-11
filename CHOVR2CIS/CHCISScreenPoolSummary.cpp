#include "StdAfx.h"
#include "CHCISScreenPoolSummary.h"
#include "CHCISPaint.h"
#include "CHCISProcess.h"
#include "..\CHMngtModel\CHPoolResult.h"

CHCISScreenPoolSummary::CHCISScreenPoolSummary(MSLString key)
:GTHCISScreenPoolSummary(key)
{
}

CHCISScreenPoolSummary::CHCISScreenPoolSummary(MSLString key, MSLString name, MSLString designFile, GTHPhase * pPhase)
:GTHCISScreenPoolSummary(key, name, designFile,pPhase)
{
}

CHCISScreenPoolSummary::~CHCISScreenPoolSummary()
{
}

void CHCISScreenPoolSummary::onRun()
{
	if (!m_pData || m_pData->isA()!=__GTHPHASE)
		return;

	GTHPhase* pPhase = (GTHPhase*)m_pData;
	MSLSortedVector vPools;
	pPhase->getPoolesVector(vPools);
	short line=0;
	for (short i=0;i<vPools.entries();i++)
	{
		GTHPool* pPool = (GTHPool*)vPools[i];
		runCHGroup(pPool, line);		
	}
}

void CHCISScreenPoolSummary::runCHGroup(GTHPool* pPool, short &line)
{
	MSLSortedVector vPoolResults;
	CHPROCESS->getColPoolResults(vPoolResults,isA(),pPool);	

	CHPAINT->paintPoolHeader(isA(), LIST_SUMMARY, line, pPool );	
	line++;

	CHPAINT->paintPoolResultHeader(isA(), LIST_SUMMARY, line, pPool );	
	line++;

	for(int i=0; i<vPoolResults.entries() ; i++)
	{
		CHPoolResult * pPoolResult = (CHPoolResult *)vPoolResults[i];	
		if (pPoolResult &&
			pPoolResult->getBye())
			continue;

		GTHPAINT->paintPoolResult(isA(), LIST_SUMMARY, line, (GTHPoolResult *)vPoolResults[i]);	
		line++;
	}

	CISAPP->setListEndLine(LIST_SUMMARY, line);
}

