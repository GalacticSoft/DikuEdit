#if !defined(AFX_WINDEDLG_H__AB46590E_4717_4274_A65C_C4964C1AA139__INCLUDED_)
#define AFX_WINDEDLG_H__AB46590E_4717_4274_A65C_C4964C1AA139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class ColorEditWnd;
class area_data;
class room_data;
class mob_data;
class object_data;
class quest_data;

#include "Bits.h"
#include "SampleColorizer.h"
#include "CtrlToolBar.h"
#include "Interp.h"
#include "ZoneTree.h"
#include "EasySize.h"
#include "SplitterControl.h"
#include "DlgDirections.h"
#include "DlgSave.h"
#include "DlgCreateGrid.h"
#include "DlgMapEdit.h"
#include "CmdHistory.h"
#include "Alias.h"
#include "ColorEditWnd.h"
#include "DlgMapEdit.h"
#include "ShipBuilder.h"
#include "DlgAbout.h"

enum {
	//settings bits
	OPEN_AREA_FORMAT	= BV00,
	SAVE_AREA_FORMAT	= BV01,
	AUTO_SAVE			= BV02,
	WALK_CREATE			= BV03,
	SHOW_COMPAS			= BV04,
	OPEN_DE_FORMAT		= BV05,
	SAVE_DE_FORMAT		= BV06,
	ECHO_COMMANDS		= BV07,
	WINDOW_VISIBLE		= BV08,
	SHOW_MAP			= BV09,
	OPEN_AREA_V1_FORMAT = BV10,
	SAVE_AREA_V1_FORMAT = BV11,
	SAVE_ON_EXIT		= BV12,
	DISP_LINE_LEN		= BV13,

	PAGE_LEN			= 40,

	//misc
	ICON_MESSAGE	= WM_APP+1,
	TRAY_ID			= 1
};

extern unsigned int	editor_flags;

class CWinDEDlg : public CDialog
{
	DECLARE_EASYSIZE
public:
	static char		class_name[];
	static int		class_index;
	
public:
	friend class CZoneTree;
	friend class DlgDirections;
	friend class DlgSave;
	friend class DlgMapEdit;

public:
	CWinDEDlg(CWnd* pParent = NULL);	// standard constructor
	
	NOTIFYICONDATA	niData; 
	HICON			tray_icon;

	unsigned int	timer;
	
	room_data		*in_room;
	
	mob_index		*user;

	CSplitterControl split;
	CStatusBar		m_Status;
	CCtrlToolBar	m_Tool;
	CZoneTree		zone_tree;
	CmdHistory		history;
	
	DlgDirections	dlg;
	DlgMapEdit		map;
	DlgSave			save_progress;
	AliasList		alias_list;

	HTREEITEM		m_tArea;
	HTREEITEM		m_tRooms;
	HTREEITEM		m_tObjects;
	HTREEITEM		m_tMobiles;

	COLORREF		def_color;
	COLORREF		echo_color;

	static class InterpData {
	public:
		char* keyword;
		bool needs_args;
		bool show_prompt;
		int cmd;
	}  keyword_list[];
	
	enum Commands {
		CMD_NONE,
		CMD_NORTH,
		CMD_SOUTH,
		CMD_WEST,
		CMD_EAST,
		CMD_UP,
		CMD_DOWN,
		CMD_NORTHWEST,
		CMD_SOUTHWEST,
		CMD_NORTHEAST,
		CMD_SOUTHEAST,
		CMD_LOOK,
		CMD_GOTO,
		CMD_NEW,
		CMD_EDIT,
		CMD_DELETE,
		CMD_GRID,
		CMD_SAVE,
		CMD_CLOSE,
		CMD_EXIT,
		CMD_COMMAND,
		CMD_STAT,
		CMD_FOLLOW,
		CMD_MOUNT,
		CMD_GIVE,
		CMD_EQUIP,
		CMD_LOAD,
		CMD_DEF_ROOM,
		CMD_ALIAS,
		CMD_UNALIAS,
		CMD_RENUMBER,
		CMD_ASK,
		CMD_LINK,
		CMD_EXITS,
		CMD_CLONE,	
		CMD_PURGE,
		CMD_DROP,
		CMD_GET,
		CMD_LIST,
		CMD_SHOW,
		CMD_INV,
		CMD_TAKE,
		CMD_WHERE,
	};

	HTREEITEM InsertItem(CString &title, HTREEITEM parent, void* data, int class_index);
	void UpdateItem(CString &title, HTREEITEM item);
	void RemoveItem(HTREEITEM item);
	
    void UpdateStatusBar();

	void AddRoom(room_data *room);
	void AddMob(mob_data *mob);
	void AddObject(object_data *obj);
	void AddMobToRoom(mob_index *mob, room_data *room);
	void AddObjToRoom(obj_index *obj, room_data *room);
	
	void ShowPrompt();
	bool PromptResponse();
	void ShowRoom(bool prompt = true);
	void MoveRoom(int dir);

	void LoadSettings();
	void SaveSettings();

	void DeleteAllRooms();
	void DeleteAllMobs();
	void DeleteAllObjs();

	void CloseArea();

	void InitColorControl();
	void AdjustToolLine();
	void InitSplitter();
	void InitZoneTree();
	void InitTrayIcon();

	int LastKey();
	
	bool CheckPortalCommand(CString str);

	int InterpKeyWord(CString &str);
	
	void Look(CString args);
	void Goto(CString args);
	void New(CString args);
	void Edit(CString args);
	void Delete(CString args);
	void Grid(CString args);
	void Command(CString args);
	void Stat(CString args);
	void Follow(CString args);
	void Mount(CString args);
	void Give(CString args);
	void Equip(CString args);
	void Load(CString args);
	void Default(CString args);
	void Alias(CString args);
	void UnAlias(CString args);
	void Renumber(CString args);
	void Ask(CString args);
	void Link(CString args);
	void Exits(CString args);
	void Clone(CString args);
	void Purge(CString args);
	void Get(CString args);
	void Drop(CString args);
	void List(CString args);
	void Show(CString args);
	void Inv(CString args);
	void Take(CString args);
	void Where(CString args);

	void StatMob(int vnum);
	void StatObj(int vnum);
	void StatRoom(int vnum);
	void StatArea(int vnum);

	void DeleteMob(int vnum);
	void DeleteObj(int vnum);
	void DeleteRoom(int vnum);

	void DeleteRoom(room_data *room);

	room_data *CreateRoomGrid(int x, int y, int z);

	void ShowText(const char* str, bool show_prompt);

	void OnTrayNotify(WPARAM wParam, LPARAM lParam);

	void AreaLoaded();

	void SaveDefaults();
	void LoadDefaults();
	void OpenCommandLineFile();

	void CheckQuests(mob_index *mindex);
	void GiveQuestReward(mob_index *mob, quest_data *quest);
	void RemoveQuestItems(mob_index *mob, quest_data *quest);

	// Dialog Data
	//{{AFX_DATA(CWinDEDlg)
	enum { IDD = IDD_WINDE_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinDEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
	
	void DoResize1(int delta);
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// Implementation
protected:
	HICON m_hIcon;

	ColorEditWnd * m_pColorWnd;
   
    // our own special colorizer
    CAnsiColorizer m_colorizer;

	// Generated message map functions
	//{{AFX_MSG(CWinDEDlg)
	virtual void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnter();
	afx_msg void OnMobilesDeletemob();
	afx_msg void OnMobilesEditmob();
	afx_msg void OnMobilesNewmob();
	afx_msg void OnObjectsDeleteobject();
	afx_msg void OnObjectsEditobject();
	afx_msg void OnObjectsNewobject();
	afx_msg void OnRoomsDeleteroom();
	afx_msg void OnRoomsEditroom();
	afx_msg void OnRoomsNewroom();
	afx_msg void OnNorthWest();
	afx_msg void OnNorth();
	afx_msg void OnNorthEast();
	afx_msg void OnWest();
	afx_msg void OnLook();
	afx_msg void OnEast();
	afx_msg void OnSouth();
	afx_msg void OnSouthWest();
	afx_msg void OnSouthEast();
	afx_msg void OnSave();
	afx_msg void OnSettings();
	afx_msg void OnHistory();
	afx_msg void OnOpen();
	afx_msg void OnExit();
	afx_msg void OnNewArea();
	afx_msg void OnAreaEdit();
	afx_msg void OnDown();
	afx_msg void OnUp();
	afx_msg void OnDirections();
	afx_msg void OnMap();
	afx_msg void OnNewRoom();
	afx_msg void OnEditRoom(int vnum);
	afx_msg void OnNewMob();
	afx_msg void OnEditMob(int vnum);
	afx_msg void OnNewObject();
	afx_msg void OnEditObject(int vnum);
	afx_msg void OnAreaProperties();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnCreateGrid();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void HistoryMenu(UINT id);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect); 
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnShipBuilder();
	afx_msg void OnBitCalc();
	afx_msg void OnStatistics();
	afx_msg BOOL OnTrayMenu(UINT id);
	afx_msg void OnHelp();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDEDLG_H__AB46590E_4717_4274_A65C_C4964C1AA139__INCLUDED_)
