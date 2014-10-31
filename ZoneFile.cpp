#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

ZoneFile::ZoneFile()
{
	parent = NULL;
	txt = NULL;
	prg = NULL;
	pos = 0;
}

ZoneFile::ZoneFile(CWinDEDlg *parent)
{
	this->parent = parent;
	dlg_save.Create(IDD_SAVE, parent);
	dlg_save.CenterWindow();
	dlg_save.SetWindowPos(&parent->wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	txt = NULL;
	prg = NULL;
	pos = 0;
	DisplayProg();
}

ZoneFile::~ZoneFile()
{
	CloseProg();
}

void ZoneFile::DisplayProg()
{
	dlg_save.ShowWindow(SW_SHOW);
	
	txt = (CStatic*)dlg_save.GetDlgItem(IDC_SAVING);
	prg = (CProgressCtrl*)dlg_save.GetDlgItem(IDC_SAVING_PROGRESS);
}

void ZoneFile::CloseProg()
{
	dlg_save.ShowWindow(SW_HIDE);
	txt = NULL;
	prg = NULL;
}

void ZoneFile::SetProgRange(int x, int y)
{
	prg->SetRange(x, y);
}

void ZoneFile::SetProgPos(int x)
{
	prg->SetPos(x);
}

void ZoneFile::SetProgText(CString str)
{
	txt->SetWindowText(str);
}

/*
 * Read a letter from a file.
 */
char fread_letter( FILE *fp )
{
    char c;

    do
    {
		c = getc( fp );
    }
    while ( isspace( c ) );

    return c;
}

/*
 * Read a number from a file.
 */
int fread_number( FILE *fp, int *status )
{
    int  c;
    bool sign;
    int  number;
    int  stat;

    do
    {
		c = getc( fp );
    }
    while ( isspace( c ) );

    number = 0;

    sign   = FALSE;
    
	if ( c == '+' )
    {
		c = getc( fp );
    }
    else if ( c == '-' )
    {
		sign = TRUE;
		c = getc( fp );
    }

    if ( !isdigit( c ) )
    {
        *status = 1;
		AfxMessageBox( "Fread_number: bad format.");
		AfxMessageBox( "If bad object, check for missing '~' in value[] fields.", 0 );
		return 0;
    }

    while ( isdigit(c) )
    {
		number = number * 10 + c - '0';
		c      = getc( fp );
    }

    if ( sign )
		number = 0 - number;

    if ( c == '|' )
		number += fread_number( fp, &stat );
    else if ( c != ' ' )
		ungetc( c, fp );

    return number;
}

/*
 * Read to end of line (for comments).
 */
void fread_to_eol( FILE *fp )
{
    int c;

    do
    {
		c = getc( fp );
    }
    while ( c != '\n' && c != '\r' && c != EOF );

    do
    {
		c = getc( fp );
    }
    while ( c == '\n' || c == '\r' );

    ungetc( c, fp );
    
	return;
}

/*
 * Read one word (into static buffer).
 */
CString fread_word( FILE *fp, int *status )
{
    static char  word[5024];
           char *pword;
           int   cEnd;

    *status = 0;

    do
    {
		cEnd = getc( fp );
    }
    while (isspace( cEnd ));

    if ( cEnd == '\'' || cEnd == '"' )
    {
		pword   = word;
    }
    else
    {
		word[0] = cEnd;
		pword   = word+1;
		cEnd    = ' ';
    }
	
    for (;pword < word + 5024; pword++ )
    {
		*pword = getc( fp );
		
		if ( cEnd == ' ' ? isspace( *pword ) : *pword == cEnd )
		{
			if ( cEnd == ' ' )
				ungetc( *pword, fp );
			*pword = '\0';
			return word;
		}
    }

    AfxMessageBox( "Fread_word: word too long.", 0 );
    *status = 1;
    
	return "\0";
}

CString fread_prog_string( FILE *fp, int *status )
{
    char  c;
    int count;
	
	CString str;

    count = 0;

    *status = 0;

    for ( ;; )
    {
        count++;
		switch ( c = getc( fp ) )
		{
			default:
				str += c;
			break;

			case EOF:
				*status = 1;
			return "";
			case '\n':
				return str;
			break;
		}
    }
}

CString fread_string( FILE *fp, int *status )
{
    char  c;
    int count;
	
	CString str;

    count = 0;

    *status = 0;

    do 
	{ 
		c = getc( fp ); 
	}
    while(isspace(c));

    if( ( str = c ) == '~' )
	{
		str = "";
        return str;
	}

    for ( ;; )
    {
        count++;
		switch ( c = getc( fp ) )
		{
			default:
				str += c;
			break;

			case EOF:
				*status = 1;
			return "";

			case '\n':
				str += "\r\n";
			break;

			case '\r':
			break;

			case '~':
				//remove extra return at end of text
				if(str[str.GetLength()-1] == '\n' || str[str.GetLength()-1] == '\r')
					str.SetAt(str.GetLength()-1, ' ');
				
				if(str[str.GetLength()-2] == '\n' || str[str.GetLength()-2] == '\r')
					str.SetAt(str.GetLength()-2, ' ');
				
				str.TrimRight();
			return str;
		}
    }
}

AreFileOpen::AreFileOpen() 
{

}

AreFileOpen::AreFileOpen(const char*dir, CWinDEDlg *par) : ZoneFile(par)
{
	CString word;
	int stat;

	if(Open(dir))
	{	
		SetProgRange(0, 10);
		SetProgPos(0);

		for ( ; ; )
		{
			if ( fread_letter( file ) != '#' )
			{
				AfxMessageBox( "Load_area: # not found.");
			}

			word = fread_word( file, &stat );

			if ( word[0] == '$')
				break;
			else if(word == "AREADATA" || word == "AREA")
			{
				SetProgText("Loading Area Data...");
				ReadAreaData(dir);
				Sleep(30);
				SetProgPos(++pos);
			}
			else if(word == "RECALL")
				break; 
			else if(word == "BASTMOBS")
			{
				SetProgText("Loading Mobiles...");
				LoadMobs();
				Sleep(30);
				SetProgPos(++pos);
			}
			else if(word == "MOBPROGS")
			{
				SetProgText("Loading Mobile Programs...");
				LoadProgs();
				Sleep(30);
				SetProgPos(++pos);
				break;
			}
			else if(word == "BASTRESETS")
			{
				SetProgText("Loading Reset Data...");
				LoadResets();
				Sleep(30);
				SetProgPos(++pos);
			}
			else if(word == "BASTSHOPS")
			{
				SetProgText("Loading Shops...");
				LoadShops();
				Sleep(30);
				SetProgPos(++pos);
			}
			else if(word == "SPECIALS")
			{
				SetProgText("Loading Specials...");
				LoadSpecials();
				Sleep(30);
				SetProgPos(++pos);
				break;
			}
			else if (word == "QUESTS")
			{
				SetProgText("Loading Quest Data...");
				LoadQuests();
				Sleep(30);
				SetProgPos(++pos);
				break;
			}
			else if(word == "BASTROOMS")
			{
				SetProgText("Loading Rooms...");
				LoadRooms();
				Sleep(30);
				SetProgPos(++pos);
			}
			else if(word == "BASTOBJECTS")
			{
				SetProgText("Loading Objects...");
				LoadObjects();
				Sleep(30);
				SetProgPos(++pos);
			}
			
			else
			{	
				AfxMessageBox( "Load_area: bad section name.");
			}
		}
		
		Close();
	}
	else 
	{
		AfxMessageBox("File was unable to open!");
	}
}

bool AreFileOpen::Open(const char*dir)
{	
	if((file = fopen(dir, "r")))
		return true;

	return false;
}

void AreFileOpen::Close()
{
	fclose(file);
}

void AreFileOpen::ReadAreaData(const char* dir)
{
	area_data::area = new area_data();
	area_data::area->path = dir;

	area_data::area->ReadArea(file);
}

void AreFileOpen::LoadSpecials()
{
	char letter;
	
	for (;;) 
	{	
		letter = fread_letter(file);

		if(letter == 'S')
			break;
		else
			fread_to_eol(file);
	}
}

void AreFileOpen::LoadQuests( )
{
	quest_data *qdata;
	quest_item *qitem;
	talk_data *message;
	mob_data *mob;
	CString str;
	
	bool exit_loop = FALSE;

	if (!area_data::area)
    {
		str.Format("Load_quests: no #AREA seen yet.");
		AfxMessageBox(str);
		return;
	}

	for (;;) 
	{
		char letter;
		int vnum;
		int stat;

		letter = fread_letter(file);
		if (letter != '#') 
		{
			str.Format("Load_quests: # not found.");
			AfxMessageBox(str);
		}

		vnum = fread_number(file, &stat);
		if (vnum == 0)
			break;

		mob = GetMobByVnum(vnum);

		mob->quests = new quest_index_data();

		mob->quests->vnum = vnum;

		exit_loop = FALSE;
		for (;!exit_loop;) 
		{
			letter = fread_letter(file);

			switch(letter) 
			{
				case 'M':
					if (!mob->quests) {
						str.Format("Error in load_quests:  message data seen before quest vnum.");
						AfxMessageBox(str);
					}
					
					message = new talk_data();
					message->keywords = fread_string(file, &stat);
					message->message = fread_string(file, &stat);
					message->next = mob->quests->messages;
					mob->quests->messages = message;

				break;
				case 'Q':

					if (!mob->quests) {
						str.Format("Error in load_quests:  quest data seen before quest vnum.");
						AfxMessageBox(str);
					}
				
					qdata = new quest_data();
					qdata->complete = fread_string(file, &stat);
					qdata->next = mob->quests->quests;
					mob->quests->quests = qdata;
				
				break;
				case 'R':
					if (!mob->quests) {
						str.Format("Error in load_quests:  receive (wants) item data seen before quest vnum.");
						AfxMessageBox(str);
					}
					if (!mob->quests->quests) {
						str.Format("Error in load_quests:  receive (wants) item data seen before quest data.");
						AfxMessageBox(str);
					}
				
					qitem = new quest_item();
					letter = fread_letter(file);
				
					switch (letter) {
					case 'I':
						qitem->type = 0;
					break;
					case 'C': // coins given to player
						qitem->type = 1;
					break;
					case 'S': // skill given to player
						qitem->type = 2;
					break;
					case 'E': // experience given to player
						qitem->type = 3;
					break;
					case 'G': // spell given to player
						qitem->type = 4;
					break;
					case 'K': // spell kast on player 
						qitem->type = 5;
					break;
					case 'T': // transfer mob(s) from room to here
						qitem->type = 6;
					break;
					case 'M': // create mob
						qitem->type = 7;
					break;
					case 'P': // create mob and make it player's pet
						qitem->type = 8;
					break;
					case 'R': // transfer player to room
						qitem->type = 9;
					break;
					case 'W': // transfer whole group of people to room
						qitem->type = 10;
					break;
					default:
						str.Format("Quest Item data:  Invalid Recieve type!");
						AfxMessageBox(str);
					break;
					}
				
					qitem->value = fread_number(file, &stat);
					qitem->next = mob->quests->quests->give;
					mob->quests->quests->give = qitem;
				
				break;
				
				case 'G':
					if (!mob->quests) {
						str.Format("Error in load_quests:  give (rewards) item data seen before quest vnum.");
						AfxMessageBox(str);
					}
					if (!mob->quests->quests) {
						str.Format("Error in load_quests:  give (rewards) item data seen before quest data.");
						AfxMessageBox(str);
					}
				
					qitem = new quest_item();
					letter = fread_letter(file);
					
					switch (letter) {
					case 'I':
						qitem->type = 0;
					break;
					case 'C':
						qitem->type = 1;
					break;
					case 'T':
						qitem->type = 2;
					break;
					default:
						str.Format("Quest Item data:  Invalid Give (rewards) type!", 0);
						AfxMessageBox(str);
					break;
					}
				
					qitem->value = fread_number(file, &stat);
					qitem->next = mob->quests->quests->receive;
					mob->quests->quests->receive= qitem;
				
				break;
				case 'S':
				// reset everything so we get proper error messages:
					exit_loop = TRUE;
				break;
			
				case 'D':
					if (!mob->quests) {
						str.Format("Error in load_quests:  disappear message seen before quest vnum.", 0);
						AfxMessageBox(str);
					}
					if (!mob->quests->quests) {
						str.Format("Error in load_quests:  disappear message seen before quest data.", 0);
						AfxMessageBox(str);
					}
				
					mob->quests->quests->disappear = fread_string(file, &stat);
				break;
				default:
				break;
			}
		}
	}
	return;
}

void AreFileOpen::LoadRooms( )
{
    room_data *room;
	CString str;

    if ( !area_data::area )
    {
        AfxMessageBox( "Load_rooms: no #AREA seen yet.");
    }

    for ( ; ; )
    {
        char letter;
        int  vnum;
        int  door;
        int  stat;

        letter = fread_letter( file );
        
		if ( letter != '#' )
        {
            AfxMessageBox( "Load_rooms: # not found.");
        }

        vnum = fread_number( file, &stat );

		if(room_data::room_hi_vnum < vnum)
			room_data::room_hi_vnum = vnum;

        if ( vnum == 0 )
            break;

		if(GetRoomByVnum(vnum))
        {
			str.Format("Load_rooms: vnum %d duplicated.", vnum);
            
			AfxMessageBox(str);
			
			vnum = GetValidVnum(ROOM);
        }
        room = new room_data();
        room->people              = NULL;
        room->contents            = NULL;
        room->first_extra_descr   = NULL;
		room->last_extra_desc	  = NULL;
        room->vnum                = vnum;

        room->name                = fread_string( file, &stat );
        room->description         = fread_string( file, &stat );
        room->room_flags[1]		  = fread_number( file, &stat ); /*Unused*/
        room->room_flags[0]       = fread_number( file, &stat );
        room->sector_type         = fread_number( file, &stat );
        room->light               = 0;
        
		

		for ( door = 0; door < MAX_DIR; door++ )
            room->exit[door] = NULL;

        for ( ; ; )
        {
            letter = fread_letter( file );

            if ( letter == 'S' || letter == 's' )
            {
                if ( letter == 's' )
				{
					str.Format("Load_rooms: vnum %d has lowercase 's'", vnum);
                    AfxMessageBox(str);	
				}
				
				break;
            }

            if ( letter == 'D' )
            {
                exit_data *pexit;
                int        locks;

                door = fread_number( file, &stat );
                if ( door < 0 || door >= MAX_DIR )
                {
					str.Format("Fread_rooms: vnum %d has bad door number.", vnum );
                    AfxMessageBox(str);
                }

                pexit                   = new exit_data;
                pexit->description      = fread_string( file, &stat );
                pexit->keyword          = fread_string( file, &stat );
                locks                   = fread_number( file, &stat );
                // convert exits - Veygoth
                switch( locks )
                {
                  case 0:
                    pexit->exit_info = 0;
                    break;
                  case 1:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED;
                    break;
                  case 2:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED;
                    break;
                  case 3:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_BASHPROOF | EX_PICKPROOF;
                    break;
                  case 4:
                    pexit->exit_info = EX_ISDOOR | EX_SECRET;
                    break;
                  case 5:
                    pexit->exit_info = EX_SECRET | EX_ISDOOR | EX_CLOSED;
                    break;
                  case 6:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_SECRET;
                    break;
                  case 7:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_BASHPROOF | EX_PICKPROOF |
                                       EX_SECRET;
                    break;
                  case 8:
                    pexit->exit_info = EX_BLOCKED;
                    break;
                  case 9:
                    pexit->exit_info = EX_BLOCKED | EX_ISDOOR | EX_CLOSED;
                    break;
                  case 10:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_BLOCKED;
                    break;
                  case 11:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_BASHPROOF | EX_PICKPROOF |
                                       EX_BLOCKED;
                    break;
                  case 12:
                    pexit->exit_info = EX_ISDOOR | EX_BLOCKED | EX_SECRET;
                    break;
                  case 13:
                    pexit->exit_info = EX_SECRET | EX_ISDOOR | EX_CLOSED |
                                       EX_BLOCKED;
                    break;
                  case 14:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_SECRET | EX_BLOCKED;
                    break;
                  case 15:
                    pexit->exit_info = EX_ISDOOR | EX_CLOSED | EX_LOCKED |
                                       EX_BASHPROOF | EX_PICKPROOF |
                                       EX_SECRET | EX_BLOCKED;
                    break;
                  default:
					str.Format("The MUD does not understand an exits value of %d.  Defaulting to generic closed door.", locks );
                    AfxMessageBox(str);
					pexit->exit_info = EX_ISDOOR;
                    break;
                };

                pexit->key              = fread_number( file, &stat );
                pexit->vnum             = fread_number( file, &stat );


                room->exit[door]          = pexit;
            }
            else if ( letter == 'E' )
            {
                extra_desc *ed;

                ed                      = new extra_desc();
                ed->keyword             = fread_string( file, &stat );
                ed->description         = fread_string( file, &stat );
                ed->next                = room->first_extra_descr;
                room->first_extra_descr = ed;
            }
            // Fall chance - Veygoth
            else if ( letter == 'F' )
            {
                room->fall_chance  = fread_number( file, &stat );
            }
            // Current not yet used, values discarded - Veygoth
            else if ( letter == 'C' )
            {
                room->current = fread_number( file, &stat );
                room->current_dir = fread_number( file, &stat );
            }
            // Mana not yet used, values discarded - Veygoth
            else if ( letter == 'M' )
            {
                fread_number( file, &stat );
                fread_number( file, &stat );
            }
            else
            {
				str.Format("Load_rooms: vnum %d has flag not 'DES'.", vnum );
                AfxMessageBox(str);
            }
        }

		room->AddToList();
    }

    return;
}

void AreFileOpen::LoadMobs()
{
	mob_data *mob;
    int count;
	CString str;

    if (!area_data::area)				/* OLC */
    {
        AfxMessageBox( "Load_mobiles: no #AREA seen yet.");
    }

    for ( ; ; )
    {
		CString race;
		char  letter;
		int   vnum;
		int   stat;

		letter				= fread_letter( file );
	
		if ( letter != '#' )
		{
			AfxMessageBox( "Load_mobiles: # not found.");
		}

		vnum				= fread_number( file, &stat );
	
		if(mob_data::high_mob_vnum < vnum)
			mob_data::high_mob_vnum = vnum;

		if ( vnum == 0 )
			break;

		if (GetMobByVnum(vnum))
		{
			str.Format("Load_mobiles: vnum %d duplicated.", vnum);
	    
			AfxMessageBox( str );
	    
			vnum = GetValidVnum(MOBILE);
		}

		mob					= new mob_data();
		mob->vnum			= vnum;

		mob->name			= fread_string( file, &stat );
		mob->short_descr	= fread_string( file, &stat );
		mob->long_descr		= fread_string( file, &stat );
		mob->description	= fread_string( file, &stat );

		mob->act					= fread_number( file, &stat ) | ACT_IS_NPC;
		mob->affected_by[0]			= fread_number( file, &stat );
		mob->affected_by[1]			= fread_number( file, &stat );
		mob->affected_by[2]			= fread_number( file, &stat );
		mob->affected_by[3]			= fread_number( file, &stat );
        
		// Set all other vectors to zero since this file format only has
        // two vectors - Veygoth
        if( NUM_AFFECT_VECTORS > 4 )
        {
           for( count = 2; count < NUM_AFFECT_VECTORS; count++ )
           {
                mob->affected_by[count] = 0;
           }
        }
	
		mob->shop			= NULL;
		mob->alignment		= fread_number( file, &stat );
		letter				= fread_letter( file );
        race                = fread_word( file, &stat );

	
		mob->race = GetRaceByKey(race);
		if ( mob->race < 0 )
		{
			str.Format("Load_mobiles: vnum %d bad race key %s", vnum, race );
            AfxMessageBox(str);
			mob->race = 0;
		}

        /* hometown not used */           fread_number( file, &stat );

        mob->c_class                = fread_number( file, &stat );
        // This class_convert will not be necessary if we add
        // classes in the same order as they are in DE.
        // It'll make us load a lil faster - Veygoth
        //mob->c_class = class_convert( mob->c_class );

		mob->level		= fread_number( file, &stat );
		
		/*
		 * The unused stuff is for imps who want to use the old-style
		 * stats-in-files method.
		 */
		fread_number( file, &stat );	/* Unused */
		fread_number( file, &stat );	/* Unused */
		fread_number( file, &stat );	/* Unused */
		
		fread_letter( file );		/* Unused */
		
		fread_number( file, &stat );	/* Unused */
		
		fread_letter( file );		/* Unused */
		fread_number( file, &stat );	/* Unused */
		
		fread_number( file, &stat );	/* Unused */
		
		fread_letter( file );		/* Unused */
		
		fread_number( file, &stat );	/* Unused */
		
		fread_letter( file );		/* Unused */
		
		fread_number( file, &stat );	/* Unused */
		
		fread_word( file, &stat );	/* Unused */
		
		fread_number( file, &stat );	/* Unused */
		fread_number( file, &stat );	/* Unused */
        fread_number( file, &stat );
		
		mob->sex		= fread_number( file, &stat );

		if ( letter != 'S' )
		{
			str.Format("Load_mobiles: vnum %d non-S.", vnum );
			AfxMessageBox(str);
		}

        letter = fread_letter( file );
        if ( letter == '>' )
        {
          ungetc( letter, file );
          //mprog_read_programs( file, mob );
        }
        else ungetc( letter,file );

		mob->AddToList();
    }

    return;
}

void AreFileOpen::LoadObjects()
{
	int count;
    object_data *obj;
	CString str;
	int af_loc = 0;

    if ( !area_data::area )
    {
        AfxMessageBox( "Load_objects: no #AREA seen yet.");
    }

    for ( ; ; )
    {
		char  letter;
		int   vnum;
		int   stat;

		letter				= fread_letter( file );
		if ( letter != '#' )
		{
			AfxMessageBox( "Load_objects: # not found.");
		}

		vnum				= fread_number( file, &stat );

		if(object_data::high_obj_vnum < vnum)
			object_data::high_obj_vnum = vnum;

		if ( vnum == 0 )
			break;

		if ( GetObjByVnum( vnum ) )
		{
			str.Format("Load_objects: vnum %d duplicated.", vnum );
			AfxMessageBox(str);

			vnum = GetValidVnum(OBJECT);
		}

		obj			= new object_data();
		obj->vnum	= vnum;

        for( count = 0; count < NUM_AFFECT_VECTORS; count++ )
        {
            obj->affected_by[count] = 0;
        }

		obj->name			= fread_string( file, &stat );
		obj->short_descr	= fread_string( file, &stat );
		obj->description	= fread_string( file, &stat );
		obj->dummy_str		= fread_string( file, &stat );

		obj->item_type		= fread_number( file, &stat );
        obj->material       = fread_number( file, &stat );
        
		if( obj->material >= MAX_MATERIAL )
        {
            str.Format("Object %d has material type beyond maximum allowable value.", vnum );
            AfxMessageBox(str);
        }
        
		obj->size                 = fread_number( file, &stat );
        obj->volume               = fread_number( file, &stat );
        obj->craftsmanship        = fread_number( file, &stat );
        // Damage resistance bonus not used, may not be - Veygoth
        obj->dummy				  = fread_number( file, &stat );
		obj->extra_flags[0]		  = fread_number( file, &stat );
		obj->wear_flags			  = fread_number( file, &stat );
		obj->extra_flags[1]		  = fread_number( file, &stat );
        obj->anti_flags[0]        = fread_number( file, &stat );
        obj->anti_flags[1]        = fread_number( file, &stat );
		obj->value[0]             = fread_number( file, &stat );
		obj->value[1]             = fread_number( file, &stat );
		obj->value[2]             = fread_number( file, &stat );
		obj->value[3]             = fread_number( file, &stat );
		obj->value[4]             = fread_number( file, &stat );
		obj->value[5]             = fread_number( file, &stat );
		obj->value[6]             = fread_number( file, &stat );
		obj->value[7]             = fread_number( file, &stat );
		obj->weight				  = fread_number( file, &stat );
									fread_number( file, &stat );
        //obj->trap                 = NULL;
        obj->condition            = fread_number( file, &stat );

        if( obj->item_type == TYPE_WEAPON && obj->value[3] == 0 )
		{
			str.Format("Object vnum %d: object type weapon with no damage type specified", vnum );
            AfxMessageBox(str); 
		}
	    
		for ( ; ; )
		{
			char letter;
	
			letter = fread_letter( file );

			if ( letter == 'A' )
			{
				obj->applies[af_loc].loc = fread_number(file, &stat);
				obj->applies[af_loc].value = fread_number(file, &stat);

				af_loc++;

				if(af_loc == 2)
					af_loc = 0;
			}

			else if ( letter == 'E' )
			{
				extra_desc *ed;

				ed					= new extra_desc;
				ed->keyword			= fread_string( file, &stat );
				ed->description		= fread_string( file, &stat );
				ed->next			= obj->first_extra_descr;
				obj->first_extra_descr	= ed;
			}

            else if( letter == 'T' )
            {
                //obj->trap = new trap_data;
                
				obj->trap.trigger = fread_number( file, &stat );
                obj->trap.damage = fread_number( file, &stat );

				obj->trap.charges = fread_number( file, &stat );
                obj->trap.level = fread_number( file, &stat );

                obj->trap.percent = 100; // fread_number( file, &stat );
            }

			else if( letter == '#' )
			{	
				ungetc( letter, file );
				break;
			}
			else
			{
					// Currently ignoring affect bits on objects - Veygoth
				ungetc( letter, file );
                obj->affected_by[0] = fread_number( file, &stat );
                obj->affected_by[1] = fread_number( file, &stat );
                obj->affected_by[2] = fread_number( file, &stat );
                obj->affected_by[3] = fread_number( file, &stat );
			}
		}

		obj->AddToList();
    }

    return;
}

void AreFileOpen::LoadResets()
{
    reset_data *pReset = NULL;
    int         iLastRoom = 0;
    int         iLastObj  = 0;
	int			iLastMob  = 0;
    int			stat;
	CString		str;
	obj_index	*olast;
	

    if(!area_data::area)
    {
		AfxMessageBox("Load_resets: no #AREA seen yet.");
    }

    // Ignore all Basternae area header stuff...
	area_data::area->dummy_str[0] = fread_word(file, &stat);
    area_data::area->dummy_str[1] = fread_string(file, &stat);
    
	area_data::area->dummy[0] = fread_number(file, &stat);    
    area_data::area->dummy[1] =fread_number(file, &stat);    
    area_data::area->dummy[2] =fread_number(file, &stat);    
    area_data::area->dummy[3] =fread_number(file, &stat);    
    area_data::area->dummy[4] =fread_number(file, &stat);    
    area_data::area->dummy[5] =fread_number(file, &stat);    

    for(;;)
    {
		//exit_data       *pexit;
		room_data		*room;
		mob_data		*mob;
		object_data		*obj;
		char            letter;

		if((letter = fread_letter( file ) ) == 'S')
			break;

		if(letter == '*')
		{
			fread_to_eol(file);
			continue;
		}

		pReset			= new reset_data;
		pReset->command	= letter;
		/* if_flag 	  fread_number( file, &stat ); */
		pReset->arg0	= fread_number(file, &stat);
		pReset->arg1	= fread_number(file, &stat);
		pReset->arg2	= fread_number(file, &stat);
		pReset->arg3	= fread_number(file, &stat);
		pReset->arg4    = fread_number(file, &stat);
		pReset->arg5	= fread_number(file, &stat);
		pReset->arg6	= fread_number(file, &stat);
		pReset->arg7	= fread_number(file, &stat);
	
		fread_to_eol( file );

		/*
		 * Validate parameters.
		 * We're calling the index functions for the side effect.
		 */
		switch(letter)
		{
			default:
				str.Format("Load_resets: bad command '%c'.", letter);
				AfxMessageBox(str); 
			break;

			case 'M'://regular mob
				mob = GetMobByVnum(pReset->arg1);
				if((room = GetRoomByVnum(pReset->arg3)))
				{
					room->AddPerson(mob);
					iLastRoom = pReset->arg3;
					iLastMob = pReset->arg1;
				}
            break;

			case 'F'://following 
				mob = GetMobByVnum(pReset->arg1);
				if((room = GetRoomByVnum( pReset->arg3)))
				{
				   room->AddPerson(mob);
				   iLastRoom = pReset->arg3;
				}
            break;

			case 'O': //regular object
				obj = GetObjByVnum(pReset->arg1);
				if((room = GetRoomByVnum(pReset->arg3)))
				{
				   olast = room->AddContent(obj);
				   iLastObj = pReset->arg3;
				}
            break;

			case 'P': //put object in object
				obj = GetObjByVnum(pReset->arg1);
				if((room = GetRoomByVnum( iLastObj)))
				{	
					if(olast)
						olast->AddContent(obj);
				}
            break;

         case 'E': //equip item on mob
            if((room = GetRoomByVnum(iLastRoom)))
            {
				mob_index *m_index = NULL;
				
				obj = GetObjByVnum(pReset->arg1);
				
				for(m_index = room->people; m_index; m_index = m_index->next)
				{
					if(m_index)
					{
						if(m_index->vnum == iLastMob)
							m_index->EquipObj(obj, pReset->arg3);
					}
				}

                iLastObj = iLastRoom;
            }
            break;
         case 'G': //give item mob   
			obj = GetObjByVnum(pReset->arg1);
            if((room = GetRoomByVnum(iLastRoom)))
            {

				mob_index *m_index = NULL;

				for(m_index = room->people; m_index; m_index = m_index->next)
				{
					if(m_index->vnum == iLastMob)
						m_index->AddObjToInv(obj);
				}

                iLastObj = iLastRoom;
            }
            break;

        case 'D'://door not needed
            /*room = GetRoomByVnum(pReset->arg1);

            if(!room)
               AfxMessageBox("Nonexistant room index for door.");

            if(pReset->arg2 < 0
                || pReset->arg2 >= MAX_DIR
                || !room
                || !(pexit = room->exit[pReset->arg2]))
            {
				str.Format("Load_resets: 'D' exit %d not door.", pReset->arg2 );
                AfxMessageBox(str); 
            }*/
            break;

        case 'R'://rider
			if(pReset->arg0 == 1)
			{ // If this is a ridden mob ..
					mob = GetMobByVnum(pReset->arg1);
					if((room = GetRoomByVnum(pReset->arg3)))
					{
					    room->AddPerson(mob);
					    iLastRoom = pReset->arg3;
					}
					else
					{
						str.Format("Ridden mob not loaded: No room %d.", pReset->arg3);
						AfxMessageBox(str);
					}
			}
			else
			{ // Otherwise ..
                if(pReset->arg2 < 0 || pReset->arg2 > MAX_DIR) /* Last Door. */
            	{
					str.Format("Load_resets: 'R' bad exit %d.", pReset->arg2 );
                    AfxMessageBox(str); 
            	}
			}
            break;
		}

		if(pReset)
		{
			delete pReset;
			pReset = NULL;
		}
    }

    return;
}

void AreFileOpen::LoadShops()
{
    shop_data *pShop;
    int        keeper = 0;

    for ( ; ; )
    {
		mob_data	*mob;
		int             iTrade;
		int             stat;
        char            letter;
        int             count;

        letter = fread_letter( file );
        
		if( letter != '#' )
        {
            AfxMessageBox( "Load shops: # not found before vnum");
        }
        
		keeper = fread_number( file, &stat );
        
		letter = fread_letter( file );
        if( letter != '~' )
        {
            AfxMessageBox( "Load shops: ~ not found after vnum");
        }
        
		letter                  = fread_letter( file );
        if( letter == 'S' )
           return;
        else if( letter != 'N' )
        {
           AfxMessageBox( "Shop section: Letter 'N' not found after shop vnum");
        }
		
		if ( keeper == 0 )
			break;
		
		pShop				= new shop_data();
		pShop->keeper		= keeper;
        
		for( count = 0; count < MAX_SELL; count++ )
        {
           pShop->sell_item[count] = fread_number( file, &stat );
           if( pShop->sell_item[count] == 0)
               break;
        }

		pShop->profit_sell	= fread_number( file, &stat ) * 100;
        
		letter = fread_letter( file );
        if( letter != '.' )
           AfxMessageBox( "Expecting decimal point in shop profit_sell value", 0);
        
		pShop->profit_sell       += fread_number( file, &stat );

		pShop->profit_buy	= fread_number( file, &stat ) * 100;
        
		letter = fread_letter( file );
        if( letter != '.' )
           AfxMessageBox( "Expecting decimal point in shop profit_buy value", 0);
        
		pShop->profit_buy       += fread_number( file, &stat );

		for ( iTrade = 0; iTrade < MAX_BUY; iTrade++ )
        {
			pShop->buy_type[iTrade] = fread_number( file, &stat );
            if( pShop->buy_type[iTrade] == 0 )
               break;
        }
        
		for(int i = 0; i < 7; i++)
		{
			pShop->shop_string[i] = fread_string( file, &stat );
		}

        // discard two numbers
        pShop->dummy[0] = fread_number( file, &stat );
        pShop->dummy[1] = fread_number( file, &stat );

		pShop->dummy[2] = fread_number( file, &stat );
        pShop->dummy[3] = fread_number( file, &stat );
       
		// room vnum of shop discarded
        pShop->dummy[4] = fread_number( file, &stat );
		
		pShop->open_hour	= fread_number( file, &stat );
		pShop->close_hour	= fread_number( file, &stat );
        
		// discard second open and close times
        pShop->dummy[5] = fread_number( file, &stat);
        pShop->dummy[6] = fread_number( file, &stat);
        
		// discard racist, roam, and killable flags
        pShop->dummy_char[0] = fread_letter( file );
        pShop->dummy_char[1] = fread_letter( file );
        pShop->dummy_char[2] = fread_letter( file );
        
		// discard open and close messages
        pShop->dummy_str[0] = fread_string( file, &stat );
        pShop->dummy_str[1] = fread_string( file, &stat );
        
		// discard the rest of the junk
        pShop->dummy[7]			= fread_number( file, &stat );
        pShop->dummy[8]			= fread_number( file, &stat );
        
		pShop->dummy_char[3]	= fread_letter( file );
        
		pShop->dummy[9]			= fread_number( file, &stat );
        
		pShop->dummy_str[2]		= fread_string( file, &stat );
        // end of the shop
        
		letter = fread_letter( file );
        if( letter != 'X')
        {
           AfxMessageBox( "Letter 'X' not found at end of shop section", 0 );
        }
	
		fread_to_eol( file );
	
		mob			= GetMobByVnum( pShop->keeper );
		mob->shop	= pShop;

		pShop->AddToList();
    }

    return;
}

void AreFileSave::Write(char *str, ...)
{
	va_list args;

	va_start(args, str);
	vfprintf(file, str, args);
	va_end(args);	
}

void AreFileSave::Write(CString &str)
{
	fprintf(file, str);
}

void AreFileSave::Write(int &i)
{
	fprintf(file, "%d", i);
}

void AreFileSave::Write(float &i)
{
	fprintf(file, "%f", i);
}

void AreFileSave::WriteMobiles()
{
	SetProgText("Saving Mobiles...");
	
	Write("#BASTMOBS\n\n");
	
	for(mob_data *mob = mob_data::first_mob; mob; mob = mob->next)
	{
		WriteMob(mob);
		SetProgPos(++pos);
	}

	Write("#0\n\n");
}

void AreFileSave::WriteMob(mob_data *mob)
{
	Write("#%d\n",mob->vnum);
	Write("%s\n~\n",mob->name);
	Write("%s~\n",mob->short_descr);
	Write("%s\n~\n",mob->long_descr);
	Write("%s\n~\n",mob->description);

	Write("%d\t%d %d %d %d\t%d S\n",
		mob->act,mob->affected_by[0],mob->affected_by[1],mob->affected_by[2],mob->affected_by[3],mob->alignment);

	Write("%s\t%d %d\n",GetRaceKey(mob->race),0,mob->c_class );
	Write("%d\t 0 0 1d1+1 1d1+1\n",mob->level);
	Write("0.0.0.0 0\n");
	Write("%d 0 %d\n",mob->position, mob->sex);
}

void AreFileSave::WriteObjects()
{
	SetProgText("Saving Objects...");
	
	Write("#BASTOBJECTS\n\n");

	for(object_data *obj = object_data::obj_head; obj; obj = obj->next)
	{
		WriteObj(obj);
		SetProgPos(++pos);
	}

	Write("#0\n\n");
}

void AreFileSave::WriteObj(object_data *obj)
{
	Write("#%d\n",obj->vnum);
	Write("%s~\n",obj->name);
	Write("%s~\n",obj->short_descr);
	Write("%s~\n",obj->description);
	Write("~\n"); // Action Description

	Write("%d %d %d %d %d %d %d %d %d %d %d\n",
		obj->item_type,
		obj->material,
		obj->size,
		obj->volume,
		obj->craftsmanship,
		obj->extra_flags[2],
		obj->extra_flags[0],
		obj->wear_flags,
		obj->extra_flags[1],
		obj->anti_flags[0],
		obj->anti_flags[1]);

	Write("%d %d %d %d %d %d %d %d\n",
		obj->value[0], obj->value[1], obj->value[2],	obj->value[3],
		obj->value[4], obj->value[5],	obj->value[6],	obj->value[7]);


	Write("%d %d %d %d %d %d %d\n",
		obj->weight, 0, obj->condition,
		obj->affected_by[0],
		obj->affected_by[1],
		obj->affected_by[2],
		obj->affected_by[3]
		);

	for (extra_desc *extras = obj->first_extra_descr; extras; extras = extras->next)
		Write("E\n%s~\n%s~\n",extras->keyword,extras->description);
	
	Write("A\n%i %i\n",obj->applies[0].loc,obj->applies[0].value);
	Write("A\n%i %i\n",obj->applies[1].loc,obj->applies[1].value);

	if(obj->trap.damage > 0)
		Write("T\n%d %d %d %d\n",
		obj->trap.trigger,
		obj->trap.damage,
		obj->trap.charges,
		obj->trap.level/*,
		obj->trap.percent*/);
}

void AreFileSave::WriteRooms()
{
	SetProgText("Saving Rooms...");
	
	Write("#BASTROOMS\n\n");

	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		WriteRoom(room);
		SetProgPos(++pos);
	}
	
	Write("#0\n\n");
}

void AreFileSave::WriteRoom(room_data *room)
{
	int x;

	Write("#%d\n",room->vnum);
	Write("%s\n~\n",room->name);
	Write("%s\n~\n",room->description);
	Write("%d\t%d\t%d\n",
		room->room_flags[1],
		room->room_flags[0],
		room->sector_type);

	// Save Exit Information			
	for (int door = 0; door < MAX_DIR; door++)
		if(room->exit[door])
		{
			Write("D%i\n",door);
			Write("%s\n~\n",room->exit[door]->description);
			Write("%s\n~\n",room->exit[door]->keyword);

			if(room->exit[door]->exit_info == 0)
					x = 0;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED))
					x = 1;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED))
					x = 2;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF))
					x = 3;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_SECRET))
					x = 4;
				else if(IS_SET(room->exit[door]->exit_info, EX_SECRET | EX_ISDOOR | EX_CLOSED))
					x = 5;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_SECRET))
					x = 6;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF |EX_SECRET))
					x = 7;
				else if(IS_SET(room->exit[door]->exit_info, EX_BLOCKED))
					x = 8;
				else if(IS_SET(room->exit[door]->exit_info, EX_BLOCKED | EX_ISDOOR | EX_CLOSED))
					x = 9;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BLOCKED))
					x = 10;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF | EX_BLOCKED))
					x = 11;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_BLOCKED | EX_SECRET))
					x = 12;
				else if(IS_SET(room->exit[door]->exit_info, EX_SECRET | EX_ISDOOR | EX_CLOSED | EX_BLOCKED))
					x = 13;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_SECRET | EX_BLOCKED))
					x = 14;
				else if(IS_SET(room->exit[door]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF | EX_SECRET | EX_BLOCKED))
					x = 15;
				else x = 0;

			Write("%d %d %d\n",
				x,
				room->exit[door]->key,
				room->exit[door]->vnum);
		}

	// Save Extra Desriptions
	for (extra_desc *extras = room->first_extra_descr; extras; extras = extras->next)
		Write("E\n%s~\n%s\n~\n",extras->keyword,extras->description);

	// Save Fall Chance
	if(room->fall_chance)
		Write("F\n%d\n",room->fall_chance);

	if(room->current)
		Write("C\n%d %d\n",room->current,room->current_dir);


	Write("S\n\n");
}

void AreFileSave::WriteShops()
{
	
	SetProgText("Saving Shops...");

	if(shop_count > 0)
	{
		Write("#BASTSHOPS\n\n");

		for(mob_data *mob = mob_data::first_mob; mob; mob = mob->next)
		{	
			if(mob->shop)
			{
				WriteShop(mob->shop);
				SetProgPos(++pos);
			}
		}	

		Write("#0~\nS\n\n");
	}
}

void AreFileSave::WriteShop(shop_data *shop)
{
	Write("#%i~\n",shop->keeper);
	Write("N\n");
	
	for (int count = 0; count < MAX_SELL; count++) 
	{
		if(shop->sell_item[count] > 0) 
			Write("%i\n",shop->sell_item[count]);
	}
	
	Write("0\n");
	Write("%1.2f\n%1.2f\n",((float)shop->profit_sell / 100),((float)shop->profit_buy/100));
	
	for(int iTrade = 0; iTrade < MAX_BUY; iTrade++)
	{
		if(shop->buy_type[iTrade] >0 )
			Write("%i\n",shop->buy_type[iTrade]);
	}
	
	Write("0\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("0\n0\n0\n0\n0\n");
	Write("%i\n%i\n",shop->open_hour,shop->close_hour);
	Write("0\n0\nN\nN\nN\n");
	Write("Blank~\n");
	Write("Blank~\n");
	Write("0\n0\nN\n0\n~\n");
	Write("X\n");
}

void AreFileSave::WriteQuests()
{	
	quest_data *quest;
	talk_data *clue;

	SetProgText("Saving Quests...");
	if(quest_count > 0)
	{
		Write("#QUESTS\n\n");

		for(mob_data *mob = mob_data::first_mob; mob; mob = mob->next)
		{
			if(mob->quests)
			{
				Write("#%i\n", mob->vnum);

				for(quest = mob->quests->quests; quest; quest = quest->next)
				{
					WriteQuest(quest);
					SetProgPos(++pos);
				}
				
				for(clue = mob->quests->messages; clue; clue = clue->next)
				{
					WriteQuest(clue);
					SetProgPos(++pos);
				}
			
				Write("S\n");
			}
		}

		Write("#0\n\n");
	}
}

void AreFileSave::WriteQuest(quest_data *quest)
{
	static char wants_types [] = {'I','C','T' };
	static char rewards_types [] = {'I','C','S','E','G','K','T','M','P','R','W' };
	
	Write("Q\n");
	Write("%s~\n",quest->complete);

	for(quest_item *r = quest->receive;r;r=r->next) 
	{
		Write("G %c %i\n",wants_types[r->type], r->value);
	}
	
	for(quest_item *g = quest->give;g;g=g->next) 
	{
		Write("R %c %i\n",rewards_types[g->type], g->value);
	}
	
	if (quest->disappear) 
	{ 
		Write("D\n");
		Write("%s~\n",quest->disappear);
	}	
}

void AreFileSave::WriteQuest(talk_data *quest)
{
	Write("M\n%s~\n%s~\n",quest->keywords,quest->message);
}

AreFileSave::AreFileSave(const char *dir, CWinDEDlg *par) : ZoneFile(par)
{
	CString str;
	str = dir;

	if(str.Right(4) != ".are")
		str += ".are";

	if(Open(str))
	{
		SetProgRange(0, mob_count + obj_count + room_count + shop_count + quest_count);
		
		SetProgPos(0);
		
		WriteArea();
		WriteRooms();
		WriteMobiles();
		WriteObjects();
		WriteResets();
		WriteShops();
		WriteQuests();
		WriteProgs();
	
		Close();
		
		CloseProg();
	}
}

void AreFileOpen::LoadProgs()
{
	for ( ; ; )
    {
		ProgFile	*prog;
		FILE *fp;
		int vnum;
		char letter;
		int stat;
        
		letter = fread_letter( file );
        
		prog = new ProgFile();

		if(letter == 'M')
		{
			prog->type = MOBILE;
			vnum = fread_number(file, &stat);

			prog->mob = GetMobByVnum(vnum);

			if(!prog->mob)
			{
				delete prog;
				continue;
			}
		}
		else if(letter == 'O')
		{
			prog->type = OBJECT;
			vnum = fread_number(file, &stat);

			prog->obj = GetObjByVnum(vnum);

			if(!prog->obj)
			{
				delete prog;
				continue;
			}
		}
		else if(letter == 'S')
			return;
		else
		{
			delete prog;
			fread_to_eol(file);
			continue;
		}
		
		prog->filename = fread_prog_string(file, &stat);

		if((fp = fopen("./Progs/"+prog->filename, "r")))
		{
			while(!feof(fp))
			{
				prog->prog_text += fread_prog_string(fp, &stat);
				prog->prog_text += '\n';
			}
		}
			
		area_data::area->progs.AddProg(prog);
    }
}

void AreFileSave::WriteProgs()
{
	ProgFile *prog;
	FILE *fp;

	CreateDirectory("./Progs/", NULL);
	
	Write("#MOBPROGS\n");

	for(prog = area_data::area->progs.first; prog; prog = prog->next)
	{
		if(prog->prog_text.GetLength() <= 0 || prog->prog_text.IsEmpty())
			continue;

		if(prog->type == MOBILE)
		{
			Write("M ");
			Write(prog->mob->vnum);
			Write(" ");
			Write(prog->filename);
			Write("\n");
		}
		else if(prog->type == OBJECT)
		{
			Write("O ");
			Write(prog->obj->vnum);
			Write(" ");
			Write(prog->filename);
			Write("\n");
		}

		if(fp = fopen("./Progs/" + prog->filename, "w"))
			fprintf(fp, prog->prog_text);
	}

	Write("S\n");
}

bool AreFileSave::Open(const char *dir)
{
	if((file = fopen(dir, "w")))
		return true;

	return false;
}

void AreFileSave::Close()
{
	Write("#$\n");
	fclose(file);
}

AreFileSave::~AreFileSave()
{
	Close();
}

void AreFileSave::WriteResets()
{
	Write("#BASTRESETS\n");
	Write("#0\n%s~\n0 %i 0 %i %i 0\n", area_data::area->name, area_data::area->resetmode, area_data::area->llifespan, area_data::area->ulifespan);
		
	SaveExitResets();
	Write("*\n");
	
	SaveObjectResets();
	Write("*\n");
	
	SaveMobileResets();
	Write("*\n");
	
	Write("S\n\n");
}

void AreFileSave::SaveExitResets()
{
	int x;

	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		for(int i = DIR_NORTH; i < MAX_DIR; i++)
		{
			if(room->exit[i] && IS_SET(room->exit[i]->exit_info, EX_ISDOOR))
			{
				if(room->exit[i]->exit_info == 0)
					x = 0;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED))
					x = 1;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED))
					x = 2;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF))
					x = 3;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_SECRET))
					x = 4;
				else if(IS_SET(room->exit[i]->exit_info, EX_SECRET | EX_ISDOOR | EX_CLOSED))
					x = 5;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_SECRET))
					x = 6;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF |EX_SECRET))
					x = 7;
				else if(IS_SET(room->exit[i]->exit_info, EX_BLOCKED))
					x = 8;
				else if(IS_SET(room->exit[i]->exit_info, EX_BLOCKED | EX_ISDOOR | EX_CLOSED))
					x = 9;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BLOCKED))
					x = 10;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF | EX_BLOCKED))
					x = 11;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_BLOCKED | EX_SECRET))
					x = 12;
				else if(IS_SET(room->exit[i]->exit_info, EX_SECRET | EX_ISDOOR | EX_CLOSED | EX_BLOCKED))
					x = 13;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_SECRET | EX_BLOCKED))
					x = 14;
				else if(IS_SET(room->exit[i]->exit_info, EX_ISDOOR | EX_CLOSED | EX_LOCKED | EX_BASHPROOF | EX_PICKPROOF | EX_SECRET | EX_BLOCKED))
					x = 15;
				else x = 0;

				Write("D 0 %d %d %d 100 0 0 0\n", room->exit[i]->vnum, i, x);
			}
		}
	}
}

void AreFileSave::SaveMobileResets()
{	
	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		for(mob_index *mob = room->people; mob; mob = mob->next)
		{
			Write("M %d %d 1 %d 100 0 0 0\n", mob->mob->load_limit, mob->vnum, room->vnum);
			
			for(obj_index *obj = mob->inventory; obj; obj = obj->next)
				Write("G 1 %d 1 %d 100 0 0 0\n", obj->vnum, mob->vnum);
			
			for(int i = WEAR_NONE; i < MAX_WEAR; i++)
			{
				if(mob->eq[i])
					Write("E 0 %d 1 %d 100 0 0 0\n", mob->eq[i]->vnum, i);
			}

			for(mob_index *fol =  mob->follower; fol; fol = fol->next_in_group)
				Write("F %d %d 1 %d 100 0 0 0\n", mob->mob->load_limit, fol->vnum, mob->vnum);

			if(mob->rider)
				Write("M %d %d 1 %d 100 0 0 0\n", mob->mob->load_limit, mob->rider->vnum, room->vnum );
		}
	}
}

void AreFileSave::SaveObjectResets()
{
	for(room_data *room = room_data::room_list; room; room = room->next)
	{
		for(obj_index *obj = room->contents; obj; obj = obj->next)
		{
			Write("O 1 %d 1 %d 100 0 0 0\n", obj->vnum, room->vnum);
			
			for(obj_index *inv = obj->contents; inv; inv = inv->next)
				Write("P 1 %d 1 %d 100 0 0 0\n", inv->vnum, obj->vnum);
		}
	}
}

void AreFileSave::WriteArea()
{
	area_data *area = area_data::area;

	Write("#AREADATA\n");

	Write("Name %s~\n",area->name);
	Write("Author %s~\n",area->author);
	Write("Levels %d %d\n",area->llv,area->ulv);
	Write("Security %d\n",area->security);
	Write("VNUMs %d %d\n",area->lvnum,area->uvnum);
	
	Write("Builders %s~\n",area->builders);
	Write("ClanId %d\n",area->clan_id);
	Write("AreaFlags %d\n",area->area_flags);

	Write("Justice %d\n",area->justice);
	Write("Judge %d\n",area->judge);
	Write("Jail %d\n",area->jail);
	Write("Squads %d\n",area->squads);
	Write("Nodim %d\n",area->nodim);
	Write("Barracks %d\n",area->barracks);
	Write("Defender %d %d\n",area->defender,area->defender_num);
	Write("Recall %d\n",area->recall);
	Write("Reset %s~\n",area->resetmsg);

	Write("End\n\n");
	SetProgPos(++pos);
}

