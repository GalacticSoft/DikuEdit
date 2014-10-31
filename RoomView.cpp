// RoomView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "RoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RoomView dialog


RoomView::RoomView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(RoomView::IDD, pParent)
{
	//{{AFX_DATA_INIT(RoomView)
	legend = FALSE;
	mob_count = 0;
	obj_count = 0;
	room_count = 0;
	//}}AFX_DATA_INIT
}


void RoomView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RoomView)
	DDX_Check(pDX, IDC_LEGEND, legend);
	DDX_Text(pDX, IDC_MOB_COUNT, mob_count);
	DDX_Text(pDX, IDC_OBJ_COUNT, obj_count);
	DDX_Text(pDX, IDC_ROOM_COUNT, room_count);
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RoomView, CTabPageSSL)
	//{{AFX_MSG_MAP(RoomView)
	ON_BN_CLICKED(IDC_LEGEND, OnLegend)
	ON_BN_CLICKED(IDC_BAR, OnBar)
	ON_BN_CLICKED(IDC_PIE, OnPie)
	ON_BN_CLICKED(IDC_3D, On3d)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RoomView message handlers

BOOL RoomView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	mob_count = GetAvgMobsPerRoom();
	room_count = GetRoomCount();
	obj_count = GetAvgObjsPerRoom();
	
	COleSafeArray saRet;
	
	SAFEARRAYBOUND sab[2];
	CString csTemp;
	long index[2] = {0,0}; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0]=1;
	int x=1, max_x =0, i;
	
	for( i = 0; i < SECT_MAX; i++)
	{
		if(GetRoomTerrainCount(i) > 0)
			max_x++;
	}
	m_ChartControl.SetRowCount(1);
	m_ChartControl.SetShowLegend(TRUE);
	//m_ChartControl.SetAllowSelections(false);

	sab[0].cElements =1;
	sab[1].cElements = max_x+1;//number of columns + 1 (because the first column is where we put 

	sab[0].lLbound = sab[1].lLbound = 1;	
	
	saRet.Create(VT_BSTR, 2, sab);
	
	m_ChartControl.SetColumnCount(max_x);
	m_ChartControl.SetColumnLabelCount(max_x);
	
	index[1]=1;
	csTemp = "Terrain Statistics";
	bstr = csTemp.AllocSysString(); // Row label
	saRet.PutElement(index, bstr);

	for(i = 0; i < SECT_MAX; i++)
	{
		if(GetRoomTerrainCount(i) > 0)
		{
			x++;
			index[1]=x;
			csTemp.Format("%f", GetRoomTerrainPercent(i));
			bstr = csTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			::SysFreeString(bstr);
		}
	}

	m_ChartControl.SetChartData(saRet.Detach());
	
	x = 1;
	for(i = 0; i< SECT_MAX; i++)
	{
		if(GetRoomTerrainCount(i) > 0)
		{
			m_ChartControl.SetColumn(x);
			m_ChartControl.SetColumnLabel(sector_names[i][0]);
			x++;
		}
	}
	
	legend = true;

	UpdateData(false);

	((CButton*)GetDlgItem(IDC_BAR))->SetCheck(true);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RoomView::OnLegend() 
{
	UpdateData(true);

	m_ChartControl.SetShowLegend(legend);
}

void RoomView::OnBar() 
{
	m_ChartControl.SetChartType(1);	
}

void RoomView::OnPie() 
{
	m_ChartControl.SetChartType(14);
}

void RoomView::On3d() 
{
	m_ChartControl.SetChartType(8);
}
