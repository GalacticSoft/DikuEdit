#ifndef _PROG_H_
#define _PROG_H_

#include "Mobs.h"

enum ProgsTypes
{
	ERROR_PROG		   =-1,
	IN_FILE_PROG	   =0,
	ACT_PROG		   =BV00,
	SPEECH_PROG		   =BV01,
	RAND_PROG		   =BV02,
	FIGHT_PROG		   =BV03,
	DEATH_PROG		   =BV04,
	HITPRCNT_PROG	   =BV05, // percentage attack prog - mobs only
	ENTRY_PROG		   =BV06,
	GREET_PROG		   =BV07,
	ALL_GREET_PROG	   =BV08,
	GIVE_PROG		   =BV09,
	BRIBE_PROG		   =BV10,
	PROC_PROG          =BV11, // weapon combat proc - objects only
	MOVE_PROG          =BV12, // movement script - Veygoth
	EXIT_PROG		   =BV13,
};

enum ProgTemplates
{
	greet_prog=0,
	act_prog,
	fight_prog,
	bribe_prog,
	death_prog,
	hitpercent_prog,
	speech_prog,
	rand_prog,
	move_prog,
	max_template,
};


typedef struct prog_types
{
	int type;
	char *name;
} prog_type;

class ProgFile
{
public:
	int type;
	CString filename;
	
	union
	{
		mob_data *mob;
		object_data *obj;
	};

	CString prog_text;

	ProgFile *next;
	ProgFile *prev;

public:
	ProgFile();
	~ProgFile();
};

class ProgList
{
public:
	ProgFile *first;

public:
	ProgList();
	~ProgList();

	ProgFile* GetProg(mob_index*mob);
	ProgFile* GetProg(mob_data *mob);
	ProgFile* GetProg(object_data *obj);
	ProgFile* GetProg(obj_index *obj);
	void AddProg(ProgFile *prog);
	void RemoveProg(ProgFile *prog);
	void RemoveAll();
};

extern const prog_types progs[];
extern const CString prog_vars[];
extern const CString prog_funcs[];
extern const CString prog_comms[];
extern const CString progkeywords[];
extern const CString prog_templates[];
extern const CString prog_operators[];

int ProgKeywordCount();
int ProgCommCount();
int ProgCount();
int VarCount();
int ProgFuncCount();
#endif