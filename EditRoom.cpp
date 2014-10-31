#include "stdafx.h"
#include "WinDE.h"
#include "EditRoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

EditRoom::EditRoom(CWnd* pParent /*=NULL*/)
	: CDialog(EditRoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditRoom)
	current_dir = 0;
	current_strength = 0;
	room_desc = _T("A non-descript room.");
	room_name = _T("An Unamed Room.");
	vnum = 0;
	fall_chance = 0;
	lighting = 0;
	sector = 0;
	//}}AFX_DATA_INIT

	if(room_data::def_room)
	{
		current_dir = room_data::def_room->current_dir;
		current_strength = room_data::def_room->current;
		room_desc = room_data::def_room->description;
		room_name = room_data::def_room->name;
		fall_chance = room_data::def_room->fall_chance;
		lighting = room_data::def_room->light;
		sector = room_data::def_room->sector_type;
	}
}

void EditRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditRoom)
	DDX_CBIndex(pDX, IDC_CURRENT_DIR, current_dir);
	DDX_Text(pDX, IDC_CURRENT_STRENGTH, current_strength);
	DDV_MinMaxInt(pDX, current_strength, 0, 100);
	DDX_Text(pDX, IDC_EDIT_ROOM_DESC, room_desc);
	DDX_Text(pDX, IDC_EDIT_ROOM_NAME, room_name);
	DDX_Text(pDX, IDC_EDIT_ROOM_VNUM, vnum);
	DDX_Text(pDX, IDC_FALL_CHANCE, fall_chance);
	DDV_MinMaxInt(pDX, fall_chance, 0, 100);
	DDX_Text(pDX, IDC_LIGHTING, lighting);
	DDV_MinMaxInt(pDX, lighting, 0, 100);
	DDX_CBIndex(pDX, IDC_SECTOR, sector);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(EditRoom, CDialog)
	//{{AFX_MSG_MAP(EditRoom)
	ON_BN_CLICKED(IDC_EDIT_EXITS, OnEditExits)
	ON_BN_CLICKED(IDC_ROOM_FLAGS, OnRoomFlags)
	ON_BN_CLICKED(IDC_EXTRA_DESCS, OnExtraDescs)
	ON_BN_CLICKED(IDC_DELETE_ROOM, OnDeleteRoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL EditRoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	
	CComboBox *pCmb = (CComboBox *)GetDlgItem(IDC_SECTOR);
	
	for(i=SECT_INSIDE;i < SECT_MAX; i++) 
		pCmb->InsertString(i, sector_names[i][0]);
	
	pCmb->SetCurSel(sector);
	
	pCmb = (CComboBox *)GetDlgItem(IDC_CURRENT_DIR);
	
	for(i = DIR_NORTH; i < MAX_DIR; i++)
		pCmb->InsertString(i, dir_name[i]);

	pCmb->SetCurSel(current_dir);

	return TRUE;
}

void EditRoom::OnEditExits() 
{
	DlgEditExits dlg_exits(this);
	int i, ret;

	for(i = 0; i < MAX_DIR; i++)
		dlg_exits.exits[i] = room->exit[i];

	dlg_exits.in_room = room->vnum;

	ret = dlg_exits.DoModal();

	if(ret == IDOK){
		for(i = 0; i < MAX_DIR; i++)
			room->exit[i] = dlg_exits.exits[i];
	}	
}

void EditRoom::OnRoomFlags() 
{
	DlgRoomFlags rf(this);
	
	rf.room = room;

	rf.DoModal();
}

void EditRoom::OnExtraDescs() 
{
	DlgExtraDesc ed(this);
	extra_desc *ped, *next;
	int ret;
	
	ed.old_ed_list = room->first_extra_descr;
	ed.last_old_ed = room->last_extra_desc;
	ed.cur_ed = ed.old_ed_list;

	ret = ed.DoModal();

	if(ret == IDOK) {
		if(room->last_extra_desc != NULL) 
			room->last_extra_desc->next = ed.first_new_ed;
	    else
			room->first_extra_descr = ed.first_new_ed;

			room->last_extra_desc = ed.last_new_ed;
		
		for(ped = room->first_extra_descr; ped; ped = next) {
			if(ped == NULL)
				break;
		
			if(ped->deleted == true || ped->keyword == "" ) {
				if(ped->prev != NULL)
					ped->prev->next = ped->next;
				if(ped->next != NULL)
					ped->next->prev = ped->prev;
				
				if(ped == room->first_extra_descr)
					room->first_extra_descr = ped->next;
				if(ped == room->last_extra_desc)
					room->last_extra_desc = ped->prev;
			
				next = ped->next;
				
				delete ped;
				
				ped = next;
			}
			else  {
				next = ped->next;
			}
		}
	}
	else if(ret == IDCANCEL) {
		for(ped = ed.first_new_ed; ped; ped = next) {
			if(ped == NULL)
				break;
			
			next = ped->next;
			delete ped;
		}
		for(ped = room->first_extra_descr; ped; ped = ped->next) {
			if(ped == NULL)
				break;
		
			if(ped->deleted == true) 
				ped->deleted = false;
		}
	}
}

void EditRoom::OnCancel() 
{	
	int i;

	if(!GetRoomByVnum(vnum)) {
		extra_desc *ex, *next;

		for(i = 0; i < MAX_DIR; i++) {
			if(room->exit[i] != NULL)
				delete room->exit[i];
		}

		for(ex = room->first_extra_descr; ex; ex = next) {
			if(ex) {
				next = ex->next;
				delete ex;
			}
		}

		if(room) {
			((CWinDEDlg *)this->GetParent())->RemoveItem(room->m_tThis);
			delete room;
		}
	}
	
	CDialog::OnCancel();
}

void EditRoom::OnDeleteRoom() 
{
	((CWinDEDlg *)this->GetParent())->RemoveItem(room->m_tThis);

	if(GetRoomByVnum(vnum))
		room->RemoveFromList();
	else
		delete room;

	room = NULL;

	CDialog::OnCancel();
}

void EditRoom::OnOK() 
{
	CString str;
	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_ROOM_VNUM);
	UpdateData(true);

	room->description	= room_desc;
	room->name			= room_name;

	room->vnum			= vnum;
	room->light			= lighting;
	room->sector_type	= sector;
	room->current_dir	= current_dir;
	room->current		= current_strength;
	room->fall_chance   = fall_chance;
	
	if(vnum <= 0) {
		MessageBox("Vnums less than 1 not allowed.");
		edit->SetFocus();
		edit->SetSel(0, edit->GetWindowTextLength());
		return;
	}
	
	if(!(GetRoomByVnum(vnum))) {
		room->AddToList();
		
		if(room->vnum == room_data::room_hi_vnum)
			room_data::room_hi_vnum++;
	} else if(room != GetRoomByVnum(vnum)) {
		str.Format("Vnum %d is already in use!", vnum);
		MessageBox(str, "Duplicate Vnum!", MB_OK);
		
		edit->SetFocus();
		edit->SetSel(0, edit->GetWindowTextLength());
		return;
	} 

	CDialog::OnOK();
}
