// CannonBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "CannonBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CannonBuilder dialog


CannonBuilder::CannonBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(CannonBuilder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CannonBuilder)
	accuracy = 0;
	name = _T("");
	vnum = 0;
	price = 0;
	power = 0;
	range = 0;
	filename = _T("");
	//}}AFX_DATA_INIT
}

void CannonBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CannonBuilder)
	DDX_Control(pDX, IDC_SHIPWRIGHTS, Shipwrights);
	DDX_Text(pDX, IDC_ACCURACY, accuracy);
	DDV_MinMaxInt(pDX, accuracy, 0, 100);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_OBJECT, vnum);
	DDX_Text(pDX, IDC_PRICE, price);
	DDX_Text(pDX, IDC_POWER, power);
	DDX_Text(pDX, IDC_RANGE, range);
	DDV_MinMaxInt(pDX, range, 0, 10);
	DDX_Text(pDX, IDC_FILENAME, filename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CannonBuilder, CDialog)
	//{{AFX_MSG_MAP(CannonBuilder)
		ON_BN_CLICKED(IDC_REMOVE,		OnRemove)
		ON_BN_CLICKED(IDC_ADD,			OnAdd)
		ON_BN_CLICKED(IDC_CALC,			OnCalculator)
		ON_BN_CLICKED(IDC_OBJ_LIST,		OnObjectList)
		ON_BN_CLICKED(IDOK,			OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CannonBuilder message handlers

void CannonBuilder::OnAdd()
{
	UpdateData(true);

	shop_list.Add(Shipwrights);

	UpdateData(false);
}

void CannonBuilder::OnCalculator()
{
	UpdateData(true);

	DlgCalcCoins dlg_coins(this);

	if(dlg_coins.DoModal() == IDOK)
		price = dlg_coins.total;

	UpdateData(false);
}

void CannonBuilder::OnRemove()
{
	shop_list.Remove(Shipwrights);
}

void CannonBuilder::OnObjectList()
{
	UpdateData(true);

	DlgVnumList vnum_list(this);

	vnum_list.type = OBJECT;

	if(vnum_list.DoModal() == IDOK)
		vnum = vnum_list.vnum;

	UpdateData(false);
}

void CannonBuilder::OnOK()
{
	UpdateData(true);

	if(cannon)
	{
		cannon->name = name;
		cannon->value = price;
		cannon->accuracy = accuracy;
		cannon->power = power;
		cannon->range = range;
		cannon->obj_vnum = vnum;
		cannon->filename = filename;

		shop_list.Update(cannon->shops);
	}

	CDialog::OnOK();
}

BOOL CannonBuilder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;

	DWORD dwStyle = ::SendMessage(Shipwrights, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(Shipwrights, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	Shipwrights.GetClientRect(rect);
	Shipwrights.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/5);
	Shipwrights.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));

	shop_list.InitList(cannon->shops, Shipwrights);
	
	name = cannon->name;
	price =	cannon->value;
	accuracy = cannon->accuracy;
	power = cannon->power;
	range =	cannon->range;
	vnum = cannon->obj_vnum;
	filename = cannon->filename;

	UpdateData(false);

	return TRUE;  
}
