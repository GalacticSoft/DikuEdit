#if !defined(AFX_DLGEDITOBJECT_H__E51D746D_A5F5_4822_A3BD_EF52ECB79171__INCLUDED_)
#define AFX_DLGEDITOBJECT_H__E51D746D_A5F5_4822_A3BD_EF52ECB79171__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Objects.h"

class DlgEditObject : public CDialog
{
	// Construction
public:
	DlgEditObject(CWnd* pParent = NULL);   // standard constructor
	
	object_data *object;

	// Dialog Data
	//{{AFX_DATA(DlgEditObject)
	enum { IDD = IDD_EDIT_OBJ };
	CNumericEdit	m_Value6;
	CNumericEdit	m_Value7;
	CNumericEdit	m_Value8;
	CNumericEdit	m_Value4;
	CNumericEdit	m_Value5;
	CNumericEdit	m_Value3;
	CNumericEdit	m_Value2;
	CNumericEdit	m_Value1;
	CNumericEdit	m_Apply2;
	CNumericEdit	m_Apply1;
	int		condition;
	int		crafts;
	CString	keywords;
	CString	long_desc;
	int		material;
	CString	short_desc;
	int		size;
	int		type;
	int		vnum;
	int		volume;
	int		weight;
	int		apply_loc1;
	int		apply_val2;
	int		apply_val1;
	int		apply_loc2;
	//}}AFX_DATA

	int		values[MAX_ITEM_VALUE];
	int     wear_flags;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void ValueStrings(int obj_type);
	void ValueInput(int obj_type);
	void ValueData(int i, int obj_type, CComboBox *cb);

	void SetValues();
	void SaveValues();

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditObject)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnObjAff();
	afx_msg void OnExtraFlags();
	afx_msg void OnAntiFlags();
	afx_msg void OnObjExtraDesc();
	afx_msg void OnEditContents();
	afx_msg void OnObjLoad();
	afx_msg void OnSelchangeObjType();
	virtual void OnCancel();
	afx_msg void OnTrap();
	afx_msg void OnEditProgs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITOBJECT_H__E51D746D_A5F5_4822_A3BD_EF52ECB79171__INCLUDED_)
