#include "stdafx.h"
#include "WinDE.h"
#include "DlgGuardFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgGuardFlags::DlgGuardFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGuardFlags::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGuardFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	flags = 0;
}

void DlgGuardFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGuardFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgGuardFlags, CDialog)
	//{{AFX_MSG_MAP(DlgGuardFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgGuardFlags::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CListBox* lb;
	
	lb = (CListBox*)GetDlgItem(IDC_GUARD_FLAGS);

	for(int i = 0; i < GuardBitCount(); i++)
	{
		lb->InsertString(i, guard_bits[i].name);
		lb->SetItemData(i, guard_bits[i].bit);
	}
	
	SetFlags();

	return TRUE;
}

void DlgGuardFlags::OnOK() 
{	
	flags = GetFlags();

	CDialog::OnOK();
}

void DlgGuardFlags::SetFlags()
{
	CListBox* lb;

	lb = (CListBox*)GetDlgItem(IDC_GUARD_FLAGS);

	for(int i = 0; i < GuardBitCount(); i++)
	{
		if(IS_SET(flags, guard_bits[i].bit))
			lb->SetSel(i);
	}
}

int DlgGuardFlags::GetFlags()
{
	CListBox *lb;
	int new_flags = 0;
	
	lb = (CListBox*)GetDlgItem(IDC_GUARD_FLAGS);
	
	for(int i = 0; i < GuardBitCount(); i++) 
	{
		if(lb->GetSel(i))
			SET_BIT(new_flags, lb->GetItemData(i));
		else
			REMOVE_BIT(new_flags, lb->GetItemData(i));
	}

	return new_flags;
}
