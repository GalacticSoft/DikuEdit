#if !defined(AFX_DLGEDITCONTENTS_H__3FD608F0_E5F9_42A7_A920_18BB90839B27__INCLUDED_)
#define AFX_DLGEDITCONTENTS_H__3FD608F0_E5F9_42A7_A920_18BB90839B27__INCLUDED_

#include "Objects.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditContents.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditContents dialog

class DlgEditContents : public CDialog
{
// Construction
public:
	obj_index *obj;
	DlgEditContents(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEditContents)
	enum { IDD = IDD_EDIT_CONTENTS };
	CListCtrl	m_ObjList;
	CListCtrl	m_InvList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditContents)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditContents)
	afx_msg void OnAddObj();
	afx_msg void OnRemoveObj();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeContents();
	afx_msg void OnSelchangeObjectList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITCONTENTS_H__3FD608F0_E5F9_42A7_A920_18BB90839B27__INCLUDED_)
