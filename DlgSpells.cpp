// DlgSpells.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgSpells.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSpells dialog


DlgSpells::DlgSpells(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSpells::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSpells)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	spell = 0;
	type = TYPE_WALLS;
}


void DlgSpells::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSpells)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSpells, CDialog)
	//{{AFX_MSG_MAP(DlgSpells)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_LBN_SELCHANGE(IDC_SPELLS, OnSelchangeSpells)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSpells message handlers

void DlgSpells::OnSelchangeType() 
{
	int i, x = 0;
	CListBox *lb;
	CComboBox*cb;

	cb = (CComboBox*)GetDlgItem(IDC_TYPE);
	lb = (CListBox*)GetDlgItem(IDC_SPELLS);

	type = cb->GetItemData(cb->GetCurSel());

	lb->ResetContent();

	for(i = 0; i < SPELL_HIGHEST; i++)
	{
		if(spells[i].Active())
		{
			if(type == TYPE_ALL)
			{
				lb->InsertString(x, spells[i].SpellName());
				lb->SetItemData(x, spells[i].Id());
				x++;
			}
			else 
			{
				if(spells[i].type == type)
				{
					lb->InsertString(x, spells[i].SpellName());
					lb->SetItemData(x, spells[i].Id());
					x++;
				}
			}
		}
	}
}

BOOL DlgSpells::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComboBox *cb;

	cb = (CComboBox*)GetDlgItem(IDC_TYPE);

	for(int i = 0; i < TYPE_MAX; i++)
	{
		cb->InsertString(i, types[i].name);
		cb->SetItemData(i, types[i].type);
	}

	cb->SetCurSel(0);
	type = TYPE_ALL;

	OnSelchangeType();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSpells::OnSelchangeSpells() 
{
	CListBox *lb;
	
	lb = (CListBox*)GetDlgItem(IDC_SPELLS);

	spell = lb->GetItemData(lb->GetCurSel());
}
