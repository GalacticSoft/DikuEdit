//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGAGGROSTATISTICS_H__364F158C_CADB_4F7E_B7F9_F2BE20087184__INCLUDED_)
#define AFX_DLGAGGROSTATISTICS_H__364F158C_CADB_4F7E_B7F9_F2BE20087184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAggroStatistics.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAggroStatistics dialog
typedef struct AggroMobs
{
	CString header;
	CString aggro_evil;
	CString aggro_good;
	CString aggro_neut;	
	CString aggro_evilrace;
	CString aggro_goodrace;
	CString aggro_all;
	CString not_aggro;
} AggroMobs;

class DlgAggroStatistics : public CTabPageSSL
{
// Construction
public:
	DlgAggroStatistics(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAggroStatistics)
	enum { IDD = IDD_AGGRO_STATS };
	CMSChart	m_ChartControl;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAggroStatistics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	int DlgAggroStatistics::UpdateAggroChart();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAggroStatistics)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAGGROSTATISTICS_H__364F158C_CADB_4F7E_B7F9_F2BE20087184__INCLUDED_)
