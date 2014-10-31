#if !defined(AFX_DLGQUESTCLUE_H__3F182170_6B4C_4899_ADF6_8E0B6DF43BF0__INCLUDED_)
#define AFX_DLGQUESTCLUE_H__3F182170_6B4C_4899_ADF6_8E0B6DF43BF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQuestClue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgQuestClue dialog

class DlgQuestClue : public CDialog
{
// Construction
public:
	DlgQuestClue(CWnd* pParent = NULL);   // standard constructor

	talk_data *clue;

// Dialog Data
	//{{AFX_DATA(DlgQuestClue)
	enum { IDD = IDD_QUEST_CLUE };
	CString	keywords;
	CString	message;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgQuestClue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgQuestClue)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUESTCLUE_H__3F182170_6B4C_4899_ADF6_8E0B6DF43BF0__INCLUDED_)
