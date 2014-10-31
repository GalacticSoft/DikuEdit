// ClassView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "ClassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassView dialog


ClassView::ClassView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(ClassView::IDD, pParent)
{
	//{{AFX_DATA_INIT(ClassView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ClassView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ClassView)
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClassView, CTabPageSSL)
	//{{AFX_MSG_MAP(ClassView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassView message handlers

BOOL ClassView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	COleSafeArray saRet;
	SAFEARRAYBOUND sab[2];
	CString csTemp;
	long index[2] = {0,0}; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0]=1;
	int x=1, max_x =0, i;
	
	for( i = CLASS_NONE; i < MAX_CLASS; i++)
	{
		if(GetClassCount(i) > 0)
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
	csTemp = "Class Statistics";
	bstr = csTemp.AllocSysString(); // Row label
	saRet.PutElement(index, bstr);

	for(i = CLASS_NONE; i < MAX_CLASS; i++)
	{
		if(GetClassCount(i) > 0)
		{
			x++;
			index[1]=x;
			csTemp.Format("%f", GetClassPercent(i));
			bstr = csTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			::SysFreeString(bstr);
		}
	}

	m_ChartControl.SetChartData(saRet.Detach());
	
	x = 1;
	for(i = CLASS_NONE; i< MAX_CLASS; i++)
	{
		if(GetClassCount(i) > 0)
		{
			m_ChartControl.SetColumn(x);
			m_ChartControl.SetColumnLabel(GetClassName(i));
			x++;
		}
	}

	//m_ChartControl.SetTitleText("Class Percentages");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
