#if !defined(AFX_EDITROOM_H__053543C6_A725_4355_926B_7D58A5460348__INCLUDED_)
#define AFX_EDITROOM_H__053543C6_A725_4355_926B_7D58A5460348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditRoom.h : header file
//
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// EditRoom dialog

class EditRoom : public CDialog
{
// Construction
public:
	EditRoom(CWnd* pParent = NULL);   // standard constructor
	room_data *room;
// Dialog Data
	//{{AFX_DATA(EditRoom)
	enum { IDD = IDD_EDIT_ROOM };
	int		current_dir;
	int		current_strength;
	CString	room_desc;
	CString	room_name;
	long	vnum;
	int		fall_chance;
	int		lighting;
	int		sector;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditRoom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditRoom)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditExits();
	afx_msg void OnRoomFlags();
	afx_msg void OnExtraDescs();
	virtual void OnCancel();
	afx_msg void OnDeleteRoom();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITROOM_H__053543C6_A725_4355_926B_7D58A5460348__INCLUDED_)
