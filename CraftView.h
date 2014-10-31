//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_CRAFTVIEW_H__FE7F6DEF_C6EA_4F6E_B37B_4ED6EDB6ECE8__INCLUDED_)
#define AFX_CRAFTVIEW_H__FE7F6DEF_C6EA_4F6E_B37B_4ED6EDB6ECE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CraftView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CraftView dialog

class CraftView : public CTabPageSSL
{
// Construction
public:
	CraftView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CraftView)
	enum { IDD = IDD_CRAFT_VIEW };
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CraftView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CraftView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRAFTVIEW_H__FE7F6DEF_C6EA_4F6E_B37B_4ED6EDB6ECE8__INCLUDED_)
