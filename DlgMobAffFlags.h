#if !defined(AFX_DLGMOBAFFFLAGS_H__60589919_7D23_4ADB_B9E5_77FFAA5923A9__INCLUDED_)
#define AFX_DLGMOBAFFFLAGS_H__60589919_7D23_4ADB_B9E5_77FFAA5923A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mobs.h"
#include "resource.h"

class DlgMobAffFlags : public CDialog
{
	
// Construction
public:
	DlgMobAffFlags(CWnd* pParent = NULL);   // standard constructor

	int aff_flags[NUM_AFFECT_VECTORS];

// Dialog Data
	//{{AFX_DATA(DlgMobAffFlags)
	enum { IDD = IDD_EDIT_MOB_AFFECTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgMobAffFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgMobAffFlags)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOBAFFFLAGS_H__60589919_7D23_4ADB_B9E5_77FFAA5923A9__INCLUDED_)
