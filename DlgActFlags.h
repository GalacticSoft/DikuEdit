#if !defined(AFX_DLGACTFLAGS_H__615CA943_961E_44AE_A591_8984017947C6__INCLUDED_)
#define AFX_DLGACTFLAGS_H__615CA943_961E_44AE_A591_8984017947C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class DlgActFlags : public CDialog
{
// Construction
public:
	DlgActFlags(CWnd* pParent = NULL);   // standard constructor

	int act;

// Dialog Data
	//{{AFX_DATA(DlgActFlags)
	enum { IDD = IDD_ACT_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgActFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgActFlags)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACTFLAGS_H__615CA943_961E_44AE_A591_8984017947C6__INCLUDED_)
