#if !defined(AFX_DLGEDITFRIENDS_H__7EE582E3_D6DC_4C00_8436_B9958B5927AB__INCLUDED_)
#define AFX_DLGEDITFRIENDS_H__7EE582E3_D6DC_4C00_8436_B9958B5927AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditFriends.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditFriends dialog

class DlgEditFriends : public CDialog
{
// Construction
public:
	DlgEditFriends(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEditFriends)
	enum { IDD = IDD_EDIT_FRIENDS };
	CListCtrl	m_FolList;
	CListCtrl	m_PeopleList;
	//}}AFX_DATA

	mob_index *mob;
	mob_index *mount;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditFriends)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditFriends)
	afx_msg void OnAddFollower();
	afx_msg void OnRemoveFollower();
	afx_msg void OnDblclkFolList();
	afx_msg void OnDblclkMobList();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnMount();
	afx_msg void OnDismount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITFRIENDS_H__7EE582E3_D6DC_4C00_8436_B9958B5927AB__INCLUDED_)
