// MaterialView.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "MaterialView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MaterialView dialog


MaterialView::MaterialView(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(MaterialView::IDD, pParent)
{
	//{{AFX_DATA_INIT(MaterialView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MaterialView::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MaterialView)
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MaterialView, CTabPageSSL)
	//{{AFX_MSG_MAP(MaterialView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MaterialView message handlers

BOOL MaterialView::OnInitDialog() 
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
	
	for( i = 0; i < MAX_MATERIAL; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;

		if(GetObjMaterialCount(i) > 0)
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
	csTemp = "Material";
	bstr = csTemp.AllocSysString(); // Row label
	saRet.PutElement(index, bstr);

	for(i = 0; i < MAX_MATERIAL; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;

		if(GetObjMaterialCount(i) > 0)
		{
			x++;
			index[1]=x;
			csTemp.Format("%f", GetObjMaterialPercent(i));
			bstr = csTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			::SysFreeString(bstr);
		}
	}
	
	if(GetLoadedObjCount() >  0)
		m_ChartControl.SetChartData(saRet.Detach());
	
	x = 1;
	for(i = 0; i< MAX_MATERIAL; i++)
	{
		if(GetLoadedObjCount() == 0)
			break;
		if(GetObjMaterialCount(i) > 0)
		{
			m_ChartControl.SetColumn(x);
			m_ChartControl.SetColumnLabel(materials[i]);
			x++;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
