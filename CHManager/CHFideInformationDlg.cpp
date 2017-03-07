/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHFideInformationDlg.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 12-01-2006
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "chmanager.h"
#include "CHFideInformationDlg.h"
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>
#include <SPORTS/CH/DATA/CHRegister.h>
#include "CHReadFile.h"
#include "CHDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDBBKCLEAR				1701
#define IDBBKBLUE				1702
#define IDBBKBROWN				1703
#define BUCH_BACK				1704
#define BUCH_CANCEL				1705
#define LBL_VALUE				1706
#define ED_VALUE				1707
#define RED						1708
#define BLUE					1709
#define IDBBKYELLOW				1710
#define LBL_CARTEL_NAME			1711
#define FONTDLBG				1712
#define GRID_FIDE_INFOR			1713
#define BUCH_ADD				1714
#define BUCH_DEL				1715
#define FONTDLG					1716
#define BMP_BACK				1718
#define LBL_FIDE_INFOR			1719
#define LBL_LINEA_FIDE			1720
#define GRID_INSCRIPTIONS		1721
#define LBL_REGISTERS			1722
#define LBL_LINEA_REG			1723
#define BMP_SEND_FIDE			1724
#define BUCH_FIDE				1725
#define GRID_MEMBERS			1726


#define CR			char(0x0D)
#define LF			char(0x0A)

static
int orderMasterTypeByCode(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHFideElement *pFideElementA = (CHFideElement *)lParam1;
	CHFideElement *pFideElementB = (CHFideElement *)lParam2;
	
	return pFideElementA->getIdNumber() - pFideElementB->getIdNumber();
	
}
static
int orderMasterTypeByName(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHFideElement *pFideElementA = (CHFideElement *)lParam1;
	CHFideElement *pFideElementB = (CHFideElement *)lParam2;
	
	int order =stricmp(pFideElementA->getName(), pFideElementB->getName());
	if(order)
		return order;

	return pFideElementA->getIdNumber() - pFideElementB->getIdNumber();
}

static
int orderMasterTypeByRating(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHFideElement *pFideElementA = (CHFideElement *)lParam1;
	CHFideElement *pFideElementB = (CHFideElement *)lParam2;
	
	int order =pFideElementB->getRating() - pFideElementA->getRating();
	if(order)
		return order;

	return pFideElementA->getIdNumber() - pFideElementB->getIdNumber();
}
static
int orderInscripIDNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHInscription *pInscripA = (CHInscription *)lParam1;
	CHInscription *pInscripB = (CHInscription *)lParam2;
	
	int order = atoi(pInscripA->getAcreditation()) - atoi(pInscripB->getAcreditation());
	if(order)
		return order;
	
	return strcmp(pInscripA->getKey(),pInscripB->getKey());
}
static
int orderInscripEventNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHInscription *pInscripA = (CHInscription *)lParam1;
	CHInscription *pInscripB = (CHInscription *)lParam2;
	
	int order =strcmp(pInscripA->getEventKey(),pInscripB->getEventKey());
	if(order)
		return order;

	order =pInscripB->getRating() - pInscripB->getRating();
	if(order)
		return order;

	order = atoi(pInscripA->getAcreditation()) - atoi(pInscripB->getAcreditation());
	if(order)
		return order;
	
	return strcmp(pInscripA->getKey(),pInscripB->getKey());
}

static
int orderInscripName(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHInscription *pInscripA = (CHInscription *)lParam1;
	CHInscription *pInscripB = (CHInscription *)lParam2;
	
	int order =wcsicmp(pInscripA->getPrnLName(),pInscripB->getPrnLName());
	if(order)
		return order;

	return strcmp(pInscripA->getKey(),pInscripB->getKey());
}
static
int orderInscripRatingNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHInscription *pInscripA = (CHInscription *)lParam1;
	CHInscription *pInscripB = (CHInscription *)lParam2;
	
	int order =pInscripB->getRating() - pInscripA->getRating();
	if(order)
		return order;

	return strcmp(pInscripA->getKey(),pInscripB->getKey());
}
static
int orderInscripEventSeed(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHInscription *pInscripA = (CHInscription *)lParam1;
	CHInscription *pInscripB = (CHInscription *)lParam2;
	
	int order =strcmp(pInscripA->getEventKey(),pInscripB->getEventKey());
	if(order)
		return order;

	return pInscripA->getSeed() - pInscripB->getSeed();
	
}

static
int orderMemberIDNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHMember *pMemberA = (CHMember *)lParam1;
	CHMember *pMemberB = (CHMember *)lParam2;
	
	int order = atoi(pMemberA->getAcreditation()) - atoi(pMemberB->getAcreditation());
	if(order)
		return order;
	
	return strcmp(pMemberA->getKey(),pMemberB->getKey());
}
static
int orderMemberName(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHMember *pMemberA = (CHMember *)lParam1;
	CHMember *pMemberB = (CHMember *)lParam2;
	
	int order =wcsicmp(pMemberA->getPrnLName(),pMemberB->getPrnLName());
	if(order)
		return order;

	return strcmp(pMemberA->getKey(),pMemberB->getKey());
}
static
int orderMemberEventNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHMember *pMemberA = (CHMember *)lParam1;
	CHMember *pMemberB = (CHMember *)lParam2;
	
	CHEvent *pEventA = pMemberA->getEvent();
	CHEvent *pEventB = pMemberB->getEvent();

		
	int order =pMemberB->getRating() - pMemberA->getRating();
	if(order)
		return order;

	order = atoi(pMemberA->getAcreditation()) - atoi(pMemberB->getAcreditation());
	if(order)
		return order;
	
	return strcmp(pMemberA->getKey(),pMemberB->getKey());
}
static
int orderMemberRatingNumber(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	UNREFERENCED_PARAMETER(lSortParam);
	CHMember *pMemberA = (CHMember *)lParam1;
	CHMember *pMemberB = (CHMember *)lParam2;
	
	int order =pMemberB->getRating() - pMemberA->getRating();
	if(order)
		return order;

	return strcmp(pMemberA->getKey(),pMemberB->getKey());
}
/////////////////////////////////////////////////////////////////////////////
// CHFideInformationDlg dialog

extern CCHManagerApp theApp;
CHFideInformationDlg::CHFideInformationDlg(CHMemoryDataBase* pMem,CWnd* pParent /*=NULL*/)
:CDialog(CHFideInformationDlg::IDD, pParent)
,pMemory(pMem)
,w(0)
,hasErrors(false)
,insMember(true)
{
	//{{AFX_DATA_INIT(CHFideInformationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CHFideInformationDlg::~CHFideInformationDlg()
{
	vFideInformations.clearAndDestroy();
}

void CHFideInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHFideInformationDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHFideInformationDlg, CDialog)
	//{{AFX_MSG_MAP(CHFideInformationDlg)
		ON_MESSAGE(UM_CLICK, onClick)
		ON_MESSAGE(UM_DBLCLICK, onDblClick)
		ON_MESSAGE(UM_PAINTGRID, onPaintGrid)	
		ON_WM_SIZE()
		ON_WM_CLOSE()
		ON_MESSAGE(UM_CLICKHEADER, onClickHeader)
		ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHFideInformationDlg message handlers

BOOL CHFideInformationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	w=new CGraphicWnd(this);

	if (!w)
		return FALSE;
	INITW(w);
	
	SetWindowPos(0,0,105,1024,650,0);
	
	w->addBitmapT(BMP_BACK,IDB_BMP_BACK);
	w->addBitmapT(BMP_SEND_FIDE,IDB_SEND_FIDE);
	
	//w->addBackgroundColor(IDBBKCLEAR,RGB(240,240,250));
	w->addBackgroundColor(IDBBKBLUE ,RGB(194,206,245));
	w->addBackgroundColor(IDBBKBROWN,RGB(239,220,189));
	w->addBackgroundColor(IDBBKYELLOW,RGB(255,255,207));
	w->setBackground (IDBBKCLEAR);	
	w->addFont (FONTDLG,6,14,1,0,0,0,_T("Arial"));
	w->addFont (FONTDLBG,8,16,1,0,0,0,_T("Arial"));
	w->addColorSet(RED   ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(BLUE  ,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	
	CString cartel=_T("");
	
	w->createLabel(LBL_CARTEL_NAME,CRect(5,5,465,25),cartel,BORDER_SINGLE,JUST_LEFT,IDBBKCLEAR,0,FONTDLG);
	paintCartel();
	
	// Label de Cabecera
	w->createLabel (LBL_FIDE_INFOR,    CRect(15,15,575,35),"FIDE Information",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BIG);
	w->createLabel (LBL_LINEA_FIDE,    CRect(15,35,575,39),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);

	w->createGrid(GRID_FIDE_INFOR,CRect(15,40,575,540),BORDER_3DDOWN,20,IDBCK_GRID,0,FONTDLG, TRUE, 15);
	w->addGridColumn(GRID_FIDE_INFOR,"ID Number", JUST_LEFT  , 70);
	w->addGridColumn(GRID_FIDE_INFOR,"Name", JUST_LEFT  ,220);
	w->addGridColumn(GRID_FIDE_INFOR,"Title", JUST_LEFT  ,40);
	w->addGridColumn(GRID_FIDE_INFOR,"Federation", JUST_LEFT  ,70);
	w->addGridColumn(GRID_FIDE_INFOR,"Rating", JUST_LEFT  ,40);
	w->addGridColumn(GRID_FIDE_INFOR,"Games", JUST_LEFT  ,40);
	w->addGridColumn(GRID_FIDE_INFOR,"Born", JUST_LEFT  ,40);
	w->addGridColumn(GRID_FIDE_INFOR,"Flag", JUST_LEFT  ,40);
	w->gridLineColor(GRID_FIDE_INFOR,RGB(207,207,207),RGB(207,207,207));
	w->multipleSelection(GRID_FIDE_INFOR,true);
	fillFideInformation();

	// Label de Cabecera
	w->createLabelEx (LBL_REGISTERS,    CRect(595,15,1000,35),"",BORDER_NONE,JUST_LEFT,IDBCK,BLUE,IDFNT_BIG,IDBCK,RED,IDFNT_BIG);
	w->createLabel (LBL_LINEA_REG,    CRect(595,35,1000,39),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	w->createGrid(GRID_INSCRIPTIONS,CRect(595,40,1000,540),BORDER_3DDOWN,20,IDBCK_GRID,0,FONTDLG, TRUE, 15);
	w->gridLineColor(GRID_INSCRIPTIONS,RGB(207,207,207),RGB(207,207,207));
	w->addGridColumn(GRID_INSCRIPTIONS,"ID Number", JUST_LEFT  ,70);
	w->addGridColumn(GRID_INSCRIPTIONS,"Name", JUST_LEFT  , 150);
	w->addGridColumn(GRID_INSCRIPTIONS,"Event", JUST_LEFT  ,105);
	w->addGridColumn(GRID_INSCRIPTIONS,"Rating", JUST_LEFT  ,40);
	w->addGridColumn(GRID_INSCRIPTIONS,"Seed", JUST_LEFT  ,40);
	fillInscriptions();

		
	w->createGrid(GRID_MEMBERS,CRect(595,40,1000,540),BORDER_3DDOWN,20,IDBCK_GRID,0,FONTDLG, TRUE, 15);
	w->gridLineColor(GRID_MEMBERS,RGB(207,207,207),RGB(207,207,207));
	w->addGridColumn(GRID_MEMBERS,"ID Number", JUST_LEFT  ,70);
	w->addGridColumn(GRID_MEMBERS,"Name", JUST_LEFT  , 150);
	w->addGridColumn(GRID_MEMBERS,"Event", JUST_LEFT  ,105);
	w->addGridColumn(GRID_MEMBERS,"Rating", JUST_LEFT  ,40);
	fillMembers();

	paintInsMember();
	
	// BUCHON ADD MasterType
	//w->createButton (BUCH_ADD,CRect( 395, 120,495, 140),"Add MasterType.",IDBBKBROWN,0,FONTDLG);
	// BUCHON SUB MasterType
	//w->createButton (BUCH_DEL,CRect( 395, 150,495, 170),"Del MasterType.",IDBBKBROWN,0,FONTDLG);
	// BUCHON OK / CANCEL
	
	w->createButton (BUCH_BACK,CRect( 875, 580,975, 610),"Back",IDBCK_BUT,0,FONTDLBG);
	w->changeBmp(BUCH_BACK,BMP_BACK);
	w->setToolTip(BUCH_BACK ,"Back to the previous screen");

	w->createButton (BUCH_FIDE,CRect( 20, 580,140, 610),"FIDE FILE",IDBCK_BUT,0,FONTDLBG);
	w->changeBmp(BUCH_FIDE,BMP_SEND_FIDE);
	w->setToolTip(BUCH_FIDE ,"Save Ratings from FIDE File");
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHFideInformationDlg::paintCartel()
{
	CHMasterType* pMasterType=0; 
	RWWString aux=_T("FIDE Information");
	int selLine=w->getSelectedLine(GRID_FIDE_INFOR);
	

	w->changeTxt(LBL_CARTEL_NAME,aux);
	w->redraw(LBL_CARTEL_NAME,true);
}

void CHFideInformationDlg::fillFideInformation()
{
	w->gridDeleteAllItems(GRID_FIDE_INFOR);
	

	CString defExt(_T("*.txt\0"));
	static TCHAR BASED_CODE szFilter[] = _T("Result files (*.txt)|*.txt|Application extension (*.txt)|*.txt|All Files (*.*)|*.*||"); 
	CFileDialog fdlg(TRUE, defExt, NULL,
					 OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,
					 szFilter, AfxGetMainWnd());	
	RWCString resultFile=NULLRWSTRING;
	RWCString resultPath=NULLRWSTRING;
	CHFideElement *pFideElement=0;
	if (fdlg.DoModal()==IDOK)
	{
		
		

		resultPath=RWWString(fdlg.GetPathName()).toAscii();

		m_logFile.initLog("fielog.log"); // --w
		
		RWCString buffer = "Initilializing File..." + resultPath;
		buffer+=CR;
		buffer+=LF;
		m_logFile.write(buffer.data(),buffer.length());

		RWCString line;
		CHReadFile aReadFile(resultPath);	
		if (!aReadFile.getValidFile())
		{
			AfxMessageBox(_T("Invalid File\n"));
			return;
		}
		
		int cont = 0;
				

		BeginWaitCursor();
		while( aReadFile.getLine(line) )
		{
			// La primera linea es la cabecera y no la queremos
			if(!cont)
			{	
				cont ++;
				continue;
			}
			pFideElement = new CHFideElement();
			if(processIn(line,pFideElement))
				vFideInformations.insert(pFideElement);
			else
				delete pFideElement;
			cont ++;
		}

		
		RWCString buffer2 = "End File..." + resultPath;
		buffer2 += CR;
		buffer2 += LF;
		buffer2 += "-----------------------------------";
		buffer2 += CR;
		buffer2 += LF;
		m_logFile.write(buffer2.data(),buffer2.length());
		EndWaitCursor();

		if(hasErrors)
			::msg("Warning","Check File fielog.log to see posible errors",ICO_X,MSG_OK);
		else ::msg("FIDE Information","File Loaded Successfully",ICO_I,MSG_OK);
		
	}
	
	for(size_t i=0;i<vFideInformations.entries();i++)
	{
		pFideElement=(CHFideElement*)vFideInformations[i]->getElement(); 
		w->addGridLine(GRID_FIDE_INFOR,LPARAM(pFideElement),"");
	}
	
	w->gridSort(GRID_FIDE_INFOR,orderMasterTypeByCode);
	
}		

void CHFideInformationDlg::fillInscriptions()
{
	w->gridDeleteAllItems(GRID_INSCRIPTIONS);
	RWSet& colInscriptions=CHMemoryDataBase::getColInscriptions();
	RWSetIterator it( colInscriptions );
	CHInscription *pInscriptionAux=0;

	while( (pInscriptionAux=(CHInscription*)it())!=0 )
	{
		w->addGridLine(GRID_INSCRIPTIONS,LPARAM(pInscriptionAux),"");
	}
	
	w->gridSort(GRID_INSCRIPTIONS,orderInscripEventNumber);
}
void CHFideInformationDlg::fillMembers()
{
	w->gridDeleteAllItems(GRID_MEMBERS);
	RWSet& colMembers=CHMemoryDataBase::getColMember();
	RWSetIterator it( colMembers );
	CHMember *pMemberAux=0;

	while( (pMemberAux=(CHMember*)it())!=0 )
	{
		w->addGridLine(GRID_MEMBERS,LPARAM(pMemberAux),"");
	}
	
	w->gridSort(GRID_MEMBERS,orderMemberEventNumber);
}

void CHFideInformationDlg::sortFideInformation(short type)
{
	
	PFN_ORDER_FC compare=0;
	switch(type)
	{
		case 0: compare = orderMasterTypeByCode;
			break;
		case 1: compare = orderMasterTypeByName;
			break;
		case 2: compare = orderMasterTypeByRating;
			break;
	}
	w->gridSort(GRID_FIDE_INFOR,compare);
	
}		
void CHFideInformationDlg::sortInscriptions(short type)
{
	
	PFN_ORDER_FC compare=0;
	switch(type)
	{
		case 0: compare = orderInscripIDNumber;
			break;
		case 1: compare = orderInscripName;
			break;
		case 2: compare = orderInscripEventNumber;
			break;
		case 3: compare = orderInscripRatingNumber;
			break;
		case 4: compare = orderInscripEventSeed;
			break;
	}
	w->gridSort(GRID_INSCRIPTIONS,compare);
}
void CHFideInformationDlg::sortMembers(short type)
{
	
	PFN_ORDER_FC compare=0;
	switch(type)
	{
		case 0: compare = orderMemberIDNumber;
			break;
		case 1: compare = orderMemberName;
			break;
		case 2: compare = orderMemberEventNumber;
			break;
		case 3: compare = orderMemberRatingNumber;
			break;
		
	}
	w->gridSort(GRID_MEMBERS,compare);
}


BOOL CHFideInformationDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(w)	
		delete w;
	return CDialog::DestroyWindow();
}

LRESULT CHFideInformationDlg::onPaintGrid(WPARAM wParam,LPARAM lParam)
{
	if (wParam==GRID_FIDE_INFOR)
	{
		paintFideInformation((GridItem*)lParam);
		return TRUE;
	}
	if (wParam==GRID_INSCRIPTIONS)
	{
		paintInscriptions((GridItem*)lParam);
		return TRUE;
	}
	if (wParam==GRID_MEMBERS)
	{
		paintMembers((GridItem*)lParam);
		return TRUE;
	}
	return FALSE;
}

void CHFideInformationDlg::paintFideInformation(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHFideElement* pFideElement=(CHFideElement*) gi->lParam;
	if (!pFideElement) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	char tmp[20];
	switch(gi->x)
	{
		
		case 0:	// Id Number
		{
			sprintf(tmp,"%d",pFideElement->getIdNumber());
			w->paintGridText(5,0,RWCString(tmp),JUST_LEFT);	
			break;
		}
		case 1: // Name
		{
			w->paintGridText(5,3,pFideElement->getName(),JUST_LEFT);	
			break;
		}
		case 2: // Title 
		{
			w->paintGridText(5,3,pFideElement->getTitle(),JUST_LEFT);	
			break;
		}
		case 3: // Federation 
		{
			w->paintGridText(5,3,pFideElement->getFederation(),JUST_LEFT);	
			break;
		}
		
		case 4: // Rating
		{
			sprintf(tmp,"%d",pFideElement->getRating());
			w->paintGridText(5,3,RWCString(tmp),JUST_LEFT);	
			break;
		}
		case 5: // Games
		{
			sprintf(tmp,"%d",pFideElement->getGames());
			w->paintGridText(5,3,RWCString(tmp),JUST_LEFT);	
			break;
		}
		case 6: // Born
		{
			w->paintGridText(5,3,pFideElement->getYearOBirth(),JUST_LEFT);	
			break;
		}
		case 7: // Flag
		{
			w->paintGridText(5,3,pFideElement->getFlag(),JUST_LEFT);	
			break;
		}
	}
}
void CHFideInformationDlg::paintInscriptions(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHInscription* pInscription=(CHInscription*) gi->lParam;
	if (!pInscription) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro
	

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(!existInFideFile(pInscription))
			gi->cdc->FillSolidRect(gi->rc,RGB(230,183,186));
		else
			if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	switch(gi->x)
	{
		case 0:	// Id Number
		{
			w->paintGridText(5,0,pInscription->getAcreditation(),JUST_LEFT);	
			break;
		}	
		case 1:	// Name
		{
			w->paintGridText(5,0,pInscription->getPrnLName().toAscii(),JUST_LEFT);	
			break;
		}
		case 2: // Event
		{
			w->paintGridText(5,3,pInscription->getEventLDescription().toAscii(),JUST_LEFT);	
			break;
		}
		case 3: // Rating
		{
			w->paintGridText(5,3,pInscription->getRatingAsString(),JUST_LEFT);	
			break;
		}
		case 4: // Seed
		{
			w->paintGridText(5,3,pInscription->getSeedAsString(),JUST_LEFT);	
			break;
		}
	
	}
}
void CHFideInformationDlg::paintMembers(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHMember* pMember=(CHMember*) gi->lParam;
	if (!pMember) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro
	

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(!existInFideFile(pMember))
			gi->cdc->FillSolidRect(gi->rc,RGB(230,183,186));
		else
			if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	switch(gi->x)
	{
		case 0:	// Id Number
		{
			w->paintGridText(5,0,pMember->getAcreditation(),JUST_LEFT);	
			break;
		}	
		case 1:	// Name
		{
			w->paintGridText(5,0,pMember->getPrnLName().toAscii(),JUST_LEFT);	
			break;
		}
		case 2: // Event
		{
			w->paintGridText(5,3,pMember->getEventLDescription().toAscii(),JUST_LEFT);	
			break;
		}
		case 3: // Rating
		{
			w->paintGridText(5,3,pMember->getRatingAsString(),JUST_LEFT);	
			break;
		}
		
	
	}
}

LRESULT CHFideInformationDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (wParam)
	{
		
		case BUCH_BACK:
		{
			OnOK();
			break;
		}
		
		case GRID_FIDE_INFOR:
		{
			paintCartel();
			break;
		}
		case BUCH_FIDE:
		{
			saveFideFile();
			w->redraw(GRID_INSCRIPTIONS,FALSE);
			break;
		}
		case LBL_REGISTERS:
			insMember=!insMember;
			paintInsMember();
			break;
	}
	return TRUE;
}

LRESULT CHFideInformationDlg::onDblClick(WPARAM wParam, LPARAM lParam)
{
	if (wParam==GRID_FIDE_INFOR)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);
		switch (x)  // Columns
		{
			case 0: // Id Number
			{
				
				break;
			}
			case 1: // Name
			{
				
				break;
			}
			case 2: // Title
			{
				break;
				
			}
		}
	}
	if (wParam==GRID_INSCRIPTIONS)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);

		CHInscription *pInscription=(CHInscription*)w->getSelectedData(GRID_INSCRIPTIONS);
		if(!pInscription)
			return false;
		switch (x)  // Columns
		{
			case 3: // Rating
			{
				editRating(x,y,pInscription);
				break;
			}
			case 4: // Seed
			{
				editSeed(x,y,pInscription);
				break;
			}
			
		}
	}
	return 0;
}

void CHFideInformationDlg::editRating(int x,int y,CHInscription *pInscription)
{
	char tmp[10];
	CString aux =_T("");
	int rating=pInscription->getRating();
	if (rating)
		aux=itoa(rating,tmp,10);
	CString text = w->editGridCell(GRID_INSCRIPTIONS,x,y,aux);
	if (text!=aux)
	{
		if( text.IsEmpty() )
			pInscription->setRating(0);
		else
			pInscription->setRating(short(_wtoi(text)));
		theApp.queueOut(pInscription);
		theApp.out(TRN_SET_INSCRIPTION);
		
		w->redraw(GRID_INSCRIPTIONS);
	}
}

void CHFideInformationDlg::editSeed(int x,int y,CHInscription *pInscription)
{
	char tmp[10];
	CString aux =_T("");
	short seed=pInscription->getSeed();
	if (seed)
		aux=itoa(seed,tmp,10);
	CString text = w->editGridCell(GRID_INSCRIPTIONS,x,y,aux);
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
			theApp.queueOut(pInscription);
			theApp.out(TRN_SET_INSCRIPTION);
			w->redraw(GRID_INSCRIPTIONS);
			
		}
		else
			::msg("Seed incorrect","The seed is repeat",ICO_W,MSG_OK);
	}
}
RWBoolean CHFideInformationDlg::repeatSeed(CHInscription* pInscription, short seed)
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
void CHFideInformationDlg::OnOK()
{
	
	CDialog::OnOK();
}

LRESULT CHFideInformationDlg::onClickHeader(WPARAM wParam,LPARAM lParam)
{
	switch (wParam)
	{
		case GRID_FIDE_INFOR:
		{
			switch (lParam)
			{
				case 0: //ID Number
					sortFideInformation(0);
				break;
				case 1: //Name
					sortFideInformation(1);
				break;
				case 4: //Rating
					sortFideInformation(2);
				break;
			}
			break;
		}

		case GRID_INSCRIPTIONS:
		{
			switch (lParam)
			{
				case 0: //ID Number
					sortInscriptions(0);
				break;
				case 1: //Name
					sortInscriptions(1);
				break;
				case 2: //Event
					sortInscriptions(2);
				case 3: //Rating
					sortInscriptions(3);
				break;
				case 4: //Seed
					sortInscriptions(4);
				break;
			}
			break;
		}
		case GRID_MEMBERS:
		{
			switch (lParam)
			{
				case 0: //ID Number
					sortMembers(0);
				break;
				case 1: //Name
					sortMembers(1);
				break;
				case 2: //Event
					sortMembers(2);
				case 3: //Rating
					sortMembers(3);
				break;
				
			}
			break;
		}
	}
	return 0;
}

void CHFideInformationDlg::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
		
	}
}

RWBoolean CHFideInformationDlg::processIn(RWCString line,CHFideElement *pFideElement)
{
	size_t i = 0;
	size_t pos = 0;
	 
	
	RWCString aux=NULLRWSTRING;

	// ID_NUMBER 
	int number=0;
	//pos = line.first(' ');
	pos =8;
	
	/*if (pos==RW_NPOS)
		return false;*/

	aux = line(i,pos);
	number=atoi(aux);
	// Solo queremos incluir los que tengamos en base de datos
	if(!existIDNumber(number))
		return false;

	pFideElement->setIdNumber(atoi(aux));
	line.remove(0,pos+2); // 2 espacios en blanco entre columnas
		
	//NAME
	pos = 34;
	aux = line(i,pos);
	aux = aux.strip(RWCString::trailing,' ');
	pFideElement->setName(aux);
	line.remove(0,pos);

	//TITLE
	pos=2;
	aux = line(i,pos);
	pFideElement->setTitle(aux);
	line.remove(0,pos+2);

	//FEDERATION
	pos=3;
	aux = line(i,pos);
	pFideElement->setFederation(aux);
	line.remove(0,pos+2);

	//RATING
	pos=4;
	aux = line(i,pos);
	pFideElement->setRating(atoi(aux));
	line.remove(0,pos+2);

	//GAMES
	pos=3;
	aux = line(i,pos);
	pFideElement->setGames(atoi(aux));
	line.remove(0,pos+2);

	//DATE OF BIRTH
	pos=4;
	aux = line(i,pos);
	pFideElement->setYearOfBirth(aux);
	line.remove(0,pos+2);

	//FLAG
	pos=2;
	aux = line(i,pos);
	pFideElement->setFlag(aux);
		
	return true;
}
CHInscription *CHFideInformationDlg::existIDNumber(int number)
{
		
	RWSetIterator it(CHMemoryDataBase::getColInscriptions());
	CHInscription *pIns=NULL;	
	GSortedVector vectorAll;
	
	
	while( (pIns = (CHInscription*)it()) != 0 ) 
		vectorAll.insert(pIns);
			
	RWCString data=NULLRWSTRING;
	
	for (size_t j=0; j<vectorAll.entries(); j++)
	{
		pIns=(CHInscription *)(vectorAll[j]->getElement());		
		if( pIns )
		{
			if (atoi(pIns->getAcreditation())==number)
			{
				vectorAll.clearAndDestroy();
				return pIns;
				
			}
			
		}
	}
	vectorAll.clearAndDestroy();

	return NULL;

}
void CHFideInformationDlg::setInformation(CHFideElement *pFideElement)
{
		
	RWSetIterator it(CHMemoryDataBase::getColInscriptions());
	CHInscription *pIns=NULL;	
	GSortedVector vectorIns;
	
	
	while( (pIns = (CHInscription*)it()) != 0 ) 
		vectorIns.insert(pIns);
			
	RWCString data=NULLRWSTRING;
	
	for (size_t j=0; j<vectorIns.entries(); j++)
	{
		pIns=(CHInscription *)(vectorIns[j]->getElement());		
		if( pIns )
		{
			if (atoi(pIns->getAcreditation())==pFideElement->getIdNumber())
			{
				pIns->setRating(short(pFideElement->getRating()));
				theApp.queueOut(pIns);
				
				
			}
			
		}
	}
	vectorIns.clearAndDestroy();

	RWSetIterator ite(CHMemoryDataBase::getColMember());
	CHMember *pMemb=NULL;	
	GSortedVector vectorMemb;
	
	
	while( (pMemb = (CHMember*)ite()) != 0 ) 
		vectorMemb.insert(pMemb);
			
	
	for (j=0; j<vectorMemb.entries(); j++)
	{
		pMemb=(CHMember *)(vectorMemb[j]->getElement());		
		if( pMemb )
		{
			if (atoi(pMemb->getAcreditation())==pFideElement->getIdNumber())
			{
				pMemb->setRating(short(pFideElement->getRating()));
				theApp.queueOut(pMemb);
				
				
			}
			
		}
	}
	vectorMemb.clearAndDestroy();

}

RWBoolean CHFideInformationDlg::existInFideFile(CHInscription *pInscription)
{
	CHFideElement *pFideElement=0;
	for(size_t i=0;i<vFideInformations.entries();i++)
	{
		pFideElement=(CHFideElement*)vFideInformations[i]->getElement();
		if(pFideElement->getIdNumber()==atoi(pInscription->getAcreditation()))
			return true;
	}
	return false;
	
}
RWBoolean CHFideInformationDlg::existInFideFile(CHMember *pMember)
{
	CHFideElement *pFideElement=0;
	for(size_t i=0;i<vFideInformations.entries();i++)
	{
		pFideElement=(CHFideElement*)vFideInformations[i]->getElement();
		if(pFideElement->getIdNumber()==atoi(pMember->getAcreditation()))
			return true;
	}
	return false;
	
}
void CHFideInformationDlg::saveFideFile()
{
	CHFideElement *pFideElement=0;

	if(!vFideInformations.entries())
		return;

	for(size_t i=0;i<vFideInformations.entries();i++)
	{
		pFideElement=(CHFideElement*)vFideInformations[i]->getElement();
		setInformation(pFideElement);
				
	}
	theApp.out(TRN_SET_INSCRIPTION);
	::msg("FIDE Information","Transfer Completed",ICO_I,MSG_OK);
	w->redraw(GRID_INSCRIPTIONS);
	w->redraw(GRID_MEMBERS);
}
void CHFideInformationDlg::paintInsMember()
{
	if(insMember)
	{
		w->show(GRID_INSCRIPTIONS);
		w->hide(GRID_MEMBERS);
		w->changeTxt(LBL_REGISTERS,"Inscriptions");
	}
	else
	{
		w->show(GRID_MEMBERS);
		w->hide(GRID_INSCRIPTIONS);
		w->changeTxt(LBL_REGISTERS,"Members");
	}
}