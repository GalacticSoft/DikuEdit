#include "StdAfx.h"

room_data *room_data::room_list = NULL;
room_data *room_data::room_last = NULL;
room_data *room_data::def_room = NULL;              

int room_data::room_hi_vnum = 1;

const char room_data::class_name[] = "room_data";
const int  room_data::class_index = ROOM_DATA;


char exit_data::class_name[] = "exit_data";
int  exit_data::class_index = EXIT_DATA;

char RoomFlags::class_name[] = "RoomFlags";
int  RoomFlags::class_index = ROOM_FLAGS;

char extra_desc::class_name[] = "extra_desc";
int  extra_desc::class_index = EXTRA_DESC;

const BITVECT_DATA ROOM_NONE 					= {0,    0};
const BITVECT_DATA ROOM_DARK                    = {0, BV00};
const BITVECT_DATA ROOM_LIMITSCAN               = {0, BV01};
const BITVECT_DATA ROOM_NO_MOB                  = {0, BV02};
const BITVECT_DATA ROOM_INDOORS                 = {0, BV03};
const BITVECT_DATA ROOM_SILENT                  = {0, BV04};
const BITVECT_DATA ROOM_UNDERWATER              = {0, BV05}; 
const BITVECT_DATA ROOM_NO_RECALL               = {0, BV06};
const BITVECT_DATA ROOM_NO_MAGIC                = {0, BV07};
const BITVECT_DATA ROOM_TUNNEL                  = {0, BV08};
const BITVECT_DATA ROOM_PRIVATE                 = {0, BV09};
const BITVECT_DATA ROOM_NOCAMP					= {0, BV10};
const BITVECT_DATA ROOM_SAFE                    = {0, BV11};
const BITVECT_DATA ROOM_NO_PRECIP               = {0, BV12};
const BITVECT_DATA ROOM_SINGLE_FILE             = {0, BV13};
const BITVECT_DATA ROOM_JAIL                    = {0, BV14};
const BITVECT_DATA ROOM_NO_TELEPORT             = {0, BV15};
const BITVECT_DATA ROOM_SOLITARY                = {0, BV16};
const BITVECT_DATA ROOM_HEAL                    = {0, BV17}; 
const BITVECT_DATA ROOM_NO_HEAL                 = {0, BV18};
const BITVECT_DATA ROOM_INN                     = {0, BV19};
const BITVECT_DATA ROOM_DOCKABLE                = {0, BV20};
const BITVECT_DATA ROOM_MAGICDARK               = {0, BV21};
const BITVECT_DATA ROOM_MAGICLIGHT              = {0, BV22};
const BITVECT_DATA ROOM_NO_SUMMON               = {0, BV23};
const BITVECT_DATA ROOM_GUILDROOM               = {0, BV24};
const BITVECT_DATA ROOM_TWILIGHT                = {0, BV25};
const BITVECT_DATA ROOM_NO_PSIONICS             = {0, BV26};
const BITVECT_DATA ROOM_NO_GATE                 = {0, BV27};
const BITVECT_DATA ROOM_BANK                    = {0, BV28};
const BITVECT_DATA ROOM_PET_SHOP                = {0, BV29};
const BITVECT_DATA ROOM_NO_SCAN                 = {0, BV30};

const BITVECT_DATA ROOM_EARTHEN_STARSHELL       = {1, BV00};
const BITVECT_DATA ROOM_AIRY_STARSHELL          = {1, BV01};
const BITVECT_DATA ROOM_FIERY_STARSHELL         = {1, BV02};
const BITVECT_DATA ROOM_WATERY_STARSHELL        = {1, BV03};
const BITVECT_DATA ROOM_HYPNOTIC_PATTERN        = {1, BV04};
const BITVECT_DATA ROOM_ARENA                   = {1, BV05};
const BITVECT_DATA ROOM_TREASUREROOM            = {1, BV06};

RoomFlags room_flags_info[] = {
	{IDC_DARK,         &ROOM_DARK,		"&+LDark&n"},
	{IDC_LIMITSCAN,    &ROOM_LIMITSCAN, "Limit Scan"},
	{IDC_SAFE,         &ROOM_SAFE,		"&+WSafe&n"},
	{IDC_NO_MOB,       &ROOM_NO_MOB,	"&nNo Mob"},
	{IDC_INDOORS,      &ROOM_INDOORS,	"&+yIndoors&n"},
	{IDC_SILENT,       &ROOM_SILENT,	"&+wSilent&n"},
	{IDC_UNDERWATER,   &ROOM_UNDERWATER,"&+BUnderwater&n"},
	{IDC_NO_RECALL,    &ROOM_NO_RECALL, "&nNo Recall"},
	{IDC_NO_MAGIC,     &ROOM_NO_MAGIC,	"&+bNo Magic&n"},
	{IDC_TUNNEL,       &ROOM_TUNNEL,	"&+LTunnel&n"},
	{IDC_PRIVATE,      &ROOM_PRIVATE,	"&nPrivate"},
	{IDC_NOCAMP,       &ROOM_NOCAMP,	"&nNo Camp"},
	{IDC_NO_PRECIP,    &ROOM_NO_PRECIP, "&+bNo Precipitation&n"},
	{IDC_JAIL,         &ROOM_JAIL,		"&+WJ&+La&+Wi&+Ll&n"},
	{IDC_NO_TELEPORT,  &ROOM_NO_TELEPORT,"&nNo Teleport"},
	{IDC_SOLITARY,     &ROOM_SOLITARY,	"&nSolitary"},
	{IDC_HEAL,         &ROOM_HEAL,		"&+WHeal&n"},
	{IDC_NO_GATE,      &ROOM_NO_GATE,	"&+GNo Gate&n"},
	{IDC_NO_HEAL,      &ROOM_NO_HEAL,	"&+rNo Heal&n"},
	{IDC_INN,          &ROOM_INN,		"&nInn"},
	{IDC_DOCKABLE,     &ROOM_DOCKABLE,	"&+yDockable&n"},
	{IDC_MAGICDARK,    &ROOM_MAGICDARK, "&+LMagic Dark&n"},
	{IDC_MAGICLIGHT,   &ROOM_MAGICLIGHT,"&+YMagic Light&n"},
	{IDC_NOSUMMON,     &ROOM_NO_SUMMON, "&nNo Summon"},
	{IDC_GUILDROOM,    &ROOM_GUILDROOM, "&+gGuild Room&n"},
	{IDC_TWILIGHT,     &ROOM_TWILIGHT,  "&+cTwilight&n"},
	{IDC_NO_PSIONICS,  &ROOM_NO_PSIONICS, "&+mNo Psionics"},
	{IDC_BANK,         &ROOM_BANK,		"&nBank"},
	{IDC_PET_SHOP,     &ROOM_PET_SHOP,  "Pet Shop"},
	{IDC_NO_SCAN,      &ROOM_NO_SCAN,   "No Scan"},
	{IDC_ARENA,        &ROOM_ARENA,     "&+RArena&n"},
	{IDC_TREASUREROOM, &ROOM_TREASUREROOM, "&+YTreasure Room&n"},
};
const struct exit_flags ExitFlags[] = 
{
	{"&+yH&n", EX_ISDOOR},
	{"&+yC&n", EX_CLOSED},
	{"&+YL&n", EX_LOCKED},
	{"&+LS&N", EX_SECRET},
	{"&+LB&n", EX_BLOCKED},
	{"&+WP&N", EX_PICKPROOF},
	{"&+YW&N", EX_WALLED},
	{"&+wK&n", EX_SPIKED},
	{"&+MI&N", EX_ILLUSION},
	{"&+yD&n", EX_BASHED},
	{"&+WA&n", EX_BASHPROOF},
	{"&+WF&N", EX_PASSPROOF},
	{"&+MT&N", EX_TRAPPED},
	{"&+RE&N", EX_EAT_KEY},
	{"&+LJ&N", EX_JAMMED},
	{"R", EX_BARROW},
};

const GuardBitData guard_bits[] = {
	{"Guarded", EX_GUARDED, true},
	{"Pass Good", EX_PASS_GOOD, true},
	{"Pass Evil", EX_PASS_EVIL, true},
	{"Pass Neutral", EX_PASS_NEUTRAL, true},
	{"Pass NPC", EX_PASS_NPC, true},
	{"Pass Class", EX_PASS_CLASS, true},
	{"Pass Clan", EX_PASS_CLAN, true},
};
int GuardBitCount() {return sizeof(guard_bits)/sizeof(GuardBitData);}

char* dir_name[MAX_DIR] = {
	"North", 
	"East",
	"South",
	"West",
	"Up",
	"Down",
	"Northwest",
	"Southwest",
	"Northeast",
	"Southeast",
};

char* dir_names[MAX_DIR] = {
	"north", 
	"east",
	"south",
	"west",
	"up",
	"down",
	"northwest",
	"southwest",
	"northeast",
	"southeast",
};

char * short_dir_names[MAX_DIR] = {
	"n",
	"e",
	"s",
	"w",
	"u",
	"d",
	"nw",
	"sw",
	"ne",
	"se",
};

int rev_dir[MAX_DIR] = {
	DIR_SOUTH,
	DIR_WEST,
	DIR_NORTH,
	DIR_EAST,
	DIR_DOWN,
	DIR_UP,
	DIR_SOUTHEAST,
	DIR_NORTHEAST,
	DIR_SOUTHWEST,
	DIR_NORTHWEST,
};

char* sector_names[SECT_MAX][2] = {
	{"Inside",					"Inside"},
	{"City",					"&+yCity&n"},
	{"Field",					"&+gField&n"},
	{"Forest",					"&+GForest&n"},
	{"Hills",					"&+yHills&n"},
	{"Mountain",				"&+YMountains&n"},
	{"Water Swim",				"&+BWater&n"},
	{"Water No-Swim",			"&+BWater No-Swim&n"},
	{"Air",						"&+CAir&n"},
	{"Underwater",				"&+bUnderwater&n"},
	{"Underwater Ground",		"&+bUnderwater Ground&n"},
	{"Plane of Fire",			"&+rPlane of Fire&n"},
	{"Ocean",					"&+BOcean&n"},
	{"Underground Wild",		"&+LUnderground Wild&n"},
	{"Underground City",		"&+LUnderground City&n"},
	{"Underground Inside",		"&+LUnderground Inside&n"},
	{"Underground Water",		"&+LUnderground Water&N"},
	{"Underground Water No-Swim","&+LUnderground Water No-Swim&n"},
	{"Underground No-Ground",	"&+LUnderground No-Ground&n"},
	{"Plane of Air",			"&+CPlane of Air&n"},
	{"Plane of Water",			"&+BPlane of Water&N"},
	{"Plane of Earth",			"&+yPlane of Earth&n"},
	{"Ethereal Plane",			"&+CEthereal Plane&n"},
	{"Astral Plane",			"&+WAstral Plane&n"},
	{"Desert",					"&+YDesert&n"},
	{"Artic",					"&+WArtic&n"},
	{"Swamp",					"&+mSwamp&n"},
	{"Road",					"&+LRoad&n"},
	{"Underground Impassible",	"&+LUnderground Impassible&n"},
	{"Underground Ocean",		"&+LUnderground Ocean&n"},
};

room_data::room_data () 
{
	int i;
	
	next = NULL;
	
	first_extra_descr = NULL;
	last_extra_desc = NULL;
	
	contents = NULL;
	people = NULL;
	
	for(i = 0; i < MAX_DIR; i++)
		exit[i] = NULL;
	
	vnum = 0;
	
	if(!def_room)
	{
		name = "An Unamed Room.";
		description = "A non-descript room.";
	

		for(i = 0; i < NUM_ROOM_FLAGS; i++)
			room_flags[i] = 0;

		light = 0;
		current = 0;
		current_dir = 0;
		fall_chance = 0;
		sector_type = 0;
	}
	else
	{
		name = def_room->name;
		description = def_room->description;
	

		for(i = 0; i < NUM_ROOM_FLAGS; i++)
			room_flags[i] = def_room->room_flags[i];

		light = def_room->light;
		current = def_room->current;
		current_dir = def_room->current_dir;
		fall_chance = def_room->fall_chance;
		sector_type = def_room->sector_type;
	}
}

room_data::~room_data ()
{
		first_extra_descr = NULL;
		last_extra_desc = NULL;
}

void room_data::SetRoomBit(BITVECT_DATA bv) 
{
	SET_BIT(room_flags[bv.group], bv.vector);
}

bool room_data::RoomIsSet(BITVECT_DATA bv) 
{
	return IS_SET(room_flags[bv.group], bv.vector) ? true : false;
}

void room_data::RemoveRoomBit(BITVECT_DATA bv) 
{
	REMOVE_BIT(room_flags[bv.group], bv.vector);
}

room_data *GetRoomByVnum(int vnum)
{
	room_data *room = NULL;

	if(vnum == 0)
		return NULL;

	for(room = room_data::room_list; room; room = room->next)
		if(room->vnum == vnum)
			return room;

	return room;
}

void room_data::RemoveFromList()
{
	extra_desc *ped, *next;
	room_data *proom = NULL;
	int i;

	if(!room_data::room_list)
		return;

	for(i = 0; i < MAX_DIR; i++)
		if(this->exit[i])
			delete this->exit[i];
		
	for(ped = this->first_extra_descr; ped; ped = next) {
		next = ped->next;
		delete ped;
	}	

	if(this == room_data::room_list) {
		room_data::room_list = this->next;
		
		if(this == room_data::room_last)
			room_data::room_last = NULL;
	}
	else if(this == room_data::room_last) {
		for(proom = room_data::room_list; proom; proom = proom->next) {
			if(proom->next == room_data::room_last) {
				room_data::room_last = proom;
				proom->next = NULL;
			}
		}
	} else {
		for(proom = room_data::room_list; proom; proom = proom->next) {
			if(proom->next)
				if(proom->next == this) {
					proom->next = this->next;
					break;
				}
		}
	}
	
	this->RemoveContents();
	this->RemoveEveryone();
	
	this->next = NULL;

	delete this;
}

void room_data::AddToList() 
{
	if(room_data::room_list == NULL)
		room_data::room_list = this;
		
	if(room_data::room_last == NULL)
		room_data::room_last = this;
	else 
	{
		room_data::room_last->next = this;
		room_data::room_last = this;
	}

	this->next = NULL;
}

CString room_data::DisplayRoom() 
{
	CString str;
	CString exit_str;
	mob_index *m_index;
	obj_index *o_index;
	int i, x;

	str.Format("&n&+C[&N&+c%d&+C]&n %s&n [%s&n]&n\n", 
		vnum, name, sector_names[sector_type][1]);
	
	for(i = 0, x = 0; i < MaxRoomFlags;i++) {
		if(RoomIsSet(*room_flags_info[i].bv)) {
			if(x%4 == 0 && x != 0)
				str += "\n";
			str += "&n(";
			str += room_flags_info[i].name;
			str += "&n) ";
			x++;
		}
	}
		
	str += "\n&n";
	if(IS_SET(editor_flags, DISP_LINE_LEN))
		str += "&+L|-------------------------- &+rMaximum Line Length: &+L--------------------------|&n\n";
	str += description + "&n\n";
	str += "&+cExits:&n";

	for(i = 0; i < MAX_DIR; i++) {
		if(exit[i]) {
			exit_str += " ";
			
			for(int y = 0; y < EX_MAX; y++)
			{
				if(IS_SET(exit[i]->exit_info, ExitFlags[y].bit))
					exit_str += ExitFlags[y].name;
			}

			str += exit_str;

			exit_str.Format("&+c%s&n&+L(&+r%d&+L)&n", dir_name[i], exit[i]->vnum);
		}
	}

	if(exit_str == "")
		exit_str = " &+RNone!&N";
	
	str += exit_str;
	
	for(o_index = contents; o_index; o_index = o_index->next) 
	{
		exit_str.Format("\n&+L(&+r%d&N&+L)&n%s", o_index->vnum, o_index->ShowObject());
		str+=exit_str;
	}
	
	for(m_index = people; m_index; m_index = m_index->next) 
	{
		str += "\n";
		str += m_index->ShowMobInRoom();
	}
	
	return str;
}

mob_index* room_data::AddPerson(mob_data *mob)
{
	mob_index *index, *tmp;

	if(mob == NULL)
		return NULL;

	index = new mob_index;
	index->in_room = this;
	index->mob = mob;
	index->vnum = mob->vnum;
	mob->load_limit++;

	if(!people)
		people = index;
	else {
		for(tmp = people; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = index;
				break;
			}
		}
	}

	return index;
}

void room_data::AddPerson(mob_index *mob)
{
	mob_index *tmp;

	if(!people)
		people = mob;
	else {
		for(tmp = people; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = mob;
				break;
			}
		}
	}
}

void room_data::RemovePerson(mob_index *mob)
{
	mob_index *tmp;

	if(mob == people) {
		people = people->next;
		mob->next = NULL;
	} else {
		for(tmp = people;tmp; tmp = tmp->next) {
			if(tmp->next == mob) {
				tmp->next = mob->next;
				mob->next = NULL;
			}
		}
	}
}

CString extra_desc::ShowDesc()
{
	CString str;

	str = description;

	str += "\n";

	return str;
}

obj_index* room_data::AddContent(object_data *obj)
{

	obj_index *index, *tmp;

	if(obj == NULL)
		return NULL;

	index = new obj_index;
	index->in_room = this;
	index->obj = obj;
	index->vnum = obj->vnum;

	index->AddToList();

	if(!contents)
		contents = index;
	else {
		for(tmp = contents; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = index;
				break;
			}
		}
	}

	return index;
}

void room_data::AddContent(obj_index *obj)
{
	obj_index *tmp;

	if(!contents)
		contents = obj;
	else {
		for(tmp = contents; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = obj;
				break;
			}
		}
	}
}

void room_data::RemoveContent(obj_index *obj)
{
	obj_index *tmp;

	if(obj == contents) {
		contents = contents->next;
		obj->next = NULL;
	} else {
		for(tmp = contents;tmp; tmp = tmp->next) {
			if(tmp->next == obj) {
				tmp->next = obj->next;
				obj->next = NULL;
			}
		}
	}
}

void room_data::RemoveEveryone()
{
	mob_index *mob, *next;

	if(people == NULL)
		return;

	for(mob = people; mob; mob = next) {
		next = mob->next;
		//we need to delete thier eq and inventory!!!!!
		delete mob;
	}

	people = NULL;
}

void room_data::RemoveContents()
{
	obj_index *obj, *next;

	if(contents == NULL)
		return;
	for(obj = contents; obj; obj = next) {
		next = obj->next;
		obj->RemoveFromList();
	}

	contents = NULL;
}

exit_data::exit_data()
{
	exit_info = 0;
	guardbits = 0;
	vnum = 0;
	keyword = "";
	description = "";
	key = 0;
	next = NULL;
}

mob_index *room_data::GetMobInRoom(int vnum)
{
	mob_index *tmp;

	for(tmp = people; tmp; tmp = tmp->next)
	{
		if(tmp->vnum == vnum)
			return tmp;
	}

	return NULL;
}

obj_index *room_data::GetObjInRoom(int vnum)
{
	obj_index *tmp;

	for(tmp = contents; tmp; tmp = tmp->next)
	{
		if(tmp->vnum == vnum)
			return tmp;
	}

	return NULL;
}

object_data* room_data::GetPortal()
{
	for(obj_index *tmp = contents; tmp; tmp = tmp->next)
	{
		if(tmp->obj)
		{
			if(tmp->obj->item_type == TYPE_TELEPORT)
				return tmp->obj;
		}
	}

	return NULL;
}