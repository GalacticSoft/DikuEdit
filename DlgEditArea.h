#if !defined(AFX_DLGEDITAREA_H__0CFCB6BE_0BF6_42D6_A121_E8C5FB30A5A1__INCLUDED_)
#define AFX_DLGEDITAREA_H__0CFCB6BE_0BF6_42D6_A121_E8C5FB30A5A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditArea dialog

class DlgEditArea : public CDialog
{
// Construction
public:
	DlgEditArea(CWnd* pParent = NULL);   // standard constructor

	area_data *area;

// Dialog Data
	//{{AFX_DATA(DlgEditArea)
	enum { IDD = IDD_EDIT_AREA };
	CString	author;
	int		high_level;
	int		defender_vnum;
	int		barracks_vnum;
	int		jail_vnum;
	int		judge_vnum;
	int		low_level;
	int		high_reset;
	CString	reset_message;
	CString	filename;
	int		squads;
	int		starting_vnum;
	int		justice;
	int		reset_mode;
	CString	name;
	int		low_reset;
	//}}AFX_DATA

	int area_flags;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditArea)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeJustice();
	afx_msg void OnSelchangeResetMode();
	afx_msg void OnDefenderList();
	afx_msg void OnBarracksList();
	afx_msg void OnJailList();
	afx_msg void OnJudgeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITAREA_H__0CFCB6BE_0BF6_42D6_A121_E8C5FB30A5A1__INCLUDED_)
