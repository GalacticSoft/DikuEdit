#include "StdAfx.h"
#include "Progs.h"   

const prog_types progs[] =
{
	{IN_FILE_PROG,		"in_file_prog"	},
    {ACT_PROG,			"act_prog"		},
    {SPEECH_PROG,		"speech_prog"	},
    {RAND_PROG,			"rand_prog"		},
    {FIGHT_PROG,		"fight_prog"	},
    {HITPRCNT_PROG,		"hitprcnt_prog"	},
    {DEATH_PROG,		"death_prog"	},
    {ENTRY_PROG,		"entry_prog"	},
    {GREET_PROG,		"greet_prog"	},
    {ALL_GREET_PROG,	"all_greet_prog"},
    {GIVE_PROG,			"give_prog"		},
    {BRIBE_PROG,		"bribe_prog"	},
	{MOVE_PROG,			"move_prog"		},
	{EXIT_PROG,			"exit_prog"		},
};

const CString prog_operators[] =
{
	"==",
	"!=",
	"/",
	"!/",
	"<",
	">",
	"<=",
	">=",
	"&",
	"|",
};

const CString prog_vars[] = 
{
	"$i",
	"$I",
	"$j",
	"$l",
	"$k",
	"$n",
	"$N",
	"$e",
	"$m",
	"$s",
	"$t",
	"$T",
	"$E",
	"$M",
	"$S",
	"$r",
	"$R",
	"$J",
	"$L",
	"$K",
	"$o",
	"$O",
	"$a",
	"$p",
	"$P",
	"$A",
};

const CString prog_funcs[] =
{
	"rand",
	"isnpc",
	"ispc",
	"isgood",
	"isfight",
	"isimmort",
	"ischarmed",
	"isfollow",
	"isaffected",
	"hitprcnt",
	"inroom",
	"sex",
	"position",
	"level",
	"class",
	"goldamt",
	"objtype",
	"objval#",
	"number",
	"name",
};

const CString prog_comms[] = 
{
	"MPSTAT",		
	"MPASOUND",
	"MPJUNK",		
	"MPECHO",
	"MPMLOAD",	
	"MPECHOAT",
	"MPOLOAD",	
	"MPECHOAROUND",
	"MPKILL",		
	"MPPURGE",
	"MPGOTO",		
	"MPAT", 
	"MPTRANSFER",	
};

const CString progkeywords[] =
{
	"if",
	"endif",
	"else",
	"or",
	"break",
};

const CString prog_templates[] =
{
	"greet_prog",
	"act_prog",
	"fight_prog",
	"bribe_prog",
	"death_prog",
	"hitpercent_prog",
	"speech_prog",
	"rand_prog",
	"move_prog",
};

int ProgKeywordCount() {return sizeof(progkeywords)/sizeof(CString);}
int ProgCommCount() {return sizeof(prog_comms)/sizeof(CString);}
int VarCount() {return sizeof(prog_vars)/sizeof(CString);}
int ProgCount() {return sizeof(progs)/sizeof(prog_types);}
int ProgFuncCount() {return sizeof(prog_funcs)/sizeof(CString);}

ProgFile::ProgFile()
{
	type = NONE;
	filename = "";
	mob = NULL;
	obj = NULL;
	prog_text = "";

	next = NULL;
	prev = NULL;
}

ProgFile::~ProgFile()
{
	filename = "";
	mob = NULL;
	prog_text = "";

	next = NULL;
	prev = NULL;
}

ProgList::ProgList()
{
	first = NULL;
}

ProgList::~ProgList()
{

}

void ProgList::AddProg(ProgFile *prog)
{
	ProgFile *tmp = NULL;

	if(first == NULL) 
	{
		first = prog;
		prog->next = NULL;
		prog->prev = NULL;
	} 
	else 
	{
		for(tmp = first; tmp; tmp = tmp->next) 
		{
			if(tmp->next == NULL) 
			{
				tmp->next = prog;
				prog->prev = tmp;
				prog->next = NULL;
				
				break;
			}
		}
	}
}

void ProgList::RemoveProg(ProgFile *prog)
{
	ProgFile *tmp = NULL;

	if(first == NULL)
		return;

	if(prog == first) 
	{
		first = prog->next;
		
		if(first)
			first->prev = NULL;
		
		prog->next = NULL;
	} 
	else 
	{
		for(tmp =first; tmp; tmp = tmp->next) 
		{
			if(tmp->next == prog) 
			{
				tmp->next = prog->next;

				break;
			}
		}
	}
}

void ProgList::RemoveAll()
{
	ProgFile *prog;

	while((prog = first))
	{
		RemoveProg(prog);
		delete prog;
	}
}

ProgFile* ProgList::GetProg(mob_index*mob)
{
	if(mob->mob)
		return GetProg(mob->mob);

	return NULL;
}

ProgFile* ProgList::GetProg(mob_data *mob)
{
	ProgFile *prog;

	for(prog = first; prog; prog = prog->next)
	{
		if(prog->type != MOBILE)
			continue;

		if(prog->mob == mob)
			return prog;
	}

	return NULL;
}

ProgFile* ProgList::GetProg(object_data *obj)
{
	ProgFile *prog;

	for(prog = first; prog; prog = prog->next)
	{
		if(prog->type != OBJECT)
			continue;

		if(prog->obj == obj)
			return prog;
	}

	return NULL;	
}

ProgFile* ProgList::GetProg(obj_index *obj)
{
	if(obj->obj)
		return GetProg(obj->obj);

	return NULL;

}