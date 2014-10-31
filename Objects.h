#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "TrapData.h"

class char_data;
class room_data;
class extra_desc;

enum TriggerCommands
{
     MUDCOMM_LOWEST     =1,
     MUDCOMM_NORTH      =1,
     MUDCOMM_EAST       =2,
     MUDCOMM_SOUTH      =3,
     MUDCOMM_WEST       =4,
     MUDCOMM_UP         =5,
     MUDCOMM_DOWN       =6,
     MUDCOMM_ENTER      =7,
     MUDCOMM_TURN       =8,
     MUDCOMM_KISS       =9,
     MUDCOMM_GET        =10,
     MUDCOMM_DRINK      =11,
     MUDCOMM_EAT        =12,
     MUDCOMM_WEAR       =13,
     MUDCOMM_WIELD      =14,
     MUDCOMM_LOOK       =15,
//     MUDCOMM_TASTE      =16,
     MUDCOMM_SAY        =17,
     MUDCOMM_SHOUT      =18,
     MUDCOMM_TELL       =19,
     MUDCOMM_CLIMB      =20,
     MUDCOMM_SWING      =21,
     MUDCOMM_BOUNCE     =22,
     MUDCOMM_SMILE      =23,
     MUDCOMM_DANCE      =24,
     MUDCOMM_KILL       =25,
     MUDCOMM_CACKLE     =26,
     MUDCOMM_LAUGH      =27,
     MUDCOMM_GIGGLE     =28,
     MUDCOMM_SHAKE      =29,
     MUDCOMM_PUKE       =30,
     MUDCOMM_GROWL      =31,
     MUDCOMM_SCREAM     =32,
     MUDCOMM_INSULT     =33,
     MUDCOMM_COMFORT    =34,
     MUDCOMM_NOD        =35,
     MUDCOMM_SIGH       =36,
     MUDCOMM_SULK       =37,
     MUDCOMM_PART       =38,
     MUDCOMM_TWIST      =39,
//     MUDCOMM_SING       =40,
     MUDCOMM_CHANT      =41,
     MUDCOMM_STAND      =42,
     MUDCOMM_SIT        =43,
     MUDCOMM_REST       =44,
     MUDCOMM_SLEEP      =45,
     MUDCOMM_WAKE       =46,
     MUDCOMM_DUST       =47,
     MUDCOMM_HUNT       =48,
     MUDCOMM_HUG        =49,
     MUDCOMM_SNUGGLE    =50,
     MUDCOMM_CUDDLE     =51,
     MUDCOMM_NUZZLE     =52,
     MUDCOMM_CRY        =53,
     MUDCOMM_SHIMMY     =54,
     MUDCOMM_SWIM       =55,
     MUDCOMM_FORGE      =56,
//     MUDCOMM_BASH       =57,
     MUDCOMM_SMASH      =58,
//     MUDCOMM_SMELL      =59,
     MUDCOMM_DROP       =60,
     MUDCOMM_GOTO       =61,
     MUDCOMM_WEATHER    =62,
     MUDCOMM_READ       =63,
     MUDCOMM_POUR       =64,
     MUDCOMM_GRAB       =65,
     MUDCOMM_REMOVE     =66,
     MUDCOMM_PUT        =67,
     MUDCOMM_SHUTDOW    =68,
     MUDCOMM_SAVE       =69,
     MUDCOMM_HIT        =70,
     MUDCOMM_STRING     =71,
     MUDCOMM_GIVE       =72,
     MUDCOMM_QUIT       =73,
     MUDCOMM_STAT       =74,
     MUDCOMM_SETSKILL   =75,
     MUDCOMM_TIME       =76,
     MUDCOMM_LOAD       =77,
     MUDCOMM_PURGE      =78,
     MUDCOMM_SHUTDOWN   =79,
     MUDCOMM_IDEA       =80,
     MUDCOMM_TYPO       =81,
     MUDCOMM_BUG        =82,
     MUDCOMM_WHISPER    =83,
     MUDCOMM_CAST       =84,
     MUDCOMM_AT         =85,
     MUDCOMM_ASK        =86,
     MUDCOMM_ORDER      =87,
     MUDCOMM_SIP        =88,
     MUDCOMM_TASTE      =89,
     MUDCOMM_SNOOP      =90,
     MUDCOMM_FOLLOW     =91,
     MUDCOMM_RENT       =92,
     MUDCOMM_OFFER      =93,
     MUDCOMM_POKE       =94,
     MUDCOMM_ADVANCE    =95,
     MUDCOMM_ACCUSE     =96,
     MUDCOMM_GRIN       =97,
     MUDCOMM_BOW        =98,
     MUDCOMM_OPEN       =99,
     MUDCOMM_CLOSE      =100,
     MUDCOMM_LOCK       =101,
     MUDCOMM_UNLOCK     =102,
     MUDCOMM_LEAVE      =103,
     MUDCOMM_APPLAUD    =104,
     MUDCOMM_BLUSH      =105,
     MUDCOMM_BURP       =106,
     MUDCOMM_CHUCKLE    =107,
     MUDCOMM_CLAP       =108,
     MUDCOMM_COUGH      =109,
     MUDCOMM_CURTSEY    =110,
     MUDCOMM_FART       =111,
     MUDCOMM_FLIP       =112,
     MUDCOMM_FONDLE     =113,
     MUDCOMM_FROWN      =114,
     MUDCOMM_GASP       =115,
     MUDCOMM_GLARE      =116,
     MUDCOMM_GROAN      =117,
     MUDCOMM_GROPE      =118,
     MUDCOMM_HICCUP     =119,
     MUDCOMM_LICK       =120,
     MUDCOMM_LOVE       =121,
     MUDCOMM_MOAN       =122,
     MUDCOMM_NIBBLE     =123,
     MUDCOMM_POUT       =124,
     MUDCOMM_PURR       =125,
     MUDCOMM_RUFFLE     =126,
     MUDCOMM_SHIVER     =127,
     MUDCOMM_SHRUG      =128,
     MUDCOMM_SING       =129,
     MUDCOMM_SLAP       =130,
     MUDCOMM_SMIRK      =131,
     MUDCOMM_SNAP       =132,
     MUDCOMM_SNEEZE     =133,
     MUDCOMM_SNICKER    =134,
     MUDCOMM_SNIFF      =135,
     MUDCOMM_SNORE      =136,
     MUDCOMM_SPIT       =137,
     MUDCOMM_SQUEEZE    =138,
     MUDCOMM_STARE      =139,
     MUDCOMM_STRUT      =140,
     MUDCOMM_THANK      =141,
     MUDCOMM_TWIDDLE    =142,
     MUDCOMM_WAVE       =143,
     MUDCOMM_WHISTLE    =144,
     MUDCOMM_WIGGLE     =145,
     MUDCOMM_WINK       =146,
     MUDCOMM_YAWN       =147,
     MUDCOMM_SNOWBALL   =148,
     MUDCOMM_WRITE      =149,
     MUDCOMM_HOLD       =150,
     MUDCOMM_FLEE       =151,
     MUDCOMM_SNEAK      =152,
     MUDCOMM_HIDE       =153,
     MUDCOMM_BACKSTAB   =154,
     MUDCOMM_PICK       =155,
     MUDCOMM_STEAL      =156,
     MUDCOMM_BASH       =157,
     MUDCOMM_RESCUE     =158,
     MUDCOMM_KICK       =159,
     MUDCOMM_FRENCH     =160,
     MUDCOMM_COMB       =161,
     MUDCOMM_MASSAGE    =162,
     MUDCOMM_TICKLE     =163,
     MUDCOMM_PRACTICE   =164,
     MUDCOMM_PAT        =165,
     MUDCOMM_EXAMINE    =166,
     MUDCOMM_TAKE       =167,
     MUDCOMM_INFO       =168,
     MUDCOMM_SPELLS     =169,
     MUDCOMM_PRACTISE   =170,
     MUDCOMM_CURSE      =171,
     MUDCOMM_USE        =172,
     MUDCOMM_WHERE      =173,
     MUDCOMM_LEVELS     =174,
     MUDCOMM_REROLL     =175,
     MUDCOMM_PRAY       =176,
     MUDCOMM_COLON      =177,
     MUDCOMM_BEG        =178,
     MUDCOMM_BLEED      =179,
     MUDCOMM_CRINGE     =180,
     MUDCOMM_DREAM      =181,
     MUDCOMM_FUME       =182,
     MUDCOMM_GROVEL     =183,
     MUDCOMM_HOP        =184,
     MUDCOMM_NUDGE      =185,
     MUDCOMM_PEER       =186,
     MUDCOMM_POINT      =187,
     MUDCOMM_PONDER     =188,
     MUDCOMM_PUNCH      =189,
     MUDCOMM_SNARL      =190,
     MUDCOMM_SPANK      =191,
     MUDCOMM_STEAM      =192,
     MUDCOMM_TACKLE     =193,
     MUDCOMM_TAUNT      =194,
     MUDCOMM_THINK      =195,
     MUDCOMM_WHINE      =196,
     MUDCOMM_WORSHIP    =197,
     MUDCOMM_YODEL      =198,
     MUDCOMM_TOGGLE     =199,
     MUDCOMM_WIZLIST    =200,
     MUDCOMM_CONSIDER   =201,
     MUDCOMM_GROUP      =202,
     MUDCOMM_RESTORE    =203,
     MUDCOMM_RETURN     =204,
     MUDCOMM_SWITCH     =205,
     MUDCOMM_QUAFF      =206,
     MUDCOMM_RECITE     =207,
     MUDCOMM_USERS      =208,
     MUDCOMM_POSE       =209,
     MUDCOMM_SILENCE    =210,
     MUDCOMM_WIZHELP    =211,
     MUDCOMM_CREDITS    =212,
     MUDCOMM_DISBAND    =213,
     MUDCOMM_VIS        =214,
     MUDCOMM_PFLAGS     =215,
     MUDCOMM_POOFIN     =216,
     MUDCOMM_WIZMSG     =217,
     MUDCOMM_DISPLAY    =218,
     MUDCOMM_ECHOA      =219,
     MUDCOMM_DEMOTE     =220,
     MUDCOMM_POOFOUT    =221,
     MUDCOMM_WIMPY      =222,
     MUDCOMM_BALANCE    =223,
     MUDCOMM_WIZLOCK    =224,
     MUDCOMM_DEPOSIT    =225,
     MUDCOMM_WITHDRAW   =226,
     MUDCOMM_IGNORE     =227,
     MUDCOMM_SETATTR    =228,
     MUDCOMM_TITLE      =229,
     MUDCOMM_AGGR       =230,
     MUDCOMM_GSAY       =231,
     MUDCOMM_CONSENT    =232,
     MUDCOMM_SETBIT     =233,
     MUDCOMM_HITALL     =234,
     MUDCOMM_TRAP       =235,
     MUDCOMM_MURDER     =236,
     MUDCOMM_237        =237,
     MUDCOMM_AUCTION    =238,
     MUDCOMM_CHANNEL    =239,
     MUDCOMM_FILL       =240,
     MUDCOMM_GOSSIP     =241,
     MUDCOMM_NOKILL     =242,
     MUDCOMM_PAGE       =243,
     MUDCOMM_MUDCOMMS   =244,
     MUDCOMM_ATTRIBUTES =245,
     MUDCOMM_RULES      =246,
     MUDCOMM_TRACK      =247,
     MUDCOMM_LISTEN     =248,
     MUDCOMM_DISARM     =249,
     MUDCOMM_PARRY      =250,
     MUDCOMM_DELETE     =251,
     MUDCOMM_BAN        =252,
     MUDCOMM_ALLOW      =253,
     MUDCOMM_PASSWORD   =254,
     MUDCOMM_DESCRIPTION =255,
     MUDCOMM_BRIBE      =256,
     MUDCOMM_BONK       =257,
     MUDCOMM_CALM       =258,
     MUDCOMM_RUB        =259,
     MUDCOMM_CENSOR     =260,
     MUDCOMM_CHOKE      =261,
     MUDCOMM_DROOL      =262,
     MUDCOMM_FLEX       =263,
//     MUDCOMM_JUMP       =264,
     MUDCOMM_LEAN       =265,
     MUDCOMM_MOON       =266,
     MUDCOMM_OGLE       =267,
     MUDCOMM_PANT       =268,
     MUDCOMM_PINCH      =269,
     MUDCOMM_PUSH       =270,
     MUDCOMM_SCARE      =271,
     MUDCOMM_SCOLD      =272,
     MUDCOMM_SEDUCE     =273,
     MUDCOMM_SHOVE      =274,
     MUDCOMM_SHUDDER    =275,
     MUDCOMM_SHUSH      =276,
     MUDCOMM_SLOBBER    =277,
     MUDCOMM_SMELL      =278,
     MUDCOMM_SNEER      =279,
     MUDCOMM_SPIN       =280,
     MUDCOMM_SQUIRM     =281,
     MUDCOMM_STOMP      =282,
     MUDCOMM_STRANGLE   =283,
     MUDCOMM_STRETCH    =284,
     MUDCOMM_TAP        =285,
     MUDCOMM_TEASE      =286,
     MUDCOMM_TIPTOE     =287,
     MUDCOMM_TWEAK      =288,
     MUDCOMM_TWIRL      =289,
     MUDCOMM_UNDRESS    =290,
     MUDCOMM_WHIMPER    =291,
     MUDCOMM_EXCHANGE   =292,
     MUDCOMM_RELEASE    =293,
     MUDCOMM_SEARCH     =294,
     MUDCOMM_FLY        =295,
     MUDCOMM_LEVITATE   =296,
     MUDCOMM_SECRET     =297,
     MUDCOMM_LOOKUP     =298,
     MUDCOMM_REPORT     =299,
     MUDCOMM_SPLIT      =300,
     MUDCOMM_WORLD      =301,
     MUDCOMM_JUNK       =302,
     MUDCOMM_PETITION   =303,
     MUDCOMM_DO         =304,
     MUDCOMM_APOSTROPHE =305,
     MUDCOMM_CARESS     =306,
     MUDCOMM_BURY       =307,
     MUDCOMM_DONATE     =308,
     MUDCOMM_DIG        =309,
     MUDCOMM_SCALE      =310,
     MUDCOMM_CUT        =311,
     MUDCOMM_SLASH      =312,
     MUDCOMM_HACK       =313,
     MUDCOMM_YELL       =314,
     MUDCOMM_RING       =315,
//     MUDCOMM_TUG        =316,
     MUDCOMM_JUMP       =317,
     MUDCOMM_TRACE      =318,
     MUDCOMM_WATER      =319,
     MUDCOMM_TOUCH      =320,
     MUDCOMM_SCRATCH    =321,
     MUDCOMM_WINCE      =322,
     MUDCOMM_TOSS       =323,
     MUDCOMM_FLAME      =324,
     MUDCOMM_ARCH       =325,
     MUDCOMM_AMAZE      =326,
     MUDCOMM_BATHE      =327,
     MUDCOMM_EMBRACE    =328,
     MUDCOMM_BRB        =329,
     MUDCOMM_ACK        =330,
     MUDCOMM_CHEER      =331,
     MUDCOMM_SNORT      =332,
     MUDCOMM_EYEBROW    =333,
     MUDCOMM_BANG       =334,
     MUDCOMM_PILLOW     =335,
     MUDCOMM_NAP        =336,
     MUDCOMM_NOSE       =337,
     MUDCOMM_RAISE      =338,
     MUDCOMM_HAND       =339,
     MUDCOMM_PULL       =340,
     MUDCOMM_TUG        =341,
     MUDCOMM_WET        =342,
     MUDCOMM_MOSH       =343,
     MUDCOMM_WAIT       =344,
     MUDCOMM_HI5        =345,
     MUDCOMM_ENVY       =346,
     MUDCOMM_FLIRT      =347,
     MUDCOMM_BARK       =348,
     MUDCOMM_WHAP       =349,
     MUDCOMM_ROLL       =350,
     MUDCOMM_BLINK      =351,
     MUDCOMM_DUH        =352,
     MUDCOMM_GAG        =353,
     MUDCOMM_GRUMBLE    =354,
     MUDCOMM_DROPKICK   =355,
     MUDCOMM_WHATEVER   =356,
     MUDCOMM_FOOL       =357,
     MUDCOMM_NOOGIE     =358,
     MUDCOMM_MELT       =359,
     MUDCOMM_SMOKE      =360,
     MUDCOMM_WHEEZE     =361,
     MUDCOMM_BIRD       =362,
     MUDCOMM_BOGGLE     =363,
     MUDCOMM_HISS       =364,
     MUDCOMM_BITE       =365,
};

enum ItemTypes { 
	TYPE_NONE = 0,
	TYPE_LIGHT,
	TYPE_SCROLL,
    TYPE_WAND,
    TYPE_STAFF,
    TYPE_WEAPON,
    TYPE_RANGED_WEAPON,
    TYPE_MISSILEWEAP,
    TYPE_TREASURE,
    TYPE_ARMOR,
    TYPE_POTION,
    TYPE_CLOTHING,
    TYPE_OTHER,
    TYPE_TRASH,
    TYPE_TRAP,
    TYPE_CONTAINER,
    TYPE_NOTE,
    TYPE_DRINK_CON,
    TYPE_KEY,
    TYPE_FOOD,
    TYPE_MONEY,
    TYPE_PEN,
    TYPE_BOAT,
    TYPE_BOOK, //EXCLUDE
    TYPE_BATTERY, //EXCLUDE
    TYPE_TELEPORT,
    TYPE_TIMER,
    TYPE_VEHICLE,
    TYPE_SHIP,
    TYPE_SWITCH,
    TYPE_QUIVER,
    TYPE_LOCKPICK,
    TYPE_INSTRUMENT,
    TYPE_SPELLBOOK,
    TYPE_TOTEM,
    TYPE_STORAGECHEST,
    TYPE_SCABBARD,
    TYPE_SHIELD,
    TYPE_CORPSE_NPC,
    TYPE_CORPSE_PC,
    TYPE_PORTAL,
    TYPE_PILL,
    TYPE_HERB,
    TYPE_MESSAGE_BOARD,
    TYPE_PIPE, 
    TYPE_WANTED_LIST,
    TYPE_WALL,
	TYPE_UNUSED,// ExCLUDE!!!!!!!
    TYPE_AMMO,
    TYPE_TRADITION_ICON,
    TYPE_ROPE,
    TYPE_DISGUISE_KIT,
    TYPE_CONTROL_PANEL,
    TYPE_VEHICLE_KEY,
    TYPE_SUMMON,
	TYPE_GLYPH,
	TYPE_HOLY,
	TYPE_SPELLSCROLL,
    MAX_ITEM_TYPE,
};

enum ShipTypes 
{	
	VEH_NONE				= 0,
	VEH_SHIP_ANY_WATER		= 1, // multi-purpose boats, medium size
	VEH_SHIP_SHALLOWS		= 2, // rowboats and canoes
	VEH_SHIP_DEEPWATER		= 3, // giant boats, submarines
	VEH_SHIP_ANY_TERRAIN	= 4, // hovercraft, magic carpets, etc.
	VEH_NO_WATER			= 5, // all-terrain land vehicles
	VEH_FLATLAND			= 6, // flat land vehicles like carts and buggies
	VEH_SHIP_SPELLJAMMER	= 7, // any-terrain spelljammer
	VEH_SHIP_SJ_LAND		= 8, // spelljammer that can't go in the water
	VEH_SHIP_SJ_WATER		= 9, // spelljammer that can't go on land
	VEH_SHIP_SJ_SKYONLY		= 10,// spelljammer that can't land
	VEH_WAGON				= 11,// wagon or other land vehicle
	VEH_CREATURE			= 12,// Giant creature
	VEH_MAX,
}; 

enum ShipClass
{
	SHIP_NONE = 0,
	SHIP_SMALL_WAR,
	SHIP_MEDIUM_WAR,
	SHIP_LARGE_WAR,
	SHIP_SMALL_CARGO,
	SHIP_MEDIUM_CARGO,
	SHIP_LARGE_CARGO,
	SHIP_MAX,
};

class ItemType 
{
public:
	char* name; //name of item type
	bool sellable; //if the item type is sold or bought
	bool in_use; //is the item type in use
};

extern const ItemType item_types[MAX_ITEM_TYPE];

extern const BITVECT_DATA ITEM_GLOW;
extern const BITVECT_DATA ITEM_NOSHOW;
extern const BITVECT_DATA ITEM_BURIED; // Not yet implemented
extern const BITVECT_DATA ITEM_NOSELL;
extern const BITVECT_DATA ITEM_EVIL;
extern const BITVECT_DATA ITEM_INVIS;
extern const BITVECT_DATA ITEM_MAGIC;
extern const BITVECT_DATA ITEM_NODROP;
extern const BITVECT_DATA ITEM_BLESS;
extern const BITVECT_DATA ITEM_ANTI_GOOD;
extern const BITVECT_DATA ITEM_ANTI_EVIL;
extern const BITVECT_DATA ITEM_ANTI_NEUTRAL;
extern const BITVECT_DATA ITEM_SECRET;
extern const BITVECT_DATA ITEM_FLOAT; // Not yet implemented
extern const BITVECT_DATA ITEM_NOBURN;
extern const BITVECT_DATA ITEM_NOLOCATE; // Not yet implemented
extern const BITVECT_DATA ITEM_NOID;
extern const BITVECT_DATA ITEM_NOSUMMON; // Not yet implemented
extern const BITVECT_DATA ITEM_LIT; 
extern const BITVECT_DATA ITEM_FLY; 
extern const BITVECT_DATA ITEM_TRANSIENT;
extern const BITVECT_DATA ITEM_NOSLEEP; // Not yet implemented
extern const BITVECT_DATA ITEM_NOCHARM; // Not yet implemented
extern const BITVECT_DATA ITEM_TWOHANDED;
extern const BITVECT_DATA ITEM_NORENT; // Not yet implemented
extern const BITVECT_DATA ITEM_GOODONLY; // Not yet implemented
extern const BITVECT_DATA ITEM_HUM;
extern const BITVECT_DATA ITEM_LEVITATES;
extern const BITVECT_DATA ITEM_INVENTORY;
extern const BITVECT_DATA ITEM_WAS_DISARMED; // Not yet implemented - probably will not be used.
extern const BITVECT_DATA ITEM_WHOLEBODY; // Not yet implemented
extern const BITVECT_DATA ITEM_WHOLEHEAD; // Not yet implemented
// extra2 flags, basternae area format - Veygoth
extern const BITVECT_DATA ITEM_SILVER; // Not yet implemented
extern const BITVECT_DATA ITEM_THROW_RETURN; // Not yet implemented
extern const BITVECT_DATA ITEM_THROW_ONEROOM; // Not yet implemented
extern const BITVECT_DATA ITEM_THROW_TWOROOMS; // Not yet implemented
extern const BITVECT_DATA ITEM_ENLARGED; // Not yet implemented
extern const BITVECT_DATA ITEM_REDUCED; // Not yet implemented
extern const BITVECT_DATA ITEM_POISONED;
extern const BITVECT_DATA ITEM_SAVE;
extern const BITVECT_DATA ITEM_ALTERED; // fields are not the same as prototype
extern const BITVECT_DATA ITEM_NO_FLEE; // makes wielder !flee
extern const BITVECT_DATA ITEM_NO_REPAIR; //makes item non repairable
extern const BITVECT_DATA ITEM_VARIABLE; // Variable stats (Veygoth)
extern const BITVECT_DATA ITEM_DELETE; 
extern const BITVECT_DATA ITEM_REMOVEPL;
extern const BITVECT_DATA ITEM_RELOAD;
extern const BITVECT_DATA ITEM_ARTIFACT;
extern const BITVECT_DATA ITEM_MINORARTI;
extern const BITVECT_DATA ITEM_UNIQUE;
extern const BITVECT_DATA ITEM_UNDEAD;
extern const BITVECT_DATA ITEM_FLAG;

class extra_flags 
{
public:
	char* name; //name of flag
	const BITVECT_DATA *bv; //bitvector
	bool used; //flag is in use or not
};

enum {NUM_ITEM_EXTRA_VECTORS = 3};

enum WearLocs {
	ITEM_TAKE			=	BV00,
	ITEM_WEAR_FINGER	=	BV01,
	ITEM_WEAR_NECK		=	BV02,
	ITEM_WEAR_BODY		=	BV03,
	ITEM_WEAR_HEAD		=	BV04,
	ITEM_WEAR_LEGS		=	BV05,
	ITEM_WEAR_FEET		=	BV06,
	ITEM_WEAR_HANDS		=	BV07,
	ITEM_WEAR_ARMS		=	BV08,
	ITEM_WEAR_SHIELD	=	BV09,
	ITEM_WEAR_ABOUT		=	BV10,
	ITEM_WEAR_WAIST		=	BV11,
	ITEM_WEAR_WRIST		=	BV12,
	ITEM_WIELD			=	BV13,
	ITEM_HOLD			=	BV14,
	ITEM_WEAR_EYES		=	BV17,
	ITEM_WEAR_FACE		=	BV18,
	ITEM_WEAR_EAR		=	BV19,
	ITEM_QUIVER			=	BV20,
	ITEM_BADGE			=	BV21,
	ITEM_WEAR_ONBACK	=	BV22,
	ITEM_ATTACH_BELT	=	BV23,
	ITEM_HORSE_BODY		=	BV24,
	ITEM_TAIL			=	BV25,
	ITEM_NOSE			=	BV26,
	ITEM_HORNS			=	BV27,
};

class wear_data 
{	
public:
	char *name; //name of wear location
	int bv; //bitvector
};

enum { NUM_ITEM_WEAR_VECTORS = 26};

extern const BITVECT_DATA	USE_ANYONE;
extern const BITVECT_DATA	USE_WARRIOR;
extern const BITVECT_DATA	USE_RANGER;
extern const BITVECT_DATA	USE_PALADIN;
extern const BITVECT_DATA	USE_ANTI;
extern const BITVECT_DATA	USE_CLERIC;
extern const BITVECT_DATA	USE_MONK;
extern const BITVECT_DATA	USE_DRUID;
extern const BITVECT_DATA	USE_SHAMAN;
extern const BITVECT_DATA	USE_SORCERER;
extern const BITVECT_DATA	USE_NECROMANCER;
extern const BITVECT_DATA	USE_ELEMENTAL;
extern const BITVECT_DATA	USE_PSI;
extern const BITVECT_DATA	USE_THIEF;
extern const BITVECT_DATA	USE_ASSASSIN;
extern const BITVECT_DATA	USE_MERCENARY;
extern const BITVECT_DATA	USE_BARD;
extern const BITVECT_DATA	USE_NOHUMAN;
extern const BITVECT_DATA	USE_NOGREYELF;
extern const BITVECT_DATA	USE_NOHALFELF;
extern const BITVECT_DATA	USE_NODWARF;
extern const BITVECT_DATA	USE_NOHALFLING;
extern const BITVECT_DATA	USE_NOGNOME;
extern const BITVECT_DATA	USE_NOBARBARIAN;
extern const BITVECT_DATA	USE_NODUERGAR;
extern const BITVECT_DATA	USE_NODROW;
extern const BITVECT_DATA	USE_NOTROLL;
extern const BITVECT_DATA	USE_NOOGRE;
extern const BITVECT_DATA	USE_ANTIGOODRACE;
extern const BITVECT_DATA	USE_NOORC;
extern const BITVECT_DATA	USE_ANTIEVILRACE;
extern const BITVECT_DATA	USE_NOTHRIKREEN; 
extern const BITVECT_DATA	USE_NOCENTAUR;
extern const BITVECT_DATA	USE_NOGITHYANKI;
extern const BITVECT_DATA	USE_NOMINOTAUR;
extern const BITVECT_DATA	USE_ANTIMALE;
extern const BITVECT_DATA	USE_ANTIFEMALE;
extern const BITVECT_DATA	USE_ANTINEUTER;
extern const BITVECT_DATA	USE_NOHALFORC;
extern const BITVECT_DATA	USE_NOSAHAUGIN;
extern const BITVECT_DATA	USE_NOGOBLIN;
extern const BITVECT_DATA	USE_NORAKSHASA;
extern const BITVECT_DATA	USE_NOFLIND;
extern const BITVECT_DATA	USE_NOGITHZERAI;
extern const BITVECT_DATA	USE_NODUAL;

class AntiFlags 
{
public:
	char* name;
	const BITVECT_DATA *bv;
};

enum Materials {
	MAT_UNDEFINED = 0,
	MAT_NONSUBSTANTIAL,
	MAT_FLESH,
	MAT_CLOTH,
	MAT_BARK,
	MAT_SOFTWOOD,
	MAT_HARDWOOD,
	MAT_GLASS,
	MAT_CRYSTAL,
	MAT_CERAMIC,
	MAT_BONE,
	MAT_STONE,
	MAT_HIDE,
	MAT_LEATHER,
	MAT_CUREDLEATHER,
	MAT_IRON,
	MAT_STEEL,
	MAT_BRASS,
	MAT_MITHRIL,
	MAT_ADAMANTIUM,
	MAT_BRONZE,
	MAT_COPPER,
	MAT_SILVER,
	MAT_ELECTRUM,
	MAT_GOLD,
	MAT_PLATINUM,
	MAT_GEM,
	MAT_DIAMOND,
	MAT_PAPER,
	MAT_PARCHMENT,
	MAT_LEAVES,
	MAT_RUBY,
	MAT_EMERALD,
	MAT_SAPPHIRE,
	MAT_IVORY,
	MAT_DRAGONSCALE,
	MAT_OBSIDIAN,
	MAT_GRANITE,
	MAT_MARBLE,
	MAT_LIMESTONE,
	MAT_LIQUID,
	MAT_BAMBOO,
	MAT_REEDS,
	MAT_HEMP,
	MAT_GLASSTEEL,
	MAT_EGGSHELL,
	MAT_CHITINOUS,
	MAT_REPTILESCALE,
	MAT_GENERICFOOD,
	MAT_RUBBER,
	MAT_FEATHER,
	MAT_WAX,
	MAT_PEARL,
	MAT_SILK,
	MAT_SPIDERSILK,
	MAT_JADE,
	MAT_LEAD,
	MAX_MATERIAL,
};

enum {
	CRAFT_TERRIBLE	=	0,
	CRAFT_EXT_POOR,
	CRAFT_VERY_POOR,
	CRAFT_FAIRLY_POOR,
	CRAFT_WELL_BELOW_AVE,
	CRAFT_BELOW_AVE,
	CRAFT_SLIGHT_BELOW_AVE,
	CRAFT_AVERAGE,
	CRAFT_SLIGHT_ABOVE_AVE,
	CRAFT_ABOVE_AVE,
	CRAFT_WELL_ABOVE_AVE,
	CRAFT_EXCELLENT,
	CRAFT_SKILLED_ARTISAN,
	CRAFT_GIFTED_ARTISAN,
	CRAFT_MASTER_ARTISAN,
	CRAFT_ONEOFAKIND,
	MAX_CRAFT,
};

enum { MAX_ITEM_VALUE = 8 };

enum Applies
{
	APPLY_NONE =0,
	APPLY_STR,
	APPLY_DEX,
	APPLY_INT,
	APPLY_WIS,
	APPLY_CON,
	APPLY_SEX,
	APPLY_CLASS,
	APPLY_LEVEL,
	APPLY_AGE,
	APPLY_HEIGHT,
	APPLY_WEIGHT,
	APPLY_MANA,
	APPLY_HIT,
	APPLY_MOVE,
	APPLY_GOLD,
	APPLY_EXP,
	APPLY_AC,
	APPLY_HITROLL,
	APPLY_DAMROLL,
	APPLY_SAVING_PARA,
	APPLY_SAVING_ROD,
	APPLY_SAVING_PETRI,
	APPLY_SAVING_BREATH,
	APPLY_SAVING_SPELL,
	APPLY_FIRE_PROT,
	APPLY_AGI,
	APPLY_POW,
	APPLY_CHA,
	APPLY_LUK,
	APPLY_MAX_STR,
	APPLY_MAX_DEX,
	APPLY_MAX_INT,
	APPLY_MAX_WIS,
	APPLY_MAX_CON,
	APPLY_MAX_AGI,
	APPLY_MAX_POW,
	APPLY_MAX_CHA,
	APPLY_MAX_LUK,
	APPLY_RACE_STR,
	APPLY_RACE_DEX,
	APPLY_RACE_INT,
	APPLY_RACE_WIS,
	APPLY_RACE_CON,
	APPLY_RACE_AGI,
	APPLY_RACE_POW,
	APPLY_RACE_CHA,
	APPLY_RACE_LUK,
	APPLY_CURSE,
	APPLY_RESISTANT,
	APPLY_IMMUNE,
	APPLY_SUSCEPTIBLE,
	APPLY_RACE,
	APPLY_SIZE,
	APPLY_APPARENT_RACE,
	APPLY_VULNERABLE,
	APPLY_SPELL_RESIST,
	APPLY_HIGHEST,
};

enum WeaponTypes
{
	WEAPON_NONE				= 0,
	WEAPON_AXE				= 1,  // axes - slashing
	WEAPON_DAGGER			= 2,  // daggers, knives - piercing, slashing (with -)
	WEAPON_FLAIL			= 3,  // flails - whip
	WEAPON_HAMMER			= 4,  // hammers - bludgeon
	WEAPON_LONGSWORD		= 5,  // long swords - slashing/piercing (with -)
	WEAPON_MACE				= 6,  // mace - bludgeon
	WEAPON_SPIKED_MACE		= 7,  // spiked mace - bludgeon with pierce thrown in
	WEAPON_POLEARM			= 8,  // polearm - halberds, pikes, etc - piercing
	WEAPON_SHORTSWORD		= 9,  // short swords - slashing/piercing
	WEAPON_CLUB				= 10,  // clubs - bludgeon
	WEAPON_SPIKED_CLUB		= 11,  // spiked clubs - bludgeon and piercing
	WEAPON_STAFF			= 12,  // staff - like club but longer, maybe 2-handed - bludgeon
	WEAPON_2HANDSWORD		= 13,  // two-handed swords - slash
	WEAPON_WHIP				= 14,  // whips - whip
	WEAPON_PICK				= 15,  // pick - pierce
	WEAPON_LANCE			= 16,  // lance - special handling probably
	WEAPON_SICKLE			= 17,  // sickle - slash/pierce?
	WEAPON_FORK				= 18,  // forks/rakes - slash
	WEAPON_HORN				= 19,  // curved piercer - piercing
	WEAPON_NUMCHUCKS		= 20,  // numchucks - bludgeon
	WEAPON_SPEAR 			=21,
	WEAPON_BATTLEAXE		=22,
	WEAPON_KATANA			=23,
	WEAPON_BASTARDSWORD		=24,
	WEAPON_MORNINGSTAR		=25,
    WEAPON_RAPIER			=26,
    WEAPON_SCIMITAR			=27,
    WEAPON_SABRE			=28,
    WEAPON_CUTLASS			=29,
    WEAPON_WARHAMMER		=30,
    WEAPON_CLAYMORE			=32,
    WEAPON_KHOPESH			=33,
    WEAPON_FLAMBERGE		=34,
    WEAPON_GREATAXE			=35,
    WEAPON_HALBERD			=36,
    WEAPON_GLAIVE			=37,
    WEAPON_FALCHION			=38,
    WEAPON_NAGINATA			=39,
    WEAPON_PIKE				=40,
    WEAPON_WAKIZASHI		=41,
    WEAPON_SCYTHE			=42,
    WEAPON_PARRYINGDAGGER	=43, // includes sai
    WEAPON_KNIFE			=44,
    WEAPON_DIRK				=45,
    WEAPON_KRIS				=46,// that funny-lookin' wavy dagger
    WEAPON_CLAW				=47,
    WEAPON_FANG				=48,
    WEAPON_GYTHKA			=49,
    WEAPON_CHATKCHA			=50,
    WEAPON_SCEPTER			=51,
    WEAPON_QUARTERSTAFF		=52,
    WEAPON_STILETTO			=53,
    WEAPON_TRIDENT			=54,
    WEAPON_MAX,	
};

enum Liquids
{
     LIQ_WATER      =0,
     LIQ_BEER       =1,
     LIQ_WINE       =2,
     LIQ_ALE        =3,
     LIQ_DARKALE    =4,
     LIQ_WHISKY     =5,
     LIQ_LEMONADE   =6,
     LIQ_FIREBRT    =7,
     LIQ_LOCALSPC   =8,
     LIQ_SLIME      =9,
     LIQ_MILK       =10,
     LIQ_TEA        =11,
     LIQ_COFFEE     =12,
     LIQ_BLOOD      =13,
     LIQ_SALTWATER  =14,
     LIQ_COKE       =15,
     LIQ_WHITEWINE  =16,
     LIQ_ROOTBEER   =17,
     LIQ_CHAMPAGNE  =18,
     LIQ_VODKA		=19,
     LIQ_ABSINTH    =20,
     LIQ_BRANDY     =21,
     LIQ_SCHAPPS    =22,
     LIQ_ORANGEJUICE=23,
     LIQ_SHERRY     =24,
     LIQ_RUM		=25,
     LIQ_PORT       =26,
     LIQ_HOLYWATER  =27,
     LIQ_UNHOLYWAT  =28,
	 LIQ_MAX,
};

enum Instruments
{
	INSTRUMENT_FLUTE             =184,
	INSTRUMENT_LYRE              =185,
	INSTRUMENT_MANDOLIN          =186,
	INSTRUMENT_HARP              =187,
	INSTRUMENT_DRUMS            = 188,
	INSTRUMENT_HORN              =189,
	INSTRUMENT_PIPES             =190,
	INSTRUMENT_FIDDLE            =191,
	INSTRUMENT_DULCIMER          =192,
	INSTRUMENT_MAX,
};

enum Totem
{
	TOTEM_L_ANIMAL			=BV00,
	TOTEM_G_ANIMAL			=BV01,
	TOTEM_L_ELEMENTAL       =BV02,
	TOTEM_G_ELEMENTAL		=BV03,
	TOTEM_L_SPIRIT			=BV04,
	TOTEM_G_SPIRIT			=BV05,
};

enum DamTypes
{
	DAM_NONE	= 0,		/*  weapon damage types */
	DAM_BASH	= 1,
	DAM_PIERCE	= 2,
	DAM_SLASH	= 3,
	DAM_MAX,
};

enum MissileTypes
{
	MISSILE_NONE = 0,
	MISSILE_ARROW                   =1,
	MISSILE_LIGHT_CBOW_QUARREL      =2,
	MISSILE_HEAVY_CBOW_QUARREL      =3,
	MISSILE_HAND_CBOW_QUARREL       =4,
	MISSILE_SLING_BULLET            =5,
	MISSILE_MAX,
};

enum ShieldType
{
	SHIELDTYPE_NONE    =0,
	SHIELDTYPE_STRAPARM =1,  // strapped to the arm - bucklers, others
	SHIELDTYPE_HANDHELD =2, // held by hand
	SHIELDTYPE_MAX
};

enum ShieldShape
{
	SHIELDSHAPE_NONE     = 0,
	SHIELDSHAPE_CIRCULAR =1,  // perfect circle
	SHIELDSHAPE_SQUARE   =2,  // square..
	SHIELDSHAPE_RECTVERT =3,  // a rectangle aligned vertically
	SHIELDSHAPE_RECTHORZ =4,  // horizontally..  you never know
	SHIELDSHAPE_OVALVERT =5,  // vertical 'oval'
	SHIELDSHAPE_OVALHORZ =6,  // horizontal 'oval' - you never know
	SHIELDSHAPE_TRIBIGUP =7, // triangle - wide side on top
	SHIELDSHAPE_TRISMLUP =8,  // triangle - narrow point on top
	SHIELDSHAPE_MAX,
};

enum ShieldSize
{
	SHIELDSIZE_NONE = 0,
	SHIELDSIZE_TINY     =1,  // really small suckers
	SHIELDSIZE_SMALL    =2,  // bucklers, small shields
	SHIELDSIZE_MEDIUM   =3,  // normal shields
	SHIELDSIZE_LARGE    =4,  // big shields
	SHIELDSIZE_HUGE     =5,  // huge shields (might not need this)
	SHIELDSIZE_MAX,
};

enum ContFlags
{
	CONT_CLOSEABLE		   =BV00,
	CONT_PICKPROOF		   =BV01,
	CONT_CLOSED		   =BV02,
	CONT_LOCKED		   =BV03,
};

struct ApplyType
{
	int loc;
	int value;
};

class object_data 
{
public:	
	static char class_name[];
	static int class_index;
	static object_data *obj_head;				//head of the object list
	static int high_obj_vnum;					//highest obj vnum not in use
	static object_data *def_obj;

public:
	HTREEITEM			m_tThis;

	int					vnum;					//objects virtual number
    object_data *		next;					//next object in list
    obj_index *			contains;				// contents for container objects

    extra_desc *		first_extra_descr;		//begging of objs extra descriptions
	extra_desc *		last_extra_desc;		//last of objs extra descriptions
    CString				name;					//keywords of the object
    CString				short_descr;			//shows in messages/inventory
    CString				description;			//shows in room
    int 				item_type;				//type of item 
    int 				extra_flags[NUM_ITEM_EXTRA_VECTORS]; //object bit values
    int					affected_by[NUM_AFFECT_VECTORS]; //spells this object grants
    int 				wear_flags;				//where the object can be worn
    int					anti_flags[2];				//anti usage flags
    int					material;				//material obj is made of
    int					size;					//size of object
    int					volume;					//volume object takes up
    int					craftsmanship;			//craftsmanship
    int 				weight;					//weight of object
    int 				level;					//level of the object
    int					value[MAX_ITEM_VALUE];  //used with item_type
    int					condition;				//how long till object break 0-100
	ApplyType			applies[2];
	TrapData			trap;

	int dummy;
	CString dummy_str;

public:
	object_data(); //constructor

	void AddToList(); //adds object to main list
	void RemoveFromList(); //removes object from main list

	bool AffIsSet(const BITVECT_DATA& bv); //checks object affects
	void SetAffBit(const BITVECT_DATA& bv); //sets object affects
	void RemoveAffBit(const BITVECT_DATA& bv); //removes object affect

	bool ExtraIsSet(const BITVECT_DATA& bv); //checks object extra
	void SetExtraBit(const BITVECT_DATA& bv); //sets object extra
	void RemoveExtraBit(const BITVECT_DATA& bv); //removes object extra

	obj_index *AddContent(object_data *obj);
	void AddContent(obj_index *obj);
	void RemoveContent(obj_index*obj);
	void RemoveContents();

	bool IsContainer();

	obj_index *AddToInv(obj_index **head); //adds obj to list head points to returns the new index
	
	CString ShowObject();			//Formats the object for displaying
	bool IsName(CString &arg);
	bool IsWearable(int loc);
};

class obj_index
{
public:
	static char class_name[];
	static int class_index;
	static obj_index* o_ind_head;

public:
	HTREEITEM m_tThis;
	HTREEITEM m_tRoom;
	HTREEITEM m_tContents;

	int vnum; //vnum of object
	int wear_loc; //wear worn -1 for not worn
	
	room_data	*in_room;
	mob_index	*on_mob;
	object_data *in_obj;
	
	obj_index *n_list;

	obj_index *next; //next content in inventory
	obj_index *contents; //contents for single object not global
	object_data *obj; //the actual object in inventory

public:
	obj_index() : vnum(0), wear_loc(-1), next(NULL), 
		contents(NULL), obj(NULL), in_room(NULL), 
		on_mob(NULL), in_obj(NULL), n_list(NULL) 
	{ }; //constructor

	obj_index *AddContent(object_data *obj);
	void RemoveContent(obj_index **index);
	void RemoveContents();

	void AddToList();
	void RemoveFromList();

	bool IsContainer();
	extra_desc *GetFirstExtraDesc();
	bool IsName(CString &arg);

	CString ShowObject();
	CString GetShortName();

	bool IsWearable(int loc);

	CString GetExtraDesc(CString &str);
};

object_data *GetObjByVnum(int vnum); //gets object by vnum

struct flag_types
{
	char *name;
	int  index;
};

int ExtraFlagCount(); //counts extra flags for objects
int AntiFlagsCount(); //counts anti_flags1 entries
int InstrumentCount();
int GetWeapCount();
int CommandCount();
int TotemCount();
int ContainerCount();
int ShipTypeCount();

extern const CString craftsmanship[];
extern const CString materials[MAX_MATERIAL];
extern const AntiFlags anti_flags[];
extern const wear_data wear_locs[NUM_ITEM_WEAR_VECTORS];
extern const extra_flags obj_flags[];
extern const CString apply_names[];
extern const flag_types weapon_types[];
extern const CString liquid_types[];
extern const CString dam_types[];
extern const flag_types instrument_types[];
extern const CString missile_types[];
extern const flag_types comm_types[];
extern const CString shield_size[];
extern const CString shield_shape[];
extern const CString shield_types[];
extern const flag_types totem_types[];
extern const flag_types cont_types[];
extern const flag_types ship_types[];
extern const CString vehicle_types[];

#endif