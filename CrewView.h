#if !defined(AFX_CREWVIEW_H__17D0E85B_D7B8_4763_B913_99BCEC75A10D__INCLUDED_)
#define AFX_CREWVIEW_H__17D0E85B_D7B8_4763_B913_99BCEC75A10D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrewView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CrewView dialog

class CrewView : public CTabPageSSL
{
// Construction
public:
	CrewView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CrewView)
	enum { IDD = IDD_CREW_TAB };
	CListCtrl	CrewList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CrewView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CrewView)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkCrewList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREWVIEW_H__17D0E85B_D7B8_4763_B913_99BCEC75A10D__INCLUDED_)
