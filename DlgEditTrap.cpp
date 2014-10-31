// DlgEditTrap.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditTrap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEditTrap dialog


DlgEditTrap::DlgEditTrap(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditTrap::IDD, pParent)
{
	trigger = 0;
	obj = NULL;
	//{{AFX_DATA_INIT(DlgEditTrap)
	charges = 0;
	damage_type = -1;
	level = 0;
	percent = 0;
	//}}AFX_DATA_INIT
}


void DlgEditTrap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditTrap)
	DDX_Control(pDX, IDC_LIST4, m_TrigList);
	DDX_Text(pDX, IDC_TRAP_CHARGES, charges);
	DDX_CBIndex(pDX, IDC_TRAP_DAMAGE, damage_type);
	DDX_Text(pDX, IDC_TRAP_LEVEL, level);
	DDX_Text(pDX, IDC_TRAP_PERCENT, percent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditTrap, CDialog)
	//{{AFX_MSG_MAP(DlgEditTrap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditTrap message handlers

void DlgEditTrap::OnOK() 
{	
	UpdateData(true);

	int i;
	POSITION pos;
	
	trigger = 0;

	pos = m_TrigList.GetFirstSelectedItemPosition();
	while(pos)
	{
		i = m_TrigList.GetNextSelectedItem(pos);
		SET_BIT(trigger, m_TrigList.GetItemData(i));
	}

	if(obj)
	{
		obj->trap.damage = damage_type;
		obj->trap.level = level;
		obj->trap.percent = percent;
		obj->trap.charges = charges;
		obj->trap.trigger = trigger;
	}
	CDialog::OnOK();
}

BOOL DlgEditTrap::OnInitDialog() 
{
	CRect rect;
	int i;
	CDialog::OnInitDialog();
	
	if(obj)
	{
		damage_type = obj->trap.damage;
		level = obj->trap.level;
		percent = obj->trap.percent;
		charges = obj->trap.charges;
		trigger = obj->trap.trigger;
	}

	//DWORD dwStyle = ::SendMessage(m_TrigList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	//dwStyle |= LVS_EX_FULLROWSELECT; 

	//::SendMessage(m_TrigList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_TrigList.GetClientRect(rect);
	m_TrigList.InsertColumn(0, "Trigger Type", LVCFMT_LEFT, rect.Width()-1);

	for(i = 0; i < TRIG_MAX; i++)
	{
		m_TrigList.InsertItem(i, trap_trigs[i].name, 0);
		m_TrigList.SetItemData(i, trap_trigs[i].bit);
		
		if(IS_SET(trigger, trap_trigs[i].bit))
		{
			m_TrigList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
			m_TrigList.EnsureVisible(i, FALSE);
		}
	}

	CComboBox *cb;

	cb = (CComboBox*)GetDlgItem(IDC_TRAP_DAMAGE);

	for(i = 0; i < TRAP_MAX; i++)
	{
		cb->InsertString(i, trap_damage[i]);
		cb->SetItemData(i, i);
	}
	
	UpdateData(false);

	return TRUE;
}
