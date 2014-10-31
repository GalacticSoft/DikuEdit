#if !defined(AFX_DLGMAPEDIT_H__222EE499_80C6_452B_91F5_C53AFD778072__INCLUDED_)
#define AFX_DLGMAPEDIT_H__222EE499_80C6_452B_91F5_C53AFD778072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapEdit.h : header file
//
#include "Rooms.h"

/////////////////////////////////////////////////////////////////////////////
// DlgMapEdit dialog

enum {MID_X = 50, MID_Y = 50};
enum {MAX_X = 100, MAX_Y = 100};
enum {CELL_WIDTH = 25, CELL_HEIGHT = 25};
enum {X_SCROLL = 100, Y_SCROLL = 100};
enum {V_CELLS = 10, H_CELLS = 14};

class MapCell
{
public:
	int terrain;
	room_data *room;
	CRect pos;
	bool painted;

public:
	MapCell() : room(NULL), terrain(-1), painted(false){ };
	~MapCell() {room = NULL; terrain = -1; painted = false;};
};

class MapLevel
{
public:
	//MapCell map[MAX_X][MAX_Y];
	MapCell **map;

	MapLevel* above;
	MapLevel* below;
	
	int level;
	bool painted;
	int x, y;

public:
	MapLevel() : above(NULL), below(NULL), level(0) 
	{
		map = new MapCell*[MAX_X];

		for(int i = 0; i < x; i++)
			map[i] = new MapCell[y];
	};

	MapLevel(int x, int y)  :above(NULL), below(NULL), level(0), x(x), y(y)
	{
		map = new MapCell*[MAX_X];

		for(int i = 0; i < x; i++)
			map[i] = new MapCell[y];
	};

	~MapLevel()
	{
		for(int i = 0; i < x; i++)
			delete [] map[i];

		delete [] map;
	};
};

class RoomPos
{
public:
	int x, y, z;
};

class DlgMapEdit : public CDialog
{
public:
	friend class CWinDEDlg;

	DECLARE_EASYSIZE
public:
	DlgMapEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgMapEdit();
	bool show_vnum;
	bool shut_down;

	const HICON& GetTerrainIcon(const int& ter) const;
	
	bool IsCurrentRoom(const int& x, const int& y, const int& z);
	
	bool IsCurrentRoom(const RoomPos &point);
	
	void ShowVnum();

	void Center();
	
	void CenterOnCurrRoom();

	void DrawArea();

	void ChangeLevel(int dir);

	RoomPos SelectRoom(const CPoint& point);
	
	void MoveRoom(int dir);

	void ChangeTerrain(int sect);

	void AddMob();
	void AddItem();

	HTREEITEM InsertItem(CString &title, HTREEITEM parent, void *data, int image);

	// Dialog Data
	//{{AFX_DATA(DlgMapEdit)
	enum { IDD = IDD_MAP };
	CTreeCtrl	room_tree;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgMapEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgMapEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:		
	void ClearArea();
	
	void DrawRoom(room_data *room, int x, int y, MapLevel *level);
	
	BOOL ChangeLevel(UINT id);
	
	BOOL MenuSelect(UINT id);
	
	void UpdateDisplay();
	
	void LoadTerrain(const int& ter);

	const RoomPos GetCell(const CPoint& point) const;

private:
	HICON terrain[SECT_MAX+1];
	
	MapLevel *ground_level;
	
	MapLevel *curr_level;
	
	CToolBar m_Tool;
	
	RoomPos curr_room;

	CWinDEDlg *par;

	CDC *pdc;

	HTREEITEM mob_parent;
	HTREEITEM obj_parent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPEDIT_H__222EE499_80C6_452B_91F5_C53AFD778072__INCLUDED_)

