// DlgAreaStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgAreaStatistics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAreaStatistics dialog


DlgAreaStatistics::DlgAreaStatistics(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAreaStatistics::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAreaStatistics)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgAreaStatistics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAreaStatistics)
	DDX_Control(pDX, IDC_TAB1, StatTabs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAreaStatistics, CDialog)
	//{{AFX_MSG_MAP(DlgAreaStatistics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAreaStatistics message handlers

BOOL DlgAreaStatistics::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	room_tab.Create(IDD_ROOM_VIEW, this);
	StatTabs.AddSSLPage(_T("Room Statistics"), 0, &room_tab);
	mob_tab.Create (IDD_MOB_VIEW, this);
	StatTabs.AddSSLPage (_T("Mobiles Statistics"), 0, &mob_tab);
	obj_tab.Create(IDD_OBJ_VIEW, this);
	StatTabs.AddSSLPage(_T("Object Statistics"), 0, &obj_tab);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
