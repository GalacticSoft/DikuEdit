#if !defined(AFX_DLGPROGEDIT_H__36CE08D1_0A5C_429C_A7CE_094B1772233B__INCLUDED_)
#define AFX_DLGPROGEDIT_H__36CE08D1_0A5C_429C_A7CE_094B1772233B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgEdit.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// DlgProgEdit dialog

#include "ColorEditWnd.h"

class DlgProgEdit : public CDialog
{
// Construction
public:
	DlgProgEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgProgEdit)
	//enum { IDD = IDD_DIALOG1 };
	//}}AFX_DATA

	ColorEditWnd *m_pColorWnd;
	CProgColorizer m_colorizer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgProgEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgProgEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROGEDIT_H__36CE08D1_0A5C_429C_A7CE_094B1772233B__INCLUDED_)
