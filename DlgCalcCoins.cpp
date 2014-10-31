// DlgCalcCoins.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgCalcCoins.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCalcCoins dialog

DlgCalcCoins::DlgCalcCoins(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCalcCoins::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCalcCoins)
	platinum = 0;
	copper = 0;
	gold = 0;
	silver = 0;
	total = 0;
	//}}AFX_DATA_INIT
}

void DlgCalcCoins::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCalcCoins)
	DDX_Text(pDX, IDC_PLATINUM, platinum);
	DDX_Text(pDX, IDC_COPPER, copper);
	DDX_Text(pDX, IDC_GOLD, gold);
	DDX_Text(pDX, IDC_SILVER, silver);
	DDX_Text(pDX, IDC_TOTAL, total);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgCalcCoins, CDialog)
	//{{AFX_MSG_MAP(DlgCalcCoins)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCalcCoins message handlers

void DlgCalcCoins::OnOK() 
{	
	UpdateData(true);

	OnCalculate();

	CDialog::OnOK();
}

void DlgCalcCoins::OnCalculate() 
{
	int cop = 0;
	int i = 0;

	UpdateData(true);

	cop = copper;

	i = silver * 10;

	cop += i;

	i = gold * 100;
	
	cop += i;

	i = platinum * 1000;
	
	cop += i;

	total = cop;

	UpdateData(false);
}
