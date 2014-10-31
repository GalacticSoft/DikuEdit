#if !defined(AFX_DLGABOUT_H__02E03FB3_0F04_4905_BA3B_509E47338ABE__INCLUDED_)
#define AFX_DLGABOUT_H__02E03FB3_0F04_4905_BA3B_509E47338ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAbout.h : header file
//
#include "MyHyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// DlgAbout dialog

class DlgAbout : public CDialog
{
// Construction
public:
	DlgAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAbout)
	enum { IDD = IDD_ABOUT };
	CMyHyperLink	link;
	CMyHyperLink	mail;
	CString	about;
	CString	company;
	CString	date;
	CString	name;
	CString	vdate;
	CString	version;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAbout)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGABOUT_H__02E03FB3_0F04_4905_BA3B_509E47338ABE__INCLUDED_)
