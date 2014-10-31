//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_MATERIALVIEW_H__54BDA1E2_BB1C_4D4A_B0AB_0ED4D8DD3584__INCLUDED_)
#define AFX_MATERIALVIEW_H__54BDA1E2_BB1C_4D4A_B0AB_0ED4D8DD3584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MaterialView dialog

class MaterialView : public CTabPageSSL
{
// Construction
public:
	MaterialView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MaterialView)
	enum { IDD = IDD_MAT_VIEW };
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MaterialView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MaterialView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALVIEW_H__54BDA1E2_BB1C_4D4A_B0AB_0ED4D8DD3584__INCLUDED_)
