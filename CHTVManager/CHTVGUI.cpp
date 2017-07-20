/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVGUI.cpp
*	Description	:Defines the entry point for the application
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: WU TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHTVGUI.h"
#include "CHTVApp.h"
#include "CHTVDefs.h"
#include "CHTVOrderFunctions.h"
#include <OVR\core\th\gthmsgdefines.h>

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"

CHTVGUI::CHTVGUI(long id)
:MSLAppModuleTV(id)
,m_pMem(0)
{
}

CHTVGUI::~CHTVGUI()
{
}

bool CHTVGUI::onInit()
{
	bool rc = MSLAppModuleTV::onInit();
	m_tools.init(this);
	m_pMem = (CHMemoryDataBase*)GMemoryDataBase::getMem();
	return rc;
}

void CHTVGUI::callForRequiredFiles()
{
	m_tools.init(0);
	MSLString mode=m_tools.getMode();
	DWORD file=0;
	if( mode=="TV" || mode=="FULL" )
	{
		// PARTICIPANTS
		file=addReqFile(FILE_CSV_PARTICIPANTS,SPORT_LEVEL,fnOrderRegByTVLName);
			addReqField(file,"Athlete_ID");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Short_TV_Name");
			addReqField(file,"NOC_Code");
			addReqField(file,"Country_Long_TV_Name");
			addReqField(file,"Country_Short_TV_Name");
	
			
		// SCHEDULE
		file=addReqFile(FILE_CSV_SCHEDULE,SESSION_LEVEL,fnOrderPhaseByDateTime); 
			addReqField(file,"Gender");
			addReqField(file,"Event_Code");
			addReqField(file,"Competition_Phase");
			addReqField(file,"Event_Unit");

		// SCHEDULE_DETAILED
		file=addReqFile(FILE_CSV_SCHEDULE_DETAILED,SESSION_LEVEL,fnOrderMatchByDateTime); 
			addReqField(file,"Gender");
			addReqField(file,"Event_Code");
			addReqField(file,"Competition_Phase");
			addReqField(file,"Event_Unit");
			addReqField(file,"Mat_Code");
			addReqField(file,"Bout_Number");
			addReqField(file,"Start_Time");

		// SCHEDULE_UNIT
		file=addReqFile(FILE_CSV_SCHEDULE_UNIT,SESSION_LEVEL,fnOrderKey); 
			addReqField(file,"Gender");
			addReqField(file,"Event_Code");
			addReqField(file,"Phase_Code");
			addReqField(file,"Unit_Code");
			addReqField(file,"Venue_Code");
			addReqField(file,"Court_Code");
			addReqField(file,"Unit_Order");
			addReqField(file,"Unit_Number");
			addReqField(file,"Session_Code");
			addReqField(file,"Start_Date");
			addReqField(file,"Start_Time");
			addReqField(file,"Unit_Status");
			addReqField(file,"Medal_Unit");
			addReqField(file,"Athlete_ID");
			addReqField(file,"Athlete_Description");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Short_TV_Name");
			addReqField(file,"NOC_Code");
			addReqField(file,"Position");
			addReqField(file,"IRM");
			addReqField(file,"Result");
			addReqField(file,"Ranking");
			addReqField(file,"Display_Pos");
			addReqField(file,"Current_OnCourt");
			addReqField(file,"Next_OnCourt");
			addReqField(file,"Round");


		// EVENT INFO
		file=addReqFile(FILE_CSV_EVENT_INFO,EVENT_LEVEL);
			addReqField(file,"Discipline");
			addReqField(file,"Gender");
			addReqField(file,"Event_Code");
			addReqField(file,"Competition_Phase");
			addReqField(file,"Event_Unit");
			addReqField(file,"Venue");
			addReqField(file,"Round");
			addReqField(file,"Referee_Long_TV_Name");
			addReqField(file,"Referee_Short_TV_Name");
			addReqField(file,"Referee_NOC");
			addReqField(file,"Mat_Code");

		// OFFICIALS
		file=addReqFile(FILE_CSV_OFFICIALS,EVENT_LEVEL,fnOrderMatchJudgeByPosition);
			addReqField(file,"Position");
			addReqField(file,"NOC");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Short_TV_Name");
		
		// COMPETITORS
		file=addReqFile(FILE_CSV_COMPETITORS,EVENT_LEVEL,fnOrderMatchResultByColor);
			addReqField(file,"Athlete_ID");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Short_TV_Name");
			addReqField(file,"NOC_Code");
			addReqField(file,"Color");
			addReqField(file,"Score");
			addReqField(file,"Points");
			addReqField(file,"Decision");
			addReqField(file,"W");
			addReqField(file,"L");
			addReqField(file,"Display_Pos");
			addReqField(file,"IRM");
			addReqField(file,"AdvanceTo_Phase");
			addReqField(file,"AdvanceTo_Match");
		
		// COMPETITORS
		file=	addReqFile(FILE_CSV_POOL_STANDINGS,EVENT_LEVEL,fnOrderPoolResultsByRankPo);
				addReqField(file,"NOC_Code");
				addReqField(file,"Group");
				addReqField(file,"Rank");
				addReqField(file,"GP");
				addReqField(file,"W");
				addReqField(file,"L");
				addReqField(file,"Pts");
				addReqField(file,"Match_Pts");
				addReqField(file,"Display_Pos");
				addReqField(file,"IRM");
				addReqField(file,"AdvanceFrom");
				addReqField(file,"AdvanceTo");
				addReqField(file,"AdvanceTo_Game");				
				addReqField(file,"Long_TV_Name");
				addReqField(file,"Short_TV_Name");
	
		// BRACKET
		file=addReqFile(FILE_CSV_BRACKET, EVENT_LEVEL, fnOrderKey);
			addReqField(file,"Match_ID");
			addReqField(file,"Athlete_ID");
			
		// TOURNAMENT HISTORY
		file=addReqFile(FILE_CSV_TOURNAMENT_HISTORY, EVENT_LEVEL,fnOrderKey);
			addReqField(file,"Athlete_ID");
			addReqField(file,"Opp_ID");
			addReqField(file,"Match_Display_Pos");
			addReqField(file,"Result");
			addReqField(file,"Decision");
			addReqField(file,"IRM");

		// MEDALS
		file=addReqFile(FILE_CSV_MEDALS, EVENT_LEVEL,fnOrderEventResultByRankPo);
			addReqField(file,"Athlete_ID");
			addReqField(file,"NOC_Code");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Short_TV_Name");
			addReqField(file,"Medal");
			addReqField(file,"Display_Pos");
			addReqField(file,"Rank");

		// MEDAL STANDINGS
		file=addReqFile(FILE_CSV_MEDAL_STANDINGS, SPORT_LEVEL,fnOrderKey);
			addReqField(file,"NOC_Code");
			addReqField(file,"Rank");
			addReqField(file,"Display_Pos");
			addReqField(file,"Long_TV_Name");
			addReqField(file,"Gold");
			addReqField(file,"Silver");
			addReqField(file,"Bronze");
			addReqField(file,"Total");
	}
	
	if( mode=="TV" || mode=="FULL" )
	{
		// STS Session
		addReqFile("session.sts",SESSION_LEVEL,fnOrderMatchByMatchNumber);

		// GRD Event
		addReqFile("event.grd",EVENT_LEVEL);
		// GRD a nivel de session
		addReqFile("session.grd",SESSION_LEVEL);
	}

	// GRD Sport
	addReqFile("event.grd",SPORT_LEVEL);

	MSLAppModuleTV::callForRequiredFiles();
}

void CHTVGUI::callForPaths()
{
	DWORD		pathSession(0),
				pathWU=addPath(ROOT_LEVEL,"CH",SPORT_LEVEL);

	if( m_tools.getMode()=="TV" || m_tools.getMode()=="FULL" )
	{
		CHMatch *pMatch = 0;
		GSession *pSession = 0, * lastSession = 0;
		
		MSLSortedVector vMatches;
		m_tools.getMatches(vMatches);
		
		for( long i=0; i<vMatches.entries(); i++ )
		{
			pMatch = (CHMatch *)vMatches[i];
			pSession = (GSession *)pMatch->getSession();
			if( !pSession && !pathSession )
				pathSession = addPath(pathWU,m_tools.getSessionDesc(pSession),DWORD(pSession));
			else if( pSession && pSession != (GSession *)lastSession )
			{
				lastSession=pSession;
				pathSession = addPath(pathWU,m_tools.getSessionDesc(pSession),DWORD(pSession));
			}
			addPath(pathSession,m_tools.getDesc(pMatch),DWORD(pMatch),m_tools.getStatus(pMatch));
		}
	}
}

void CHTVGUI::callForContent  (long level,MSLString name,DWORD dataParent)
{
	UNREFERENCED_PARAMETER(level);	
	UNREFERENCED_PARAMETER(level);
	
	if( name==FILE_CSV_PARTICIPANTS )
		m_tools.saveParticipants();
	else if( name==FILE_CSV_SCHEDULE && dataParent )
		m_tools.saveSessionSchedule((GSession *)dataParent);
	else if( name==FILE_CSV_SCHEDULE_DETAILED && dataParent )
		m_tools.saveSessionScheduleDetailed((GSession *)dataParent);
	else if( name==FILE_CSV_SCHEDULE_UNIT && dataParent )
		m_tools.saveSessionScheduleUnit((GSession *)dataParent);
	else if( name==FILE_CSV_EVENT_INFO && dataParent )
		m_tools.saveEventInfo((CHMatch *)dataParent);
	else if( name==FILE_CSV_OFFICIALS && dataParent )
		m_tools.saveOfficials((CHMatch *)dataParent);
	else if( name==FILE_CSV_COMPETITORS && dataParent )
		m_tools.saveCompetitor((CHMatch *)dataParent);
	else if( name==FILE_CSV_POOL_STANDINGS && dataParent )
		m_tools.savePoolStandings((CHMatch *)dataParent);
	else if( name==FILE_CSV_BRACKET && dataParent )
		m_tools.saveBracket((CHMatch *)dataParent);
	else if( name==FILE_CSV_TOURNAMENT_HISTORY && dataParent )
		m_tools.saveHistory((CHMatch *)dataParent);
	else if( name==FILE_CSV_MEDALS && dataParent )
		m_tools.saveMedals((CHMatch *)dataParent);

	MSLAppModuleTV::callForContent(level,name,dataParent);
}

bool CHTVGUI::callForIsRequired (long level,MSLString name,DWORD dataParent)
{
	UNREFERENCED_PARAMETER(level);
	if( name==FILE_CSV_MEDALS && dataParent )
	{
		CHMatch * pMatch = (CHMatch *)dataParent;
		if(  pMatch->getPhaseCode() == BRONZE_MEDAL	|| 
			 pMatch->getPhaseCode() == GOLD_MEDAL	)
			return true;

		return false;
	}
		
	if (name==FILE_CSV_BRACKET && dataParent )
	{
		CHMatch * pMatch = (CHMatch *)dataParent;
		return true;		
	}

	if (name==FILE_CSV_TOURNAMENT_HISTORY && dataParent )
	{
		CHMatch * pMatch = (CHMatch *)dataParent;
		return true;		
	}

	return true;
}


void CHTVGUI::onComms(MSLTransaction &pt)
{
	// TODAVIA NO ESTA ACTUALIZADO EL MODELO
	bool preprocessed=false;
	long trnId = pt.getTrnId();	
	switch( trnId )
	{
	case TRN_NOTIFICATION:
		preprocessed=preprocessNotifies(pt);
		break;	
	case TRN_SET_PROGRESSION:
	case TRN_SET_UNPROGRESSION:
		preprocessed=preprocessTrnProgression(pt);
		break;
	}
	if( !preprocessed )
	{
		pt.resetPos();
		MSLAppModuleTV::onComms(pt);
	}
}

void CHTVGUI::onComms(long idTrn,bool bInsert,GData *pData,long index)
{
	UNREFERENCED_PARAMETER(index);
	long isA = pData->isA();
	if (isA == __GREGISTER)
		m_tools.changedRegister(bInsert,(GRegister*)m_pMem->find(*pData));
	
	if( idTrn == TRN_CHANGE_MATCH_STATUS )
	{
		if( isA == __CHMATCH )
		{
			CHMatch * pMatch = (CHMatch *)m_pMem->find(*(CHMatch *)pData);
			if( pMatch )
			{
				if( pMatch->hasByes() )
				{
					delPath(DWORD(pMatch));
					rebuildCSV(FILE_CSV_SCHEDULE,DWORD((GSession*)pMatch->getSession()));
					rebuildCSV(FILE_CSV_SCHEDULE_DETAILED,DWORD((GSession*)pMatch->getSession()));
				}
				else
					pathStatus(DWORD(pMatch),m_tools.getStatus(pMatch));
				rebuildCSV(FILE_CSV_SCHEDULE_UNIT,DWORD((GSession*)pMatch->getSession()));
			}
			
		}		
	}
	
	MSLAppModuleTV::onComms(idTrn,bInsert,pData,index);
}

bool CHTVGUI::preprocessNotifies(MSLTransaction &pt)
{
	long isA;
	bool bInsert;
	MSLPack pack;
	while (pt.get(isA,bInsert,pack))
	{
		GData *pData=m_pMem->getObject(isA,pack);
		if( !pData )
			break;
		GNotify * pNotify =(GNotify *)pData;
		long nID=pNotify->getID();
		MSLString buffer=pNotify->getBuffer();
		MSLString rem(buffer);
		MSLString tokStr;
		MSLString key="";
		int isA=-1,index=0;

		while( rem.tok("|",tokStr,rem) )
		{
			if(index==0)		//isA
				isA=atoi(tokStr);
			else if(index==1)	//key
				key=tokStr;
			else
				break;
			index++;
		}
		if(isA==-1)
			return false;

		CHMatch *pMatch = 0;
	
		switch( nID )
		{
		case N_SCHEDULE:
			{
				if( isA == __CHMATCH )
				{
					updateModel(pt); // actualizo el modelo
					pMatch = (CHMatch *)m_pMem->getCol(__CHMATCH).find(&key);
					if( pMatch )
					{
						rebuildCSV(FILE_CSV_SCHEDULE,DWORD((GSession*)pMatch->getSession()));
						rebuildCSV(FILE_CSV_SCHEDULE_DETAILED,DWORD((GSession*)pMatch->getSession()));
						rebuildCSV(FILE_CSV_SCHEDULE_UNIT,DWORD((GSession*)pMatch->getSession()));
					}
					return true; // processed
				}
				break;
			}
		}
	}
	return false; // not processed
}

bool CHTVGUI::preprocessTrnOfficials(MSLTransaction &pt)
{
	long isA;
	bool bInsert;
	MSLPack pack;
	GData *pData=0;
	while (pt.get(isA,bInsert,pack))
	{
		pData=m_pMem->getObject(isA,pack);
		if (!pData)
			break;
		CHMatch * pMatch = 0;
		if( isA == __CHMATCH )
		{
			updateModel(pt); // actualizo el modelo
			pMatch = (CHMatch *)m_pMem->find(*pData);
		}
		else if( isA == __GTHMATCHJUDGE )
		{
			if( bInsert )
			{
				updateModel(pt); // actualizo el modelo
				GTHMatchJudge *pMatchJudge = (GTHMatchJudge *)m_pMem->find(*pData);
				pMatch = pMatchJudge ? (CHMatch*) pMatchJudge->getMatch():0;
			}
			else
			{
				GTHMatchJudge *pMatchJudge = (GTHMatchJudge *)m_pMem->find(*pData);
				pMatch = pMatchJudge ? (CHMatch*) pMatchJudge->getMatch():0;
				updateModel(pt); // actualizo el modelo
				pMatch = (CHMatch *)m_pMem->find(*pMatch);
			}
		}
		
		if( pMatch )
		{
			rebuildCSV(FILE_CSV_EVENT_INFO,DWORD(pMatch));
			rebuildCSV(FILE_CSV_OFFICIALS,DWORD(pMatch));
			return true;
		}
	}
	return false;
}

bool CHTVGUI::preprocessTrnDataEntry(MSLTransaction &pt)
{
	long isA;
	bool bInsert;
	MSLPack pack;
	GData *pData=0;
	while (pt.get(isA,bInsert,pack))
	{
		pData=m_pMem->getObject(isA,pack);
		if (!pData)
			break;
	
		if( isA == __CHMATCH )
		{
			updateModel(pt); // actualizo el modelo
			CHMatch * pMatch = (CHMatch *)m_pMem->find(*pData);
			if( pMatch )
			{
				rebuildCSV(FILE_CSV_COMPETITORS,DWORD(pMatch));				
				rebuildCSV(FILE_CSV_SCHEDULE_UNIT,DWORD((GSession*)pMatch->getSession()));
			}
			return true;
		}
		else if( isA == __CHMATCHRESULT )
		{
			updateModel(pt); // actualizo el modelo
			CHMatchResult * pMatchResult = (CHMatchResult *)m_pMem->find(*pData);
			if (pMatchResult->getMatch())
				rebuildCSV(FILE_CSV_COMPETITORS,DWORD(pMatchResult->getMatch()));			
		}

	}
	return false;
}

bool CHTVGUI::preprocessTrnProgression(MSLTransaction &pt)
{
	long isA;
	bool bInsert;
	MSLPack pack;
	GData *pData=0;
	while (pt.get(isA,bInsert,pack))
	{
		pData=m_pMem->getObject(isA,pack);
		if (!pData)
			break;
		// A donde progresa
		if( isA == __CHMATCHRESULT )
		{
			updateModel(pt); // actualizo el modelo
			CHMatchResult * pMatchResult = (CHMatchResult *)m_pMem->find(*pData);
			CHMatch *pMatch = pMatchResult ? (CHMatch*) pMatchResult->getMatch():0;
			if( pMatch )
			{
				// Cogemos la phase order de donde viene
				short phaseOrder = 0;
				CHMatchResult *pMatchResultSource = pMatchResult->getSourceByProgression();
				CHMatch * pMatchSource = pMatchResultSource ? (CHMatch*)pMatchResultSource->getMatch():0;
				if( pMatchSource )
					phaseOrder = pMatchSource->getPhaseOrder();

				// competidores
				
				rebuildCSV(FILE_CSV_COMPETITORS,DWORD(pMatch));				
				rebuildCSV(FILE_CSV_SCHEDULE_UNIT,DWORD((GSession*)pMatch->getSession()));

				MSLSortedVector vMatches;
				m_pMem->getVector(__CHMATCH,vMatches,pMatch->getEvent());
				short courtProgressed=0;
				for(long i=0;i<vMatches.entries();i++)
				{
					CHMatch * pMatchAux = (CHMatch *)vMatches[i];
					if( pMatchAux->getPhaseOrder() >= phaseOrder /*pMatch->getPhaseOrder()*/ )
					{

						rebuildCSV(FILE_CSV_BRACKET,DWORD(pMatchAux));
						if( pt.getTrnId()== TRN_SET_UNPROGRESSION ||
							(pt.getTrnId() == TRN_SET_PROGRESSION && (pMatchAux->findMatchResult(pMatch->getWhiteInscription()) ||
																	  pMatchAux->findMatchResult(pMatch->getBlackInscription()))) )
						{
							rebuildCSV(FILE_CSV_COMPETITORS,DWORD(pMatchAux));							
							rebuildCSV(FILE_CSV_TOURNAMENT_HISTORY,DWORD(pMatchAux));
							courtProgressed=pMatchAux->getCourtCode();
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool CHTVGUI::preprocessTrnMedals(MSLTransaction &pt)
{
	long isA;
	bool bInsert;
	MSLPack pack;
	GData *pData=0;
	while (pt.get(isA,bInsert,pack))
	{
		pData=m_pMem->getObject(isA,pack);
		if (!pData)
			break;
	
		if( isA == __GMEDALLIST )
		{
			if( bInsert )
				updateModel(pt); // actualizo el modelo
			GMedallist * pMedallist = (GMedallist *)m_pMem->find(*pData);
			GEvent * pEvent = pMedallist ? pMedallist->getEvent():0;
			if( pEvent )
			{
				if( !bInsert )
					updateModel(pt); // actualizo el modelo
				m_tools.changedMedals(true,(CHEvent*)pEvent);
				return true;
			}
		}
	}
	return false;
}

void CHTVGUI::updateModel(MSLTransaction &pt)
{
	pt.resetPos();
	bool bInsert;
	MSLPack pack;
	long   isA;	
	GData *pData=0,*pReal=0;	
	while (pt.get(isA,bInsert,pack))
	{
		pData=m_pMem->getObject(isA,pack);
		if (!pData)
			break;

		if (bInsert)
			pReal=m_pMem->set( *pData );		
		else
			delete m_pMem->remove( *pData );		
		delete pData;
	}
}

bool CHTVGUI::validateDate(MSLDate aDate)
{
	if( !aDate.isValid() ) 
		return false;
	
	return true; // da igual el día seleccionado en el interfaz.
	//return aDate == this->getGUIDate();
}

bool CHTVGUI::validateSession(const short acc)
{
	MSLString sess = getGUISession();
	if( sess=="" )
		return true; // Si no hay session seleccionada en el interfaz, todas.
	MSLString token,rem,sAcc = TOSTRING(acc,"0");
	rem=sess;
	while (rem.tok(",",token,rem) )
	{
		if( sAcc==token )
			return true;
		if( rem=="" )
			return false;
	}
	return false;
}