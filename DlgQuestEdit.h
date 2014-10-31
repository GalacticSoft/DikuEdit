#if !defined(AFX_DLGQUESTEDIT_H__975DB53A_3B60_4245_950B_5EBF0ADEBFA1__INCLUDED_)
#define AFX_DLGQUESTEDIT_H__975DB53A_3B60_4245_950B_5EBF0ADEBFA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQuestEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgQuestEdit dialog

class DlgQuestEdit : public CDialog
{
// Construction
public:
	DlgQuestEdit(CWnd* pParent = NULL);   // standard constructor

	quest_index_data * quests;

// Dialog Data
	//{{AFX_DATA(DlgQuestEdit)
	enum { IDD = IDD_QUEST_EDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgQuestEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgQuestEdit)
	afx_msg void OnEditQuest();
	afx_msg void OnNewQuest();
	afx_msg void OnDeleteQuest();
	afx_msg void OnEditRewards();
	afx_msg void OnEditWants();
	afx_msg void OnNewClue();
	afx_msg void OnEditClue();
	afx_msg void OnDeleteClue();
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUESTEDIT_H__975DB53A_3B60_4245_950B_5EBF0ADEBFA1__INCLUDED_)
