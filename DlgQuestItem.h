#if !defined(AFX_DLGQUESTITEM_H__FB11A8EA_8885_4385_A947_9F89528B3E0E__INCLUDED_)
#define AFX_DLGQUESTITEM_H__FB11A8EA_8885_4385_A947_9F89528B3E0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQuestItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgQuestItem dialog

class DlgQuestItem : public CDialog
{
// Construction
public:
	DlgQuestItem(CWnd* pParent = NULL);   // standard constructor

	quest_item *item;

	int type;

// Dialog Data
	//{{AFX_DATA(DlgQuestItem)
	enum { IDD = IDD_ADD_QUEST_ITEM };
	int		qst_type;
	int		value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgQuestItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgQuestItem)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeQuestType();
	afx_msg void OnGetVnum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUESTITEM_H__FB11A8EA_8885_4385_A947_9F89528B3E0E__INCLUDED_)
