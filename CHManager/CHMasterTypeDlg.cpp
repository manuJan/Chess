// CHMasterTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chmanager.h"
#include "CHMasterTypeDlg.h"
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>
#include <SPORTS/CH/DATA/CHRegister.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDBBKCLEAR				1701
#define IDBBKBLUE				1702
#define IDBBKBROWN				1703
#define BUCH_OK					1704
#define BUCH_CANCEL				1705
#define LBL_VALUE				1706
#define ED_VALUE				1707
#define RED						1708
#define BLUE					1709
#define IDBBKYELLOW				1710
#define LBL_CARTEL_NAME			1711
#define FONTDLBG				1712
#define GRID_MASTERTYPE			1713
#define BUCH_ADD				1714
#define BUCH_DEL				1715
#define FONTDLG					1716

int orderMasterTypeByCode(const GVectorElement** a, const GVectorElement** b)
{
	CHMasterType *pMasterTypeA = (CHMasterType *)(*a)->getElement();
	CHMasterType *pMasterTypeB = (CHMasterType *)(*b)->getElement();
	
	return pMasterTypeA->getMasterType() - pMasterTypeB->getMasterType();

}
int orderMasterTypeBySDescription(const GVectorElement** a, const GVectorElement** b)
{
	CHMasterType *pMasterTypeA = (CHMasterType *)(*a)->getElement();
	CHMasterType *pMasterTypeB = (CHMasterType *)(*b)->getElement();
	
	return _wcsicoll(pMasterTypeA->getSDescription(), pMasterTypeB->getSDescription());

}
int orderMasterTypeByLDescription(const GVectorElement** a, const GVectorElement** b)
{
	CHMasterType *pMasterTypeA = (CHMasterType *)(*a)->getElement();
	CHMasterType *pMasterTypeB = (CHMasterType *)(*b)->getElement();
	
	return _wcsicoll(pMasterTypeA->getLDescription(), pMasterTypeB->getLDescription());
}

/////////////////////////////////////////////////////////////////////////////
// CHMasterTypeDlg dialog


CHMasterTypeDlg::CHMasterTypeDlg(CHMemoryDataBase* pMem,CHRegister *pRegister,CWnd* pParent /*=NULL*/)
:CDialog(CHMasterTypeDlg::IDD, pParent)
,pMemory(pMem)
,pMasterType(0)
,pRegisterSel(pRegister)
,pressed(false)
,w(0)
{
	//{{AFX_DATA_INIT(CHMasterTypeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHMasterTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMasterTypeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHMasterTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CHMasterTypeDlg)
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
// CHMasterTypeDlg message handlers

BOOL CHMasterTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	w=new CGraphicWnd(this);

	if (!w)
		return FALSE;
	INITW(w);
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
	w->createGrid(GRID_MASTERTYPE,CRect(10,35,370,200),BORDER_3DDOWN,15,IDBCK_GRID,0,FONTDLG, TRUE, 15);
	w->addGridColumn(GRID_MASTERTYPE,"Id", JUST_LEFT  , 35);
	w->addGridColumn(GRID_MASTERTYPE,"Short Desc.", JUST_LEFT  ,55);
	w->addGridColumn(GRID_MASTERTYPE,"Long Desc.", JUST_LEFT  ,268);
	w->gridLineColor(GRID_MASTERTYPE,RGB(207,207,207),RGB(207,207,207));
	fillMasterType(0);
	// BUCHON ADD MasterType
	w->createButton (BUCH_ADD,CRect( 395, 120,495, 140),"Add MasterType.",IDBBKBROWN,0,FONTDLG);
	// BUCHON SUB MasterType
	w->createButton (BUCH_DEL,CRect( 395, 150,495, 170),"Del MasterType.",IDBBKBROWN,0,FONTDLG);
	// BUCHON OK / CANCEL
	w->createButton (BUCH_OK,CRect( 395, 50,495, 70),"OK",IDBBKBROWN,0,FONTDLG);
	//w->createButton (BUCH_CANCEL,CRect( 390, 80, 460, 100),"Cancel",IDBBKBROWN,0,FONTDLG);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHMasterTypeDlg::paintCartel()
{
	CHMasterType* pMasterType=0; 
	RWWString aux=_T("Master Type: ");
	int selLine=w->getSelectedLine(GRID_MASTERTYPE);
	if (selLine>=0)
	{
		pMasterType=(CHMasterType*)w->getSelectedLParam(GRID_MASTERTYPE);
	}
		
	if (pMasterType)
	{
		aux+=pMasterType->getSDescription()+_T("-")+pMasterType->getLDescription();
		aux+=_T(" (");
		wchar_t masterType[10];
		memset(masterType,32,sizeof(masterType));
		swprintf(masterType,_T("%d"),pMasterType->getMasterType()); // MasterType
		aux+=masterType;
		aux+=_T(")");
	}

	w->changeTxt(LBL_CARTEL_NAME,aux);
	w->redraw(LBL_CARTEL_NAME,true);
}

short CHMasterTypeDlg::fillMasterType(short type)
{
	w->gridDeleteAllItems(GRID_MASTERTYPE);

	CompareFunction compare=0;
	switch(type)
	{
		case 0: compare = orderMasterTypeByCode;
			break;
		case 1: compare = orderMasterTypeBySDescription;
			break;
		case 2: compare = orderMasterTypeByLDescription;
			break;
	}
	GSortedVector aVectorMasterType(CHMemoryDataBase::getColMasterTypes(),compare);

	CHMasterType* pMasterType=0;
	for(size_t i=0;i<aVectorMasterType.entries();i++)
	{
		pMasterType=(CHMasterType*)aVectorMasterType[i]->getElement(); 
		w->addGridLine(GRID_MASTERTYPE,LPARAM(pMasterType),"");
		if(pRegisterSel && pRegisterSel->getMasterType()==pMasterType->getMasterType())
			w->selectNLine(GRID_MASTERTYPE,i);
	}
	
	return short(i);
}		

BOOL CHMasterTypeDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(w)	
		delete w;
	return CDialog::DestroyWindow();
}

LRESULT CHMasterTypeDlg::onPaintGrid(WPARAM wParam,LPARAM lParam)
{
	if (wParam==GRID_MASTERTYPE)
	{
		paintMasterType((GridItem*)lParam);
		return TRUE;
	}
	return FALSE;
}

void CHMasterTypeDlg::paintMasterType(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHMasterType* pMasterType=(CHMasterType*) gi->lParam;
	if (!pMasterType) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	switch(gi->x)
	{
		case 0:	
		{
			char tmp[10];
			CString aux=itoa(pMasterType->getMasterType(),tmp,10);
			w->paintGridText(5,0,aux,JUST_LEFT);	
			break;
		}
		case 1:
		{
			CString aux=pMasterType->getSDescription();
			w->paintGridText(5,0,aux,JUST_LEFT);	
			break;
		}
		case 2:
		{
			CString aux=pMasterType->getLDescription();
			w->paintGridText(5,0,aux,JUST_LEFT);	
			break;
		}
	}
}

LRESULT CHMasterTypeDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (wParam)
	{
		case BUCH_OK:
		{
			OnOK();
			break;
		}
		case BUCH_ADD:
		{
			//int selLine=w->getSelectedLine(GRID_MASTERTYPE);
			addMasterType();
			short selLine=fillMasterType();
			w->selectNLine(GRID_MASTERTYPE,selLine);
			break;
		}
		case BUCH_DEL:
		{
			int selLine=w->getSelectedLine(GRID_MASTERTYPE);
			if(selLine)
			{
				CHMasterType *pMasterType=(CHMasterType*)w->getSelectedLParam(GRID_MASTERTYPE);
				if(pMasterType)
				{
					delMasterType(pMasterType);
					w->gridDeleteItem(GRID_MASTERTYPE,selLine);
				}
			}
			break;
		}
		case GRID_MASTERTYPE:
		{
			paintCartel();
			break;
		}
	}
	return TRUE;
}

LRESULT CHMasterTypeDlg::onDblClick(WPARAM wParam, LPARAM lParam)
{
	if (wParam==GRID_MASTERTYPE)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);
		switch (x)  // Columns
		{
			case 0: // Code
			{
				OnOK();
				break;
			}
			case 1: // Short Description
			{
				RWCString txt =NULLRWSTRING;
				
				CHMasterType* pMasterType =(CHMasterType*) w->getGridLParam(GRID_MASTERTYPE,y); 
				txt = w->editGridCell(GRID_MASTERTYPE, x,y,pMasterType->getSDescription().toAscii());
				RWCString aux=pMasterType->getSDescription().toAscii();
				if (txt!=aux)
				{
					int length=txt.length();
					if (length<10)
					{
						GNames aNames;
						aNames.setCode(DBApplication::getAppLanguage());
						aNames.setSName(RWWString(txt,RWWString::ascii));
						aNames.setLName(pMasterType->getLDescription());
						pMasterType->setDescription(aNames);
						saveMasterType(pMasterType);
						w->redraw(GRID_MASTERTYPE,true);
					}
					else
						::msg("Warning","The length text must be smaller than 35 characters",ICO_X,MSG_OK);
				}
				break;
			}
			case 2: // Long Description
			{
				RWCString txt =NULLRWSTRING;
				CHMasterType* pMasterType = (CHMasterType*)w->getGridLParam(GRID_MASTERTYPE,y);
				txt = w->editGridCell(GRID_MASTERTYPE, x,y,pMasterType->getLDescription().toAscii());
				RWCString aux=pMasterType->getLDescription().toAscii();
				if (txt!=aux)
				{
					int length=txt.length();
					if (length<50)
					{
						GNames aNames;
						aNames.setCode(DBApplication::getAppLanguage());
						aNames.setSName(pMasterType->getSDescription());
						aNames.setLName(RWWString(txt,RWWString::ascii));
						pMasterType->setDescription(aNames);
						saveMasterType(pMasterType);
						w->redraw(GRID_MASTERTYPE,true);
					}
					else
						::msg("Warning","The length text must be smaller than 50 characters",ICO_X,MSG_OK);
				}
				
			}
		}
	}
	return 0;
}

bool CHMasterTypeDlg::addMasterType()
{
	short newMasterType=getNextMasterTypeId();

	GNames aNames;
	aNames.setCode(DBApplication::getAppLanguage());
	//pMasterType->setDescription(aNames);

	CHMasterType aMasterType(newMasterType,aNames);

	CHMasterType* pMasterType=pMemory->setMasterType(aMasterType);
	if (pMasterType)
	{
		APP::out(TRN_CH_INSERT_MASTERTYPE);
		APP::out(*pMasterType,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		APP::out();
		return true;
	}
	return false;
}

bool CHMasterTypeDlg::delMasterType(CHMasterType *pMasterType)
{
	GNames aNames;
	aNames.setCode(DBApplication::getAppLanguage());
	CHMasterType aMasterType(pMasterType->getMasterType(),aNames);

	CHMasterType* pMasterTypeAux=pMemory->removeMasterType(aMasterType);
	if (pMasterTypeAux)
	{
		APP::out(TRN_CH_REMOVE_MASTERTYPE);
		APP::out(*pMasterTypeAux,OP_DELETE,TO_VENUE|TO_DATABASE);
		APP::out();
		return true;
	}

	return false;
}

short CHMasterTypeDlg::getNextMasterTypeId()
{
	GSortedVector aVectorMasterType(CHMemoryDataBase::getColMasterTypes(),orderMasterTypeByCode);

	if (!aVectorMasterType.entries())
		return 1;

	CHMasterType* pMasterType=(CHMasterType*)aVectorMasterType[aVectorMasterType.entries()-1]->getElement();

	return short(pMasterType->getMasterType()+1);
}

void CHMasterTypeDlg::saveMasterType(CHMasterType* pMasterType)
{
	APP::out(TRN_CH_CHANGE_MASTERTYPE);
	APP::out(*pMasterType);
	APP::out();		
}

void CHMasterTypeDlg::OnOK()
{
	pMasterType=(CHMasterType*)w->getSelectedLParam(GRID_MASTERTYPE);
	pressed=true;
	CDialog::OnOK();
}

LRESULT CHMasterTypeDlg::onClickHeader(WPARAM wParam,LPARAM lParam)
{
	switch (wParam)
	{
		case GRID_MASTERTYPE:
		{
			switch (lParam)
			{
				case 0: //Code
					fillMasterType(0);
				break;
				case 1: //SDescription
					fillMasterType(1);
				break;
				case 2: //LDescription
					fillMasterType(2);
				break;
			}
		}
	}
	return 0;
}

void CHMasterTypeDlg::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
		
	}
}
