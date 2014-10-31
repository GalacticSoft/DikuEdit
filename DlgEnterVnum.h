#if !defined(AFX_DLGENTERVNUM_H__8124B755_C3FD_4F84_8034_52EF9283D972__INCLUDED_)
#define AFX_DLGENTERVNUM_H__8124B755_C3FD_4F84_8034_52EF9283D972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class DlgEnterVnum : public CDialog
{
// Construction
public:
	DlgEnterVnum(CWnd* pParent = NULL);   // standard constructor
	
	int type;

	// Dialog Data
	//{{AFX_DATA(DlgEnterVnum)
	enum { IDD = IDD_ENTER_VNUM };
	int		vnum;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEnterVnum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEnterVnum)
	afx_msg void OnSeletectFromList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENTERVNUM_H__8124B755_C3FD_4F84_8034_52EF9283D972__INCLUDED_)
