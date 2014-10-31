#include "stdafx.h"
#include "WinDE.h"
#include "DlgExtraObjFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgExtraObjFlags::DlgExtraObjFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgExtraObjFlags::IDD, pParent)
{
	obj = NULL;
	type = 0;
	value = 0;
	//{{AFX_DATA_INIT(DlgExtraObjFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgExtraObjFlags::DoDataExchange(CDataExchange* pDX)
{
	

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgExtraObjFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgExtraObjFlags, CDialog)
	//{{AFX_MSG_MAP(DlgExtraObjFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgExtraObjFlags::OnInitDialog() 
{
	int i, x = 0;
	CListBox* lb;

	CDialog::OnInitDialog();
	
	lb = (CListBox*)GetDlgItem(IDC_EXTRA_FLAGS);

	if(type == 0)
	{
		for(i = 0; i < ExtraFlagCount(); i++) {
			if(obj_flags[i].used) {
				lb->InsertString(x, obj_flags[i].name);
				lb->SetItemData(x, i);
			
				if(obj->ExtraIsSet(*obj_flags[i].bv))
					lb->SetSel(x);

				x++;
			}
		}
	}
	else
	{
		for(i = 0; i < MAX_ITEM_TYPE; i++)
		{
			lb->InsertString(i, item_types[i].name);
			lb->SetItemData(i, i);
		}

	}

	return TRUE;
}

void DlgExtraObjFlags::OnOK() 
{
	int i;
	CListBox* lb;

	lb = (CListBox*)GetDlgItem(IDC_EXTRA_FLAGS);

	if(type == 0)
	{
		for(i = 0; i < lb->GetCount(); i++)
		{
			if(lb->GetSel(i)) {
				if(!obj->ExtraIsSet(*obj_flags[lb->GetItemData(i)].bv))
					obj->SetExtraBit(*obj_flags[lb->GetItemData(i)].bv);
			} else {
				if(obj->ExtraIsSet(*obj_flags[lb->GetItemData(i)].bv))
					obj->RemoveExtraBit(*obj_flags[lb->GetItemData(i)].bv);
			}
		}
	}
	else
	{
		int i = lb->GetCurSel();

		if(i > -1)
			value = lb->GetItemData(i);
		else
			value = TYPE_TRASH;
	}

	CDialog::OnOK();
}
