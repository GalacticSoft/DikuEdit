#ifndef _CMD_HISTORY_H_
#define _CMD_HISTORY_H_

class CSocketMudDlg;

enum
{
	MAX_ENTRIES = 25,
};

class Cmd
{
public:
	Cmd();
	~Cmd();

public:
	int cmd;
	CString name;
	CString args;
	Cmd *next;
	Cmd *prev;
};

class CmdHistory
{
public:
	int entries;
	Cmd *first;
	Cmd *last;

public:
	CmdHistory();
	~CmdHistory();

public:
	void AddCmd(int cmd, const CString &name, const CString &args);
	void RemoveCmd(Cmd *cmd);
	void ExecuteCmd(int cmd, CWinDEDlg *dlg);

	void ChangeSize(int size);

	void ShowHistory(CWnd *wnd);
};

#endif