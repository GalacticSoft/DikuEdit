#if !defined(AFX_DLGSAVE_H__F32B20D3_00C5_497C_89B5_E86EADE83476__INCLUDED_)
#define AFX_DLGSAVE_H__F32B20D3_00C5_497C_89B5_E86EADE83476__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSave dialog

class DlgSave : public CDialog
{
// Construction
public:
	DlgSave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSave)
	enum { IDD = IDD_SAVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSave)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSAVE_H__F32B20D3_00C5_497C_89B5_E86EADE83476__INCLUDED_)
