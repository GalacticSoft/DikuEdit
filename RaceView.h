//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_RACEVIEW_H__99372121_1E27_47A6_ACBC_102EA4E986BC__INCLUDED_)
#define AFX_RACEVIEW_H__99372121_1E27_47A6_ACBC_102EA4E986BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RaceView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RaceView dialog

class RaceView : public CTabPageSSL
{
// Construction
public:
	RaceView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RaceView)
	enum { IDD = IDD_RACE_STATS };
	CMSChart	m_ChartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RaceView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RaceView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RACEVIEW_H__99372121_1E27_47A6_ACBC_102EA4E986BC__INCLUDED_)
