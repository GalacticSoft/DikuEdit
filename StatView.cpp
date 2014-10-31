// StatView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "StatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StatView dialog


StatView::StatView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(StatView::IDD, pParent)
{
	//{{AFX_DATA_INIT(StatView)
	avg_maxagi = 0;
	avg_maxcon = 0;
	avg_maxdex = 0;
	avg_maxint = 0;
	avg_maxluk = 0;
	avg_maxpow = 0;
	avg_maxstr = 0;
	avg_maxwis = 0;
	avg_racagi = 0;
	avg_raccon = 0;
	avg_racdex = 0;
	avg_racint = 0;
	avg_racluk = 0;
	avg_racpow = 0;
	avg_racstr = 0;
	avg_racwis = 0;
	tot_maxagi = 0;
	tot_maxcon = 0;
	tot_maxdex = 0;
	tot_maxint = 0;
	tot_maxluk = 0;
	tot_maxpow = 0;
	tot_maxstr = 0;
	tot_maxwis = 0;
	tot_racagi = 0;
	tot_raccon = 0;
	tot_racdex = 0;
	tot_racint = 0;
	tot_racluk = 0;
	tot_racpow = 0;
	tot_racstr = 0;
	tot_racwis = 0;
	//}}AFX_DATA_INIT
}


void StatView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StatView)
	DDX_Text(pDX, IDC_AVG_MAXAGI, avg_maxagi);
	DDX_Text(pDX, IDC_AVG_MAXCON, avg_maxcon);
	DDX_Text(pDX, IDC_AVG_MAXDEX, avg_maxdex);
	DDX_Text(pDX, IDC_AVG_MAXINT, avg_maxint);
	DDX_Text(pDX, IDC_AVG_MAXLUK, avg_maxluk);
	DDX_Text(pDX, IDC_AVG_MAXPOW, avg_maxpow);
	DDX_Text(pDX, IDC_AVG_MAXSTR, avg_maxstr);
	DDX_Text(pDX, IDC_AVG_MAXWIS, avg_maxwis);
	DDX_Text(pDX, IDC_AVG_RACAGI, avg_racagi);
	DDX_Text(pDX, IDC_AVG_RACCON, avg_raccon);
	DDX_Text(pDX, IDC_AVG_RACDEX, avg_racdex);
	DDX_Text(pDX, IDC_AVG_RACINT, avg_racint);
	DDX_Text(pDX, IDC_AVG_RACLUK, avg_racluk);
	DDX_Text(pDX, IDC_AVG_RACPOW, avg_racpow);
	DDX_Text(pDX, IDC_AVG_RACSTR, avg_racstr);
	DDX_Text(pDX, IDC_AVG_RACWIS, avg_racwis);
	DDX_Text(pDX, IDC_TOT_MAXAGI, tot_maxagi);
	DDX_Text(pDX, IDC_TOT_MAXCON, tot_maxcon);
	DDX_Text(pDX, IDC_TOT_MAXDEX, tot_maxdex);
	DDX_Text(pDX, IDC_TOT_MAXINT, tot_maxint);
	DDX_Text(pDX, IDC_TOT_MAXLUK, tot_maxluk);
	DDX_Text(pDX, IDC_TOT_MAXPOW, tot_maxpow);
	DDX_Text(pDX, IDC_TOT_MAXSTR, tot_maxstr);
	DDX_Text(pDX, IDC_TOT_MAXWIS, tot_maxwis);
	DDX_Text(pDX, IDC_TOT_RACAGI, tot_racagi);
	DDX_Text(pDX, IDC_TOT_RACCON, tot_raccon);
	DDX_Text(pDX, IDC_TOT_RACDEX, tot_racdex);
	DDX_Text(pDX, IDC_TOT_RACINT, tot_racint);
	DDX_Text(pDX, IDC_TOT_RACLUK, tot_racluk);
	DDX_Text(pDX, IDC_TOT_RACPOW, tot_racpow);
	DDX_Text(pDX, IDC_TOT_RACSTR, tot_racstr);
	DDX_Text(pDX, IDC_TOT_RACWIS, tot_racwis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StatView, CTabPageSSL)
	//{{AFX_MSG_MAP(StatView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StatView message handlers

BOOL StatView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	avg_maxagi = GetAvgApply(APPLY_MAX_AGI);
	avg_maxcon = GetAvgApply(APPLY_MAX_CON);
	avg_maxdex = GetAvgApply(APPLY_MAX_DEX);
	avg_maxint = GetAvgApply(APPLY_MAX_INT);
	avg_maxluk = GetAvgApply(APPLY_MAX_LUK);
	avg_maxpow = GetAvgApply(APPLY_MAX_POW);
	avg_maxstr = GetAvgApply(APPLY_MAX_STR);
	avg_maxwis = GetAvgApply(APPLY_MAX_WIS);
	avg_racagi = GetAvgApply(APPLY_RACE_AGI);
	avg_raccon = GetAvgApply(APPLY_RACE_CON);
	avg_racdex = GetAvgApply(APPLY_RACE_DEX);
	avg_racint = GetAvgApply(APPLY_RACE_INT);
	avg_racluk = GetAvgApply(APPLY_RACE_LUK);
	avg_racpow = GetAvgApply(APPLY_RACE_POW);
	avg_racstr = GetAvgApply(APPLY_RACE_STR);
	avg_racwis = GetAvgApply(APPLY_RACE_WIS);
	tot_maxagi = GetTotalApply(APPLY_MAX_AGI);
	tot_maxcon = GetTotalApply(APPLY_MAX_CON);
	tot_maxdex = GetTotalApply(APPLY_MAX_DEX);
	tot_maxint = GetTotalApply(APPLY_MAX_INT);
	tot_maxluk = GetTotalApply(APPLY_MAX_LUK);
	tot_maxpow = GetTotalApply(APPLY_MAX_POW);
	tot_maxstr = GetTotalApply(APPLY_MAX_STR);
	tot_maxwis = GetTotalApply(APPLY_MAX_WIS);
	tot_racagi = GetTotalApply(APPLY_RACE_AGI);
	tot_raccon = GetTotalApply(APPLY_RACE_CON);
	tot_racdex = GetTotalApply(APPLY_RACE_DEX);
	tot_racint = GetTotalApply(APPLY_RACE_INT);
	tot_racluk = GetTotalApply(APPLY_RACE_LUK);
	tot_racpow = GetTotalApply(APPLY_RACE_POW);
	tot_racstr = GetTotalApply(APPLY_RACE_STR);
	tot_racwis = GetTotalApply(APPLY_RACE_WIS);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
