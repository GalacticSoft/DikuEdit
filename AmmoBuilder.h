#if !defined(AFX_AMMOBUILDER_H__2CA2B7A4_633A_447D_B295_724D08632FF6__INCLUDED_)
#define AFX_AMMOBUILDER_H__2CA2B7A4_633A_447D_B295_724D08632FF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmmoBuilder.h : header file
//
#include "ShipUpgrades.h"
#include "ShipwrightList.h"
/////////////////////////////////////////////////////////////////////////////
// AmmoBuilder dialog

class AmmoBuilder : public CDialog
{
// Construction
public:
	AmmoBuilder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AmmoBuilder)
	enum { IDD = IDD_AMMO_BUILDER };
	CListCtrl	Shipwrights;
	int		crew;
	int		hull;
	CString	name;
	int		price;
	int		quantity;
	int		range;
	int		sail;
	CString	filename;
	//}}AFX_DATA

	Ammo *ammo;
	ShipwrightList ammo_shops;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AmmoBuilder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AmmoBuilder)
	virtual BOOL OnInitDialog();
	afx_msg void OnCalc();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMMOBUILDER_H__2CA2B7A4_633A_447D_B295_724D08632FF6__INCLUDED_)
