// DlgAbout.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAbout dialog


DlgAbout::DlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAbout)
	about = _T("");
	company = _T("");
	date = _T("");
	name = _T("");
	vdate = _T("");
	version = _T("");
	//}}AFX_DATA_INIT
}


void DlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAbout)
	DDX_Control(pDX, IDC_MAIL, mail);
	DDX_Text(pDX, IDC_ABOUT, about);
	DDX_Text(pDX, IDC_COMPANY, company);
	DDX_Text(pDX, IDC_DATE, date);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_VDATE, vdate);
	DDX_Text(pDX, IDC_VERSION, version);
	DDX_Control(pDX, IDC_LINK, link);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAbout, CDialog)
	//{{AFX_MSG_MAP(DlgAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAbout message handlers

BOOL DlgAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();
		about = _T("Diku MUD Area Editor was created in an attempt to create\r\n"
		"an easily usable area editor, I had tried other zone editors in the\r\n"
		"past and found them lacking. At first I had made an attempt to\r\n"
		"create this in VB 6.0 but it was never completed.\r\n"
		"A few years later I had decided it was time to test out MFC, and\r\n"
		"this is the result of that attempt. It was created with MFC 6.0\r\n"
		"and MSVC 6.0.");
	company = _T("Galactic Software Solutions");
	date = _T("6/2003");
	name = _T("Marissa du Bois");
	vdate = _T("11/3/2014");
	version = _T("1.8.1");
	
	link.SetLinkText("Visit My Website");
	link.SetTootTipText("Check Here for Updates");
	link.SetLinkUrl("http://www.galacticsoft.net");

	mail.SetLinkText("marissa@galacticsoft.net");
	mail.SetTootTipText("marissa@galacticsoft.net");
	mail.SetLinkUrl("mailto:marissa@galacticsoft.net");

	UpdateData(false);

	return TRUE;  
}
