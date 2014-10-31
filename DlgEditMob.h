#if !defined(AFX_DLGEDITMOB_H__66C52E00_9750_490C_BBB6_2E4026DE18F5__INCLUDED_)
#define AFX_DLGEDITMOB_H__66C52E00_9750_490C_BBB6_2E4026DE18F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NumericEdit.h"

class mob_data;

class DlgEditMob : public CDialog
{
// Construction
public:
	DlgEditMob(CWnd* pParent = NULL);   // standard constructor
	
	mob_data *mob;

// Dialog Data
	//{{AFX_DATA(DlgEditMob)
	enum { IDD = IDD_EDIT_MOB };
	CNumericEdit	m_Align;
	int		align;
	int		mob_class;
	CString	mob_desc;
	CString	mob_keywords;
	int		level;
	CString	mob_long;
	int		position;
	int		race;
	int		sex;
	CString	mob_short;
	int		size;
	int		vnum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditMob)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditMob)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	virtual void OnCancel();
	afx_msg void OnMobShop();
	afx_msg void OnMobQuest();
	afx_msg void OnMobAct();
	afx_msg void OnMobAffects();
	afx_msg void OnQuests();
	afx_msg void OnEditProgs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITMOB_H__66C52E00_9750_490C_BBB6_2E4026DE18F5__INCLUDED_)
