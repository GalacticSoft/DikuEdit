// DlgEditFriends.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditFriends.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEditFriends dialog


DlgEditFriends::DlgEditFriends(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditFriends::IDD, pParent)
{
	mob = NULL;
	mount = NULL;
	//{{AFX_DATA_INIT(DlgEditFriends)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgEditFriends::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditFriends)
	DDX_Control(pDX, IDC_LIST3, m_FolList);
	DDX_Control(pDX, IDC_LIST2, m_PeopleList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditFriends, CDialog)
	//{{AFX_MSG_MAP(DlgEditFriends)
	ON_BN_CLICKED(IDC_ADD_FOLLOWER, OnAddFollower)
	ON_BN_CLICKED(IDC_REMOVE_FOLLOWER, OnRemoveFollower)
	//ON_LBN_DBLCLK(IDC_FOL_LIST, OnDblclkFolList)
	//ON_LBN_DBLCLK(IDC_MOBS_IN_ROOM, OnDblclkMobList)
	ON_BN_CLICKED(IDC_MOUNT, OnMount)
	ON_BN_CLICKED(IDC_DISMOUNT, OnDismount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditFriends message handlers

void DlgEditFriends::OnAddFollower() 
{
	mob_index *mob;
	CString str;
	int i, count, ret = IDYES;
	POSITION pos;

	pos = m_PeopleList.GetFirstSelectedItemPosition();
	i = m_PeopleList.GetNextSelectedItem(pos);
	if(i < 0)
		MessageBox("Please select a new follower");
	else
	{	
		mob = (mob_index*)m_PeopleList.GetItemData(i);
		
		count = m_FolList.GetItemCount();
		
		if(mob)
		{
			if(mob->group_leader)
			{
				ret = MessageBox("Mob already has leader, change anyways?", "Reset Leader?", MB_YESNO);

				if(ret == IDNO)
					return;
			}

			str.Format("%d", mob->vnum);
			m_FolList.InsertItem(count, str, 0);
			m_FolList.SetItem(count, 1, LVIF_TEXT, StripAnsiChars(mob->GetShortName()), 0, 0, 0, 0);
			m_FolList.SetItemData(count, (DWORD)mob);
			
		}	
		
		m_PeopleList.DeleteItem(i);
	}
}

void DlgEditFriends::OnRemoveFollower() 
{
	mob_index *mob;
	CString str;
	int i, count;

	POSITION pos;

	pos = m_FolList.GetFirstSelectedItemPosition();
	i = m_FolList.GetNextSelectedItem(pos);

	if(i < 0)
		MessageBox("Please select follower to remove");
	else
	{
		mob = (mob_index*)m_FolList.GetItemData(i);
		count = m_PeopleList.GetItemCount();
		if(mob)
		{
			str.Format("%d", mob->vnum);
			m_PeopleList.InsertItem(count, str, 0);
			m_PeopleList.SetItem(count, 1, LVIF_TEXT, StripAnsiChars(mob->GetShortName()), 0, 0, 0, 0);
			m_PeopleList.SetItemData(count, (DWORD)mob);
		}	
		m_FolList.DeleteItem(i);
	}
}

void DlgEditFriends::OnDblclkFolList() 
{
	OnRemoveFollower();
}

void DlgEditFriends::OnDblclkMobList() 
{
	OnAddFollower();
}

void DlgEditFriends::OnOK() 
{	
	mob_index *tmp;
	int i;
	mob->RemoveFollowers();

	for(i = 0; i < m_FolList.GetItemCount(); i++)
	{
		tmp = (mob_index*)m_FolList.GetItemData(i);
		mob->AddFollower(tmp);
	}

	if(!mount)
	{
		if(mob->riding)
			mob->RemoveRiding();
	}
	else
		mob->AddRiding(mount);

	CDialog::OnOK();
}

void DlgEditFriends::OnCancel() 
{	
	CDialog::OnCancel();
}

BOOL DlgEditFriends::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStatic *riding;
	CString str;
	mob_index *tmp = NULL;
	int index;
	CRect rect;

	DWORD dwStyle = ::SendMessage(m_FolList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_FolList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_FolList.GetClientRect(rect);
	m_FolList.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/4);
	m_FolList.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/4));

	dwStyle = ::SendMessage(m_PeopleList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_PeopleList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_PeopleList.GetClientRect(rect);
	m_PeopleList.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/4);
	m_PeopleList.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/4));

	if(!mob)
	{
		CDialog::OnCancel();
		return TRUE;
	}

	if(mob->in_room)
	{	
		index = 0;

		for(tmp = mob->in_room->people; tmp; tmp = tmp->next)
		{
			if(tmp == mob)
				continue;
			if(mob->IsFollower(tmp))
				continue;

			str.Format("%d",tmp->vnum);
			m_PeopleList.InsertItem(index, str, 0);
			m_PeopleList.SetItem(index, 1, LVIF_TEXT, StripAnsiChars(tmp->GetShortName()), 0, 0, 0, 0);
			m_PeopleList.SetItemData(index, (DWORD)tmp);
			index++;
		}
	}
	
	if(mob->follower)
	{
		index = 0;
		tmp = NULL;

		for(tmp = mob->follower; tmp; tmp = tmp->next_in_group)
		{
			str.Format("%d",tmp->vnum);
			m_FolList.InsertItem(index, str, 0);
			m_FolList.SetItem(index, 1, LVIF_TEXT, StripAnsiChars(tmp->GetShortName()), 0, 0, 0, 0);
			m_FolList.SetItemData(index, (DWORD)tmp);
			index++;
		}
	}
	
	if(mob->riding)
	{
		riding = (CStatic*)GetDlgItem(IDC_RIDERTXT);
		str.Format("%d - %s", mob->riding->vnum, StripAnsiChars(mob->riding->GetShortName()));
		riding->SetWindowText(str);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgEditFriends::OnMount() 
{
	DlgVnumList dlg_vnum(this);
	CStatic *txt;
	mob_index *tmp = NULL;
	CString str;
	int ret;

	dlg_vnum.m_index = mob;
	dlg_vnum.type = MOUNT;

	ret = dlg_vnum.DoModal();

	if(ret == IDOK)
	{
		txt = (CStatic*)GetDlgItem(IDC_RIDERTXT);

		tmp = mob->in_room->GetMobInRoom(dlg_vnum.vnum);

		if(tmp)
		{
			if(tmp->rider)
			{
				ret = MessageBox("Mob is already being ridden, change rider?", "Change Rider?", MB_YESNO);
				
				if(ret == IDNO)
					return;
			}

			str.Format("%d - %s", tmp->vnum, StripAnsiChars(tmp->GetShortName()));
			txt->SetWindowText(str);
			mount = tmp;
		}
	}

}

void DlgEditFriends::OnDismount() 
{
	CStatic *txt;

	mount = NULL;

	txt = (CStatic*)GetDlgItem(IDC_RIDERTXT);

	txt->SetWindowText("No Mount");
}
