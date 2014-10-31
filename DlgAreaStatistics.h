#if !defined(AFX_DLGAREASTATISTICS_H__27D903C5_A286_4DDC_A66C_75D9497F7A97__INCLUDED_)
#define AFX_DLGAREASTATISTICS_H__27D903C5_A286_4DDC_A66C_75D9497F7A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAreaStatistics.h : header file
//

#include "MobView.h"
#include "RoomView.h"
#include "ObjView.h"

/////////////////////////////////////////////////////////////////////////////
// DlgAreaStatistics dialog

class DlgAreaStatistics : public CDialog
{
// Construction
public:
	DlgAreaStatistics(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAreaStatistics)
	enum { IDD = IDD_STATISTICS };
	CTabCtrlSSL	StatTabs;
	//}}AFX_DATA
	MobView mob_tab;
	RoomView room_tab;
	ObjView obj_tab;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAreaStatistics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAreaStatistics)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREASTATISTICS_H__27D903C5_A286_4DDC_A66C_75D9497F7A97__INCLUDED_)
