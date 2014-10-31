// CrewView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "CrewView.h"
#include "CrewBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CrewView dialog


CrewView::CrewView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CrewView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CrewView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CrewView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CrewView)
	DDX_Control(pDX, IDC_CREW_LIST, CrewList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CrewView, CTabPageSSL)
	//{{AFX_MSG_MAP(CrewView)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_CREW_LIST, OnDblclkCrewList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CrewView message handlers

BOOL CrewView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	CRect rect;

	DWORD dwStyle = ::SendMessage(CrewList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(CrewList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	CrewList.GetClientRect(rect);
	CrewList.InsertColumn(0, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	CrewList.InsertColumn(1, "Price", LVCFMT_LEFT, rect.Width()/5);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CrewView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabPageSSL::OnShowWindow(bShow, nStatus);
	Crew *crew;
	int i = 0;
	CString str;

	if(bShow == 1)
	{
		CrewList.DeleteAllItems();
		for(crew = CrewList::crews.first; crew; crew = crew->next)
		{
			CrewList.InsertItem(i, StripAnsiChars(crew->name), 0);
			str.Format("%d", crew->price);
			CrewList.SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
			CrewList.SetItemData(i, (DWORD)crew);
			i++;
		}
	}
	
}

void CrewView::OnDblclkCrewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CrewBuilder crew_dlg(this);
	CListCtrl *list;
	POSITION pos;
	int i;
	CString str;

	list = (CListCtrl*)GetDlgItem(IDC_CREW_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the crew you wish to edit.");
		return;
	}

	crew_dlg.crew = (Crew*)list->GetItemData(i);

	if(crew_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(crew_dlg.crew->name), 0);
		str.Format("%d", crew_dlg.crew->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)crew_dlg.crew);
	}
	
	*pResult = 0;
}
