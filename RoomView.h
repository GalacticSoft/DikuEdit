//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_ROOMVIEW_H__7F573BC4_ED71_4429_97B7_787D8B64106D__INCLUDED_)
#define AFX_ROOMVIEW_H__7F573BC4_ED71_4429_97B7_787D8B64106D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RoomView dialog

class RoomView : public CTabPageSSL
{
// Construction
public:
	RoomView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RoomView)
	enum { IDD = IDD_ROOM_VIEW };
	BOOL	legend;
	float	mob_count;
	float	obj_count;
	int		room_count;
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RoomView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RoomView)
	virtual BOOL OnInitDialog();
	afx_msg void OnLegend();
	afx_msg void OnBar();
	afx_msg void OnPie();
	afx_msg void On3d();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMVIEW_H__7F573BC4_ED71_4429_97B7_787D8B64106D__INCLUDED_)
