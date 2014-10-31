// Alias.h: interface for the Alias class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALIAS_H__ED1B4374_0A53_4BA7_8A25_6790E5C867AF__INCLUDED_)
#define AFX_ALIAS_H__ED1B4374_0A53_4BA7_8A25_6790E5C867AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class Alias;

class AliasList
{
private:
	Alias *first;
	Alias *cur;
	Alias *last;

public:
	AliasList();
	virtual ~AliasList();

	CString GetCommand(CString alias);
	bool AddAlias(CString alias, CString command);
	Alias* GetAlias(CString alias);
	void DeleteAll();
	void DeleteAlias(Alias *alias);
	bool DeleteAlias(CString alias);

	CString ShowAliasList();

	void SaveAliasList(ofstream &file);
	void LoadAliasList(ifstream &file);
};

class Alias  
{
private:
	CString alias;
	CString command;
	
	Alias *next;
	Alias *prev;

public:
	Alias();
	Alias(CString al, CString com);
	virtual ~Alias();

public:
	Alias*GetNext();
	void SetNext(Alias *alias);

	Alias*GetPrev();
	void SetPrev(Alias *alias);

	CString GetAlias();
	CString GetCommand();
};

#endif // !defined(AFX_ALIAS_H__ED1B4374_0A53_4BA7_8A25_6790E5C867AF__INCLUDED_)
