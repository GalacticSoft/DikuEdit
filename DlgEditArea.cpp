#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditArea::DlgEditArea(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditArea::IDD, pParent)
{
	area = NULL;

	//{{AFX_DATA_INIT(DlgEditArea)
	author = _T("Unknown");
	high_level = 1;
	defender_vnum = 0;
	barracks_vnum = 0;
	jail_vnum = 0;
	judge_vnum = 0;
	low_level = 1;
	high_reset = 0;
	reset_message = _T("You hear some strange noises.");
	filename = _T("Unnamed");
	squads = 0;
	starting_vnum = 1;
	justice = 0;
	reset_mode = 0;
	name = _T("Unnamed");
	low_reset = 0;
	//}}AFX_DATA_INIT
	
	area_flags = 0;
}

void DlgEditArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditArea)
	DDX_Text(pDX, IDC_AUTHOR, author);
	DDX_Text(pDX, IDC_HIGH_LEVEL, high_level);
	DDV_MinMaxInt(pDX, high_level, 1, 65);
	DDX_Text(pDX, IDC_DEFENDER_VNUM, defender_vnum);
	DDX_Text(pDX, IDC_BARRACKS_VNUM, barracks_vnum);
	DDX_Text(pDX, IDC_JAIL_VNUM, jail_vnum);
	DDX_Text(pDX, IDC_JUDGE_VNUM, judge_vnum);
	DDX_Text(pDX, IDC_LOW_LEVEL, low_level);
	DDV_MinMaxInt(pDX, low_level, 1, 65);
	DDX_Text(pDX, IDC_HIGH_RESET, high_reset);
	DDX_Text(pDX, IDC_RESET_MESSAGE, reset_message);
	DDX_Text(pDX, IDC_SAVE_AS, filename);
	DDX_Text(pDX, IDC_SQUADS, squads);
	DDX_Text(pDX, IDC_STARTING_VNUM, starting_vnum);
	DDX_CBIndex(pDX, IDC_JUSTICE, justice);
	DDX_CBIndex(pDX, IDC_RESET_MODE, reset_mode);
	DDX_Text(pDX, IDC_AREA_NAME, name);
	DDX_Text(pDX, IDC_LOW_RESET, low_reset);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditArea, CDialog)
	//{{AFX_MSG_MAP(DlgEditArea)
	ON_CBN_SELCHANGE(IDC_JUSTICE, OnSelchangeJustice)
	ON_CBN_SELCHANGE(IDC_RESET_MODE, OnSelchangeResetMode)
	ON_BN_CLICKED(IDC_DEFENDER_LIST, OnDefenderList)
	ON_BN_CLICKED(IDC_BARRACKS_LIST, OnBarracksList)
	ON_BN_CLICKED(IDC_JAIL_LIST, OnJailList)
	ON_BN_CLICKED(IDC_JUDGE_LIST, OnJudgeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEditArea::OnOK() 
{
	if(area) 
	{
		UpdateData(true);

		area->author = author;
		area->ulv = high_level;
		area->defender = defender_vnum;
		area->barracks = barracks_vnum;
		area->jail = jail_vnum;
		area->judge = judge_vnum;
		area->llv = low_level;
		area->ulifespan = high_reset;
		area->llifespan = low_reset;
		area->resetmsg = reset_message;
		area->path = filename;
		area->squads = squads;
		area->vnum = starting_vnum;
		area->justice = justice;
		area->resetmode = reset_mode;
		area->name = name;
		area->defender_num = 5;

		CButton *cb;
		
		cb = (CButton*)GetDlgItem(IDC_AREA_SILENT);
		if(cb->GetCheck()) {
			if(!IS_SET(area_flags, ZONE_SILENT)) 
				SET_BIT(area_flags, ZONE_SILENT);
		} else {
			if(IS_SET(area_flags, ZONE_SILENT))
				REMOVE_BIT(area_flags, ZONE_SILENT);
		}

		cb = (CButton*)GetDlgItem(IDC_AREA_SAFE);
		if(cb->GetCheck()) {
			if(!IS_SET(area_flags, ZONE_SAFE))
				SET_BIT(area_flags, ZONE_SAFE);
		} else {
			if(IS_SET(area_flags, ZONE_SAFE))
				REMOVE_BIT(area_flags, ZONE_SAFE);
		}

		cb = (CButton*)GetDlgItem(IDC_AREA_HOMETOWN);
		if(cb->GetCheck()) {
			if(!IS_SET(area_flags, ZONE_HOMETOWN))
				SET_BIT(area_flags, ZONE_HOMETOWN);
		} else {
			if(IS_SET(area_flags, ZONE_HOMETOWN))
				REMOVE_BIT(area_flags, ZONE_HOMETOWN);
		}

		cb = (CButton*)GetDlgItem(IDC_AREA_NO_TELEPORT);
		if(cb->GetCheck()) {
			if(!IS_SET(area_flags, ZONE_NO_TELEPORT))
				SET_BIT(area_flags, ZONE_NO_TELEPORT);
		} else {
			if(IS_SET(area_flags, ZONE_NO_TELEPORT))
				REMOVE_BIT(area_flags, ZONE_NO_TELEPORT);
		}
		
		area->area_flags = area_flags;

		room_data::room_hi_vnum = starting_vnum;
		mob_data::high_mob_vnum = starting_vnum;
		object_data::high_obj_vnum = starting_vnum;
		
		UpdateData(false);
	}

	CDialog::OnOK();
}

BOOL DlgEditArea::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComboBox *pCmb = (CComboBox *)GetDlgItem(IDC_JUSTICE);

	pCmb->InsertString(0, "No Justice");
	pCmb->InsertString(JUSTICE_GOOD,        "Crimes Illegal, Evils Outlawed");
	pCmb->InsertString(JUSTICE_EVIL,		"Crimes Legal, Goods Outlawed");
	pCmb->InsertString(JUSTICE_NEUTRAL,     "Crimes Illegal, all welcome");
	pCmb->InsertString(JUSTICE_NEUT_CLOSED, "Crimes Illegal, Goods and Evils Outlawed");
	pCmb->InsertString(JUSTICE_LAWFUL_EVIL, "Crimes Illegal, Goods Outlawed");
	pCmb->InsertString(JUSTICE_CHAOTIC_GOOD,"Crimes Legal, Evils Outlawed");
	pCmb->InsertString(JUSTICE_CHAOTIC_NEUT,"Crimes Legal, Goods and Evils Outlawed");
	pCmb->InsertString(JUSTICE_CLOSED_GOOD, "Crimes Illegal, Evil and Neutral Outlawed");
	pCmb->InsertString(JUSTICE_CLOSED_EVIL, "Crimes Legal, Good and Neutral Outlawed");
	
	pCmb->SetCurSel(justice);

	if(pCmb->GetCurSel() > 0)
	{
		CWnd *ctrl;

		ctrl = (CEdit*)GetDlgItem(IDC_DEFENDER_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_DEFENDER_LIST);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_BARRACKS_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_BARRACKS_LIST);
		ctrl->EnableWindow(true);
		
		ctrl = (CEdit*)GetDlgItem(IDC_JAIL_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_JAIL_LIST);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_SQUADS);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_JUDGE_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_JUDGE_LIST);
		ctrl->EnableWindow(true);
	}

	pCmb = (CComboBox*)GetDlgItem(IDC_RESET_MODE);
	
	pCmb->InsertString(ZONE_NO_RESET, "Doesn't Reset");
	pCmb->InsertString(ZONE_RESET_EMPTY, "Resets When Empty");
	pCmb->InsertString(ZONE_RESET_ALWAYS, "Always Resets");

	pCmb->SetCurSel(reset_mode);
		
	if(pCmb->GetCurSel() > 0)
	{
		CWnd *ctrl;

		ctrl = (CEdit*)GetDlgItem(IDC_LOW_RESET);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_HIGH_RESET);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_RESET_MESSAGE);
		ctrl->EnableWindow(true);
	}

	if(area)
		area_flags = area->area_flags;

	CButton *cb = (CButton*)GetDlgItem(IDC_AREA_NO_TELEPORT);
	if(IS_SET(area_flags, ZONE_NO_TELEPORT))
		cb->SetCheck(true);

	cb = (CButton*)GetDlgItem(IDC_AREA_SILENT);
	if(IS_SET(area_flags, ZONE_SILENT))
		cb->SetCheck(true);

	cb = (CButton*)GetDlgItem(IDC_AREA_SAFE);
	if(IS_SET(area_flags, ZONE_SAFE))
		cb->SetCheck(true);

	cb = (CButton*)GetDlgItem(IDC_AREA_HOMETOWN);
	if(IS_SET(area_flags, ZONE_HOMETOWN))
		cb->SetCheck(true);

	return TRUE;
}

void DlgEditArea::OnSelchangeJustice() 
{
	CComboBox *cb = (CComboBox*)GetDlgItem(IDC_JUSTICE);

	UpdateData(true);

	if(cb->GetCurSel() > 0)
	{
		CWnd *ctrl;

		ctrl = (CEdit*)GetDlgItem(IDC_DEFENDER_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_DEFENDER_LIST);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_BARRACKS_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_BARRACKS_LIST);
		ctrl->EnableWindow(true);
		
		ctrl = (CEdit*)GetDlgItem(IDC_JAIL_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_JAIL_LIST);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_SQUADS);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_JUDGE_VNUM);
		ctrl->EnableWindow(true);

		ctrl = (CButton*)GetDlgItem(IDC_JUDGE_LIST);
		ctrl->EnableWindow(true);
	}
	
	UpdateData(false);
}

void DlgEditArea::OnSelchangeResetMode() 
{
	CComboBox *cb = (CComboBox*)GetDlgItem(IDC_RESET_MODE);

	UpdateData(true);

	if(cb->GetCurSel() > 0)
	{
		CWnd *ctrl;

		ctrl = (CEdit*)GetDlgItem(IDC_LOW_RESET);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_HIGH_RESET);
		ctrl->EnableWindow(true);

		ctrl = (CEdit*)GetDlgItem(IDC_RESET_MESSAGE);
		ctrl->EnableWindow(true);
	}

	UpdateData(false);
}

void DlgEditArea::OnDefenderList() 
{
	DlgEnterVnum dlg_vnum(this);
	mob_data *mob;

	int ret;

	dlg_vnum.type = MOBILE;
	dlg_vnum.vnum = 0;

	ret = dlg_vnum.DoModal();
	
	if(ret == IDOK) {
		mob = GetMobByVnum(dlg_vnum.vnum);
		
		if(mob) {
			this->defender_vnum = mob->vnum;
			UpdateData(false);
		} else {
			CString str;
			str.Format("No Mob With Vnum: %d", dlg_vnum.vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	
}

void DlgEditArea::OnBarracksList() 
{
	DlgEnterVnum dlg_vnum(this);
	room_data *room;

	int ret;

	dlg_vnum.type = ROOM;
	dlg_vnum.vnum = 0;

	ret = dlg_vnum.DoModal();
	
	if(ret == IDOK) {
		room = GetRoomByVnum(dlg_vnum.vnum);
		
		if(room) {
			this->barracks_vnum = room->vnum;
			UpdateData(false);
		} else {
			CString str;
			str.Format("No Room With Vnum: %d", dlg_vnum.vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	
}

void DlgEditArea::OnJailList() 
{
	DlgEnterVnum dlg_vnum(this);
	room_data *room;

	int ret;

	dlg_vnum.type = ROOM;
	dlg_vnum.vnum = 0;

	ret = dlg_vnum.DoModal();
	
	if(ret == IDOK) {
		room = GetRoomByVnum(dlg_vnum.vnum);
		
		if(room) {
			this->jail_vnum = room->vnum;
			UpdateData(false);
		} else {
			CString str;
			str.Format("No Room With Vnum: %d", dlg_vnum.vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	
	
}

void DlgEditArea::OnJudgeList() 
{
	DlgEnterVnum dlg_vnum(this);
	room_data *room;

	int ret;

	dlg_vnum.type = ROOM;
	dlg_vnum.vnum = 0;

	ret = dlg_vnum.DoModal();
	
	if(ret == IDOK) {
		room = GetRoomByVnum(dlg_vnum.vnum);
		
		if(room) {
			this->judge_vnum = room->vnum;
			UpdateData(false);
		} else {
			CString str;
			str.Format("No Room With Vnum: %d", dlg_vnum.vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	
}
