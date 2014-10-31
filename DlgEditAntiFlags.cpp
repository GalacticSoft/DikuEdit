#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditAntiFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditAntiFlags::DlgEditAntiFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditAntiFlags::IDD, pParent)
{
	antis[0] = 0;
	antis[1] = 0;
	//{{AFX_DATA_INIT(DlgEditAntiFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgEditAntiFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditAntiFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditAntiFlags, CDialog)
	//{{AFX_MSG_MAP(DlgEditAntiFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgEditAntiFlags::OnInitDialog() 
{
	CListBox* lb;
	int i;
	
	lb = (CListBox*)GetDlgItem(IDC_ANTI_FLAGS);

	for(i = 0; i < AntiFlagsCount(); i++) {
		lb->InsertString(i, anti_flags[i].name);

		if(IS_SET(antis[anti_flags[i].bv->group], anti_flags[i].bv->vector))
			lb->SetSel(i);
	}

	CDialog::OnInitDialog();
	
	return TRUE;  
}

void DlgEditAntiFlags::OnOK() 
{
	CListBox* lb;
	int i;

	lb = (CListBox*)GetDlgItem(IDC_ANTI_FLAGS);

	for(i = 0; i < lb->GetCount(); i++) {
		if(lb->GetSel(i)) {
			SET_BIT(antis[anti_flags[i].bv->group], anti_flags[i].bv->vector);
		} else if(IS_SET(antis[anti_flags[i].bv->group], anti_flags[i].bv->vector)) {
			REMOVE_BIT(antis[anti_flags[i].bv->group], anti_flags[i].bv->vector);
		}
	}
	
	CDialog::OnOK();
}
