// DlgProgEdit.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgProgEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgProgEdit dialog


DlgProgEdit::DlgProgEdit(CWnd* pParent /*=NULL*/)
	: CDialog(DlgProgEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgProgEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgProgEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgProgEdit)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgProgEdit, CDialog)
	//{{AFX_MSG_MAP(DlgProgEdit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgProgEdit message handlers

BOOL DlgProgEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect frameRect;
	
	GetDlgItem(IDC_PROG_FRAME)->GetWindowRect(frameRect);
	
	ScreenToClient(frameRect);
	frameRect.InflateRect(-2,-2);

	m_pColorWnd = new ColorEditWnd(this, frameRect,	IDC_DISPLAY, 4, 100, "Terminal", true, true);
	m_pColorWnd->SetCharXSpacing(1);
	m_pColorWnd->SetColorizer(&m_colorizer);
	m_pColorWnd->SetReadOnly(false);
	m_pColorWnd->ClearUndoHistory();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgProgEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}
