// AmmoView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "AmmoView.h"
#include "AmmoBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AmmoView dialog


AmmoView::AmmoView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(AmmoView::IDD, pParent)
{
	//{{AFX_DATA_INIT(AmmoView)
	//}}AFX_DATA_INIT
}


void AmmoView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AmmoView)
	DDX_Control(pDX, IDC_AMMO_LIST, AmmoList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AmmoView, CTabPageSSL)
	//{{AFX_MSG_MAP(AmmoView)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_AMMO_LIST, OnDblclkAmmoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AmmoView message handlers

BOOL AmmoView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	CRect rect;

	DWORD dwStyle = ::SendMessage(AmmoList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(AmmoList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	AmmoList.GetClientRect(rect);
	AmmoList.InsertColumn(0, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	AmmoList.InsertColumn(1, "Price", LVCFMT_LEFT, rect.Width()/5);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AmmoView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabPageSSL::OnShowWindow(bShow, nStatus);
	Ammo *ammo;
	int i = 0;
	CString str;

	if(bShow == 1)
	{
		AmmoList.DeleteAllItems();

		for(ammo = AmmoList::ammos.first; ammo; ammo = ammo->next)
		{
			AmmoList.InsertItem(i, StripAnsiChars(ammo->name), 0);
			str.Format("%d", ammo->price);
			AmmoList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			AmmoList.SetItemData(i, (DWORD)ammo);
			i++;
		}
	}
	
}

void AmmoView::OnDblclkAmmoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AmmoBuilder ammo_dlg(this);
	POSITION pos;
	int i;
	CString str;
	CListCtrl *list;

	list = (CListCtrl*)GetDlgItem(IDC_AMMO_LIST);
	
	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the ammunition you wish to edit.");
		return;
	}

	ammo_dlg.ammo = (Ammo*)list->GetItemData(i);

	if(ammo_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(ammo_dlg.ammo->name), 0);
		str.Format("%d", ammo_dlg.ammo->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)ammo_dlg.ammo);
	}
	
	*pResult = 0;
}
