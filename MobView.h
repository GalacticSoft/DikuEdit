#if !defined(AFX_MOBVIEW_H__87046162_8DED_45B8_84DE_8630E66F761C__INCLUDED_)
#define AFX_MOBVIEW_H__87046162_8DED_45B8_84DE_8630E66F761C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MobView.h : header file
//
#include "DlgAggroStatistics.h"
#include "ClassView.h"
#include "RaceView.h"

/////////////////////////////////////////////////////////////////////////////
// MobView dialog

class MobView : public CTabPageSSL
{
// Construction
public:
	MobView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MobView)
	enum { IDD = IDD_MOB_VIEW };
	CSliderCtrl	Slider;
	CTabCtrlSSL	MobTabs;
	float	avg_align;
	float	avg_level;
	CString	avg_size;
	int		mob_count;
	int		mobs_loaded;
	BOOL	legend;
	int		pos;
	//}}AFX_DATA

	DlgAggroStatistics aggro_tab;
	ClassView		class_tab;
	RaceView		race_tab;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MobView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MobView)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowlegend();
	afx_msg void OnBar();
	afx_msg void OnPie();
	afx_msg void On3d();
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBVIEW_H__87046162_8DED_45B8_84DE_8630E66F761C__INCLUDED_)
