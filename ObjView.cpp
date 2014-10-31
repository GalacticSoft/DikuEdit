// ObjView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "ObjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObjView dialog


ObjView::ObjView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(ObjView::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObjView)
	legend = FALSE;
	obj_count = 0;
	objs_loaded = 0;
	avg_ac = 0;
	avg_agi = 0;
	avg_con = 0;
	avg_dam = 0;
	avg_dex = 0;
	avg_hit = 0;
	avg_int = 0;
	avg_str = 0;
	avg_wis = 0;
	tot_ac = 0;
	tot_agi = 0;
	tot_con = 0;
	tot_dam = 0;
	tot_dex = 0;
	tot_hit = 0;
	tot_int = 0;
	tot_str = 0;
	tot_wis = 0;
	//}}AFX_DATA_INIT
}


void ObjView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObjView)
	DDX_Control(pDX, IDC_TAB1, ObjTabs);
	DDX_Check(pDX, IDC_LEGEND, legend);
	DDX_Text(pDX, IDC_OBJ_COUNT, obj_count);
	DDX_Text(pDX, IDC_OBJS_LOADED, objs_loaded);
	DDX_Text(pDX, IDC_AVG_AC, avg_ac);
	DDX_Text(pDX, IDC_AVG_AGI, avg_agi);
	DDX_Text(pDX, IDC_AVG_CON, avg_con);
	DDX_Text(pDX, IDC_AVG_DAM, avg_dam);
	DDX_Text(pDX, IDC_AVG_DEX, avg_dex);
	DDX_Text(pDX, IDC_AVG_HIT, avg_hit);
	DDX_Text(pDX, IDC_AVG_INT, avg_int);
	DDX_Text(pDX, IDC_AVG_STR, avg_str);
	DDX_Text(pDX, IDC_AVG_WIS, avg_wis);
	DDX_Text(pDX, IDC_TOT_AC, tot_ac);
	DDX_Text(pDX, IDC_TOT_AGI, tot_agi);
	DDX_Text(pDX, IDC_TOT_CON, tot_con);
	DDX_Text(pDX, IDC_TOT_DAM, tot_dam);
	DDX_Text(pDX, IDC_TOT_DEX, tot_dex);
	DDX_Text(pDX, IDC_TOT_HIT, tot_hit);
	DDX_Text(pDX, IDC_TOT_INT, tot_int);
	DDX_Text(pDX, IDC_TOT_STR, tot_str);
	DDX_Text(pDX, IDC_TOT_WIS, tot_wis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObjView, CTabPageSSL)
	//{{AFX_MSG_MAP(ObjView)
	ON_BN_CLICKED(IDC_BAR, OnBar)
	ON_BN_CLICKED(IDC_PIE, OnPie)
	ON_BN_CLICKED(IDC_3D, On3d)
	ON_BN_CLICKED(IDC_LEGEND, OnLegend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObjView message handlers

void ObjView::OnBar() 
{
	type_tab.m_ChartControl.SetChartType(1);
	mat_tab.m_ChartControl.SetChartType(1);
	craft_tab.m_ChartControl.SetChartType(1);
}

void ObjView::OnPie() 
{
	type_tab.m_ChartControl.SetChartType(14);
	mat_tab.m_ChartControl.SetChartType(14);
	craft_tab.m_ChartControl.SetChartType(14);
}

void ObjView::On3d() 
{
	type_tab.m_ChartControl.SetChartType(8);
	mat_tab.m_ChartControl.SetChartType(8);
	craft_tab.m_ChartControl.SetChartType(8);
}

void ObjView::OnLegend() 
{
	UpdateData(true);
	type_tab.m_ChartControl.SetShowLegend(legend);
	mat_tab.m_ChartControl.SetShowLegend(legend);
	craft_tab.m_ChartControl.SetShowLegend(legend);
}

BOOL ObjView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	legend = true;
	
	((CButton*)GetDlgItem(IDC_BAR))->SetCheck(true);
	
	type_tab.Create(IDD_TYPE_VIEW, this);
	ObjTabs.AddSSLPage(_T("Type Statistics"), 0, &type_tab);
	mat_tab.Create(IDD_MAT_VIEW, this);
	ObjTabs.AddSSLPage(_T("Material Statistics"), 0, &mat_tab);
	craft_tab.Create(IDD_CRAFT_VIEW, this);
	ObjTabs.AddSSLPage(_T("Craft Statistics"), 0, &craft_tab);
	stats_tab.Create(IDD_STAT_VIEW, this);
	ObjTabs.AddSSLPage(_T("Stats"), 0, &stats_tab);
	stat_tab.Create(IDD_EXTENDED_STATS, this);
	ObjTabs.AddSSLPage(_T("Extended Stats"), 0, &stat_tab);

	obj_count = GetObjCount();
	objs_loaded = GetLoadedObjCount();
	
	avg_ac = GetAvgApply(APPLY_AC);
	avg_agi = GetAvgApply(APPLY_AGI);
	avg_con = GetAvgApply(APPLY_CON);
	avg_dam = GetAvgApply(APPLY_DAMROLL);
	avg_dex = GetAvgApply(APPLY_DEX);
	avg_hit = GetAvgApply(APPLY_HITROLL);
	avg_int = GetAvgApply(APPLY_INT);
	avg_str = GetAvgApply(APPLY_STR);
	avg_wis = GetAvgApply(APPLY_WIS);
	tot_ac = GetTotalApply(APPLY_AC);
	tot_agi = GetTotalApply(APPLY_AGI);
	tot_con = GetTotalApply(APPLY_CON);
	tot_dam = GetTotalApply(APPLY_DAMROLL);
	tot_dex = GetTotalApply(APPLY_DEX);
	tot_hit = GetTotalApply(APPLY_HITROLL);
	tot_int = GetTotalApply(APPLY_INT);
	tot_str = GetTotalApply(APPLY_STR);
	tot_wis = GetTotalApply(APPLY_WIS);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
