//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_TYPEVIEW_H__29843367_E813_4A71_81FD_1EE44152005D__INCLUDED_)
#define AFX_TYPEVIEW_H__29843367_E813_4A71_81FD_1EE44152005D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TypeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TypeView dialog

class TypeView : public CTabPageSSL
{
// Construction
public:
	TypeView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TypeView)
	enum { IDD = IDD_TYPE_VIEW };
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TypeView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TypeView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPEVIEW_H__29843367_E813_4A71_81FD_1EE44152005D__INCLUDED_)
