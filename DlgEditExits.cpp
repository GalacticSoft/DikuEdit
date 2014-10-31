#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditExits.h"
#include "DlgGuardFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditExits::DlgEditExits(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditExits::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEditExits)
	exit_desc = _T("");
	exit_keyword = _T("");
	key_vnum = 0;
	to_room = 0;
	//}}AFX_DATA_INIT
	
	ex = 0;
}


void DlgEditExits::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditExits)
	DDX_Control(pDX, IDC_TO_ROOM, m_ToRoom);
	DDX_Text(pDX, IDC_EXIT_DESC, exit_desc);
	DDX_Text(pDX, IDC_EXIT_KEYWORD, exit_keyword);
	DDX_Text(pDX, IDC_KEY_VNUM, key_vnum);
	DDX_Text(pDX, IDC_TO_ROOM, to_room);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditExits, CDialog)
	//{{AFX_MSG_MAP(DlgEditExits)
	ON_BN_CLICKED(IDC_ROOM_LIST, OnRoomList)
	ON_BN_CLICKED(IDC_KEY_LIST, OnKeyList)
	ON_BN_CLICKED(IDC_EXIT_UP, OnExitUp)
	ON_BN_CLICKED(IDC_EXIT_NW, OnExitNw)
	ON_BN_CLICKED(IDC_EXIT_NORTH, OnExitNorth)
	ON_BN_CLICKED(IDC_EXIT_NE, OnExitNe)
	ON_BN_CLICKED(IDC_EXIT_WEST, OnExitWest)
	ON_BN_CLICKED(IDC_EXIT_EAST, OnExitEast)
	ON_BN_CLICKED(IDC_EXIT_SW, OnExitSw)
	ON_BN_CLICKED(IDC_EXIT_SOUTH, OnExitSouth)
	ON_BN_CLICKED(IDC_EXIT_SE, OnExitSe)
	ON_BN_CLICKED(IDC_EXIT_DOWN, OnExitDown)
	ON_BN_CLICKED(IDC_REVERSE_EXIT, OnReverseExit)
	ON_BN_CLICKED(IDC_GUARD_FLAGS, OnGuardFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEditExits::OnRoomList() 
{
	DlgVnumList vl(this);
	int ret;

	vl.vnum = 0;
	vl.type = ROOM;

	ret = vl.DoModal( );

	if(ret == IDOK) {
		this->to_room = vl.vnum;
		UpdateData(false);
	}
}

void DlgEditExits::OnKeyList() 
{
	DlgVnumList vl(this);
	int ret;

	vl.vnum = 0;
	vl.type = KEY;

	ret = vl.DoModal( );

	if(ret == IDOK) {
		this->key_vnum = vl.vnum;
		UpdateData(false);
	}
}

void DlgEditExits::OnExitUp() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();
	
	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("Up");
	
	ex = DIR_UP;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");

	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}

	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitNw() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("North West");
	
	ex = DIR_NORTHWEST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitNorth() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("North");
	
	ex = DIR_NORTH;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();
		
		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);	
}

void DlgEditExits::OnExitNe() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("North East");
	
	ex = DIR_NORTHEAST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitWest() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("West");
	
	ex = DIR_WEST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitEast() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("East");
	
	ex = DIR_EAST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitSw() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();

	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("South West");
	
	ex = DIR_SOUTHWEST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitSouth() 
{
	UpdateData(true);

	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();
	
	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}
	
	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("South");
	
	ex = DIR_SOUTH;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
	
}

void DlgEditExits::OnExitSe() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();
	
	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("South East");
	
	ex = DIR_SOUTHEAST;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnExitDown() 
{
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();
	
	if(exits[ex]->vnum == 0) {
		delete exits[ex];
		exits[ex] = NULL;
	}

	CStatic *txt_dir = (CStatic *)GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("Down");
	
	ex = DIR_DOWN;
	
	if(exits[ex] == NULL) {
		exits[ex] = new exit_data;	
		exit_desc = "";
		exit_keyword = "";
		key_vnum = 0;
		to_room = 0;
		((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(false);
		GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Make Reverse Exit");
	} else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();

		room_data *rm;
		if((rm = GetRoomByVnum(to_room))) 
		{	
			if(rm->exit[rev_dir[ex]]) 
			{
				if(rm->exit[rev_dir[ex]]->vnum == in_room)
				{
					((CButton*)GetDlgItem(IDC_REVERSE_EXIT))->SetCheck(true);
					GetDlgItem(IDC_REVERSE_EXIT)->SetWindowText("Delete Reverse Exit");
				}
			}
		}
	}
	
	UpdateData(false);
}

void DlgEditExits::OnOK() 
{	
	UpdateData(true);
	
	exits[ex]->description = exit_desc;
	exits[ex]->keyword = exit_keyword;
	exits[ex]->key = key_vnum;
	exits[ex]->vnum = to_room;
	exits[ex]->exit_info = CheckDoorBits();
	
	for(int i = 0; i < MAX_DIR; i++)
	{
		if(!exits[i])
			continue;

		if(exits[i]->vnum == 0) 
		{
			if(exits[i] != NULL) 
			{
				delete exits[i];
				exits[i] = NULL;
			}
		}
	}

	CDialog::OnOK();
}

void DlgEditExits::OnCancel() 
{
	for(int i = 0; i < MAX_DIR; i++) 
	{
		if(!exits[i])
			continue;

		if(exits[i]->vnum == 0) 
		{
			if(exits[i] != NULL) 
			{
				delete exits[i];
				exits[i] = NULL;
			}
		}
	}

	CDialog::OnCancel();
}

BOOL DlgEditExits::OnInitDialog() 
{
	ex = DIR_NORTH;
	
	if(this->exits[ex] == NULL)
		this->exits[ex] = new exit_data;
	else {
		exit_desc = exits[ex]->description;
		exit_keyword = exits[ex]->keyword;
		key_vnum = exits[ex]->key;
		to_room = exits[ex]->vnum;
		SetDoorBits();
		
		if(to_room > 0) 
		{
			room_data *room;
			room = GetRoomByVnum(to_room);

			if(room && room->exit[rev_dir[ex]])
			{
				if(room->exit[rev_dir[ex]]->vnum == in_room) 
				{
					CButton *bn;
					bn = (CButton*)GetDlgItem(IDC_REVERSE_EXIT);
					bn->SetCheck(true);
					bn->SetWindowText("Delete Reverse Exit");
				}
			}
		}
		
		UpdateData(false);
		
		
	}

	CButton *north = (CButton*)this->GetDlgItem(IDC_EXIT_NORTH);
	north->SetCheck(true);
	
	CStatic *txt_dir = (CStatic *)this->GetDlgItem(IDC_STATIC_DIR);
	txt_dir->SetWindowText("North");
	
	CDialog::OnInitDialog();
	
	VERIFY(key.AutoLoad(IDC_KEY_LIST, this));
	
	return TRUE;  
}

int DlgEditExits::CheckDoorBits()
{
	int bits = 0;
	
	CButton *b = (CButton *)GetDlgItem(IDC_HAS_DOOR);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_ISDOOR))
			SET_BIT(bits, EX_ISDOOR);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_ISDOOR)) {
			REMOVE_BIT(bits, EX_ISDOOR);
		}
	}

	b = (CButton *)GetDlgItem(IDC_SECRET);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_SECRET))
			SET_BIT(bits, EX_SECRET);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_SECRET)) {
			REMOVE_BIT(bits, EX_SECRET);
		}
	}

	b = (CButton *)GetDlgItem(IDC_LOCKED);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_LOCKED))
			SET_BIT(bits, EX_LOCKED);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_LOCKED)) {
			REMOVE_BIT(bits, EX_LOCKED);
		}
	}

	b = (CButton *)GetDlgItem(IDC_PICK_PROOF);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_PICKPROOF))
			SET_BIT(bits, EX_PICKPROOF);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_PICKPROOF)) {
			REMOVE_BIT(bits, EX_PICKPROOF);
		}
	}
	
	b = (CButton *)GetDlgItem(IDC_PASS_PROOF);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_PASSPROOF))
			SET_BIT(bits, EX_PASSPROOF);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_PASSPROOF)) {
			REMOVE_BIT(bits, EX_PASSPROOF);
		}
	}

	b = (CButton *)GetDlgItem(IDC_BASH_PROOF);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_BASHPROOF))
			SET_BIT(bits, EX_BASHPROOF);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_BASHPROOF)) {
			REMOVE_BIT(bits, EX_BASHPROOF);
		}
	}

	b = (CButton *)GetDlgItem(IDC_CLOSED);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_CLOSED))
			SET_BIT(bits, EX_CLOSED);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_CLOSED)) {
			REMOVE_BIT(bits, EX_CLOSED);
		}
	}

	b = (CButton *)GetDlgItem(IDC_EAT_KEY);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_EAT_KEY))
			SET_BIT(bits, EX_EAT_KEY);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_EAT_KEY)) {
			REMOVE_BIT(bits, EX_EAT_KEY);
		}
	}

	b = (CButton *)GetDlgItem(IDC_BLOCKED);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_BLOCKED))
			SET_BIT(bits, EX_BLOCKED);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_BLOCKED)) {
			REMOVE_BIT(bits, EX_BLOCKED);
		}
	}

	b = (CButton *)GetDlgItem(IDC_BASHED);
	if(b->GetCheck()) {
		if(!IS_SET(bits, EX_BASHED))
			SET_BIT(bits, EX_BASHED);
		b->SetCheck(false);
	} else {
		if(IS_SET(bits, EX_BASHED)) {
			REMOVE_BIT(bits, EX_BASHED);
		}
	}

	return bits;
}


void DlgEditExits::SetDoorBits()
{
	CButton *b = (CButton *)GetDlgItem(IDC_HAS_DOOR);
	if(IS_SET(exits[ex]->exit_info, EX_ISDOOR))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_SECRET);
	if(IS_SET(exits[ex]->exit_info, EX_SECRET))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_LOCKED);
	if(IS_SET(exits[ex]->exit_info, EX_LOCKED))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_PICK_PROOF);
	if(IS_SET(exits[ex]->exit_info, EX_PICKPROOF))
		b->SetCheck(true);
	
	b = (CButton *)GetDlgItem(IDC_PASS_PROOF);
	if(IS_SET(exits[ex]->exit_info, EX_PASSPROOF))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_BASH_PROOF);
	if(IS_SET(exits[ex]->exit_info, EX_BASHPROOF))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_CLOSED);
	if(IS_SET(exits[ex]->exit_info, EX_CLOSED))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_EAT_KEY);
	if(IS_SET(exits[ex]->exit_info, EX_EAT_KEY))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_BLOCKED);
	if(IS_SET(exits[ex]->exit_info, EX_BLOCKED))
		b->SetCheck(true);

	b = (CButton *)GetDlgItem(IDC_BASHED);
	if(IS_SET(exits[ex]->exit_info, EX_BASHED))
		b->SetCheck(true);
}

void DlgEditExits::OnReverseExit() 
{
	CButton *bn;
	room_data *room;
	int dir = rev_dir[ex];

	UpdateData(true);
	
	room = GetRoomByVnum(to_room);

	bn = (CButton*)GetDlgItem(IDC_REVERSE_EXIT);

	if(bn->GetCheck()) 
	{
		if(room) 
		{
			if(!room->exit[dir])
			{
				room->exit[dir] = new exit_data;
				goto NewExit;
			} 
			else if(room->exit[dir]->vnum != in_room)
			{
				CString str;
				str.Format("Room %d already has reverse exit to room %d.\nDelete and Replace with New Exit?",
					room->vnum, room->exit[dir]->vnum);
				int ret = MessageBox(str, "Exit Already Exists!", MB_YESNO);

				if(ret == IDYES) 
				{
					goto NewExit;
				}	
				else if(ret == IDNO)
				{
					bn->SetCheck(false);
				}
			}
		}
	} 
	else 
	{
		if(room) 
		{
			if(room->exit[dir] && room->exit[dir]->vnum == in_room)
			{
				delete room->exit[dir];
				room->exit[dir] = NULL;
				bn->SetWindowText("Make Reverse Exit");
			}
		}
	}

	return;

NewExit:
			room->exit[dir]->description = exit_desc;
			room->exit[dir]->key = key_vnum;
			room->exit[dir]->keyword = exit_keyword;
			room->exit[dir]->vnum = in_room;
			room->exit[dir]->exit_info = CheckDoorBits();
			bn->SetWindowText("Delete Reverse Exit");
}

void DlgEditExits::OnGuardFlags() 
{
	DlgGuardFlags dlg(this);

	dlg.flags = exits[ex]->guardbits;

	int ret = dlg.DoModal();

	if(ret == IDOK)
		exits[ex]->guardbits = dlg.flags;

}
