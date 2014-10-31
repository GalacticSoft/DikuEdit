#if !defined(AFX_DLGEXTRADESC_H__3622EABE_DFD1_45CA_8A8B_0AEBEA630F18__INCLUDED_)
#define AFX_DLGEXTRADESC_H__3622EABE_DFD1_45CA_8A8B_0AEBEA630F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExtraDesc.h : header file
//
#include "Rooms.h"

class DlgExtraDesc : public CDialog
{
// Construction
public:
	DlgExtraDesc(CWnd* pParent = NULL);   // standard constructor
	
	extra_desc *first_new_ed;
	extra_desc *cur_ed;
	extra_desc *last_new_ed;
	
	extra_desc *old_ed_list;
	extra_desc *last_old_ed;

	void DlgExtraDesc::FocusOnKeyword();

	// Dialog Data
	//{{AFX_DATA(DlgExtraDesc)
	enum { IDD = IDD_EXTRA_DESC };
	CString	ed;
	CString	keywords;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgExtraDesc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgExtraDesc)
	afx_msg void OnPrevDesc();
	afx_msg void OnAddDesc();
	afx_msg void OnDeleteDesc();
	afx_msg void OnDescNext();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnFirstEd();
	afx_msg void OnLastEd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTRADESC_H__3622EABE_DFD1_45CA_8A8B_0AEBEA630F18__INCLUDED_)
