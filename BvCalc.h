// bv calcutatorDlg.h : header file
//
#include "Resource.h"
#if !defined(AFX_BVCALCUTATORDLG_H__6BDFE3B7_7CE9_4819_B601_E17115545297__INCLUDED_)
#define AFX_BVCALCUTATORDLG_H__6BDFE3B7_7CE9_4819_B601_E17115545297__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBvcalcutatorDlg dialog

class CBvcalcutatorDlg : public CDialog
{
// Construction
public:
	CBvcalcutatorDlg(CWnd* pParent = NULL);	// standard constructor
	bool input;
	
	int value;

// Dialog Data
	//{{AFX_DATA(CBvcalcutatorDlg)
	enum { IDD = IDD_BVCALCUTATOR_DIALOG };
	int		bits;
	//}}AFX_DATA
	void Clear();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBvcalcutatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	HICON m_hIcon;
	void CBvcalcutatorDlg::SetBit(int bit);
	
	
	void ClearInput();

	// Generated message map functions
	//{{AFX_MSG(CBvcalcutatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBv00();
	afx_msg void OnConvert();
	afx_msg void OnOk();
	afx_msg void OnBv01();
	afx_msg void OnBv02();
	afx_msg void OnBv03();
	afx_msg void OnBv04();
	afx_msg void OnBv05();
	afx_msg void OnBv06();
	afx_msg void OnBv07();
	afx_msg void OnBv08();
	afx_msg void OnBv09();
	afx_msg void OnBv10();
	afx_msg void OnBv11();
	afx_msg void OnBv12();
	afx_msg void OnBv13();
	afx_msg void OnBv14();
	afx_msg void OnBv15();
	afx_msg void OnBv16();
	afx_msg void OnBv17();
	afx_msg void OnBv18();
	afx_msg void OnBv19();
	afx_msg void OnBv20();
	afx_msg void OnBv21();
	afx_msg void OnBv22();
	afx_msg void OnBv23();
	afx_msg void OnBv24();
	afx_msg void OnBv25();
	afx_msg void OnBv26();
	afx_msg void OnBv27();
	afx_msg void OnBv28();
	afx_msg void OnBv29();
	afx_msg void OnBv30();
	afx_msg void OnClear();
	afx_msg void OnChangeText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BVCALCUTATORDLG_H__6BDFE3B7_7CE9_4819_B601_E17115545297__INCLUDED_)
