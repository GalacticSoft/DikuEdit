#if !defined(AFX_DLGEDITANTIFLAGS_H__7C415B8A_F51F_4417_B1EB_9D902F4B629F__INCLUDED_)
#define AFX_DLGEDITANTIFLAGS_H__7C415B8A_F51F_4417_B1EB_9D902F4B629F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditAntiFlags.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditAntiFlags dialog

class DlgEditAntiFlags : public CDialog
{
// Construction
public:
	DlgEditAntiFlags(CWnd* pParent = NULL);   // standard constructor
	int antis[2];

// Dialog Data
	//{{AFX_DATA(DlgEditAntiFlags)
	enum { IDD = IDD_EDIT_ANTI_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditAntiFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditAntiFlags)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITANTIFLAGS_H__7C415B8A_F51F_4417_B1EB_9D902F4B629F__INCLUDED_)
