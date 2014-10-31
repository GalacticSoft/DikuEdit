// DlgMapEdit.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgMapEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgMapEdit dialog

DlgMapEdit::DlgMapEdit(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMapEdit::IDD, pParent)
{	


	//{{AFX_DATA_INIT(DlgMapEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DlgMapEdit::~DlgMapEdit()
{
	MapLevel *level, *next;

	for(level = ground_level->above; level; level = next)
	{
		next = level->above;
		delete level;
	}

	for(level = ground_level->below; level; level = next)
	{
		next = level->below;
		delete level;
	}

	if(ground_level)
		delete ground_level;
	
}

void DlgMapEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgMapEdit)
	DDX_Control(pDX, IDC_ROOM_TREE, room_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgMapEdit, CDialog)
	//{{AFX_MSG_MAP(DlgMapEdit)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZING()
	ON_WM_MENUSELECT()
	ON_COMMAND_EX(ID_MAPMENU_EDITROOM,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_DELETEROOM,	MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_NEWROOM,		MenuSelect)
	ON_COMMAND(ID_CENTER,					Center)
	ON_COMMAND(ID_VNUM,						ShowVnum)
	ON_COMMAND_EX(ID_LEVEL_UP,				ChangeLevel)
	ON_COMMAND_EX(ID_LEVEL_DOWN,			ChangeLevel)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_INSIDE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_CITY,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_FIELD,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_FOREST,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_HILLS,		MenuSelect)	
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_MOUNTAIN,		MenuSelect)	
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_WATERSWIM,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_WATERNOSWIM,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_AIR,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERWATER	,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERWATERGROUND,		MenuSelect)	
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_FIREPLANE,		MenuSelect)	
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_OCEAN,		MenuSelect)		
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDWILD,		MenuSelect)	
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDCITY,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDWATER,		MenuSelect)		
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDNOSWIM,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDAIR,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_AIRPLANE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_WATERPLANE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_EARTHPLANE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_ETHEREALPLANE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_ASTRALPLANE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_DESERT,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_ARCTIC,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_SWAMP,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_ROAD,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDNOPASS,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDOCEAN,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_TERRAIN_UNDERGROUNDINSIDE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_MOBILES_ADDMOBILE,		MenuSelect)
	ON_COMMAND_EX(ID_MAPMENU_CONTENTS_ADDITEM,		MenuSelect)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgMapEdit message handlers

BOOL DlgMapEdit::OnInitDialog() 
{
	ground_level = new MapLevel(101, 101);
	
	curr_level = ground_level;

	for(int ter = 0; ter < SECT_MAX+1; ter++)
		LoadTerrain(ter);

	curr_room.x = MID_X;
	curr_room.y = MID_Y;
	curr_room.z = 0;

	shut_down = false;
	show_vnum = false;

	CRect rect, window_size;

	m_Tool.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC );
	m_Tool.LoadToolBar(IDR_MAP_TOOLS);
	m_Tool.GetClientRect(rect);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDR_MAP_TOOLS);

	SetScrollRange(SB_VERT, 0, Y_SCROLL-V_CELLS);
	SetScrollPos(SB_VERT, (Y_SCROLL-V_CELLS)/2);

	SetScrollRange(SB_HORZ, 0, X_SCROLL-H_CELLS);
	SetScrollPos(SB_HORZ, (X_SCROLL-H_CELLS)/2);

	GetWindowRect(window_size);

	//don't ask me it just works :P
	window_size.bottom = (15*(CELL_HEIGHT/*V_CELLS*/))+rect.bottom+5;
	window_size.right = (16*(CELL_WIDTH/*H_CELLS*/))+2;
	
	//window_size.bottom = (curr_level->y/V_CELLS)/*CELL_HEIGHT*/;
	//window_size.right = (16*(CELL_WIDTH/*H_CELLS*/))+2;
	MoveWindow(window_size);

	CDialog::OnInitDialog();

	par = (CWinDEDlg*)GetParent();
	
	ClearArea();
	DrawArea();

	CImageList iml;
	CBitmap bm;
	iml.Create(IDB_TREE_MOB_INDEX, 16, 0, RGB(255, 0, 0));

	bm.LoadBitmap(IDB_TREE_OBJ_INDEX);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_PEOPLE);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_CONTENTS);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	room_tree.SetImageList(&iml, TVSIL_NORMAL);
	
	iml.Detach();
	
	UpdateDisplay();

	INIT_EASYSIZE;

	return TRUE;
}

BEGIN_EASYSIZE_MAP(DlgMapEdit)
//	EASYSIZE(IDC_ROOM_TREE,ES_BORDER,ES_BORDER,IDC_STATIC,ES_BORDER,0)
//	EASYSIZE(IDC_STATIC, IDC_ROOM_TREE, ES_BORDER, ES_BORDER, ES_BORDER, 0);	
END_EASYSIZE_MAP

void DlgMapEdit::OnPaint() 
{
	CDC MemDC;

	CPaintDC dc(this); // device context for painting

	CRect toolbar, client, outline, room;
	
	const int offset = 2;
	
	int x, y;
	int posx, posy;
	int yoff, xoff;
	
	HICON cell;
	dc.SetMapMode( MM_TEXT );

	GetWindowRect(client);
	 
	m_Tool.GetClientRect(toolbar);
	toolbar.bottom += offset;
	
	//room_tree.GetClientRect(&room);

	//client.left = room.right;
	client.top += toolbar.bottom;

	yoff = GetScrollPos(SB_VERT);
	xoff = GetScrollPos(SB_HORZ);
	CRect  rect;

	dc.FillSolidRect(client, black);

	for(y = yoff; y < curr_level->y /* = yoff+V_CELLS+1*/; y++)
	{
		for(x = xoff; x < curr_level->x /*= xoff+H_CELLS+1*/; x++)
		{
			cell = GetTerrainIcon(curr_level->map[x][y].terrain);
			
			if(x == 0 && y == 0) 
			{
				posx = x-(xoff*CELL_WIDTH);
				posy = toolbar.bottom-(yoff*CELL_HEIGHT);
			}
			else if(x == 0)
			{
				posx = x-(xoff*CELL_WIDTH);
				posy = y*CELL_HEIGHT+toolbar.bottom-(yoff*CELL_HEIGHT);
			}
			else if(y == 0)
			{
				posx = x*CELL_WIDTH-(xoff*CELL_WIDTH);
				posy = toolbar.bottom-(yoff*CELL_HEIGHT);
			}
			else
			{
				posx = x*CELL_WIDTH-(xoff*CELL_WIDTH);
				posy = y*CELL_HEIGHT+toolbar.bottom-(yoff*CELL_HEIGHT);
			}
			
			dc.DrawIcon(posx, posy, cell);
			
			curr_level->map[x][y].pos.left = posx;
			curr_level->map[x][y].pos.top = posy;
			curr_level->map[x][y].pos.right = posx+CELL_WIDTH;
			curr_level->map[x][y].pos.bottom = posy+CELL_HEIGHT;
			
			if(show_vnum)
			{
				CString str;
			
				if(curr_level->map[x][y].room)
				{
					str.Format("%d", curr_level->map[x][y].room->vnum);
					CRect rc;
					rc.bottom = curr_level->map[x][y].pos.bottom - 15;
					rc.left = curr_level->map[x][y].pos.left;
					rc.right = curr_level->map[x][y].pos.right;
					rc.top = curr_level->map[x][y].pos.top;
					dc.Draw3dRect(rc, black, yellow);
				
				
					dc.SetTextColor(black);
				
					int points = rc.Height() * 7;
					CFont newFont;
					newFont.CreatePointFont(points, "Arial", &dc);
					CFont *defFont = dc.SelectObject(&newFont); 
				
					dc.DrawText(str, rc, DT_SINGLELINE | DT_LEFT); 
				
					dc.SelectObject(defFont); // Restore the font in the dc
				}
			}

			if(IsCurrentRoom(x, y, curr_room.z))
			{
				outline = curr_level->map[x][y].pos;

				dc.Draw3dRect(outline, yellow, yellow);
			}
		}
	}
	
	//dc.BitBlt(0,0,client.right,client.bottom,&MemDC,0,0,SRCCOPY);	//See Note 3
}

void DlgMapEdit::OnSize(UINT nType, int cx, int cy)
{
	if (this->IsWindowVisible())
	{
		CDialog::OnSize(nType, cx, cy);

		CRect rect, rect2, rect1;

		GetClientRect(&rect);

		room_tree.GetWindowRect(&rect2);

		ScreenToClient(rect2);

		rect1.top = rect.top + 24;
		rect1.left = rect.left;
		rect1.right = rect2.right;
		rect1.bottom = rect.bottom;

		room_tree.MoveWindow(rect1, TRUE);


		UPDATE_EASYSIZE;
		//split.SetRange(rect.left+200, rect.right-150);

		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDR_MAP_TOOLS);
	}
}

inline const HICON& DlgMapEdit::GetTerrainIcon(const int& ter) const
{
	return (ter < 0 || ter > SECT_MAX) ? terrain[SECT_MAX] : terrain[ter];
}

void DlgMapEdit::LoadTerrain(const int& ter)
{
	switch(ter)
	{
	case SECT_AIR:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_AIR);
		break;
	case SECT_PLANE_WATER:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_WATER_PLANE);
		break;
	case SECT_FIELD:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_FIELD);
		break;
	case SECT_HILLS:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_HILLS);
		break;
	case SECT_UNDERG_INSIDE:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_INSIDE);
		break;
	case SECT_INSIDE:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_INSIDE);
		break;
	case SECT_UNDERG_CITY:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_CITY);
		break;
	case SECT_CITY:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_CITY);
		break;		
	case SECT_MOUNTAIN:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_MOUNTAIN);
		break;
	case SECT_PLANE_ASTRAL:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_ASTRAL_PLANE);
		break;
	case SECT_ROAD:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_ROAD);
		break;
	case SECT_DESERT:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_DESERT);
		break;
	case SECT_UNDERWATER:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_UNDERWATER);
		break;
	case SECT_UNDERWATER_GROUND:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_UNDERWATER_GROUND);
		break;
	case SECT_UNDERG_WILD:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_WILD);
		break;
	case SECT_UNDERG_NOGROUND:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_NOGROUND);
		break;
	case SECT_UNDERG_IMPASSABLE:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_NOPASS);
		break;
	case SECT_UNDERG_OCEAN:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_OCEAN);
		break;
	case SECT_PLANE_ETHEREAL:	
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_PLANE_ETHEREAL);
		break;
	case SECT_PLANE_EARTH:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_PLANE_EARTH);
		break;
	case SECT_PLANE_AIR:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_PLANE_AIR);
		break;
	case SECT_FOREST:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_FOREST);
		break;
	case SECT_UNDERG_WATER:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_WATER);
		break;
	case SECT_WATER_SWIM:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_WATER);
		break;
	case SECT_UNDERG_WATER_NOSWIM:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_U_WATER_NOSWIM);
		break;
	case SECT_WATER_NOSWIM:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_WATER_NOSWIM);
		break;
	case SECT_PLANE_FIRE:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_FIRE_PLANE);
		break;
	case SECT_SWAMP:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_SWAMP);
		break;
	case SECT_OCEAN:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_OCEAN);
		break;
	case SECT_ARCTIC:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_ARTIC);
		break;
	case SECT_MAX:
		terrain[ter] = AfxGetApp()->LoadIcon(IDI_ROOM_BASE);
		break;
	}
}

RoomPos DlgMapEdit::SelectRoom(const CPoint& point)
{
	CRect outline;
	CDC *dc = GetDC();
	RoomPos room;
	
	room = GetCell(point);
	
	if(room.x < 0 || room.x > curr_level->x)
	{
		room.x = 0; room.y = 0; room.z = 0;
		return room;
	}

	if(room.y < 0 || room.x > curr_level->y)
	{
		room.x = 0; room.y = 0; room.z = 0;
		return room;
	}

	if(curr_level->map[room.x][room.y].terrain != -1)
	{
		outline.left	= curr_level->map[curr_room.x][curr_room.y].pos.left;
		outline.right	= curr_level->map[curr_room.x][curr_room.y].pos.right;
		outline.top		= curr_level->map[curr_room.x][curr_room.y].pos.top;
		outline.bottom	= curr_level->map[curr_room.x][curr_room.y].pos.bottom;
	
		dc->Draw3dRect(outline, black, black);

		outline.left	= curr_level->map[room.x][room.y].pos.left;
		outline.right	= curr_level->map[room.x][room.y].pos.right;
		outline.top		= curr_level->map[room.x][room.y].pos.top;
		outline.bottom	= curr_level->map[room.x][room.y].pos.bottom;
	
		dc->Draw3dRect(outline, yellow, yellow);

		if(curr_level && curr_level->map[room.x][room.y].room)
		{
			par->in_room = curr_level->map[room.x][room.y].room;
			par->ShowRoom();
		}
	}
	else 
		room = curr_room;

	return room;
}

void DlgMapEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	CString str;
	int x,y;

	curr_room = SelectRoom(point);
	
	x = curr_room.x;
	y = curr_room.y;

	if(curr_level->map[x][y].terrain != -1)
	{		
		if(curr_level->map[x][y].room)
		{
			par->OnEditRoom(curr_level->map[x][y].room->vnum);
		}
	}				
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void DlgMapEdit::OnClose() 
{
	if(shut_down)
	{
		CDialog::OnCancel();
		CDialog::OnClose();
	}
	else 
		par->OnMap();
}

void DlgMapEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case SB_BOTTOM:
		SetScrollPos(SB_HORZ, X_SCROLL);
		break;
	case SB_LINEDOWN:
		SetScrollPos(SB_HORZ,GetScrollPos(SB_HORZ)+1);
		break;
	case SB_LINEUP:
		SetScrollPos(SB_HORZ,GetScrollPos(SB_HORZ)-1);
		break;
	case SB_PAGEDOWN:
		SetScrollPos(SB_HORZ,GetScrollPos(SB_HORZ)+H_CELLS);
		break;
	case SB_PAGEUP: 
		SetScrollPos(SB_HORZ,GetScrollPos(SB_HORZ)-H_CELLS);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:	
		SetScrollPos(SB_HORZ,nPos);
		break;
	case SB_TOP:
		SetScrollPos(SB_HORZ,0);
		break;
	}

	UpdateDisplay();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void DlgMapEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case SB_BOTTOM:
		SetScrollPos(SB_VERT, Y_SCROLL);
		break;
	case SB_LINEDOWN:
		SetScrollPos(SB_VERT,GetScrollPos(SB_VERT)+1);
		break;
	case SB_LINEUP:
		SetScrollPos(SB_VERT,GetScrollPos(SB_VERT)-1);
		break;
	case SB_PAGEDOWN:
		SetScrollPos(SB_VERT,GetScrollPos(SB_VERT)+V_CELLS);
		break;
	case SB_PAGEUP: 
		SetScrollPos(SB_VERT,GetScrollPos(SB_VERT)-V_CELLS);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:	
		SetScrollPos(SB_VERT,nPos);
		break;
	case SB_TOP:
		SetScrollPos(SB_VERT,0);
		break;
	}
	
	UpdateDisplay();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL DlgMapEdit::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

inline bool DlgMapEdit::IsCurrentRoom(const RoomPos &point)
{
	return 
		(point.x == curr_room.x && point.y == curr_room.y && point.z == curr_level->level) ? 
		true : false;
}

inline bool DlgMapEdit::IsCurrentRoom(const int& x, const int& y, const int& z)
{
	return 
		(x == curr_room.x && y == curr_room.y && z == curr_level->level) ? 
		true : false;
}

HTREEITEM DlgMapEdit::InsertItem(CString &title, HTREEITEM parent, void *data, int image)
{
	HTREEITEM ti;
	
	title = StripAnsiChars(title);

	ti = room_tree.InsertItem(TVIF_TEXT | TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM | 
	      TVIF_SELECTEDIMAGE | TVIF_STATE, title, image, image, 0, 0, NULL, parent, NULL);

	room_tree.SetItemData(ti, (DWORD)data);

	room_tree.RedrawWindow();

	return ti;  
}

void DlgMapEdit::UpdateDisplay()
{
	CRect rect, toolRect, roomRect;
	room_data *room;
	mob_index *mob;
	obj_index *obj;
	CString str;
	
	room_tree.DeleteAllItems();

	mob_parent = InsertItem(CString("People"),  NULL, NULL, 2);
	obj_parent = InsertItem(CString("Contents"),  NULL, NULL, 3);

	m_Tool.GetClientRect(toolRect);
	GetClientRect(rect);
	//room_tree.GetClientRect(roomRect);
	
	//rect.left = roomRect.right;
	rect.top += toolRect.bottom+3;
	
	InvalidateRect(rect);
	
	if((room = curr_level->map[curr_room.x][curr_room.y].room))
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			str.Format("%d - %s", mob->vnum, mob->GetShortName()); 
			mob->m_tRoom = InsertItem(str, mob_parent, mob, 2); 
		}

		for(obj = room->contents; obj; obj = obj->next)
		{
			str.Format("%d - %s", obj->vnum, obj->GetShortName()); 
			obj->m_tRoom = InsertItem(str, obj_parent, obj, 1); 
		}
	}	
}

void DlgMapEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	curr_room = SelectRoom(point);

	CDialog::OnLButtonDown(nFlags, point);
}

const RoomPos DlgMapEdit::GetCell(const CPoint& point) const
{
	int x, y;
	RoomPos cell;

	for(y = 0; y < curr_level->y; y++)
	{
		for(x = 0; x < curr_level->x; x++)
		{
			if(point.x >= curr_level->map[x][y].pos.left 
				&& point.x <= curr_level->map[x][y].pos.right)
			{
				if(point.y <= curr_level->map[x][y].pos.bottom 
					&& point.y >= curr_level->map[x][y].pos.top)
				{	
					cell.x = x;
					cell.y = y;
					cell.z = curr_level->level;

					break;
				}
			}
		}
	}
	
	return cell;
}

void DlgMapEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	CMenu *pop_up;
	RoomPos room;
	CPoint pos = point;
	CMenu *mobs;
	room_data *r;
	mob_index *mob;
	obj_index *obj, *tmp;
	int i;
	CString str, str2, str3;
	CMenu *objs;
//	CMenu *sub;
	
	ScreenToClient(&pos);

	room = GetCell(pos);
	
	if(room.x < 0 || room.x > MAX_X)
		return;
	if(room.y < 0 || room.y > MAX_Y)
		return;

	if(curr_level->map[room.x][room.y].terrain != -1)
	{
		menu.LoadMenu(IDR_MAP_MENU);
	
		pop_up = menu.GetSubMenu(0);
		
		if((r = curr_level->map[room.x][room.y].room))
		{
			i = 0;
			mobs = pop_up->GetSubMenu(4);
			objs = pop_up->GetSubMenu(5);

			for(mob = r->people; mob; mob = mob->next)
			{	
				str.Format("%d: %d - %s", i+1, mob->vnum, StripAnsiChars(mob->GetShortName()));

				if(mob->inventory)
				{
					int x = 0;
					for(tmp = mob->inventory; tmp; tmp = tmp->next)
					{
						str2.Format("%d: %d - %s", ++x, tmp->vnum, tmp->GetShortName());
						str3.Format("%s\\%s", str, str2);
					
						MenuFunctions::AddMenuItem(mobs->GetSafeHmenu(), str3, ID_INVPOPUP_EQUIP, tmp);
					}
					
					i++;
				}
				else
					MenuFunctions::AddMenuItem(mobs->GetSafeHmenu(), str, ID_MOBPOPUP_EDITMOB, mob);
			}

			i = 0;
			for(obj = r->contents; obj; obj = obj->next)
			{
				str.Format("%d: %d - %s", i+1, obj->vnum, StripAnsiChars(obj->GetShortName()));

				if(obj->contents)
				{
					int x = 0;
					for(tmp = obj->contents; tmp; tmp = tmp->next)
					{
						str2.Format("%d: %d - %s", ++x, tmp->vnum, tmp->GetShortName());
						str3.Format("%s\\%s", str, str2);
					
						MenuFunctions::AddMenuItem(objs->GetSafeHmenu(), str3, ID_INVPOPUP_EQUIP, tmp);
					}
					
					i++;
				}
				else
					MenuFunctions::AddMenuItem(objs->GetSafeHmenu(), str, ID_MOBPOPUP_EDITMOB, obj);
			}
		}
		
		pop_up->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
	}
}

BOOL DlgMapEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void DlgMapEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	curr_room = SelectRoom(point);

	CDialog::OnRButtonDown(nFlags, point);
}

BOOL DlgMapEdit::MenuSelect(UINT id)
{
	switch(id)
	{
	case ID_MAPMENU_DELETEROOM:
		par->DeleteRoom(curr_level->map[curr_room.x][curr_room.y].room->vnum);
		break;
	case ID_MAPMENU_EDITROOM:
		par->OnEditRoom(curr_level->map[curr_room.x][curr_room.y].room->vnum);
		break;
	case ID_MAPMENU_TERRAIN_INSIDE:
		ChangeTerrain(SECT_INSIDE);
		break;
	case ID_MAPMENU_TERRAIN_CITY:
		ChangeTerrain(SECT_CITY);
		break;
	case ID_MAPMENU_TERRAIN_FIELD:
		ChangeTerrain(SECT_FIELD);
		break;
	case ID_MAPMENU_TERRAIN_FOREST:
		ChangeTerrain(SECT_FOREST);
		break;
	case ID_MAPMENU_TERRAIN_HILLS:
		ChangeTerrain(SECT_HILLS);
		break;
	case ID_MAPMENU_TERRAIN_MOUNTAIN:
		ChangeTerrain(SECT_MOUNTAIN);
		break;
	case ID_MAPMENU_TERRAIN_WATERSWIM:
		ChangeTerrain(SECT_WATER_SWIM);
		break;
	case ID_MAPMENU_TERRAIN_WATERNOSWIM:
		ChangeTerrain(SECT_WATER_NOSWIM);
		break;
	case ID_MAPMENU_TERRAIN_AIR:
		ChangeTerrain(SECT_AIR);
		break;
	case ID_MAPMENU_TERRAIN_UNDERWATER:
		ChangeTerrain(SECT_UNDERWATER);
		break;
	case ID_MAPMENU_TERRAIN_UNDERWATERGROUND:
		ChangeTerrain(SECT_UNDERWATER_GROUND);
		break;
	case ID_MAPMENU_TERRAIN_FIREPLANE:
		ChangeTerrain(SECT_PLANE_FIRE);
		break;
	case ID_MAPMENU_TERRAIN_OCEAN:
		ChangeTerrain(SECT_OCEAN);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDWILD:
		ChangeTerrain(SECT_UNDERG_WILD);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDCITY:
		ChangeTerrain(SECT_UNDERG_CITY);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDINSIDE:
		ChangeTerrain(SECT_UNDERG_INSIDE);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDWATER:
		ChangeTerrain(SECT_UNDERG_WATER);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDNOSWIM:
		ChangeTerrain(SECT_UNDERG_WATER_NOSWIM);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDAIR:
		ChangeTerrain(SECT_UNDERG_NOGROUND);
		break;
	case ID_MAPMENU_TERRAIN_AIRPLANE:
		ChangeTerrain(SECT_PLANE_AIR);
		break;
	case ID_MAPMENU_TERRAIN_WATERPLANE:
		ChangeTerrain(SECT_PLANE_WATER);
		break;
	case ID_MAPMENU_TERRAIN_EARTHPLANE:
		ChangeTerrain(SECT_PLANE_EARTH);
		break;
	case ID_MAPMENU_TERRAIN_ETHEREALPLANE:
		ChangeTerrain(SECT_PLANE_ETHEREAL);
		break;
	case ID_MAPMENU_TERRAIN_ASTRALPLANE:
		ChangeTerrain(SECT_PLANE_ASTRAL);
		break;
	case ID_MAPMENU_TERRAIN_DESERT:
		ChangeTerrain(SECT_DESERT);
		break;
	case ID_MAPMENU_TERRAIN_ARCTIC:
		ChangeTerrain(SECT_ARCTIC);
		break;
	case ID_MAPMENU_TERRAIN_SWAMP:
		ChangeTerrain(SECT_SWAMP);
		break;
	case ID_MAPMENU_TERRAIN_ROAD:
		ChangeTerrain(SECT_ROAD);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDNOPASS:
		ChangeTerrain(SECT_UNDERG_IMPASSABLE);
		break;
	case ID_MAPMENU_TERRAIN_UNDERGROUNDOCEAN:
		ChangeTerrain(SECT_UNDERG_OCEAN);
		break;
	case ID_MAPMENU_MOBILES_ADDMOBILE:
		AddMob();
		break;
	case ID_MAPMENU_CONTENTS_ADDITEM:
		AddItem();
		break;
	}

	return TRUE;
}

void DlgMapEdit::AddMob()
{
	DlgEnterVnum dlg_vnum(this);
	mob_data *mob;
	int vnum;
	room_data *room;

	dlg_vnum.type = MOBILE;
	
	if(dlg_vnum.DoModal() == IDOK)
	{
		vnum = dlg_vnum.vnum;

		mob = GetMobByVnum(vnum);
		
		if((room = curr_level->map[curr_room.x][curr_room.y].room))
		{
			room->AddPerson(mob);
		}
	}
}

void DlgMapEdit::AddItem()
{
	DlgEnterVnum dlg_vnum(this);
	object_data *obj;
	int vnum;
	room_data *room;

	dlg_vnum.type = OBJECT;
	
	if(dlg_vnum.DoModal() == IDOK)
	{
		vnum = dlg_vnum.vnum;

		obj = GetObjByVnum(vnum);
		
		if((room = curr_level->map[curr_room.x][curr_room.y].room))
		{
			room->AddContent(obj);
		}
	}
}

void DlgMapEdit::ChangeTerrain(int sect)
{
	curr_level->map[curr_room.x][curr_room.y].room->sector_type = sect;
	curr_level->map[curr_room.x][curr_room.y].terrain = sect;

	UpdateDisplay();
}

BOOL DlgMapEdit::PreTranslateMessage(MSG* pMsg) 
{
	room_data *room;

	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_UP:
			if(curr_room.y - 1 > (Y_SCROLL-1)-(V_CELLS/2))
			{
				if(curr_level->map[curr_room.x][curr_room.y-1].terrain != -1)
					curr_room.y--;
			}
			else if((curr_room.y - 1) > -1)
			{
				if(curr_level->map[curr_room.x][curr_room.y-1].terrain != -1)
				{
					curr_room.y--;
				
					OnVScroll(SB_LINEUP, 0, NULL);	
				}
			}

			UpdateDisplay();
			
			break;
		case VK_DOWN:
			if(curr_room.y + 1 < (V_CELLS/2)+1)
			{
				if(curr_level->map[curr_room.x][curr_room.y+1].terrain != -1)
					curr_room.y++;
			}
			else if((curr_room.y + 1) < curr_level->y)
			{
				if(curr_level->map[curr_room.x][curr_room.y+1].terrain != -1)
				{
					curr_room.y++;
				
					OnVScroll(SB_LINEDOWN, 0, NULL);	
				}
			}
		
			UpdateDisplay();
			
			break;
		case VK_LEFT:
			if(curr_room.x - 1 > (X_SCROLL-1)-(H_CELLS/2))
			{
				if(curr_level->map[curr_room.x-1][curr_room.y].terrain != -1)
					curr_room.x--;
			}
			else if((curr_room.x - 1) > -1)
			{
				if(curr_level->map[curr_room.x-1][curr_room.y].terrain != -1)
				{
					curr_room.x--;
				
					OnHScroll(SB_LINEUP, 0, NULL);	
				}
			}
			
			UpdateDisplay();
			
			break;
		case VK_RIGHT:
			if(curr_room.x + 1 < (H_CELLS/2)+1)
			{
				if(curr_level->map[curr_room.x+1][curr_room.y].terrain != -1)
					curr_room.x++;
			}
			else if((curr_room.x + 1) < curr_level->x)
			{
				if(curr_level->map[curr_room.x+1][curr_room.y].terrain != -1)
				{
					curr_room.x++;
				
					OnHScroll(SB_LINEDOWN, 0, NULL);
				}
			}
			
			UpdateDisplay();
			
			break;
		case VK_RETURN:
			par->OnEditRoom(curr_level->map[curr_room.x][curr_room.y].room->vnum);
			break;
		}
		
		room = curr_level->map[curr_room.x][curr_room.y].room;
			
		if(room != par->in_room)
		{
			par->in_room = room;
			par->ShowRoom();
		}
		
		return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void DlgMapEdit::Center()
{
	OnHScroll(SB_THUMBPOSITION, (X_SCROLL/2)-(H_CELLS/2), NULL);
	OnVScroll(SB_THUMBPOSITION, (Y_SCROLL/2)-(V_CELLS/2), NULL);

	curr_room.x = MID_X;
	curr_room.y = MID_Y;
}

void DlgMapEdit::ChangeLevel(int dir)
{
	if(dir == DIR_UP)
	{
		if(curr_level->above)
		{
			curr_level = curr_level->above;
			//curr_room.z++;
		}
	}
	else if(dir == DIR_DOWN)
	{
		if(curr_level->below)
		{
			curr_level = curr_level->below;
			//curr_room.z--;
		}
	}

	DrawArea();
}

BOOL DlgMapEdit::ChangeLevel(UINT id)
{
	if(id == ID_LEVEL_UP)
	{
		ChangeLevel(DIR_UP);
	}
	else if(id == ID_LEVEL_DOWN)
	{
		ChangeLevel(DIR_DOWN);
	}

	return false;
}

void DlgMapEdit::ClearArea()
{
	room_data *room;
	int y, x;

	for(room = room_data::room_list; room; room = room->next)
	{
		room->painted = false;
	}

	for(y = 0; y < curr_level->y; y++)
	{
		for(x = 0; x < curr_level->x; x++)
		{
			curr_level->map[x][y].terrain = -1;
			curr_level->map[x][y].room = NULL;
			curr_level->map[x][y].painted = false;
			curr_level->painted = false;
		}
	}

	/*int y, x;
	MapLevel *level, *next;

	x = ground_level->x;
	y = ground_level->y;

	for(level = ground_level->above; level; level = next)
	{
		next = level->above;
		delete level;
	}

	for(level = ground_level->below; level; level = next)
	{
		next = level->below;
		delete level;
	}

	if(ground_level)
		delete ground_level;

	ground_level = new MapLevel(x, y);

	curr_level = ground_level;
	*/
}
			
void DlgMapEdit::DrawRoom(room_data *room, int x, int y, MapLevel *level)
{
	int index;
	room_data *tmp;

	if(room)
	{
		if(x > -1 && x < curr_level->x && y > -1 && y < curr_level->y)
		{
			level->map[x][y].room = room;
			level->map[x][y].terrain = room->sector_type;
		
			if(room == par->in_room)
			{
				curr_room.x = x;
				curr_room.y = y;
			}
		}
	
		room->painted = true;
			
		for(index = 0; index < MAX_DIR; index++)
		{
			if(room->exit[index])
			{
				tmp = GetRoomByVnum(room->exit[index]->vnum);

				if(tmp && !tmp->painted)
				{
					switch(index)
					{
					case DIR_NORTH:
						DrawRoom(tmp, x, y-1,	level);
						break;
					case DIR_SOUTH:
						DrawRoom(tmp, x, y+1,	level);
						break;
					case DIR_WEST:
						DrawRoom(tmp, x-1, y,	level);
						break;
					case DIR_EAST:
						DrawRoom(tmp, x+1, y,	level);
						break;
					case DIR_NORTHWEST:
						DrawRoom(tmp, x-1, y-1, level);
						break;
					case DIR_NORTHEAST:
						DrawRoom(tmp, x+1, y-1, level);
						break;
					case DIR_SOUTHWEST:
						DrawRoom(tmp, x-1, y+1, level);
						break;
					case DIR_SOUTHEAST:
						DrawRoom(tmp, x+1, y+1, level);
						break;
					case DIR_UP:
						if(level->above == NULL)
						{
							level->above = new MapLevel(curr_level->x, curr_level->y);
							level->above->below = level;
							level->above->level = level->level+1;
						}

						level = level->above;

						DrawRoom(tmp, x, y, level);
						break;
					case DIR_DOWN:
						if(level->below == NULL)
						{
							level->below = new MapLevel(curr_level->x, curr_level->y);
							level->below->above = level;
							level->below->level = level->level-1;
						}

						level = level->below;

						DrawRoom(tmp, x, y, level);
						break;
					}
				}
			}
		}
	}
}

void DlgMapEdit::DrawArea()
{
	room_data *room;	

	ClearArea();

	DrawRoom(room_data::room_list, MID_X, MID_Y, ground_level);

	//Draw Unpainted unconnected rooms!!!!
	for(room = room_data::room_list; room; room = room->next)
	{
		if(!room->painted)
		{
			//paint it somewhere
			//DrawRoom(room, ?, ?, ?);
		}
	}
		
	//nterOnCurrRoom();
	
	UpdateDisplay();		
}

void DlgMapEdit::CenterOnCurrRoom()
{
	int x, y;

	x = curr_room.x - H_CELLS/2;
	y = curr_room.y - V_CELLS/2;

	if(y > curr_level->y-1)
		y = curr_level->y-1;
	else if(y < 0)
		y = 0;
	
	if(x > curr_level->x-1)
		x = curr_level->x-1;
	else if(x < 0)
		x = 0;

	SetScrollPos(SB_VERT, y);
	SetScrollPos(SB_HORZ, x);

	if(curr_room.z != curr_level->level)
	{
		MapLevel *tmp;
		
		if(curr_room.z > 0)
		{
			for(tmp = ground_level; tmp; tmp = tmp->above)
			{
				if(curr_room.z == tmp->level)
				{
					curr_level = tmp;
				}
			}
		}
		else if(curr_room.z < 0)
		{
			for(tmp = ground_level; tmp; tmp = tmp->below)
			{
				if(curr_room.z == tmp->level)
				{
					curr_level = tmp;
				}
			}
		}
		else 
		{
			curr_level = ground_level;
		}

	}
}

void DlgMapEdit::MoveRoom(int dir)
{
	switch(dir)
	{
	case DIR_NORTH:
		curr_room.y--;
		break;
	case DIR_SOUTH:
		curr_room.y++;
		break;
	case DIR_EAST:
		curr_room.x++;
		break;
	case DIR_WEST:
		curr_room.x--;
		break;
	case DIR_NORTHWEST:
		curr_room.y--;
		curr_room.x--;
		break;
	case DIR_NORTHEAST:
		curr_room.y--;
		curr_room.x++;
		break;
	case DIR_SOUTHWEST:
		curr_room.y++;
		curr_room.x--;
		break;
	case DIR_SOUTHEAST:
		curr_room.y++;
		curr_room.x++;
		break;
	case DIR_UP:
		if(curr_level->above)
		{
			curr_level = curr_level->above;
			curr_room.z = curr_level->level;
		}
		else if(IS_SET(/*((CWinDEDlg*)GetParent())->*/editor_flags, WALK_CREATE))
		{
			curr_room.z++;
		}
		break;
	case DIR_DOWN:
		if(curr_level->below)
		{
			curr_level = curr_level->below;
			curr_room.z = curr_level->level;
		}
		else if(IS_SET(/*((CWinDEDlg*)GetParent())->*/editor_flags, WALK_CREATE))
		{
			curr_room.z--;
		}
		break;
	}
}

void DlgMapEdit::ShowVnum()
{
	CRect rect;

	show_vnum = !show_vnum;
	this->GetClientRect(&rect);
	InvalidateRect(rect, true);
}

void DlgMapEdit::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	//split.SetRange(frameRect.left+200, frameRect.right-150);
    
	EASYSIZE_MINSIZE(400,400,fwSide,pRect);	
	
}

void DlgMapEdit::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
/*	CString str;
	mob_index *mob;
	CDialog::OnMenuSelect(nItemID, nFlags, hSysMenu);
	MENUITEMINFO menuItemInfo;

	memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));
	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_DATA;
		
	::GetMenuItemInfo(hSysMenu, nItemID, TRUE, &menuItemInfo);

	switch(nItemID)
	{	
	case ID_MOBPOPUP_EDITMOB:
		mob = (mob_index*)menuItemInfo.dwItemData;
		//str.Format("%d EDITMOB", mob->vnum);
		MessageBox(str);
		break;
	case ID_MOBPOPUP_REMOVEFROMROOM:
		break;
	case ID_INVPOPUP_EQUIP:
		break;
	case ID_INVPOPUP_EDITOBJECT:
		break;
	case ID_INVPOPUP_REMOVEFROMMOB:
		break;
	}
*/
}

void DlgMapEdit::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnSysCommand(nID, lParam);
}
