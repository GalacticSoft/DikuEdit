// CtrlToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "CtrlToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrlToolBar

CCtrlToolBar::CCtrlToolBar()
{
}

CCtrlToolBar::~CCtrlToolBar()
{
}


BEGIN_MESSAGE_MAP(CCtrlToolBar, CToolBar)
	//{{AFX_MSG_MAP(CCtrlToolBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlToolBar message handlers
int CCtrlToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	LoadToolBar(IDR_TOOLBAR1);

	SetButtonStyle(1, TBBS_DISABLED);
	SetButtonStyle(3, TBBS_DISABLED);

	SetButtonStyle(5, TBBS_DISABLED);
	SetButtonStyle(6, TBBS_DISABLED);
	SetButtonStyle(7, TBBS_DISABLED);
	SetButtonStyle(8, TBBS_DISABLED);

	SetButtonStyle(10, TBBS_DISABLED);
	SetButtonStyle(11, TBBS_DISABLED);
	SetButtonStyle(12, TBBS_DISABLED);

	SetButtonStyle(14, TBBS_DISABLED);
	SetButtonStyle(15, TBBS_DISABLED);
	SetButtonStyle(16, TBBS_DISABLED);

	SetButtonStyle(21, TBBS_DISABLED);

	SetButtonStyle(19, TBBS_CHECKED);

	ShowWindow(true);
	return 0;
}
