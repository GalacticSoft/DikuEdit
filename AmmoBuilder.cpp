// AmmoBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "AmmoBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AmmoBuilder dialog


AmmoBuilder::AmmoBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(AmmoBuilder::IDD, pParent)
{
	//{{AFX_DATA_INIT(AmmoBuilder)
	crew = 0;
	hull = 0;
	name = _T("");
	price = 0;
	quantity = 0;
	range = 0;
	sail = 0;
	filename = _T("");
	//}}AFX_DATA_INIT
}

void AmmoBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AmmoBuilder)
	DDX_Control(pDX, IDC_SHIPWRIGHTS, Shipwrights);
	DDX_Text(pDX, IDC_CREW, crew);
	DDX_Text(pDX, IDC_HULL, hull);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_PRICE, price);
	DDX_Text(pDX, IDC_QUANTITY, quantity);
	DDX_Text(pDX, IDC_RANGE, range);
	DDX_Text(pDX, IDC_SAIL, sail);
	DDX_Text(pDX, IDC_FILENAME, filename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AmmoBuilder, CDialog)
	//{{AFX_MSG_MAP(AmmoBuilder)
	ON_BN_CLICKED(IDC_CALC, OnCalc)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AmmoBuilder message handlers

BOOL AmmoBuilder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;

	DWORD dwStyle = ::SendMessage(Shipwrights, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(Shipwrights, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	Shipwrights.GetClientRect(rect);
	Shipwrights.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/5);
	Shipwrights.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	
	ammo_shops.InitList(ammo->shops, Shipwrights);

	crew = ammo->crew_dam;
	sail = ammo->sail_dam;
	hull = ammo->hull_dam;
	name = ammo->name;
	price = ammo->price;
	range =ammo->range;
	quantity = ammo->max_quan;
	filename = ammo->filename;

	UpdateData(false);

	return TRUE; 
}

void AmmoBuilder::OnCalc() 
{
	UpdateData(true);

	DlgCalcCoins dlg_coins(this);

	if(dlg_coins.DoModal() == IDOK)
		price = dlg_coins.total;

	UpdateData(false);
}

void AmmoBuilder::OnAdd() 
{
	ammo_shops.Add(Shipwrights);
}

void AmmoBuilder::OnRemove() 
{
	ammo_shops.Remove(Shipwrights);
}

void AmmoBuilder::OnOK() 
{	
	UpdateData(true);

	CDialog::OnOK();
	ammo_shops.Update(ammo->shops);

	ammo->crew_dam = crew;
	ammo->sail_dam = sail;
	ammo->hull_dam = hull;
	ammo->name = name;
	ammo->price = price;
	ammo->range = range;
	ammo->max_quan = quantity;
	ammo->filename = filename;
}

void AmmoBuilder::OnCancel() 
{
	CDialog::OnCancel();
}
