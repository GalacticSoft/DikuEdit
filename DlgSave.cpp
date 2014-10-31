// DlgSave.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgSave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSave dialog


DlgSave::DlgSave(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSave::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSave)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSave, CDialog)
	//{{AFX_MSG_MAP(DlgSave)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSave message handlers

BOOL DlgSave::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;
}

void DlgSave::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}
