// StatsView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "StatsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StatsView dialog


StatsView::StatsView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(StatsView::IDD, pParent)
{
	//{{AFX_DATA_INIT(StatsView)
	avg_breath = 0;
	avg_hp = 0;
	avg_mp = 0;
	avg_mv = 0;
	avg_para = 0;
	avg_petri = 0;
	avg_rod = 0;
	avg_spell = 0;
	tot_breath = 0;
	tot_hp = 0;
	tot_mp = 0;
	tot_mv = 0;
	tot_para = 0;
	tot_petri = 0;
	tot_rod = 0;
	tot_spell = 0;
	//}}AFX_DATA_INIT
}


void StatsView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StatsView)
	DDX_Text(pDX, IDC_AVG_BREATH, avg_breath);
	DDX_Text(pDX, IDC_AVG_HP, avg_hp);
	DDX_Text(pDX, IDC_AVG_MP, avg_mp);
	DDX_Text(pDX, IDC_AVG_MV, avg_mv);
	DDX_Text(pDX, IDC_AVG_PARA, avg_para);
	DDX_Text(pDX, IDC_AVG_PETRI, avg_petri);
	DDX_Text(pDX, IDC_AVG_ROD, avg_rod);
	DDX_Text(pDX, IDC_AVG_SPELL, avg_spell);
	DDX_Text(pDX, IDC_TOT_BREATH, tot_breath);
	DDX_Text(pDX, IDC_TOT_HP, tot_hp);
	DDX_Text(pDX, IDC_TOT_MP, tot_mp);
	DDX_Text(pDX, IDC_TOT_MV, tot_mv);
	DDX_Text(pDX, IDC_TOT_PARA, tot_para);
	DDX_Text(pDX, IDC_TOT_PETRI, tot_petri);
	DDX_Text(pDX, IDC_TOT_ROD, tot_rod);
	DDX_Text(pDX, IDC_TOT_SPELL, tot_spell);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StatsView, CTabPageSSL)
	//{{AFX_MSG_MAP(StatsView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StatsView message handlers

BOOL StatsView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	avg_breath = GetAvgApply(APPLY_SAVING_BREATH);
	avg_hp = GetAvgApply(APPLY_HIT);
	avg_mp = GetAvgApply(APPLY_MANA);
	avg_mv = GetAvgApply(APPLY_MOVE);
	avg_para = GetAvgApply(APPLY_SAVING_PARA);
	avg_petri = GetAvgApply(APPLY_SAVING_PETRI);
	avg_rod = GetAvgApply(APPLY_SAVING_ROD);
	avg_spell = GetAvgApply(APPLY_SAVING_SPELL);
	tot_breath = GetTotalApply(APPLY_SAVING_BREATH);
	tot_hp = GetTotalApply(APPLY_HIT);
	tot_mp = GetTotalApply(APPLY_MANA);
	tot_mv = GetTotalApply(APPLY_MOVE);
	tot_para = GetTotalApply(APPLY_SAVING_PARA);
	tot_petri = GetTotalApply(APPLY_SAVING_PETRI);
	tot_rod = GetTotalApply(APPLY_SAVING_ROD);
	tot_spell = GetTotalApply(APPLY_SAVING_SPELL);

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
