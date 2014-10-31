// bv calcutatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BvCalc.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBvcalcutatorDlg dialog
int button_values[][2] =
{
	{IDC_BV00, BV00},
	{IDC_BV01, BV01},
	{IDC_BV02, BV02},
	{IDC_BV03, BV03},
	{IDC_BV04, BV04},
	{IDC_BV05, BV05},
	{IDC_BV06, BV06},
	{IDC_BV07, BV07},
	{IDC_BV08, BV08},
	{IDC_BV09, BV09},
	{IDC_BV10, BV10},
	{IDC_BV11, BV11},
	{IDC_BV12, BV12},
	{IDC_BV13, BV13},
	{IDC_BV14, BV14},
	{IDC_BV15, BV15},
	{IDC_BV16, BV16},
	{IDC_BV17, BV17},
	{IDC_BV18, BV18},
	{IDC_BV19, BV19},
	{IDC_BV20, BV20},
	{IDC_BV21, BV21},
	{IDC_BV22, BV22},
	{IDC_BV23, BV23},
	{IDC_BV24, BV24},
	{IDC_BV25, BV25},
	{IDC_BV26, BV26},
	{IDC_BV27, BV27},
	{IDC_BV28, BV28},
	{IDC_BV29, BV29},
	{IDC_BV30, BV30},
};

CBvcalcutatorDlg::CBvcalcutatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBvcalcutatorDlg::IDD, pParent)
{
	input = false;
	value = 0;
	//{{AFX_DATA_INIT(CBvcalcutatorDlg)
	bits = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBvcalcutatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBvcalcutatorDlg)
	DDX_Text(pDX, IDC_TEXT, bits);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBvcalcutatorDlg, CDialog)
	//{{AFX_MSG_MAP(CBvcalcutatorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BV00, OnBv00)
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDOK,	OnOk)
	ON_BN_CLICKED(IDC_BV01, OnBv01)
	ON_BN_CLICKED(IDC_BV02, OnBv02)
	ON_BN_CLICKED(IDC_BV03, OnBv03)
	ON_BN_CLICKED(IDC_BV04, OnBv04)
	ON_BN_CLICKED(IDC_BV05, OnBv05)
	ON_BN_CLICKED(IDC_BV06, OnBv06)
	ON_BN_CLICKED(IDC_BV07, OnBv07)
	ON_BN_CLICKED(IDC_BV08, OnBv08)
	ON_BN_CLICKED(IDC_BV09, OnBv09)
	ON_BN_CLICKED(IDC_BV10, OnBv10)
	ON_BN_CLICKED(IDC_BV11, OnBv11)
	ON_BN_CLICKED(IDC_BV12, OnBv12)
	ON_BN_CLICKED(IDC_BV13, OnBv13)
	ON_BN_CLICKED(IDC_BV14, OnBv14)
	ON_BN_CLICKED(IDC_BV15, OnBv15)
	ON_BN_CLICKED(IDC_BV16, OnBv16)
	ON_BN_CLICKED(IDC_BV17, OnBv17)
	ON_BN_CLICKED(IDC_BV18, OnBv18)
	ON_BN_CLICKED(IDC_BV19, OnBv19)
	ON_BN_CLICKED(IDC_BV20, OnBv20)
	ON_BN_CLICKED(IDC_BV21, OnBv21)
	ON_BN_CLICKED(IDC_BV22, OnBv22)
	ON_BN_CLICKED(IDC_BV23, OnBv23)
	ON_BN_CLICKED(IDC_BV24, OnBv24)
	ON_BN_CLICKED(IDC_BV25, OnBv25)
	ON_BN_CLICKED(IDC_BV26, OnBv26)
	ON_BN_CLICKED(IDC_BV27, OnBv27)
	ON_BN_CLICKED(IDC_BV28, OnBv28)
	ON_BN_CLICKED(IDC_BV29, OnBv29)
	ON_BN_CLICKED(IDC_BV30, OnBv30)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBvcalcutatorDlg message handlers

BOOL CBvcalcutatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(value > 0)
	{
		bits = value;
		input = true;
		OnConvert();
	}
	
	UpdateData(false);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBvcalcutatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBvcalcutatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBvcalcutatorDlg::OnConvert() 
{
	UpdateData(false);
	UpdateData(true);
	CButton *btn;
	
	if(input)
	{
		Clear();

		for(int i = 0; i < 31; i++)
		{
			if(IS_SET(bits, button_values[i][1]))
			{
				btn = (CButton*)GetDlgItem(button_values[i][0]);
				btn->SetCheck(true);
			}
		}
	}
	
	UpdateData(false);
}

void CBvcalcutatorDlg::SetBit(int bit)
{
	if(IS_SET(bits, bit))
		REMOVE_BIT(bits, bit);
	else
		SET_BIT(bits, bit);

	UpdateData(false);
}

void CBvcalcutatorDlg::OnBv00() 
{
	SetBit(BV00);
}

void CBvcalcutatorDlg::OnBv01() 
{
	SetBit(BV01);
}

void CBvcalcutatorDlg::OnBv02() 
{
	SetBit(BV02);
}

void CBvcalcutatorDlg::OnBv03() 
{
	SetBit(BV03);
}

void CBvcalcutatorDlg::OnBv04() 
{
	SetBit(BV04);
}

void CBvcalcutatorDlg::OnBv05() 
{
	SetBit(BV05);
}

void CBvcalcutatorDlg::OnBv06() 
{
	SetBit(BV06);
}

void CBvcalcutatorDlg::OnBv07() 
{
	SetBit(BV07);
}

void CBvcalcutatorDlg::OnBv08() 
{
	SetBit(BV08);
}

void CBvcalcutatorDlg::OnBv09() 
{
	SetBit(BV09);
}

void CBvcalcutatorDlg::OnBv10() 
{
	SetBit(BV10);
}

void CBvcalcutatorDlg::OnBv11() 
{
	SetBit(BV11);
}

void CBvcalcutatorDlg::OnBv12() 
{
	SetBit(BV12);
}

void CBvcalcutatorDlg::OnBv13() 
{
	SetBit(BV13);
}

void CBvcalcutatorDlg::OnBv14() 
{
	SetBit(BV14);
}

void CBvcalcutatorDlg::OnBv15() 
{
	SetBit(BV15);
}

void CBvcalcutatorDlg::OnBv16() 
{
	SetBit(BV16);
}

void CBvcalcutatorDlg::OnBv17() 
{
	SetBit(BV17);
}

void CBvcalcutatorDlg::OnBv18() 
{
	SetBit(BV18);
}

void CBvcalcutatorDlg::OnBv19() 
{
	SetBit(BV19);
}

void CBvcalcutatorDlg::OnBv20() 
{
	SetBit(BV20);
}

void CBvcalcutatorDlg::OnBv21() 
{
	SetBit(BV21);
}

void CBvcalcutatorDlg::OnBv22() 
{
	SetBit(BV22);
}

void CBvcalcutatorDlg::OnBv23() 
{
	SetBit(BV23);
}

void CBvcalcutatorDlg::OnBv24() 
{
	SetBit(BV24);
}

void CBvcalcutatorDlg::OnBv25() 
{
	SetBit(BV25);
}

void CBvcalcutatorDlg::OnBv26() 
{
	SetBit(BV26);
}

void CBvcalcutatorDlg::OnBv27() 
{
	SetBit(BV27);
}

void CBvcalcutatorDlg::OnBv28() 
{
	SetBit(BV28);
}

void CBvcalcutatorDlg::OnBv29() 
{
	SetBit(BV29);
}

void CBvcalcutatorDlg::OnBv30() 
{
	SetBit(BV30);
}

void CBvcalcutatorDlg::ClearInput() 
{
	if(input)
	{
		input = false;
		bits = 0;
	}

	UpdateData(false);
}

void CBvcalcutatorDlg::Clear()
{
	CButton *btn;
	
	for(int i = 0; i < 31; i++)
	{
		btn = (CButton*)GetDlgItem(button_values[i][0]);
		btn->SetCheck(false);
	}
}

void CBvcalcutatorDlg::OnClear()
{
	input = false;
	bits = 0;

	Clear();
	
	UpdateData(false);
}

void CBvcalcutatorDlg::OnChangeText() 
{
	input = true;
	Clear();
}

void CBvcalcutatorDlg::OnOk()
{
	UpdateData(true);
	
	value = bits;

	CDialog::OnOK();
}
