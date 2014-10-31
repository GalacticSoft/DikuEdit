#ifndef _MOBS_H_
#define _MOBS_H_ 1

class room_data;
class obj_index;
#include "Quests.h"
#include "Progs.h"
#include "Classes.h"

class coin_data 
{
public:
	unsigned int platinum;
	unsigned int gold;
	unsigned int silver;
	unsigned int copper;
};

enum Positions { 
	POS_DEAD = 0,
	POS_MORTAL,
	POS_INCAP,
	POS_SLEEPING,
	POS_RECLINING,
	POS_RESTING,
	POS_SITTING,
	POS_KNEELING,
	POS_STANDING,
	POS_MAX,
};

enum Sexs { 
	SEX_NEUTRAL = 0,
	SEX_MALE,
	SEX_FEMALE,
	SEX_MAX
};

enum Sizes {
	SIZE_ANY = 0, 
	SIZE_TINY,
	SIZE_SMALL, 
	SIZE_MEDIUM,
	SIZE_LARGE, 
	SIZE_HUGE, 
	SIZE_GIANT,
	SIZE_TITANIC,
	SIZE_GARGANTUAN, 
	SIZE_NONE,
	MAX_SIZE,
};

enum Acts {
	ACT_SIZEMINUS		= BV00,
	ACT_SENTINEL		= BV01,	/* Stays in one room	*/
	ACT_SCAVENGER		= BV02,	/* Picks up objects	*/
	ACT_IS_NPC			= BV03,	/* Auto set for mobs	*/
	ACT_GUARDIAN		= BV04,     /* Check guardian acts  */ 
	ACT_AGGRESSIVE		= BV05,	/* Attacks PC's		*/
	ACT_STAY_AREA		= BV06,	/* Won't leave area	*/
	ACT_WIMPY			= BV07,	/* Flees when hurt	*/
	ACT_AGGROEVIL		= BV08,
	ACT_AGGROGOOD		= BV09,
	ACT_AGGRONEUT		= BV10,
	ACT_MEMORY			= BV11,
	ACT_NOPARA			= BV12,
	ACT_NOSUMMON		= BV13,
	ACT_NOBASH			= BV14,
	ACT_TEACHER			= BV15,
	ACT_OUTLAW			= BV16,
	ACT_CANFLY			= BV17,	
	ACT_CANSWIM			= BV18,
	ACT_CANT_TK			= BV19,
	ACT_MOVED			= BV20, // Ingame - Not settable in DE
	ACT_PET				= BV21, // Ingame - Not settable in DE
	ACT_NOEXP			= BV22,
	ACT_SIZEPLUS		= BV23,
	ACT_WITNESS			= BV24,
	ACT_NOCHARM			= BV25,
	ACT_PROTECTOR		= BV26,
	ACT_MOUNT			= BV27,
	ACT_AGGROEVILRACE	= BV28,
	ACT_AGGROGOODRACE	= BV29,
	ACT_HUNTER			= BV30,
};

enum Races {
	RACE_HUMAN = 0,
	RACE_BARBARIAN,
	RACE_GREYELF,
	RACE_RAKSHASA,
	RACE_HALFELF,
	RACE_FLIND,
	RACE_DROW,
	RACE_DWARF,
	RACE_DUERGAR,
	RACE_HALFLING,
	RACE_TROLL,
	RACE_OGRE,
	RACE_ORC,
	RACE_GNOME,
	RACE_CENTAUR,
	RACE_GITHYANKI,
	RACE_GOBLIN,
	RACE_MINOTAUR,
	RACE_GITHZERAI,
	RACE_THRIKREEN,
	RACE_HALFORC,
	RACE_NEOGI,
	RACE_SAHAUGIN,
	RACE_DARKHUMAN,
	RACE_HALFDWARF,
	RACE_HALFKOBOLD,
	RACE_GIANT, 
	RACE_ILLITHID,
	RACE_AQUATICELF,
	RACE_KOBOLD,
	RACE_HOBGOBLIN,
	RACE_WEMIC,
	RACE_HUMANOID,
	RACE_DEMON,
	RACE_GOD,
	RACE_DEVIL,
	RACE_ANGEL,
	RACE_FAERIE,
	RACE_VAMPIRE,
	RACE_WEREWOLF,
	RACE_DRAGON,
	RACE_BEHOLDER,
	RACE_DERRO,
	RACE_SLAAD,
	RACE_GOLEM,
	RACE_DRACOLICH,
	RACE_DRAGONKIN,
	RACE_UNDEAD,
	RACE_GHOST,
	RACE_HARPY,
	RACE_RUSTMONSTER,
	RACE_FIRE_ELE,
	RACE_AIR_ELE,
	RACE_WATER_ELE,
	RACE_EARTH_ELE,
	RACE_LYCANTHROPE,
	RACE_OBJECT,
	RACE_MIST,
	RACE_IXITXACHITL,
	RACE_ABOLETH,
	RACE_HYDRA,
	RACE_REPTILE,
	RACE_BOAR,
	RACE_INSECT,
	RACE_ANIMAL,
	RACE_HERBIVORE,
	RACE_CARNIVORE,
	RACE_BIRD,
	RACE_HORSE,
	RACE_PRIMATE,
	RACE_BEAR,
	RACE_BAT,
	RACE_PLANT,
	RACE_TREE,
	RACE_RAT,
	RACE_PARASITE,
	RACE_ARACHNID,
	RACE_SNAKE,
	RACE_WORM,
	RACE_FISH,
	RACE_SHADOW_ELE,
	MAX_RACE,
};

enum { MAX_BUY	= 10 }; // Max number of item types shop will buy
enum { MAX_SELL = 20 }; // Max number of items shop can sell.

enum EquipSlots {
	WEAR_NONE		=	-1,
	//WEAR_LIGHT	=	0
	WEAR_FINGER_L	=	1,
	WEAR_FINGER_R	=	2,
	WEAR_NECK_1		=	3,
	WEAR_NECK_2		=	4,
	 WEAR_BODY		=	5,
	WEAR_HEAD		=	6,
	WEAR_LEGS		=	7,
	WEAR_FEET		=	8,
	WEAR_HANDS		=	9,
	WEAR_ARMS		=	10,
	WEAR_SHIELD	=	11,
	WEAR_ABOUT		=	12,
	WEAR_WAIST		=	13,
	WEAR_WRIST_L	=	14,
	WEAR_WRIST_R	=	15,
	WEAR_HAND		=	16,
	WEAR_HOLD		=	17,
	WEAR_HAND_2		=	18,
	WEAR_EYES		=	19,
	WEAR_FACE		=	20,
	WEAR_EAR_L		=	21,
	WEAR_EAR_R		=	22,
	WEAR_BADGE		=	23,
	WEAR_ONBACK		=	24,
	WEAR_BELT_1		=	25,
	WEAR_BELT_2		=	26,
	WEAR_BELT_3		=	27,
	UNUSED			=   28,
	WEAR_QUIVER		=	29,
	WEAR_TAIL		=	30,
	WEAR_HORSE_BODY	=	31,
	WEAR_HORNS		=	32,
	WEAR_NOSE		=	33,
	WEAR_HAND_3		=	34,
	WEAR_HAND_4		=	35,
	WEAR_LOWER_ARMS =	36,
	WEAR_LOWER_HANDS=	37,
	WEAR_LWRIST_L	=	38, // Lower wrist for thri
	WEAR_LWRIST_R	=	39, // Lower wrist for thri
	MAX_WEAR		=	40,
};

extern const BITVECT_DATA AFF_NONE;
extern const BITVECT_DATA AFF_BLIND;
extern const BITVECT_DATA AFF_INVISIBLE;
extern const BITVECT_DATA AFF_FARSEE;
extern const BITVECT_DATA AFF_DETECT_INVIS;
extern const BITVECT_DATA AFF_HASTE;
extern const BITVECT_DATA AFF_SENSE_LIFE;
extern const BITVECT_DATA AFF_MINOR_GLOBE;
extern const BITVECT_DATA AFF_STONESKIN;
extern const BITVECT_DATA AFF_UNDERDARK_VIS;
extern const BITVECT_DATA AFF_SHADOW;
extern const BITVECT_DATA AFF_GHOUL; // wraithform
extern const BITVECT_DATA AFF_GILLS; // waterbreath
extern const BITVECT_DATA AFF_KO;
extern const BITVECT_DATA AFF_PROTECT_EVIL;
extern const BITVECT_DATA AFF_BOUND;
extern const BITVECT_DATA AFF_SLOW_POISON;
extern const BITVECT_DATA AFF_PROTECT_GOOD;
extern const BITVECT_DATA AFF_SLEEP;
extern const BITVECT_DATA AFF_SKL_AWARE;
extern const BITVECT_DATA AFF_SNEAK;
extern const BITVECT_DATA AFF_HIDE;
extern const BITVECT_DATA AFF_FEAR;
extern const BITVECT_DATA AFF_CHARM;
extern const BITVECT_DATA AFF_MEDITATE;
extern const BITVECT_DATA AFF_BARKSKIN;
extern const BITVECT_DATA AFF_INFRARED;
extern const BITVECT_DATA AFF_LEVITATE;
extern const BITVECT_DATA AFF_FLYING;
extern const BITVECT_DATA AFF_AWARE;
extern const BITVECT_DATA AFF_PROTECT_FIRE;
extern const BITVECT_DATA AFF_CAMPING;

extern const BITVECT_DATA AFF_FLAMING;
extern const BITVECT_DATA AFF_ULTRAVISION;
extern const BITVECT_DATA AFF_DETECT_EVIL;
extern const BITVECT_DATA AFF_DETECT_GOOD;
extern const BITVECT_DATA AFF_DETECT_MAGIC;
extern const BITVECT_DATA AFF_MAJOR_PHYSICAL;
extern const BITVECT_DATA AFF_PROTECT_COLD;
extern const BITVECT_DATA AFF_PROTECT_LIGHTNING;
extern const BITVECT_DATA AFF_MINOR_PARA;
extern const BITVECT_DATA AFF_HOLD; // major para
extern const BITVECT_DATA AFF_SLOWNESS;
extern const BITVECT_DATA AFF_MAJOR_GLOBE;
extern const BITVECT_DATA AFF_PROTECT_GAS;
extern const BITVECT_DATA AFF_PROTECT_ACID;
extern const BITVECT_DATA AFF_POISON;
extern const BITVECT_DATA AFF_SOULSHIELD;
extern const BITVECT_DATA AFF_DUERGAR_HIDE;
extern const BITVECT_DATA AFF_MINOR_INVIS;
extern const BITVECT_DATA AFF_VAMP_TOUCH;
extern const BITVECT_DATA AFF_STUNNED;
extern const BITVECT_DATA AFF_DROPPED_PRIMARY;
extern const BITVECT_DATA AFF_DROPPED_SECOND;
extern const BITVECT_DATA AFF_FUMBLED_PRIMARY;
extern const BITVECT_DATA AFF_CTFFLAG;
extern const BITVECT_DATA AFF_HOLDING_BREATH;
extern const BITVECT_DATA AFF_MEMORIZING;
extern const BITVECT_DATA AFF_DROWNING;
extern const BITVECT_DATA AFF_PASS_DOOR;
extern const BITVECT_DATA AFF_DRAINING;
extern const BITVECT_DATA AFF_CASTING;
extern const BITVECT_DATA AFF_SCRIBING;

extern const BITVECT_DATA AFF_TENSORS_DISC;  // Unused DE bit
extern const BITVECT_DATA AFF_TRACKING;
extern const BITVECT_DATA AFF_SINGING;
extern const BITVECT_DATA AFF_ECTOPLASMIC;
extern const BITVECT_DATA AFF_ABSORBING	;  // Unused DE bit
extern const BITVECT_DATA AFF_VAMP_BITE;  // Unused DE bit
extern const BITVECT_DATA AFF_SPIRIT_WARD;
extern const BITVECT_DATA AFF_GREATER_SPIRIT_WARD;
extern const BITVECT_DATA AFF_MASTERED;  // Unused DE bit - For control over summoned/called creatures
extern const BITVECT_DATA AFF_SILVER;
extern const BITVECT_DATA AFF_PLUS_ONE;
extern const BITVECT_DATA AFF_PLUS_TWO;
extern const BITVECT_DATA AFF_PLUS_THREE;
extern const BITVECT_DATA AFF_PLUS_FOUR;
extern const BITVECT_DATA AFF_PLUS_FIVE;
extern const BITVECT_DATA AFF_ENLARGED;
extern const BITVECT_DATA AFF_REDUCED;
extern const BITVECT_DATA AFF_COVER;
extern const BITVECT_DATA AFF_FOUR_ARMS;
extern const BITVECT_DATA AFF_INERTIAL_BARRIER;
extern const BITVECT_DATA AFF_INTELLECT_FORTRESS;
extern const BITVECT_DATA AFF_COLDSHIELD;
extern const BITVECT_DATA AFF_CONJURED;  // Unused DE bit - For conjured creatures...
extern const BITVECT_DATA AFF_SWIMMING;
extern const BITVECT_DATA AFF_TOWER_OF_IRON_WILL;
extern const BITVECT_DATA AFF_UNDERWATER;  // Unused DE bit
extern const BITVECT_DATA AFF_BLUR;
extern const BITVECT_DATA AFF_NECKBITING;  // Unused DE bit
extern const BITVECT_DATA AFF_ELEMENTAL_FORM;
extern const BITVECT_DATA AFF_PASS_WITHOUT_TRACE;
extern const BITVECT_DATA AFF_PALADIN_AURA;

extern const BITVECT_DATA AFF_LOOTER;
extern const BITVECT_DATA AFF_PLAGUE; // diseased
extern const BITVECT_DATA AFF_SACKING;  // Unused DE bit
extern const BITVECT_DATA AFF_SENSE_FOLLOWER;
extern const BITVECT_DATA AFF_STORNOG_SPHERES;  // Unused DE bit
extern const BITVECT_DATA AFF_GREATER_SPHERES;  // Unused DE bit
extern const BITVECT_DATA AFF_VAMPIRE_FORM;  // Unused DE bit
extern const BITVECT_DATA AFF_NO_UNMORPH;  // Unused DE bit
extern const BITVECT_DATA AFF_HOLY_SACRIFICE;
extern const BITVECT_DATA AFF_BATTLE_ECSTASY;
extern const BITVECT_DATA AFF_DAZZLE;
extern const BITVECT_DATA AFF_DAZZLED;
extern const BITVECT_DATA AFF_THROAT_CRUSH;
extern const BITVECT_DATA AFF_REGENERATION;
extern const BITVECT_DATA AFF_BEARHUG;
extern const BITVECT_DATA AFF_GRAPPLING;
extern const BITVECT_DATA AFF_GRAPPLED;
extern const BITVECT_DATA AFF_MAGE_FLAME;  // Unused DE bit
extern const BITVECT_DATA AFF_NO_IMMOLATE;
extern const BITVECT_DATA AFF_MULTICLASS;
extern const BITVECT_DATA AFF_DETECT_UNDEAD;
extern const BITVECT_DATA AFF_CLARITY;
extern const BITVECT_DATA AFF_MAJOR_PARA;
extern const BITVECT_DATA AFF_WARD_UNDEAD;
extern const BITVECT_DATA AFF_TRUE_SEEING;

extern const BITVECT_DATA AFF_IS_FLEEING;
extern const BITVECT_DATA AFF_HUNTING;
extern const BITVECT_DATA AFF_BIOFEEDBACK;
extern const BITVECT_DATA AFF_FAMINE;
extern const BITVECT_DATA AFF_MUTE;
extern const BITVECT_DATA AFF_FAERIE_FIRE;
extern const BITVECT_DATA AFF_SANCTUARY;
extern const BITVECT_DATA AFF_CHANGE_SEX;
extern const BITVECT_DATA AFF_CURSE;
extern const BITVECT_DATA AFF_DETECT_HIDDEN;
extern const BITVECT_DATA AFF_POLYMORPH;
extern const BITVECT_DATA AFF_COMP_LANG;
extern const BITVECT_DATA AFF_DENY_EARTH;
extern const BITVECT_DATA AFF_DENY_AIR;
extern const BITVECT_DATA AFF_DENY_FIRE;
extern const BITVECT_DATA AFF_DENY_WATER;
extern const BITVECT_DATA AFF_TRACK;
extern const BITVECT_DATA AFF_JUSTICE_TRACKER;
extern const BITVECT_DATA AFF_LAYHANDS_TIMER;
extern const BITVECT_DATA AFF_ELEM_SIGHT;
extern const BITVECT_DATA AFF_BLOCKEDTMP;
extern const BITVECT_DATA AFF_MISDIRECTION;
extern const BITVECT_DATA AFF_VACANCY;
extern const BITVECT_DATA AFF_CHANGE_SELF;
extern const BITVECT_DATA AFF_PROWESS;
extern const BITVECT_DATA AFF_SUMMON_MOUNT_TIMER;
extern const BITVECT_DATA AFF_INCOMPETENCE;
extern const BITVECT_DATA AFF_CLIMBING;
extern const BITVECT_DATA AFF_UNDEAD_MUTE;
extern const BITVECT_DATA AFF_COORDINATION;
extern const BITVECT_DATA AFF_CHARM_OTTER;

extern const BITVECT_DATA AFF_ENDURANCE;
extern const BITVECT_DATA AFF_FORTITUDE;
extern const BITVECT_DATA AFF_INSIGHT;
extern const BITVECT_DATA AFF_MIGHT;
extern const BITVECT_DATA AFF_SAVVY;
extern const BITVECT_DATA AFF_WRISTLOCKED1;
extern const BITVECT_DATA AFF_WRISTLOCKED2;
extern const BITVECT_DATA AFF_WRISTLOCKING;
extern const BITVECT_DATA AFF_PROTECT_UNDEAD;
extern const BITVECT_DATA AFF_CHANTING;
extern const BITVECT_DATA AFF_SIMULACRUM;
extern const BITVECT_DATA AFF_APPROVAL;
extern const BITVECT_DATA AFF_LISTENING;
extern const BITVECT_DATA AFF_INVADER_TRACKER;
extern const BITVECT_DATA AFF_DISGUISE;
extern const BITVECT_DATA AFF_DEAF;
extern const BITVECT_DATA AFF_HELLFIRE;
extern const BITVECT_DATA AFF_BLURTIMER;
extern const BITVECT_DATA AFF_CONSUMING;
extern const BITVECT_DATA AFF_DRAINEE;
extern const BITVECT_DATA AFF_TOWER_IRON_WILL;
extern const BITVECT_DATA AFF_FLUXED;
extern const BITVECT_DATA AFF_HP_STOP;
extern const BITVECT_DATA AFF_MANA_STOP;
extern const BITVECT_DATA AFF_MOVE_STOP;

enum { NUM_AFFECT_VECTORS = 6 };

class	shop_data
{
public:
	static shop_data *first_shop;
	static shop_data *last_shop;

    shop_data *	next;					/* Next shop in list			*/
    int 		keeper;					/* Vnum of shop keeper mob		*/
    int 		buy_type [ MAX_BUY ];	/* Item types shop will buy		*/
    int			sell_item[ MAX_SELL ];  /* Items that shop is selling   */
    int 		profit_buy;				/* Cost multiplier for buying	*/
    int 		profit_sell;			/* Cost multiplier for selling	*/
    int 		open_hour;				/* First opening hour			*/
    int 		close_hour;				/* First closing hour			*/
	CString     shop_string[7];			/* Shop messages not used		*/

	//unused data stored for writing.
	int dummy[10];
	char dummy_char[4];
	CString dummy_str[3];

public:
	shop_data();

	void AddToList();
	void RemoveFromList();

	void WriteShop();
	void ReadShop();
};

class mob_data 
{
public:
	static const char  class_name[];
	static const int class_index;

	static mob_data *first_mob;				//first mob in list
	static mob_data *last_mob;				//last mob in list

	static int high_mob_vnum;				//highest mob vnum not in use

	static mob_data *def_mob;
		
public:
	HTREEITEM m_tThis;

	mob_data * next;						//next mob in list
		
	obj_index *carrying;					//objects mob is carrying
		
	CString name;							//keywords of the mobs
	CString short_descr;					//description that shows in messages
	CString long_descr;						//description that shows in room
	CString description;					//description that shows when looked at
			
	coin_data money;						//money mob is carrying

	int vnum;								//vnum of mob
	int c_class;							//class of mob
	int race;								//race of mob
	int level;								//level of mob
	int size;								//size of mob
	int alignment;							//alignment of mob
	int position;							//position mob is in
	int sex;								//sex of the mob
	int act;								//act flags determines how mob acts
	int affected_by[NUM_AFFECT_VECTORS];	//spells mob is affected by
		
	shop_data *shop;						//shop mob has NULL of none
	quest_index_data *quests;				//index of all mobs quests NULL of none

	int load_limit;							// load limits for mobile

	ProgFile progs;

public:
	void AddToList();						//adds mob to master list
	void RemoveFromList();					//removes mob from master list
		
	void SetAff(const BITVECT_DATA& bv);	//sets mob affects
	bool AffIsSet(const BITVECT_DATA& bv);	//checks if mob is affected by BV
	void RemoveAff(const BITVECT_DATA& bv);	//Removes affect from mob

	mob_data();								//constructor

	CString ShowMobInRoom();						//Formats a mob for display
	CString ShowMob();						//Formats the mobs description for display
	bool IsName(CString &arg);

	bool IsMount();
};

#include "Objects.h"
class mob_index 
{
public:
	static const char class_name[];
	static const int class_index;

public:
	HTREEITEM m_tThis;
	HTREEITEM m_tRoom;

	int vnum;
	
	mob_index *next;
	mob_index *next_in_group;
	mob_index *rider;
	mob_index *riding;
	mob_index *group_leader;
	mob_index *follower;
	
	obj_index *eq[MAX_WEAR];
	obj_index *inventory;
	
	room_data* in_room;
	
	mob_data *mob;

public:
	mob_index();
	
	void AddObjToInv(object_data *obj);
	void AddObjToInv(obj_index *obj);
	void RemoveObjFromInv(obj_index *obj);
	
	void EquipObj(obj_index *obj, int loc);
	void EquipObj(object_data *obj, int loc);
	void UnEquipObj(obj_index *obj, int loc);

	void DeleteAllEquip();
	void DeleteAllInv();

	CString ShowMob();

	void AddFollower(mob_index *mob);
	void RemoveFollower(mob_index *mob);
	void RemoveFollowers();
	bool IsFollower(mob_index *mob);
	
	void AddRider(mob_index *mob);
	void RemoveRider();

	void AddRiding(mob_index *mob);
	void RemoveRiding();

	bool IsMount();

	CString GetShortName();
	CString ShowMobInRoom();
	int GetRace();
	int GetSex();

	bool InInventory(obj_index*obj);
	obj_index* GetObjInInv(int vnum);

	bool IsName(CString &arg);

	bool HasQuestItem(object_data *obj);
};

CString		GetSex(int i);
CString		GetPosition(int i);
CString		GetSize(int i);
CString		GetRaceName(int i);
CString		GetRaceKey(int i);
int			GetRaceIndex(const CString& str);
int			GetRaceByKey(CString &str);

extern CString slot_names[MAX_WEAR];
extern CString slot_names2[MAX_WEAR];
extern int equip_top_down[MAX_WEAR];
extern CString sex[SEX_MAX];
extern CString sizes[MAX_SIZE];

struct wear_types
{
	char *name;
	int bit;
};

extern const wear_types wear_names[MAX_WEAR]; 

#endif