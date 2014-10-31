#if !defined(AFX_DLGEQUIPITEM_H__8841C4F8_D2DA_4CE5_92AF_4F7C933DDB6A__INCLUDED_)
#define AFX_DLGEQUIPITEM_H__8841C4F8_D2DA_4CE5_92AF_4F7C933DDB6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEquipItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEquipItem dialog

class DlgEquipItem : public CDialog
{
// Construction
public:
	DlgEquipItem(CWnd* pParent = NULL);   // standard constructor
	
	int race; //race of mob being equiped

	obj_index *obj; //newly equiped item

// Dialog Data
	//{{AFX_DATA(DlgEquipItem)
	enum { IDD = IDD_ADD_EQ_ITEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEquipItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEquipItem)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelChangeEquipLoc();
	afx_msg void OnDblclkEqList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEQUIPITEM_H__8841C4F8_D2DA_4CE5_92AF_4F7C933DDB6A__INCLUDED_)
