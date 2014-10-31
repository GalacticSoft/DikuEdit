#include "stdafx.h"
#include "WinDE.h"
#include "DlgMobAffFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgMobAffFlags::DlgMobAffFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMobAffFlags::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgMobAffFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgMobAffFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgMobAffFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgMobAffFlags, CDialog)
	//{{AFX_MSG_MAP(DlgMobAffFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgMobAffFlags::OnOK() 
{
/*	CListBox* lb;
	int loc;
	int i;

	lb = (CListBox*)GetDlgItem(IDC_AFF_LIST1);
	for(i = 0; i < lb->GetCount(); i++) {
		loc = lb->GetItemData(i);
		if(lb->GetSel(i)) {
			if(!IS_SET(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector))
				SET_BIT(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector);
		} else { 
			if(IS_SET(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector))
				REMOVE_BIT(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector);
		}
	}
	
	lb = (CListBox*)GetDlgItem(IDC_AFF_LIST2);
	for(i = 0; i < lb->GetCount(); i++) {
		loc = lb->GetItemData(i);
		if(lb->GetSel(i)) {
			if(!IS_SET(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector))
				SET_BIT(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector);
		} else { 
			if(IS_SET(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector))
				REMOVE_BIT(aff_flags[mob_aff_flags[loc].bv->group], mob_aff_flags[loc].bv->vector);
		}
	}*/

	CDialog::OnOK();
}


BOOL DlgMobAffFlags::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/*CListBox* lb;
	int i, x = 0, y = 0;

	for(i = 0; i < MaxAffFlags(); i++) {
		if(mob_aff_flags[i].in_use) {
			switch(mob_aff_flags[i].bv->group) {
				case 0: {
					lb = (CListBox*)GetDlgItem(IDC_AFF_LIST1);
					lb->InsertString(y, mob_aff_flags[i].name);
					lb->SetItemData(y, i);
					if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
						lb->SetSel(y, TRUE);
					y++;
				}
				break;
				case 1: {
					lb = (CListBox*)GetDlgItem(IDC_AFF_LIST2);
					lb->InsertString(x, mob_aff_flags[i].name);
					lb->SetItemData(x, i);
					if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
						lb->SetSel(x, TRUE);
					x++;
				}
				break;
				case 2: 
				case 3: {
					lb = (CListBox*)GetDlgItem(IDC_AFF_LIST1);
					lb->InsertString(y, mob_aff_flags[i].name);
					lb->SetItemData(y, i);
					if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
						lb->SetSel(y, TRUE);
					y++;
				}
				break;
				case 4:
				case 5: {
					lb = (CListBox*)GetDlgItem(IDC_AFF_LIST2);
					lb->InsertString(x, mob_aff_flags[i].name);
					lb->SetItemData(x, i);
					if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
						lb->SetSel(x, TRUE);
					x++;
				}
				break;
			}
		}
	}*/
	
	return TRUE;
}
