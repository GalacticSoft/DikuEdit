#if !defined(AFX_DLGGUARDFLAGS_H__C3C052A2_0479_4ECD_A757_4DC2BF23C3F4__INCLUDED_)
#define AFX_DLGGUARDFLAGS_H__C3C052A2_0479_4ECD_A757_4DC2BF23C3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGuardFlags.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGuardFlags dialog

class DlgGuardFlags : public CDialog
{
// Construction
public:
	DlgGuardFlags(CWnd* pParent = NULL);   // standard constructor
	
	unsigned int flags;

// Dialog Data
	//{{AFX_DATA(DlgGuardFlags)
	enum { IDD = IDD_GUARD_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	void SetFlags();
	int GetFlags();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGuardFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGuardFlags)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGUARDFLAGS_H__C3C052A2_0479_4ECD_A757_4DC2BF23C3F4__INCLUDED_)
