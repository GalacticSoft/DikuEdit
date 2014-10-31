#if !defined(AFX_CANNONBUILDER_H__F5086044_EDEC_472E_9639_D6CDE90E593F__INCLUDED_)
#define AFX_CANNONBUILDER_H__F5086044_EDEC_472E_9639_D6CDE90E593F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CannonBuilder.h : header file
//
#include "ShipUpgrades.h"
#include "ShipwrightList.h"

/////////////////////////////////////////////////////////////////////////////
// CannonBuilder dialog

class CannonBuilder : public CDialog
{
// Construction
public:
	CannonBuilder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CannonBuilder)
	enum { IDD = IDD_CANNON_BUILDER };
	CListCtrl	Shipwrights;
	int		accuracy;
	CString	name;
	int		vnum;
	int		price;
	int		power;
	int		range;
	CString	filename;
	//}}AFX_DATA

	Cannon *cannon;
	
	ShipwrightList shop_list;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CannonBuilder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CannonBuilder)
		virtual void OnOK();
		virtual void OnRemove();
		virtual void OnAdd();
		virtual void OnCalculator();
		virtual void OnObjectList();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANNONBUILDER_H__F5086044_EDEC_472E_9639_D6CDE90E593F__INCLUDED_)
