// DlgQuestEdit.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgQuestEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgQuestEdit dialog


DlgQuestEdit::DlgQuestEdit(CWnd* pParent /*=NULL*/)
	: CDialog(DlgQuestEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgQuestEdit)
	quests = NULL;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgQuestEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgQuestEdit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgQuestEdit, CDialog)
	//{{AFX_MSG_MAP(DlgQuestEdit)
	ON_BN_CLICKED(IDC_EDIT_QUEST, OnEditQuest)
	ON_BN_CLICKED(IDC_NEW_QUEST, OnNewQuest)
	ON_BN_CLICKED(IDC_DELETE_QUEST, OnDeleteQuest)
	ON_BN_CLICKED(IDC_EDIT_REWARDS, OnEditRewards)
	ON_BN_CLICKED(IDC_EDIT_WANTS, OnEditWants)
	ON_BN_CLICKED(IDC_NEW_CLUE, OnNewClue)
	ON_BN_CLICKED(IDC_EDIT_CLUE, OnEditClue)
	ON_BN_CLICKED(IDC_DELETE_CLUE, OnDeleteClue)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgQuestEdit message handlers

void DlgQuestEdit::OnEditQuest() 
{
	DlgEditQuest dlg_quest(this);
	quest_data *qst;
	CListBox* lb;
	CString str;
	int i, ret;

	lb = (CListBox*)GetDlgItem(IDC_QUEST_LIST);

	i = lb->GetCurSel();

	if(i == -1)
	{
		MessageBox("Please pick a quest to edit.", "No Selection");
	}
	else
	{
		qst = (quest_data*)lb->GetItemDataPtr(i);

		dlg_quest.qst = qst;

		ret = dlg_quest.DoModal();

		if(ret == IDOK)
		{
			lb->DeleteString(i);
			if(qst->complete != "")
				lb->InsertString(i, qst->complete);
			else
			{
				str.Format("Quest %d", i);
				lb->InsertString(i, str);
			}
			lb->SetItemDataPtr(i, qst);
		}
	}
}	

void DlgQuestEdit::OnNewQuest() 
{
	DlgEditQuest dlg_quest(this);
	quest_data *qst, *tmp;
	CString str;
	CListBox *lb;
	int ret, i = 0;

	lb = (CListBox*)GetDlgItem(IDC_QUEST_LIST);

	qst = new quest_data();
	
	dlg_quest.qst = qst;

	ret = dlg_quest.DoModal();

	i = lb->GetCount();

	if(ret == IDOK)
	{
		if(quests->quests == NULL)
			quests->quests = qst;
		else
		{
			for(tmp = quests->quests; tmp; tmp = tmp->next)
			{
				if(tmp->next == NULL)
				{
					tmp->next = qst;
					break;
				}
			}
		}
		
		if(qst->complete != "")
			lb->InsertString(i, qst->complete);
		else
		{
			str.Format("Quest %d", i);
			lb->InsertString(i, str);
		}

		lb->SetItemDataPtr(i, qst);
	}
	else if(ret == IDCANCEL)
	{
		delete qst;
	}
	
}

void DlgQuestEdit::OnDeleteQuest() 
{
	CListBox *lb;
	int i, ret;
	quest_data *qst = NULL, *tmp;

	lb = (CListBox*)GetDlgItem(IDC_QUEST_LIST);

	i = lb->GetCurSel();

	if(i == -1)
	{
		MessageBox("Select quest to delete.", "No Selection");
	}
	else
	{
		ret = MessageBox("Are you sure?", "Delete Quest?", MB_YESNO);
		
		if(ret == IDYES)
		{
			qst = (quest_data*)lb->GetItemDataPtr(i);

			if(qst == quests->quests)
			{
				quests->quests = qst->next;
				lb->DeleteString(i);
				delete qst;
			}
			else
			{
				for(tmp = quests->quests; tmp; tmp = tmp->next)
				{
					if(tmp->next == qst)
					{
						tmp->next = qst->next;
						lb->DeleteString(i);
						delete qst;
					}
				}
			}
		}
	}
}

void DlgQuestEdit::OnEditRewards() 
{
	
}

void DlgQuestEdit::OnEditWants() 
{
	// TODO: Add your control notification handler code here
}

void DlgQuestEdit::OnNewClue() 
{
	DlgQuestClue dlg_clue(this);
	talk_data *td, *tmp = NULL;
	CListBox *lb;
	int ret, i = 0;

	td = new talk_data();
	
	dlg_clue.clue = td;

	ret = dlg_clue.DoModal();

	if(ret == IDOK)
	{
		lb = (CListBox*)GetDlgItem(IDC_CLUE_LIST);
		
		i = lb->GetCount();
		td = dlg_clue.clue;
		
		lb->InsertString(i, td->keywords);
		lb->SetItemDataPtr(i, td);
		
		if(quests->messages == NULL)
			quests->messages = td;
		else
		{
			for(tmp = quests->messages; tmp; tmp = tmp->next)
			{
				if(tmp->next == NULL) 
				{
					tmp->next = td;
					td->next = NULL;
					break;
				}
			}
		}
	}
	else if(ret == IDCANCEL)
		delete td;
}

void DlgQuestEdit::OnEditClue() 
{
	DlgQuestClue dlg_clue(this);
	talk_data *td;
	CListBox *lb;
	int i = -1, ret;

	lb = (CListBox*)GetDlgItem(IDC_CLUE_LIST);

	i = lb->GetCurSel();

	if(i == -1)
	{
		MessageBox("Please select a clue to edit.", "No Selection");
	} 
	else
	{
		td = (talk_data*)lb->GetItemDataPtr(i);
		
		dlg_clue.clue = td;

		ret = dlg_clue.DoModal();

		if(ret == IDOK)
		{
			lb->DeleteString(i);
			lb->InsertString(i, td->keywords);
			lb->SetItemDataPtr(i, td);
		}
	}
}

void DlgQuestEdit::OnDeleteClue() 
{
	int i = -1, ret;
	talk_data *clue, *next, *tmp;
	CListBox* lb;

	lb = (CListBox*)GetDlgItem(IDC_CLUE_LIST);

	i = lb->GetCurSel();

	if(i == -1)
	{
		MessageBox("Please select a clue to delete.", "No Selection");
	}

	ret = MessageBox("Delete this clue?", "Delete Item", MB_YESNO);

	clue = (talk_data*)lb->GetItemDataPtr(i);

	if(ret == IDYES)
	{
		if(clue == quests->messages)
		{
			quests->messages = clue->next;
			lb->DeleteString(i);
			
			delete clue;
		}
		else
		{
			for(tmp = quests->messages; tmp; tmp = next)
			{
				next = tmp->next;

				if(tmp->next == clue)
				{
					tmp->next = clue->next;
					lb->DeleteString(i);
					
					delete clue;
					
					break;
				}
			}
		}
	}
}

BOOL DlgQuestEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CListBox* lb;
	talk_data *clue;
	quest_data *qst;
	CString str;
	int i;

	for(qst = quests->quests, i = 0; qst; qst = qst->next, i++)
	{
		lb = (CListBox*)GetDlgItem(IDC_QUEST_LIST);
		
		if(qst->complete != "")
			lb->InsertString(i, qst->complete);
		else
		{
			str.Format("Quest %d", i);
			lb->InsertString(i, str);
		}

		lb->SetItemDataPtr(i, qst);
	}
	
	for(clue = quests->messages, i=0; clue; clue = clue->next, i++)
	{
		lb = (CListBox*)GetDlgItem(IDC_CLUE_LIST);
		lb->InsertString(i, clue->keywords);
		lb->SetItemDataPtr(i, clue);
	}


	return TRUE; 
}

void DlgQuestEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL DlgQuestEdit::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
	//	switch(pMsg->wParam)
	//	{
	//	case VK_DELETE:
	//		OnDeleteClue();
	//		break;
	//	case VK_RETURN:
	//		OnEditClue();
	//		break;
	//	}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
