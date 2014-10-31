#if !defined(AFX_AMMOVIEW_H__CFB05294_48C9_4AD1_A61C_A3C6B8785071__INCLUDED_)
#define AFX_AMMOVIEW_H__CFB05294_48C9_4AD1_A61C_A3C6B8785071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmmoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AmmoView dialog

class AmmoView : public CTabPageSSL
{
// Construction
public:
	AmmoView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AmmoView)
	enum { IDD = IDD_AMMO_TAB };
	CListCtrl	AmmoList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AmmoView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AmmoView)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkAmmoList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMMOVIEW_H__CFB05294_48C9_4AD1_A61C_A3C6B8785071__INCLUDED_)
