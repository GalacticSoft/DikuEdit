//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_CLASSVIEW_H__F384A92B_1928_4DC1_8625_789FDE4B97B0__INCLUDED_)
#define AFX_CLASSVIEW_H__F384A92B_1928_4DC1_8625_789FDE4B97B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ClassView dialog

class ClassView : public CTabPageSSL
{
// Construction
public:
	ClassView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ClassView)
	enum { IDD = IDD_CLASS_STATS };
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ClassView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSVIEW_H__F384A92B_1928_4DC1_8625_789FDE4B97B0__INCLUDED_)
