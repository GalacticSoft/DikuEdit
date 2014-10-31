// DlgActFlags.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgActFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgActFlags dialog


DlgActFlags::DlgActFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgActFlags::IDD, pParent)
{
	act = 0;

	//{{AFX_DATA_INIT(DlgActFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgActFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgActFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgActFlags, CDialog)
	//{{AFX_MSG_MAP(DlgActFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

enum {MaxActButtons = 28};

const int act_flags[MaxActButtons][2] = {
	{IDC_SIZEMINUS,		ACT_SIZEMINUS},
	{IDC_SENTINAL,		ACT_SENTINEL},
	{IDC_SCAVENGER,		ACT_SCAVENGER},
	{IDC_GUARDIAN,		ACT_GUARDIAN},
	{IDC_AGGRESSIVE,	ACT_AGGRESSIVE},
	{IDC_STAY_AREA,		ACT_STAY_AREA},
	{IDC_WIMPY,			ACT_WIMPY},
	{IDC_AGGROEVIL,		ACT_AGGROEVIL},
	{IDC_AGGROGOOD,		ACT_AGGROGOOD},
	{IDC_AGGRONEUT,		ACT_AGGRONEUT},
	{IDC_MEMORY,		ACT_MEMORY},
	{IDC_NOPARA,		ACT_NOPARA},
	{IDC_NOBASH,		ACT_NOBASH},
	{IDC_TEACHER,		ACT_TEACHER},
	{IDC_WITNESS,		ACT_WITNESS},
	{IDC_CANFLY,		ACT_CANFLY},
	{IDC_CANSWIM,		ACT_CANSWIM},
	{IDC_CANT_TK,		ACT_CANT_TK},
	{IDC_PET,			ACT_PET},
	{IDC_NOEXP,			ACT_NOEXP},
	{IDC_SIZEPLUS,		ACT_SIZEPLUS},
	{IDC_NOCHARM,		ACT_NOCHARM},
	{IDC_PROTECTOR,		ACT_PROTECTOR},
	{IDC_MOUNT,			ACT_MOUNT},
	{IDC_AGGROEVILRACE,	ACT_AGGROEVILRACE},
	{IDC_AGGROGOODRACE, ACT_AGGROGOODRACE},
	{IDC_HUNTER,		ACT_HUNTER},
	{IDC_NOSUMMON,		ACT_NOSUMMON},
};

BOOL DlgActFlags::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton *b;
	int i;

	for(i = 0; i < MaxActButtons; i++) {
		b = (CButton *)GetDlgItem(act_flags[i][0]);	
		if(IS_SET(act, act_flags[i][1]))
			b->SetCheck(true);
	}

	return TRUE;
}

void DlgActFlags::OnOK() 
{	
	CButton *b;
	int i;

	for(i = 0; i < MaxActButtons; i++) {
		b = (CButton *)GetDlgItem(act_flags[i][0]);
		if(b->GetCheck()) {
			if(!IS_SET(act, act_flags[i][1]))
				SET_BIT(act, act_flags[i][1]);
			b->SetCheck(false);
		} else {
			if(IS_SET(act, act_flags[i][1])) {
				REMOVE_BIT(act, act_flags[i][1]);
			}
		}
	}

	CDialog::OnOK();
}
