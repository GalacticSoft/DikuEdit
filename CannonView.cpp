// CannonView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "CannonView.h"
#include "ShipUpgrades.h"
#include "CannonBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CannonView dialog


CannonView::CannonView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CannonView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CannonView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CannonView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CannonView)
	DDX_Control(pDX, IDC_CANNON_LIST, m_CannonList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CannonView, CTabPageSSL)
	//{{AFX_MSG_MAP(CannonView)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_DBLCLK, IDC_CANNON_LIST, OnDblclkCannonList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CannonView message handlers


BOOL CannonView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog ();
	
	CRect rect;

	DWORD dwStyle = ::SendMessage(m_CannonList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_CannonList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_CannonList.GetClientRect(rect);
	m_CannonList.InsertColumn(0, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	m_CannonList.InsertColumn(1, "Price", LVCFMT_LEFT, rect.Width()/5);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CannonView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabPageSSL::OnShowWindow(bShow, nStatus);
	CString str;
	Cannon *cannon;
	int i;

	if(bShow == 1)
	{
		i = 0;
		m_CannonList.DeleteAllItems();

		for(cannon = CannonList::cannons.first; cannon; cannon = cannon->next)
		{
			if(cannon)
			{
				m_CannonList.InsertItem(i, StripAnsiChars(cannon->name), 0);
				str.Format("%d", cannon->value);
				m_CannonList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
				m_CannonList.SetItemData(i, (DWORD)cannon);
				i++;
			}
		}
	}
	
}


void CannonView::OnDblclkCannonList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CannonBuilder cannon_dlg(this);
	CListCtrl *list;
	POSITION pos;
	int i;
	CString str;
	
	list = (CListCtrl*)GetDlgItem(IDC_CANNON_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the cannon you wish to edit.");
		return;
	}

	cannon_dlg.cannon = (Cannon*)list->GetItemData(i);

	if(cannon_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(cannon_dlg.cannon->name), 0);
		str.Format("%d", cannon_dlg.cannon->value);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)cannon_dlg.cannon);
	}
	
	*pResult = 0;
}
