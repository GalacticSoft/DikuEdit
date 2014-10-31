#include "StdAfx.h"
#include "CmdHistory.h"
//#include "ServerCommands.h"

Cmd::Cmd()
{
	cmd = CWinDEDlg::CMD_NONE;
	args = "";
	next = NULL;
	prev = NULL;
}

Cmd::~Cmd()
{
	CWinDEDlg::CMD_NONE;
	args = "";
	next = NULL;
	prev = NULL;
}

CmdHistory::CmdHistory()
{
	entries = 0;
	first = NULL;
	last = NULL;
}

CmdHistory::~CmdHistory()
{

}

void CmdHistory::AddCmd(int cmd, const CString &name, const CString &args)
{
	Cmd *tmp;

	tmp = new Cmd();
	tmp->cmd = cmd;
	tmp->name = name;
	tmp->args = args;

	if(!first)
	{
		first = tmp;
		last = first;
		entries++;
	}
	else if(entries < MAX_ENTRIES)
	{
		last->next = tmp;
		tmp->prev = last;
		last = tmp;
		entries++;
	}
	else if(entries >= MAX_ENTRIES)
	{
		RemoveCmd(first);
		AddCmd(cmd, name, args);
	}
}

void CmdHistory::RemoveCmd(Cmd *cmd)
{
	if(first == cmd)
	{
		if(first->next)
			first->next->prev = NULL;

		first = first->next;

	}
	else if(cmd == last)
	{
		last->prev->next = NULL;
		last = last->prev;
	}
	else
	{
		cmd->next->prev = cmd->prev;
		cmd->prev->next = cmd->next;
	}

	delete cmd;
	cmd = NULL;
	entries--;

}

void CmdHistory::ExecuteCmd(int cmd, CWinDEDlg *dlg)
{
	
	Cmd *tmp;
	CString str;

	cmd = cmd-ID_HISTORY_0;
	
	tmp = first;
	
	for(int i = 0; i < MAX_ENTRIES; i++)
	{
		if(i == cmd)
		{
			str.Format("%s %s", tmp->name, tmp->args);
			dlg->InterpKeyWord(str);
			break;
		}
		
		tmp = tmp->next;
	}
}

void CmdHistory::ShowHistory(CWnd *wnd)
{
	CPoint pos(-1, -1);   
	CRect rect;
	CMenu menu; 
	CButton *btn;
	Cmd *tmp;
	CString str;
	int i = ID_HISTORY_0;
	
	btn = (CButton*)wnd->GetDlgItem(IDC_HISTORY);
	
	btn->GetWindowRect(rect);

	menu.CreatePopupMenu();
	
	pos = rect.TopLeft();
	
	for(tmp = first; tmp; tmp = tmp->next)
	{
		str.Format("%d: %s %s%s", (i+1)-ID_HISTORY_0, tmp->name, tmp->args.IsEmpty() ? "" : "- ", tmp->args);

		menu.AppendMenu(MF_STRING, i++, str);
	}              
		      
	menu.TrackPopupMenu(TPM_BOTTOMALIGN | TPM_LEFTBUTTON, pos.x, pos.y, wnd);   
}