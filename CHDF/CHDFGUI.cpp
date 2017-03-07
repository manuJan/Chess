/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDFGUI.h
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHDFGUI.h"
#include "CHDFProcessExt.h"
#include <GUI/DF/DFTopic.h>
#include <GUI/DF/DFEvent.h>
#include <Core/G/GClassIds.h>
#include <Core/G/GMsgDefines.h>

#include <Sports\CH\Data\CHClassIds.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDFGUI dialog

CHDFGUI::CHDFGUI()
:DFGUI()
{
	//{{AFX_DATA_INIT(CHDFGUI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}


BEGIN_MESSAGE_MAP(CHDFGUI, DFGUI)
	//{{AFX_MSG_MAP(CHDFGUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


DFProcessExt * CHDFGUI::getNewDFProcessExt()
{
	return new CHDFProcessExt(this);
}

/////////////////////////////////////////////////////////////////////////////
// CHDFGUI message handlers
BOOL CHDFGUI::OnInitDialog()
{
	return DFGUI::OnInitDialog();
}

void CHDFGUI::callForCreateTopics()
{
	//DFTopic(Idd,Description,isA,type("static/Dinamic/Event"),has descriptions)

		
	addTopic(DFTopic(10,"Events"			  ,__CHEVENT            ,"3", N_DISTRIBUTION_REPORT						));
	addTopic(DFTopic(11,"Registers"			  ,__CHREGISTER         ,"2", 0, true									));
	addTopic(DFTopic(12,"Inscriptions"		  ,__CHINSCRIPTION      ,"2", 0											));
	addTopic(DFTopic(13,"Members"			  ,__CHMEMBER	        ,"2", 0											));
	addTopic(DFTopic(14,"Judges"			  ,__CHJUDGE	        ,"2", 0											));
	addTopic(DFTopic(15,"Phases"			  ,__CHPHASE	        ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(16,"Results"			  ,__CHEVENTRESULT      ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));

	addTopic(DFTopic(17,"Pool"                ,__CHPOOL             ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(18,"Pool Results"        ,__CHPOOLRESULT       ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(19,"Matches"			  ,__CHMATCH		    ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(20,"Match Results"		  ,__CHMATCHRESULT		,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(21,"Match Judges"		  ,__CHMATCHJUDGE		,"3", N_DISTRIBUTION_REPORT						));
	addTopic(DFTopic(22,"Match Game"		  ,__CHSPLITMATCH       ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(23,"Split Match Results" ,__CHSPLITMATCHRESULT ,"3", N_DISTRIBUTION_REPORT|N_STATUS			));
	addTopic(DFTopic(24,"Sessions"			  ,__CHSESSION			,"2", 0											));
	addTopic(DFTopic(25,"Match Members"		  ,__CHMATCHMEMBER		,"3", N_DISTRIBUTION_REPORT						));
	

	addTopic(DFTopic(26,"Courts"			  ,__CHCOURT			,"2", 0											));
	addTopic(DFTopic(27,"MasterType"		  ,__CHMASTERTYPE		,"2", 0											));
	addTopic(DFTopic(28,"RatingDif"			  ,__CHRATINGDIF		,"2", 0											));
	//addTopic(DFTopic(29,"TeamMatchCnfg"		  ,__CHTEAMMATCHSCNFG	,"2", 0											));
	
	
	addTopic(DFTopic(30,"Medallist"           ,__GMEDALLIST         ,"3", N_DISTRIBUTION_REPORT|N_MEDALS			));

	//Notificaciones
	addTopic(DFTopic(100,"Notifications"	  ,__GNOTIFY			,"2", N_STATUS|N_MEDALS|N_DISTRIBUTION_REPORT	));
}

void CHDFGUI::callForCreateNotifies()
{
	addNotify(DFEvent(N_STATUS,"Status"));			//2
	addNotify(DFEvent(N_MEDALS,"Medals"));			//4
	addNotify(DFEvent(N_DISTRIBUTION_REPORT,"Generate Reports"));	//16
}

void CHDFGUI::callForCreateItemsDescription(const int idTopic,const RWBoolean isDesc/*=false*/)
{
	UNREFERENCED_PARAMETER(isDesc);

	//C		- char
	//VC	- varchar
	//UC	- unsigned char (o boolean)
	//S		- short
	//I		- int

	GBuffer aBuffer;

	//For example:
	//if( idTopic==10 )		//Event
	//	fillItemEvent(aBuffer);
		
	switch (idTopic)
	{
	
	case 10:
		fillItemEvent(aBuffer);
		break;
	case 11:
		fillItemRegister(aBuffer);
		break;
	case 12:
		fillItemInscription(aBuffer);
		break;
	case 13:
		fillItemMember(aBuffer);
		break;
	case 14:
		fillItemJudge(aBuffer);
		break;
	case 15:
		fillItemPhase(aBuffer);
		break;
	case 16:
		fillItemEventResult(aBuffer);
		break;	
	case 17:
		fillItemPool(aBuffer);
		break;
	case 18:
		fillItemPoolResult(aBuffer);
		break;
	case 19:
		fillItemMatch(aBuffer);
		break;
	case 20:
		fillMatchResult(aBuffer);
		break;
	case 21:
		fillMatchJudge(aBuffer);
		break;
	case 22:
		fillItemSplitMatch(aBuffer);
		break;
	case 23:
		fillSplitMatchResult(aBuffer);
		break;
	case 24:
		fillItemSession(aBuffer);
		break;
	case 25:
		fillMatchMember(aBuffer);
		break;
	case 26:
		fillCourt(aBuffer);
		break;
	case 27:
		fillMasterType(aBuffer);
		break;
	case 28:
		fillRatingDif(aBuffer);
		break;
	/*case 29:
		fillTeamMatchCnfg(aBuffer);
		break;*/
	case 30:
		fillMedallist(aBuffer);
		break;
	}
	RWCString buffer(aBuffer);
	if( buffer!="" )
		addDescTopic(idTopic,buffer,true);
}

void CHDFGUI::fillItemRegister(GBuffer &aBuffer)
{
	aBuffer	<< "REGISTER->Key (VC[10])"

			<< "Register (VC[10])"
			<< "TypeRegister (UC)"
			<< "Sex (C[1])"
			<< "Group (C[3])"
			<< "DateOfBirth (C[10])"
			<< "Weight (VC[12])"
			<< "Height (VC[12])"
			<< "Category (C[1])"
			<< "Acreditation (VC[15])"
			<< "IsoCountry (C[3])"
			<< "IFNumber (VC[16])"
			<< "Competitor (UC)"
			<< "Record (UC)"
			<< "Top (UC)"
			<< "Bib (VC[4])"
			<< "UseHand (S)"
			<< "Grip (VC[15])"
			<< "MedicalClass (VC[15])"

			<< "NAMES->Key (VC[13])"
			<< "Register (VC[10])"
			<< "Language (C[3])"
			<< "SurName (VC[35])"
			<< "Name (VC[25])"
			<< "PrnLName (VC[35])"
			<< "PrnSName (VC[20])"
			<< "ScbLName (VC[20])"
			<< "ScbSName (VC[20])"
			<< "TvLName (VC[35])"
			<< "TvSName (VC[35])"
			<< endLine;
}

void CHDFGUI::fillItemEvent(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[4])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Status (UC)"
			<< "StartTime (C[8])"
			<< "EndTime (C[8])"
			<< "StartDate (C[10])"
			<< "EndDate (C[10])"
			<< "medicalClass (VC[25])"
			<< "typeEvent (S)"
			<< "orderEvent (S)"
			<< "twoBronces (S)"
			<< "nSets (S)"
			<< "reqRankOrder (VC[25])"
			<< "medalDate (C[8])"
			<< "medalTime (VC[5])"
			<< endLine;
}

void CHDFGUI::fillItemPhase(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[5])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Status (UC)"
			<< "StartTime (C[8])"
			<< "EndTime (C[8])"
			<< "StartDate (C[10])"
			<< "EndDate (C[10])"
			<< "PoolsNumber (S)"
			<< "SplitsNumber (S)"
			<< "IsPool (UC)"

			<< "OrderExecution (S)"
			<< "TypePhase (S)"
			<< "TypeTie (S)"
			<< "TypeMatchWinner (S)"
			<< endLine;
}
void CHDFGUI::fillItemEventResult(GBuffer & aBuffer)
{
	aBuffer	<< "Key (VC[14])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Register (C[10])"
			<< "EventRank (S)"
			<< "EventRankPo (S)"
			<< "Qualitative (C[1])"
			<< endLine;
}
void CHDFGUI::fillItemSession(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[11])"
			<< "DateSession (C[10])"	
			<< "idSession (C[1])"
			<< "NumSession (S)"
			<< "TimeSession (C[8])"
			<< "SessionDescription (VC[25])"
			<< "SessionAccumulated (S)"
			<< endLine;
}

void CHDFGUI::fillItemInscription(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[14])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Reg (C[10])"
			<< "Seed (S)"
			<< "SubstituteReg (I)"
			<< endLine;
}

void CHDFGUI::fillItemJudge(GBuffer & aBuffer)
{
	aBuffer	<< "Key (VC[13])"
			<< "Register (C[10])"
			<< "FunctionJudge (C[3])"
			<< endLine;
}


void CHDFGUI::fillItemMember(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[24])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "RegTeam (C[10])"
			<< "RegMember (C[10])"
			<< "Function (S)"
			<< endLine;
}

void CHDFGUI::fillItemPool(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[7])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Order (S)"
			<< "NumCompetitors (S)"
			<< "NumRounds (S)"
			<< "NumMatches (S)"
			<< "Status (UC)"
			<< "StartDate (C[10])"
			<< "StartTime (C[8])"
			<< "EndDate (C[10])"
			<< "EndTime  (C[8])"
			<< endLine;
}

void CHDFGUI::fillItemPoolResult(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[10])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Order (C[3])"
			<< "Reg (I)"
			<< "QCode (C[1])"
			<< "PoolRank (S)"
			<< "PoolRankPo (S)"
			<< "PhaseRank (S)"
			<< "PhaseRankPo (S)"
			<< "Points (S)"
			<< "PhaseSource (S)"
			<< "PoolSource (S)"
			<< "RankingSource (S)"
			<< "IsBye (UC)"
			<< "PhaseLuckyLoser (S)"
			<< "IsBest (UC)"
			<< "PositionSource (S)"
			<< endLine;
}

void CHDFGUI::fillItemMatch(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[12])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Status (UC)"
			<< "MatchNumber (VC[2])"
			<< "StartTime (C[8])"
			<< "StartDate (C[10])"
			<< "EndTime (C[8])"
			<< "EndDate  (C[10])"
			<< "NumCompetitors (S)"
			<< "NumSession (VC[2])"
			<< "Venue (VC[3])"
			<< "Court (S)"
			<< "Rink (S)"
			<< "StatusMatch (S)"
			<< endLine;
}

void CHDFGUI::fillItemSplitMatch(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[14])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Split (C[2])"
			<< "Status (UC)"
			<< "NEnds (S)"
			<< "TypeSplit (S)"
			<< endLine;
}

void CHDFGUI::fillMatchMember(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[17])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Position (C[3])"
			<< "MatchMember (C[2])"
			<< "RegTeam (I)"
			<< "RegMember (I)"
			<< "Active (UC)"
			<< "Function (S)"
			<< endLine;
}

void CHDFGUI::fillMatchJudge(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[22])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Reg (C[10])"
			<< "Function (S)"
			<< "PositionJudge (S)"
			<< endLine;
}

void CHDFGUI::fillMatchResult(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[15])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Position (C[3])"
			<< "Reg (I)"
			<< "QCode (C[1])"
			<< "Ranking (S)"
			<< "RankingPosition (S)"
			<< "CodeUniform (VC[50])"
			<< "PoolPosition (S)"
			<< "isBye (UC)"
			<< "Points (S)"
			<< "Ends (S)"
			<< "Sets (S)"
			<< "SetQCode (S)"
			<< endLine;
}

void CHDFGUI::fillSplitMatchResult(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[17])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Phase (C[1])"
			<< "Pool (C[2])"
			<< "Code (C[5])"
			<< "Position (C[3])"
			<< "Split (C[2])"
			<< "ShotsFor (S)"
			<< "ShotsAgainst (S)"
			<< "NEnds (S)"
			<< endLine;
}

void CHDFGUI::fillCourt(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[6])"
			<< "CodeVenue (C[3])"
			<< "Court (C[3])"
			<< "Order (S)"
			<< endLine;
}
void CHDFGUI::fillMasterType(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[3])"
			<< "MasterType (C[3])"
			<< "Order (S)"
			<< endLine;
}
void CHDFGUI::fillRatingDif(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[3])"
			<< "Code_Rat (C[3])"
			<< "Probability (S)"
			<< "Difference (S)"
			<< endLine;
}
void CHDFGUI::fillTeamMatchCnfg(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[3])"
			<< "Code_Rat (C[3])"
			<< "NCompetitors (S)"
			<< "NMatches (S)"
			<< "NMatchesType (C[40])"
			<< "CompMatChesDistribution (C[60])"
			<< endLine;
}

void CHDFGUI::fillMedallist(GBuffer &aBuffer)
{
	aBuffer	<< "Key (VC[15])"
			<< "Sex (C[1])"
			<< "Event (C[3])"
			<< "Medal (UC)"
			<< "Reg (C[10])"
			<< "Date (C[10])"
			<< "Mark (VC[12])"
			<< endLine;
}
