#include "stdafx.h"
#include "WinDE.h"
#include "DlgExtraDesc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgExtraDesc::DlgExtraDesc(CWnd* pParent /*=NULL*/)
	: CDialog(DlgExtraDesc::IDD, pParent)
{
	cur_ed = NULL;
	first_new_ed = NULL;
	last_new_ed = NULL;

	//{{AFX_DATA_INIT(DlgExtraDesc)
	ed = _T("");
	keywords = _T("");
	//}}AFX_DATA_INIT
}

void DlgExtraDesc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgExtraDesc)
	DDX_Text(pDX, IDC_EXTRA_DESC, ed);
	DDX_Text(pDX, IDC_EXTRA_KEYS, keywords);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgExtraDesc, CDialog)
	//{{AFX_MSG_MAP(DlgExtraDesc)
	ON_BN_CLICKED(IDC_PREV_DESC, OnPrevDesc)
	ON_BN_CLICKED(IDC_ADD_DESC, OnAddDesc)
	ON_BN_CLICKED(IDC_DELETE_DESC, OnDeleteDesc)
	ON_BN_CLICKED(IDC_DESC_NEXT, OnDescNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgExtraDesc::OnPrevDesc() 
{
	extra_desc *ped;
	extra_desc *pos;
	
	UpdateData(true);

	ped = cur_ed;
	
	if(!ped) {
		FocusOnKeyword();
		return;
	}

	ped->description = ed;
	ped->keyword = keywords;
	
	if(ped == old_ed_list) {
		if(last_new_ed)
			ped = last_new_ed;
		else if(last_old_ed)
			ped = last_old_ed;
		else {
			FocusOnKeyword();
			return;
		}
	}
	else if(ped == first_new_ed)	{
		if(last_old_ed)
			ped = last_old_ed;
		else if(last_new_ed)
			ped = last_new_ed;
		else {
			FocusOnKeyword();
			return;
		}
	} else
		ped = ped->prev;

	if(!ped) {
		FocusOnKeyword();
		return;
	}

	pos = ped;

	while(ped->deleted) {
		if(ped == old_ed_list) {
			if(last_new_ed)
				ped = last_new_ed;
			else 
				ped = last_old_ed;
		}
		else if(ped == first_new_ed) {
			if(last_old_ed)
				ped = last_old_ed;
			else
				ped = last_new_ed;	
		} else
			ped = ped->prev;
		
		if(ped == pos) {
			keywords = "";
			ed = "";
			cur_ed = NULL;

			UpdateData(false);
			FocusOnKeyword();
			return;
		}
	}

	keywords = ped->keyword;
	ed = ped->description;
	cur_ed = ped;

	UpdateData(false);
	FocusOnKeyword();
}

void DlgExtraDesc::OnAddDesc() 
{
	extra_desc *ped;

	ped = new extra_desc;
	
	if(cur_ed) {
		UpdateData(true);
		cur_ed->description = ed;
		cur_ed->keyword = keywords;
	}

	if(!first_new_ed) {
		first_new_ed = ped;
		last_new_ed = ped;
		ped->prev = NULL;
		ped->next = NULL;
		cur_ed = ped;
	} else {
		last_new_ed->next = ped;
		ped->prev = last_new_ed;
		last_new_ed = ped;
		cur_ed = ped;
	}	
	
	ped->deleted = false;
	ped->description = "";
	ped->keyword = "";

	ed = ped->description;
	keywords = ped->keyword;
	
	UpdateData(false);

	FocusOnKeyword();
}

void DlgExtraDesc::OnDeleteDesc() 
{
	if(cur_ed) {
		cur_ed->deleted = true;
		OnDescNext();
	}
}

void DlgExtraDesc::OnDescNext() 
{	
	extra_desc *ped;
	extra_desc *pos;

	UpdateData(true);

	ped = cur_ed;
	
	if(!ped) {
		FocusOnKeyword();
		return;
	}

	ped->description = ed;
	ped->keyword = keywords;
	
	if(ped == last_old_ed) {
		if(first_new_ed)
			ped = first_new_ed;
		else if(old_ed_list)
			ped = old_ed_list;
		else {
			FocusOnKeyword();
			return;
		}
	}
	else if(ped == last_new_ed)	{
		if(old_ed_list)
			ped = old_ed_list;
		else if(first_new_ed)
			ped = first_new_ed;
		else {
			FocusOnKeyword();
			return;
		}
	} else
		ped = ped->next;

	if(!ped) {
		FocusOnKeyword();
		return;
	}

	pos = ped;

	while(ped->deleted) {
		if(ped == last_old_ed) {
			if(first_new_ed)
				ped = first_new_ed;
			else 
				ped = old_ed_list;
		}
		else if(ped == last_new_ed) {
			if(old_ed_list) 
				ped = old_ed_list;
			else 
				ped = first_new_ed;
		} else
			ped = ped->next;

		if(ped == pos) {
			keywords = "";
			ed = "";
			cur_ed = NULL;

			UpdateData(false);
			FocusOnKeyword();
			return;
		}
	}

	keywords = ped->keyword;
	ed = ped->description;
	cur_ed = ped;

	UpdateData(false);

	FocusOnKeyword();
}

void DlgExtraDesc::OnOK() 
{	
	UpdateData(true);

	if(cur_ed) {
		cur_ed->description = ed;
		cur_ed->keyword = keywords;
	}

	CDialog::OnOK();
}

void DlgExtraDesc::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL DlgExtraDesc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(cur_ed) {
		ed = cur_ed->description;
		keywords = cur_ed->keyword;
	}

	UpdateData(false);
	
	if(!old_ed_list)
		OnAddDesc();

	FocusOnKeyword();
	
	return TRUE;  
}

void DlgExtraDesc::OnFirstEd() 
{
	UpdateData(true);
	
	if(cur_ed) {
		cur_ed->description = ed;
		cur_ed->keyword = keywords;
	}
	
	
	if(old_ed_list)
		cur_ed = old_ed_list;
	else if(first_new_ed)
		cur_ed = first_new_ed;
	else {
		FocusOnKeyword();
		return;
	}

	ed = cur_ed->description;
	keywords = cur_ed->keyword;

	UpdateData(false);

	FocusOnKeyword();
}

void DlgExtraDesc::OnLastEd() 
{
	UpdateData(true);
	
	if(cur_ed) {
		cur_ed->description = ed;
		cur_ed->keyword = keywords;
	}

	if(last_new_ed)
		cur_ed = last_new_ed;
	else if(last_old_ed)
		cur_ed = last_old_ed;
	else {
		FocusOnKeyword();
		return;
	}
	
	ed = cur_ed->description;
	keywords = cur_ed->keyword;
	
	UpdateData(false);

	FocusOnKeyword();
}

void DlgExtraDesc::FocusOnKeyword()
{
	CEdit *tb = (CEdit*)GetDlgItem(IDC_EXTRA_KEYS);
	tb->SetFocus();
}