#if !defined(AFX_DLGEDITEXITS_H__F3650995_09C6_4AF1_BBC2_09752EA9AEF6__INCLUDED_)
#define AFX_DLGEDITEXITS_H__F3650995_09C6_4AF1_BBC2_09752EA9AEF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rooms.h"

class DlgEditExits : public CDialog
{
// Construction
public:
	DlgEditExits(CWnd* pParent = NULL);   // standard constructor
	exit_data *exits[MAX_DIR];
	
	int ex;
	int in_room;

	CBitmapButton key;
	
	// Dialog Data
	//{{AFX_DATA(DlgEditExits)
	enum { IDD = IDD_EDIT_EXITS };
	CNumericEdit m_ToRoom;
	CString	exit_desc;
	CString	exit_keyword;
	int		key_vnum;
	int		to_room;
	//}}AFX_DATA

	int CheckDoorBits();
	void SetDoorBits();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditExits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditExits)
	afx_msg void OnRoomList();
	afx_msg void OnKeyList();
	afx_msg void OnExitUp();
	afx_msg void OnExitNw();
	afx_msg void OnExitNorth();
	afx_msg void OnExitNe();
	afx_msg void OnExitWest();
	afx_msg void OnExitEast();
	afx_msg void OnExitSw();
	afx_msg void OnExitSouth();
	afx_msg void OnExitSe();
	afx_msg void OnExitDown();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnReverseExit();
	afx_msg void OnGuardFlags();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITEXITS_H__F3650995_09C6_4AF1_BBC2_09752EA9AEF6__INCLUDED_)
