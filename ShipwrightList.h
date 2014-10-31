// ShipwrightList.h: interface for the ShipwrightList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIPWRIGHTLIST_H__C066D701_3DC8_4150_8543_38DF4EB009A1__INCLUDED_)
#define AFX_SHIPWRIGHTLIST_H__C066D701_3DC8_4150_8543_38DF4EB009A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ShipwrightList  
{
public:
	ShipwrightList();
	virtual ~ShipwrightList();

	int shops[MAX_SHIPWRIGHTS];
	int count;

	void InitList(int shipwrights[], CListCtrl &list);
	void Add(CListCtrl &list);
	void Remove(CListCtrl &list);
	void Update(int shipwrights[]);
};

#endif // !defined(AFX_SHIPWRIGHTLIST_H__C066D701_3DC8_4150_8543_38DF4EB009A1__INCLUDED_)
