// EditAffBits.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "EditAffBits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditAffBits dialog


EditAffBits::EditAffBits(CWnd* pParent /*=NULL*/)
	: CDialog(EditAffBits::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditAffBits)
	val1 = 0;
	val2 = 0;
	val3 = 0;
	val4 = 0;
	val5 = 0;
	val6 = 0;
	//}}AFX_DATA_INIT
}


void EditAffBits::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditAffBits)
	DDX_Text(pDX, IDC_BIT1, val1);
	DDX_Text(pDX, IDC_BIT2, val2);
	DDX_Text(pDX, IDC_BIT3, val3);
	DDX_Text(pDX, IDC_BIT4, val4);
	DDX_Text(pDX, IDC_BIT5, val5);
	DDX_Text(pDX, IDC_BIT6, val6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditAffBits, CDialog)
	//{{AFX_MSG_MAP(EditAffBits)
	ON_BN_CLICKED(IDC_BITCALC, OnBitcalc)
	ON_BN_CLICKED(IDC_BITCALC2, OnBitcalc2)
	ON_BN_CLICKED(IDC_BITCALC3, OnBitcalc3)
	ON_BN_CLICKED(IDC_BITCALC4, OnBitcalc4)
	ON_BN_CLICKED(IDC_BITCALC5, OnBitcalc5)
	ON_BN_CLICKED(IDC_BITCALC6, OnBitcalc6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditAffBits message handlers

void EditAffBits::OnBitcalc() 
{
	UpdateData(true);
	calc.value = val1;
	calc.DoModal();
	val1 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnBitcalc2() 
{
	UpdateData(true);
	calc.value = val2;
	calc.DoModal();
	val2 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnBitcalc3() 
{
	UpdateData(true);
	calc.value = val3;
	calc.DoModal();
	val3 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnBitcalc4() 
{
	UpdateData(true);
	calc.value = val4;
	calc.DoModal();
	val4 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnBitcalc5() 
{
	UpdateData(true);
	calc.value = val5;
	calc.DoModal();
	val5 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnBitcalc6() 
{
	UpdateData(true);
	calc.value = val6;
	calc.DoModal();
	val6 = calc.value;
	UpdateData(false);
}

void EditAffBits::OnOK() 
{	
	UpdateData(true);
	 
	affs[0] = val1;
	affs[1] = val2;
	affs[2] = val3;
	affs[3] = val4;
	affs[4] = val5;
	affs[5] = val6;

	CDialog::OnOK();
}

BOOL EditAffBits::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	val1 = affs[0];
	val2 = affs[1];
	val3 = affs[2];
	val4 = affs[3];
	val5 = affs[4];
	val6 = affs[5];

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
