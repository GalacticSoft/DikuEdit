#if !defined(AFX_DLGSELECTAFF_H__F7EE456E_5E38_4B75_BBDC_7BBAA234AD6E__INCLUDED_)
#define AFX_DLGSELECTAFF_H__F7EE456E_5E38_4B75_BBDC_7BBAA234AD6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectAff.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSelectAff dialog

class DlgSelectAff : public CDialog
{
// Construction
public:
	DlgSelectAff(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSelectAff)
	enum { IDD = IDD_SELECT_AFF };
	CListCtrl	aff_list;
	//}}AFX_DATA

	int type;
	int aff_flags[NUM_AFFECT_VECTORS];

	union
	{
		mob_data *mob;
		object_data *obj;
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSelectAff)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSelectAff)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickAffList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditBits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class MobAffectData {
public:
	char* name;
	const BITVECT_DATA *bv;
	bool in_use;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTAFF_H__F7EE456E_5E38_4B75_BBDC_7BBAA234AD6E__INCLUDED_)
