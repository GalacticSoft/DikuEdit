// TypeView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "TypeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TypeView dialog


TypeView::TypeView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(TypeView::IDD, pParent)
{
	//{{AFX_DATA_INIT(TypeView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void TypeView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TypeView)
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TypeView, CTabPageSSL)
	//{{AFX_MSG_MAP(TypeView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TypeView message handlers

BOOL TypeView::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	UpdateData(false);

	COleSafeArray saRet;
	
	SAFEARRAYBOUND sab[2];
	CString csTemp;
	long index[2] = {0,0}; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0]=1;
	int x=1, max_x =0, i;
	
	for( i = 0; i < MAX_ITEM_TYPE; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;

		if(GetObjTypeCount(i) > 0)
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
	csTemp = "Item Types";
	bstr = csTemp.AllocSysString(); // Row label
	saRet.PutElement(index, bstr);

	for(i = 0; i < MAX_ITEM_TYPE; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;

		if(GetObjTypeCount(i) > 0)
		{
			x++;
			index[1]=x;
			csTemp.Format("%f", GetObjTypePercent(i));
			bstr = csTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			::SysFreeString(bstr);
		}
	}
	
	if(GetLoadedObjCount() >  0)
		m_ChartControl.SetChartData(saRet.Detach());
	
	x = 1;
	for(i = 0; i< MAX_ITEM_TYPE; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;
		if(GetObjTypeCount(i) > 0)
		{
			m_ChartControl.SetColumn(x);
			m_ChartControl.SetColumnLabel(item_types[i].name);
			x++;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
