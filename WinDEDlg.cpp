#include "stdafx.h"
#include "WinDE.h"
#include "WinDEDlg.h"
#include "Resource.h"
#include "BvCalc.h"

#include "ColorEditWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int	room_count;
int	mob_count;
int	obj_count;
int	shop_count;
int	quest_count;

char CWinDEDlg::class_name[] = "CWinDEDlg";
int  CWinDEDlg::class_index = WIN_DE_DLG;

char area_data::class_name[] = "area_data";
int area_data::class_index = AREA_DATA;

area_data* area_data::area = NULL;
unsigned int	editor_flags;

CWinDEDlg::CWinDEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinDEDlg::IDD, pParent)
{
	in_room = NULL;
	
	room_count = 0;
	mob_count = 0;
	obj_count = 0;
	shop_count = 0;
	quest_count = 0;
	
	editor_flags = 0;
	timer = 5;

	SET_BIT(editor_flags, SAVE_AREA_FORMAT);
	SET_BIT(editor_flags, OPEN_AREA_FORMAT);
	SET_BIT(editor_flags, SHOW_COMPAS);
	SET_BIT(editor_flags, WINDOW_VISIBLE);
	SET_BIT(editor_flags, SHOW_MAP);

	def_color = lightgrey;
	echo_color = yellow;

	ZeroMemory(&niData, sizeof(NOTIFYICONDATA));

	//{{AFX_DATA_INIT(CWinDEDlg)
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	tray_icon = m_hIcon;
}

void CWinDEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinDEDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinDEDlg, CDialog)
	//{{AFX_MSG_MAP(CWinDEDlg)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_COMMAND(ID_MOBILES_DELETEMOB,		OnMobilesDeletemob)
	ON_BN_CLICKED(ID_TOOL_EDIT_MOB,			OnMobilesEditmob)
	ON_BN_CLICKED(ID_TOOL_CREATE_MOB,		OnMobilesNewmob)
	ON_COMMAND(ID_OBJECTS_DELETEOBJECT,		OnObjectsDeleteobject)
	ON_BN_CLICKED(ID_TOOL_EDIT_OBJ,			OnObjectsEditobject)
	ON_BN_CLICKED(ID_TOOL_CREATE_OBJ,		OnObjectsNewobject)
	ON_COMMAND(ID_ROOMS_DELETEROOM,			OnRoomsDeleteroom)
	ON_BN_CLICKED(ID_TOOL_EDIT_ROOM,		OnRoomsEditroom)
	ON_BN_CLICKED(ID_TOOL_NEW_ROOM,			OnRoomsNewroom)
	ON_BN_CLICKED(IDC_NORTHWEST,			OnNorthWest)
	ON_BN_CLICKED(IDC_NORTH,				OnNorth)
	ON_BN_CLICKED(IDC_NORTHEAST,			OnNorthEast)
	ON_BN_CLICKED(IDC_WEST,					OnWest)
	ON_BN_CLICKED(IDC_LOOK,					OnLook)
	ON_BN_CLICKED(IDC_EAST,					OnEast)
	ON_BN_CLICKED(IDC_SOUTH,				OnSouth)
	ON_BN_CLICKED(IDC_SOUTHWEST,			OnSouthWest)
	ON_BN_CLICKED(IDC_SOUTHEAST,			OnSouthEast)
	ON_BN_CLICKED(IDC_SAVE,					OnSave)
	ON_BN_CLICKED(ID_TOOL_SETTING,			OnSettings)
	ON_BN_CLICKED(ID_OPEN_AREA,				OnOpen)
	ON_BN_CLICKED(IDC_EXIT,					OnExit)
	ON_BN_CLICKED(ID_TOOL_NEW_AREA,			OnNewArea)
	ON_BN_CLICKED(ID_EDIT_AREA,				OnAreaEdit)
	ON_BN_CLICKED(ID_TOOL_COMPAS,			OnDirections)
	ON_BN_CLICKED(ID_MAP,					OnMap)
	ON_COMMAND(ID_AREA_PROPERTIES,			OnAreaProperties)
	ON_BN_CLICKED(IDC_HISTORY,				OnHistory)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_TOOL_CREATE_GRID,		OnCreateGrid)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(ID_SAVE_AREA,				OnSave)
	ON_BN_CLICKED(ID_TOOL_DELETE_MOB,		OnMobilesDeletemob)
	ON_BN_CLICKED(ID_CANNON_BUILDER,        OnShipBuilder)
	ON_BN_CLICKED(ID_BITCALC,		        OnBitCalc)
	ON_BN_CLICKED(ID_STATISTICS,			OnStatistics)
	ON_BN_CLICKED(ID_TOOL_DELETE_OBJ,		OnObjectsDeleteobject)
	ON_BN_CLICKED(ID_SETTINGS,				OnSettings)
	ON_BN_CLICKED(ID_TOOL_DELETE_ROOM,		OnRoomsDeleteroom)
	ON_BN_CLICKED(ID_HELP,					OnHelp)
	ON_COMMAND_EX(ID_TRAYMENU_SAVE,			OnTrayMenu)
	ON_COMMAND_EX(ID_TRAYMENU_CLOSE,		OnTrayMenu)
	ON_COMMAND_EX(ID_TRAYMENU_MINIMIZE,		OnTrayMenu)
	ON_COMMAND_EX(ID_TRAYMENU_MAXIMIZE,		OnTrayMenu)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	//ON_COMMAND_EX_RANGE(ID_HISTORY_0, ID_HISTORY_24, HistoryMenu)
	//ON_MESSAGE(ICON_MESSAGE, OnTrayNotify)
	//}}AFX_MSG_MAP
	

END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] =
{	
    IDC_ROOM_COUNT,
    IDC_MOB_COUNT,
	IDC_OBJ_COUNT,
	IDC_QUEST_COUNT,
	IDC_SHOP_COUNT,
};

BOOL CWinDEDlg::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    // if there is a top level routing frame then let it handle the message
    if (GetRoutingFrame() != NULL) return FALSE;

    // to be thorough we will need to handle UNICODE versions of the message also !!
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
    TCHAR szFullText[512];
    CString strTipText;
    UINT nID = pNMHDR->idFrom;

    if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
        pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
    {
        // idFrom is actually the HWND of the tool 
        nID = ::GetDlgCtrlID((HWND)nID);
    }

    if (nID != 0) // will be zero on a separator
    {
		LoadString(NULL, nID, szFullText, 1000);
        //LoadString(nID, szFullText);
        strTipText=szFullText;

#ifndef _UNICODE
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        }
        else
        {
            _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#else
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
        }
        else
        {
            lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#endif

        *pResult = 0;

        // bring the tooltip window above other popup windows
        ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
            SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
        
        return TRUE;
    }

    return FALSE;
}



BOOL CWinDEDlg::OnInitDialog()
{
	CRect frameRect;
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CDialog::OnInitDialog();

	map.Create(IDD_MAP, this);
	
	dlg.Create(IDD_DIRECTIONS, this);
	dlg.SetWindowPos(&dlg.wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	InitColorControl();

	AdjustToolLine();
	
	InitSplitter();
	
	InitZoneTree();

	InitTrayIcon();

	m_Status.Create(this);
	m_Status.SetIndicators(indicators,5);
	UpdateStatusBar();

	m_Tool.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC );

	INIT_EASYSIZE;
	
	LoadSettings();
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDC_OBJ_COUNT);

	if(!room_data::def_room)
		room_data::def_room = new room_data;

	if(!mob_data::def_mob)
		mob_data::def_mob = new mob_data;

	if(!object_data::def_obj)
		object_data::def_obj = new object_data;

	CrewList::crews.LoadCrews();
	AmmoList::ammos.LoadAmmo();
	CannonList::cannons.LoadCannons();

	OpenCommandLineFile();

	user = new mob_index();
	user->DeleteAllInv();

	return TRUE;
}

void CWinDEDlg::OpenCommandLineFile()
{
	CString str;
	int loc=0;

	str = ::GetCommandLine();
	

	loc = str.ReverseFind('"');

	str = str.Mid(loc+1, str.GetLength()-loc);
	
	str.TrimRight();
	str.TrimLeft();
	
	if(str.GetLength() <= 0)
		return;

	CloseArea();

	AreFileOpen file(str, this);

	AreaLoaded();
	
	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		AddRoom(room);
		
		for(mob_index *mob = room->people; mob; mob = mob->next)
			AddMobToRoom(mob, room);

		for(obj_index *obj = room->contents; obj; obj = obj->next)
			AddObjToRoom(obj, room);
	}

	for(mob_data *mob = mob_data::first_mob; mob; mob = mob->next)
		AddMob(mob);

	for(object_data *obj = object_data::obj_head; obj; obj = obj->next)
		AddObject(obj);

	in_room = room_data::room_list;
	
	LoadDefaults();		
	
	ShowRoom();
	
	map.DrawArea();
}

void CWinDEDlg::InitTrayIcon()
{
    niData.cbSize = sizeof(NOTIFYICONDATA),

    niData.uID = TRAY_ID,

    niData.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP,
	
	strcpy(niData.szTip, "Diku MUD Area Editor"),

    niData.hIcon = m_hIcon,

    niData.hWnd = this->m_hWnd,

    niData.uCallbackMessage = ICON_MESSAGE,
	
	Shell_NotifyIcon(NIM_ADD, &niData);
}

void CWinDEDlg::InitZoneTree()
{
	CRect frameRect;

	GetDlgItem(IDC_ZONETREE_FRAME)->GetWindowRect(frameRect);
	
	ScreenToClient(frameRect);
	frameRect.InflateRect(-2,-2);
	
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS|TVS_HASBUTTONS;    
	zone_tree.CreateEx(WS_EX_CLIENTEDGE, /*"SysTreeView32", "Zone Tree", */ dwStyle, frameRect, this, IDC_ZONETREE);
}

void CWinDEDlg::InitSplitter()
{
	CRect frameRect;

	GetDlgItem(IDC_SPLITTER)->GetWindowRect(frameRect);
	ScreenToClient(frameRect);
	split.Create(WS_CHILD | WS_VISIBLE, frameRect, this, IDC_SPLITTER1);
	GetWindowRect(frameRect);
	ScreenToClient(frameRect);
	split.SetRange(frameRect.left+200, frameRect.right-150);
}

void CWinDEDlg::AdjustToolLine()
{
	CRect frameRect;

	GetDlgItem(IDC_LINE)->GetWindowRect(frameRect);
	ScreenToClient(frameRect);
	frameRect.right += 5;
	GetDlgItem(IDC_LINE)->MoveWindow(frameRect);
}

void CWinDEDlg::InitColorControl()
{
	CRect frameRect;

	GetDlgItem(IDC_EDIT_FRAME)->GetWindowRect(frameRect);
	
	ScreenToClient(frameRect);
	frameRect.InflateRect(-2,-2);

	m_pColorWnd = new ColorEditWnd(this, frameRect,	IDC_DISPLAY, 4, 100, "Terminal");

	m_pColorWnd->SetParent(this);
	m_pColorWnd->SetCharXSpacing(1);
	m_pColorWnd->SetColorizer(&m_colorizer);
	m_pColorWnd->SetReadOnly(true);
	m_pColorWnd->ClearUndoHistory();
	ShowText("&+WWelcome To Diku MUD Area Editor!&n\n&+WCopyright: &+GGalacticSoft &+W(&+GMarissa du Bois&n&+W, 2003-2014)", false);
}

void CWinDEDlg::AddRoom(room_data *room)
{
	if(room)
	{
		room_count++;
		
		UpdateStatusBar();
		
		CString str;
		
		str.Format("%d - %s", room->vnum, StripAnsiChars(room->name));
		
		room->m_tThis = InsertItem(str, m_tRooms, room, room->class_index);
		room->m_tContents = InsertItem(CString("Contents"), room->m_tThis, NULL, CONTENTS);
		room->m_tPeople = InsertItem(CString("Occupants"), room->m_tThis, NULL, PEOPLE);
	}
}

void CWinDEDlg::AddMob(mob_data *mob)
{
	if(mob)
	{
		CString str;

		mob_count++;
			
		UpdateStatusBar();
		
		str.Format("%d - %s", mob->vnum, StripAnsiChars(mob->short_descr));
		
		mob->m_tThis = InsertItem(str, m_tMobiles, mob, mob->class_index);
	}
}

void CWinDEDlg::AddMobToRoom(mob_index *mob, room_data *room)
{
	CString str;
	
	if(mob && room)
	{
		str.Format("%d - %s", mob->vnum, StripAnsiChars(mob->GetShortName()));
		
		mob->m_tThis = InsertItem(str, room->m_tPeople, mob, mob->class_index);
	}
}

void CWinDEDlg::AddObjToRoom(obj_index *obj, room_data *room)
{
	CString str;
	
	if(obj && room)
	{
		str.Format("%d - %s", obj->vnum, StripAnsiChars(obj->GetShortName()));
		
		obj->m_tThis = InsertItem(str, room->m_tContents, obj, obj->class_index);
	}
}

void CWinDEDlg::AddObject(object_data *obj)
{
	CString str;

	if(obj)
	{
		obj_count++;
		
		UpdateStatusBar();
		
		str.Format("%d - %s", obj->vnum, StripAnsiChars(obj->short_descr));
		
		obj->m_tThis = InsertItem(str, m_tObjects, obj, obj->class_index);
	}
}

void CWinDEDlg::UpdateStatusBar()
{
	CString str;
	
	str.Format("Rooms: %d", room_count);
	m_Status.SetPaneText(0, str);
	
	str.Format("Mobiles: %d", mob_count);
	m_Status.SetPaneText(1, str);
	
	str.Format("Objects: %d", obj_count);
	m_Status.SetPaneText(2, str);

	str.Format("Quests: %d", quest_count);
	m_Status.SetPaneText(3, str);

	str.Format("Shops: %d", shop_count);
	m_Status.SetPaneText(4, str);
}

void CWinDEDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam) 
{
	UINT msg;
	UINT id;

	msg = (UINT)lParam;
	id = (UINT)wParam;

	if(id != TRAY_ID)
		return;

	switch(msg) 
	{
	case WM_LBUTTONDBLCLK:
		if(!IS_SET(editor_flags, WINDOW_VISIBLE)) {
			ShowWindow(true);
			SET_BIT(editor_flags, WINDOW_VISIBLE);
		} else {
			ShowWindow(false);
			REMOVE_BIT(editor_flags, WINDOW_VISIBLE);
		}
		break;
	case WM_RBUTTONDOWN:
	case WM_CONTEXTMENU:
		CMenu men;
		CPoint pos;
		
		GetCursorPos(&pos);
		men.LoadMenu(IDR_TRAY_MENU);
		
		if(IS_SET(editor_flags, WINDOW_VISIBLE))
			men.GetSubMenu(0)->EnableMenuItem(ID_TRAYMENU_MINIMIZE, MF_ENABLED);
		else 
			men.GetSubMenu(0)->EnableMenuItem(ID_TRAYMENU_MAXIMIZE, MF_ENABLED);

		men.GetSubMenu(0)->
			TrackPopupMenu(TPM_BOTTOMALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, pos.x, pos.y, this);
		
		break;
	}
}

BOOL CWinDEDlg::OnTrayMenu(UINT id)
{
	switch(id) {
	case ID_TRAYMENU_SAVE:
		OnSave();
		return TRUE;
	case ID_TRAYMENU_CLOSE:
		OnClose();
		return TRUE;
	case ID_TRAYMENU_MINIMIZE:
		REMOVE_BIT(editor_flags, WINDOW_VISIBLE);
		ShowWindow(false);
		return TRUE;
	case ID_TRAYMENU_MAXIMIZE:
		SET_BIT(editor_flags, WINDOW_VISIBLE);
		ShowWindow(true);
		return TRUE;
	}

	return FALSE;
}

void CWinDEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		REMOVE_BIT(editor_flags, WINDOW_VISIBLE);
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

void CWinDEDlg::OnPaint() 
{
	CRect rect;
	GetClientRect(&rect);
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	m_Status.SetPaneInfo(0,0, SBPS_NORMAL, rect.Width()*1/5);
	m_Status.SetPaneInfo(1,0, SBPS_NORMAL, rect.Width()*1/5);
	m_Status.SetPaneInfo(2,0, SBPS_NORMAL, rect.Width()*1/5);
	m_Status.SetPaneInfo(3,0, SBPS_NORMAL, rect.Width()*1/5);
	m_Status.SetPaneInfo(4,0, SBPS_NORMAL, rect.Width()*1/5);
}

HCURSOR CWinDEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinDEDlg::OnNorthWest() 
{
	MoveRoom(DIR_NORTHWEST);
}

void CWinDEDlg::OnNorth() 
{	
	MoveRoom(DIR_NORTH);
}

void CWinDEDlg::OnNorthEast() 
{
	MoveRoom(DIR_NORTHEAST);
}

void CWinDEDlg::OnWest() 
{
	MoveRoom(DIR_WEST);
}

void CWinDEDlg::OnLook() 
{
	Look(CString("room"));
}

void CWinDEDlg::OnEast() 
{
	MoveRoom(DIR_EAST);
}

void CWinDEDlg::OnSouth() 
{
	MoveRoom(DIR_SOUTH);
}

void CWinDEDlg::OnSouthWest() 
{
	MoveRoom(DIR_SOUTHWEST);	
}

void CWinDEDlg::OnSouthEast() 
{
	MoveRoom(DIR_SOUTHEAST);
}

void CWinDEDlg::OnDown() 
{
	MoveRoom(DIR_DOWN);	
}

void CWinDEDlg::OnUp() 
{
	MoveRoom(DIR_UP);	
}

void CWinDEDlg::OnDirections() 
{	
	if(m_Tool.GetButtonStyle(19) == TBBS_CHECKED) {
		dlg.ShowWindow(SW_HIDE);
		m_Tool.SetButtonStyle(19, 0);
		REMOVE_BIT(editor_flags, SHOW_COMPAS);
	} else {
		dlg.ShowWindow(SW_SHOW);
		m_Tool.SetButtonStyle(19, TBBS_CHECKED);
		SET_BIT(editor_flags, SHOW_COMPAS);
	}

	SaveSettings();
}

void CWinDEDlg::OnMap()
{
	if(m_Tool.GetButtonStyle(18) == TBBS_CHECKED) {
		map.ShowWindow(SW_HIDE);
		m_Tool.SetButtonStyle(18, 0);
		REMOVE_BIT(editor_flags, SHOW_MAP);
	} else {
		map.ShowWindow(SW_SHOW);
		m_Tool.SetButtonStyle(18, TBBS_CHECKED);
		SET_BIT(editor_flags, SHOW_MAP);
	}

	SaveSettings();
}

void CWinDEDlg::OnNewRoom() 
{
	EditRoom dlg(this);
	int ret;
	
	dlg.room = new room_data;
	
	dlg.room->vnum = GetValidVnum(ROOM);
	dlg.vnum = dlg.room->vnum;
	
	ret = dlg.DoModal();
		
	if(ret == IDOK) {
		in_room = dlg.room;
		
		ShowRoom();

		AddRoom(dlg.room);	
	}
	
	map.DrawArea();
}

void CWinDEDlg::OnShipBuilder()
{
	ShipBuilder dlg_ship(this);

	dlg_ship.DoModal();
}

void CWinDEDlg::OnStatistics()
{
	DlgAreaStatistics dlg_stats(this);

	dlg_stats.DoModal();
}

void CWinDEDlg::OnEditRoom(int vnum) 
{
	DlgEnterVnum dlg_vnum(this);
	EditRoom dlg_room(this);
	CString str;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = ROOM;

		ret = dlg_vnum.DoModal( );

		vnum = dlg_vnum.vnum;
	} else 
		ret = IDOK;

	if(ret == IDOK) {
		if(!(dlg_room.room = GetRoomByVnum(vnum))) {
			str.Format("No Room With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		} else {
			dlg_room.room_desc			= dlg_room.room->description;
			dlg_room.room_name			= dlg_room.room->name;
			dlg_room.vnum				= dlg_room.room->vnum;
			dlg_room.lighting			= dlg_room.room->light;
			dlg_room.sector				= dlg_room.room->sector_type;
			dlg_room.current_dir		= dlg_room.room->current_dir;
			dlg_room.current_strength	= dlg_room.room->current;

			ret = dlg_room.DoModal( );
			
			if(!dlg_room.room) {
				in_room = room_data::room_list;
				ShowRoom();
				
				room_count--;
				UpdateStatusBar();
			} else {
				str.Format("%d - %s", dlg_room.room->vnum, dlg_room.room->name);
				UpdateItem(str, dlg_room.room->m_tThis);
			}
		}
	}	

	map.DrawArea();
}

void CWinDEDlg::OnNewMob() 
{
	DlgEditMob dlg(this);
	CString str;
	int ret;

	dlg.mob = new mob_data;

	ret = dlg.DoModal();

	if(ret == IDOK){
		if(dlg.mob) {
			dlg.mob->AddToList();
			AddMob(dlg.mob);
		}
	} else if(ret == IDCANCEL) {
		if(dlg.mob) {
			if(dlg.mob->shop) 
					delete dlg.mob->shop;

				if(dlg.mob->quests) {
					talk_data *tmp_t, *next_t;
					quest_data *tmp_q, *next_q;

					for(tmp_t = dlg.mob->quests->messages; tmp_t; tmp_t = next_t) {
						next_t = tmp_t->next;
						delete tmp_t;
					}

					for(tmp_q = dlg.mob->quests->quests; tmp_q; tmp_q = next_q) {
						next_q = tmp_q->next;
						delete tmp_q;
					}
				}
			delete dlg.mob;
		}
	}

	UpdateStatusBar();
}

void CWinDEDlg::OnEditMob(int vnum) 
{
	DlgEnterVnum dlg_vnum(this);
	DlgEditMob dlg_mob(this);
	mob_data *mob;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = MOBILE;
		dlg_vnum.vnum = 0;

		ret = dlg_vnum.DoModal();

		vnum = dlg_vnum.vnum;
	} else 
		ret = IDOK;
	
	if(ret == IDOK) {
		if((mob = GetMobByVnum(vnum))) {
			dlg_mob.mob = mob;
			dlg_mob.DoModal();
			
			if(!dlg_mob.mob) {
				mob_count--;
			} else {
				CString str;
				str.Format("%d - %s", dlg_mob.mob->vnum, dlg_mob.mob->short_descr);
				UpdateItem(str, dlg_mob.mob->m_tThis);
			}
		} else {
			CString str;

			str.Format("No Mob With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}

	UpdateStatusBar();
}

void CWinDEDlg::OnNewObject() 
{
	DlgEditObject dlg_obj(this);
	object_data *obj;
	CString str;
	int ret;
	
	dlg_obj.object = new object_data;
	
	dlg_obj.object->vnum = GetValidVnum(OBJECT);
	
	ret = dlg_obj.DoModal();

	if(ret == IDOK) {
		obj = dlg_obj.object;
		
		AddObject(obj);
	}
}

void CWinDEDlg::OnEditObject(int vnum) 
{
	DlgEnterVnum dlg_vnum(this);
	DlgEditObject dlg_obj(this);
	CString str;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = OBJECT;
		dlg_vnum.vnum = 0;

		ret = dlg_vnum.DoModal();

		vnum = dlg_vnum.vnum;
	} else
		ret = IDOK;
	
	if(ret == IDOK) {
		dlg_obj.object = GetObjByVnum(vnum);
		
		if(dlg_obj.object) {
			dlg_obj.DoModal();
			
			if(!dlg_obj.object) {
				obj_count--;
			} else {
				str.Format("%d - %s", dlg_obj.object->vnum, dlg_obj.object->short_descr);
				UpdateItem(str, dlg_obj.object->m_tThis);
			}
		} else {
			str.Format("No Object With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}
	
	UpdateStatusBar();
}

void CWinDEDlg::SaveDefaults()
{
	ofstream file;
	CString str;
	int i;
	
	if(area_data::area)
	{
		str.Format("%s.def", StripAnsiChars(area_data::area->name));
		file.open(str);
	
		if(file.is_open()) 
		{
			str.Format("#DEFROOM\n");
			file.write(str, str.GetLength());

			str.Format("%s~\n", room_data::def_room->name);
			file.write(str, str.GetLength());
			
			str.Format("%s~\n", room_data::def_room->description);
			file.write(str, str.GetLength());

			str.Format("%d\n", room_data::def_room->current);
			file.write(str, str.GetLength());

			str.Format("%d\n", room_data::def_room->current_dir);
			file.write(str, str.GetLength());

			str.Format("%d\n", room_data::def_room->light);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", room_data::def_room->sector_type);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", room_data::def_room->fall_chance);
			file.write(str, str.GetLength());
		
			for(i = 0; i < NUM_ROOM_FLAGS; i++)
			{
				str.Format("%d\n", room_data::def_room->room_flags[i]);
				file.write(str, str.GetLength());
			}

			str.Format("#DEFMOB\n");
			file.write(str, str.GetLength());

			str.Format("%s~\n", mob_data::def_mob->name);
			file.write(str, str.GetLength());

			str.Format("%s~\n", mob_data::def_mob->short_descr);
			file.write(str, str.GetLength());
			
			str.Format("%s~\n", mob_data::def_mob->long_descr);
			file.write(str, str.GetLength());
			
			str.Format("%s~\n", mob_data::def_mob->description);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", mob_data::def_mob->alignment);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->c_class);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->level);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->position);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->race);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->sex);
			file.write(str, str.GetLength());

			str.Format("%d\n", mob_data::def_mob->size);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", mob_data::def_mob->act);
			file.write(str, str.GetLength());

			for(i = 0; i < NUM_AFFECT_VECTORS; i++)
			{
				str.Format("%d\n", mob_data::def_mob->affected_by[i]);
				file.write(str, str.GetLength());
			}
		
			str.Format("#DEFOBJ\n");
			file.write(str, str.GetLength());

			str.Format("%s~\n", object_data::def_obj->name );
			file.write(str, str.GetLength());

			str.Format("%s~\n", object_data::def_obj->short_descr);
			file.write(str, str.GetLength());

			str.Format("%s~\n", object_data::def_obj->description);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", object_data::def_obj->anti_flags[0]);
			file.write(str, str.GetLength());
		
			str.Format("%d\n", object_data::def_obj->anti_flags[1]);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->condition);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->craftsmanship);
			file.write(str, str.GetLength());
			
			str.Format("%d\n", object_data::def_obj->extra_flags[0]);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->extra_flags[1]);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->extra_flags[2]);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->item_type);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->level);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->material);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->size);
			file.write(str, str.GetLength());

			for(i = 0; i < MAX_ITEM_VALUE; i++)
			{
				str.Format("%d\n", object_data::def_obj->value[i]);
				file.write(str, str.GetLength());
			}
	
			str.Format("%d\n", object_data::def_obj->volume);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->wear_flags);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->weight);
			file.write(str, str.GetLength());

			for(i = 0; i < NUM_AFFECT_VECTORS;i++)
			{
				str.Format("%d\n", object_data::def_obj->affected_by[i]);
				file.write(str, str.GetLength());
			}

			str.Format("%d\n", object_data::def_obj->applies[0].loc);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->applies[0].value);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->applies[1].loc);
			file.write(str, str.GetLength());

			str.Format("%d\n", object_data::def_obj->applies[1].value);
			file.write(str, str.GetLength());
		}	
	}
}

void CWinDEDlg::LoadDefaults()
{
	ifstream file;
	CString st;
	int i;
	char str[512];

	if(area_data::area)
	{
		st.Format("%s.def", StripAnsiChars(area_data::area->name));

		file.open(st);
	
		if(file.is_open()) 
		{	

			while(!file.eof())
			{
				file.getline(str, 512, '\n');

				if(!strcmp(str, "#DEFROOM"))
				{	
					file.getline(str, 512, '~');
					room_data::def_room->name = str;

					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					room_data::def_room->description = str;

					file.getline(str, 512, '\n');
					file.getline(str, 512, '\n');
					room_data::def_room->current = atoi(str);

					file.getline(str, 512, '\n');
					room_data::def_room->current_dir = atoi(str);

					file.getline(str, 512, '\n');
					room_data::def_room->light =  atoi(str);

					file.getline(str, 512, '\n');
					room_data::def_room->sector_type = atoi(str);

					file.getline(str, 512, '\n');
					room_data::def_room->fall_chance = atoi(str);

					for(i = 0; i < NUM_ROOM_FLAGS; i++)
					{
						file.getline(str, 512, '\n');
						room_data::def_room->room_flags[i] = atoi(str);
					}
				}
				else if(!strcmp(str, "#DEFMOB"))
				{
					file.getline(str, 512, '~');
					mob_data::def_mob->name = str;
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					mob_data::def_mob->short_descr = str;	
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					mob_data::def_mob->long_descr = str;
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					mob_data::def_mob->description = str;
				
					file.getline(str, 512, '\n');
					file.getline(str, 512, '\n');
					mob_data::def_mob->alignment = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->c_class  = atoi(str);
				
					file.getline(str, 512, '\n');
					mob_data::def_mob->level = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->position = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->race = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->sex = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->size = atoi(str);
					
					file.getline(str, 512, '\n');
					mob_data::def_mob->act = atoi(str);

					for(i = 0; i < NUM_AFFECT_VECTORS; i++)
					{
						file.getline(str, 512, '\n');
						mob_data::def_mob->affected_by[i] = atoi(str);
					}
				}
				else if(!strcmp(str, "#DEFOBJ"))
				{	
					file.getline(str, 512, '~');
					object_data::def_obj->name = str;
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					object_data::def_obj->short_descr = str;
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '~');
					object_data::def_obj->description = str;
					
					file.getline(str, 512, '\n');
					file.getline(str, 512, '\n');
					object_data::def_obj->anti_flags[0] = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->anti_flags[1] = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->condition = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->craftsmanship = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->extra_flags[0] = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->extra_flags[1] = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->extra_flags[2] = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->item_type = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->level = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->material = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->size = atoi(str);
		
					for(i = 0; i < MAX_ITEM_VALUE; i++)
					{
						file.getline(str, 512, '\n');
						object_data::def_obj->value[i] =atoi(str);
					}
		
					file.getline(str, 512, '\n');
					object_data::def_obj->volume = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->wear_flags = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->weight = atoi(str);
	
					for(i = 0; i < NUM_AFFECT_VECTORS;i++)
					{
						file.getline(str, 512, '\n');
						object_data::def_obj->affected_by[i] = atoi(str);
					}

					file.getline(str, 512, '\n');
					object_data::def_obj->applies[0].loc = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->applies[0].value = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->applies[1].loc = atoi(str);
					
					file.getline(str, 512, '\n');
					object_data::def_obj->applies[1].value = atoi(str);
				}
			}

			file.close();
		}
	}
}
	
void CWinDEDlg::LoadSettings() 
{
	ifstream file;
	char str[512];
	CRect *rect		= NULL;
	CRect *wndRect  = NULL;
	CRect *mapRect  = NULL;

	file.open("Diku MUD Area Editor.set");
	
	if(file.is_open()) 
	{
		rect	= new CRect;
		wndRect = new CRect;
		mapRect = new CRect;

		file.getline(str, 512, ' ');
		editor_flags = atoi(str);

		file.getline(str, 512, ' ');
		timer = atoi(str);

		file.getline(str, 512, ' ');
		rect->top = atoi(str);

		file.getline(str, 512, ' ');
		rect->bottom = atoi(str);

		file.getline(str, 512, ' ');
		rect->left = atoi(str);

		file.getline(str, 512, ' ');
		rect->right = atoi(str);

		file.getline(str, 512, ' ');
		wndRect->top = atoi(str);

		file.getline(str, 512, ' ');
		wndRect->bottom = atoi(str);

		file.getline(str, 512, ' ');
		wndRect->left = atoi(str);

		file.getline(str, 512, ' ');
		wndRect->right = atoi(str);
		
		file.getline(str, 512, ' ');
		def_color = atoi(str);

		file.getline(str, 512, ' ');
		echo_color = atoi(str);
		
		//load map position and size
		file.getline(str, 512, ' ');
		mapRect->top = atoi(str);

		file.getline(str, 512, ' ');
		mapRect->bottom = atoi(str);

		file.getline(str, 512, ' ');
		mapRect->left = atoi(str);

		file.getline(str, 512, ' ');
		mapRect->right = atoi(str);

		file.getline(str, 512, '\n');

		alias_list.LoadAliasList(file);

		file.close();
	}

	if(rect) {
		dlg.MoveWindow(rect, true);	
		delete rect;
	}
	
	if(wndRect) {
		MoveWindow(wndRect, true);
		delete wndRect;
	}

	if(mapRect) {
		map.MoveWindow(mapRect, true);
		delete mapRect;
	}

	if(IS_SET(editor_flags, SHOW_COMPAS)) {
		m_Tool.SetButtonStyle(19, TBBS_CHECKED);
		dlg.ShowWindow(SW_SHOW);
	} else {
		m_Tool.SetButtonStyle(19, 0);
		dlg.ShowWindow(SW_HIDE);
	}

	if(IS_SET(editor_flags, SHOW_MAP)) {
		m_Tool.SetButtonStyle(18, TBBS_CHECKED);
		map.ShowWindow(SW_SHOW);
	} else {
		m_Tool.SetButtonStyle(18, 0);
		map.ShowWindow(SW_HIDE);
	}
	
	if(IS_SET(editor_flags, AUTO_SAVE)) {
		SetTimer(IDT_AUTO_SAVE, timer*60000, NULL);
	}

	m_colorizer.def_color = def_color;
}

void CWinDEDlg::SaveSettings() 
{
	ofstream file;
	CString str;
	CRect rect;

	dlg.GetWindowRect(rect);
	
	file.open("Diku MUD Area Editor.set");
	
	if(file.is_open()) 
	{
		//save editor flags
		str.Format("%d ", editor_flags);
		file.write(str, str.GetLength());
		
		//save timer
		str.Format("%d ", timer);
		file.write(str, str.GetLength());
		
		//save size and position of the directions
		str.Format("%d %d %d %d ", rect.top, rect.bottom, rect.left, rect.right);
		file.write(str, str.GetLength());

		//save the size and position of the main window
		GetWindowRect(rect);
		str.Format("%d %d %d %d ", rect.top, rect.bottom, rect.left, rect.right);
		file.write(str, str.GetLength());

		//save colors
		str.Format("%d %d ", def_color, echo_color);
		file.write(str, str.GetLength());

		//save size and position of map editor
		map.GetWindowRect(rect);

		str.Format("%d %d %d %d \n", rect.top, rect.bottom, rect.left, rect.right);
		file.write(str, str.GetLength());

		alias_list.SaveAliasList(file);

		file.close();
	}
}

void CWinDEDlg::OnSave() 
{
	SaveSettings();
	
	if(area_data::area)
	{
		if(IS_SET(editor_flags, SAVE_AREA_FORMAT))
			AreFileSave file(area_data::area->path, this);
		else if(IS_SET(editor_flags, SAVE_DE_FORMAT))
			MessageBox("Diku Edit format is not yet supported.");
		else if(IS_SET(editor_flags, SAVE_AREA_V1_FORMAT))
			MessageBox("Area Format Version 1 is not yet supported.");
		SaveDefaults();

		CannonList::cannons.SaveCannons();
		AmmoList::ammos.SaveAmmo();
		CrewList::crews.SaveCrews();
	}
	
	

	GetDlgItem(IDC_COMMAND)->SetFocus();
}

bool CWinDEDlg::CheckPortalCommand(CString str)
{
	object_data *portal = NULL;
	room_data *tmp = NULL; 
	int i =  0;
	CString str1;

	if(in_room)
	{
		if((portal = in_room->GetPortal()))
		{
			for(i = 0; i < CommandCount(); i++)
			{
				if(comm_types[i].index == portal->value[1])
				{ 
					if(str == comm_types[i].name)
					{
						if((tmp = GetRoomByVnum(portal->value[0])))
						{
							in_room = tmp;
							str1.Format("%s tranports you to %s.", portal->short_descr, tmp->name);
							ShowText(str1, false);
							ShowRoom();
							
							return true;
						}
						
						ShowText("Teleporter goes to invalid room.", true);
						return true;
					}
				}
			}
		}
	}

	return false;
}

void CWinDEDlg::OnEnter() 
{
	CEdit *ed;
	CString str, tmp;
	CString new_str;
	int i;

	ed = (CEdit*)GetDlgItem(IDC_COMMAND);

	ed->GetWindowText(str);
	
	if(str.IsEmpty())
	{
		ShowPrompt();
		return;
	}

	ed->SetSel(0, str.GetLength(), true);
	
	str = StripAnsiChars(str);
	
	if(IS_SET(editor_flags, ECHO_COMMANDS)) {
		new_str += ColorRefToAnsi(echo_color);
		new_str += str + "&n";
	
		ShowText(new_str, false);
	} 
	
	tmp = alias_list.GetCommand(str);

	if(!CheckPortalCommand(str))
	{
		if(tmp.IsEmpty())
			i = InterpKeyWord(str);
		else
		{
			GetArg(str);
			tmp += " " + str;
			i = InterpKeyWord(tmp);
		}

		if(i == -1) {
			ShowText("&nHuh!?&n", true); 
		} else {
			if(keyword_list[i].show_prompt) {
				ShowText("&n", true);
				//ShowPrompt();
			}
		}
	}
}

void CWinDEDlg::OnAreaProperties() 
{
	OnAreaEdit();
}

void CWinDEDlg::DeleteMob(int vnum)
{
	DlgEnterVnum dlg_vnum(this);
	mob_data *mob;
	CString str;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = MOBILE;
		dlg_vnum.vnum = 0;

		ret = dlg_vnum.DoModal();

		vnum = dlg_vnum.vnum;
	} else
		ret = IDOK;
	
	if(ret == IDOK) {
		mob = GetMobByVnum(vnum);
		
		if(mob) {
			str.Format("Delete mob with vnum: %d?", mob->vnum);
			ret = MessageBox(str, "Delete Mob", MB_YESNO);
			if(ret == IDYES) {
				mob->RemoveFromList();
				
				RemoveItem(mob->m_tThis);
				
				if(mob->shop) {
					shop_count--;
					delete mob->shop;
				}

				if(mob->quests) {
					talk_data *tmp_t, *next_t;
					quest_data *tmp_q, *next_q;

					for(tmp_t = mob->quests->messages; tmp_t; tmp_t = next_t) {
						next_t = tmp_t->next;
						delete tmp_t;
						quest_count--;
					}

					for(tmp_q = mob->quests->quests; tmp_q; tmp_q = next_q) {
						next_q = tmp_q->next;
						delete tmp_q;
						quest_count--;
					}
				}

				for(room_data *room = room_data::room_list; room; room = room->next)
				{
					for(mob_index *tmp = room->people; tmp; tmp = tmp->next)
						if(tmp->mob == mob)
							tmp->mob = NULL;
				}

				delete mob;
				mob_count--;

				UpdateStatusBar();
			}
		} else {
			str.Format("No Mob With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}
}

void CWinDEDlg::OnMobilesDeletemob() 
{
	DeleteMob(-1);
}

void CWinDEDlg::OnMobilesEditmob() 
{
	OnEditMob(-1);
}

void CWinDEDlg::OnMobilesNewmob() 
{
	OnNewMob();
}
void CWinDEDlg::DeleteObj(int vnum)
{
	DlgEnterVnum dlg_vnum(this);
	extra_desc *ped, *next_ed;
	object_data *obj;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = OBJECT;
		dlg_vnum.vnum = 0;

		ret = dlg_vnum.DoModal();

		vnum = dlg_vnum.vnum;
	} else
		ret = IDOK;
	
	if(ret == IDOK) {
		obj = GetObjByVnum(vnum);
		CString str;
		
		if(obj) {
			str.Format("Delete object with vnum: %d?", obj->vnum);
			ret = MessageBox(str, "Delete Object", MB_YESNO);
			
			if(ret == IDYES) {

				for(ped = obj->first_extra_descr; ped; ped = next_ed) {
					next_ed = ped->next;
					delete ped;
				}
				
				for(obj_index *index = obj_index::o_ind_head; index; index = index->n_list )
				{
					if(index->obj == obj)
						index->obj = NULL;
				}

				RemoveItem(obj->m_tThis);
				
				obj->RemoveFromList();
				
				obj_count--;
				UpdateStatusBar();
			}
		} else {
			str.Format("No Object With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	
}

void CWinDEDlg::OnObjectsDeleteobject() 
{
	DeleteObj(-1);
}

void CWinDEDlg::OnObjectsEditobject() 
{
	OnEditObject(-1);
}

void CWinDEDlg::OnObjectsNewobject() 
{
	OnNewObject();
}

void CWinDEDlg::DeleteRoom(int vnum) 
{
	DlgEnterVnum dlg_vnum(this);
	room_data *room;
	int ret;

	if(vnum == -1) {
		dlg_vnum.type = ROOM;
		dlg_vnum.vnum = 0;

		ret = dlg_vnum.DoModal();

		vnum = dlg_vnum.vnum;
	} else
		ret = IDOK;
	
	if(ret == IDOK) {
		room = GetRoomByVnum(vnum);
		CString str;
		
		if(room) {
			str.Format("Delete room with vnum: %d?", room->vnum);
			ret = MessageBox(str, "Delete Room", MB_YESNO);
			
			if(ret == IDYES) {
				DeleteRoom(room);
			}
		} else {
			str.Format("No Room With Vnum: %d", vnum);
			MessageBox(str, "Invalid Vnum");
		}
	}	

	map.DrawArea();
}

void CWinDEDlg::OnHelp() 
{
	DlgAbout about;
	about.DoModal();
}

void CWinDEDlg::OnRoomsDeleteroom() 
{
	DeleteRoom(-1);
}

void CWinDEDlg::OnRoomsEditroom() 
{
	OnEditRoom(-1);
}

void CWinDEDlg::OnRoomsNewroom() 
{
	OnNewRoom();	
}

void CWinDEDlg::OnClose() 
{	
	SaveSettings();
	
	if(IS_SET(editor_flags, SAVE_ON_EXIT))
	{
		if(area_data::area)
		{
			int ret = MessageBox("Save current area?", "Save Area?", MB_YESNOCANCEL);
			
			if(ret == IDYES)
				OnSave();
			else if(ret == IDCANCEL)
				return;
		}
	}

	Shell_NotifyIcon(NIM_DELETE, &niData);	
	
	dlg.ShowWindow(SW_HIDE);
	
	map.shut_down = true;
	map.ShowWindow(SW_HIDE);
	map.OnClose();

	CannonList::cannons.SaveCannons();
	CannonList::cannons.RemoveAll();

	AmmoList::ammos.SaveAmmo();
	AmmoList::ammos.RemoveAll();

	CrewList::crews.SaveCrews();
	CrewList::crews.DeleteAllCrews();

	CDialog::OnCancel();
	
	CloseArea();
	
	m_pColorWnd->Reset();
	m_pColorWnd->CloseWindow();
	
	delete m_pColorWnd;
	
	if(user)
	{
		user->DeleteAllInv();
		delete user;
	}

	if(room_data::def_room)
		delete room_data::def_room;

	if(mob_data::def_mob)
		delete mob_data::def_mob;

	if(object_data::def_obj)
		delete object_data::def_obj;
	
	CDialog::OnClose();
}

void CWinDEDlg::OnSettings() 
{
	DlgSettings dlg;
	int ret;

	dlg.m_timer = timer;
	dlg.def_color = def_color;
	dlg.echo_color = echo_color;
	dlg.m_auto_save = IS_SET(editor_flags, AUTO_SAVE);
	dlg.m_echo_commands = IS_SET(editor_flags, ECHO_COMMANDS);
	dlg.m_walk_create = IS_SET(editor_flags, WALK_CREATE);
	dlg.m_save_exit = IS_SET(editor_flags, SAVE_ON_EXIT);
	dlg.m_disp_line_len = IS_SET(editor_flags, DISP_LINE_LEN);

	if(IS_SET(editor_flags, OPEN_AREA_FORMAT))
		dlg.m_open_format = 0;
	else 
		dlg.m_open_format = 1;

	if(IS_SET(editor_flags, SAVE_AREA_FORMAT))
		dlg.m_save_format = 0;
	else 
		dlg.m_save_format = 1;

	ret = dlg.DoModal();
	
	if(ret == IDOK) {
		if(dlg.m_walk_create)
			SET_BIT(editor_flags, WALK_CREATE);
		else
			REMOVE_BIT(editor_flags, WALK_CREATE);

		if(dlg.m_echo_commands)
			SET_BIT(editor_flags, ECHO_COMMANDS);
		else 
			REMOVE_BIT(editor_flags, ECHO_COMMANDS);

		if(dlg.m_save_exit)
			SET_BIT(editor_flags, SAVE_ON_EXIT);
		else
			REMOVE_BIT(editor_flags, SAVE_ON_EXIT);

		if(dlg.m_disp_line_len)
			SET_BIT(editor_flags, DISP_LINE_LEN);
		else 
			REMOVE_BIT(editor_flags, DISP_LINE_LEN);

		timer = dlg.m_timer;

		if(dlg.m_auto_save) {
			KillTimer(IDT_AUTO_SAVE);
			SET_BIT(editor_flags, AUTO_SAVE);
			SetTimer(IDT_AUTO_SAVE, timer*60000, NULL);
		} else {
			KillTimer(IDT_AUTO_SAVE);
			REMOVE_BIT(editor_flags, AUTO_SAVE);
		}

		if(dlg.m_save_format == 0) {
			REMOVE_BIT(editor_flags, SAVE_DE_FORMAT);
			SET_BIT(editor_flags, SAVE_AREA_FORMAT);
		} else {
			REMOVE_BIT(editor_flags, SAVE_AREA_FORMAT);
			SET_BIT(editor_flags, SAVE_DE_FORMAT);
		}
		
		if(dlg.m_open_format == 0) {
			REMOVE_BIT(editor_flags, OPEN_DE_FORMAT);
			SET_BIT(editor_flags, OPEN_AREA_FORMAT);
		} else {
			REMOVE_BIT(editor_flags, OPEN_AREA_FORMAT);
			SET_BIT(editor_flags, OPEN_DE_FORMAT);
		}

		def_color = dlg.def_color;
		echo_color = dlg.echo_color;
	}

	m_colorizer.def_color = def_color;
	
	SaveSettings();
}

void CWinDEDlg::OnOpen() 
{
	if(IS_SET(editor_flags, OPEN_DE_FORMAT)) 
	{
		CFileDialog de_file(true, "", "", NULL, 
			"Zone Files (*.zon)|*.zon|"
			"Room Files (*.wld)|*.wld|"
			"Mob Files (*.mob)|*.mob|"
			"Object Files (*.obj)|*.obj|");

		if(de_file.DoModal() == IDOK)
			MessageBox(de_file.GetPathName());

		MessageBox("Diku Edit format is not yet supported.");
		return;
	}
	else 
	{
		CString str("Area Files (*.are)|*.are|");
		CFileDialog are_file(true, "", "", NULL, str);
		
		if(are_file.DoModal() == IDOK) 
		{
			CloseArea();

			ShowText("&+WWelcome To Diku MUD Area Editor!&n\n&+WCopyright: &+GGalacticSoft &+W(&+GMarissa du Bois&n&+W, 2003-2014)", false);

			if(IS_SET(editor_flags, OPEN_AREA_FORMAT))
				AreFileOpen file(are_file.GetPathName(), this);
			else if(IS_SET(editor_flags, OPEN_AREA_V1_FORMAT))
			{
				MessageBox("Area Format Version1 is not yet supported.");
				return;
			}

			AreaLoaded();
		}
		else
			return;
	}
	
	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		AddRoom(room);
		
		for(mob_index *mob = room->people; mob; mob = mob->next)
			AddMobToRoom(mob, room);

		for(obj_index *obj = room->contents; obj; obj = obj->next)
			AddObjToRoom(obj, room);
	}

	for(mob_data *mob = mob_data::first_mob; mob; mob = mob->next)
		AddMob(mob);

	for(object_data *obj = object_data::obj_head; obj; obj = obj->next)
		AddObject(obj);

	in_room = room_data::room_list;
	
	LoadDefaults();		
	
	ShowRoom();
	
	map.DrawArea();
}

void CWinDEDlg::OnExit() 
{
	OnClose( );
}

void CWinDEDlg::AreaLoaded()
{
	CWnd *b;
	int i;

	zone_tree.EnableWindow(true);

	b = (CButton*)GetDlgItem(IDC_COMMAND);
	b->EnableWindow(true);
	b->SetFocus();

	GetDlgItem(IDC_ENTER)->EnableWindow(true);
			
	dlg.GetDlgItem(IDC_NORTH)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_SOUTH)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_WEST)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_EAST)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_DOWN)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_UP)			->EnableWindow(true);
	dlg.GetDlgItem(IDC_LOOK)		->EnableWindow(true);
	dlg.GetDlgItem(IDC_NORTHWEST)	->EnableWindow(true);
	dlg.GetDlgItem(IDC_NORTHEAST)	->EnableWindow(true);
	dlg.GetDlgItem(IDC_SOUTHWEST)	->EnableWindow(true);
	dlg.GetDlgItem(IDC_SOUTHEAST)	->EnableWindow(true);

	for(i = 0; i < m_Tool.GetCount(); i++) 
	{
		if(m_Tool.GetButtonStyle(i) == TBBS_DISABLED)
			m_Tool.SetButtonStyle(i, TBSTATE_ENABLED);
	}
			
	m_tArea		= InsertItem(StripAnsiChars(area_data::area->name), TVI_ROOT, area_data::area, 0);
	m_tRooms	= InsertItem(CString("Rooms"),		m_tArea, NULL, ROOM_PARENT);
	m_tMobiles	= InsertItem(CString("Mobiles"),	m_tArea, NULL, MOB_PARENT);
	m_tObjects	= InsertItem(CString("Objects"),	m_tArea, NULL, OBJ_PARENT);
		
}

void CWinDEDlg::OnNewArea() 
{
	DlgEditArea ea(this);
	int ret;
	room_data *new_room;
	CString str;

	if(!area_data::area)
	{
		area_data::area = new area_data;
		ea.area = area_data::area;
	}
	else 
	{
		ret = MessageBox("Would you like to save the current area?", "Save Area?", MB_YESNOCANCEL);
		
		if(ret == IDYES) 
		{
			OnSave();
			CloseArea();
			ea.area = area_data::area;
		} 
		else if(ret == IDNO) 
		{
			CloseArea();
			ea.area = area_data::area;
		} 
		else if(ret == IDCANCEL)
			return;
	}
	
	ret = ea.DoModal();

	if(ret == IDOK) 
	{
		area_data::area = ea.area;

		if(area_data::area) 
		{
			AreaLoaded();
			
			new_room = new room_data;
			
			new_room->vnum = GetValidVnum(ROOM);
			
			new_room->AddToList();

			in_room = new_room;
			
			room_count++;

			ShowRoom();

			UpdateStatusBar();
		
			str.Format("%d - %s", new_room->vnum, StripAnsiChars(new_room->name));
		
			new_room->m_tThis = InsertItem(str, m_tRooms, new_room, new_room->class_index);
			new_room->m_tContents = InsertItem(CString("Contents"), new_room->m_tThis, NULL, CONTENTS);
			new_room->m_tPeople = InsertItem(CString("Occupants"),  new_room->m_tThis, NULL, PEOPLE);
		
		}
	} 
	else if(ret == IDCANCEL) 
	{
		delete area_data::area;
		area_data::area = NULL;
	}

	map.DrawArea();
}

void CWinDEDlg::OnAreaEdit() 
{
	DlgEditArea dlg(this);
	
	if(area_data::area)
	{
		dlg.area = area_data::area;
	
		dlg.author			= area_data::area->author;
		dlg.barracks_vnum	= area_data::area->barracks;
		dlg.defender_vnum	= area_data::area->defender;
		dlg.filename		= area_data::area->path;
		dlg.high_level		= area_data::area->ulv;
		dlg.jail_vnum		= area_data::area->jail;
		dlg.judge_vnum		= area_data::area->judge;
		dlg.low_level		= area_data::area->llv;
		dlg.high_reset		= area_data::area->ulifespan;
		dlg.reset_message	= area_data::area->resetmsg;	
		dlg.squads			= area_data::area->squads;
		dlg.starting_vnum	= area_data::area->vnum;	 
		dlg.justice			= area_data::area->justice;
		dlg.reset_mode		= area_data::area->resetmode;
		dlg.name			= area_data::area->name;
		dlg.reset_mode		= area_data::area->resetmode;
		dlg.low_reset		= area_data::area->llifespan;
		dlg.area_flags		= area_data::area->area_flags;

		dlg.DoModal();
	}
}

void CWinDEDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CWinDEDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}

BEGIN_EASYSIZE_MAP(CWinDEDlg)
	EASYSIZE(IDC_EDIT_FRAME,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_DISPLAY,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	
	EASYSIZE(IDC_ZONETREE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_ZONETREE_FRAME, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	
	EASYSIZE(IDC_SPLITTER1, IDC_DISPLAY, ES_BORDER, IDC_ZONETREE, ES_BORDER, 0)
	EASYSIZE(IDC_LINE, ES_BORDER, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0);
	
	EASYSIZE(IDC_HISTORY, ES_BORDER, IDC_DISPLAY, IDC_COMMAND, ES_BORDER, 0)
	EASYSIZE(IDC_COMMAND, ES_BORDER, IDC_DISPLAY, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_ENTER,IDC_COMMAND,IDC_DISPLAY,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

void CWinDEDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	UPDATE_EASYSIZE;
	
	CRect frameRect;
	
	GetWindowRect(frameRect);
	ScreenToClient(frameRect);
	
	split.SetRange(frameRect.left+200, frameRect.right-150);
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDC_OBJ_COUNT);
}

void CWinDEDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CRect frameRect;
    
	CDialog::OnSizing(fwSide, pRect);
	
	GetWindowRect(frameRect);
	ScreenToClient(frameRect);
	
	split.SetRange(frameRect.left+200, frameRect.right-150);
    
	EASYSIZE_MINSIZE(600,400,fwSide,pRect);	
}

bool CWinDEDlg::PromptResponse()
{
	if(MessageBox("List Exceedes Maximum Length, Continue?", "Continue?", MB_YESNO) == IDYES)
		return true;

	return false;
}

void CWinDEDlg::ShowRoom(bool prompt) 
{
	if(in_room && m_pColorWnd) {
		ShowText("&n", false);
		ShowText(in_room->DisplayRoom() + CString("\n") , false);

		if(prompt)
			ShowPrompt();
	}
}

void CWinDEDlg::MoveRoom(int dir) 
{
	room_data *proom;
	
	if(!in_room)
		return;

	if(in_room->exit[dir]) {
		if((proom = GetRoomByVnum(in_room->exit[dir]->vnum))) {
			in_room = proom;
			ShowRoom();
		}
	} else {
		if(IS_SET(editor_flags, WALK_CREATE)) {
			room_data *new_room;
			CString str;

			new_room = new room_data;
			
			new_room->vnum = GetValidVnum(ROOM);
			
			new_room->AddToList();

			in_room->exit[dir] = new exit_data;
			in_room->exit[dir]->vnum = new_room->vnum;

			new_room->exit[rev_dir[dir]] = new exit_data;
			new_room->exit[rev_dir[dir]]->vnum = in_room->vnum;

			in_room = new_room;
			
			ShowRoom();

			room_count++;

			UpdateStatusBar();
		
			str.Format("%d - %s", new_room->vnum, StripAnsiChars(new_room->name));
		
			new_room->m_tThis = InsertItem(str, m_tRooms, new_room, new_room->class_index);
			new_room->m_tContents = InsertItem(CString("Contents"), new_room->m_tThis, NULL, CONTENTS);
			new_room->m_tPeople = InsertItem(CString("Occupants"),  new_room->m_tThis, NULL, PEOPLE);
		} 
		else 
		{
			ShowText("&nAlas, there is no clear path in that direction.", true);
			return;
		}
	}
	
	map.MoveRoom(dir);
	
	map.CenterOnCurrRoom();
	
	map.DrawArea();	
}

CWinDEDlg::InterpData CWinDEDlg::keyword_list[] = {
	//Movement Commands
	//{"",		false,  false,  CMD_NONE},
	{"north",		false,	false,	CMD_NORTH},
	{"south",		false,	false,	CMD_SOUTH},
	{"west",		false,	false,	CMD_WEST},
	{"east",		false,	false,	CMD_EAST},
	{"down",		false,	false,	CMD_DOWN},
	{"up",			false,	false,	CMD_UP},
	{"northwest",	false,	false,	CMD_NORTHWEST},
	{"southwest",	false,	false,	CMD_SOUTHWEST},
	{"nw",			false,	false,	CMD_NORTHWEST},
	{"sw",			false,	false,	CMD_SOUTHWEST},
	{"northeast",	false,	false,	CMD_NORTHEAST},
	{"southeast",	false,	false,	CMD_SOUTHEAST},
	{"ne",			false,	false,	CMD_NORTHEAST},
	{"se",			false,	false,	CMD_SOUTHEAST},
	
	{"goto",		true,   false,	CMD_GOTO},
	{"look",		true,	false,	CMD_LOOK},
	
	//builder commands
	{"new",         true,	true,	CMD_NEW},
	{"create",		true,   true,   CMD_NEW},
	{"edit",		true,	false,	CMD_EDIT},
	{"grid",        true,   false,	CMD_GRID},
	{"delete",		true,   true,   CMD_DELETE},
	{"renumber",    true,   true,   CMD_RENUMBER},
	{"default",     true,   true,   CMD_DEF_ROOM},

	//misc commands
	{"save",		true,   true,   CMD_SAVE},
	{"commands",	true,	true,   CMD_COMMAND},
	{"quit",        true,   false,  CMD_EXIT},
	
	{"follow",      true,   true,   CMD_FOLLOW},
	{"mount",       true,   true,   CMD_MOUNT},
	{"ask",			true,	true,   CMD_ASK},
	
	{"alias",       true,   true,   CMD_ALIAS},
	{"unalias",     true,   true,   CMD_UNALIAS},
	
	{"link",        true,   true,   CMD_LINK},
	{"exits",		true,	true,   CMD_EXITS},
	
	{"load",        true,   false,  CMD_LOAD},
	{"clone",		true,   true,   CMD_CLONE},
	{"purge",		true,	true,   CMD_PURGE},
	
	{"list",		true,   true,   CMD_LIST},
	{"show",        true,   false,  CMD_SHOW},
	{"stat",		true,   false,  CMD_STAT},
	{"where",		true,   false,  CMD_WHERE},
	
	{"give",        true,   false,  CMD_GIVE},
	{"equip",       true,   true,   CMD_EQUIP},
	{"get",			true,   false,  CMD_GET},
	{"drop",		true,   false,  CMD_DROP},
	{"inventory",	true,   true,   CMD_INV},
	{"take",		true,   false,  CMD_TAKE},

};

int CWinDEDlg::LastKey() {return sizeof(keyword_list)/sizeof(InterpData);}

void CWinDEDlg::List(CString args)
{
	mob_index *mob;
	object_data *obj;
	CString str;

	if(!in_room)
	{
		ShowText("You must be in a room in order to view shop items", false);
		return;
	}

	for(mob = in_room->people; mob; mob = mob->next)
	{
		if(mob->mob)
		{
			if(mob->mob->shop)
			{
				str.Format("%s sells the following:&n", mob->GetShortName());
				ShowText(str, false);

				for(int i = 0; i < MAX_SELL; i++)
				{
					if(mob->mob->shop->sell_item[i] < 0)
						continue;

					if((obj = GetObjByVnum(mob->mob->shop->sell_item[i])))
						str.Format("&+B[&N&+r%d&N&+B]&N %s (%d)", i, obj->short_descr, obj->vnum);
					else
						str.Format("&+B[&n&+r%d&+B]&n %s (%d)", i, "An unknown object", mob->mob->shop->sell_item[i]);

					ShowText(str, false);
				}
			}
		}
	}
}

void CWinDEDlg::Where(CString args)
{
	int i = 0;
	int pages = 0;
	room_data *room;
	bool found = false;

	CString str;
	CString arg1, arg2;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(arg1.IsEmpty())
		ShowText("Please specify, Mob, Room, or Object\n", false);
	else
	{
		if(GetArgType(arg1) == OBJECT)
		{
			object_data *obj;
			
			if(!(obj = GetObj(arg2)))
			{
				str.Format("No object: %s", arg2);
				ShowText(str, true);
				return;
			}

			str.Format("Looking for object: %s&+L(&+r%d&+L)", obj->short_descr, obj->vnum);
			ShowText(str, false);

			for(room = room_data::room_list; room; room = room->next)
			{	
				if(room->GetObjInRoom(obj->vnum))
				{
					found = true;
					str.Format("%d: %s&n &+L(&+r%d&+L)&n", i+1, room->name, room->vnum);
				
					ShowText(str, false);
					i++;

					if(i == PAGE_LEN)
					{
						pages++;
					
						str.Format("&+G--------------------- Showing Pages: %d of %d (%d/%d Objects) ---------------------&n", 
							pages, (GetObjCount() / PAGE_LEN)+1, i*pages, GetObjCount());
					
						ShowText(str, false);

						i = 0;
						if(PromptResponse())
							continue;
					
						break;
					}
				}
			}

			if(found == false)
			{
				str.Format("Object %s&+L(&+r%d&N&+L)&n, not found.", obj->short_descr, obj->vnum);
				ShowText(str, true);
				return;
			}

			ShowText("", true);
		}
		else if(GetArgType(arg1) == MOBILE)
		{
			mob_data *mob;
			
			if(!(mob = GetMob(arg2)))
			{
				str.Format("No mobile: %s", arg2);
				ShowText(str, true);
				return;
			}

			str.Format("Looking for mobile: %s&+L(&+r%d&+L)", mob->short_descr, mob->vnum);
			ShowText(str, false);

			for(room = room_data::room_list; room; room = room->next)
			{	
				if(room->GetMobInRoom(mob->vnum))
				{
					found = true;
					str.Format("%d: %s&n &+L(&+r%d&+L)&n", i+1, room->name, room->vnum);
				
					ShowText(str, false);
					i++;

					if(i == PAGE_LEN)
					{
						pages++;
					
						str.Format("&+G--------------------- Showing Pages: %d of %d (%d/%d Objects) ---------------------&n", 
							pages, (GetObjCount() / PAGE_LEN)+1, i*pages, GetObjCount());
					
						ShowText(str, false);

						i = 0;
						if(PromptResponse())
							continue;
					
						break;
					}
				}
			}

			if(found == false)
			{
				str.Format("Mobile %s&+L(&+r%d&N&+L)&n, not found.", mob->short_descr, mob->vnum);
				ShowText(str, true);
				return;
			}

			ShowText("", true);
		}
	}
}
void CWinDEDlg::Show(CString args)
{
	int i = 0;
	int pages = 0;
	bool disp= false;

	CString str;
	CString arg1, arg2;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(arg2 == "l"  || arg2 == "long")
		disp = true;

	if(arg1.IsEmpty())
		ShowText("Please specify, Mob, Room, or Object\n", false);
	else
	{
		if(GetArgType(arg1) == OBJECT)
		{
			object_data *obj;
			
			for(obj = object_data::obj_head; obj; obj = obj->next)
			{	
				if(disp)
					str.Format("%s&n (%d)", obj->description, obj->vnum);
				else
					str.Format("%s&n (%d)", obj->short_descr, obj->vnum);
				
				ShowText(str, false);
				i++;

				if(i == PAGE_LEN)
				{
					pages++;
					
					str.Format("&+G--------------------- Showing Pages: %d of %d (%d/%d Objects) ---------------------&n", 
						pages, (GetObjCount() / PAGE_LEN)+1, i*pages, GetObjCount());
					
					ShowText(str, false);

					i = 0;
					if(PromptResponse())
						continue;
					
					break;
				}
			}
		}
		else if(GetArgType(arg1) == MOBILE)
		{
			mob_data *mob;
			
			for(mob = mob_data::first_mob; mob; mob = mob->next)
			{	
				if(disp)
					str.Format("%s&n (%d)", mob->long_descr, mob->vnum);
				else
					str.Format("%s&n (%d)", mob->short_descr, mob->vnum);

				ShowText(str, false);
				i++;

				if(i == PAGE_LEN)
				{
					pages++;
					
					str.Format("&+G--------------------- Showing Pages: %d of %d (%d/%d Mobiles) ---------------------&n", 
						pages, (GetMobCount() / PAGE_LEN)+1, i*pages, GetMobCount());
					
					ShowText(str, false);

					i = 0;
					if(PromptResponse())
						continue;
					
					break;
				}
			}
		}
		else if(GetArgType(arg1) == ROOM)
		{
			room_data *room;
			
			for(room = room_data::room_list; room; room = room->next)
			{	
				str.Format("%s&n (%d)", room->name, room->vnum);
				ShowText(str, false);
				i++;

				if(i == PAGE_LEN)
				{
					pages++;
					
					str.Format("&+G--------------------- Showing Pages: %d of %d (%d/%d Rooms) ---------------------&n", 
						pages, (GetRoomCount() / PAGE_LEN), i*pages, GetRoomCount());
					
					ShowText(str, false);

					i = 0;
					if(PromptResponse())
						continue;
					
					break;
				}
			}
		}
	}

	ShowText("", true);
}

void CWinDEDlg::Inv(CString args)
{
	obj_index *obj;
	CString str;

	if(user->inventory)
	{
		ShowText("You are carrying:", false);

		for(obj = user->inventory; obj; obj = obj->next)
		{
			str.Format("%s (%d)", obj->GetShortName(), obj->vnum);
			ShowText(str, false);
		}
	}
	else
		ShowText("You aren't carrying anything.", false);
}

void CWinDEDlg::Take(CString args)
{
	CString arg1, arg2;
	object_data *obj;
	mob_index *mob;
	CString str;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if((mob = GetMobInRoom(in_room, arg2)))
	{
		if((obj = GetObj(arg1)))
		{
			for(obj_index *o = mob->inventory; o; o = o->next)
			{
				if(o->obj == obj)
				{
					mob->RemoveObjFromInv(o);
					user->AddObjToInv(o);

					str.Format("You take %s from %s", o->GetShortName(), mob->GetShortName());

					ShowText(str, true);
				}
			}
		}
		else
			ShowText("They aren't carrying that.", true);
					
	}
	else
		ShowText("They aren't there.", true);

}

void CWinDEDlg::Get(CString args)
{
	obj_index *obj;
	object_data *object;
	CString str;
	
	if(args.IsEmpty())
		ShowText("Get which object?", true);
	else
	{
		if((object = GetObj(args)))
		{
			if(in_room)
			{
				if((obj = in_room->GetObjInRoom(object->vnum)))
				{
					in_room->RemoveContent(obj);
					RemoveItem(obj->m_tThis);
					user->AddObjToInv(obj);
					
					str.Format("You got %s (%d).", obj->GetShortName(), obj->vnum);
					ShowText(str, true);
				}
				else
					ShowText("You do not see that here.", true);
			}
			else
				ShowText("You must be in a room to pick stuff up.", true);
		}
	}
}

void CWinDEDlg::Drop(CString args)
{
	obj_index *obj;
	object_data *object;
	CString str;
	
	if(args.IsEmpty())
	{
		ShowText("Drop which object?", true);
		return;
	}
	else
	{
		if((object = GetObj(args)))
		{
			if((obj = user->GetObjInInv(object->vnum)))
			{
				user->RemoveObjFromInv(obj);
				in_room->AddContent(obj);
				
				str.Format("You have dropped %s (%d).", obj->GetShortName(), obj->vnum);
				ShowText(str, true);
			}
		}
	}
}

void CWinDEDlg::Clone(CString args)
{
	CString str, arg1, arg2;
	room_data *room;
	mob_data *mob;
	object_data *obj;
	int ret;
	
	arg1 = GetArg(args);
	arg2 = GetArg(args);
	
	arg1.MakeLower();
	
	if(GetArgType(arg1) == ROOM)
	{
		room = GetRoom(arg2);
		
		if(room)
		{
			EditRoom dlg(this);
	
			dlg.room = new room_data;
	
			dlg.room->name = room->name;
			dlg.room->description = room->description;
			dlg.room->fall_chance = room->fall_chance;
			dlg.room->current = room->current;
			dlg.room->current_dir = room->current_dir;
			dlg.room->light = room->light;

			dlg.room->room_flags[1] = room->room_flags[1];
			dlg.room->room_flags[0] = room->room_flags[0];

			dlg.room->vnum = GetValidVnum(ROOM);
			dlg.vnum = dlg.room->vnum;
	
			ret = dlg.DoModal();
		
			if(ret == IDOK) {
				in_room = dlg.room;
		
				ShowRoom();

				AddRoom(dlg.room);	
			}
	
			map.DrawArea();	

			str.Format("\n%s cloned to room %d", room->name, dlg.room->vnum);
			ShowText(str, false);
		}
		else
			ShowText("Invalid room vnum to clone.", false);
	}
	else if(GetArgType(arg1) == MOBILE)
	{
		DlgEditMob dlg(this);
		CString str;
		
		mob = GetMob(arg2);

		if(mob)
		{
			dlg.mob = new mob_data;

			dlg.mob->money = mob->money;
			dlg.mob->description = mob->description;
			dlg.mob->short_descr = mob->short_descr;
			dlg.mob->long_descr = mob->long_descr;
			dlg.mob->c_class = mob->c_class;
			dlg.mob->race = mob->race;
			dlg.mob->alignment = mob->alignment;
			dlg.mob->act = mob->act;
			for(int i = 0; i < NUM_AFFECT_VECTORS; i++)
				dlg.mob->affected_by[i] = mob->affected_by[i];
			dlg.mob->level = mob->level;
			dlg.mob->name = mob->name;
			dlg.mob->position = mob->position;
			dlg.mob->sex = mob->sex;
			dlg.mob->size = mob->size;

			ret = dlg.DoModal();

			if(ret == IDOK)
			{
				if(dlg.mob) 
				{
					dlg.mob->AddToList();
					AddMob(dlg.mob);
					
					str.Format("\n%s now cloned to mobile %d.", mob->short_descr, dlg.mob->vnum);
					ShowText(str, false);
				}
			} 
			else if(ret == IDCANCEL) 
			{
				if(dlg.mob) 
				{
					if(dlg.mob->shop) 
						delete dlg.mob->shop;

					if(dlg.mob->quests) 
					{
						talk_data *tmp_t, *next_t;
						quest_data *tmp_q, *next_q;

						for(tmp_t = dlg.mob->quests->messages; tmp_t; tmp_t = next_t) 
						{
							next_t = tmp_t->next;
							delete tmp_t;
						}

						for(tmp_q = dlg.mob->quests->quests; tmp_q; tmp_q = next_q) 
						{
							next_q = tmp_q->next;
							delete tmp_q;
						}
					}
					delete dlg.mob;
				}
				
				ShowText("Mob was not cloned", false);
			}

			UpdateStatusBar();
		}
		else
			ShowText("Invalid mobile vnum to clone.", false);
	}
	else if(GetArgType(arg1) == OBJECT)
	{
		int i;

		DlgEditObject dlg_obj(this);
		obj = GetObj(arg2);

		if(obj)
		{
			dlg_obj.object = new object_data;
	
			dlg_obj.object->vnum = GetValidVnum(OBJECT);
	
			dlg_obj.object->anti_flags[0] = obj->anti_flags[0];
			dlg_obj.object->anti_flags[1] = obj->anti_flags[1];
			dlg_obj.object->condition = obj->condition;
			dlg_obj.object->craftsmanship = obj->craftsmanship;
			dlg_obj.object->description = obj->description;
			dlg_obj.object->extra_flags[0] = obj->extra_flags[0];
			dlg_obj.object->extra_flags[1] = obj->extra_flags[1];
			dlg_obj.object->extra_flags[2] = obj->extra_flags[2];
			dlg_obj.object->item_type = obj->item_type;
			dlg_obj.object->level = obj->level;
			dlg_obj.object->material = obj->material;
			dlg_obj.object->name = obj->name;
			dlg_obj.object->short_descr = obj->short_descr;
			dlg_obj.object->size = obj->size;
	
			for(int i = 0; i < MAX_ITEM_VALUE; i++)
				dlg_obj.object->value[i] = obj->value[i];
	
			dlg_obj.object->volume = obj->volume;
			dlg_obj.object->wear_flags = obj->wear_flags;
			dlg_obj.object->weight = obj->weight;
	
			for(i = 0; i < NUM_AFFECT_VECTORS;i++)
				dlg_obj.object->affected_by[i] = obj->affected_by[i];

			dlg_obj.object->applies[0].loc = obj->applies[0].loc;
			dlg_obj.object->applies[0].value = obj->applies[0].value;
			dlg_obj.object->applies[1].loc = obj->applies[1].loc;
			dlg_obj.object->applies[1].value = obj->applies[1].value;

			ret = dlg_obj.DoModal();

			if(ret == IDOK)
				AddObject(dlg_obj.object);

			str.Format("%s has been cloned to object %d.", obj->short_descr, obj->vnum);
			ShowText(str, false);
		}
		else
			ShowText("Invalid object vnum to clone.", false);
	}
	else
		ShowText("Please specify mob, obj, or room.", false);
}

void CWinDEDlg::Purge(CString args)
{
	CString arg1, arg2, str;
	mob_index *mob;
	obj_index *obj;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(in_room)
	{
		if(GetArgType(arg1) == MOBILE)
		{
			mob = GetMobInRoom(in_room, arg2);
		
			if(mob)
			{
				RemoveItem(mob->m_tThis);
				in_room->RemovePerson(mob);
				str.Format("%s purged from %s", mob->GetShortName(), in_room->name);
				ShowText(str, false);
			}
			else
				ShowText("Mob not in room.", false);
		}
		else if(GetArgType(arg1) == OBJECT)
		{
			obj = GetObjInRoom(in_room, arg2);
			
			if(obj)
			{
				RemoveItem(obj->m_tThis);
				in_room->RemoveContent(obj);
				str.Format("%s purged from %s", obj->GetShortName(), in_room->name);
				ShowText(str, false);
			}
			else
				ShowText("Object not in room.", false);
		}
		else if(GetArgType(arg1) == MOBILE)
		{
			in_room->RemoveEveryone();
			ShowText("All mobs purged from room.", false);
		}
		else if(arg1 == "objs" || arg1 == "objects")
		{
			in_room->RemoveContents();
			ShowText("All objects purged from room.", false);
		}
		else if(arg1 == "all")
		{
			in_room->RemoveContents();
			in_room->RemoveEveryone();
			ShowText("You have purged everything in the room.", false);
		}
		else
			ShowText("Please specify mob(s), obj(s), or all.", false);
	}
	else
		ShowText("You are not in a room.", false);
}

void CWinDEDlg::Default(CString args)
{
	int i;
	CString str, arg1, arg2;
	mob_data *mob;
	object_data *obj;

	if(args.IsEmpty())
	{
		if(in_room)
		{
			room_data::def_room->description = in_room->description;
			room_data::def_room->name = in_room->name;
			room_data::def_room->current = in_room->current;
			room_data::def_room->current_dir = in_room->current_dir;
			room_data::def_room->light = in_room->light;
			room_data::def_room->sector_type = in_room->sector_type;
			room_data::def_room->fall_chance = in_room->fall_chance;
		
			for(i = 0; i < NUM_ROOM_FLAGS; i++)
				room_data::def_room->room_flags[i] = in_room->room_flags[i];

			str.Format("Default room set to room %d.", in_room->vnum);

			ShowText(str, false);
		}
		else
			ShowText("No default room set.", false);
	}
	else
	{
		arg1 = GetArg(args);
		arg2 = GetArg(args);

		if(GetArgType(arg1) == MOBILE)
		{
			mob = GetMob(arg2);

			if(mob)
			{	
				mob_data::def_mob->name = mob->name;
				mob_data::def_mob->short_descr = mob->short_descr;
				mob_data::def_mob->alignment = mob->alignment;
				mob_data::def_mob->c_class  = mob->c_class;
				mob_data::def_mob->description = mob->description;
				mob_data::def_mob->level = mob->level;
				mob_data::def_mob->long_descr = mob->long_descr;
				mob_data::def_mob->position = mob->position;
				mob_data::def_mob->race = mob->race;
				mob_data::def_mob->sex = mob->sex;
				mob_data::def_mob->size = mob->size;
				mob_data::def_mob->act = mob->act;

				for(i = 0; i < NUM_AFFECT_VECTORS; i++)
					mob_data::def_mob->affected_by[i] = mob->affected_by[i];

				str.Format("Default mob set to mob %d", mob->vnum);
				ShowText(str, false);
			}
			else
				ShowText("No default mob set.", false);
		}
		else if(GetArgType(arg1) == OBJECT)
		{
			obj = GetObj(arg2);

			if(obj)
			{	
				object_data::def_obj->anti_flags[0] = obj->anti_flags[0];
				object_data::def_obj->anti_flags[1] = obj->anti_flags[1];
				object_data::def_obj->condition = obj->condition;
				object_data::def_obj->craftsmanship = obj->craftsmanship;
				object_data::def_obj->description = obj->description;
				object_data::def_obj->extra_flags[0] = obj->extra_flags[0];
				object_data::def_obj->extra_flags[1] = obj->extra_flags[1];
				object_data::def_obj->extra_flags[2] = obj->extra_flags[2];
				object_data::def_obj->item_type = obj->item_type;
				object_data::def_obj->level = obj->level;
				object_data::def_obj->material = obj->material;
				object_data::def_obj->name = obj->name;
				object_data::def_obj->short_descr = obj->short_descr;
				object_data::def_obj->size = obj->size;
	
				for(i = 0; i < MAX_ITEM_VALUE; i++)
					object_data::def_obj->value[i] = obj->value[i];
	
				object_data::def_obj->volume = obj->volume;
				object_data::def_obj->wear_flags = obj->wear_flags;
				object_data::def_obj->weight = obj->weight;
	
				for(i = 0; i < NUM_AFFECT_VECTORS;i++)
					object_data::def_obj->affected_by[i] = obj->affected_by[i];

				object_data::def_obj->applies[0].loc = obj->applies[0].loc;
				object_data::def_obj->applies[0].value = obj->applies[0].value;
				object_data::def_obj->applies[1].loc = obj->applies[1].loc;
				object_data::def_obj->applies[1].value = obj->applies[1].value;

				str.Format("Default object set to object %d", obj->vnum);
				ShowText(str, false);
			}
			else
				ShowText("No default mob set.", false);
		}
	}
}

void CWinDEDlg::Renumber(CString args)
{
	CString arg1, str;
	int vnum, old_vnum;
	room_data *room, *tmp;
	mob_data *mob;
	mob_index *m_ind;
	object_data *obj;
	obj_index *o_ind;

	arg1 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You must specify a new starting vnum.", false);
		return;
	}

	vnum = atoi(arg1);

	object_data::high_obj_vnum = vnum;
	room_data::room_hi_vnum = vnum;
	mob_data::high_mob_vnum = vnum;

	zone_tree.DeleteAllItems();
	
	AreaLoaded();

	for(room = room_data::room_list; room; room = room->next)
	{
		old_vnum = room->vnum;
		room->vnum = GetValidVnum(ROOM);
		
		for(tmp = room_data::room_list; tmp; tmp = tmp->next)
		{
			for(int i = DIR_NORTH; i < MAX_DIR; i++)
			{
				if(tmp->exit[i])
				{
					if(tmp->exit[i]->vnum == old_vnum)
						tmp->exit[i]->vnum = room->vnum;
				}
			}	
		}
		
		AddRoom(room);
	}

	for(mob = mob_data::first_mob; mob; mob = mob->next)
	{
		mob->vnum = GetValidVnum(MOBILE);
		
		AddMob(mob);

		for(room = room_data::room_list; room; room = room->next)
		{
			for(m_ind = room->people; m_ind; m_ind = m_ind->next)
			{
				if(m_ind->mob == mob)
					m_ind->vnum = mob->vnum;
			}
		}
	}

	for(obj = object_data::obj_head; obj; obj = obj->next)
	{
		obj->vnum = GetValidVnum(OBJECT);
	
		AddObject(obj);
		
		for(o_ind = obj_index::o_ind_head; o_ind; o_ind = o_ind->n_list)
		{
			if(o_ind->obj == obj)
				o_ind->vnum = obj->vnum;
		}
	}
	
	for(room = room_data::room_list; room; room = room->next)
	{
		for(m_ind = room->people; m_ind; m_ind = m_ind->next)
			AddMobToRoom(m_ind, room);

		for(o_ind = room->contents; o_ind; o_ind = o_ind->next)
			AddObjToRoom(o_ind, room);
	}	

	str.Format("Zone re-numbered starting with vnum %d.", vnum);
	ShowText(str, false);
}


void CWinDEDlg::UnAlias(CString str)
{
	CString str1;

	if(str.IsEmpty())
		ShowText("Please specify which alias to remove.", false);
	else
	{
		if(alias_list.DeleteAlias(str))
			str1.Format("Alias %s has been removed.", str);
		else
			str1.Format("Alias %s does not exsist.", str);
	
		ShowText(str1, false);
	}
}

void CWinDEDlg::Link(CString args)
{
	CString arg1, arg2, str;
	int dir = -1, ret;
	room_data *room;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You must specify a room to link to this one.", false);
		return;
	}

	if(arg2.IsEmpty())
	{
		ShowText("You must specify a direction to create the exit in.", false);
		return;
	}

	room = GetRoomByVnum(atoi(arg1));

	if(room && in_room)
	{
		dir = GetDir(arg2);

		if(dir == -1)
		{
			ShowText("Invalid direction.", false);
			return;
		}

		if(in_room->exit[dir])
		{
			ret = MessageBox("Current room already has exit in that direction.\rDelete old exit?", 
				"Delete exit?", MB_YESNO);
			
			if(ret == IDYES)
			{
				delete in_room->exit[dir];
				in_room->exit[dir] = NULL;
			}
			else
				return;
		}

		if(room->exit[rev_dir[dir]])
		{
			ret = MessageBox("Target room already has exit in that direction.\rDelete old exit?", 
				"Delete exit?", MB_YESNO);
			
			if(ret == IDYES)
			{
				delete room->exit[rev_dir[dir]];
				room->exit[rev_dir[dir]] = NULL;
			}
			else
				return;
		}

		in_room->exit[dir] = new exit_data;
		in_room->exit[dir]->vnum = room->vnum;
		
		room->exit[rev_dir[dir]] = new exit_data;
		room->exit[rev_dir[dir]]->vnum = in_room->vnum;

		str.Format("%s exit now connects room %d to room %d", arg2, in_room->vnum, room->vnum);
		
		ShowText(str, false);
	}
}

void CWinDEDlg::Exits(CString args)
{
	int i;
	room_data *room;
	CString str, str2;

	if(in_room)
	{
		for(i = DIR_NORTH; i < MAX_DIR; i++)
		{
			if(in_room->exit[i])
			{
				room = GetRoomByVnum(in_room->exit[i]->vnum);
			
				str2.Format("\n&+L[&N%s&+L][&+b%d&N&+L]&n%s", dir_names[i], room->vnum, room->name);
				
				if(!in_room->exit[i]->keyword.IsEmpty())
					str2 += CString("\n") + in_room->exit[i]->keyword;
				
				if(!in_room->exit[i]->description.IsEmpty())
					str2 += CString("\n") + in_room->exit[i]->description;
				
				str += str2;
			}
		}
		
		if(!str.IsEmpty())
			ShowText(str, false);
		else
			ShowText("No Exits in current room.", false);
	}
	else
		ShowText("You are not in a room!.", false);
}

void CWinDEDlg::Alias(CString args)
{
	CString arg1,str;

	if(args.IsEmpty())
	{
		ShowText(alias_list.ShowAliasList(), false);
		return;
	}

	arg1 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You need to specify an alias to make.", false);
		return;
	}
	
	if(args.IsEmpty())
	{
		ShowText("You need to specify the command to alias.", false);
		return;
	}
	
	for(int i = 0; i < LastKey(); i++)
	{
		if(keyword_list[i].keyword == arg1)
		{	
			ShowText("Cannont alias a command keyword.", false);
			return;
		}
	}

	if(alias_list.AddAlias(arg1, args))
	{
		str.Format("%s now an alias for %s.", arg1, args);
		ShowText(str, false);
	}
	else
		ShowText("Alias already exists.", false);
}

void CWinDEDlg::Ask(CString args)
{
	CString arg1, arg2;
	mob_index *m_index;
	talk_data *quest;
	mob_data *mob;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(in_room)
	{		
		m_index = GetMobInRoom(in_room, arg1);

		mob = m_index->mob;

		if(mob && mob->quests)
		{
			for(quest = mob->quests->messages; quest; quest = quest->next)
			{
				if(quest->keywords.Find(arg2) > -1)
				{
					ShowText(quest->message, false);
				}
				else
					ShowText("No quest with that keyword.", false);
			}
		}
		else
			ShowText("Mobile has no quests.", false);
	}
}

void CWinDEDlg::Look(CString args)
{
	extra_desc *ed;
	mob_index *m_index;
	obj_index *o_index;
	room_data *room;
	CString str;
	obj_index *ob;
	
	if(!in_room)
		return;

	if(GetArgType(args) == ROOM || args.IsEmpty())
		ShowRoom();
	else if(str_prefix(args, "in"))
	{	
		CString arg1, arg2;
		arg1 = GetArg(args);
		arg2 = GetArg(args);

		if(o_index = ::GetObjInRoom(in_room, arg2))
		{
			str.Format("%s contains:", o_index->GetShortName());
			
			if(o_index->contents)
				ShowText(str, false);
			else
				ShowText(str, true);

			for( ob = o_index->contents; ob; ob = ob->next)
			{	
				str.Format("%s (%d)", ob->GetShortName(), ob->vnum);
				ShowText(str, true);
			}
		}
		else
		{
			for(ob = user->inventory; ob; ob = ob->next)
			{
				str.Format("%s contains:", ob->GetShortName());
				
			if(ob->contents)
				ShowText(str, false);
			else
				ShowText(str, true);

				if(ob->obj)
				{
					if(ob->obj->name.Find(arg2, 0))
					{
						for(obj_index *ob1 = ob->contents; ob1; ob1 = ob1->next)
						{
							str.Format("%s (%d)", ob1->GetShortName(), ob1->vnum);
							ShowText(str, true);
						}
					}
				}
			}
		}
	}
	else 
	{
		for(ed = in_room->first_extra_descr; ed; ed = ed->next) 
		{
			if(ed->keyword.Find(args) > -1) 
			{
				ShowText(ed->ShowDesc(), true);
				return;
			}
		}
	
		if((m_index = GetMobInRoom(in_room, args)))
		{
			ShowText(m_index->ShowMob(), true);
			return;
		}
		
		if((o_index = GetObjInRoom(in_room, args)))
		{
			if(!o_index->GetExtraDesc(args).IsEmpty())
			{
				ShowText(o_index->ShowObject(), false);
				ShowText(o_index->GetExtraDesc(args), true);
			}
			else
				ShowText(o_index->ShowObject(), false);

			return;
		}
		else
		{
			for(o_index = in_room->contents; o_index; o_index = o_index->next)
			{
				if((o_index->GetExtraDesc(str)).IsEmpty())
					continue;

				ShowText(o_index->GetExtraDesc(str), true);
				break;
			
			}
		}

		for(int i = DIR_NORTH; i < MAX_DIR; i++)
		{
			if(args == dir_names[i] || args == short_dir_names[i])
			{
				if(in_room)
				{
					if(in_room->exit[i])
					{
						room = in_room;

						in_room = GetRoomByVnum(in_room->exit[i]->vnum);

						ShowRoom();

						in_room = room;
					}
				}
			}
		}
	}
}

void CWinDEDlg::Goto(CString args)
{
	room_data *room;
	mob_index *mob;
	obj_index *obj;
	int x, i;


	if(args.IsEmpty()) {
		ShowText("Please Specify a room vnum, mob name, or object name.", true);
	} else {
		
		x = number_argument(args);

		if(GetMob(args))
		{
			i = 1;
			for(room = room_data::room_list; room; room = room->next)
			{
				for( mob = room->people; mob; mob = mob->next)
				{
					if(mob->mob)
					{
						if(mob->mob->name.Find(args) > -1)
						{
							if(x != i++ && x > -1)
								continue;

							in_room = room;
							ShowRoom();
							return;
						}
					}
				}
			}
		}
		else if(GetObj(args))
		{
			i = 1;
			for(room = room_data::room_list; room; room = room->next)
			{
				for(obj = room->contents; obj; obj = obj->next)
				{
					if(obj->obj)
					{
						if(obj->obj->name.Find(args) > -1)
						{
							if(x != i++ && x > -1)
								continue;

							in_room = room;
							ShowRoom();
							return;
						}
					}
				}
			}
		}
		else if((room = GetRoomByVnum(atoi(args)))) {
			in_room = room;
			ShowRoom();
		}
		else
			ShowText("Go where?", true);
	}	
	
	ShowText("Go where?", true);
}

void CWinDEDlg::Follow(CString args)
{
	mob_index *leader;
	mob_index *mob;
	CString arg1, arg2, str;
	int ret;

	arg1 = GetArg(args);
	arg2 = GetArg(args);
	
	if(arg1.IsEmpty())
	{
		ShowText("Please specify the vnum of the leader and follower.", false);
		return;
	}
	
	if(arg2.IsEmpty())
	{
		ShowText("Please specify vnum of the leader.", false);
		return;
	}

	if(in_room)
	{	
		mob = GetMobInRoom(in_room, arg1);
		leader = GetMobInRoom(in_room, arg2);

		if(!mob)
		{
			ShowText("Invalid follower.", false);
			return;
		}

		if(!leader)
		{
			ShowText("Invalid leader.", false);
			return;
		}

		if(mob->group_leader)
		{
			str.Format("Mobile %d already has a leader, change leaders?", mob->vnum);
			ret = MessageBox(str, "Change Leader?", MB_YESNO);
			
			if(ret == IDNO)
				return;
		}

		leader->AddFollower(mob);

		str.Format("%s now follows %s.", mob->GetShortName(), leader->GetShortName());
		ShowText(str, false);
	}
}

void CWinDEDlg::Mount(CString args)
{
	mob_index *mob, *mount;
	int ret;
	CString arg1, arg2, str;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You must specify the vnum of the mount and rider.", false);
		return;
	}

	if(arg2.IsEmpty())
	{
		ShowText("You must specify the vnum for the mount.", false);
		return;
	}
	
	if(in_room)
	{
		mob = GetMobInRoom(in_room, arg1);
		mount = GetMobInRoom(in_room, arg2);

		if(!mob)
		{
			ShowText("Invalid rider.", false);
			return;
		}

		if(!mount)
		{
			ShowText("Invalid mount.", false);
			return;
		}

		if(mount->rider)
		{
			str.Format("%s already has a rider, change riders?", mount->GetShortName());
			ret = MessageBox(str, "Change Rider?", MB_YESNO);

			if(ret == IDNO)
				return;
		}

		if(mob->riding)
		{
			str.Format("%s is already riding %s, change mount?", mob->GetShortName(), mob->riding->GetShortName());
			ret = MessageBox(str, "Change Mount?", MB_YESNO);

			if(ret == IDNO)
				return;
		}

		if(!mount->IsMount())
		{
			str.Format("%s is not a mount.", mount->GetShortName());
			ShowText(str, false);
			return;
		}

		mob->AddRiding(mount);

		str.Format("%s is now riding %s.", mob->GetShortName(), mount->GetShortName());
		ShowText(str, false);
	}
}

void CWinDEDlg::Equip(CString args)
{
	CString arg1, arg2, arg3, str;
	int loc= -1;
	mob_index *mob;
	obj_index *obj;

	arg1 = GetArg(args);
	arg2 = GetArg(args);
	arg3 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You must specify a mob to equip.", false);
		return;
	}

	if(arg2.IsEmpty())
	{
		ShowText("You must specify which item to equip", false);
		return;
	}

	if(in_room)
	{
		mob = GetMobInRoom(in_room, arg1);
		
		if(!mob)
		{
			ShowText("Invalid mobile.", false);
			return;		
		}
	
		obj = mob->GetObjInInv(atoi(arg2));
		
		if(!obj) 
		{
			ShowText("Invalid object vnum.", false);
			return;	
		}
		
		if(!arg3.IsEmpty())
		{
			for(loc = 0; loc < MAX_WEAR; loc++)
			{
				if(arg3 == wear_names[loc].name && obj->IsWearable(loc))
					break;
			}
		}
		else
		{	
			for(loc = 0; loc < MAX_WEAR; loc++)
			{
				if(obj->IsWearable(loc))
					break;
			}
		}

		if(loc == -1 || loc == MAX_WEAR)
		{
			ShowText("Object cannot be worn there.", false);
			return;
		}

		if(mob->InInventory(obj))
		{
			mob->RemoveObjFromInv(obj);
			mob->EquipObj(obj, loc);
			
			str.Format("%s now wears %s on %s %s.", mob->GetShortName(), obj->GetShortName(), sex[mob->GetSex()], slot_names[loc]); 
			ShowText(str, false);
		}
		else
			ShowText("Mobile must have object in inventory in order to wear it.", false);
	}
	else
		ShowText("You cannot equip a mob while your not in a room.", false);
}

void CWinDEDlg::CheckQuests(mob_index *mindex)
{
	mob_data *mob;
	quest_data *quest;

	if((mob = mindex->mob))
	{
		for(quest = mob->quests->quests; quest; quest = quest->next)
		{
			for(quest_item *tmp = quest->receive; tmp; tmp = tmp->next)
			{
				for(obj_index *obj = mindex->inventory; obj; obj = obj->next)
				{
					if(tmp->value == obj->vnum)
					{
						if(tmp->next == NULL)
						{
							GiveQuestReward(mindex, quest);
							RemoveQuestItems(mindex, quest);
						}
					}
						
				}
			}
		}
	}
}

void CWinDEDlg::RemoveQuestItems(mob_index *mob, quest_data *quest)
{
	for(obj_index *obj = mob->inventory; obj; obj = obj->next)
	{
		for(quest_item *item = quest->give; item; item = item->next)
		{
			if(obj->vnum == item->value)
				mob->RemoveObjFromInv(obj);
		}
	}
}

void CWinDEDlg::GiveQuestReward(mob_index *mob, quest_data *quest)
{
	object_data *obj;
	mob_data *mb;
	room_data *room;
	CString str;

	if(!quest->complete.IsEmpty())
		ShowText(quest->complete, false);
	if(!quest->disappear.IsEmpty())
		ShowText(quest->disappear, false);

	for(quest_item *item = quest->give; item; item = item->next)
	{
		switch(item->type)
		{
		case QST_GIVES_OBJ:
			if((obj = GetObjByVnum(item->value)))
			{
				str.Format("%s gives you %s.", mob->GetShortName(), obj->short_descr);
				ShowText(str, false);
				user->AddObjToInv(obj);	
			}
			else
				ShowText("QST_GIVES_OBJ: Unknown object vnum in quest.", false);
			break;
		case QST_GIVES_COINS:
			str.Format("%s gives you %d coins.", mob->GetShortName(), item->value);
			ShowText(str, false);
			break;
		case QST_GIVES_SKILL:
			break;
		case QST_GIVES_EXP:
			str.Format("%s gives you %d experience.", mob->GetShortName(), item->value);
			ShowText(str, false);
			break;
		case QST_GIVES_SPELL:
			str.Format("%s grants you '%s'", mob->GetShortName(), spells[item->value].SpellName());
			ShowText(str, false);
			break;
		case QST_GIVES_AFF:
			str.Format("%s casts '%s' on you.", mob->GetShortName(), spells[item->value].SpellName());
			ShowText(str, false);
			break;	
		case QST_GIVES_MOBS:
			if((room = GetRoomByVnum(item->value)))
			{
				mob_index *mob1;
				mob_index *next;

				for(mob1 = room->people; mob1; mob1 = next)
				{
					str.Format("%s transfers %s.", mob->GetShortName(), mob1->GetShortName());
					next = mob1->next;
					room->RemovePerson(mob1);
					in_room->AddPerson(mob1);
					ShowText(str, false);
				}

				room->RemoveEveryone();
			}
			else
				ShowText("QST_GIVES_MOBS: Invalid room vnum in quest.", false);
			break;
		case QST_GIVES_MOB:
			if((mb = GetMobByVnum(item->value)))
			{
				str.Format("A %s appears suddenly.", mb->short_descr);
				in_room->AddPerson(mb);
				ShowText(str, false);
			}
			else
				ShowText("QST_GIVES_MOB: Invalid mobile vnum in quest.", false);
			break;
		case QST_GIVES_PET:
			if((mb = GetMobByVnum(item->value)))
			{
				str.Format("A %s now follows you.", mb->short_descr);
				in_room->AddPerson(mb);
				ShowText(str, false);
			}
			else
				ShowText("QST_GIVES_PET: Invalid pet vnum in quest.", false);
			break;
		case QST_GIVES_TELE:
			if((room = GetRoomByVnum(item->value)))
			{
				str.Format("You are teleported to %s.", room->name);
				in_room = room;
				ShowText(str, false);
				ShowRoom(false);
			}
			else
				ShowText("QST_GIVE_TELE: Invalid room vnum in quest.", false);	
			break;
		case QST_GIVES_TRANS:
			if((room = GetRoomByVnum(item->value)))
			{
				str.Format("You are transfered to %s.", room->name);
				in_room = room;
				ShowText(str, false);
				ShowRoom(false);
			}
			else
				ShowText("QST_GIVE_TRANS: Invalid room vnum in quest.", false);
			break;
		}

		
	}

	ShowPrompt();
}

void CWinDEDlg::Give(CString args)
{
	CString arg1, arg2, str;
	mob_index *mob;
	obj_index *obj;
	object_data *object;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(arg1.IsEmpty())
	{
		ShowText("You must specify object and mobile vnums.", true);
		return;
	}

	if(arg2.IsEmpty())
	{
		ShowText("You must specify a mobile to give the object too.", true);
		return;
	}
	
	if(in_room)
	{
		if((object = GetObj(arg1)))
			obj = user->GetObjInInv(object->vnum);

		mob = GetMobInRoom(in_room, arg2);

		if(!obj)
		{
			ShowText("Invalid object vnum.", true);
			return;
		}

		if(!mob)
		{
			ShowText("Invalid mobile vnum.", true);
			return;
		}

		mob->AddObjToInv(obj);
		user->RemoveObjFromInv(obj);

		str.Format("%s now has %s.", mob->GetShortName(), obj->GetShortName());
		ShowText(str, true);
	
		CheckQuests(mob);
	}
}

void CWinDEDlg::Load(CString args)
{
	CString arg1, arg2, str;
	object_data *obj;
	mob_index *m_ind;
	obj_index *o_ind;
	mob_data *mob;

	arg1 = GetArg(args);
	arg2 = GetArg(args);

	if(GetArgType(arg1) == MOBILE)
	{
		mob = GetMob(arg2);

		if(mob)
		{
			if(in_room)
			{
				m_ind = in_room->AddPerson(mob);

				str.Format("%s loaded in room %s.", mob->short_descr, in_room->name);

				AddMobToRoom(m_ind, in_room);

				ShowText(str, true);
			}
			else
				ShowText("Unable to load anything without being in a room.", true);
		}
		else
			ShowText("Invalid vnum for mobile.", true);

	}
	else if(GetArgType(arg1) == OBJECT)
	{
		obj = GetObj(arg2);

		if(obj)
		{
			if(in_room)
			{
				o_ind = in_room->AddContent(obj);

				str.Format("%s loaded in room %s.", obj->short_descr, in_room->name);
				
				AddObjToRoom(o_ind, in_room);

				ShowText(str, true);
			}
			else
				ShowText("Unable to load anything without being in a room.", true);
		}
		else
			ShowText("Invalid vnum for object.", true);
	}
	else
		ShowText("Please specify mob or obj.", true);
}

void CWinDEDlg::New(CString args)
{
	CString arg1, arg;
	room_data *room;

	if(args.IsEmpty()) {
		ShowText("Please specify either Area, Room, Mob, or Object.", false);
		return;
	}

	arg = GetArg(args);

	if(GetArgType(arg) == MOBILE)
		OnNewMob();
	else if(GetArgType(arg) == OBJECT)
		OnNewObject();
	else if(GetArgType(arg) == ROOM)
	{
		room = in_room;

		EditRoom dlg(this);
		int ret;
	
		dlg.room = new room_data;
	
		dlg.room->vnum = GetValidVnum(ROOM);
		dlg.vnum = dlg.room->vnum;
	
		ret = dlg.DoModal();
		
		if(ret == IDOK) 
		{
			in_room = dlg.room;
		
			AddRoom(dlg.room);	
		
			arg1 = GetArg(args);

			if(!arg1.IsEmpty())
			{
				for(int i = DIR_NORTH; i < MAX_DIR; i++)
				{
					if(arg1 == dir_names[i] || arg1 == short_dir_names[i])
					{
						if(room->exit[i])
						{
							CString str;
							str.Format("%s already has a %s exit\nReplace?", room->name, dir_names[i]);
						
							if(MessageBox(str, "Replace Exit?", MB_YESNO) == IDNO)
								return;
							else
								delete in_room->exit[i];
						}
					
						room->exit[i] = new exit_data();
						room->exit[i]->vnum = in_room->vnum;

						in_room->exit[rev_dir[i]] = new exit_data();
						in_room->exit[rev_dir[i]]->vnum = room->vnum;
					}
				}
			}

			map.DrawArea();
			ShowRoom(false);
		}
	}
	else if(GetArgType(arg) == AREA)
		OnNewArea();
}

void CWinDEDlg::Edit(CString args)
{
	CString vnum_str, arg;
	int vnum;

	if(args.IsEmpty()) {
		ShowText("Please specify Room, Mob, Area, or Object.", true);
		return;
	}
	
	arg = GetArg(args);
	vnum_str = GetArg(args);
	
	if(vnum_str.IsEmpty())
		vnum = -1;
	else
		vnum = atoi(vnum_str);
		
	if(GetArgType(arg) == MOBILE)
		OnEditMob(vnum);
	else if(GetArgType(arg) == OBJECT)
		OnEditObject(vnum);
	else if(GetArgType(arg) == ROOM) {
		if(vnum == -1)
		{
			OnEditRoom(in_room->vnum);
			ShowRoom();
		}
		else
			OnEditRoom(vnum);
	} 
	else if(GetArgType(arg) == AREA)
		OnAreaProperties();
	else 
		ShowText("Please specify Room, Mob, Object, or Area.", true);
}

void CWinDEDlg::Delete(CString args)
{
	CString vnum_str, arg;
	int vnum;
	room_data *room;

	if(args.IsEmpty()) {
		ShowText("Please specify Room, Mob, or Object.", false);
		return;
	}
	
	arg = GetArg(args);
	vnum_str = GetArg(args);
	
	if(GetArgType(arg) == EXIT)
	{
		int dir = GetDir(vnum_str);
		if(in_room)
		{
			if(in_room->exit[dir])
			{
				room = GetRoomByVnum(in_room->exit[dir]->vnum);

				if(room)
				{
					if(room->exit[rev_dir[dir]])
					{
						delete room->exit[rev_dir[dir]];
						room->exit[rev_dir[dir]] = NULL;
					}
				}

				delete in_room->exit[dir];
				in_room->exit[dir] = NULL;
			}
		}
		
		return;
	}
	
	if(vnum_str.IsEmpty())
		vnum = -1;
	else
		vnum = atoi(vnum_str);
	
	
	if(GetArgType(arg) == MOBILE)
		DeleteMob(vnum);
	else if(GetArgType(arg) == OBJECT)
		DeleteObj(vnum);
	else if(GetArgType(arg) == ROOM) {
		if(vnum == -1)
			if(in_room) DeleteRoom(in_room->vnum);
		else
			DeleteRoom(vnum);
	} 
	else 
		ShowText("Please specify Room, Mob, or Object.", false);
}

void CWinDEDlg::Command(CString args)
{
	int i, max = 10, len, spaces, x;
	CString str, str2 ;
	
	for(i = 0; i < LastKey(); i++) {
		str = keyword_list[i].keyword;
		
		if(str == "none")
			continue;

		len = str.GetLength();

		spaces = max - len;
		
		for(x = 0; x < spaces; x++)
			str+= " ";

		if(++i < LastKey()) 
			str2 = keyword_list[i].keyword;
		else {
			ShowText(str, false);
			break;
		}

		len = str2.GetLength();
		
		spaces = max - len;
		
		for(x = 0; x < spaces; x++)
			str2 += " ";

		if(++i < LastKey())
			str2 += keyword_list[i].keyword;
		else {
			str += str2;
			ShowText(str, false);
			break;
		}
		
		str += str2;
		
		ShowText(str, false);
	}
}

int CWinDEDlg::InterpKeyWord(CString &str)
{
	int i, num, cmd = -1;
	CString keyword, args;

	str.TrimLeft();
	str.TrimRight();

	str.MakeLower();
	num = str.Find(' ', 0);
	
	if(num > 0) {
		keyword = str.Left(num);
		args = str.Right(str.GetLength() - (num+1));
	} else 
		keyword = str;

	for(i = 0; i < LastKey(); i++) {
		if(str_prefix(keyword, keyword_list[i].keyword)) {
			cmd = keyword_list[i].cmd;
			break;
		}
	}

	switch(cmd) 
	{
		case CMD_NORTH:		OnNorth();		break;
		case CMD_SOUTH:		OnSouth();		break;
		case CMD_WEST:		OnWest();		break;
		case CMD_EAST:		OnEast();		break;
		case CMD_UP:		OnUp();			break;
		case CMD_DOWN:		OnDown();		break;
		case CMD_NORTHWEST:	OnNorthWest();	break;
		case CMD_SOUTHWEST:	OnSouthWest();	break;
		case CMD_NORTHEAST:	OnNorthEast();	break;
		case CMD_SOUTHEAST:	OnSouthEast();	break;
		case CMD_LOOK:		Look(args);		break;
		case CMD_GOTO:		Goto(args);		break;
		case CMD_NEW:		New(args); 	    break;
		case CMD_EDIT:		Edit(args);	    break;
		case CMD_DELETE:	Delete(args);	break;
		case CMD_GRID:		Grid(args);		break;
		case CMD_SAVE:		OnSave();		break;
		case CMD_EXIT:		OnClose();		break;
		case CMD_COMMAND:	Command(args);	break;
		case CMD_STAT:		Stat(args);		break;
		case CMD_FOLLOW:    Follow(args);   break;
		case CMD_MOUNT:     Mount(args);    break;
		case CMD_GIVE:      Give(args);     break;
		case CMD_EQUIP:     Equip(args);    break;
		case CMD_LOAD:      Load(args);     break;
		case CMD_DEF_ROOM:  Default(args);  break;
		case CMD_ALIAS:     Alias(args);    break;
		case CMD_RENUMBER:  Renumber(args); break;
		case CMD_ASK:		Ask(args);		break;
		case CMD_UNALIAS:   UnAlias(args);  break;
		case CMD_LINK:		Link(args);     break;
		case CMD_EXITS:		Exits(args);	break;
		case CMD_CLONE:		Clone(args);	break;
		case CMD_PURGE:		Purge(args);	break;
		case CMD_DROP:		Drop(args);		break;
		case CMD_GET:		Get(args);		break;
		case CMD_LIST:		List(args);		break;
		case CMD_SHOW:		Show(args);		break;
		case CMD_INV:		Inv(args);		break;
		case CMD_TAKE:		Take(args);		break;
		case CMD_WHERE:		Where(args);	break;
		case CMD_NONE:						
		default: 
			return -1;
	}
	
	history.AddCmd(cmd, keyword, args);

	return i;
}

HTREEITEM CWinDEDlg::InsertItem(CString &title, HTREEITEM parent, void *data, int image)
{
	HTREEITEM ti;
	
	title = StripAnsiChars(title);

	ti = zone_tree.InsertItem(TVIF_TEXT | TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM | 
	      TVIF_SELECTEDIMAGE | TVIF_STATE, title, image, image, 0, 0, NULL, parent, NULL);

	zone_tree.SetItemData(ti, (DWORD)data);

	zone_tree.RedrawWindow();

	return ti;  
}

void CWinDEDlg::RemoveItem(HTREEITEM item)
{
	zone_tree.DeleteItem(item);
	
	zone_tree.RedrawWindow();
}

void CWinDEDlg::UpdateItem(CString &title, HTREEITEM item)
{	
	zone_tree.SetItemText(item, StripAnsiChars(title));

	zone_tree.RedrawWindow();
}

LRESULT CWinDEDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	SPC_NMHDR* pHdr = (SPC_NMHDR*) lParam;
	int msg;
	switch(message) 
	{
	case WM_NOTIFY:
		switch(wParam) 
		{
		case IDC_SPLITTER1:	
			DoResize1(pHdr->delta);
			break;
		}
	case ICON_MESSAGE:
		break;	
	case WM_COMMAND:
		msg = HIWORD(wParam);
		switch(msg) 
		{
		case EN_SETFOCUS:
			CWnd *ed;
			ed = GetDlgItem(IDC_COMMAND);
			ed->SetFocus();
			break;
		}
	}
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CWinDEDlg::DoResize1(int delta)
{
	CWnd *frame = GetDlgItem(IDC_EDIT_FRAME);
	CWnd *text = GetDlgItem(IDC_COMMAND);
	CWnd *button = GetDlgItem(IDC_ENTER);

	CSplitterControl::ChangeWidth(m_pColorWnd, delta);
	CSplitterControl::ChangeWidth(frame, delta);
	CSplitterControl::ChangeWidth(text, delta);
	CSplitterControl::ChangePos(button, -delta, 0);
	CSplitterControl::ChangeWidth(&zone_tree, -delta, CW_RIGHTALIGN);

	Invalidate();
	UpdateWindow();
}

void CWinDEDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == IDT_AUTO_SAVE)
		OnSave();

	CDialog::OnTimer(nIDEvent);
}

void CWinDEDlg::ShowPrompt() 
{
	int mobs = 0, objs = 0;
	mob_index *mob;
	obj_index *obj;
	CString str;
	
	if(!in_room) {
		ShowText("&+g<In Room: None Mobs: 0 Objs: 0>", false);
		return;
	}

	for(mob = in_room->people; mob; mob = mob->next)
		mobs++;

	for(obj = in_room->contents; obj; obj = obj->next)
		objs++;

	str.Format("&+g<In Room: %d Mobs: %d Objs: %d>", in_room->vnum, mobs, objs);
	
	ShowText(str, false);
}

room_data *CWinDEDlg::CreateRoomGrid(int sizex, int sizey, int sizez)
{
	room_data *room;
	int *room_array;
	int vnum;
	int pos;
	int gridsize;
	int x, y, z, i;

	if(sizex <= 0 || sizey <= 0 || sizez < 0)
		return NULL;
	
	if(sizez == 0) sizez = 1;

	gridsize = sizex*sizey*sizez;
	
	room_array = new int[gridsize];

	for(i = 0; i < gridsize; i++)
	{
		room = new room_data;
		room->vnum = GetValidVnum(ROOM);
		room->AddToList();
		
		room_count++;

		UpdateStatusBar();
		
		CString str;
		
		str.Format("%d - %s", room->vnum, StripAnsiChars(room->name));
		
		room->m_tThis = InsertItem(str, m_tRooms, room, room->class_index);
		room->m_tContents = InsertItem(CString("Contents"), room->m_tThis, NULL, CONTENTS);
		room->m_tPeople = InsertItem(CString("Occupants"), room->m_tThis, NULL, PEOPLE);
		
		room_array[i] = room->vnum;
	}

	pos = 0;
	for(z = 0; z < sizez; z++) {
		for(y = 0; y < sizey; y++) {
			for(x = 0; x < sizex; x++) {

				vnum = room_array[pos];

				if (z != 0) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_DOWN] = new exit_data;
					room->exit[DIR_DOWN]->vnum = room_array[pos - (sizex*sizey)];
				}
				
				if (z != (sizez - 1)) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_UP] = new exit_data;
					room->exit[DIR_UP]->vnum = room_array[pos + (sizex * sizey)];
				}

				if (y != 0) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_SOUTH] = new exit_data;
					room->exit[DIR_SOUTH]->vnum = room_array[pos - sizex];
				}
				
				if (y != (sizey - 1)) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_NORTH] = new exit_data;
					room->exit[DIR_NORTH]->vnum = room_array[pos+sizex];
                }
				
				if (x != 0) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_EAST] = new exit_data;
					room->exit[DIR_EAST]->vnum = room_array[pos-1];
				}
				
				if (x != (sizex - 1)) {
					room = GetRoomByVnum(vnum);
					room->exit[DIR_WEST] = new exit_data;
					room->exit[DIR_WEST]->vnum = room_array[pos+1];
				}
				
				pos++;
			}
		}
	}
			
	delete [] room_array;

	map.DrawArea();

	return room;
}

void CWinDEDlg::OnCreateGrid()
{
	DlgCreateGrid grid;
	room_data *room;
	int x, y, z;

	if(grid.DoModal() == IDOK)
	{
		x = grid.sizex;
		y = grid.sizey;
		z = grid.sizez;

		room = CreateRoomGrid(x, y, z);

		if(room != NULL) {
			in_room = room;
			ShowRoom();
		}
	}
}

void CWinDEDlg::ShowText(const char* str, bool show_prompt)
{
	CString st;

	st = str;

	if(show_prompt)
	st += "&n\n";

	if(show_prompt) {
		st += "&n\n";
		m_pColorWnd->ReplaceSelText(st);
		
		ShowPrompt();
	} else
	{
		st += "&n\n";
		m_pColorWnd->ReplaceSelText(st);
	}
}

void CWinDEDlg::Grid(CString args)
{
	CString str_x;
	CString str_y;
	CString str_z;
	int x, y, z=1, num=-1;
	
	num = args.Find(' ', 0);
	
	if(num > 0) 
	{
		str_x = args.Left(num);
		args = args.Right(args.GetLength() - (num+1));
		x = atoi(str_x);
	} 
	else 
	{
		ShowText("You Must Specify the length of the grid", true);
		return;
	}
	
	if(x < 1 || x > 100) 
	{
		ShowText("Specify a width between 1 and 20 please", true);
		return;
	}
	
	num = -1;
	num = args.Find(' ', 0);
	
	if(num < 0 && !args.IsEmpty()) 
	{
		str_y = args;
		args = "";
		y = atoi(str_y);
	}
	else if(num > 0) 
	{
		str_y = args.Left(num);
		args = args.Right(args.GetLength() - (num+1));
		y = atoi(str_y);
	} 
	else 
	{
		ShowText("You Must Specify the width of the grid", true);
		return;
	}
	
	if(y < 1 || y > 100) 
	{
		ShowText("Specify a length between 1 and 20 please", true);
		return;
	}
	
	if(!args.IsEmpty())
	{
		str_z = args;
		z = atoi(str_z);
	
		if(z < 0 || z > 100) 
		{
			ShowText("Specify a depth between 0 and 10 please", true);
			return;
		}
	} else
		z = 1;
	
	args.Format("%d rooms succesfuly created.", x*y*z);
	ShowText(args, false);
	in_room = CreateRoomGrid(x, y, z);
	ShowRoom();
}

void CWinDEDlg::DeleteRoom(room_data *room)
{		
	RemoveItem(room->m_tPeople);
	RemoveItem(room->m_tContents);
	RemoveItem(room->m_tThis);
	
	room->RemoveFromList();
	
	if(in_room == room) 
	{
		in_room = room_data::room_list;
		
		if(in_room)
			ShowRoom();
		else
			ShowPrompt();
	}

	room_count--;
	UpdateStatusBar();
	
	room = NULL;

	map.DrawArea();
}

void CWinDEDlg::DeleteAllRooms()
{	
	while(room_data::room_list)
		DeleteRoom(room_data::room_list);

	room_data::room_hi_vnum = 1;
	room_data::room_list = NULL;
	in_room = NULL;
}

void CWinDEDlg::DeleteAllMobs()
{
	mob_data	*mob,	*mob_next;
	talk_data	*tmp_t, *next_t;
	quest_data	*tmp_q, *next_q;

	for(mob = mob_data::first_mob; mob; mob = mob_next) 
	{
		mob_next = mob->next;
		
		if(mob->shop)
		{
			shop_count--;
			delete mob->shop;
		}

		if(mob->quests) 
		{
			for(tmp_t = mob->quests->messages; tmp_t; tmp_t = next_t) 
			{
				next_t = tmp_t->next;
				delete tmp_t;
				quest_count--;
			}

			for(tmp_q = mob->quests->quests; tmp_q; tmp_q = next_q) 
			{
				next_q = tmp_q->next;
				delete tmp_q;
				quest_count--;
			}
		}
		
		RemoveItem(mob->m_tThis);

		delete mob;
		mob_count--;
	}
	
	mob_data::high_mob_vnum = 1;
	mob_data::last_mob = NULL;
	mob_data::first_mob = NULL;
	
	UpdateStatusBar();
}

void CWinDEDlg::DeleteAllObjs()
{	
	extra_desc	*ped,	*next_ed;
	object_data *obj,	*obj_next;
	
	for(obj = object_data::obj_head; obj; obj = obj_next) 
	{
		for(ped = obj->first_extra_descr; ped; ped = next_ed) 
		{
			next_ed = ped->next;
			delete ped;
		}
		
		obj->RemoveContents();

		obj_next = obj->next;
		
		RemoveItem(obj->m_tThis);

		delete obj;
		obj_count--;
	}
	
	object_data::high_obj_vnum = 1;
	object_data::obj_head = NULL;
	UpdateStatusBar();
}

void CWinDEDlg::CloseArea()
{	
	if(area_data::area) 
	{
		DeleteAllRooms();
	
		DeleteAllMobs();

		DeleteAllObjs();

		delete area_data::area;
		area_data::area = NULL;
	}
	
	shop_count = 0;
	room_count = 0;
	mob_count = 0;
	quest_count = 0;
	obj_count = 0;

	if(m_pColorWnd)
		m_pColorWnd->Reset();
	
	zone_tree.DeleteAllItems();
}

void CWinDEDlg::Stat(CString args)
{
	CString vnum_str, arg;
	int vnum;

	mob_data *mob;
	object_data *obj;

	if(args.IsEmpty()) 
	{
		ShowText("Please specify Room, Mob, Area, or Object.", true);
		return;
	}
	
	arg = GetArg(args);
	vnum_str = GetArg(args);	

	if(GetArgType(arg) == MOBILE)
	{	
		mob = GetMob(vnum_str);
		vnum = mob->vnum;
		StatMob(vnum);
	}
	else if(GetArgType(arg) == OBJECT)
	{
		obj = GetObj(vnum_str);
		vnum = obj->vnum;
		StatObj(vnum);
	}
	else if(GetArgType(arg) == ROOM) 
	{
		vnum = atoi(vnum_str);

		if(vnum == -1)
			StatRoom(in_room->vnum);
		else
			StatRoom(vnum);
	} 
	else if(GetArgType(arg) == AREA)
		OnAreaProperties();
	else 
		ShowText("Please specify Room, Mob, Object, or Area.", true);
}

void CWinDEDlg::StatMob(int vnum)
{
	mob_data *mob;
	CString str;
	
	if(vnum == -1) 
	{
		ShowText("Please specify a valid vnum.", true);
		return;
	}

	if(!(mob = GetMobByVnum(vnum))) 
	{
		str.Format("No mobile with vnum: %d", vnum);
	} 
	else 
	{
		CString str2;
		str2.Format("&+cVnum:&n %d      &+cLevel:&n %d\n", mob->vnum, mob->level);
		str = str2;
		str += "&+cKeywords:&n    " + mob->name			+ "\n";
		str += "&+cShort Name:&n  " + mob->short_descr	+ "\n";
		str += "&+cLong Name:&n   " + mob->long_descr	+ "\n";
		str += "&+cDescription:&n " + mob->description	+ "\n";
		str2.Format("&+cRace:&n        %-10s ", GetRaceName(mob->race));
		str += str2;
		str2.Format("&+cClass:&n       %s\n", GetClassName(mob->c_class));
		str += str2;
		str2.Format("&+cSex:&n         %-10s ", GetSex(mob->sex));
		str += str2;
		str2.Format("&+cPosition:&n    %s\n", GetPosition(mob->position));
		str += str2;
		str2.Format("&+cSize:&n        %-10s ", GetSize(mob->size));
		str += str2;
		str2.Format("&+cAlignment:&n   %d\n", mob->alignment);
		str += str2;
	}
		
	ShowText(str, true);
}

void CWinDEDlg::StatObj(int vnum)
{
	int i, x;
	object_data *obj;
	CString str;
	CString str2;

	if(vnum == -1) 
	{
		ShowText("Please specify a valid vnum.", true);
		return;
	}

	if(!(obj = GetObjByVnum(vnum))) 
	{
		str.Format("No object with vnum: %d", vnum);
	} 
	else 
	{
		str2.Format("&+cVnum:&n %d      &+cType:&n %s\n", obj->vnum, item_types[obj->item_type].name);
		str = str2;
		str += "&+cKeywords:&n    " + obj->name			+ "\n";
		str += "&+cShort Name:&n  " + obj->short_descr	+ "\n";
		str += "&+cDescription:&n " + obj->description	+ "\n";
		str2.Format("&+cMaterial:&n    %-15s ", materials[obj->material]);
		str += str2;
		str2.Format("&+cCraftsmanship:&n %s\n", craftsmanship[obj->craftsmanship]);
		str += str2;
		str2.Format("&+cWeight:&n      %-15d ", obj->weight);
		str += str2;
		str2.Format("&+cVolume:&n		  %d\n", obj->volume);
		str += str2;
		str2.Format("&+cSize:&n        %-15d ",obj->size);
		str += str2;
		str2.Format("&+cCondition:&n     %d\n", obj->condition);
		str += str2;
		str2.Format("&+cApply Type:&n  %-15s &+cApply Value:&n   %d\n", apply_names[obj->applies[0].loc], obj->applies[0].value);
		str += str2;
		str2.Format("&+cApply Type:&n  %-15s &+cApply Value:&n   %d\n", apply_names[obj->applies[1].loc], obj->applies[1].value);
		str += str2;
		
		str2.Format("&+cValue 1:&n %-3d &+cValue 2:&n %-6d &+cValue 3:&n %-5d &+cValue 4:&n %d\n", obj->value[0], obj->value[1], obj->value[2], obj->value[3]);
		str += str2;

		str2.Format("&+cValue 5:&n %-3d &+cValue 6:&n %-6d &+cValue 7:&n %-5d &+cValue 8:&n %d\n", obj->value[4], obj->value[5], obj->value[6], obj->value[7]);
		str += str2;

		str += "&+cWear Locations:&n ";

		x = 0;
		for(i = 0; i < NUM_ITEM_WEAR_VECTORS; i++)
		{
			if(IS_SET(obj->wear_flags, wear_locs[i].bv))
			{
				x++;

				str += "(";
				str += wear_locs[i].name;
				str += ") ";

				if(x % 4 == 0)
						str += "\n                ";
			}
		}

		str += "\n\n&+cExtra Flags:&n ";
		
		
		x = 0;
		
		for(i = 0; i < ExtraFlagCount(); i++)
		{
			if(obj->ExtraIsSet(*obj_flags[i].bv))
			{
				x++;
				
				str += "(";
				str += obj_flags[i].name;
				str += ") ";
				
				if(x % 6 == 0)
					str += "\n             ";
			}
		}
	}
		
	ShowText(str, true);
}

void CWinDEDlg::StatRoom(int vnum)
{
	room_data *room;
	CString str;
	CString str2;
	int i, x;

	if(vnum == -1) 
	{
		ShowText("Please specify a valid vnum.", true);
		return;
	}

	if(!(room = GetRoomByVnum(vnum))) 
	{
		str.Format("No room with vnum: %d", vnum);
	} 
	else 
	{
		str2.Format("&+cVnum:&n %d        &+cSector:&n %s\n", room->vnum, sector_names[room->sector_type][1]);
		str = str2;
		str += "&+cKeywords:&n      " + room->name + "\n";
		str += "&+cDescription:&n   " + room->description + "\n";
		
		str2 = "";

		for(i = 0, x = 0; i < MaxRoomFlags;i++) 
		{
			if(room->RoomIsSet(*room_flags_info[i].bv)) 
			{
				if(!str2.IsEmpty())
				{
					if(x%4 == 0)
						str2 += "\n";
				}
				
				str2 += "&n(";
				str2 += room_flags_info[i].name;
				str2 += "&n) ";
				x++;
			}
		}
		
		if(!str2.IsEmpty())
		{
			str += "&+cRoom Flags:&n\n";
			str += str2;
			str += "\n\n";
		}

		str2.Format("&+cCurrent Speed:&n %-5d ", room->current);
		str += str2;
		str2.Format("&+cCurrent Dir:&n   %s\n", dir_name[room->current_dir]);
		str += str2;
		str2.Format("&+cFall Chance:&n   %-5d ", room->fall_chance);
		str += str2;
		str2.Format("&+cLighting:&n      %d\n", room->light);
		str += str2;

		str2 = "";

		for(i = DIR_NORTH; i< MAX_DIR; i++)
		{
			if(room->exit[i])
				str2 += dir_name[i] + CString(" ");
		}
	
		if(!str2.IsEmpty())
		{
			str += "&+cExits:         &n";
			str += str2;
			str += "\n";
		}

		if(room->people)
		{
			str += "&+cPeople In Room:\n";
			for(mob_index *mob = room->people; mob; mob = mob->next)
			{
				str2.Format("%d - %s\n", mob->vnum, mob->GetShortName());
				str += str2;
			}
		}

		if(room->contents)
		{
			str += "&+cObjects In Room:\n";
			for(obj_index *obj = room->contents; obj; obj = obj->next)
			{
				str2.Format("%d - %s\n", obj->vnum, obj->GetShortName());
				str += str2;
			}
		}
	}
		
	ShowText(str, true);
}

void CWinDEDlg::OnHistory()
{
	history.ShowHistory(this);
}

void CWinDEDlg::HistoryMenu(UINT id)
{
	history.ExecuteCmd(id, this);
}


BOOL CWinDEDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CWinDEDlg::OnBitCalc()
{
	CBvcalcutatorDlg bv;

	bv.DoModal();
}