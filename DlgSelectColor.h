#if !defined(AFX_DLGSELECTCOLOR_H__A5E674EF_12CA_413E_8B10_3507A0EBD98D__INCLUDED_)
#define AFX_DLGSELECTCOLOR_H__A5E674EF_12CA_413E_8B10_3507A0EBD98D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSelectColor dialog

class DlgSelectColor : public CDialog
{
// Construction
public:
	DlgSelectColor(CWnd* pParent = NULL);   // standard constructor

	COLORREF	  def_color;
	COLORREF	  echo_color;

	CImageList iml;

// Dialog Data
	//{{AFX_DATA(DlgSelectColor)
	enum { IDD = IDD_COLORS };
	BOOL	m_def_dim;
	BOOL	m_echo_dim;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSelectColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSelectColor)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDefBlack();
	afx_msg void OnClickDefColor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickEchoColor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEchoDim();
	afx_msg void OnDefDim();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTCOLOR_H__A5E674EF_12CA_413E_8B10_3507A0EBD98D__INCLUDED_)
