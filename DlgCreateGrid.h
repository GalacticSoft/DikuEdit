#if !defined(AFX_DLGCREATEGRID_H__A26B93FD_63AA_4641_83AF_59ECE5D2D41E__INCLUDED_)
#define AFX_DLGCREATEGRID_H__A26B93FD_63AA_4641_83AF_59ECE5D2D41E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCreateGrid dialog

class DlgCreateGrid : public CDialog
{
// Construction
public:
	DlgCreateGrid(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCreateGrid)
	enum { IDD = IDD_CREATE_GRID };
	int		sizez;
	int		sizex;
	int		sizey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCreateGrid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCreateGrid)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATEGRID_H__A26B93FD_63AA_4641_83AF_59ECE5D2D41E__INCLUDED_)
