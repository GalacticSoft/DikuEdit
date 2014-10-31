// Alias.cpp: implementation of the Alias class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinDE.h"
#include "Alias.h"
#include "Utils.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Alias::Alias()
{
	next = NULL;
	prev = NULL;
	alias = "";
	command = "";
}

Alias::~Alias()
{
	next = NULL;
	prev = NULL;
	alias = "";
	command = "";
}

Alias::Alias(CString al, CString com)
{
	next = NULL;
	prev = NULL;
	this->alias = al;
	this->command = com;
}

Alias* Alias::GetNext()
{
	return next;
}

void Alias::SetNext(Alias *alias)
{
	next = alias;
}

Alias* Alias::GetPrev()
{
	return prev;
}

void Alias::SetPrev(Alias *alias)
{
	prev = alias;
}

CString Alias::GetAlias()
{
	return alias;	
}

CString Alias::GetCommand()
{
	return command;
}

AliasList::AliasList()
{
	first = NULL;
	cur = NULL;
	last = NULL;
}

AliasList::~AliasList()
{
	DeleteAll();
	first = NULL;
	cur = NULL;
	last = NULL;
}

CString AliasList::GetCommand(CString alias)
{
	alias = GetArg(alias);

	for(cur = first; cur; cur = cur->GetNext())
	{
		if(cur->GetAlias() == alias)
			return cur->GetCommand();
	}

	return "";
}

bool AliasList::AddAlias(CString alias, CString command)
{
	Alias *new_alias;
	CString tmp;

	tmp = GetCommand(alias);

	if(!tmp.IsEmpty())
		return false;

	new_alias = new Alias(alias, command);

	if(first == NULL)
	{
		first = new_alias;
		cur = new_alias;
		last = new_alias;
	}
	else 
	{
		new_alias->SetPrev(last);
		last->SetNext(new_alias);
		last = new_alias;
	}

	return true;
}

void AliasList::DeleteAll()
{
	while(first)
		DeleteAlias(first);
}

Alias* AliasList::GetAlias(CString alias)
{
	for(cur = first; cur; cur = cur->GetNext())
	{
		if(cur->GetAlias() == alias)
			return cur;
	}

	return NULL;
}

bool AliasList::DeleteAlias(CString alias)
{
	cur = GetAlias(alias);

	if(cur)
	{
		DeleteAlias(cur);
		cur = NULL;
		return true;
	}

	return false;
}

void AliasList::DeleteAlias(Alias* alias)
{
	Alias *prev = NULL, *next = NULL;

	if(alias->GetPrev())
		prev = alias->GetPrev();
	if(alias->GetNext())
		next = alias->GetNext(); 

	if(alias == first || alias == last)
	{
		if(alias == first)
		{
			first = first->GetNext();
		
			if(next)
				next->SetPrev(NULL);
		}
	
		if(alias == last)
		{
			last = last->GetPrev();

			if(prev)
				prev->SetNext(NULL);
		}
	}
	else
	{
		if(next)
			next->SetPrev(prev);

		if(prev)
			prev->SetNext(next);
	}

	delete alias;
}

CString AliasList::ShowAliasList()
{
	CString str, list;
	
	if(!first)
		list.Format("No aliases have been created.");
	else
	{
		for(cur = first; cur; cur = cur->GetNext())
		{
			if(cur != last)
				str.Format("Alias: %s Command: %s\r\n", cur->GetAlias(), cur->GetCommand());
			else
				str.Format("Alias: %s Command: %s", cur->GetAlias(), cur->GetCommand());
				
			list += str;
		}
	}

	return list;
}

void AliasList::SaveAliasList(ofstream &file)
{
	CString str;

	if(file.is_open())
	{
		for(cur = first; cur; cur = cur->GetNext())
		{
			if(cur)
			{
				str.Format("#Alias %s %s\n", cur->GetAlias(), cur->GetCommand());
				file.write(str, str.GetLength());
			}
		}
	}
}

void AliasList::LoadAliasList(ifstream &file)
{
	char str[512];
	CString str1;
	CString arg1, arg2;

	while(!file.eof())
	{
		file.getline(str, 512, '\n');

		str1 = str;

		arg1 = GetArg(str1);

		if(arg1 == "#Alias")
		{
			arg2 = GetArg(str1);
			
			AddAlias(arg2, str1);
		}
	}
}