#if !defined(AFX_CANNONVIEW_H__8441B5CE_2857_4C5E_943B_677C7D1F3AA8__INCLUDED_)
#define AFX_CANNONVIEW_H__8441B5CE_2857_4C5E_943B_677C7D1F3AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CannonView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CannonView dialog

class CannonView : public CTabPageSSL
{
// Construction
public:
	CannonView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CannonView)
	enum { IDD = IDD_CANNON_TAB };
	CListCtrl	m_CannonList;
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CannonView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CannonView)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkCannonList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANNONVIEW_H__8441B5CE_2857_4C5E_943B_677C7D1F3AA8__INCLUDED_)
