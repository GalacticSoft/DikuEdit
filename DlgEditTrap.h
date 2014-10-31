#if !defined(AFX_DLGEDITTRAP_H__21F38FDE_9B6A_422B_9219_80C1D728E406__INCLUDED_)
#define AFX_DLGEDITTRAP_H__21F38FDE_9B6A_422B_9219_80C1D728E406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditTrap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditTrap dialog

class DlgEditTrap : public CDialog
{
// Construction
public:
	DlgEditTrap(CWnd* pParent = NULL);   // standard constructor
	object_data *obj;
	int trigger;
// Dialog Data
	//{{AFX_DATA(DlgEditTrap)
	enum { IDD = IDD_EDIT_TRAP };
	CListCtrl	m_TrigList;
	int		charges;
	int		damage_type;
	int		level;
	int		percent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditTrap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditTrap)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITTRAP_H__21F38FDE_9B6A_422B_9219_80C1D728E406__INCLUDED_)
