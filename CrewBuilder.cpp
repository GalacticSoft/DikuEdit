// CrewBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "CrewBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CrewBuilder dialog


CrewBuilder::CrewBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(CrewBuilder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CrewBuilder)
	atk = 0;
	def = 0;
	frt = 0;
	gun = 0;
	leader = 0;
	max_atk = 0;
	max_def = 0;
	max_gun = 0;
	max_sail = 0;
	member = 0;
	max_men = 0;
	name = _T("");
	price = 0;
	sail = 0;
	spd = 0;
	str = 0;
	filename = _T("");
	//}}AFX_DATA_INIT
}


void CrewBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CrewBuilder)
	DDX_Control(pDX, IDC_SHIPWRIGHTS, Shipwrights);
	DDX_Text(pDX, IDC_ATK, atk);
	DDX_Text(pDX, IDC_DEF, def);
	DDX_Text(pDX, IDC_FORTITUDE, frt);
	DDX_Text(pDX, IDC_GUN, gun);
	DDX_Text(pDX, IDC_LEADER, leader);
	DDX_Text(pDX, IDC_MAX_ATK, max_atk);
	DDX_Text(pDX, IDC_MAX_DEF, max_def);
	DDX_Text(pDX, IDC_MAX_GUN, max_gun);
	DDX_Text(pDX, IDC_MAX_SAIL, max_sail);
	DDX_Text(pDX, IDC_MEMBER, member);
	DDX_Text(pDX, IDC_MEMBERS, max_men);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_PRICE, price);
	DDX_Text(pDX, IDC_SAIL, sail);
	DDX_Text(pDX, IDC_SPEED, spd);
	DDX_Text(pDX, IDC_STRENGTH, str);
	DDX_Text(pDX, IDC_FILENAME, filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CrewBuilder, CDialog)
	//{{AFX_MSG_MAP(CrewBuilder)
	ON_BN_CLICKED(IDC_MEMBER_LIST, OnMemberList)
	ON_BN_CLICKED(IDC_LEADER_LIST, OnLeaderList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_CALC, OnCalc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CrewBuilder message handlers

void CrewBuilder::OnMemberList() 
{
	UpdateData(true);

	DlgVnumList vnum_list(this);

	vnum_list.type = MOBILE;

	if(vnum_list.DoModal() == IDOK)
		member = vnum_list.vnum;

	UpdateData(false);	
}

void CrewBuilder::OnLeaderList() 
{
	UpdateData(true);

	DlgVnumList vnum_list(this);

	vnum_list.type = MOBILE;

	if(vnum_list.DoModal() == IDOK)
		leader = vnum_list.vnum;

	UpdateData(false);
}

void CrewBuilder::OnAdd() 
{
	shop_list.Add(Shipwrights);
}

void CrewBuilder::OnRemove() 
{
	shop_list.Remove(Shipwrights);
}

void CrewBuilder::OnCalc() 
{
	UpdateData(true);

	DlgCalcCoins dlg_coins(this);

	if(dlg_coins.DoModal() == IDOK)
		price = dlg_coins.total;

	UpdateData(false);
}

void CrewBuilder::OnOK() 
{
	UpdateData(true);

	crew->atk = atk;
	crew->def = def;
	crew->frt = frt;
	crew->gun = gun;
	crew->leader = leader;
	crew->max_atk = max_atk;
	crew->max_def = max_def;
	crew->max_gun = max_gun;
	crew->max_sail = max_sail;
	crew->member = member;
	crew->max_men = max_men;
	crew->name = name;
	crew->price = price;
	crew->sail = sail;
	crew->spd = spd;
	crew->str = str;
	crew->filename = filename;

	shop_list.Update(crew->shops);
	CDialog::OnOK();
}

void CrewBuilder::OnCancel() 
{	
	CDialog::OnCancel();
}

BOOL CrewBuilder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;

	DWORD dwStyle = ::SendMessage(Shipwrights, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(Shipwrights, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	Shipwrights.GetClientRect(rect);
	Shipwrights.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/5);
	Shipwrights.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	
	shop_list.InitList(crew->shops, Shipwrights);

	atk = crew->atk;
	def = crew->def;
	frt = crew->frt;
	gun = crew->gun;
	leader=crew->leader;
	max_atk = crew->max_atk;
	max_def = crew->max_def;
	max_gun = crew->max_gun;
	max_sail = crew->max_sail;
	member = crew->member;
	max_men = crew->max_men;
	name = crew->name;
	price = crew->price;
	sail = crew->sail;
	spd = crew->spd;
	str = crew->str;
	filename = crew->filename;

	UpdateData(false);

	return TRUE;
}
