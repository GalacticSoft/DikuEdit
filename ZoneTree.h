#if !defined(AFX_ZONETREE_H__3AA952F2_3504_4221_8FC4_44C24EA7A120__INCLUDED_)
#define AFX_ZONETREE_H__3AA952F2_3504_4221_8FC4_44C24EA7A120__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoneTree window

class CZoneTree : public CTreeCtrl
{
public:
	CZoneTree();
	HCURSOR cursor_arr;
	HCURSOR cursor_no;
	bool	isCursorArrow;

	CImageList*	m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM	m_hitemDrag,m_hitemDrop;
	
	HTREEITEM MoveChildItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter);
	
	void ConvertMobToIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent);
	void CopyMobIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent);
	void ConvertObjToIndex(HTREEITEM &hItem, HTREEITEM &NewItem, HTREEITEM &htiNewParent);
	void CopyObjIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent);

	BOOL MenuSelect(UINT id);
	virtual ~CZoneTree();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoneTree)
	//}}AFX_VIRTUAL

	

	// Generated message map functions
protected:
	//{{AFX_MSG(CZoneTree)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZONETREE_H__3AA952F2_3504_4221_8FC4_44C24EA7A120__INCLUDED_)
