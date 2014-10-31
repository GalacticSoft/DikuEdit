#if !defined(AFX_DLGDIRECTIONS_H__EC0A2822_9EED_43CB_8A4A_33B52AF1ED12__INCLUDED_)
#define AFX_DLGDIRECTIONS_H__EC0A2822_9EED_43CB_8A4A_33B52AF1ED12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDirections.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgDirections dialog

class DlgDirections : public CDialog
{
// Construction
public:
	DlgDirections(CWnd* pParent = NULL);   // standard constructor

	CBitmapButton north;
	CBitmapButton south;
	CBitmapButton west;
	CBitmapButton east;
	CBitmapButton northwest;
	CBitmapButton northeast;
	CBitmapButton southwest;
	CBitmapButton southeast;
	CBitmapButton up;
	CBitmapButton down;
	CBitmapButton look;

// Dialog Data
	//{{AFX_DATA(DlgDirections)
	enum { IDD = IDD_DIRECTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgDirections)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgDirections)
	afx_msg void OnUp();
	afx_msg void OnNorthwest();
	afx_msg void OnNorth();
	afx_msg void OnNortheast();
	afx_msg void OnWest();
	afx_msg void OnLook();
	afx_msg void OnEast();
	afx_msg void OnSouthwest();
	afx_msg void OnSouth();
	afx_msg void OnSoutheast();
	afx_msg void OnDown();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDIRECTIONS_H__EC0A2822_9EED_43CB_8A4A_33B52AF1ED12__INCLUDED_)
