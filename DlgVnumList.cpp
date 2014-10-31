#include "stdafx.h"
#include "WinDE.h"
#include "DlgVnumList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgVnumList::DlgVnumList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVnumList::IDD, pParent)
{
	vnum = 0;
	type = -1;
	m_index = NULL;

	//{{AFX_DATA_INIT(DlgVnumList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgVnumList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVnumList)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVnumList, CDialog)
	//{{AFX_MSG_MAP(DlgVnumList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgVnumList::OnInitDialog() 
{
	CRect rect;
	CString str;
	int i;
	
	CDialog::OnInitDialog();
	DWORD dwStyle = ::SendMessage(m_List, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_List, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_List.GetClientRect(rect);
	m_List.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/5);
	m_List.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));
	
	switch(type) {
		case ROOM: {
			room_data *room;
			
			for(room = room_data::room_list, i = 0; room; room = room->next, i++) {
				str.Format("%d", room->vnum);
				m_List.InsertItem(i, str, 0);
				m_List.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(room->name), 1, 0, 0, 0);
				m_List.SetItemData(i, room->vnum);
			}	
		}
		break;
		case KEY: {
			object_data *obj;
			
			for(obj = object_data::obj_head, i = 0; obj; obj = obj->next) {
				if(obj->item_type == TYPE_KEY) {
					str.Format("%d", obj->vnum);
					m_List.InsertItem(i, str, 0);
					m_List.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(obj->name), 1, 0, 0, 0);
					m_List.SetItemData(i, obj->vnum);
					i++;
				}
			}
		}
		break;
		case OBJECT: {
			object_data *obj;
			
			for(obj = object_data::obj_head, i = 0; obj; obj = obj->next, i++) {
				str.Format("%d", obj->vnum);
				m_List.InsertItem(i, str, 0);
				m_List.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(obj->name), 1, 0, 0, 0);
				m_List.SetItemData(i, obj->vnum);
			}
		}
		break;
		case MOBILE: {
			mob_data *mob;

			for(mob = mob_data::first_mob, i = 0; mob; mob = mob->next, i++) {
				str.Format("%d", mob->vnum);
				m_List.InsertItem(i, str, 0);
				m_List.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(mob->name), 1, 0, 0, 0);
				m_List.SetItemData(i, mob->vnum);
			}
		}
		break;
		case MOUNT: {
			mob_index *mount;

			if(m_index && m_index->in_room) {
				for(mount = m_index->in_room->people, i = 0; mount; mount = mount->next) {
					if(mount->IsMount()) {
						str.Format("%d", mount->vnum);
						m_List.InsertItem(i, str, 0);
						m_List.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(mount->GetShortName()), 1, 0, 0, 0);
						m_List.SetItemData(i, mount->vnum);
						i++;
					}
				}
			}
		}
		break;
	}

	return TRUE;
}

void DlgVnumList::OnOK() 
{
	POSITION pos;

	pos = m_List.GetFirstSelectedItemPosition();
	vnum = m_List.GetItemData(m_List.GetNextSelectedItem(pos));
	
	if(vnum == -1)
		vnum = 0;

	CDialog::OnOK();
}

void DlgVnumList::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DlgVnumList::OnOK();
	
	*pResult = 0;
}
