#if !defined(AFX_PROGEDITOR_H__301E92CC_E679_4E18_A3E1_C6383B4DE8D4__INCLUDED_)
#define AFX_PROGEDITOR_H__301E92CC_E679_4E18_A3E1_C6383B4DE8D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgEditor.h : header file
//
#include "SampleColorizer.h"
#include "ProgEditWnd.h"

/////////////////////////////////////////////////////////////////////////////
// ProgEditor dialog

class ProgEditor : public CDialog
{
// Construction
public:
	ProgEditor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ProgEditor)
	enum { IDD = IDD_PROG_EDIT };
	CComboBox	vars;
	CComboBox	templates;
	CComboBox	prog_types;
	CComboBox	keywords;
	CComboBox	functions;
	CComboBox	commands;
	CButton	frameRect;
	CString	filename;
	//}}AFX_DATA

	ProgEditWnd *prog_editor;
	CProgColorizer m_colorizer;
	
	ProgFile *prog;

	int type;

	union
	{
		mob_data *mob;
		object_data *obj;
	};

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	void InsertBribeTemplate();
	void InsertGreetTemplate();
	void InsertFightTemplate();
	void InsertDeathTemplate();
	void InsertRandTemplate();
	void InsertHPPercentTemplate();
	void InsertMoveTemplate();
	void InsertSpeechTemplate();
	void InsertActTemplate();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ProgEditor)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCommands();
	afx_msg void OnSelchangeKeywords();
	afx_msg void OnSelchangeFunctions();
	afx_msg void OnSelchangeVars();
	afx_msg void OnSelchangeTemplate();
	afx_msg void OnSelchangeProgType();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGEDITOR_H__301E92CC_E679_4E18_A3E1_C6383B4DE8D4__INCLUDED_)
