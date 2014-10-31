// DlgEditQuest.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditQuest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEditQuest dialog


DlgEditQuest::DlgEditQuest(CWnd* pParent /*=NULL*/) : CDialog(DlgEditQuest::IDD, pParent)
{
	qst = NULL;

	//{{AFX_DATA_INIT(DlgEditQuest)
	complete = _T("");
	dissapear = _T("");
	//}}AFX_DATA_INIT
}

void DlgEditQuest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditQuest)
	DDX_Control(pDX, IDC_LIST2, m_RewardList);
	DDX_Control(pDX, IDC_LIST1, m_WantList);
	DDX_Text(pDX, IDC_COMPLETE, complete);
	DDX_Text(pDX, IDC_DISSAPEAR, dissapear);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditQuest, CDialog)
	//{{AFX_MSG_MAP(DlgEditQuest)
	ON_BN_CLICKED(IDC_ADD_WANT, OnAddWant)
	ON_BN_CLICKED(IDC_ADD_REWARDS, OnAddRewards)
	ON_BN_CLICKED(IDC_EDIT_WANTS, OnEditWants)
	ON_BN_CLICKED(IDC_DELETE_WANTS, OnDeleteWants)
	ON_BN_CLICKED(IDC_EDIT_REWARDS, OnEditRewards)
	ON_BN_CLICKED(IDC_DELETE_REWARDS, OnDeleteRewards)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditQuest message handlers

BOOL DlgEditQuest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	quest_item *tmp;
	object_data *obj;
	room_data *room;
	mob_data *mob;
	CString str;
	Spell spl;
	int i = 0;

	complete = qst->complete;
	dissapear = qst->disappear;

	DWORD dwStyle = ::SendMessage(m_WantList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_WantList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_WantList.GetClientRect(rect);
	m_WantList.InsertColumn(0, "Type", LVCFMT_LEFT, rect.Width()/4);
	m_WantList.InsertColumn(1, "Value", LVCFMT_LEFT, rect.Width()/5);
	m_WantList.InsertColumn(2, "Name", LVCFMT_LEFT, (rect.Width()-(rect.Width()/4))-rect.Width()/5);

	dwStyle = ::SendMessage(m_RewardList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_RewardList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_RewardList.GetClientRect(rect);
	m_RewardList.InsertColumn(0, "Type", LVCFMT_LEFT, rect.Width()/4);
	m_RewardList.InsertColumn(1, "Value", LVCFMT_LEFT, rect.Width()/5);
	m_RewardList.InsertColumn(2, "Name", LVCFMT_LEFT, (rect.Width()-(rect.Width()/4))-rect.Width()/5);

	for(tmp = qst->receive, i = 0; tmp; tmp = tmp->next, i++)
	{	
		m_WantList.InsertItem(i, wants[tmp->type], 0);
	
		switch(tmp->type)
		{
		case QST_WANTS_OBJ:
			if((obj = GetObjByVnum(tmp->value)))
			{
				str.Format("%d", obj->vnum);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", tmp->value);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
			}
			break;
		case QST_WANTS_COINS:
			str.Format("%d", tmp->value);
			m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_WantList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
			break;
		case QST_WANTS_TYPE:
			str.Format("%d", tmp->value);
			m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_WantList.SetItem(i, 2, LVIF_TEXT, item_types[tmp->value].name, 1, 0, 0, 0);
			break;
		}
		
		m_WantList.SetItemData(i, (DWORD)tmp);
	}

	for(tmp = qst->give; tmp; tmp = tmp->next)
	{
		i = m_RewardList.GetItemCount();
		m_RewardList.InsertItem(i, rewards[tmp->type], 0);
		
		switch(tmp->type)
		{
		case QST_GIVES_OBJ:
			if((obj = GetObjByVnum(tmp->value)))
			{
				str.Format("%d", obj->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", tmp->value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
			}
			break;
		case QST_GIVES_EXP:
			str.Format("%d", tmp->value);
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			break;
		case QST_GIVES_COINS:
			str.Format("%d", tmp->value);
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_RewardList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
			break;
		case QST_GIVES_SKILL:
			break;		
		case QST_GIVES_SPELL:
		case QST_GIVES_AFF:	
			spl = spells[tmp->value];
			
			str.Format("%d", spl.Id());
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_RewardList.SetItem(i, 2, LVIF_TEXT, spl.SpellName(), 1, 0, 0, 0);
			break;
		case QST_GIVES_MOB:
		case QST_GIVES_PET:
			if((mob = GetMobByVnum(tmp->value)))
			{
				str.Format("%d", mob->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(mob->short_descr), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", tmp->value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Mobile", 1, 0, 0, 0);	
			}
			break;
		case QST_GIVES_MOBS:
		case QST_GIVES_TELE:
		case QST_GIVES_TRANS:
			if((room = GetRoomByVnum(tmp->value)))
			{
				str.Format("%d", room->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(room->name), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", tmp->value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant room", 1, 0, 0, 0);	
			}
			break;
		}

		m_RewardList.SetItemData(i, (DWORD)tmp);
	}
	
	UpdateData(false);

	return TRUE;
}

void DlgEditQuest::OnOK() 
{
	UpdateData(true);
	
	qst->complete = complete;
	qst->disappear = dissapear;

	CDialog::OnOK();
}

void DlgEditQuest::OnAddWant() 
{
	DlgQuestItem dlg_item(this);
	CString str;
	quest_item *item, *tmp;
	object_data *obj;
	int ret, i;

	item = new quest_item();

	dlg_item.item = item;
	dlg_item.type = MOB_WANTS;

	i = m_WantList.GetItemCount();

	ret = dlg_item.DoModal();
	
	if(ret == IDOK)
	{
		switch(dlg_item.qst_type)
		{
		case QST_WANTS_OBJ:
			if((obj = GetObjByVnum(dlg_item.value)))
			{
				m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
				str.Format("%d", obj->vnum);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
			}
			else
			{
				m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
				str.Format("%d", dlg_item.value);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
			}
			break;
		case QST_WANTS_COINS:
			m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
			str.Format("%d", dlg_item.value);
			m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_WantList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
			break;
		case QST_WANTS_TYPE:
			m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
			str.Format("%d", dlg_item.value);
			m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_WantList.SetItem(i, 2, LVIF_TEXT, item_types[dlg_item.value].name, 1, 0, 0, 0);
			break;
		}
		
		m_WantList.SetItemData(i, (DWORD)item);
		
		if(!qst->receive)
			qst->receive = item;
		else
		{
			for(tmp = qst->receive; tmp; tmp = tmp->next)
			{
				if(tmp->next == NULL)
				{
					tmp->next = item;
					break;
				}
			}
		}
	}
}

void DlgEditQuest::OnEditWants() 
{
	DlgQuestItem dlg_item(this);
	int i = -1, ret;
	CString str;
	object_data *obj;
	quest_item *item;
	POSITION pos;

	pos = m_WantList.GetFirstSelectedItemPosition();
	i = m_WantList.GetNextSelectedItem(pos);

	if(i == -1)
		MessageBox("Please select what the mob wants", "No Selection");
	else
	{	
		item = (quest_item*)m_WantList.GetItemData(i);
		
		dlg_item.item = item;
		dlg_item.type = MOB_WANTS;

		ret = dlg_item.DoModal();

		if(ret == IDOK)
		{
			m_WantList.DeleteItem(i);

			switch(dlg_item.qst_type)
			{
			case QST_WANTS_OBJ:
				if((obj = GetObjByVnum(dlg_item.value)))
				{
					m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
					str.Format("%d", obj->vnum);
					m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_WantList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
				}
				else
				{
					m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
					str.Format("%d", dlg_item.value);
					m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_WantList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
				}
			break;
			case QST_WANTS_COINS:
				m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
				str.Format("%d", dlg_item.value);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
			break;
			case QST_WANTS_TYPE:
				m_WantList.InsertItem(i, wants[dlg_item.item->type], 0);
				str.Format("%d", dlg_item.value);
				m_WantList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_WantList.SetItem(i, 2, LVIF_TEXT, item_types[dlg_item.value].name, 1, 0, 0, 0);
				break;
			}
			
			m_WantList.SetItemData(i, (DWORD)item);
		}
	}
}

void DlgEditQuest::OnDeleteWants() 
{
	int i = 0, ret = IDCANCEL;
	quest_item *item, *tmp;
	POSITION pos;

	pos = m_WantList.GetFirstSelectedItemPosition();
	i = m_WantList.GetNextSelectedItem(pos);
	
	item = (quest_item*)m_WantList.GetItemData(i);

	if(i == -1)
		MessageBox("Please select an item to delete", "No Selection");
	else
	{
		ret = MessageBox("Are you sure you want to delete this item?", "Delete Item", MB_YESNO);
		
		if(ret == IDYES)
		{
			if(item == qst->receive)
				qst->receive = item->next;
			else
			{
				for(tmp = qst->receive; tmp; tmp = tmp->next)
				{
					if(tmp->next == item)
					{
						tmp->next = item->next;
						break;
					}
				}
			}

			delete item;
			m_WantList.DeleteItem(i);
		}
	}
}

void DlgEditQuest::OnAddRewards() 
{
	DlgQuestItem dlg_item(this);
	DlgVnumList dlg_vnum(this);
	object_data *obj;
	room_data *room;
	mob_data *mob;
	Spell spl;
	quest_item *item, *tmp;
	int type;
	CString str;
	int ret, i;

	item = new quest_item();

	dlg_item.item = item;
	dlg_item.type = MOB_REWARDS;

	ret = dlg_item.DoModal();

	if(ret == IDOK)
	{
		type = dlg_item.qst_type;

		i = m_RewardList.GetItemCount();
		m_RewardList.InsertItem(i,rewards[type], 0);
		
		switch(type)
		{
		case QST_GIVES_OBJ:
			if((obj = GetObjByVnum(dlg_item.value)))
			{
				str.Format("%d", obj->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", dlg_item.value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
			}
			break;
		case QST_GIVES_EXP:
			str.Format("%d", dlg_item.value);
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			break;
		case QST_GIVES_COINS:
			str.Format("%d", dlg_item.value);
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_RewardList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
			break;
		case QST_GIVES_SKILL:
			break;		
		case QST_GIVES_SPELL:
		case QST_GIVES_AFF:	
			spl = spells[dlg_item.value];
			
			str.Format("%d", spl.Id());
			m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			m_RewardList.SetItem(i, 2, LVIF_TEXT, spl.SpellName(), 1, 0, 0, 0);
			break;
		case QST_GIVES_MOB:
		case QST_GIVES_PET:
			if((mob = GetMobByVnum(dlg_item.value)))
			{
				str.Format("%d", mob->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(mob->short_descr), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", dlg_item.value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Mobile", 1, 0, 0, 0);	
			}
			break;
		case QST_GIVES_MOBS:
		case QST_GIVES_TELE:
		case QST_GIVES_TRANS:
			if((room = GetRoomByVnum(dlg_item.value)))
			{
				str.Format("%d", room->vnum);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(room->name), 1, 0, 0, 0);
			}
			else
			{
				str.Format("%d", dlg_item.value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant room", 1, 0, 0, 0);	
			}
			break;
		}

		m_RewardList.SetItemData(i, (DWORD)item);

		if(!qst->give)
			qst->give = item;
		else
		{
			for(tmp = qst->give; tmp; tmp = tmp->next)
			{
				if(tmp->next == NULL)
				{
					tmp->next = item;
					break;
				}
			}
		}
	}
	else 
		delete item;
}

void DlgEditQuest::OnEditRewards() 
{
	DlgQuestItem dlg_item(this);
	int i = -1, ret, type;
	CString str;
	object_data *obj;
	mob_data *mob;
	room_data *room;
	quest_item *item;
	Spell spl;

	POSITION pos;

	pos = m_RewardList.GetFirstSelectedItemPosition();
	i = m_RewardList.GetNextSelectedItem(pos);
	if(i == -1)
		MessageBox("Please select what the mob wants", "No Selection");
	else
	{	
		item = (quest_item*)m_RewardList.GetItemData(i);
		dlg_item.item = item;
		dlg_item.type = MOB_REWARDS;

		ret = dlg_item.DoModal();

		if(ret == IDOK)
		{
			type = dlg_item.qst_type;
			
			m_RewardList.DeleteItem(i);
			i = m_RewardList.GetItemCount();
			m_RewardList.InsertItem(i, rewards[type], 0);
		
			switch(type)
			{
			case QST_GIVES_OBJ:
				if((obj = GetObjByVnum(dlg_item.value)))
				{
					str.Format("%d", obj->vnum);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
				}
				else
				{
					str.Format("%d", dlg_item.value);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Object", 1, 0, 0, 0);	
				}
				break;
			case QST_GIVES_EXP:
				str.Format("%d", dlg_item.value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				break;
			case QST_GIVES_COINS:
				str.Format("%d", dlg_item.value);
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, "Copper Coins", 1, 0, 0, 0);
				break;
			case QST_GIVES_SKILL:
				break;		
			case QST_GIVES_SPELL:
			case QST_GIVES_AFF:	
				spl = spells[dlg_item.value];
			
				str.Format("%d", spl.Id());
				m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_RewardList.SetItem(i, 2, LVIF_TEXT, spl.SpellName(), 1, 0, 0, 0);
				break;
			case QST_GIVES_MOB:
			case QST_GIVES_PET:
				if((mob = GetMobByVnum(dlg_item.value)))
				{
					str.Format("%d", mob->vnum);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(mob->short_descr), 1, 0, 0, 0);
				}
				else
				{
					str.Format("%d", dlg_item.value);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant Mobile", 1, 0, 0, 0);	
				}
				break;
			case QST_GIVES_MOBS:
			case QST_GIVES_TELE:
			case QST_GIVES_TRANS:
				if((room = GetRoomByVnum(dlg_item.value)))
				{
					str.Format("%d", room->vnum);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, StripAnsiChars(room->name), 1, 0, 0, 0);
				}
				else
				{
					str.Format("%d", dlg_item.value);
					m_RewardList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
					m_RewardList.SetItem(i, 2, LVIF_TEXT, "A Non-Existant room", 1, 0, 0, 0);	
				}
				break;
			}

			m_RewardList.SetItemData(i, (DWORD)item);
		}
	}
}

void DlgEditQuest::OnDeleteRewards() 
{
	int i = 0, ret = IDCANCEL;
	quest_item *item, *tmp;
	POSITION pos;

	pos = m_RewardList.GetFirstSelectedItemPosition();
	i = m_RewardList.GetNextSelectedItem(pos);
	
	item = (quest_item*)m_RewardList.GetItemData(i);

	if(i == -1)
		MessageBox("Please select an item to delete", "No Selection");
	else
	{
		ret = MessageBox("Are you sure you want to delete this item?", "Delete Item", MB_YESNO);
		
		if(ret == IDYES)
		{
			if(item == qst->give)
				qst->give = item->next;
			else
			{
				for(tmp = qst->give; tmp; tmp = tmp->next)
				{
					if(tmp->next == item)
					{
						tmp->next = item->next;
						break;
					}
				}
			}

			m_RewardList.DeleteItem(i);
			delete item;
		}
	}
}
