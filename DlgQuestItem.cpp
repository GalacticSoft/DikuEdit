// DlgQuestItem.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgQuestItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgQuestItem dialog


DlgQuestItem::DlgQuestItem(CWnd* pParent /*=NULL*/)
	: CDialog(DlgQuestItem::IDD, pParent)
{
	item = NULL;

	//{{AFX_DATA_INIT(DlgQuestItem)
	qst_type = -1;
	value = 0;
	//}}AFX_DATA_INIT
}


void DlgQuestItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgQuestItem)
	DDX_CBIndex(pDX, IDC_QUEST_TYPE, qst_type);
	DDX_Text(pDX, IDC_QUEST_VALUE, value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgQuestItem, CDialog)
	//{{AFX_MSG_MAP(DlgQuestItem)
	ON_CBN_SELCHANGE(IDC_QUEST_TYPE, OnSelChangeQuestType)
	ON_BN_CLICKED(IDC_GET_VNUM, OnGetVnum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgQuestItem message handlers

void DlgQuestItem::OnOK() 
{	
	UpdateData(true);
	
	item->value = value;
	item->type = qst_type;

	CDialog::OnOK();
}

BOOL DlgQuestItem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComboBox *cb;
	
	cb = (CComboBox*)GetDlgItem(IDC_QUEST_TYPE);
	
	if(item)
	{
		qst_type = item->type;
		value = item->value;
		cb->SetCurSel(item->type);
	}

	switch(type)
	{
		case MOB_WANTS: {
			for(int i = 0; i < QST_WANTS_MAX ;i++)
			{
				cb->InsertString(i, want_types[i]);
			}
			break;
		}
		case MOB_REWARDS: {
			for(int i = 0; i < QST_GIVES_MAX ;i++)
			{
				cb->InsertString(i, reward_types[i]);
			}
			break;
		}
	}

	UpdateData(false);

	return TRUE;  
}

void DlgQuestItem::OnSelChangeQuestType() 
{
	CButton *btn;
	
	btn = (CButton*)GetDlgItem(IDC_GET_VNUM);
	
	UpdateData(true);

	switch(type)
	{
		case MOB_WANTS:
		{
			switch(qst_type)
			{
				case QST_WANTS_OBJ:
					btn->SetWindowText("Object List");
					btn->EnableWindow(true);
					break;
				case QST_WANTS_COINS:
					btn->SetWindowText("Copper Coins");
					btn->EnableWindow(true);
					break;
				case QST_WANTS_TYPE:
					btn->SetWindowText("Object Types");
					btn->EnableWindow(true);
					break;
			}
			break;
		}
		case MOB_REWARDS:
		{
			switch(qst_type)
			{
				case QST_GIVES_OBJ:
					btn->SetWindowText("Object List");
					btn->EnableWindow(true);
					break;
				case QST_GIVES_COINS:
					btn->SetWindowText("Copper Coins");
					btn->EnableWindow(true);
					break;
				case QST_GIVES_SKILL:
					btn->SetWindowText("Skill List");
					btn->EnableWindow(true);
					break;
				case QST_GIVES_EXP:
					btn->SetWindowText("Experience");
					btn->EnableWindow(false);
					break;
				case QST_GIVES_SPELL:
				case QST_GIVES_AFF:	
					btn->SetWindowText("Spell List");
					btn->EnableWindow(true);
					break;
				case QST_GIVES_MOB:
				case QST_GIVES_PET:
					btn->SetWindowText("Mob List");
					btn->EnableWindow(true);
					break;
				case QST_GIVES_TRANS:
				case QST_GIVES_TELE:
				case QST_GIVES_MOBS:
					btn->SetWindowText("Room List");
					btn->EnableWindow(true);
					break;
			}
			break;
		}
	}
}

void DlgQuestItem::OnGetVnum() 
{
	DlgVnumList dlg_vnum(this);
	DlgSpells dlg_spells(this);
	DlgCalcCoins dlg_coins(this);
	DlgExtraObjFlags dlg_types(this);

	int ret;

	switch(type)
	{
		case MOB_WANTS:
			{
				switch(qst_type)
				{
				case QST_WANTS_OBJ:
					dlg_vnum.type = OBJECT;
					
					ret = dlg_vnum.DoModal();
					
					if(ret == IDOK)
						value = dlg_vnum.vnum;
					break;
				case QST_WANTS_COINS:
					ret = dlg_coins.DoModal();
					
					if(ret == IDOK)
						value = dlg_coins.total;
					break;
				case QST_WANTS_TYPE:
					dlg_types.type = 1;
					
					dlg_types.DoModal();

					value = dlg_types.value;

					break;
				}
			}
			break;
		case MOB_REWARDS:
			switch(qst_type)
			{
				case QST_GIVES_OBJ:
					dlg_vnum.type = OBJECT;
					
					ret = dlg_vnum.DoModal();
					
					if(ret == IDOK)
						value = dlg_vnum.vnum;
					break;
				case QST_GIVES_COINS:
					ret = dlg_coins.DoModal();

					if(ret == IDOK)
						value = dlg_coins.total;
					break;
				case QST_GIVES_SKILL:
					break;
				case QST_GIVES_SPELL:
				case QST_GIVES_AFF:
					ret = dlg_spells.DoModal();
					
					if(ret == IDOK)
						value = dlg_spells.spell;
					break;
				case QST_GIVES_MOB:
				case QST_GIVES_PET:
					dlg_vnum.type = MOBILE;

					ret = dlg_vnum.DoModal();

					if(ret == IDOK)
						value = dlg_vnum.vnum;
					break;
				case QST_GIVES_TRANS:
				case QST_GIVES_TELE:
				case QST_GIVES_MOBS:
					dlg_vnum.type = ROOM;

					ret = dlg_vnum.DoModal();

					if(ret == IDOK)
						value = dlg_vnum.vnum;
					break;
			}
			break;
	}
	UpdateData(false);
}
