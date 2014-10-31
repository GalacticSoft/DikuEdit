#if !defined(AFX_DLGEDITSHOP_H__DA58BE69_7437_45A8_8A79_9FD18381F671__INCLUDED_)
#define AFX_DLGEDITSHOP_H__DA58BE69_7437_45A8_8A79_9FD18381F671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class shop_data;

class DlgEditShop : public CDialog
{
// Construction
public:
	DlgEditShop(CWnd* pParent = NULL);   // standard constructor

	shop_data *shop;

// Dialog Data
	//{{AFX_DATA(DlgEditShop)
	enum { IDD = IDD_EDIT_SHOP };
	CListCtrl	m_ShopList;
	int		buy_profit;
	int		closes;
	int		opens;
	int		sale_profit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditShop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditShop)
	afx_msg void OnAddItem();
	virtual void OnOK();
	afx_msg void OnDeleteShop();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTypeList();
	afx_msg void OnRemoveItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITSHOP_H__DA58BE69_7437_45A8_8A79_9FD18381F671__INCLUDED_)
