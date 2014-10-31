// MobView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "MobView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MobView dialog


MobView::MobView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(MobView::IDD, pParent)
{
	//{{AFX_DATA_INIT(MobView)
	avg_align = 0;
	avg_level = 0;
	avg_size = _T("");
	mob_count = 0;
	mobs_loaded = 0;
	legend = FALSE;
	pos = 0;
	//}}AFX_DATA_INIT
}


void MobView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MobView)
	DDX_Control(pDX, IDC_SLIDER1, Slider);
	DDX_Control(pDX, IDC_TAB1, MobTabs);
	DDX_Text(pDX, IDC_AVG_ALIGN, avg_align);
	DDX_Text(pDX, IDC_AVG_LEVEL, avg_level);
	DDX_Text(pDX, IDC_AVG_SIZE, avg_size);
	DDX_Text(pDX, IDC_MOB_COUNT, mob_count);
	DDX_Text(pDX, IDC_MOBS_LOADED, mobs_loaded);
	DDX_Check(pDX, IDC_SHOWLEGEND, legend);
	DDX_Slider(pDX, IDC_SLIDER1, pos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MobView, CTabPageSSL)
	//{{AFX_MSG_MAP(MobView)
	ON_BN_CLICKED(IDC_SHOWLEGEND, OnShowlegend)
	ON_BN_CLICKED(IDC_BAR, OnBar)
	ON_BN_CLICKED(IDC_PIE, OnPie)
	ON_BN_CLICKED(IDC_3D, On3d)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MobView message handlers

BOOL MobView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	int size;
	
	mob_count = GetMobCount();
	mobs_loaded = GetLoadedMobCount();
	avg_level = GetAvgMobLevel();
	avg_align = GetAvgMobAlign();
	

	size = GetAvgMobSize();
	
	if(size > -1 && size < MAX_SIZE)
		avg_size = sizes[size];
	else
		avg_size = "";

	aggro_tab.Create (IDD_AGGRO_STATS, this);
	MobTabs.AddSSLPage (_T("Aggressive Statistics"), 0, &aggro_tab);

	class_tab.Create (IDD_CLASS_STATS, this);
	MobTabs.AddSSLPage (_T("Class Statistics"), 0, &class_tab);

	race_tab.Create (IDD_RACE_STATS, this);
	MobTabs.AddSSLPage (_T("Race Statistics"), 0, &race_tab);
	
	legend = true;
	
	((CButton*)GetDlgItem(IDC_BAR))->SetCheck(true);
	
	Slider.SetRange(1, 60);

	pos = avg_level;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MobView::OnShowlegend() 
{
	UpdateData(true);

	aggro_tab.m_ChartControl.SetShowLegend(legend);

	class_tab.m_ChartControl.SetShowLegend(legend);

	race_tab.m_ChartControl.SetShowLegend(legend);
}

void MobView::OnBar() 
{
	UpdateData(true);

	aggro_tab.m_ChartControl.SetChartType(1);

	class_tab.m_ChartControl.SetChartType(1);

	race_tab.m_ChartControl.SetChartType(1);
}

void MobView::OnPie() 
{
	UpdateData(true);

	aggro_tab.m_ChartControl.SetChartType(14);

	class_tab.m_ChartControl.SetChartType(14);

	race_tab.m_ChartControl.SetChartType(14);		
}

void MobView::On3d() 
{
	UpdateData(true);

	aggro_tab.m_ChartControl.SetChartType(8);

	class_tab.m_ChartControl.SetChartType(8);

	race_tab.m_ChartControl.SetChartType(8);
		
}


void MobView::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int dif;
	mob_data *mob;

	UpdateData(true);

	dif = pos - GetAvgMobLevel();

	
	for(mob = mob_data::first_mob; mob; mob = mob->next)
	{
		mob->level = mob->level + dif;

		if(mob->level > 60)
			mob->level = 60;
		if(mob->level < 1)
			mob->level = 1;
	}

	avg_level = GetAvgMobLevel();

	UpdateData(false);

	*pResult = 0;
}
