#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditContents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditContents::DlgEditContents(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditContents::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEditContents)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgEditContents::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditContents)
	DDX_Control(pDX, IDC_LIST2, m_ObjList);
	DDX_Control(pDX, IDC_LIST1, m_InvList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditContents, CDialog)
	//{{AFX_MSG_MAP(DlgEditContents)
	ON_BN_CLICKED(IDC_ADD_OBJ, OnAddObj)
	ON_BN_CLICKED(IDC_REMOVE_OBJ, OnRemoveObj)
	ON_LBN_SELCHANGE(IDC_CONTENTS, OnSelchangeContents)
	ON_LBN_SELCHANGE(IDC_OBJECT_LIST, OnSelchangeObjectList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEditContents::OnAddObj() 
{
	int i;
	CString str;
	object_data *obj_content;
	obj_index *index;
	POSITION pos;

	pos = m_ObjList.GetFirstSelectedItemPosition();
	i = m_ObjList.GetNextSelectedItem(pos);
	
	if(i > -1)
	{
		obj_content = (object_data*)m_ObjList.GetItemData(i);
	
		i = m_InvList.GetItemCount();

		index  = obj->AddContent(obj_content);

		str.Format("%d", index->vnum);
		m_InvList.InsertItem(i, str, 0);
		m_InvList.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(obj_content->short_descr), 1, 0, 0, 0);
		m_InvList.SetItemData(i, (DWORD)index);
		m_InvList.SetSelectionMark(i);
	}
	else
		MessageBox("Please select an item to put in the container.");
}

void DlgEditContents::OnRemoveObj() 
{
	CString str;
	obj_index *index;
	int i;
	POSITION pos;
	
	pos = m_InvList.GetFirstSelectedItemPosition();
	i = m_InvList.GetNextSelectedItem(pos);

	if(i > -1)
	{
		index = (obj_index*)m_InvList.GetItemData(i);
	
		m_InvList.DeleteItem(i);

		obj->RemoveContent(&index);
	}
	else
		MessageBox("Please select an item to remove from the container.");
}

BOOL DlgEditContents::OnInitDialog() 
{
	object_data *tmp;
	obj_index *index;
	CString str;
	CRect rect;
	int i;
	
	CDialog::OnInitDialog();

	DWORD dwStyle = ::SendMessage(m_ObjList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_ObjList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_ObjList.GetClientRect(rect);
	m_ObjList.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/4);
	m_ObjList.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/4));

	for(tmp = object_data::obj_head, i = 0; tmp; tmp = tmp->next, i++) {
		str.Format("%d", tmp->vnum);
		m_ObjList.InsertItem(i, str, 0);
		m_ObjList.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(tmp->short_descr), 1, 0, 0, 0);
		m_ObjList.SetItemData(i, (DWORD)tmp);
	}

	dwStyle = ::SendMessage(m_InvList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_InvList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_InvList.GetClientRect(rect);
	m_InvList.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/4);
	m_InvList.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/4));

	for(index = obj->contents, i = 0; index; index = index->next, i++) {
		str.Format("%d", index->vnum);
		m_InvList.InsertItem(i, str, 0);
		m_InvList.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(index->GetShortName()), 1, 0, 0, 0);
		m_InvList.SetItemData(i, (DWORD)index);
	}
	
	return TRUE;
}

void DlgEditContents::OnSelchangeContents() 
{
	CListBox* lb;
	CButton *b;

	lb = (CListBox*)GetDlgItem(IDC_CONTENTS);
	
	b = (CButton*)GetDlgItem(IDC_REMOVE_OBJ);
	
	if(lb->GetCurSel() != -1)
		b->EnableWindow(true);
	else
		b->EnableWindow(false);
}

void DlgEditContents::OnSelchangeObjectList() 
{
	CListBox* lb;
	CButton *b;

	lb = (CListBox*)GetDlgItem(IDC_OBJECT_LIST);
	
	b = (CButton*)GetDlgItem(IDC_ADD_OBJ);

	if(lb->GetCurSel() != -1)
		b->EnableWindow(true);
	else
		b->EnableWindow(false);
}


void DlgEditContents::OnOK() {
	CDialog::OnOK();
}
