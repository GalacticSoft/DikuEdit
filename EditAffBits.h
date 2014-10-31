#if !defined(AFX_EDITAFFBITS_H__6AFB762E_DE2C_4D75_B1DC_1365243AE793__INCLUDED_)
#define AFX_EDITAFFBITS_H__6AFB762E_DE2C_4D75_B1DC_1365243AE793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditAffBits.h : header file
//

#include "BvCalc.h"

/////////////////////////////////////////////////////////////////////////////
// EditAffBits dialog

class EditAffBits : public CDialog
{
// Construction
public:
	EditAffBits(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditAffBits)
	enum { IDD = IDD_EDIT_AFF_BITS };
	int		val1;
	int		val2;
	int		val3;
	int		val4;
	int		val5;
	int		val6;
	//}}AFX_DATA

	int affs[NUM_AFFECT_VECTORS];
	CBvcalcutatorDlg calc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditAffBits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditAffBits)
	afx_msg void OnBitcalc();
	afx_msg void OnBitcalc2();
	afx_msg void OnBitcalc3();
	afx_msg void OnBitcalc4();
	afx_msg void OnBitcalc5();
	afx_msg void OnBitcalc6();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITAFFBITS_H__6AFB762E_DE2C_4D75_B1DC_1365243AE793__INCLUDED_)
