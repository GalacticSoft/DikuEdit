#if !defined(AFX_DLGVNUMLIST_H__37D7F025_AD76_45D9_BE57_C2EBC9B78E05__INCLUDED_)
#define AFX_DLGVNUMLIST_H__37D7F025_AD76_45D9_BE57_C2EBC9B78E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DlgVnumList : public CDialog
{
// Construction
public:
	DlgVnumList(CWnd* pParent = NULL);   // standard constructor

	int type;
	int vnum;
	mob_index *m_index;

	// Dialog Data
	//{{AFX_DATA(DlgVnumList)
	enum { IDD = IDD_VNUM_LIST };
	CListCtrl	m_List;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVnumList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVnumList) 
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVNUMLIST_H__37D7F025_AD76_45D9_BE57_C2EBC9B78E05__INCLUDED_)
