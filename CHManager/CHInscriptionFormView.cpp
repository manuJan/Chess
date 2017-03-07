/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHInscriptionFormView.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Manager
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#include "stdafx.h"
#include "CHmanager.h"
#include "CHInscriptionFormView.h"
#include "CHMasterTypeDlg.h"
#include "CHFideInformationDlg.h"


#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHPoolResult.h>

#include <Sports/CH/Reports/CHRC30.h>
#include <Sports/CH/Reports/CHRC32A.h>
#include <Sports/CH/Reports/CHRC32C.h>
#include <Sports/CH/Reports/CHRC38.h>
#include <Sports/CH/Reports/CHReportDefines.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int IDFNTXBIG=1002;
const int BLUE=1003;
const int RED=1004;
const int LBLEX_SEEDS=1006;
const int TITMASTERTYPE=1007;
const int LBLMASTERTYPE=1008;
const int BUTMASTERTYPE=1009;
const int LBLEX_CALC_RATING=1010;


extern CCHManagerApp theApp;

static int CALLBACK 
orderInscByEventTree(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
   // lParamSort contains a pointer to the tree control.
   // The lParam of an item is just its handle.
	CHRegister * pReg1=(CHRegister *)CHMemoryDataBase::findRegister(lParam1);
	CHRegister * pReg2=(CHRegister *)CHMemoryDataBase::findRegister(lParam2);

	CString sInscA=_T(" ");
	CString sInscB=_T(" ");

	if(pReg1 && pReg2)
	{
		CHEvent * pEvent=(CHEvent *)lParamSort;
		int nSeed;

		CHInscription * pInsc1=(CHInscription *)CHMemoryDataBase::findInscription(pReg1,pEvent);
		if(pInsc1)
		{
			nSeed=pInsc1->getSeed();
			if (nSeed<=0)
				nSeed=99999;
			sInscA.Format(_T("%05d%05d%s"),nSeed,pInsc1->getRating(),pReg1->getPrnLName());
		}

		CHInscription * pInsc2=(CHInscription *)CHMemoryDataBase::findInscription(pReg2,pEvent);
		if(pInsc2)
		{
			nSeed=pInsc2->getSeed();
			if (nSeed<=0)
				nSeed=99999;
			sInscB.Format(_T("%05d%05d%s"),nSeed,pInsc2->getRating(),pReg2->getPrnLName());
		}
	}
	return wcsicmp(sInscA, sInscB);
}

static int orderInscByEventRating(const GVectorElement** a, const GVectorElement** b)
{
	CHInscription *pInscriptionA=(CHInscription*)(*a)->getElement();
	CHInscription *pInscriptionB=(CHInscription*)(*b)->getElement();

	CHEvent * pEventA=(CHEvent *)pInscriptionA->getEvent();
	CHEvent * pEventB=(CHEvent *)pInscriptionB->getEvent();

	if (pEventA->getKey()!=pEventB->getKey())
		return (pEventA->getOrderEvent()-pEventB->getOrderEvent());

	if (pInscriptionA->getRating()!=pInscriptionB->getRating())
	{
		if (pInscriptionA->getRating()<=0)
			return(1);

		if (pInscriptionB->getRating()<=0)
			return(-1);

		return (pInscriptionB->getRating()-pInscriptionA->getRating());
	}

	RWWString nameA=pInscriptionA->getPrnLName();
	RWWString nameB=pInscriptionB->getPrnLName();
	return wcsicmp(nameA, nameB);
}
static int orderMembersByKey(const GVectorElement** a, const GVectorElement** b)
{
	CHMember *pMemberA=(CHMember*)(*a)->getElement();
	CHMember *pMemberB=(CHMember*)(*b)->getElement();
	
	return strcmp(pMemberA->getKey(),pMemberB->getKey());
	
}

static int orderByOrderEvent(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEvA=(CHEvent *)(*a)->getElement();
	CHEvent *pEvB=(CHEvent *)(*b)->getElement();

	int rc=pEvA->getOrderEvent() - pEvB->getOrderEvent();
	return rc;
}
// SelectFunctions
RWBoolean  selectRegistersOfGroup(const RWCollectable* item,const void* param)
{
	CHRegister *pReg=(CHRegister *) item;
	CHInscription *pInsc=(CHInscription *)param;
	RWBoolean sexFilter=true;
	if (pInsc->getEventSexCode()!="2")
		sexFilter=(pReg->getSex()   == pInsc->getSex());
	return ((pReg->getFlagCompetitor())
		&&  (pReg->getType()  == GRegister::individual)
		&&  (pReg->getGroup() == pInsc->getGroup())
		&&	sexFilter);
}

IMPLEMENT_DYNCREATE(CHInscriptionFormView, CFormView)

BEGIN_MESSAGE_MAP(CHInscriptionFormView, GInscriptionFormView)
	//{{AFX_MSG_MAP(CHInscriptionsGUI)	
	ON_MESSAGE(UM_NEW_INSCRIPTION	, onNewInscription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHInscriptionFormView::CHInscriptionFormView()
:GInscriptionFormView(false/*withDataReg*/,true/*withMembers*/,false/*lockByRegister*/)
,teamCompetition(false)
{
}

CHInscriptionFormView::~CHInscriptionFormView()
{
}

GInscription * CHInscriptionFormView::getNewInscription()
{
	return new CHInscription();
}

GMember * CHInscriptionFormView::getNewMember()
{
	return new CHMember();
}

GRegister * CHInscriptionFormView::getNewRegister()
{
	return new CHRegister();
}

RWSet * CHInscriptionFormView::getIndvCandidatesMembers(GInscription * pInscription)
{
	RWSet * pColRegOfGroup=0;
	pColRegOfGroup= (RWSet*)CHMemoryDataBase::getColRegisters()
	.select(selectRegistersOfGroup,pInscription);

	RWSetIterator iter(CHMemoryDataBase::getColMember());
	CHMember * pMember=0;
	while ((pMember=(CHMember*)iter())!=0)
	{	
		if(pMember->getEvent() ==pInscription->getEvent())
			pColRegOfGroup->remove(pMember->getRegister());
	}
	return pColRegOfGroup;
}

RWBoolean CHInscriptionFormView::canCreateDeleteInscription(GEvent &aEvent, GRegister &aRegister)
{
	CHRegister * pRegister = (CHRegister*)CHMemoryDataBase::findRegister(aRegister);
	CHEvent    * pEvent    = (CHEvent*)CHMemoryDataBase::findEvent(aEvent);
	CHInscription *pInscription=(CHInscription *)CHMemoryDataBase::findInscription(pRegister,pEvent);
	if (pInscription)
	{
		RWSetIterator iter(CHMemoryDataBase::getColPoolResults());
		CHPoolResult * pPoolResult=0;
		while((pPoolResult=(CHPoolResult*)iter())!=0)
		{
			if(pPoolResult->getRegister() == &aRegister && 
			   pPoolResult->getEventCode()==aEvent.getEvent() &&
			   pPoolResult->getSex() == aEvent.getSex())
			{
				::msg("Delete Inscription","You can´t delete this inscription because is in a Match",ICO_X,MSG_OK);
				return false;
			}
		}
	}
	else
	{
		// Si Status del evento >= Running no se puede Crear.
		if ( pEvent->getStatus() >= GMemoryDataBase::eRunning ) 
			return false;
	}
	return true;
}

PFNTVCOMPARE CHInscriptionFormView::getOrderInscByTreeByEvent()
{
	return orderInscByEventTree;
}

void CHInscriptionFormView::onReportRequest(CReportItem *pItem)
{
	if (!pItem) return;
	switch (pItem->getNReport())
	{
	case RC30: // Number of Entries by NOC
		pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC((GData *)0));
		break;
	case RC32A:
		pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC((GData *)0));
		break;
	case RC32C:
		{
			CHEvent *pEvent=(CHEvent *)pItem->getLParam1();
			if (pEvent)
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pEvent));
		}
		break;
	case RC38:
	case RC38__GROUP:
		{
			pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC((GData *)0));
			GGroup *pGroup = GInscriptionFormView::getGroup();
			if(pGroup)
				pItem->addParameters(pGroup->getGroup());
		}
		break;
	}
}

bool CHInscriptionFormView::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	switch( pItem->getNReport() )
	{
	case RC30: // Number of Entries by NOC
		{
		CHRC30 aCHEntriesbyNOC(*pReportMngr,*pReportCfg);
		return aCHEntriesbyNOC.Run();
		}
		break;
	case RC32A:
		{
		CHRC32A aCHEntryListByNoc(*pReportMngr,*pReportCfg);
		return aCHEntryListByNoc.Run();
		}
		break;
	case RC32C:
		{
			CHEvent *pEvent=(CHEvent *)pItem->getLParam1();
			if(!pEvent)
			{
				::msg("Warning","Please select event to print.",ICO_X,MSG_OK);
				return false;
			}
			if (pEvent)
			{
				if (!pEvent->getInscriptions())
					return false;
				CHRC32C aCHEntryListByEvent(*pReportMngr,*pReportCfg,pEvent);
				return aCHEntryListByEvent.Run();
			}
		}
		break;
	case RC38:
	case RC38__GROUP:
		{
			GGroup *pGroup = GInscriptionFormView::getGroup();
			if (pGroup)
			{
				CHRC38 aRC38(*pReportMngr,*pReportCfg,getGroup()->getGroup());
				return aRC38.Run();
			}
			else
			{
				CHRC38 aRC38(*pReportMngr,*pReportCfg);
				return aRC38.Run();
			}
		}
		break;
	}
	return false;
}

void CHInscriptionFormView::init()
{
	GInscriptionFormView::init();
	w->hide(BUTNAMEMBER);
	w->addFont(IDFNTXBIG,6,15,0,0,1,0,_T("Tahoma"));
	w->addColorSet(BLUE,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(RED ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addBackgroundColor (2,RGB(215,230,215));
	w->changeRect(LSTEVENT,CRect(262,135,1000,293));
	//Inscriciones
	w->addGridColumn(LSTEVENT,"Rating",JUST_LEFT,75);
	w->addGridColumn(LSTEVENT,"Seed",JUST_LEFT,75);
	w->addGridColumn(LSTEVENT,"KConst",JUST_LEFT,75);
	//typo de registro
	w->createLabel(TITMASTERTYPE,CRect(265,295,355,313),"Master Type",BORDER_NONE,JUST_CENTER,w->getCurrentBck(LSTEVENT),w->getCurrentColor(LSTEVENT),w->getCurrentFont(LSTEVENT));
	w->createLabel(LBLMASTERTYPE,CRect(265,315,385,335),"",BORDER_DOWN,JUST_CENTER,2,w->getCurrentColor(LSTEVENT),w->getCurrentFont(LSTEVENT));
	w->createLabelEx(BUTMASTERTYPE,CRect(385,315,485,335),"Change...",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,IDFNTXBIG,IDBCK,RED);
	//Asignación automática de seed por world ranking
	w->createLabelEx(LBLEX_SEEDS,CRect(482,76, 782,95),"Import Data from FIDE",BORDER_NONE,JUST_LEFT	,IDBCK,BLUE,IDFNTXBIG,IDBCK,RED);
	w->createLabelEx(LBLEX_CALC_RATING,CRect(482,96, 782,115),"Calculate Seeds from Initial Rating",BORDER_NONE,JUST_LEFT	,IDBCK,BLUE,IDFNTXBIG,IDBCK,RED);
	
	areThereTeamCompetition();
	
	w->addGridColumn(LSTMEMBER,"Rating",JUST_LEFT,75);
	w->addGridColumn(LSTMEMBER,"KConst",JUST_LEFT,75);

	fillReports();
}

void CHInscriptionFormView::areThereTeamCompetition()
{
	RWSet& colEvents=CHMemoryDataBase::getColEvents();
	RWSetIterator it( colEvents );
	CHEvent* pEvent=0;

	teamCompetition=false;
	while( (pEvent=(CHEvent*)it())!=0 )
	{
		if ( pEvent->isTeam())
		{
			teamCompetition=true;
		}
	}
}

void CHInscriptionFormView::enableDisableButtons()
{
	if (teamCompetition && findTeamEvent(getSex()))
	{
		w->enable(BUTADDTEAM,true);
		w->enable(BUTMASTERTYPE,false);
		//w->chgMenuItem (MENUINSCRIP,301,false);
		//w->chgMenuItem (MENUINSCRIP,302,true);
	}
	else
	{
		w->enable(BUTADDTEAM,false);
		w->enable(BUTMASTERTYPE,true);
		//w->chgMenuItem (MENUINSCRIP,302,false);
	}
	CHRegister *pReg=(CHRegister *)getRegister();
	if (pReg && pReg->getType()==GRegister::individual)
	{//Muestro y pinto
		w->show(LBLMASTERTYPE);
		w->show(TITMASTERTYPE);
		w->show(BUTMASTERTYPE);
		if (pReg->getMasterType()==CHRegister::mNone)
		{
			w->changeColor (LBLMASTERTYPE,RED);
			w->changeTxt(LBLMASTERTYPE,"*");
		}
		else
		{
			w->changeColor (LBLMASTERTYPE,w->getCurrentColor(LSTEVENT));
			w->changeTxt(LBLMASTERTYPE,pReg->getMasterTypeAsString());
		}
	}
	else
	{//No muestro
		w->hide(LBLMASTERTYPE);
		w->hide(TITMASTERTYPE);
		w->hide(BUTMASTERTYPE);
	}
}

void CHInscriptionFormView::onSelChangedRegister(GRegister * pRegister)
{
	UNREFERENCED_PARAMETER(pRegister);
	enableDisableButtons();
}

void CHInscriptionFormView::onSelChangedEvent(GEvent * pEvent)
{
	UNREFERENCED_PARAMETER(pEvent);
	enableDisableButtons();
}

void CHInscriptionFormView::paintListEvent(GridItem *gi)
{
	if (!gi)
		return;

	CHEvent *pEvent=(CHEvent *)gi->lParam;
	if (!pEvent)
		return;
	// Buscamos la inscripcion
	CHInscription* pInscription=(CHInscription *)CHMemoryDataBase::findInscription(getRegister(),pEvent);

	switch (gi->x)
	{
		case 3://Ranking
		{
			if (!pInscription)
				return;

			char tmp[10];
			int rating=pInscription->getRating();
			if (rating)
				w->paintGridText(5,0,itoa(rating,tmp,10),JUST_LEFT);
			else w->paintGridText(10,0,"*",w->getCurrentFont(LSTEVENT),RGB(255,0,0),JUST_LEFT);
			break;
		}
		case 4://Seed
		{
			if (!pInscription)
				return;

			char tmp[10];
			int seed=pInscription->getSeed();
			if (seed)
			w->paintGridText(5,0,itoa(seed,tmp,10),JUST_LEFT);
			else w->paintGridText(10,0,"*",w->getCurrentFont(LSTEVENT),RGB(255,0,0),JUST_LEFT);
			break;
		}
		case 5://KConst
		{
			if (!pInscription)
				return;

			char tmp[10];
			int kConst=pInscription->getKConst();
			if (kConst)
			w->paintGridText(5,0,itoa(kConst,tmp,10),JUST_LEFT);
			else w->paintGridText(10,0,"*",w->getCurrentFont(LSTEVENT),RGB(255,0,0),JUST_LEFT);
			break;
		}
	}
}

void CHInscriptionFormView::paintListMember(GridItem *gi)
{
	if (!gi)
		return;

	CHMember *pMember=(CHMember *)gi->lParam;
	if (!pMember)
		return;
	
	switch (gi->x)
	{
		case 2://Ranking
		{
			if (!pMember)
				return;

			char tmp[10];
			int rating=pMember->getRating();
			if (rating)
				w->paintGridText(5,0,itoa(rating,tmp,10),JUST_LEFT);
			else w->paintGridText(10,0,"*",w->getCurrentFont(LSTMEMBER),RGB(255,0,0),JUST_LEFT);
			break;
		}
		
		case 3://KConst
		{
			if (!pMember)
				return;

			char tmp[10];
			int kConst=pMember->getKConst();
			if (kConst)
			w->paintGridText(5,0,itoa(kConst,tmp,10),JUST_LEFT);
			else w->paintGridText(10,0,"*",w->getCurrentFont(LSTMEMBER),RGB(255,0,0),JUST_LEFT);
			break;
		}
	}
}

void CHInscriptionFormView::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch (idGrid)
	{
		case LSTEVENT:
		{
			CHEvent *pEvent=(CHEvent *)lParam;
			if (!pEvent)
				return;
			// Buscamos la inscripcion
			CHInscription* pInscription=(CHInscription *)CHMemoryDataBase::findInscription(getRegister(),pEvent);
			if (!pInscription )
				return;

			switch (x)
			{
				case 3://Rating
					{
						editRating(x,y,pInscription);
						w->redrawLine(LSTEVENT,y);
					}
					break;

				case 4://Seed
					{
						editSeed(x,y,pInscription);
						w->redrawLine(LSTEVENT,y);
					}
					break;
				case 5://KConst
					{
						editKConst(x,y,pInscription);
						w->redrawLine(LSTEVENT,y);
					}
					break;
			}
		}
		break;
		case LSTMEMBER:
		{
			CHMember *pMember=(CHMember *)lParam;
			if (!pMember)
				return;
			// Buscamos el Member
			
			if (!pMember)
				return;

			switch (x)
			{
				case 2://Rating
					editRatingMember(x,y,pMember);
				break;
				
				case 3://KConst
					editKConstMember(x,y,pMember);
				break;
			}
		}
		break;
	}
}

RWBoolean CHInscriptionFormView::repeatSeed(CHInscription* pInscription, short seed)
{
	RWSet& colInscriptions=CHMemoryDataBase::getColInscriptions();
	RWSetIterator it( colInscriptions );
	CHInscription *pInscriptionAux=0;

	while( (pInscriptionAux=(CHInscription*)it())!=0 )
	{
		if ( pInscriptionAux->getEvent()==pInscription->getEvent() )
		{
			if ( pInscriptionAux->getSeed() &&
				 pInscriptionAux->getSeed()==seed )
				 return true;
		}
	}
	return false;
}

void CHInscriptionFormView::sendRegister(CHRegister *pRegister)
{
	APP::out(TRN_SET_REGISTER);
	APP::out(*pRegister,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

void CHInscriptionFormView::sendInscription(CHInscription *pInscription)
{
	CHEvent *pEvent=(CHEvent *)pInscription->getEvent();
	APP::out(TRN_SET_INSCRIPTION);
	APP::out(*pInscription,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();

	sendIDSNotify(!pEvent->isTeam()?N_REGISTER:N_TEAM,pInscription->getRegister(),N_UPDATE);
	::Sleep(300L);
}

void CHInscriptionFormView::sendMember(CHMember *pMember)
{
	APP::out(TRN_SET_MEMBER);
	APP::out(*pMember,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

void CHInscriptionFormView::editRating(int x,int y,CHInscription *pInscription)
{
	char tmp[10];
	CString aux =_T("");
	int rating=pInscription->getRating();
	if (rating)
		aux=itoa(rating,tmp,10);
	CString text = w->editGridCell(LSTEVENT,x,y,aux);
	if (text!=aux)
	{
		if( text.IsEmpty() )
			pInscription->setRating(0);
		else
			pInscription->setRating(short(_wtoi(text)));
		sendInscription(pInscription);
		w->redraw(LSTEVENT);
	}
}

void CHInscriptionFormView::editSeed(int x,int y,CHInscription *pInscription)
{
	char tmp[10];
	CString aux =_T("");
	short seed=pInscription->getSeed();
	if (seed)
		aux=itoa(seed,tmp,10);
	CString text = w->editGridCell(LSTEVENT,x,y,aux);
	if (text!=aux)
	{
		short newSeed=short(_wtoi(text));
		if( text.IsEmpty() )
		{
			pInscription->setSeed(0);
		}
		else if (!repeatSeed(pInscription,newSeed))
		{
			pInscription->setSeed(newSeed);
			sendInscription(pInscription);
			w->redraw(LSTEVENT);
			//Repintado del arbol de busqueda por evento
			updateRegisterTreeByEvent(pInscription->getRegister());
		}
		else
			::msg("Seed incorrect","The seed is repeat",ICO_W,MSG_OK);
	}
}
void CHInscriptionFormView::editKConst(int x,int y,CHInscription *pInscription)
{
	char tmp[10];
	CString aux =_T("");
	short kConst=pInscription->getKConst();
	if (kConst)
		aux=itoa(kConst,tmp,10);
	CString text = w->editGridCell(LSTEVENT,x,y,aux);
	if (text!=aux)
	{
		short newkConst=short(_wtoi(text));
		if( text.IsEmpty() )
		{
			pInscription->setKConst(0);
		}
		
		pInscription->setKConst(newkConst);
		sendInscription(pInscription);
						
	}
}
void CHInscriptionFormView::editRatingMember(int x,int y,CHMember *pMember)
{
	char tmp[10];
	CString aux =_T("");
	int rating=pMember->getRating();
	if (rating)
		aux=itoa(rating,tmp,10);
	CString text = w->editGridCell(LSTMEMBER,x,y,aux);
	if (text!=aux)
	{
		if( text.IsEmpty() )
			pMember->setRating(0);
		else
			pMember->setRating(short(_wtoi(text)));
		sendMember(pMember);
		w->redrawLine(LSTMEMBER,w->getSelectedLine(LSTMEMBER));
		
	}
}

void CHInscriptionFormView::editKConstMember(int x,int y,CHMember *pMember)
{
	char tmp[10];
	CString aux =_T("");
	short kConst=pMember->getKConst();
	if (kConst)
		aux=itoa(kConst,tmp,10);
	CString text = w->editGridCell(LSTMEMBER,x,y,aux);
	if (text!=aux)
	{
		short newkConst=short(_wtoi(text));
		if( text.IsEmpty() )
		{
			pMember->setKConst(0);
		}
		
		pMember->setKConst(newkConst);
		sendMember(pMember);
		w->redrawLine(LSTMEMBER,w->getSelectedLine(LSTMEMBER));
	}
}

void CHInscriptionFormView::setRegistrationProperties(GRegister & aRegister)
{
	CHRegister& aReg=(CHRegister&)aRegister;
	if(aReg.getType()==GRegister::individual)
	{
		short masterType=aReg.getMasterType();
		CHMasterType *pMasterType=(CHMasterType *)CHMemoryDataBase::findMasterType(masterType);
		RWCString aux=NULLRWSTRING;
		aux=pMasterType->getSDescription().toMultiByte();
		if(masterType==CHRegister::mNone)
			aux="";
		APP::addProperty("Master Type", aux,"",2);
	}
	else
		APP::delProperty("Master Type");
}

void CHInscriptionFormView::getRegistrationProperties(GRegister & aRegister)
{
	CHRegister& aReg=(CHRegister&)aRegister;
	if(aReg.getType()==GRegister::individual)
	{
		RWCString aux=NULLRWSTRING;
		aux=APP::getProperty("Master Type");
		aux.toUpper();
		if(!strcmp(aux,"GM"))
			aReg.setMasterType(CHRegister::mGMaster);
		else if(!strcmp(aux,"FM"))
			aReg.setMasterType(CHRegister::mFMaster);
		else if(!strcmp(aux,"IM"))
			aReg.setMasterType(CHRegister::mIMaster);
		else
			aReg.setMasterType(CHRegister::mNone);
	}
}

void CHInscriptionFormView::cancelRegistrationProperties(GRegister & aRegister)
{
	if(aRegister.getType()==GRegister::individual)
		APP::delProperty("Master Type");
}

void CHInscriptionFormView::setSeeedByWorldRt(GEvent *pEvent, bool reset)
{
	GSortedVector *gsvMembers=new GSortedVector(CHMemoryDataBase::getColMember(), orderMembersByKey);
	CHMember *pMemb=0;
	
	
	for (size_t i=0; i<gsvMembers->entries(); i++ )
	{
		pMemb=(CHMember *)(*gsvMembers)[i]->getElement();
			
		pMemb->setKConst(getKConst(pMemb));
		theApp.queueOut(pMemb);
	}
	theApp.out(TRN_SET_MEMBER);
	delete gsvMembers;

	w->redraw(LSTMEMBER);

	GSortedVector *gsvInscriptions=new GSortedVector(CHMemoryDataBase::getColInscriptions(), orderInscByEventRating);
	CHInscription *pInsc=0;
	GEvent *pLastEvent=0;
	CHEvent *pEv=0;
	short seed=1;
	short inscSeed=0;
	for ( i=0; i<gsvInscriptions->entries(); i++ )
	{
		bool changeSeed=false;
		pInsc=(CHInscription *)(*gsvInscriptions)[i]->getElement();
		pEv=(CHEvent *)pInsc->getEvent();

		if (pEvent && pEvent->getKey()!=pEv->getKey())
			continue;

		if (!pLastEvent || pLastEvent->getKey()!=pEv->getKey())
		{
			seed=1;
			pLastEvent=pEv;
		}
		inscSeed=pInsc->getSeed();
		if (reset)
		{
			if (inscSeed!=0)
			{
				changeSeed=true;
				pInsc->setSeed(0);
			}
		}
		else if (inscSeed!=seed)
		{
			changeSeed=true;
			pInsc->setSeed(seed);
		}
		
		pInsc->setKConst(getKConst(pInsc));
		// Le pongo el rating de los miembros
		if(pEv->isTeam())
			pInsc->setRating(getTeamRating(pInsc));

		if (changeSeed)
		{
			theApp.queueOut(pInsc);
			updateRegisterTreeByEvent(pInsc->getRegister());
		}
		seed++;
	}
	theApp.out(TRN_SET_INSCRIPTION);
	delete gsvInscriptions;


	w->redraw(LSTEVENT);
}

RWBoolean CHInscriptionFormView::findTeamEvent(GSex *pSex)
{
	if (!pSex)
		return false;
	RWSet& colEvents=CHMemoryDataBase::getColEvents();
	RWSetIterator it(colEvents);
	CHEvent* pEvent=0;
	while((pEvent=(CHEvent*)it())!=0)
	{
		if (pEvent->isTeam() && pEvent->getSex()==pSex->getSex())
			return true;
	}
	return false;
}

void CHInscriptionFormView::onClick(UINT idCtrl,LPARAM lParam)
{
	switch (idCtrl)
	{
	case LBLEX_SEEDS:
		{
			CHFideInformationDlg *pFideInfDlg=new CHFideInformationDlg((CHMemoryDataBase*)mem(),this);
			pFideInfDlg->DoModal();
			break;
		}
	case LBLEX_CALC_RATING:
		{
			int doIt=RET_NO;
			doIt=::msg("Warning","With this operation could be erased seeds assigned manual, continue?",ICO_W,MSG_YESNO);
			if (doIt==RET_NO)
				break;

			setSeeedByWorldRt(0,false);
			break;
		}
	case BUTMASTERTYPE:
		{//pulso el cambio de tipo de registro
			CHRegister *pRegister=(CHRegister *)getRegister();
			if (pRegister)
			{
				if (pRegister->getType()  != GRegister::individual)
					break;
				CHMasterTypeDlg *pDlg=new CHMasterTypeDlg((CHMemoryDataBase*)mem(),pRegister,this);
				int ok=pDlg->DoModal();
				CHMasterType *pMastType=pDlg->getMasterType();
				if (pMastType)
				{
					if(pRegister->getMasterType()!=pMastType->getMasterType() && ok==IDOK)
					{
						pRegister->setMasterType(pMastType->getMasterType());
						sendRegister(pRegister);
					}
				}
				if (pDlg) delete pDlg;
			}
		}
		break;
	default:
			GInscriptionFormView::onClick(idCtrl,lParam);

		break;
	}
	enableDisableButtons();
}

RWWString CHInscriptionFormView::getRegisterName(GInscription * pInsc)
{
	CHInscription * pInscription =(CHInscription*)pInsc;
	RWWString txt = GInscriptionFormView::getRegisterName(pInsc);
	CString seed;
	int nSeed=pInscription->getSeed();
	if(nSeed>0)
	{
		if (nSeed<=pInscription->getSeed())
			seed.Format(_T("%d )  %s"),nSeed, txt);
		else
			seed.Format(_T("%s (%d)"),txt,nSeed);
		return RWWString(seed);
	}
	return txt;
}

void CHInscriptionFormView::fillReports()
{
	int index=0, currentParent=0, parent32C=0;
	APP::addReport(++index,currentParent,RC30_NAME,RC30,CH_INSCRIPTION_FORMVIEW,0,0);
	APP::addReport(++index,currentParent,RC32A_NAME,RC32A,CH_INSCRIPTION_FORMVIEW,0,0);

	APP::addReport(++index,currentParent,RC32C_NAME,RC32C,CH_INSCRIPTION_FORMVIEW,0,0);
	GSortedVector pVEvents = GSortedVector(mem()->getColEvents(),orderByOrderEvent);
	CHEvent *pEvent=0;
	parent32C=index;
	for (size_t i=0; i<pVEvents.entries(); i++)
	{
		pEvent = (CHEvent*) (pVEvents)[i]->getElement();
		CString description=CString(pEvent->getLDescription());
		APP::addReport(++parent32C,index,description,RC32C,CH_INSCRIPTION_FORMVIEW,LPARAM(pEvent),0);
	}
	pVEvents.clearAndDestroy();
	index=parent32C;
	APP::addReport(++index,currentParent,RC38__NAME,RC38,CH_INSCRIPTION_FORMVIEW,0,0);
}
LRESULT CHInscriptionFormView::onNewInscription(WPARAM wParam, LPARAM lParam)
{
	// Al crearse una nueva inscripción tenemos que crear su 
	CHInscription* pNewInscription=(CHInscription*)lParam;
	if (pNewInscription)
	{
		CHEventResult aResult(pNewInscription);
		CHEventResult* pResult=(CHEventResult*)((CHMemoryDataBase*)mem())->setEventResult(aResult);
		if (pResult)
		{
			APP::out(TRN_SET_EVENT_RESULT);
			APP::out(*pResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
			APP::out();
		}
	}

	return true;
	UNREFERENCED_PARAMETER(wParam);
}
short CHInscriptionFormView::getKConst(CHInscription *pInsc)
{
	// KConst = 25, si no ha jugado 30 partidas en su vida
	// KConst = 15, si su rating es menor de 2400
	// KConst = 10, si su rating es mayor de 2400
	short kConst=25;
	if(!pInsc)
		return 0;

	if(pInsc->getRating())
	{
		if(pInsc->getRating()>2400)
			return 10;
		else 
			return 15;
	}

	return kConst;
}
short CHInscriptionFormView::getKConst(CHMember *pMemb)
{
	// KConst = 25, si no ha jugado 30 partidas en su vida
	// KConst = 15, si su rating es menor de 2400
	// KConst = 10, si su rating es mayor de 2400
	short kConst=25;
	if(!pMemb)
		return 0;

	if(pMemb->getRating())
	{
		if(pMemb->getRating()>2400)
			return 10;
		else 
			return 15;
	}

	return kConst;
}
short CHInscriptionFormView::getTeamRating(CHInscription *pIns)
{
	CHMember *pMember=0;
	short teamRating=0;
	for(size_t i=0;i<pIns->getMembersVector().entries();i++)
	{
		pMember=(CHMember*)pIns->getMembersVector()[i]->getElement();
		teamRating+=pMember->getRating();

	}
	if(pIns->getMembersVector().entries())
		teamRating/=short(pIns->getMembersVector().entries());

	return teamRating;
}
RWBoolean CHInscriptionFormView::canAssignMembers(GEvent & aEvent)
{
	return (aEvent.getStatus() != GMemoryDataBase::eFinished);
}