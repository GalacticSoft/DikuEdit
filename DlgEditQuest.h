#if !defined(AFX_DLGEDITQUEST_H__6CC7E18A_89A7_443B_BE32_0D710F4B9B52__INCLUDED_)
#define AFX_DLGEDITQUEST_H__6CC7E18A_89A7_443B_BE32_0D710F4B9B52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditQuest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditQuest dialog

class DlgEditQuest : public CDialog
{
// Construction
public:
	DlgEditQuest(CWnd* pParent = NULL);   // standard constructor

	quest_data *qst;

	// Dialog Data
	//{{AFX_DATA(DlgEditQuest)
	enum { IDD = IDD_EDIT_QUEST };
	CListCtrl	m_RewardList;
	CListCtrl	m_WantList;
	CString	complete;
	CString	dissapear;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditQuest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditQuest)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddWant();
	afx_msg void OnAddRewards();
	afx_msg void OnEditWants();
	afx_msg void OnDeleteWants();
	afx_msg void OnEditRewards();
	afx_msg void OnDeleteRewards();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITQUEST_H__6CC7E18A_89A7_443B_BE32_0D710F4B9B52__INCLUDED_)
