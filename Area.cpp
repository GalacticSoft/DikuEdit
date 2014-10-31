#include "StdAfx.h"

int area_data::ReadArea(FILE *fp)
{
	CString word;
	char buf[5024];
	int i;
	int j;
	int error_count = 0;
	int status;
	CString p;
	int tmpi;
	int num_keys;
	int last_key = 0;

	char def_author[] = "Unknown";
	char def_reset[] =  "You hear the patter of little feet.";
  
	struct key_data key_tab[] = 
	{
		{"Version",		FALSE,	0,					{&version,		NULL}},
		{"Name",		TRUE,	MAND,				{&name,			NULL}},
		{"Author",		TRUE,	(ULONG)&def_author,	{&author,		NULL}},
		{"Levels",		FALSE,	1,					{&llv, &ulv,	NULL}},
		{"Security",	FALSE,	MAND,				{&security,		NULL}},
		{"VNUMs",		FALSE,	MAND,				{&vnum, &uvnum, NULL}},
		{"Builders",	TRUE,	MAND,				{&builders,		NULL}},
		{"ClanId",		FALSE,	0,					{&clan_id,		NULL}},
		{"AreaFlags",	FALSE,	0,					{&area_flags,	NULL}},
		{"Justice",		FALSE,	0,					{&justice,		NULL}},
		{"Judge",		FALSE,	0,					{&judge,		NULL}},
		{"Jail",		FALSE,	0,					{&jail,			NULL}},
		{"Squads",		FALSE,	0,					{&squads,		NULL}},
		{"Nodim",		FALSE,	FALSE,				{&nodim,		NULL}},
		{"Barracks",	FALSE,	0,					{&barracks,		NULL}},
		{"Defender",	FALSE,	0,					{&defender, &defender_num, NULL}},
		{"Recall",		FALSE,	vnum,				{&recall,		NULL}},
		{"Reset",		TRUE,	(ULONG)&def_reset,	{&resetmsg,		NULL}},
		{"\0",			FALSE,	0}
	};
  
	for (num_keys = 0; *key_tab[num_keys].key;)
		num_keys++;
  
	for (; !feof(fp);) 
	{
		word = fread_word(fp, &status);
	  
		if (!word) 
		{
			AfxMessageBox("fread_area:  Error reading key.  EOF?");
			fread_to_eol(fp);
			break;
		}
    
		/* This little diddy searches for the keyword
			from the last keyword found */
		
		for(i = last_key; i < last_key + num_keys && strcmp(key_tab[i % num_keys].key, word);)
			i++;
    
		i = i % num_keys;
    
		if (!strcmp(key_tab[i].key, word))
			last_key = i;
		else
		i = num_keys;
    
		if (*key_tab[i].key) 
		{	
			/* Key entry found in key_tab */
			if (key_tab[i].status == SPECIFIED)
				AfxMessageBox("Key already specified.");
      
			/* Entry is a string */
      
			else if (key_tab[i].status) 
			{
				if ((p = fread_string(fp, &status)) && !status) 
				{	
					*(CString*) key_tab[i].ptrs[0] = p;
				}
			}
			else
				for (j = 0; key_tab[i].ptrs[j]; j++) 
				{
					tmpi = fread_number(fp, &status);
					
					if (!status)
						*(int *) key_tab[i].ptrs[j] = tmpi;
				}
      
			if (status) 
			{
				fread_to_eol(fp);
				continue;
			} 
			else
				key_tab[i].status = SPECIFIED;
		}
		else if( !strcmp( word, "Ansimap" ))
		{                    
			fread_number( fp, &status );
			fread_number( fp, &status );
			fread_number( fp, &status );
			fread_number( fp, &status );
			fread_string( fp, &status );
		}
		else if (!strcmp(word, "End"))
			break;
		else 
		{
			fread_to_eol(fp);
		}
	}
	
	/* Require all manditory fields, set defaults */
	
	for (i = 0; *key_tab[i].key; i++) 
	{
		if (key_tab[i].status == SPECIFIED || key_tab[i].deflt == DEFLT)
			continue;
    
		if (key_tab[i].deflt == MAND) 
		{
			sprintf(buf, "Manditory field '%s' missing from file.", key_tab[i].key);
			AfxMessageBox(buf);
			error_count++;
			continue;
		}
    
		/* This if/else sets default strings and numbers */
    
		if (key_tab[i].status && key_tab[i].deflt) 
		{
			strcpy(*(char **) key_tab[i].ptrs[0] ,(char *)key_tab[i].deflt);
		} 
		else
			for (j = 0; key_tab[i].ptrs[j]; j++)
				*(int *) key_tab[i].ptrs[j] = key_tab[i].deflt;
	}

	llifespan = 15;
	ulifespan = 15;
  
	return error_count;
}
