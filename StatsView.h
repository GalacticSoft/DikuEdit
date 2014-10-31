#if !defined(AFX_STATSVIEW_H__C711ED9E_4901_49D6_A370_6A991D53C8B5__INCLUDED_)
#define AFX_STATSVIEW_H__C711ED9E_4901_49D6_A370_6A991D53C8B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StatsView dialog

class StatsView : public CTabPageSSL
{
// Construction
public:
	StatsView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StatsView)
	enum { IDD = IDD_STAT_VIEW };
	float		avg_breath;
	float		avg_hp;
	float		avg_mp;
	float		avg_mv;
	float		avg_para;
	float		avg_petri;
	float		avg_rod;
	float		avg_spell;
	int		tot_breath;
	int		tot_hp;
	int		tot_mp;
	int		tot_mv;
	int		tot_para;
	int		tot_petri;
	int		tot_rod;
	int		tot_spell;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StatsView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StatsView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATSVIEW_H__C711ED9E_4901_49D6_A370_6A991D53C8B5__INCLUDED_)
