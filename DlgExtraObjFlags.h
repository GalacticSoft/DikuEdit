#if !defined(AFX_DLGEXTRAOBJFLAGS_H__BADDA0BB_5777_49CF_8646_92F5BFCEA36E__INCLUDED_)
#define AFX_DLGEXTRAOBJFLAGS_H__BADDA0BB_5777_49CF_8646_92F5BFCEA36E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Objects.h"

class DlgExtraObjFlags : public CDialog
{
// Construction
public:
	DlgExtraObjFlags(CWnd* pParent = NULL);   // standard constructor

	object_data *obj;
	int type;
	int value;

// Dialog Data
	//{{AFX_DATA(DlgExtraObjFlags)
	enum { IDD = IDD_OBJ_EXTRA_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgExtraObjFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgExtraObjFlags)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTRAOBJFLAGS_H__BADDA0BB_5777_49CF_8646_92F5BFCEA36E__INCLUDED_)
