// DlgDirections.cpp : implementation file
//
#include "stdafx.h"
#include "WinDE.h"
#include "DlgDirections.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDirections dialog


DlgDirections::DlgDirections(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDirections::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDirections)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgDirections::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDirections)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDirections, CDialog)
	//{{AFX_MSG_MAP(DlgDirections)
	ON_BN_CLICKED(IDC_UP,			OnUp)
	ON_BN_CLICKED(IDC_NORTHWEST,	OnNorthwest)
	ON_BN_CLICKED(IDC_NORTH,		OnNorth)
	ON_BN_CLICKED(IDC_NORTHEAST,	OnNortheast)
	ON_BN_CLICKED(IDC_WEST,			OnWest)
	ON_BN_CLICKED(IDC_LOOK,			OnLook)
	ON_BN_CLICKED(IDC_EAST,			OnEast)
	ON_BN_CLICKED(IDC_SOUTHWEST,	OnSouthwest)
	ON_BN_CLICKED(IDC_SOUTH,		OnSouth)
	ON_BN_CLICKED(IDC_SOUTHEAST,	OnSoutheast)
	ON_BN_CLICKED(IDC_DOWN,			OnDown)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_BN_DOUBLECLICKED(IDC_NORTH,		OnNorth)
	ON_BN_DOUBLECLICKED(IDC_SOUTH,		OnSouth)
	ON_BN_DOUBLECLICKED(IDC_EAST,		OnEast)
	ON_BN_DOUBLECLICKED(IDC_WEST,		OnWest)
	ON_BN_DOUBLECLICKED(IDC_UP,			OnUp)
	ON_BN_DOUBLECLICKED(IDC_DOWN,		OnDown)
	ON_BN_DOUBLECLICKED(IDC_NORTHWEST,	OnNorthwest)
	ON_BN_DOUBLECLICKED(IDC_NORTHEAST,	OnNortheast)
	ON_BN_DOUBLECLICKED(IDC_SOUTHWEST,	OnSouthwest)
	ON_BN_DOUBLECLICKED(IDC_SOUTHEAST,	OnSoutheast)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDirections message handlers

void DlgDirections::OnUp() 
{
	((CWinDEDlg*)GetParent())->OnUp();	
}

void DlgDirections::OnNorthwest() 
{
	((CWinDEDlg*)GetParent())->OnNorthWest();	
}

void DlgDirections::OnNorth() 
{
	((CWinDEDlg*)GetParent())->OnNorth();	
}

void DlgDirections::OnNortheast() 
{
	((CWinDEDlg*)GetParent())->OnNorthEast();
}

void DlgDirections::OnWest() 
{
	((CWinDEDlg*)GetParent())->OnWest();	
}

void DlgDirections::OnLook() 
{
	((CWinDEDlg*)GetParent())->OnLook();	
}

void DlgDirections::OnEast() 
{
	((CWinDEDlg*)GetParent())->OnEast();	
}

void DlgDirections::OnSouthwest() 
{
	((CWinDEDlg*)GetParent())->OnSouthWest();	
}

void DlgDirections::OnSouth() 
{
	((CWinDEDlg*)GetParent())->OnSouth();	
}

void DlgDirections::OnSoutheast() 
{
	((CWinDEDlg*)GetParent())->OnSouthEast();	
}

void DlgDirections::OnDown() 
{
	((CWinDEDlg*)GetParent())->OnDown();	
}

BOOL DlgDirections::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

void DlgDirections::OnClose() 
{
	((CWinDEDlg*)GetParent())->OnDirections();
	
	CDialog::OnClose();
}

BOOL DlgDirections::OnInitDialog() 
{
	CDialog::OnInitDialog();

	north.AutoLoad(IDC_NORTH, this);
	south.AutoLoad(IDC_SOUTH, this);
	
	east.AutoLoad(IDC_EAST, this);
	west.AutoLoad(IDC_WEST, this);
	
	northwest.AutoLoad(IDC_NORTHWEST, this);
	northeast.AutoLoad(IDC_NORTHEAST, this);
	southwest.AutoLoad(IDC_SOUTHWEST, this);
	southeast.AutoLoad(IDC_SOUTHEAST, this);
	
	up.AutoLoad(IDC_UP, this);
	down.AutoLoad(IDC_DOWN, this);
	
	look.AutoLoad(IDC_LOOK, this);
	
	return TRUE;
}

void DlgDirections::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	CBrush br(RGB(192, 192, 192));

	GetWindowRect(rect);
	ScreenToClient(rect);
	dc.FillRect(rect, &br);
}
