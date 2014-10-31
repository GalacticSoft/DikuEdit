#if !defined(AFX_DLGSPELLS_H__3E759970_4CB5_4D69_850D_634C7D1CC206__INCLUDED_)
#define AFX_DLGSPELLS_H__3E759970_4CB5_4D69_850D_634C7D1CC206__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpells.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSpells dialog

class DlgSpells : public CDialog
{
// Construction
public:
	DlgSpells(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSpells)
	enum { IDD = IDD_SPELLS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	int spell;
	int type;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSpells)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSpells)
	afx_msg void OnSelchangeType();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSpells();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPELLS_H__3E759970_4CB5_4D69_850D_634C7D1CC206__INCLUDED_)
