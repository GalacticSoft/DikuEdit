// DlgSettings.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSettings dialog


DlgSettings::DlgSettings(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSettings)
	m_auto_save = FALSE;
	m_open_format = 0;
	m_walk_create = FALSE;
	m_echo_commands = 1;
	m_timer = 5;
	m_save_exit = FALSE;
	m_save_format = -1;
	m_disp_line_len = TRUE;
	//}}AFX_DATA_INIT
}


void DlgSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSettings)
	DDX_Check(pDX, IDC_AUTO_SAVE, m_auto_save);
	DDX_CBIndex(pDX, IDC_OPEN_FORMAT, m_open_format);
	DDX_Check(pDX, IDC_WALK_CREATE, m_walk_create);
	DDX_Check(pDX, IDC_ECHO, m_echo_commands);
	DDX_Text(pDX, IDC_TIMER, m_timer);
	DDV_MinMaxInt(pDX, m_timer, 1, 10);
	DDX_Check(pDX, IDC_SAVE_ON_EXIT, m_save_exit);
	DDX_CBIndex(pDX, IDC_SAVE_FORMAT, m_save_format);
	DDX_Check(pDX, IDC_DISP_LINE_LENGTH, m_disp_line_len);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSettings, CDialog)
	//{{AFX_MSG_MAP(DlgSettings)
	ON_BN_CLICKED(IDC_AUTO_SAVE, OnAutoSave)
	ON_BN_CLICKED(IDC_SEL_COLOR, OnSelColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSettings message handlers

void DlgSettings::OnAutoSave() 
{
	UpdateData(true);
	
	if(m_auto_save)
		GetDlgItem(IDC_TIMER)->EnableWindow(true);
	else 
		GetDlgItem(IDC_TIMER)->EnableWindow(false);
}

void DlgSettings::OnOK() 
{
	CDialog::OnOK();
}

int DlgSettings::DoModal() 
{
	return CDialog::DoModal();
}

BOOL DlgSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnAutoSave();
	
	return TRUE;  
}

void DlgSettings::OnSelColor() 
{
	DlgSelectColor dlg;
	
	dlg.def_color = def_color;
	dlg.echo_color = echo_color;
	
	if(dlg.DoModal() == IDOK) {
		def_color = dlg.def_color;
		echo_color = dlg.echo_color;
	}
}
