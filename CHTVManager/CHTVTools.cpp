/*************************************************************************************
*			� Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVTools.cpp
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: CH TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHTVTools.h"
#include "CHTVApp.h"
#include "CHTVGUI.h"
#include "CHTVDefs.h"
#include "CHTVOrderFunctions.h"
#include "CHTVGroupInfo.h"

#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHEventResult.h"

#include <OVR/Reports/V/VMedalStandings.h>
#include <OVR/Reports/V/GMedalsByNoc.h>


#define CH_TV_CONF_FILE			"CHTVConf.ini"
#define ATHLETE_ID_CONF			"CONF_ATHLETE_ID"
#define ATHLETE_ID_USE			"Use"
#define ATHLETE_ID_USE_AC		"ACCREDITATION"
#define ATHLETE_ID_USE_REG		"REGISTER"
#define RESULT_SCORE_CONF		"CONF_RESULT_SCORE"
#define RESULT_SCORE_USE		"Use"
	#define RESULT_SCORE_USE_NET	"NET"
	#define RESULT_SCORE_USE_TOTAL	"TOTAL"
#define SETTINGS_CONF			"TV_SETTINGS"
#define SETTINGS_MODE			"Mode"
	#define SETTINGS_MODE_TV		"TV"
	#define SETTINGS_MODE_FULL		"FULL"
#define SETTINGS_RSC_DLL		"RSC_DLL"

#define RTDS_NUM_NEXT			4


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHTVTools::CHTVTools()
:m_pMem(new CHMemoryDataBase())
,m_pGUI(0)
{

}
/**************************************************************************************/
CHTVTools::~CHTVTools()
{

}

CHMemoryDataBase *CHTVTools::mem()
{ 
	return m_pMem; 
}

void CHTVTools::init(CHTVGUI *pGUI)
{
	m_pGUI = pGUI;

	char fName[200];
	::GetModuleFileNameA(NULL,fName,200);
	MSLWString path(fName);
	MSLWString currPath = path(0,path.last('\\')+1);
	currPath = currPath+_T(CH_TV_CONF_FILE);
	m_fileIni = currPath;

	MSLFileIni aFileIni(m_fileIni,false);
	MSLString athleteID=aFileIni.read(ATHLETE_ID_CONF,ATHLETE_ID_USE,"");
	if(!athleteID.length())
		aFileIni.write(ATHLETE_ID_CONF,ATHLETE_ID_USE,ATHLETE_ID_USE_AC);
	MSLString resultScore=aFileIni.read(RESULT_SCORE_CONF,RESULT_SCORE_USE,"");
	if(!resultScore.length())
		aFileIni.write(RESULT_SCORE_CONF,RESULT_SCORE_USE,RESULT_SCORE_USE_NET);
}

MSLString CHTVTools::getAthleteID(GRegister * pRegister)
{
	if( !pRegister )
		return NULLSTRING;

	MSLFileIni aFileIni(m_fileIni,true);
	MSLString sUse = aFileIni.read(ATHLETE_ID_CONF,ATHLETE_ID_USE,ATHLETE_ID_USE_AC);
	if( sUse == ATHLETE_ID_USE_AC )
		return pRegister->getAcreditation();
	else 
		return TOSTRING(pRegister->getRegister());
}

MSLString CHTVTools::getResultScore(CHMatchResult *pMatchResult)
{
	if( !pMatchResult )
		return NULLSTRING;
	
	return pMatchResult->getPointsAsString();
}

MSLString CHTVTools::getEventScore(CHMatchResult *pMatchResult)
{
	CHEventResult * pER = (CHEventResult *) pMatchResult->getEventResult();
	return NULLSTRING;
}

MSLString CHTVTools::getEventRankPo(CHMatchResult *pMatchResult)
{
	CHEventResult * pER = (CHEventResult *) pMatchResult->getEventResult();
	if (pER && pER->getRankPo())
		return TOSTRING(pER->getRankPo());
	
	return NULLSTRING;
}

MSLString CHTVTools::getEventRank(CHMatchResult *pMatchResult)
{
	CHEventResult * pER = (CHEventResult *) pMatchResult->getEventResult();
	if (pER && pER->getRank())
		return TOSTRING(pER->getRank());
	
	return NULLSTRING;
}

MSLString CHTVTools::getMode()
{
	MSLFileIni aFileIni(m_fileIni,true);
	MSLString sMode = aFileIni.read(SETTINGS_CONF,SETTINGS_MODE,SETTINGS_MODE_TV);
	return sMode;
}

MSLString CHTVTools::getRSCDll()
{
	MSLFileIni aFileIni(m_fileIni,true);
	MSLString sMode = aFileIni.read(SETTINGS_CONF,SETTINGS_RSC_DLL,"");
	return sMode;
}

MSLString CHTVTools::getSessionDesc(GSession * pSession) const
{
	char txt[20];
	sprintf_s(txt,20,"Session CH%02d",pSession?pSession->getAcumulated():0);
	return txt;
}


void CHTVTools::getRounds(GSession * pSession, MSLSortedVector &vRounds)
{
	vRounds.clear();
	MSLSortedVector vMatches;
	getMatches(vMatches);
	CHMatch * pMatch = 0;
	CHPhase * pPhase = 0;
	for(long i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if( pMatch->getSession() != pSession )
			continue;
		
		short round = pMatch->getRound();
		bool insert=true;
		for (short j=0;j<vRounds.entries();j++)
		{
			CHMatch * pMatchF = (CHMatch*)vRounds[j];
			if (pMatchF->getPhase()==pMatch->getPhase() &&
				pMatchF->getRound()==round)
			{
				insert=false;
				break;
			}
		}
		if (insert)
			vRounds.insert(pMatch);
	}

	vRounds.setFcCompare(fnOrderMatchesByEventDateTime);
}

void CHTVTools::getMatches(MSLSortedVector &vMatches, const bool withByes/*=false*/)
{
	vMatches.clear();

	MSLSortedVector vAllMatches(m_pMem->getCol(__CHMATCH),0);
	CHMatch * pMatch = 0;
	for(long i=0; i<vAllMatches.entries(); i++ )
	{
		pMatch = (CHMatch *)vAllMatches[i];
		if( !withByes && pMatch->hasByes() ) 
			continue;
		if( !withByes && !pMatch->getMatchNumber() )
			continue;
		if( !m_pGUI->validateDate(pMatch->getStartDate()) )
			continue;
		
		/*if( !m_pGUI->validateSession(pMatch->getSessionAcumulated()) )
			continue;*/

		vMatches.insert(pMatch);
	}
	vMatches.setFcCompare(fnOrderMatchByDateTime);
}

MSLString CHTVTools::getDesc(const CHMatch * pMatch) const
{
	if( !pMatch )
		return NULLSTRING;

	MSLString	descMatch = "";
	
	char tmp[4];
	if (pMatch->getMatchNumber())
		sprintf_s(tmp,"%.3d",pMatch->getMatchNumber());
	else
		sprintf_s(tmp,"%.3d",pMatch->getCode());

	MSLString mn=tmp;
	descMatch = descMatch + "Match_" + MSLString(mn);
	MSLString	descEvent = pMatch->getEventSDescription().toAscii();
	MSLString	descPhase = "";
	descPhase = pMatch->getPhaseSDescription().toAscii();
	
	// sustituimos caracteres no v�lidos
	descEvent.replace("+","_");
	descPhase.replace("/","_");
	descPhase.replace("'","");
	
	if( pMatch->getPhaseCode() == GOLD_MEDAL || pMatch->getPhaseCode() == BRONZE_MEDAL )
	{
		descPhase = pMatch->getPhaseCode() == GOLD_MEDAL ? TV_GOLD : TV_BRONZE;		
		descMatch = descMatch+ "_" + descEvent + "_" + descPhase + "_Medal Match";
	}
	else 
		descMatch = descMatch + "_" + descEvent + "_" + descPhase;
	
	return descMatch;
}

long CHTVTools::getStatus(const CHMatch *pMatch) const
{
	if( !pMatch )
		return TV_ST_UNKNOWN;
	switch( pMatch->getStatus() )
	{
		case CHMemoryDataBase::eAvailable:		return TV_ST_NOT_SCHEDULED;
		case CHMemoryDataBase::eSchedulled:
		case CHMemoryDataBase::eStartList:		return TV_ST_SCHEDULED;
		case CHMemoryDataBase::eRunning:		return TV_ST_IN_PROGRESS;
		case CHMemoryDataBase::eUnofficial:		return TV_ST_UNOFFICIAL;
		case CHMemoryDataBase::eFinished:		return TV_ST_OFFICIAL;
		case CHMemoryDataBase::eProtested:		return TV_ST_PROTESTED;
	}
	return TV_ST_UNKNOWN;
}

void CHTVTools::getMembersVector(CHInscription *pInscription, MSLSortedVector& vMembers) 
{
	MSLSortedVector vAllMembers;
	pInscription->getMembersVector(vAllMembers);
	for (short i=0;i<vAllMembers.entries();i++)
	{
		GMember* pMember = (GMember*) vAllMembers[i];
		if (pMember->getType()==GRegister::individual)
			vMembers.insert(pMember);		
	}	
}


/////////////////////////////////////////////////////////////////////////////////
// Saves
/////////////////////////////////////////////////////////////////////////////////

void CHTVTools::saveParticipants()
{
	MSLSortedVector vParticipants(m_pMem->getCol(__GREGISTER),fnOrderRegByTVLName);
	for (long i=0;i<vParticipants.entries();i++)
	{
		GRegister *pReg=NULL;
		pReg=(GRegister *)vParticipants[i];
		if( pReg->getType() == GRegister::individual )
			saveRegister(pReg);
	}
}

void CHTVTools::saveRegister(GRegister *pReg) 
{
	if (!pReg)
		return;

	int pos=0;
	m_pGUI->addContent(pReg,pos++,getAthleteID(pReg));				// "Athlete_ID"
	m_pGUI->addContent(pReg,pos++,m_pGUI->getRegisterLName(pReg));	// "Long_TV_Name"
	m_pGUI->addContent(pReg,pos++,m_pGUI->getRegisterSName(pReg));	// "Short_TV_Name"
	m_pGUI->addContent(pReg,pos++,pReg->getGroup());				// "NOC_Code"	
	m_pGUI->addContent(pReg,pos++,pReg->getGroupLDescription());
	m_pGUI->addContent(pReg,pos++,pReg->getGroupSDescription());
}


void CHTVTools::saveSessionSchedule(GSession * pSession) 
{
	if( !pSession )
		return;
	CHMatch * pMatch = 0;
	MSLSortedVector vRounds;
	getRounds(pSession, vRounds);
	for(long i=0;i<vRounds.entries();i++)
	{
		pMatch = (CHMatch*)vRounds[i];
		saveSchedule(pMatch);
	}
}

void CHTVTools::saveSessionScheduleDetailed(GSession * pSession) 
{
	if( !pSession )
		return;
	CHMatch * pMatch= 0;
	MSLSortedVector vMatches;
	getMatches(vMatches);
	vMatches.setFcCompare(fnOrderMatchByDateTime);
	for(long i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*)vMatches[i];
		if(pSession && pSession!=pMatch->getSession() )
			continue;
		saveScheduleDetailed(pMatch);
	}
}


void CHTVTools::saveSessionScheduleUnit(GSession * pSession)
{
	if( !pSession )
		return;
	CHMatch * pMatch= 0;
	CHMatchResult * pBlack = 0, * pWhite = 0;
	MSLSortedVector vMatches;
	getMatches(vMatches,true);
	vMatches.setFcCompare(fnOrderMatchByDateTime);
	for(long i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*)vMatches[i];
		if(pSession && pSession!=pMatch->getSession() )
			continue;
		if( !pMatch->getMatchNumber() )
			continue; // pasamos de byes fijos
		
		pWhite = pMatch->getWhite();
		pBlack = pMatch->getBlack();
		
		saveScheduleUnit(pWhite);
		saveScheduleUnit(pBlack);
	}
}

void CHTVTools::saveSchedule(CHMatch * pMatch) 
{
	if( !pMatch )
		return;
	
	MSLString rsc = CHTVApp::getRSC_TV(pMatch, RSC_ALL);
	MSLString value="",g="",ev="",ph="",unit="";
	
	// El rsc pasado es el de msl
	if( rsc.length()==9 )
	{
		g	= rsc(2,1);
		ev	= rsc(3,3);		// Nos saltamos el event parent
		ph	= rsc(6,1);
		unit= rsc(7,2);	// dos ultimos
	}

	int pos=0;
	m_pGUI->addContent(pMatch,pos++,g);		// "Gender"
	m_pGUI->addContent(pMatch,pos++,ev);	// "Event_Code"	
	m_pGUI->addContent(pMatch,pos++,ph);	// "Competition_Phase"	
	if (pMatch->getPhaseCode()==SWISS_ROUND)
	{
		m_pGUI->addContent(pMatch,pos++,"00");	// "Event_Unit"
		m_pGUI->addContent(pMatch,pos++,pMatch->getRoundAsString(true,false));	// "Round"
	}
	else
	{
		m_pGUI->addContent(pMatch,pos++,unit);	// "Event_Unit"
		m_pGUI->addContent(pMatch,pos++,"");
	}
}

void CHTVTools::saveScheduleDetailed(CHMatch* pMatch) 
{
	if( !pMatch )
		return;
	
	MSLString rsc = CHTVApp::getRSC_TV(pMatch, RSC_ALL);
	MSLString value="",g="",ev="",ph="",unit="";
	
	// El rsc pasado es el de msl
	if( rsc.length()==9 )
	{
		g	= rsc(2,1);
		ev	= rsc(3,3);		// Nos saltamos el event parent
		ph	= rsc(6,1);
		unit= rsc(7,2);	// dos ultimos
	}

	int pos=0;
	m_pGUI->addContent(pMatch,pos++,g);	// "Gender"
	m_pGUI->addContent(pMatch,pos++,ev);	// "Event_Code"	
	m_pGUI->addContent(pMatch,pos++,ph);	// "Competition_Phase"	
	m_pGUI->addContent(pMatch,pos++,unit);	// "Event_Unit"
	m_pGUI->addContent(pMatch,pos++,TOSTRING(pMatch->getCourtCode()));		// "Table_Code"
	m_pGUI->addContent(pMatch,pos++,TOSTRING(pMatch->getMatchNumber()));	// "Bout_Number"
	m_pGUI->addContent(pMatch,pos++,pMatch->getRoundAsString(true,false));
	m_pGUI->addContent(pMatch,pos++,pMatch->getStartTimeAsString("%H:%M"));	// "Start_Time"
}

void CHTVTools::saveScheduleUnit(CHMatchResult * pMatchResult)
{
	if( !pMatchResult )
		return;

	CHMatch *pMatch = (CHMatch *) pMatchResult->getMatch();
	MSLString rsc = CHTVApp::getRSC_TV(pMatch, RSC_ALL);
	MSLString value="",g="",ev="",ph="",unit="";
	
	// El rsc pasado es el de msl
	if( rsc.length()==9 )
	{
		g	= rsc(2,1);
		ev	= rsc(3,3);		// Nos saltamos el event parent
		ph	= rsc(6,1);
		unit= rsc(7,2);	// dos ultimos
	}

	// Order: Unit start date, unit start time, unit order
	MSLString keyCode = pMatch->getEventKey()+
						pMatch->getStartDateAsString("%Y%m%d").toAscii()+
						pMatch->getStartTimeAsString("%H%M")+					
						pMatch->getCourtKey()+
						MSLString().format("%.2d",pMatch->getMatchNumber())+
						MSLString().format("%3d",pMatch->getCode())+
						TOSTRING(pMatchResult->getPosition());

	GData *pData = m_pGUI->data(keyCode);
	int pos=0;
	m_pGUI->addContent(pData,pos++,g);											// "Gender"
	m_pGUI->addContent(pData,pos++,ev);											// "Event_Code"	
	m_pGUI->addContent(pData,pos++,ph);											// "Phase_Code"
	m_pGUI->addContent(pData,pos++,unit);										// "Unit_Code"
	m_pGUI->addContent(pData,pos++,pMatch->getVenueCode());						// "Venue_Code"
	m_pGUI->addContent(pData,pos++,TOSTRING(pMatch->getCourtCode()));						// "Court_Code"
	m_pGUI->addContent(pData,pos++,pMatch->getCode());							// "Unit_Order"
	m_pGUI->addContent(pData,pos++,pMatch->getMatchNumber());					// "Unit_Number"
	m_pGUI->addContent(pData,pos++,pMatch->getSessionCode());					// "Session_Code"
	m_pGUI->addContent(pData,pos++,pMatch->getStartDateAsString("%d/%m/%Y"));	// "Start_Date"
	m_pGUI->addContent(pData,pos++,pMatch->getStartTimeAsString("%H:%M"));		// "Start_Time"
	m_pGUI->addContent(pData,pos++,pMatch->getStatusLDescription());			// "Unit_Status"
	MSLString isMedalUnit = pMatch->getPhaseCode() == GOLD_MEDAL || pMatch->getPhaseCode()==BRONZE_MEDAL ? "1":"";
	m_pGUI->addContent(pData,pos++,isMedalUnit);								// "Medal_Unit"
	m_pGUI->addContent(pData,pos++,getAthleteID(pMatchResult->getRegister()));	// "Athlete_ID"
	MSLWString athleteDesc = "";
	if( pMatchResult->getBye() )
		athleteDesc = TV_BYE;
	else
	{
		if (!pMatchResult->getRegister())
			athleteDesc = TV_NOCOMP;

		//athleteDesc = !pMatchResult->getRegister() ? pMatchResult->getIDCompetitor("-Loser to ","BYE","-Loser ","-Winner ","Contest %d",0):L"";
	}

	m_pGUI->addContent(pData,pos++,athleteDesc);								// "Athlete_Description"
	m_pGUI->addContent(pData,pos++,m_pGUI->getRegisterLName(pMatchResult->getRegister()));					// "Long_TV_Name"
	m_pGUI->addContent(pData,pos++,m_pGUI->getRegisterSName(pMatchResult->getRegister()));					// "Short_TV_Name"
	m_pGUI->addContent(pData,pos++,pMatchResult->getGroup());					// "NOC_Code"
	m_pGUI->addContent(pData,pos++,pMatchResult->getPosition());				// "NOC_Code"
	
	MSLWString irm = NULLSTRING;
	if (pMatchResult->isQualitative())
		irm = pMatchResult->getQualitativeSDescription();

	m_pGUI->addContent(pData,pos++,irm);										// "IRM"

	// Result. Running: score of competitor. >Running: decision if winner
	MSLString result = "";
	if( pMatch->getStatus()>=GMemoryDataBase::eRunning )
		result = pMatchResult->getPointsAsString();

	m_pGUI->addContent(pData,pos++,result);										// "Result"
	m_pGUI->addContent(pData,pos++,TOSTRING(pMatchResult->getRank()));			// "Ranking"
	
	MSLString displayPos = "";
	CHMatch::typeWinner winner = CHMatch::typeWinner(pMatch->getWinner());
	if (winner==CHMatch::eWinnerWhite || winner==CHMatch::eWinnerBlack)
		displayPos = TOSTRING(pMatchResult->getRankPo());
	else 
		displayPos = TOSTRING(pMatchResult->getPosition());
	
	m_pGUI->addContent(pData,pos++,pMatch->getStatus()<=GMemoryDataBase::eRunning ? "":displayPos );			// "Display_Pos"
	m_pGUI->addContent(pData,pos++,pMatch->getRoundAsString(true,false));	// "Round"
	m_pGUI->addContent(pData,pos++,TOSTRING(pMatch->getCourtCode()));		// "Table_Code"
}

void CHTVTools::saveEventInfo(CHMatch * pMatch) 
{
	if( !pMatch )
		return;
	
	MSLString rsc = CHTVApp::getRSC_TV(pMatch, RSC_ALL);
	MSLString value="",g="",ev="",ph="",unit="";
	
	// El rsc pasado es el de msl
	if( rsc.length()==9 )
	{
		g	= rsc(2,1);
		ev	= rsc(3,3);		// Nos saltamos el event parent
		ph	= rsc(6,1);
		unit= rsc(7,2);	// dos ultimos
	}

	GTHMatchJudge * pMatchJudge = (GTHMatchJudge *)pMatch->getMatchJudge(0,fnOrderMatchJudgeByPosition);
	MSLWString	sRefLong  = NULLWSTRING, sRefShort = NULLWSTRING;
	MSLString	sRefNOC   = NULLSTRING;
	if( pMatchJudge )
	{
		sRefLong  = m_pGUI->getRegisterLName(pMatchJudge->getRegister());
		sRefShort = m_pGUI->getRegisterSName(pMatchJudge->getRegister());
		sRefNOC   = pMatchJudge->getCountry();
	}

	int pos=0;
	m_pGUI->addContent(pMatch,pos++,"CH");										// "Discipline"
	m_pGUI->addContent(pMatch,pos++,g);											// "Gender"
	m_pGUI->addContent(pMatch,pos++,ev);										// "Event_Code"	
	m_pGUI->addContent(pMatch,pos++,ph);										// "Competition_Phase"	
	m_pGUI->addContent(pMatch,pos++,unit);										// "Event_Unit"
	m_pGUI->addContent(pMatch,pos++,pMatch->getVenueCode());					// "Venue"
	m_pGUI->addContent(pMatch,pos++,pMatch->getRoundAsString(true,false));
	m_pGUI->addContent(pMatch,pos++,sRefLong);									// Referee_Long_TV_Name
	m_pGUI->addContent(pMatch,pos++,sRefShort);									// Referee_Short_TV_Name
	m_pGUI->addContent(pMatch,pos++,sRefNOC);									// Referee_NOC_COde
	m_pGUI->addContent(pMatch,pos++,TOSTRING(pMatch->getCourtCode()));			// "Mat_Code"
}

void CHTVTools::saveOfficials(CHMatch * pMatch)
{
	if( !pMatch )
		return;
	
	MSLSortedVector vMatchJudges;
	pMatch->getMatchJudgesVector(vMatchJudges);

	for(int i=0;i<vMatchJudges.entries()+1;i++)
	{	
		GTHMatchJudge * pMatchJudge = (GTHMatchJudge *)vMatchJudges[i];
		saveOfficial(pMatchJudge);
	}
}


void CHTVTools::saveOfficial(GTHMatchJudge * pMatchJudge)
{
	if( !pMatchJudge )
		return;

	int pos=0;
	m_pGUI->addContent(pMatchJudge,pos++,pMatchJudge->getFunctionLDescription());		// "Position"
	m_pGUI->addContent(pMatchJudge,pos++,pMatchJudge->getCountry());					// "NOC"
	m_pGUI->addContent(pMatchJudge,pos++,m_pGUI->getRegisterLName(pMatchJudge->getRegister()));					// "Long name"
	m_pGUI->addContent(pMatchJudge,pos++,m_pGUI->getRegisterSName(pMatchJudge->getRegister()));					// "Short name"
}

void CHTVTools::saveCompetitor(CHMatch * pMatch)
{
	if( !pMatch )
		return;

	saveCompetitor(pMatch->getWhite());
	saveCompetitor(pMatch->getBlack());	
}

void CHTVTools::saveTeamCompetitor(CHMatch * pMatch)
{
	if( !pMatch )
		return;

	saveTeamCompetitor(pMatch->getWhite());
	saveTeamCompetitor(pMatch->getBlack());	
}

void CHTVTools::saveCompetitor(CHMatchResult *pMatchResult, GData *pData/*=0*/,long pos/*=0*/,bool showProgression/*=false*/)
{
	if( !pMatchResult )
		return;

	CHMatch * pMatch  = (CHMatch*) pMatchResult->getMatch();
	//bool isLoser = pMatch->getWinner() && !pMatchResult->isWinner();

	if( !pData )
		pData = pMatchResult;

	MSLWString	shortName = m_pGUI->getRegisterSName(pMatchResult->getRegister());
	MSLWString  longName = m_pGUI->getRegisterLName(pMatchResult->getRegister());
	
	if( !pMatchResult->getRegister() && showProgression )
	{
		CHMatchResult *pSource = pMatchResult->getSourceByProgression();
		if( pSource && pSource->getMatch() && pSource->getMatch()->getMatchNumber() )
		{
			shortName = L"Winner of bout "+TOWSTRING(pSource->getMatch()->getMatchNumber());
			longName = shortName;
		}
	}
	
	m_pGUI->addContent(pData,pos++,getAthleteID(pMatchResult->getRegister()));					// "Athlete_ID"
	m_pGUI->addContent(pData,pos++,longName);													// "Long_TV_Name"
	m_pGUI->addContent(pData,pos++,shortName);													// "Short_TV_Name"
	m_pGUI->addContent(pData,pos++,pMatchResult->getGroup());									// "NOC_Code"	
	m_pGUI->addContent(pData,pos++,pMatchResult->getColor()==CHMatchResult::eWhite?"W":"B");	// "Color"	
	m_pGUI->addContent(pData,pos++,pMatchResult->getPointsAsString());							// "Score"
	m_pGUI->addContent(pData,pos++,pMatchResult->getSwissRoundScore());							//"Points"
		
	short W,L,D;
	getWinnsLossesDrawn(pMatchResult, W, L, D);
	m_pGUI->addContent(pData,pos++,TOSTRING(W,"0"));										// "W"
	m_pGUI->addContent(pData,pos++,TOSTRING(D,"0"));										// "D"
	m_pGUI->addContent(pData,pos++,TOSTRING(L,"0"));										// "L"

	MSLString dispPos = NULLSTRING;
	if( pMatch->getWinner()!=CHMatch::eNoWinner &&
		pMatch->getWinner()!=CHMatch::eDraw)
		dispPos = TOSTRING(pMatchResult->getRankPo());
	else
		dispPos = pMatchResult->getColor()==CHMatchResult::eWhite ? "1" : "2";

	m_pGUI->addContent(pData,pos++,dispPos);												// "Display_Pos"

	if (pMatchResult->getQualitativeCode()!=OK)
		m_pGUI->addContent(pData,pos++,pMatchResult->getQualitativeSDescription());			// "IRM"
	else
		m_pGUI->addContent(pData,pos++,"");													// "IRM"
		
	pMatch = (CHMatch*)pMatchResult->getMatch();
	m_pGUI->addContent(pMatchResult,pos++,pMatch->getRound());								// "Round"
}


void CHTVTools::saveTeamCompetitor(CHMatchResult *pMatchResult, GData *pData/*=0*/,long pos/*=0*/,bool showProgression/*=false*/)
{
	if( !pMatchResult )
		return;

	CHMatch * pMatch  = (CHMatch*) pMatchResult->getMatch();
	
	if( !pData )
		pData = pMatchResult;

	MSLWString	shortName = m_pGUI->getRegisterSName(pMatchResult->getRegister());
	MSLWString  longName = m_pGUI->getRegisterLName(pMatchResult->getRegister());
	
	if( !pMatchResult->getRegister() && showProgression )
	{
		CHMatchResult *pSource = pMatchResult->getSourceByProgression();
		if( pSource && pSource->getMatch() && pSource->getMatch()->getMatchNumber() )
		{
			shortName = L"Winner of bout "+TOWSTRING(pSource->getMatch()->getMatchNumber());
			longName = shortName;
		}
	}
	
	m_pGUI->addContent(pData,pos++,getAthleteID(pMatchResult->getRegister()));					// "Athlete_ID"
	m_pGUI->addContent(pData,pos++,longName);													// "Long_TV_Name"
	m_pGUI->addContent(pData,pos++,shortName);													// "Short_TV_Name"
	saveTeamMembers(pMatchResult,pos);
	m_pGUI->addContent(pData,pos++,pMatchResult->getGroup());									// "NOC_Code"	
	m_pGUI->addContent(pData,pos++,pMatchResult->getColor()==CHMatchResult::eWhite?"W":"B");	// "Color"	
	m_pGUI->addContent(pData,pos++,pMatchResult->getPointsAsString());							// "Score"
	m_pGUI->addContent(pData,pos++,pMatchResult->getSwissRoundScore());							//"Points"
		
	short W,L,D;
	getWinnsLossesDrawn(pMatchResult, W, L, D);
	m_pGUI->addContent(pData,pos++,TOSTRING(W,"0"));										// "W"
	m_pGUI->addContent(pData,pos++,TOSTRING(D,"0"));										// "D"
	m_pGUI->addContent(pData,pos++,TOSTRING(L,"0"));										// "L"

	MSLString dispPos = NULLSTRING;
	if( pMatch->getWinner()!=CHMatch::eNoWinner &&
		pMatch->getWinner()!=CHMatch::eDraw)
		dispPos = TOSTRING(pMatchResult->getRankPo());
	else
		dispPos = pMatchResult->getColor()==CHMatchResult::eWhite ? "1" : "2";

	m_pGUI->addContent(pData,pos++,dispPos);												// "Display_Pos"

	if (pMatchResult->getQualitativeCode()!=OK)
		m_pGUI->addContent(pData,pos++,pMatchResult->getQualitativeSDescription());			// "IRM"
	else
		m_pGUI->addContent(pData,pos++,"");													// "IRM"
		
	pMatch = (CHMatch*)pMatchResult->getMatch();
	m_pGUI->addContent(pMatchResult,pos++,pMatch->getRound());								// "Round"
}


void CHTVTools::saveTeamMembers(GData* pData, long &pos)
{
	MSLSortedVector vMembers;	
	CHEvent * pEvent = 0;
	CHInscription * pInscription = 0;

	if (!pData)
		return;

	if (pData->isA()==__CHMATCHRESULT)
	{
		CHMatchResult * pMatchResult = (CHMatchResult *)pData;
		pEvent = (CHEvent*) pMatchResult->getEvent();		
		pInscription = (CHInscription*) pMatchResult->getInscription();		
	}	
	else if (pData->isA()==__CHINSCRIPTION)
	{
		pEvent = (CHEvent*) pInscription->getEvent();				
		pInscription = (CHInscription *)pData;
	}
	else if (pData->isA()==__GMEDALLIST)
	{
		GMedallist * pMedallist = (GMedallist *)pData;
		pEvent = (CHEvent*) pMedallist->getEvent();		
		pInscription = (CHInscription*)CHMemoryDataBase::findInscription(pMedallist->getRegister(), pMedallist->getEvent());		
	}
	
	if (pInscription && pEvent)
	{
		getMembersVector (pInscription, vMembers );
		vMembers.setFcCompare(fnOrderMembersByName);
	}

	for (short i=0;i<2;i++)
	{
		if (!vMembers[i])
		{
			m_pGUI->addContent(pData, pos,"");
			pos++;
			m_pGUI->addContent(pData, pos,"");
			pos++;	
			m_pGUI->addContent(pData, pos,"");
			pos++;	
			continue;
		}
		
		GMember* pMember = (GMember*) vMembers[i];
		m_pGUI->addContent(pData, pos,pMember->getAcreditation());// "1_Athelete_ID"
		pos++;
		m_pGUI->addContent(pData, pos,m_pGUI->getRegisterLName(pMember->getRegister()));// "1_Long_TV_Name"
		pos++;
		m_pGUI->addContent(pData, pos,m_pGUI->getRegisterSName(pMember->getRegister()));// "1_Short_TV_Name"
		pos++;
	}	
}

void CHTVTools::savePoolStandings(CHMatch * pMatch)
{
	if(!pMatch)
		return;

	MSLSortedVector cGroupInfo;

	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHPOOLRESULT));
	
	CHPoolResult * pPoolResult=0;
	while((pPoolResult=(CHPoolResult*)iter())!=0)
	{
		if (pPoolResult->getBye())
			continue;

		if(pPoolResult->getEvent()==pMatch->getEvent() &&
		   pPoolResult->getPhase()==pMatch->getPhase())
		{
			CHTVGroupInfo * pGroupInfo=(CHTVGroupInfo*)cGroupInfo.insert(new CHTVGroupInfo(pPoolResult));

			CHInscription * pInscription = (CHInscription*) pPoolResult->getInscription();
			if (!pInscription)
				continue;

			// Obtenemos el donde avanza.
			CHMatchResult *pMRAdv = pInscription->getLastMatchResult();
			if (pMRAdv)
			{
				CHMatch *pMatchAdv = (CHMatch *)pMRAdv->getMatch();
				if (pMatchAdv && 
					pMatchAdv->getPhaseCode() != pMatch->getPhaseCode() &&
					pMatchAdv->getPhaseOrder() >  pMatch->getPhaseOrder())
				{
/*					pGroupInfo->m_advanceTo     =pMatchAdv ? CHTVApp::getRSC_TV(pMatchAdv, FILE_CSV_POOL_STANDINGS, RSC_PHASE):"";
					if (!pMatchAdv->getIsPool())
						pGroupInfo->m_advanceTo_Game= pMatchAdv ? CHTVApp::getRSC_TV(pMatchAdv, FILE_CSV_POOL_STANDINGS, RSC_UNIT):"";*/
				}
			}
		}
	}	

	if(pMatch->getIsPool())
		savePoolInfo(&cGroupInfo,pMatch);
	else
		saveKnockoutInfo(&cGroupInfo,pMatch);

	cGroupInfo.setFcCompare(fnOrderGroupInfoByRankPo);
	cGroupInfo.sort();

	int index=1;
	short lastPool=0;
	for (short i=0; i<cGroupInfo.entries(); i++ )
	{
		CHTVGroupInfo* pGrpInfo=(CHTVGroupInfo*)cGroupInfo[i];
		if (!pGrpInfo)
			continue;

		CHPoolResult * pPoolResult=pGrpInfo->m_pResult;
		if (lastPool!=pPoolResult->getPoolCode())
			index=1;
		
		m_pGUI->addContent(pPoolResult,0,pPoolResult->getGroup());										// "NOC_Code"
		m_pGUI->addContent(pPoolResult,1,pGrpInfo->m_group);											// "Group"
		m_pGUI->addContent(pPoolResult,2,TOSTRING(pGrpInfo->m_rank));									// "Rank"
		m_pGUI->addContent(pPoolResult,3,pGrpInfo->m_GP);												// "GP"
		m_pGUI->addContent(pPoolResult,4,pGrpInfo->m_W);												// "W"
		m_pGUI->addContent(pPoolResult,5,pGrpInfo->m_D);
		m_pGUI->addContent(pPoolResult,6,pGrpInfo->m_L);												// "L"
		m_pGUI->addContent(pPoolResult,7,pPoolResult->getPointsFStr());									// "Pts"
		m_pGUI->addContent(pPoolResult,8,pPoolResult->getMatchPointsStr());								// "Match Pts"

		m_pGUI->addContent(pPoolResult,9,pGrpInfo->m_displayPos ? pGrpInfo->m_displayPos : index);		// "Display_Pos"

		MSLString irm;
		CHEventResult * pEventResult=(CHEventResult*)pPoolResult->getEventResult();
		if( pEventResult &&
			pEventResult->getQualitativeCode()==DSQ)
			irm="DSQ";

		m_pGUI->addContent(pPoolResult,10,irm);									// "IRM"
		m_pGUI->addContent(pPoolResult,11,"");									// "AdvancedFrom" Empty

		m_pGUI->addContent(pPoolResult,12,pGrpInfo->m_advanceTo);				// "AdvancedTo"
		m_pGUI->addContent(pPoolResult,13,pGrpInfo->m_advanceTo_Game);			// "AdvancedTo_Game"
		
		m_pGUI->addContent(pPoolResult,14,m_pGUI->getRegisterLName(pPoolResult->getRegister()));	// "Country_Long_TV_Name"
		m_pGUI->addContent(pPoolResult,15,m_pGUI->getRegisterSName(pPoolResult->getRegister()));	// "Country_Short_TV_Name"


		index++;

		lastPool=pPoolResult->getPoolCode();
	}

	cGroupInfo.clearAndDestroy();
}

void CHTVTools::savePoolInfo(MSLSortedVector * pColGroupInfo,CHMatch * pMatch)
{
	CHPhase * pPhase=(CHPhase*)pMatch->getPhase();
	MSLSet colPoolResults;
	pPhase->getPoolResults(colPoolResults);

	MSLSetIterator iterPoolRes(colPoolResults);

	CHPoolResult * pPoolRes=0;
	while((pPoolRes=(CHPoolResult *)iterPoolRes())!=0)
	{
		if(pPoolRes->getInscription())
		{
			CHTVGroupInfo aGroupInfo((CHPoolResult*)pPoolRes);
			CHTVGroupInfo * pGroupInfo=(CHTVGroupInfo*)pColGroupInfo->find(&aGroupInfo);
			if(pGroupInfo)
			{
				char car=char((pPoolRes->getPool()->getOrder()-1)+'A');
				MSLString grp(car);
				pGroupInfo->m_group=grp;
				pGroupInfo->m_rank=pPoolRes->getRank();
				pGroupInfo->m_GP=pPoolRes->getMPlayed();
				pGroupInfo->m_W=pPoolRes->getMWon();
				pGroupInfo->m_D=pPoolRes->getMDrawn();
				pGroupInfo->m_L=pPoolRes->getMLost();				
				pGroupInfo->m_displayPos=pPoolRes->getRankPo();
			}
		}
	}
}

void CHTVTools::saveKnockoutInfo(MSLSortedVector * pColGroupInfo,CHMatch * pMatch)
{
	CHDefinition &aDef = (CHDefinition&)CHMemoryDataBase::getDefinition();

	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMATCHRESULT));

	CHMatchResult * pMR=0;
	while( (pMR=(CHMatchResult*)iter())!=0)
	{
		//victorias hasta ese partido
		if(pMR->getEvent()==pMatch->getEvent()                         && 
		   pMR->getPhase()->getOrder()<=pMatch->getPhase()->getOrder() &&
		   pMR->getMatchStatus()>=CHMemoryDataBase::eUnofficial		   &&	
		   pMR->getInscription())
		{
			CHTVGroupInfo aGroupInfo((CHPoolResult*)pMR->getPoolResult());
			CHTVGroupInfo * pGroupInfo=(CHTVGroupInfo*)pColGroupInfo->find(&aGroupInfo);
			if(pGroupInfo)
			{
				/*if(pMR->getClassPoints() == aDef.getPointsWin())
					pGroupInfo->m_W++;

				else if(pMR->getClassPoints() == aDef.getPointsLoss())
					pGroupInfo->m_L++;*/
			}
		}
	}
}

void CHTVTools::saveBracket(CHMatch * pMatch)
{
	if( !pMatch )
		return;
	CHMatchResult * pMatchResult = 0;
	MSLSortedVector vAllMatchResults;
	m_pMem->getVector(__CHMATCHRESULT,vAllMatchResults,pMatch->getEvent());
	
	for(long i=0;i<vAllMatchResults.entries();i++)
	{
		pMatchResult = (CHMatchResult*)vAllMatchResults[i];
		if (pMatchResult->getPhaseCode()==SWISS_ROUND)
			continue;

		saveBracket(pMatchResult);
	}
}

void CHTVTools::saveBracket(CHMatchResult *pMatchResult)
{
	if( !pMatchResult )
		return;
	
	CHMatch * pMatch = (CHMatch*) pMatchResult->getMatch();
	MSLString	rsc = CHTVApp::getRSC_TV(pMatch, RSC_ALL),
				matchID = NULLSTRING,
				key = NULLSTRING;

	// El rsc pasado es el de msl
	MSLString ph,unit=NULLSTRING;
	if( rsc.length()==9 )
	{
		ph	= rsc(6,1);	
		unit= rsc(7,2);	// dos ultimos
	}

	matchID = ph + "_" + unit + "_";
	key = matchID;

	if( pMatchResult->getColor() == CHMatchResult::eWhite )
	{
		matchID += "T";
		key += "1";
	}
	else
	{
		matchID += "B";
		key += "2";
	}
	
	GData * pKey = m_pGUI->data(key);	

	m_pGUI->addContent(pKey,0,matchID);	// Match_ID
	m_pGUI->addContent(pKey,1,pMatchResult->getBye() ? TV_BYE:getAthleteID(pMatchResult->getRegister())); // "Athlete_ID"
}

void CHTVTools::saveHistory(CHMatch * pMatch)
{
	if( !pMatch )
		return;
	CHMatch * pMatchAux = 0;
	CHMatchResult * pMatchResult = 0, *pMatchResultAux = 0;
	MSLSortedVector vPrevMatches;
	long i,j;
	MSLString key = NULLSTRING;

	// Red
	pMatchResult = pMatch->getWhite();
	if( pMatchResult )
	{
		m_pMem->getVector(__CHMATCH,vPrevMatches,pMatchResult->getInscription());
		vPrevMatches.setFcCompare(fnOrderMatchByInvPhaseAndCode);

		for(i=0,j=1;i<vPrevMatches.entries();i++)
		{
			pMatchAux = (CHMatch *)vPrevMatches[i];
			if( pMatchAux == pMatch )
				continue;
			pMatchResultAux = pMatchAux->findMatchResult((CHInscription*)pMatchResult->getInscription());
			if( pMatchResultAux && pMatchAux->getMatchNumber() )
			{
				key = (pMatchResult->getColor() == CHMatchResult::eBlack?"1":"2")+TOSTRING(j++);
				saveHistory(pMatchResultAux,key);
			}
		}
	}

	// Blue
	pMatchResult = pMatch->getBlack();
	if( pMatchResult )
	{
		m_pMem->getVector(__CHMATCH,vPrevMatches,pMatchResult->getInscription());
		vPrevMatches.setFcCompare(fnOrderMatchByInvPhaseAndCode);
		for(i=0,j=1;i<vPrevMatches.entries();i++)
		{
			pMatchAux = (CHMatch *)vPrevMatches[i];
			if( pMatchAux == pMatch )
				continue;
			pMatchResultAux = pMatchAux->findMatchResult((CHInscription*)pMatchResult->getInscription());
			if( pMatchResultAux && pMatchAux->getMatchNumber() )
			{
				key = (pMatchResult->getColor() == CHMatchResult::eBlack?"1":"2")+TOSTRING(j++);
				saveHistory(pMatchResultAux,key);
			}
		}

		vPrevMatches.clear();
	}

	
}

void CHTVTools::saveHistory(CHMatchResult *pMatchResult, MSLString key)
{
	if( !pMatchResult )
		return;

	CHMatchResult * pOpp = (CHMatchResult * ) pMatchResult->getOpponent();
	if( !pOpp )
		return;

	CHMatch * pMatch = (CHMatch*) pMatchResult->getMatch();

	GData * pKey = m_pGUI->data(key);	
	MSLString disPos = key(1,1);
	
	int pos=0;
	m_pGUI->addContent(pKey,pos++,getAthleteID(pMatchResult->getRegister()));			// Athlete_ID
	m_pGUI->addContent(pKey,pos++,pOpp->getBye() ? TV_BYE:getAthleteID(pOpp->getRegister())); // "Opp_ID"
	m_pGUI->addContent(pKey,pos++,disPos);											// "Match_Display_Pos"

	// "Result"
	MSLString res;
	if( pOpp->getBye() )
		res = TV_BYE;
	else if (!pOpp->getInscription())
		res = TV_NOCOMP;
	else
	{
		CHMatch::typeWinner winner = CHMatch::typeWinner(pMatch->getWinner());
		if (winner==CHMatch::eWinnerWhite && pMatchResult->getColor()==CHMatchResult::eWhite)
			res = "W";
		else if (winner==CHMatch::eWinnerBlack && pMatchResult->getColor()==CHMatchResult::eBlack)
			res = "W";
		else if (winner==CHMatch::eDraw)
			res = "D";
		else
			res = "L";
	}
		
	m_pGUI->addContent(pKey,pos++,res);

	// "Decision"
	MSLWString dec = NULLWSTRING;
	if (pOpp->isQualitative())
		dec = pOpp->getQualitativeSDescription();

	m_pGUI->addContent(pKey,pos++,dec);
	
	// "IRM"
	MSLWString irm = NULLWSTRING; 
	if (pMatchResult->isQualitative())
		irm = pMatchResult->getQualitativeSDescription();

	m_pGUI->addContent(pKey,pos++,irm);

}

void CHTVTools::saveMedals(CHMatch * pMatch)
{
	if( !pMatch )
		return;

	GTHEvent * pEvent = pMatch->getEvent();
	MSLSortedVector vEventResults;
	m_pMem->getVector(__CHEVENTRESULT,vEventResults,pEvent);
	vEventResults.setFcCompare(fnOrderEventResultByRankPo);
	CHEventResult * pEventResult = 0;
	for( long i=0,j=1;i<vEventResults.entries();i++ )
	{
		pEventResult = (CHEventResult *)vEventResults[i];
		if( pEventResult->getRank() )
			saveMedals(pEventResult,j++);
		else 
			m_pGUI->delContent(pEventResult);
	}
}

void CHTVTools::saveMedals(CHEventResult *pEventResult, const long i)
{
	if( !pEventResult )
		return;

	int pos=0;
	m_pGUI->addContent(pEventResult,pos++,getAthleteID(pEventResult->getRegister()));	// Athlete_ID
	m_pGUI->addContent(pEventResult,pos++,pEventResult->getCountry());	// NOC_Code
	m_pGUI->addContent(pEventResult,pos++,m_pGUI->getRegisterLName(pEventResult->getRegister()));	// Long_TV_Name
	m_pGUI->addContent(pEventResult,pos++,m_pGUI->getRegisterSName(pEventResult->getRegister()));	// Short_TV_Name

	MSLString medal = NULLSTRING;
	GMedallist * pMedallist = 0;
	MSLSetIterator it(m_pMem->getCol(__GMEDALLIST));
	while( (pMedallist = (GMedallist*)it())!=0 )
	{
		if( pMedallist->getEventKey() == pEventResult->getEventKey() &&
			pMedallist->getRegister() == pEventResult->getRegister() )
		{
			medal = getMedalDesc(pMedallist->getMedal()->getMedal());
			break;
		}
	}
	m_pGUI->addContent(pEventResult,pos++,medal);	// Medal
	m_pGUI->addContent(pEventResult,pos++,TOSTRING(i));	// Display_Pos
	m_pGUI->addContent(pEventResult,pos++,pEventResult->getRank());	// Rank
}

// Changes
void CHTVTools::changedRegister(bool update,GRegister *pRegister)
{
	if ( !pRegister ) 
		return;

	// Actualizamos registros
	changedParticipant(update, pRegister);

	// Actualizamos competidores: competitors, medals, event_info(judges)
	// Recorrer los combates y actualizar los registros afectados
	MSLSortedVector vMatches;
	getMatches(vMatches);

	CHMatch * pMatch	= 0;
	GRegister * pReg	= 0;
	CHMatchResult * pBlue = 0, * pWhite = 0;
	GTHMatchJudge * pMatchJudge = 0;
	CHEventResult * pEventResult = 0;

	for(long i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		pWhite = pMatch->getWhite();
		pBlue = pMatch->getBlack();

		// Competitors
		pReg = pWhite->getRegister();
		if( pReg == pRegister )
			changedCompetitor(update,pWhite);

		pReg = pBlue->getRegister();
		if( pReg == pRegister )
			changedCompetitor(update,pBlue);
		
		// Medals (si procede...) 
		if( m_pGUI->callForIsRequired(EVENT_LEVEL,FILE_CSV_MEDALS,DWORD(pMatch)) )
		{
			pEventResult = (CHEventResult*)pBlue->getEventResult();
			pReg = pEventResult ? pEventResult->getRegister():0;
			if( pReg && pReg == pRegister )
				changedMedals(update,pMatch);
			pEventResult = (CHEventResult*)pWhite->getEventResult();
			pReg = pEventResult ? pEventResult->getRegister():0;
			if( pReg && pReg == pRegister )
				changedMedals(update,pMatch);
		}

		// Event_info
		/*pMatchJudge = (GTHMatchJudge*)pMatch->getMatchJudge(CHMatchJudge::eReferee,fnOrderMatchJudgeByPosition);
		if( pMatchJudge && pMatchJudge->getRegister() == pRegister )
			changedEventInfo(update,pMatch);*/
	}

	// NO OG 
	m_pGUI->rebuildCSV(FILE_CSV_MEDAL_STANDINGS,DWORD(SPORT_LEVEL));
}

void CHTVTools::changedParticipant(bool update,GRegister *pRegister)
{
	if( pRegister )
	{
		m_pGUI->useCSV(SPORT_LEVEL,FILE_CSV_PARTICIPANTS);
		if( update )
			saveRegister(pRegister);
		else
			m_pGUI->delContent(pRegister);
		m_pGUI->saveCSV();
	}
}

void CHTVTools::changedCompetitor(bool update,CHMatchResult *pMatchResult)
{
	if( pMatchResult )
	{
		CHMatch *pMatch = (CHMatch*)pMatchResult->getMatch();
		CHEvent *pEvent = pMatch ? (CHEvent*)pMatch->getEvent() : 0;
		if (pEvent && !pEvent->isTeam())
			m_pGUI->useCSV(DWORD(pMatch),FILE_CSV_COMPETITORS);
		else
			m_pGUI->useCSV(DWORD(pMatch),FILE_CSV_TEAM_COMPETITORS);
		
		if( update )
			saveCompetitor(pMatchResult);
		else
			m_pGUI->delContent(pMatchResult);
		m_pGUI->saveCSV();		
	}

}
void CHTVTools::changedEventInfo(bool update,CHMatch *pMatch)
{
	if( pMatch )
	{
		m_pGUI->useCSV(DWORD(pMatch),FILE_CSV_EVENT_INFO);
		if( update )
			saveEventInfo(pMatch);
		else
			m_pGUI->delContent(pMatch);
		m_pGUI->saveCSV();
	}
}

void CHTVTools::changedMedals(bool update,CHEvent *pEvent)
{
	UNREFERENCED_PARAMETER(update);
	if( pEvent )
	{
		MSLSortedVector vMatches;
		m_pMem->getVector(__CHMATCH,vMatches,pEvent);
		CHMatch * pMatch = 0;
		for(long i=0;i<vMatches.entries();i++)
		{
			pMatch = (CHMatch *)vMatches[i];
			if( m_pGUI->callForIsRequired(EVENT_LEVEL,FILE_CSV_MEDALS,DWORD(pMatch)) )
				m_pGUI->rebuildCSV(FILE_CSV_MEDALS,DWORD(pMatch));
		}
		// NO OG 
		m_pGUI->rebuildCSV(FILE_CSV_MEDAL_STANDINGS,DWORD(SPORT_LEVEL));
	}
}

void CHTVTools::changedMedals(bool update,CHMatch *pMatch)
{
	if( pMatch )
	{
		m_pGUI->useCSV(DWORD(pMatch),FILE_CSV_MEDALS);
		if( update )
			saveMedals(pMatch);
		else
			m_pGUI->delContent(pMatch);
		m_pGUI->saveCSV();
	}
}

// Help
void CHTVTools::getWinnsLossesDrawn(CHMatchResult *pMatchResult, short &W, short&L, short &D)
{
	W=L=D=0;
	if( !pMatchResult || !pMatchResult->getInscription() )
		return;

	CHPoolResult * pPoolResult = (CHPoolResult*) pMatchResult->getPoolResult();
	if (!pPoolResult)
		return;

	W = pPoolResult->getMWon();
	L = pPoolResult->getMLost();
	D = pPoolResult->getMDrawn();
}

int CHTVTools::getOrderOnCourt(CHMatchResult* pMatchResult)
{
	// Retorno : -1=Nada, 0=Current, 1=Next1, 2=Next2, 3=Next3, etc... 
	if (!pMatchResult)
		return -1;
	
	CHMatch *pCurrMatch=(CHMatch *)pMatchResult->getMatch();
	if (!pCurrMatch || !pCurrMatch->getSession() || !pCurrMatch->getCourt())
		return -1;
	
	if (pCurrMatch->getStatus()>=GMemoryDataBase::eFinished)
		return -1;
	
	/* Esto no vale, nos crea mas de un current en muchos casos.
	if (pCurrMatch->getStatus()==GMemoryDataBase::eRunning || pCurrMatch->getStatus()==GMemoryDataBase::eUnofficial)
		return 0;
	*/
	
	CHMatch *pMatch = 0;
	GCourt *pCourt = pCurrMatch->getCourt();
	GSession *pSession = pCurrMatch->getSession();
	
	MSLSortedVector vMatches(fnOrderMatchByDateTime);
	MSLSetIterator it (CHMemoryDataBase::getCol(__CHMATCH));
	while ( (pMatch=(CHMatch*) it())!=0 )
	{
		if ( !pMatch )
			continue;
		if( !pMatch->getMatchNumber() )
			continue;
		if( pMatch->getSession() != pSession )
			continue;
		if( pMatch->getCourt() !=pCourt )
			continue;
		if (pMatch->getStatus()>=GMemoryDataBase::eFinished)
			continue;
		if (pMatch->getStatus()<GMemoryDataBase::eSchedulled)
			continue;

		vMatches.insert(pMatch);
	}
	
	bool isUnoficial = false; 
	int retVal = -1, valUnoff = -1;
	vMatches.sort();
	for (size_t i=0; i<size_t(vMatches.entries()); i++)
	{
		pMatch=(CHMatch *)vMatches[i];

		// Control Running.
		if (pMatch->getStatus()==GMemoryDataBase::eRunning && retVal<0)
			retVal=0;

		// Control unoffcial.
		if (pMatch->getStatus()==GMemoryDataBase::eUnofficial && retVal<0)
			retVal--;
		
		// Control start list y schedule.
		if (pMatch->getStatus()==GMemoryDataBase::eSchedulled || pMatch->getStatus()==GMemoryDataBase::eStartList)
			retVal = (retVal<0) ? 1 : retVal+1;
		
		// He encontrado el current.
		if (pCurrMatch->getMatchNumber()==pMatch->getMatchNumber())
		{	
			// Si current no es unofficial, nos vamos con su valor.
			isUnoficial = pCurrMatch->getStatus()==GMemoryDataBase::eUnofficial; 
			if (isUnoficial==false)
				return retVal;
			
			// Si es unofficial, hay que ver los siguientes para descartar duplicados de current.
			valUnoff = retVal;
		}

		// Si es unofficial y hemos encontrado otro running o unoficial, nos sin valor... 
		if (isUnoficial && (retVal==0 || retVal<valUnoff))
			return -1;
	}
	
	// Si es unofficial no se encontro otro otro running o unoficial, nos vamos con 0=current... 
	if (isUnoficial)
		return 0;
	
	return -1;
}

MSLString CHTVTools::getMedalDesc(short rank)
{
	MSLString sLang = GUtils::getAppLang();
	GMedal * pMedal = m_pMem->findMedal(char(rank));
	return pMedal ? pMedal->getSDescription(sLang).toAscii() : "";
}

void CHTVTools::getCSVMedalStandings()
{
	VMedalStandings aVMedalStandings;
	for(long i=0;i<aVMedalStandings.getNLines();i++)
	{
		GMedalsByNoc * pMedalsByNoc = (GMedalsByNoc *)aVMedalStandings[i];
		saveMedalStandings(pMedalsByNoc,i);
	}
}

void CHTVTools::saveMedalStandings(GMedalsByNoc *pMedalsByNoc, const long i)
{
	if( !pMedalsByNoc ) 
		return;

	char rk[4];
	sprintf_s(rk,4,"%.3d" ,pMedalsByNoc->getRk());
	MSLString keyCode = MSLString(rk) + "_" + TOSTRING(i+1);
	GData *pData = m_pGUI->data(keyCode);
	m_pGUI->addContent(pData,0,pMedalsByNoc->getGroup()->getGroup());		// NOC_Code
	m_pGUI->addContent(pData,1,pMedalsByNoc->getRk());						// Rank
	m_pGUI->addContent(pData,2,pMedalsByNoc->getRkPo());					// Display_Pos
	m_pGUI->addContent(pData,3,pMedalsByNoc->getGroup()->getLDescription());// Long_TV_Name
	m_pGUI->addContent(pData,4,pMedalsByNoc->getNMedals(1));				// Gold
	m_pGUI->addContent(pData,5,pMedalsByNoc->getNMedals(2));				// Silver
	m_pGUI->addContent(pData,6,pMedalsByNoc->getNMedals(3));				// Bronze
	m_pGUI->addContent(pData,7,pMedalsByNoc->getNMedals());					// Total
}
