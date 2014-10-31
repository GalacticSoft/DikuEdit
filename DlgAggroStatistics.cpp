// DlgAggroStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgAggroStatistics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAggroStatistics dialog


DlgAggroStatistics::DlgAggroStatistics(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(DlgAggroStatistics::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAggroStatistics)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgAggroStatistics::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAggroStatistics)
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAggroStatistics, CTabPageSSL)
	//{{AFX_MSG_MAP(DlgAggroStatistics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAggroStatistics message handlers

BOOL DlgAggroStatistics::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	
	UpdateAggroChart();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------

int DlgAggroStatistics::UpdateAggroChart()
{
	COleSafeArray saRet;
	SAFEARRAYBOUND sab[2];
	CString csTemp;
	AggroMobs aggro_mobs;
	long index[2] = {0,0}; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0]=1;		
	
	csTemp.Format("%s", "Aggro Mobs");
	aggro_mobs.header = csTemp;
	
	csTemp.Format("%f", GetAggroGoodPercent());
	aggro_mobs.aggro_evil =csTemp;
		
	csTemp.Format("%f",GetAggroEvilPercent());
	aggro_mobs.aggro_good =csTemp;
		
	csTemp.Format("%f",GetAggroNeutPercent());
	aggro_mobs.aggro_neut = csTemp;
	
	csTemp.Format("%f",GetAggroEvilRacePercent());
	aggro_mobs.aggro_evilrace = csTemp;

	csTemp.Format("%f",GetAggroGoodRacePercent());
	aggro_mobs.aggro_goodrace = csTemp;

	csTemp.Format("%f",GetAggroAllPercent());
	aggro_mobs.aggro_all = csTemp;

	csTemp.Format("%f", GetNonAggroPercent());
	aggro_mobs.not_aggro = csTemp;

	sab[0].cElements =1;// give this exact
	sab[1].cElements = 8; //number of columns + 1 (because the first column is where we put 
						// the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc

	sab[0].lLbound = sab[1].lLbound = 1;

	m_ChartControl.SetShowLegend(TRUE);

	saRet.Create(VT_BSTR, 2, sab);
			
	index[1]=1;
	bstr = aggro_mobs.header.AllocSysString(); // Row label
	saRet.PutElement(index, bstr);

	index[1]=2;
	
	bstr = aggro_mobs.aggro_evil.AllocSysString(); // Data for column 1
	::SysFreeString(bstr);
	saRet.PutElement(index, bstr);
			
	index[1]=3;
	bstr = aggro_mobs.aggro_good.AllocSysString(); // Data for column 2
	::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

	index[1]=4;
	bstr = aggro_mobs.aggro_neut.AllocSysString(); // Data for column 3
	::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

	index[1]=5;
	bstr = aggro_mobs.aggro_evilrace.AllocSysString();// Data for column 4
    ::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

	index[1]=6;
	bstr = aggro_mobs.aggro_goodrace.AllocSysString();// Data for column 4
    ::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

	index[1]=7;
	bstr = aggro_mobs.aggro_all.AllocSysString();// Data for column 4
    ::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

	index[1]=8;
	bstr = aggro_mobs.not_aggro.AllocSysString();// Data for column 4
    ::SysFreeString(bstr);
	saRet.PutElement(index, bstr);

		
    m_ChartControl.SetChartData(saRet.Detach()); 
	
	m_ChartControl.SetRowCount(1);
	//m_ChartControl.SetRowLabel("Agressive Mobs");
	m_ChartControl.SetColumnLabelCount(7);
	m_ChartControl.SetColumn(1);
	m_ChartControl.SetColumnLabel("Aggro Evil");
	m_ChartControl.SetColumn(2);
	m_ChartControl.SetColumnLabel("Aggro Good");
	m_ChartControl.SetColumn(3);
	m_ChartControl.SetColumnLabel("Aggro Neutral");
	m_ChartControl.SetColumn(4);
	m_ChartControl.SetColumnLabel("Aggro Evil Race");
	m_ChartControl.SetColumn(5);
	m_ChartControl.SetColumnLabel("Aggro Good Race");
	m_ChartControl.SetColumn(6);
	m_ChartControl.SetColumnLabel("Agressive");
	m_ChartControl.SetColumn(7);
	m_ChartControl.SetColumnLabel("Not Agressive");

	//m_ChartControl.SetAllowSelections(false);

	return 1;

}
