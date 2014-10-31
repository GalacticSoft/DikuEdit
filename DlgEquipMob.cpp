#include "stdafx.h"
#include "WinDE.h"
#include "DlgEquipMob.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEquipMob::DlgEquipMob(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEquipMob::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEquipMob)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	mob = NULL;
}

void DlgEquipMob::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEquipMob)
	DDX_Control(pDX, IDC_LIST2, m_ListInv);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEquipMob, CDialog)
	//{{AFX_MSG_MAP(DlgEquipMob)
	ON_BN_CLICKED(IDC_ADD_EQUIP_ITEM, OnAddEquipItem)
	ON_BN_CLICKED(IDC_REMOVE_EQUIP_ITEM, OnRemoveEquipItem)
	ON_BN_CLICKED(IDC_ADD_INV_ITEM, OnAddInvItem)
	ON_BN_CLICKED(IDC_REMOVE_INV_ITEM, OnRemoveInvItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEquipMob message handlers

void DlgEquipMob::OnAddEquipItem() 
{
	DlgEquipItem dlg;
	int ret;

	dlg.race = mob->GetRace();
	
	ret = dlg.DoModal();

	if(ret == IDOK) 
	{
		if(dlg.obj != NULL) 
		{
			if(mob->eq[dlg.obj->wear_loc]) 
			{
				ret = MessageBox("Mobile already equiped.\nReplace item with new one?", 
					"Replace object", MB_YESNO);
				
				if(ret == IDYES) 
				{
					mob->eq[dlg.obj->wear_loc]->RemoveFromList();
					dlg.obj->on_mob = mob;
					mob->eq[dlg.obj->wear_loc] = dlg.obj;
					UpdateEquip();
				} 
				else if(ret == IDNO) 
				{
					if(dlg.obj)
						dlg.obj->RemoveFromList();
				}
			} 
			else 
			{
				dlg.obj->on_mob = mob;
				mob->eq[dlg.obj->wear_loc] = dlg.obj;
				UpdateEquip();
			}
		}
	}
}

void DlgEquipMob::OnRemoveEquipItem() 
{
	obj_index *index;
	POSITION pos;

	pos = m_List.GetFirstSelectedItemPosition();
	index = (obj_index*)m_List.GetItemData(m_List.GetNextSelectedItem(pos));
	
	if(index)
	{
		mob->eq[index->wear_loc] = NULL;
		index->RemoveFromList();
	}

	UpdateEquip();	
}

void DlgEquipMob::OnAddInvItem() 
{
	DlgVnumList dlg;
	int ret;
	object_data *obj;
	obj_index *index;

	dlg.type = OBJECT;

	ret = dlg.DoModal();

	if(ret == IDOK) 
	{
		obj = GetObjByVnum(dlg.vnum);

		if(obj) 
		{
			index = new obj_index;
			
			index->vnum = obj->vnum;
			index->obj = obj;
			index->on_mob = mob;
			
			index->AddToList();
			
			mob->AddObjToInv(index);

			UpdateInv();
		}
	}	
}

void DlgEquipMob::OnRemoveInvItem() 
{
	obj_index *index;
	POSITION pos;

	pos = m_ListInv.GetFirstSelectedItemPosition();
	index = (obj_index*)m_ListInv.GetItemData(m_ListInv.GetNextSelectedItem(pos));
	
	if(index)
	{
		mob->RemoveObjFromInv(index);
	
		index->RemoveFromList();
	}

	UpdateInv();
}

void DlgEquipMob::OnOK() 
{	
	CDialog::OnOK();
}

BOOL DlgEquipMob::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	DWORD dwStyle = ::SendMessage(m_List, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_List, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_List.GetClientRect(rect);
	m_List.InsertColumn(0, "Location", LVCFMT_LEFT, rect.Width()/2);
	m_List.InsertColumn(2, "Name", LVCFMT_LEFT, (rect.Width())/2);

	dwStyle = ::SendMessage(m_ListInv, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_ListInv, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	

	m_ListInv.GetClientRect(rect);
	m_ListInv.InsertColumn(0, "Vnum", LVCFMT_LEFT, (rect.Width()/4));
	m_ListInv.InsertColumn(2, "Name", LVCFMT_LEFT, ((rect.Width())-(rect.Width()/4)));
	
	if(mob) 
	{
		UpdateEquip();
		UpdateInv();
	}

	return TRUE; 
}


void DlgEquipMob::UpdateEquip()
{
	int i, x, loc;
	CString str;
	obj_index *index;

	m_List.DeleteAllItems();

	if(mob) 
	{
		x = 0;

		for(i = 0;i < MAX_WEAR;i++) 
		{
			loc = equip_top_down[i];
			
			if(loc > -1) 
			{
				if((index = mob->eq[loc])) 
				{
					m_List.InsertItem(x, slot_names2[loc], 0);
					m_List.SetItem(x, 1, LVIF_TEXT, StripAnsiChars(index->GetShortName()), 1, 0, 0, 0);
					m_List.SetItemData(x, (DWORD)index);
					x++;
				}
			}
		}
	}
}

void DlgEquipMob::UpdateInv()
{
	obj_index *index;
	int i = 0;
	CString str;

	m_ListInv.DeleteAllItems();
	
	for(index = mob->inventory; index; index = index->next) {
		str.Format("%d", index->vnum);
		m_ListInv.InsertItem(i, str, 0);
		m_ListInv.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(index->GetShortName()), 1, 0, 0, 0);
		m_ListInv.SetItemData(i, (DWORD)index);
		i++;
	}
}
