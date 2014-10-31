#include "stdafx.h"
#include "WinDE.h"
#include "DlgEnterVnum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEnterVnum::DlgEnterVnum(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEnterVnum::IDD, pParent)
{
	type = -1;

	//{{AFX_DATA_INIT(DlgEnterVnum)
	vnum = 0;
	//}}AFX_DATA_INIT
}

void DlgEnterVnum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEnterVnum)
	DDX_Text(pDX, IDC_ENTER_VNUM, vnum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEnterVnum, CDialog)
	//{{AFX_MSG_MAP(DlgEnterVnum)
	ON_BN_CLICKED(IDC_SELETECT_FROM_LIST, OnSeletectFromList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEnterVnum::OnSeletectFromList() 
{
	DlgVnumList vl(this);
	int ret;

	vl.vnum = 0;
	vl.type = this->type;

	ret = vl.DoModal( );

	if(ret == IDOK) {
		this->vnum = vl.vnum;
		UpdateData(false);
	}	
}

