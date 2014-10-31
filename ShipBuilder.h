#if !defined(AFX_ShipBuilder_H__29DFA066_FD7F_47D0_A1F3_91EF1AAD57CC__INCLUDED_)
#define AFX_ShipBuilder_H__29DFA066_FD7F_47D0_A1F3_91EF1AAD57CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShipBuilder.h : header file
//
#include "TabCtrlSSL.h"
#include "ShipUpgrades.h"
#include "AmmoView.h"
#include "CannonView.h"
#include "CrewView.h"

/////////////////////////////////////////////////////////////////////////////
// ShipBuilder dialog

class ShipBuilder : public CDialog
{
// Construction
public:
	ShipBuilder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShipBuilder)
	enum { IDD = IDD_SHIPBUILDER };
	CTabCtrlSSL	BuilderTabs;
	//}}AFX_DATA

	AmmoView ammo_tab;
	CrewView crew_tab;
	CannonView cannon_tab;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShipBuilder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void CreateCannon();
	void EditCannon();
	void DeleteCannon();

	void CreateAmmo();
	void EditAmmo();
	void DeleteAmmo();

	void CreateCrew();
	void EditCrew();
	void DeleteCrew();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShipBuilder)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCreate();
	virtual void OnEdit();
	virtual void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ShipBuilder_H__29DFA066_FD7F_47D0_A1F3_91EF1AAD57CC__INCLUDED_)
