#if !defined(AFX_DLGEQUIPMOB_H__021B8692_3095_4C09_8BE1_502FE9FD298F__INCLUDED_)
#define AFX_DLGEQUIPMOB_H__021B8692_3095_4C09_8BE1_502FE9FD298F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEquipMob.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEquipMob dialog

class DlgEquipMob : public CDialog
{
// Construction
public:
	DlgEquipMob(CWnd* pParent = NULL);   // standard constructor

	mob_index *mob;

	void UpdateEquip();
	void UpdateInv();

// Dialog Data
	//{{AFX_DATA(DlgEquipMob)
	enum { IDD = IDD_EQUIP_MOB };
	CListCtrl	m_ListInv;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEquipMob)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEquipMob)
	afx_msg void OnAddEquipItem();
	afx_msg void OnRemoveEquipItem();
	afx_msg void OnAddInvItem();
	afx_msg void OnRemoveInvItem();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEQUIPMOB_H__021B8692_3095_4C09_8BE1_502FE9FD298F__INCLUDED_)
