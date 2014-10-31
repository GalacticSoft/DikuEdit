#if !defined(AFX_LISTCTRL_H__69A11F57_2379_4226_A32B_E1578A77A93F__INCLUDED_)
#define AFX_LISTCTRL_H__69A11F57_2379_4226_A32B_E1578A77A93F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ListCtrl window

class ListCtrl : public CListCtrl
{
// Construction
public:
	ListCtrl();

// Attributes
public:

public:
    enum EHighlight { HIGHLIGHT_NORMAL, HIGHLIGHT_ALLCOLUMNS, HIGHLIGHT_ROW };
protected:
    int m_nHighlight; // Indicate type of selection highlighting
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ListCtrl();
	int SetHighlightType(EHighlight hilite);
	void RepaintSelectedItems();
	// Generated message map functions
protected:
	//{{AFX_MSG(ListCtrl)
	//afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRL_H__69A11F57_2379_4226_A32B_E1578A77A93F__INCLUDED_)
