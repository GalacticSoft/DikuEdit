#if !defined(AFX_DLGCALCCOINS_H__32F05444_4137_4FDA_AAD1_7923B5CFA3E0__INCLUDED_)
#define AFX_DLGCALCCOINS_H__32F05444_4137_4FDA_AAD1_7923B5CFA3E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalcCoins.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCalcCoins dialog

class DlgCalcCoins : public CDialog
{
// Construction
public:
	DlgCalcCoins(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCalcCoins)
	enum { IDD = IDD_COINS };
	int		platinum;
	int		copper;
	int		gold;
	int		silver;
	int		total;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCalcCoins)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCalcCoins)
	virtual void OnOK();
	afx_msg void OnCalculate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALCCOINS_H__32F05444_4137_4FDA_AAD1_7923B5CFA3E0__INCLUDED_)
