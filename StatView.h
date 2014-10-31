#if !defined(AFX_STATVIEW_H__AB565E37_A130_40CD_89BF_3A0293578F79__INCLUDED_)
#define AFX_STATVIEW_H__AB565E37_A130_40CD_89BF_3A0293578F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StatView dialog

class StatView : public CTabPageSSL
{
// Construction
public:
	StatView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StatView)
	enum { IDD = IDD_EXTENDED_STATS };
	float	avg_maxagi;
	float		avg_maxcon;
	float		avg_maxdex;
	float		avg_maxint;
	float		avg_maxluk;
	float		avg_maxpow;
	float		avg_maxstr;
	float		avg_maxwis;
	float		avg_racagi;
	float		avg_raccon;
	float		avg_racdex;
	float		avg_racint;
	float		avg_racluk;
	float		avg_racpow;
	float		avg_racstr;
	float		avg_racwis;
	int		tot_maxagi;
	int		tot_maxcon;
	int		tot_maxdex;
	int		tot_maxint;
	int		tot_maxluk;
	int		tot_maxpow;
	int		tot_maxstr;
	int		tot_maxwis;
	int		tot_racagi;
	int		tot_raccon;
	int		tot_racdex;
	int		tot_racint;
	int		tot_racluk;
	int		tot_racpow;
	int		tot_racstr;
	int		tot_racwis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StatView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StatView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATVIEW_H__AB565E37_A130_40CD_89BF_3A0293578F79__INCLUDED_)
