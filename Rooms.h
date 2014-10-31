#ifndef _ROOMS_H_
#define _ROOMS_H_ 1

#include "Bits.h"
class room_data;
class exit_data;
class obj_index;
class mob_index;

enum ExitBits { 
	EX_ISDOOR		= BV00,
	EX_CLOSED		= BV01,
	EX_LOCKED		= BV02,
	EX_SECRET		= BV06,
	EX_BLOCKED		= BV07,
	EX_PICKPROOF	= BV08,
	EX_WALLED		= BV09,
	EX_SPIKED		= BV10,
	EX_ILLUSION		= BV11,
	EX_BASHED		= BV12,
	EX_BASHPROOF	= BV13,
	EX_PASSPROOF	= BV14,
	EX_TRAPPED		= BV15,
	EX_EAT_KEY		= BV16,
	EX_JAMMED		= BV17,
	EX_BARROW		= BV18,
};

enum {EX_MAX = 19};

enum ExitGuardBits {
	EX_GUARDED		= BV00,
	EX_PASS_GOOD	= BV01,
	EX_PASS_EVIL	= BV02,
	EX_PASS_NEUTRAL = BV03,
	EX_PASS_NPC		= BV04,
	EX_PASS_CLASS	= BV05,
	EX_PASS_CLAN	= BV06
};

enum Sectors {
	SECT_INSIDE	= 0,
	SECT_CITY,
	SECT_FIELD,
	SECT_FOREST,
	SECT_HILLS,
	SECT_MOUNTAIN,
	SECT_WATER_SWIM,
	SECT_WATER_NOSWIM,
	SECT_AIR,
	SECT_UNDERWATER,
	SECT_UNDERWATER_GROUND,
	SECT_PLANE_FIRE,
	SECT_OCEAN,
	SECT_UNDERG_WILD,
	SECT_UNDERG_CITY,
	SECT_UNDERG_INSIDE,
	SECT_UNDERG_WATER,
	SECT_UNDERG_WATER_NOSWIM,
	SECT_UNDERG_NOGROUND,
	SECT_PLANE_AIR,
	SECT_PLANE_WATER,
	SECT_PLANE_EARTH,
	SECT_PLANE_ETHEREAL,
	SECT_PLANE_ASTRAL,
	SECT_DESERT,
	SECT_ARCTIC,
	SECT_SWAMP,
	SECT_ROAD,
	SECT_UNDERG_IMPASSABLE,
	SECT_UNDERG_OCEAN,
	SECT_MAX
};

enum Directions {
	DIR_NORTH =	0, 
	DIR_EAST,
	DIR_SOUTH,
	DIR_WEST,
	DIR_UP,
	DIR_DOWN,
	DIR_NORTHWEST,
	DIR_SOUTHWEST,
	DIR_NORTHEAST,
	DIR_SOUTHEAST,
	MAX_DIR,
};

enum {
	NUM_ROOM_FLAGS = 2,
};

class extra_desc
{
public:
	static char class_name[];
	static int  class_index;

public:
    extra_desc *next;
	extra_desc *prev;
    CString    keyword;
    CString    description;
	bool	   deleted;

	extra_desc () : deleted(false) {
		next = NULL;
		prev = NULL;
	};

	~extra_desc () {
		next = NULL;
		prev = NULL;
		deleted = true;
	};

	CString ShowDesc();
};

class exit_data
{
public:
	static char class_name[];
	static int  class_index;

public:
    //room_data   *to_room;
    int 		vnum;
    int 		exit_info;
    int 		guardbits;
    int 		key;
    CString		keyword;
    CString		description;
    exit_data   *next;

	exit_data();
};

class room_data
{
public:
	static const char	class_name[];
	static const int	class_index;
	
	static room_data	*room_list;
	static room_data	*room_last;
	static room_data    *def_room;
	
	static int			room_hi_vnum;

public:
	room_data *	next;

	HTREEITEM	m_tThis;
	HTREEITEM	m_tPeople;
	HTREEITEM	m_tContents;

    mob_index	*people;
    obj_index	*contents;

    extra_desc	*first_extra_descr;
	extra_desc	*last_extra_desc;
    exit_data	*exit[ MAX_DIR ];

    CString		name;
    CString		description;
    int 		vnum;
    int 		room_flags[NUM_ROOM_FLAGS];
    int 		light;
    int         current;
    int         current_dir;
    int         fall_chance;
    int 		sector_type;

	//for the map editor
	bool		painted;

public:
	room_data ();

	~room_data ();

	void		SetRoomBit(BITVECT_DATA bv);
	bool		RoomIsSet(BITVECT_DATA bv);
	void		RemoveRoomBit(BITVECT_DATA bv);

	void		RemoveFromList();
	void		AddToList();
	
	mob_index*	AddPerson(mob_data *mob);
	void		AddPerson(mob_index *mob);
	void		RemovePerson(mob_index *mob);
	void		RemoveEveryone();
	
	obj_index*	AddContent(object_data *obj);
	void		AddContent(obj_index *obj);
	void		RemoveContent(obj_index *obj);
	void		RemoveContents();

	object_data* GetPortal();
	
	CString		DisplayRoom();

	mob_index *GetMobInRoom(int vnum);
	obj_index *GetObjInRoom(int vnum);
};

extern const BITVECT_DATA ROOM_DARK;
extern const BITVECT_DATA ROOM_LIMITSCAN;
extern const BITVECT_DATA ROOM_NO_MOB;
extern const BITVECT_DATA ROOM_INDOORS;
extern const BITVECT_DATA ROOM_SILENT;
extern const BITVECT_DATA ROOM_UNDERWATER;
extern const BITVECT_DATA ROOM_NO_RECALL;
extern const BITVECT_DATA ROOM_NO_MAGIC;
extern const BITVECT_DATA ROOM_TUNNEL;
extern const BITVECT_DATA ROOM_PRIVATE;
extern const BITVECT_DATA ROOM_NOCAMP;
extern const BITVECT_DATA ROOM_SAFE;
extern const BITVECT_DATA ROOM_NO_PRECIP;
extern const BITVECT_DATA ROOM_SINGLE_FILE;
extern const BITVECT_DATA ROOM_JAIL;
extern const BITVECT_DATA ROOM_NO_TELEPORT;
extern const BITVECT_DATA ROOM_SOLITARY;
extern const BITVECT_DATA ROOM_HEAL;
extern const BITVECT_DATA ROOM_NO_HEAL;
extern const BITVECT_DATA ROOM_INN;
extern const BITVECT_DATA ROOM_DOCKABLE;
extern const BITVECT_DATA ROOM_MAGICDARK;
extern const BITVECT_DATA ROOM_MAGICLIGHT;
extern const BITVECT_DATA ROOM_NO_SUMMON;
extern const BITVECT_DATA ROOM_GUILDROOM;
extern const BITVECT_DATA ROOM_TWILIGHT;
extern const BITVECT_DATA ROOM_NO_PSIONICS;
extern const BITVECT_DATA ROOM_NO_GATE;
extern const BITVECT_DATA ROOM_BANK;
extern const BITVECT_DATA ROOM_PET_SHOP;
extern const BITVECT_DATA ROOM_NO_SCAN;
extern const BITVECT_DATA ROOM_EARTHEN_STARSHELL;
extern const BITVECT_DATA ROOM_AIRY_STARSHELL;
extern const BITVECT_DATA ROOM_FIERY_STARSHELL;
extern const BITVECT_DATA ROOM_WATERY_STARSHELL;
extern const BITVECT_DATA ROOM_HYPNOTIC_PATTERN;
extern const BITVECT_DATA ROOM_ARENA;
extern const BITVECT_DATA ROOM_TREASUREROOM;

enum {MaxRoomFlags = 32};

class RoomFlags 
{
public:
	static char class_name[];
	static int class_index;

public:
	int button;
	const BITVECT_DATA *bv;
	char *name;
};

class GuardBitData {
public:
	char*name;
	int bit;
	bool used;
};

struct exit_flags 
{
	char *name;
	int bit;
};

extern const struct exit_flags ExitFlags[EX_MAX];

extern char* dir_name[MAX_DIR];
extern int rev_dir[MAX_DIR];
extern char* sector_names[SECT_MAX][2];
extern RoomFlags room_flags_info[];
extern const GuardBitData guard_bits[];
extern char * short_dir_names[MAX_DIR];
extern char* dir_names[MAX_DIR];
 
room_data *GetRoomByVnum(int vnum);
int GuardBitCount();

#endif