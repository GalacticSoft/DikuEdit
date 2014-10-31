#if !defined(AFX_CREWBUILDER_H__DC85574D_F09B_4A56_8432_C5678FC2F700__INCLUDED_)
#define AFX_CREWBUILDER_H__DC85574D_F09B_4A56_8432_C5678FC2F700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrewBuilder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CrewBuilder dialog
#include "ShipUpgrades.h"
#include "ShipwrightList.h"

class CrewBuilder : public CDialog
{
// Construction
public:
	CrewBuilder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CrewBuilder)
	enum { IDD = IDD_CREW_BUILDER };
	CListCtrl	Shipwrights;
	int		atk;
	int		def;
	int		frt;
	int		gun;
	int		leader;
	int		max_atk;
	int		max_def;
	int		max_gun;
	int		max_sail;
	int		member;
	int		max_men;
	CString	name;
	int		price;
	int		sail;
	int		spd;
	int		str;
	CString	filename;
	//}}AFX_DATA

	Crew *crew;
	ShipwrightList shop_list;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CrewBuilder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CrewBuilder)
	afx_msg void OnMemberList();
	afx_msg void OnLeaderList();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnCalc();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREWBUILDER_H__DC85574D_F09B_4A56_8432_C5678FC2F700__INCLUDED_)
