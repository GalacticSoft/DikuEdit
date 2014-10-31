#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditMob.h"
#include "DlgProgEdit.h"
#include "ProgEditor.h"
#include "DlgSelectAff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditMob::DlgEditMob(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditMob::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEditMob)
	align = 0;
	mob_class = CLASS_NONE;
	mob_desc = _T("A non-descript mob.");
	mob_keywords = _T("mob unnamed");
	level = 1;
	mob_long = _T("An Unnamed Mob is standing here, looking sad.");
	position = POS_STANDING;
	race = RACE_HUMAN;
	sex = SEX_NEUTRAL;
	mob_short = _T("an unnamed mob");
	size = SIZE_ANY;
	vnum = GetValidVnum(MOBILE);
	//}}AFX_DATA_INIT
}

void DlgEditMob::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditMob)
	DDX_Control(pDX, IDC_MOB_ALIGN, m_Align);
	DDX_Text(		pDX, IDC_MOB_ALIGN,		align);
	DDV_MinMaxInt(	pDX, align, -1000, 1000);
	DDX_CBIndex(	pDX, IDC_MOB_CLASS,		mob_class);
	DDX_Text(		pDX, IDC_MOB_DESC,		mob_desc);
	DDX_Text(		pDX, IDC_MOB_KEYWORDS,	mob_keywords);
	DDX_Text(		pDX, IDC_MOB_LEVEL,		level);
	DDV_MinMaxInt(	pDX, level, 1, 60);
	DDX_Text(		pDX, IDC_MOB_LONG,		mob_long);
	DDX_CBIndex(	pDX, IDC_MOB_POSITION,	position);
	DDX_CBIndex(	pDX, IDC_MOB_RACE,		race);
	DDX_CBIndex(	pDX, IDC_MOB_SEX,		sex);
	DDX_Text(		pDX, IDC_MOB_SHORT,		mob_short);
	DDX_CBIndex(	pDX, IDC_MOB_SIZE,		size);
	DDX_Text(		pDX, IDC_MOB_VNUM,		vnum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditMob, CDialog)
	//{{AFX_MSG_MAP(DlgEditMob)
	ON_BN_CLICKED(IDC_DELETE,		OnDelete)
	ON_BN_CLICKED(IDC_MOB_SHOP,		OnMobShop)
	ON_BN_CLICKED(IDC_MOB_ACT,		OnMobAct)
	ON_BN_CLICKED(IDC_MOB_AFFECTS,  OnMobAffects)
	ON_BN_CLICKED(IDC_QUESTS,		OnQuests)
	ON_BN_CLICKED(IDC_EDIT_PROGS, OnEditProgs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEditMob::OnOK() 
{	
	mob_data *tmp;
	CString str;
	CEdit *ed;
	
	ed = (CEdit*)GetDlgItem(IDC_MOB_VNUM);
	
	UpdateData(true);
	
	if(vnum <= 0) {
		MessageBox("Vnums less than 1 not allowed.");
		ed->SetFocus();
		ed->SetSel(0, ed->GetWindowTextLength());
		return;
	}
	
	tmp = GetMobByVnum(vnum);
	
	if(!tmp || tmp == mob) {
		mob->alignment = align;
		mob->c_class = mob_class;
		mob->description = mob_desc;
		mob->name = mob_keywords;
		mob->level = level;
		mob->long_descr = mob_long;
		mob->position = position;
		mob->race = race;
		mob->sex = sex;
		mob->short_descr = mob_short;
		mob->size = size;
		mob->vnum = vnum;

		UpdateData(false);

		if(!tmp)
			if(mob->vnum == mob_data::high_mob_vnum)
				mob_data::high_mob_vnum++;
		
		CDialog::OnOK();
	} else {
		str.Format("Mob with vnum %d already exists.", vnum);
		MessageBox(str, "Duplicate Vnum!");

		ed->SetFocus();
		ed->SetSel(0, ed->GetWindowTextLength());
	}	
}

BOOL DlgEditMob::OnInitDialog() 
{
	int i, index;
	CComboBox *cb;

	CDialog::OnInitDialog();

	align = mob->alignment;
	mob_class = mob->c_class;
	mob_desc = mob->description;
	mob_keywords = mob->name;
	level = mob->level;
	mob_long = mob->long_descr;
	position = mob->position;
	race = mob->race;
	sex = mob->sex;
	mob_short = mob->short_descr;
	size = mob->size;
	vnum = mob->vnum;

	cb = (CComboBox*)GetDlgItem(IDC_MOB_SEX);

	for(i = SEX_NEUTRAL; i < SEX_MAX; i++)
		cb->InsertString(i, GetSex(i));

	cb->SetCurSel(sex);

	cb = (CComboBox*)GetDlgItem(IDC_MOB_RACE);

	for(i = RACE_HUMAN; i < MAX_RACE; i++)
		cb->InsertString(i, GetRaceName(i));

	cb->SetCurSel(race);

	cb = (CComboBox*)GetDlgItem(IDC_MOB_POSITION);

	for(i = POS_DEAD; i < POS_MAX; i++)
		cb->InsertString(i, GetPosition(i));

	cb->SetCurSel(position);

	cb = (CComboBox*)GetDlgItem(IDC_MOB_CLASS);

	for(i = CLASS_NONE, index = 0; i < MAX_CLASS; i++, index++){
		if(!ClassAvail(i)) {
			index--;
		} else {
			cb->InsertString(index, GetClassName(i));
			cb->SetItemData(index, i);
		}
		
		if(i == mob_class)
			cb->SetCurSel(index);
	}

	cb = (CComboBox*)GetDlgItem(IDC_MOB_SIZE);

	for(i = SIZE_ANY; i < MAX_SIZE; i++)
		cb->InsertString(i, GetSize(i));

	cb->SetCurSel(size);
	
	UpdateData(false);

	return TRUE;
}

void DlgEditMob::OnDelete() 
{
	if(mob) 
	{
		mob->RemoveFromList();
		
		((CWinDEDlg *)this->GetParent())->RemoveItem(mob->m_tThis);

		delete mob;
	}

	mob = NULL;

	OnCancel();
}

void DlgEditMob::OnCancel() 
{	
	CDialog::OnCancel();
}

void DlgEditMob::OnMobShop() 
{
	DlgEditShop dlg;
	int ret;

	if(mob->shop)
		dlg.shop = mob->shop;
	else {
		dlg.shop = new shop_data;
		dlg.shop->keeper = mob->vnum;
	}

	ret = dlg.DoModal();

	if(ret == IDOK)
	{
		if(mob->shop == NULL)
			shop_count++;
	
		mob->shop = dlg.shop;	
	}
}

void DlgEditMob::OnMobAct() 
{
	DlgActFlags dlg;
	int ret;

	dlg.act = mob->act;

	ret = dlg.DoModal();
	
	if(ret == IDOK)
		mob->act = dlg.act;
}

void DlgEditMob::OnMobAffects() 
{	
	DlgSelectAff aff_dlg;

	aff_dlg.type = MOBILE;
	aff_dlg.mob = mob;
	aff_dlg.DoModal();
}

void DlgEditMob::OnQuests() 
{
	DlgQuestEdit dlg_quests(this);
	
	if(mob->quests == NULL)
		mob->quests = new quest_index_data();

	dlg_quests.quests = mob->quests;

	dlg_quests.DoModal();
}

void DlgEditMob::OnEditProgs() 
{
	ProgEditor dlg_prog(this);

	dlg_prog.type = MOBILE;
	dlg_prog.mob = mob;

	dlg_prog.DoModal();
}
