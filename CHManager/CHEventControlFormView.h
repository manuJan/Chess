// CHEventControlFormView.h: interface for the CHEventControlFormView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHEVENTCONTROLFORMVIEW_H__338E5217_CD09_42B1_8FE8_BBF41F53253C__INCLUDED_)
#define AFX_CHEVENTCONTROLFORMVIEW_H__338E5217_CD09_42B1_8FE8_BBF41F53253C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/TH/GTHEventControlFormView.h>
#include <Sports/CH/Data/CHStatisticDefines.h>
#include "CHEvenControlOperations.h"

class CHEventControlTable;
class CHEventControlMultiScrollBar;


class CHEventControlFormView : public GTHEventControlFormView  
{
	DECLARE_DYNCREATE(CHEventControlFormView)

public:
	CHEventControlFormView();
	virtual ~CHEventControlFormView();

	void init();
	BOOL exit();

	// From GTHEventControlFormView
	void showAreaSelectMatch(BOOL show);
	void showAreaHistoric   (BOOL show);

	long		requestData					(long idData,long idEvent,LPARAM lParam);
	GData*		requestStatistic			(long idPlay,const GTHECStatistic &st,int posHist,RWBoolean isDo=TRUE);

	//Plays and Data
	BOOL		infoCurrentPlayStart	(long idPlay, RWOrdered m_datas);
	void		infoHistoricEnd			(int posHist, BOOL isDo,action histAction);
	BOOL	    infoCurrentPlayEnd(long idPlay,RWOrdered m_datas);	//todavia no esta creado el Historico
	void		infoHistoricRecalculation(int posHist,action typeAction);
	void		infoPlayEnd				();

	long		getDataPlayer(long idEvent, LPARAM lParam);
	long		getDataOldPosi(long idEvent, LPARAM lParam);
	long		getDataNewPosi(long idEvent, LPARAM lParam);
	long		getDataResult(long idEvent, LPARAM lParam);
	long		getDataPiece(long idEvent, LPARAM lParam);
	long		getDataNumPlay(long idEvent, LPARAM lParam);
	long		getDataEatPiece(long idEvent, LPARAM lParam);
	long		getDataGeneralPurpose(long idEvent, LPARAM lParam);

	int			getIdGridHistoric();
	
	// Scroll Bar
	int getMultiScrollBarPosition();



	// Messages
	LRESULT onGridDrag(WPARAM wParam, LPARAM lParam);
	void		onGridDrop(WPARAM wParam, LPARAM lParam);
	void		onClick(UINT idCtrl,LPARAM lParam);
	void		onDblClick(UINT idGrid,int x,int y,LPARAM lParam);
	BOOL		onPaintGrid(UINT idGrid,GridItem *gi);

	// Matches
	void hideGUI(int index);
	void createGUI(CHMatch *pMatch, int index);
	void createGrid(int idGrid);
	void destroyControls();

	BOOL launchMatches();
	bool matchView(GTHMatch * pMatch);


	void showMatchesInPlay();
	void showDataEntryArea(BOOL show);
	int  fillMatchesInPlayVector();
		
	RWBoolean insertMatchInPlay(CHMatch* pMatch);
	RWBoolean removeMatchInPlay(CHMatch* pMatch);

	CHEventControlTable	*getBoard(int index);
	CHEventControlTable	*findBoard(GTHMatch* pMatch);

	// V i r t u a l    m e t h o d s   R e p o r t s
	void onReportRequest(CReportItem    *pItem);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AREventControlGUI)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(AREventControlGUI)
		LRESULT onShowMatches	(WPARAM wParam, LPARAM lParam);
		LRESULT onChangeStatus	(WPARAM wParam, LPARAM lParam);
		LRESULT	onEvent			(WPARAM wParam, LPARAM lParam);
		LRESULT	onSetMatch		(WPARAM wParam, LPARAM lParam);
		LRESULT	onCancelEvents	(WPARAM wParam, LPARAM lParam);
		LRESULT	onOutCol		(WPARAM wParam, LPARAM lParam);
		LRESULT	onSend			(WPARAM wParam, LPARAM lParam);
		LRESULT	onProcessMovement(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	void fillReports();
		
	void savePgn();
	void loadPgn();

private:

	GSortedVector vMatchesInPlay;
	CMapStringToOb obListBoards;
	CHMatch* pSelMatch;

	CHEventControlMultiScrollBar* m_pMultiScrollBar;

	CHEvenControlOperations    eventControlOp;
};

#endif // !defined(AFX_CHEVENTCONTROLFORMVIEW_H__338E5217_CD09_42B1_8FE8_BBF41F53253C__INCLUDED_)
