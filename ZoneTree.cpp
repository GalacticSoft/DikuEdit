// ZoneTree.cpp : implementation file
//
#include "stdafx.h"
#include "WinDE.h"
#include "ZoneTree.h"
#include "DlgEditFriends.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoneTree

CZoneTree::CZoneTree()
{
	m_pDragImage = NULL;
	m_bLDragging = FALSE; 
	cursor_arr	= ::LoadCursor(NULL, IDC_ARROW);
	cursor_no	= ::LoadCursor(NULL, IDC_NO) ;
}

CZoneTree::~CZoneTree()
{

}

BEGIN_MESSAGE_MAP(CZoneTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CZoneTree)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_COMMAND_EX(ID_TREE_EDIT_AREA,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_SAVE_AREA,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_NEW_AREA,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_OPEN_AREA,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_ROOM,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_ROOM,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_OBJ,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_OBJ,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_MOB,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_MOB,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_OINDEX,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_MINDEX,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_OINDEX,	MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_MINDEX,	MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_MOBS,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_OBJS,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_DELETE_ROOMS,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_ROOM_GRID,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_REMOVE_PEOPLE,	MenuSelect)
	ON_COMMAND_EX(ID_TREE_REMOVE_CONTENTS,	MenuSelect)
	ON_COMMAND_EX(ID_TREE_NEW_ROOM,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_NEW_OBJ,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_NEW_MOB,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_EQUIP,		MenuSelect)
	ON_COMMAND_EX(ID_TREE_FRIENDS,			MenuSelect)
	ON_COMMAND_EX(ID_TREE_GOTO,				MenuSelect)
	ON_COMMAND_EX(ID_TREE_EDIT_CONTENTS,    MenuSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoneTree message handlers



void CZoneTree::OnRButtonDblClk(UINT nFlags, CPoint point) 
{	
	CTreeCtrl::OnRButtonDblClk(nFlags, point);
}

void CZoneTree::OnRButtonDown(UINT nFlags, CPoint point) 
{		
	UINT flags = 0; 
	HTREEITEM hItem = HitTest(point, &flags); 
	SelectItem(hItem);
	SetFocus();
}

void CZoneTree::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	HTREEITEM it;
	int i;

	it = GetSelectedItem();
	GetItemImage(it, i, i);
	
	switch(i) {
		case AREA_DATA: {
			((CWinDEDlg*)GetParent())->OnAreaProperties();
			break;
		}
		case MOB_DATA: {
			mob_data *mob;
			mob = (mob_data*)GetItemData(it);
			((CWinDEDlg*)GetParent())->OnEditMob(mob->vnum);
			break;
		}
		case OBJECT_DATA:{
			object_data *obj;
			obj = (object_data*)GetItemData(it);
			((CWinDEDlg*)GetParent())->OnEditObject(obj->vnum);
			break;
		}
		case ROOM_DATA: {
			room_data *room;
			room = (room_data*)GetItemData(it);
			
			((CWinDEDlg*)GetParent())->OnEditRoom(room->vnum);
			
			if(((CWinDEDlg*)GetParent())->in_room != room)
			{
				((CWinDEDlg*)GetParent())->in_room = room;
				((CWinDEDlg*)GetParent())->ShowRoom();
			}
			break;
		}
		case MOB_INDEX: {
			mob_index *m_index;
			m_index = (mob_index*)GetItemData(it);
			((CWinDEDlg*)GetParent())->OnEditMob(m_index->vnum);
			break;
		}
		case OBJ_INDEX:{
			obj_index *o_index;
			o_index = (obj_index*)GetItemData(it);
			((CWinDEDlg*)GetParent())->OnEditObject(o_index->vnum);
			break;
		}
	
	}
	
	GetParent()->SetFocus();
}

void CZoneTree::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPoint pos;
	int i;
	HTREEITEM it;
	HTREEITEM contents;
	HTREEITEM parent;
	CWinDEDlg *dlg = (CWinDEDlg*)GetParent();

	GetCursorPos(&pos);

	if(nChar == VK_RETURN)    
	{       
		GetParent()->SetFocus();
		OnLButtonDblClk(nFlags, pos);
	}    
	else if(nChar == VK_DELETE)    
	{       
		it = GetSelectedItem();
		GetItemImage(it, i, i);
		switch(i) {
			case AREA_DATA:
				break;
			case ROOM_DATA: {
				room_data *room;
				room = (room_data*)GetItemData(it);
				dlg->DeleteRoom(room->vnum);
				break;
			}
			case MOB_DATA: {
				mob_data *mob;
				mob = (mob_data*)GetItemData(it);
				dlg->DeleteMob(mob->vnum);
				break;
			}
			case OBJECT_DATA: {
				object_data *obj;
				obj = (object_data*)GetItemData(it);
				dlg->DeleteObj(obj->vnum);
				break;
			}
			case MOB_INDEX: {
				mob_index *m_index;
				room_data *room;
				
				contents = GetParentItem(it);
				parent = GetParentItem(contents);
				
				m_index = (mob_index*)GetItemData(it);
				room = (room_data*)GetItemData(parent);
				
				room->RemovePerson(m_index);
				dlg->RemoveItem(m_index->m_tThis);

				delete m_index;
				break;
			}
			case OBJ_INDEX: {
				obj_index *o_index;
				o_index = (obj_index*)GetItemData(it);
				
				//get contents indexs parent item wich is the actual object
				contents = GetParentItem(it);
				parent = GetParentItem(contents);
				
				GetItemImage(parent, i, i);
				
				switch(i) {
					case OBJ_INDEX: {
						obj_index *o_parent;
						o_parent = (obj_index*)GetItemData(parent);
						o_parent->RemoveContent(&o_index);
						break;
					}
					case MOB_INDEX:
						break;
					case ROOM_DATA:
						room_data *room;
						room = (room_data*)GetItemData(parent);
						room->RemoveContent(o_index);
						break;
					case OBJECT_DATA: {
						object_data *obj_parent;
						obj_parent = (object_data*)GetItemData(parent);
						obj_parent->RemoveContent(o_index);
						break;
					}
					case MOB_DATA:
						break;
				}

				if(o_index)
					o_index->RemoveFromList();
				
				dlg->RemoveItem(it);
				break;
			}
		}
	}
}

void CZoneTree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	int i;
	*pResult = 0;
	
	// So user cant drag root node
	if (GetParentItem(pNMTreeView->itemNew.hItem) == NULL) return; 

	// Item user started dragging ...
	m_hitemDrag = pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;
	
	GetItemImage(m_hitemDrag, i, i);
	//don't drag root items!
	switch(i){
		case CONTENTS: 
		case PEOPLE: 
		case OBJ_PARENT:
		case MOB_PARENT: 
		case ROOM_PARENT: 
		case AREA_DATA: 
		case ROOM_DATA:
			return;
	}
    
	m_pDragImage = CreateDragImage(m_hitemDrag);  // get the image list for dragging
	// CreateDragImage() returns NULL if no image list
	// associated with the tree view control
	if( !m_pDragImage )
		return;

	m_bLDragging = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-15,-15));
	
	POINT pt = pNMTreeView->ptDrag;
	
	ClientToScreen( &pt );
	
	m_pDragImage->DragEnter(NULL, pt);
	
	SetCapture();
}

void CZoneTree::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM	hitem;
	UINT		flags;
	HCURSOR     cur;
	POINT pt = point;
	int x , y;

	if(m_bLDragging) 
	{
		ClientToScreen( &pt );
		CImageList::DragMove(pt);
		
		if((hitem = HitTest(point, &flags)) != NULL) 
		{
			CImageList::DragShowNolock(FALSE);
			
			if(GetParentItem(hitem) == NULL) 
			{
				::SetCursor(cursor_no);
				SelectDropTarget(NULL);
			} 
			else 
			{
				GetItemImage(m_hitemDrag, x, x);
				GetItemImage(hitem, y, y);
				
				switch(x) 
				{
					case MOB_DATA: 
					case MOB_INDEX:
					{
						switch(y) 
						{
							case MOB_INDEX:
							case OBJ_INDEX:
							case OBJECT_DATA:
							case MOB_DATA:
							case ROOM_PARENT:
							case CONTENTS:
							case OBJ_PARENT:
							case MOB_PARENT:
								cur = cursor_no;
								break;
							default:
								cur = cursor_arr;
								break;
						}
						
					}
					break;
					case OBJECT_DATA:
					{
						switch(y) 
						{
							case PEOPLE:
							case OBJ_PARENT:
							case MOB_PARENT:
							case ROOM_PARENT:
							case MOB_INDEX:
							case MOB_DATA:
								cur = cursor_no;
								break;
							default:
								cur = cursor_arr;
								break;
						}
						
					}
					break;
					case OBJ_INDEX: 
					{
						switch(y) 
						{
							case PEOPLE:
							case OBJ_PARENT:
							case MOB_PARENT:
							case ROOM_PARENT:
							case MOB_INDEX:
							case MOB_DATA:
								cur = cursor_no;
								break;
							default:
								cur = cursor_arr;
								break;
						}
						
					}
					break;
				}
			}
			
			if(cur == cursor_arr && cursor_arr != ::GetCursor()) 
			{
				::SetCursor(cursor_arr);
				SelectDropTarget(hitem);
			} 
			else if(cur == cursor_no && cursor_no != ::GetCursor()) 
			{
				::SetCursor(cursor_no);
				SelectDropTarget(NULL);
			}

			m_hitemDrop = hitem;
			CImageList::DragShowNolock(TRUE);
		}
		
		CPoint pos;
		CRect rect;
		
		GetWindowRect(&rect);
		GetCursorPos(&pos);
		
		if(pos.y > rect.bottom)
			SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
		else if(pos.y < rect.top)
			SendMessage(WM_VSCROLL, SB_LINEUP, 0);
	} 
	else 
	{
		::SetCursor(cursor_arr);
	}

	CTreeCtrl::OnMouseMove(nFlags, point);	
}

void CZoneTree::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int i, x;

	CTreeCtrl::OnLButtonUp(nFlags, point);

	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		
		ReleaseCapture();
		GetItemImage(m_hitemDrag, i, i);

		if(m_pDragImage != NULL) 
		{ 
			delete m_pDragImage; 
			m_pDragImage = NULL; 
		} 

		// Remove drop target highlighting
		SelectDropTarget(NULL);

		if( m_hitemDrag == m_hitemDrop )
			return;

		HTREEITEM	hitem;
		
		// Make sure pt is over some item
		if (((hitem = HitTest(point, &nFlags)) == NULL)  ) 
			return;
		
		// If Drag item is an ancestor of Drop item then return
		HTREEITEM htiParent = m_hitemDrop;
		
		while( (htiParent = GetParentItem( htiParent )) != NULL )
		{
			if( htiParent == m_hitemDrag ) 
				return;
		}
		
		GetItemImage(m_hitemDrag, i, i);
		GetItemImage(m_hitemDrop, x, x);
		
		switch(i) 
		{
			case OBJ_INDEX: 
			case OBJECT_DATA:
			{
				switch(x) 
				{
					case ROOM_DATA:
					{
						room_data *room;
						room = (room_data*)GetItemData(m_hitemDrop);
						m_hitemDrop = room->m_tContents;
						break;
					}
					case CONTENTS:
						break;
					case OBJ_INDEX: 
					{
						obj_index *o_ind;
						
						o_ind = (obj_index*)GetItemData(m_hitemDrop);
						
						if(o_ind->IsContainer()) 
						{
							if(!o_ind->m_tContents) 
								o_ind->m_tContents = InsertItem("Contents", CONTENTS, CONTENTS, o_ind->m_tThis);
						
							m_hitemDrop = o_ind->m_tContents;
						} 
						else 
							return;
					}
					break;
					default: 
						return;
				}
			}
			break;
			case MOB_INDEX:
			case MOB_DATA: 
			{
				switch(x) 
				{
					case ROOM_DATA: 
					{
						room_data *room;
						
						room = (room_data*)GetItemData(m_hitemDrop);
						
						m_hitemDrop = room->m_tPeople;
						break;
					}
					case PEOPLE:
						break;
					default:
						return;
				}
				break;
			}
		}	

		Expand( m_hitemDrop, TVE_EXPAND );

		HTREEITEM htiNew = MoveChildItem( m_hitemDrag, m_hitemDrop, TVI_LAST );
		
		if(i == OBJ_INDEX || i == MOB_INDEX)
			DeleteItem(m_hitemDrag);
		
		SelectItem( htiNew );
	}
}

HTREEITEM CZoneTree::MoveChildItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
    CString sText;
	int i;

    // get information of the source item
    tvstruct.item.hItem = hItem;
    tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    GetItem(&tvstruct.item);  
    sText = GetItemText( hItem );
        
    tvstruct.item.cchTextMax = sText.GetLength();
    tvstruct.item.pszText = sText.LockBuffer();

    //insert the item at proper location
    tvstruct.hParent = htiNewParent;
    tvstruct.hInsertAfter = htiAfter;
    tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    hNewItem = InsertItem(&tvstruct);
    sText.ReleaseBuffer();
	
	GetItemImage(hNewItem, i, i);

	switch(i) {
	case OBJECT_DATA:
		ConvertObjToIndex(hItem, hNewItem, htiNewParent);
		break;
	case OBJ_INDEX:
		CopyObjIndex(hItem, hNewItem, htiNewParent);
		break;
	case MOB_DATA:
		ConvertMobToIndex(hItem, hNewItem, htiNewParent);
		break;
	case MOB_INDEX:
		CopyMobIndex(hItem, hNewItem, htiNewParent);
		break;
	}

    SetItemState(hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	HTREEITEM hItemChild = GetChildItem(hItem);
	
	while (hItemChild != NULL)
	{
		HTREEITEM hItemNextChild = GetNextSiblingItem(hItemChild);
		MoveChildItem(hItemChild, hNewItem, TVI_LAST);
		hItemChild = hItemNextChild;
	}
	
    return hNewItem;
}

void CZoneTree::ConvertMobToIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent)
{
	int x;
	HTREEITEM par;

	GetItemImage(htiNewParent, x, x);

	switch(x) {
	case PEOPLE:
		room_data *room;
		mob_index *mob;
					
		par = GetParentItem(htiNewParent);
		room = (room_data*)GetItemData(par);
					
		if(room) {
			mob = room->AddPerson((mob_data*)GetItemData(hItem));
			mob->m_tThis = hNewItem;
		}
					
		SetItemImage(hNewItem, MOB_INDEX, MOB_INDEX);
		SetItemData(hNewItem, (DWORD)mob);
		break;
	}
}

void CZoneTree::CopyMobIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent)
{
	int x;
	HTREEITEM it, par;
	
	GetItemImage(htiNewParent, x, x);
	
	switch(x){
	case PEOPLE:
		room_data *room;
		mob_index *mob;
			
		par = GetParentItem(hItem);
		it = GetParentItem(par);

		room = (room_data*)GetItemData(it);
		mob = (mob_index*)GetItemData(hItem);
					
		room->RemovePerson(mob);

		par = GetParentItem(htiNewParent);
		room = (room_data*)GetItemData(par);
					
		room->AddPerson(mob);
		mob->m_tThis = hNewItem;

		SetItemData(hNewItem, (DWORD)mob);
		DeleteItem(hItem);
		break;
	}	
}

void CZoneTree::ConvertObjToIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent)
{
	HTREEITEM par;
	int x, y;
	obj_index *o_index;
	
	par = GetParentItem(htiNewParent);
	
	GetItemImage(htiNewParent, x, x);
	
	switch(x) 
	{
	case CONTENTS:
		GetItemImage(par, y, y);
		switch(y) 
		{
		case OBJ_INDEX:
			obj_index *o_parent;

			o_parent = (obj_index*)GetItemData(par);

			if(o_parent) 
			{
				o_index = o_parent->AddContent((object_data*)GetItemData(hItem));
				o_index->m_tThis = hNewItem;
			}

			SetItemImage(hNewItem, OBJ_INDEX, OBJ_INDEX);
			SetItemData(hNewItem, (DWORD)o_index);
			
			break;
		case MOB_INDEX:
			break;
		case ROOM_DATA:
			room_data *room;
							
			room = (room_data*)GetItemData(par);

			if(room) {
				o_index = room->AddContent((object_data*)GetItemData(hItem));
				o_index->m_tThis = hNewItem;
			}

			SetItemImage(hNewItem, OBJ_INDEX, OBJ_INDEX);
			SetItemData(hNewItem, (DWORD)o_index);
			
			break;
		}
	/*	case OBJECT_DATA:
			
			GetItemImage(htiNewParent, y, y);
			switch(y)
			{
			case OBJ_INDEX:
				obj_index *o_parent;

				o_parent = (obj_index*)GetItemData(htiNewParent);

				if(o_parent) 
				{
					o_index = o_parent->AddContent((object_data*)GetItemData(hItem));
					o_index->m_tThis = hNewItem;
				}

				SetItemImage(hNewItem, OBJ_INDEX, OBJ_INDEX);
				SetItemData(hNewItem, (DWORD)o_index);
				break;
			}
			
			break;*/
	}
}

void CZoneTree::CopyObjIndex(HTREEITEM &hItem, HTREEITEM &hNewItem, HTREEITEM &htiNewParent)
{
	HTREEITEM pparent, content;
	int x, y;
	obj_index *index;
	content = GetParentItem(hItem);
	pparent = GetParentItem(content);

	GetItemImage(pparent, x, x);
	
	index = (obj_index*)GetItemData(hItem);
	
	//copy from x
	switch(x) {
	case OBJECT_DATA:
		object_data *obj;
		
		obj = (object_data*)GetItemData(pparent);
		
		obj->RemoveContent(index);

		pparent = GetParentItem(htiNewParent);

		GetItemImage(pparent, y, y);
		break;
	case OBJ_INDEX:
		break;
	case MOB_INDEX:
		break;
	case ROOM_DATA:
		room_data *room;
		
		room = (room_data*)GetItemData(pparent);
		
		room->RemoveContent(index);

		pparent = GetParentItem(htiNewParent);
		
		GetItemImage(pparent, y, y);
	}
	
	//copy to y
	switch(y) {
	case ROOM_DATA:
		room_data *room;
		room = (room_data*)GetItemData(pparent);
				
		room->AddContent(index);
		index->m_tThis = hNewItem;
				
		SetItemData(hNewItem, (DWORD)index);	
		GetItemImage(content, x, x);
		
		if(x !=CONTENTS)
			DeleteItem(hItem);
		break;
	case OBJ_INDEX:
	case MOB_INDEX:
		break;
	}
}

int CZoneTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	CBitmap bm;
	CImageList iml;

	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	iml.Create(IDB_TREE_AREA, 16, 0, RGB(255, 0, 0));
	
	bm.LoadBitmap(IDB_TREE_ROOM);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_MOB);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_OBJ);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_MOB_INDEX);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_OBJ_INDEX);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_PEOPLE);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_CONTENTS);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_ROOMS);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_OBJS);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	bm.LoadBitmap(IDB_TREE_MOBS);
	iml.Add(&bm, RGB(255, 0, 0));
	bm.DeleteObject();

	SetImageList(&iml, TVSIL_NORMAL);
	
	iml.Detach();
	
	return 0;
}

void CZoneTree::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{	
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CZoneTree::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CPoint pos(-1, -1);     
	CMenu menu; 
	int i;
	HTREEITEM hItem;
	HTREEITEM hParent;
	
	GetCursorPos(&pos);    
	ScreenToClient(&pos);     
	
	hItem = GetSelectedItem();
	
	SetFocus();

	if (hItem != NULL)    {       
		GetItemImage(hItem, i, i);

		menu.CreatePopupMenu();

		switch(i) {
			case AREA_DATA: {
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_AREA, "Edit Area");
				menu.AppendMenu(MF_STRING, ID_TREE_SAVE_AREA, "Save Area");
				menu.AppendMenu(MF_STRING, ID_TREE_NEW_AREA, "New Area");
				menu.AppendMenu(MF_STRING, ID_TREE_OPEN_AREA, "Open Area");
				break;
			}
			case ROOM_DATA: {
				menu.AppendMenu(MF_STRING, ID_TREE_GOTO,		"Goto");
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_ROOM, "Edit Room");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_ROOM, "Delete Room");
				break;
			}
			case MOB_DATA: {
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_MOB, "Edit Mobile");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_MOB, "Delete Mobile");
				break;
			}
			case MOB_INDEX: {
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_MINDEX,   "Edit Mobile");
				menu.AppendMenu(MF_STRING, ID_TREE_FRIENDS,  "Edit Friends");
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_EQUIP,    "Edit Equipment");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_MINDEX, "Remove From Room");
				break;
			}
			case OBJECT_DATA: {
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_OBJ, "Edit Object");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_OBJ, "Delete Object");
				break;
			}
			case OBJ_INDEX:{
				menu.AppendMenu(MF_STRING, ID_TREE_EDIT_OINDEX, "Edit Object");
				obj_index *obj;
				
				obj = (obj_index*)GetItemData(hItem);
				
				if(obj)
				{
					if(obj->IsContainer())
						menu.AppendMenu(MF_STRING, ID_TREE_EDIT_CONTENTS, "Edit Contents");
				}

				hParent = GetParentItem(hItem);

				GetItemImage(hParent, i, i);
				if(i == CONTENTS) {
					hParent = GetParentItem(hParent);
					GetItemImage(hParent, i, i);
				}

				switch(i) {
				case OBJ_INDEX:
					menu.AppendMenu(MF_STRING, ID_TREE_DELETE_OINDEX, "Remove From Object");
					break;
				case ROOM_DATA:
					menu.AppendMenu(MF_STRING, ID_TREE_DELETE_OINDEX, "Remove From Room");
					break;
				}
				
				break;
			}
			case OBJ_PARENT: {
				menu.AppendMenu(MF_STRING, ID_TREE_NEW_OBJ, "New Object");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_OBJS, "Delete All Objects");
				break;
			}
			case MOB_PARENT: {
				menu.AppendMenu(MF_STRING, ID_TREE_NEW_MOB, "New Mobile");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_MOBS, "Delete All Mobiles");
				break;
			}
			case ROOM_PARENT: {
				menu.AppendMenu(MF_STRING, ID_TREE_NEW_ROOM, "New Room");
				menu.AppendMenu(MF_STRING, ID_TREE_ROOM_GRID, "Create Room Grid");
				menu.AppendMenu(MF_STRING, ID_TREE_DELETE_ROOMS, "Delete All Rooms");
				break;
			}
			case PEOPLE: {
				menu.AppendMenu(MF_STRING, ID_TREE_REMOVE_PEOPLE, "Remove All Occupants");
				break;
			}
			case CONTENTS: {
				menu.AppendMenu(MF_STRING, ID_TREE_REMOVE_CONTENTS, "Remove All Contents");
				break;
			}
		}
  		       
		GetCursorPos(&pos);        
		      
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, this);    
	}
}
BOOL CZoneTree::MenuSelect(UINT id)
{	
	HTREEITEM it, par;
	room_data *room;
	int index;
	CPoint pos;
	CWinDEDlg *parent = (CWinDEDlg*)GetParent();
	
	
	switch(id) {
	case ID_TREE_GOTO:
		par = GetSelectedItem();
		
		room = (room_data*)GetItemData(par);

		parent->in_room = room;

		parent->ShowRoom();
		break;
	case ID_TREE_EDIT_AREA:
	case ID_TREE_EDIT_ROOM:
	case ID_TREE_EDIT_MINDEX:
	case ID_TREE_EDIT_OINDEX:
	case ID_TREE_EDIT_MOB:
	case ID_TREE_EDIT_OBJ:
		GetCursorPos(&pos);
		OnLButtonDblClk(0, pos);
		break;
	case ID_TREE_DELETE_ROOM:
	case ID_TREE_DELETE_MOB:
	case ID_TREE_DELETE_OBJ:
	case ID_TREE_DELETE_OINDEX:
	case ID_TREE_DELETE_MINDEX:
		OnKeyUp(VK_DELETE, 1, 0);
		break;
	case ID_TREE_NEW_AREA:
		parent->OnNewArea();
		break;
	case ID_TREE_SAVE_AREA:
		parent->OnSave();
		break;
	case ID_TREE_OPEN_AREA:
		parent->OnOpen();
		break;
	case ID_TREE_DELETE_ROOMS:
		parent->DeleteAllRooms();
		break;
	case ID_TREE_DELETE_MOBS:
		parent->DeleteAllMobs();
		break;
	case ID_TREE_DELETE_OBJS:
		parent->DeleteAllObjs();
		break;
	case ID_TREE_ROOM_GRID:
		parent->OnCreateGrid();
		break;
	case ID_TREE_FRIENDS: {
		mob_index *mob;
		DlgEditFriends friends;

		it = GetSelectedItem();
		
		mob = (mob_index*)GetItemData(it);

		friends.mob = mob;

		friends.DoModal();
							   }
		break;
	case ID_TREE_REMOVE_PEOPLE:
		it = GetSelectedItem();
		par = GetParentItem(it);
		
		room = (room_data*)GetItemData(par);
		
		DeleteItem(it);
		
		if(room) {
			room->m_tPeople = parent->InsertItem(CString("Occupants"), room->m_tThis, NULL, PEOPLE);
			room->RemoveEveryone();
		}
		
		SortChildren(par);
		
		break;
	case ID_TREE_EDIT_EQUIP: {
		mob_index *mob;
		DlgEquipMob dlg_eq;

		it = GetSelectedItem();
		mob = (mob_index*)GetItemData(it);
		
		dlg_eq.mob = mob;
		dlg_eq.DoModal();
		}
		break;
	case ID_TREE_NEW_MOB:
		parent->OnNewMob();
		break;
	case ID_TREE_NEW_OBJ:
		parent->OnNewObject();
		break;
	case ID_TREE_NEW_ROOM:
		parent->OnNewRoom();
		break;
	case ID_TREE_EDIT_CONTENTS:
		{
			DlgEditContents dlg_inv(this);
			par = GetSelectedItem();
		
			dlg_inv.obj= (obj_index*)GetItemData(par);

			dlg_inv.DoModal();
		}

		break;
	case ID_TREE_REMOVE_CONTENTS:
		it = GetSelectedItem();
		par = GetParentItem(it);

		GetItemImage(par, index, index);

		switch(index) {
		case ROOM_DATA:
			room = (room_data*)GetItemData(par);
			
			DeleteItem(it);

			if(room) {
				room->m_tContents = parent->InsertItem(CString("Contents"), room->m_tThis, NULL, CONTENTS);
				room->RemoveContents();
			}
			
			SortChildren(par);
			
			break;
		case OBJECT_DATA: {
			object_data *obj = (object_data*)GetItemData(par);

			DeleteItem(it);

			if(obj) {
				obj->RemoveContents();
			}
			break;
		}
		case OBJ_INDEX: {
			obj_index *obj = (obj_index*)GetItemData(par);

			DeleteItem(it);

			if(obj)
				obj->RemoveContents();

			break;
		}
		case MOB_INDEX:
			break;
		case MOB_DATA:
			
			break;
		}
		break;
		
	}

	return true;
}