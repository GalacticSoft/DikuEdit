// ShipwrightList.cpp: implementation of the ShipwrightList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinDE.h"
#include "ShipwrightList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ShipwrightList::ShipwrightList()
{
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;

	count = 0;
}

ShipwrightList::~ShipwrightList()
{
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;

	count = 0;
}

void ShipwrightList::Add(CListCtrl &list)
{
	DlgEnterVnum vnum_list;
	mob_data *mob;
	CString str;
	int i;

	vnum_list.type = MOBILE;
	
	i = list.GetItemCount();

	if(count != MAX_SHIPWRIGHTS)
	{
		if(vnum_list.DoModal() == IDOK)
		{
			shops[count] = vnum_list.vnum;
			

			if((mob = GetMobByVnum(vnum_list.vnum)))
			{
				str.Format("%d", mob->vnum);
				list.InsertItem(i, str, 0);
				list.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(mob->short_descr), 1, 0, 0, 0);
				list.SetItemData(i, count);
			}
			else
			{
				str.Format("%d", vnum_list.vnum);
				list.InsertItem(i, str, 0);
				list.SetItem(i, 1, LVIF_TEXT, "A Non-Existant mobile", 1, 0, 0, 0);
				list.SetItemData(i, count);
			}
			
			count++;
		}
	}
	else
	{
		CString str;
		str.Format("Item can only be sold by %d shipwrights.", MAX_SHIPWRIGHTS);
		AfxMessageBox(str);
	}

}

void ShipwrightList::InitList(int shipwrights[], CListCtrl &list)
{
	mob_data *mob;
	CString str;

	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
	{
		if(shipwrights[i] != 0)
		{
			shops[count] = shipwrights[i];

			if((mob = GetMobByVnum(shops[count])))
			{
				str.Format("%d", mob->vnum);
				list.InsertItem(i, str, 0);
				list.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(mob->short_descr), 1, 0, 0, 0);
				list.SetItemData(i, count);
			}
			else
			{
				str.Format("%d", shops[count]);
				list.InsertItem(i, str, 0);
				list.SetItem(i, 1, LVIF_TEXT, "A Non-Existant mobile", 1, 0, 0, 0);
				list.SetItemData(i, count);
			}

			count++;
		}
	}
}

void ShipwrightList::Remove(CListCtrl &list)
{
	POSITION pos;
	int i, index;

	pos = list.GetFirstSelectedItemPosition();
	i = list.GetNextSelectedItem(pos);

	index = list.GetItemData(i);

	shops[index] = 0;

	list.DeleteItem(i);

	count--;
}

void ShipwrightList::Update(int shipwrights[])
{
	int x, i;

	for(x = 0; x < MAX_SHIPWRIGHTS; x++)
		shipwrights[x] = 0;

	for(x = 0, i = 0; i < MAX_SHIPWRIGHTS; i++)
	{
		if(shops[i] != 0)
		{
			shipwrights[x] = shops[i];
			x++;
		}
	}
}