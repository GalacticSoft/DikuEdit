#if !defined(AFX_CTRLTOOLBAR_H__9BEA136F_B300_406C_B25E_DBE05DF54852__INCLUDED_)
#define AFX_CTRLTOOLBAR_H__9BEA136F_B300_406C_B25E_DBE05DF54852__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtrlToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtrlToolBar window
class CCtrlToolBar : public CToolBar
{
// Construction
public:
	CCtrlToolBar();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlToolBar)
	//}}AFX_VIRTUAL

	virtual ~CCtrlToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCtrlToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLTOOLBAR_H__9BEA136F_B300_406C_B25E_DBE05DF54852__INCLUDED_)
