//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_OBJVIEW_H__55939644_505C_49AE_A354_173FFDBBF14C__INCLUDED_)
#define AFX_OBJVIEW_H__55939644_505C_49AE_A354_173FFDBBF14C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjView.h : header file
//
#include "TypeView.h"
#include "MaterialView.h"
#include "CraftView.h"
#include "StatView.h"
#include "StatsView.h"

/////////////////////////////////////////////////////////////////////////////
// ObjView dialog

class ObjView : public CTabPageSSL
{
// Construction
public:
	ObjView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ObjView)
	enum { IDD = IDD_OBJ_VIEW };
	CTabCtrlSSL	ObjTabs;
	BOOL	legend;
	int		obj_count;
	int		objs_loaded;
	float		avg_ac;
	float		avg_agi;
	float		avg_con;
	float		avg_dam;
	float		avg_dex;
	float		avg_hit;
	float		avg_int;
	float		avg_str;
	float		avg_wis;
	int		tot_ac;
	int		tot_agi;
	int		tot_con;
	int		tot_dam;
	int		tot_dex;
	int		tot_hit;
	int		tot_int;
	int		tot_str;
	int		tot_wis;
	//}}AFX_DATA
	
	TypeView		type_tab;
	MaterialView	mat_tab;
	CraftView		craft_tab;
	StatView		stat_tab;
	StatsView		stats_tab;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObjView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ObjView)
	afx_msg void OnBar();
	afx_msg void OnPie();
	afx_msg void On3d();
	afx_msg void OnLegend();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJVIEW_H__55939644_505C_49AE_A354_173FFDBBF14C__INCLUDED_)
