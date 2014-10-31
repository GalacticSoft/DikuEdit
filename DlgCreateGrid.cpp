// DlgCreateGrid.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgCreateGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCreateGrid dialog


DlgCreateGrid::DlgCreateGrid(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCreateGrid::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCreateGrid)
	sizez = 1;
	sizex = 1;
	sizey = 1;
	//}}AFX_DATA_INIT
}


void DlgCreateGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCreateGrid)
	DDX_Text(pDX, IDC_GRID_DEPTH, sizez);
	DDV_MinMaxInt(pDX, sizez, 1, 50);
	DDX_Text(pDX, IDC_GRID_HEIGHT, sizex);
	DDV_MinMaxInt(pDX, sizex, 1, 50);
	DDX_Text(pDX, IDC_GRID_WIDTH, sizey);
	DDV_MinMaxInt(pDX, sizey, 1, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCreateGrid, CDialog)
	//{{AFX_MSG_MAP(DlgCreateGrid)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCreateGrid message handlers
