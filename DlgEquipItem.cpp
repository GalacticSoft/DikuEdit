#include "stdafx.h"
#include "WinDE.h"
#include "DlgEquipItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEquipItem::DlgEquipItem(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEquipItem::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEquipItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	race = RACE_HUMAN;
	obj = NULL;
}

void DlgEquipItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEquipItem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEquipItem, CDialog)
	//{{AFX_MSG_MAP(DlgEquipItem)
	ON_CBN_SELCHANGE(IDC_EQUIP_LOC, OnSelChangeEquipLoc)
	ON_LBN_DBLCLK(IDC_EQ_LIST, OnDblclkEqList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgEquipItem::OnInitDialog() 
{
	CComboBox *cb;
	int i, x;

	cb = (CComboBox*)GetDlgItem(IDC_EQUIP_LOC);

	for(x = 0, i = 0; i < MAX_WEAR; i++) {
		if(slot_names[i] != "UNUSED") {
			if(RaceHasSlot(race, i)) {
				cb->InsertString(x, slot_names[i]);
				cb->SetItemData(x, i);
				x++;
			}
		}
	}

	cb->SetCurSel(0);

	OnSelChangeEquipLoc();

	CDialog::OnInitDialog();
	return TRUE;
}

void DlgEquipItem::OnOK() 
{	
	CListBox *lb;
	CComboBox*cb;
	int ret;

	lb = (CListBox*)GetDlgItem(IDC_EQ_LIST);
	cb = (CComboBox*)GetDlgItem(IDC_EQUIP_LOC);

	if(lb->GetCurSel() > -1) {
		obj = new obj_index;
		obj->obj = (object_data*)lb->GetItemDataPtr(lb->GetCurSel());
		obj->wear_loc = cb->GetItemData(cb->GetCurSel());
		if(obj)
			obj->vnum = obj->obj->vnum;
		else 
			obj->vnum = 0;
		obj->AddToList();
		CDialog::OnOK();
	} else {
		ret = MessageBox("No object has been selected.\nContinue without equiping?", 
			"No Object", MB_YESNO);
		if(ret == IDYES) {
			CDialog::OnCancel();
		}
	}
}

void DlgEquipItem::OnSelChangeEquipLoc() 
{
	CComboBox* cb;
	CListBox *lb;
	object_data *ob;
	CString str;
	int i, x;

	lb = (CListBox*)GetDlgItem(IDC_EQ_LIST);
	cb = (CComboBox*)GetDlgItem(IDC_EQUIP_LOC);
	
	i = 0;

	lb->ResetContent();

	for(ob = object_data::obj_head; ob; ob = ob->next) {
		x = cb->GetItemData(cb->GetCurSel());
		if(ObjIsSlot(ob, x)) {
			str.Format("%d - %s", ob->vnum, StripAnsiChars(ob->short_descr));
			lb->InsertString(i, str);
			lb->SetItemDataPtr(i, (void*)ob);
			i++;
		}
	}
}

void DlgEquipItem::OnDblclkEqList() 
{
	OnOK();
}
