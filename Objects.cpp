#include "StdAfx.h"

object_data *object_data::obj_head = NULL;
int object_data::high_obj_vnum = 1;

obj_index* obj_index::o_ind_head = NULL;

char object_data::class_name[] = "object_data";
int object_data::class_index = OBJECT_DATA;

char obj_index::class_name[] = "obj_index";
int obj_index::class_index = OBJ_INDEX;
object_data *object_data::def_obj = NULL;

const CString vehicle_types[] =
{
	"None",
	"Ship Any Water",
	"Ship Shallow Water",
	"Ship Deep Water",
	"All Terrain",
	"Land Only",
	"Flat Land Only",
	"Spell Jammer",
	"Spell Jammer Land",
	"Spell Jammer Water",
	"Spell Jammer Sky",
	"Wagon",
	"Creature",
};
 
const flag_types ship_types[] =
{
	{"None",			SHIP_NONE},
	{"Small Combat",	SHIP_SMALL_WAR},
	{"Medium Combat",	SHIP_MEDIUM_WAR},
	{"Large Combat",	SHIP_LARGE_WAR},
	{"Small Cargo",		SHIP_SMALL_CARGO},
	{"Medium Cargo",	SHIP_MEDIUM_CARGO},
	{"Large Cargo",		SHIP_LARGE_CARGO},
};

const flag_types comm_types[] =
{
    {"north",	 MUDCOMM_NORTH      },
    {"east",     MUDCOMM_EAST       },
    {"south",     MUDCOMM_SOUTH      },
    {"west",     MUDCOMM_WEST       },
    {"up",     MUDCOMM_UP         },
    {"down",     MUDCOMM_DOWN       },
    {"enter",     MUDCOMM_ENTER      },
    {"turn",     MUDCOMM_TURN       },
    {"kiss",     MUDCOMM_KISS       },
    {"get",     MUDCOMM_GET        },
    {"drink",     MUDCOMM_DRINK      },
    {"eat",     MUDCOMM_EAT        },
    {"wear",     MUDCOMM_WEAR       },
    {"wield",     MUDCOMM_WIELD      },
    {"look",     MUDCOMM_LOOK       },
    {"say",     MUDCOMM_SAY        },
    {"shout",     MUDCOMM_SHOUT      },
    {"tell",     MUDCOMM_TELL       },
    {"climb",     MUDCOMM_CLIMB      },
    {"swing",     MUDCOMM_SWING      },
    {"bounce",     MUDCOMM_BOUNCE     },
    {"smile",     MUDCOMM_SMILE      },
    {"dance",     MUDCOMM_DANCE      },
    {"kill",     MUDCOMM_KILL       },
    {"cackle",     MUDCOMM_CACKLE     },
    {"laugh",     MUDCOMM_LAUGH      },
    {"giggle",	 MUDCOMM_GIGGLE     },
    {"shake",     MUDCOMM_SHAKE      },
    {"puke",	 MUDCOMM_PUKE       },
    {"growl",	 MUDCOMM_GROWL      },
    {"scream",     MUDCOMM_SCREAM     },
    {"insult",     MUDCOMM_INSULT     },
    {"comfort",     MUDCOMM_COMFORT    },
    {"nod",     MUDCOMM_NOD        },
    {"sigh",     MUDCOMM_SIGH       },
    {"sulk",     MUDCOMM_SULK       },
    {"part",     MUDCOMM_PART       },
    {"twist",     MUDCOMM_TWIST      },
    {"chant",     MUDCOMM_CHANT      },
    {"stand",     MUDCOMM_STAND      },
    {"sit",     MUDCOMM_SIT        },
    {"rest",     MUDCOMM_REST       },
    {"sleep",     MUDCOMM_SLEEP      },
    {"wake",     MUDCOMM_WAKE       },
    {"dust",     MUDCOMM_DUST       },
    {"hunt",     MUDCOMM_HUNT       },
    {"hug",     MUDCOMM_HUG        },
    {"snuggle",     MUDCOMM_SNUGGLE    },
    {"cuddle",     MUDCOMM_CUDDLE     },
    {"nuzzle",     MUDCOMM_NUZZLE     },
    {"cry",     MUDCOMM_CRY        },
    {"shimmy",     MUDCOMM_SHIMMY     },
    {"swim",     MUDCOMM_SWIM       },
    {"forge",     MUDCOMM_FORGE      },
    {"smash",     MUDCOMM_SMASH      },
    {"drop",     MUDCOMM_DROP       },
    {"goto",     MUDCOMM_GOTO       },
    {"weather",     MUDCOMM_WEATHER    },
    {"read",     MUDCOMM_READ       },
    {"pour",     MUDCOMM_POUR       },
    {"grab",     MUDCOMM_GRAB       },
    {"remove",     MUDCOMM_REMOVE     },
    {"put",     MUDCOMM_PUT        },
    {"shutdow",     MUDCOMM_SHUTDOW    },
    {"save",     MUDCOMM_SAVE       },
    {"hit",     MUDCOMM_HIT        },
    {"string",     MUDCOMM_STRING     },
    {"give",     MUDCOMM_GIVE       },
    {"quit",     MUDCOMM_QUIT       },
    {"stat",     MUDCOMM_STAT       },
    {"setskill",     MUDCOMM_SETSKILL   },
    {"time",     MUDCOMM_TIME       },
    {"load",     MUDCOMM_LOAD       },
    {"purge",     MUDCOMM_PURGE      },
    {"shutdown",     MUDCOMM_SHUTDOWN   },
    {"idea",     MUDCOMM_IDEA       },
    {"typo",     MUDCOMM_TYPO       },
    {"bug",     MUDCOMM_BUG        },
    {"whisper",     MUDCOMM_WHISPER    },
    {"cast",     MUDCOMM_CAST       },
    {"at",     MUDCOMM_AT         },
    {"ask",     MUDCOMM_ASK        },
    {"order",     MUDCOMM_ORDER      },
    {"sip",     MUDCOMM_SIP        },
    {"taste",     MUDCOMM_TASTE      },
    {"snoop",     MUDCOMM_SNOOP      },
    {"follow",     MUDCOMM_FOLLOW     },
    {"rent",     MUDCOMM_RENT       },
    {"offer",     MUDCOMM_OFFER      },
    {"poke",     MUDCOMM_POKE       },
    {"advance",     MUDCOMM_ADVANCE    },
    {"accuse",     MUDCOMM_ACCUSE     },
    {"grin",     MUDCOMM_GRIN       },
    {"bow",     MUDCOMM_BOW        },
    {"open",     MUDCOMM_OPEN       },
    {"close",     MUDCOMM_CLOSE      },
    {"lock",     MUDCOMM_LOCK       },
    {"unlock",     MUDCOMM_UNLOCK     },
    {"leave",     MUDCOMM_LEAVE      },
    {"applaud",     MUDCOMM_APPLAUD    },
    {"blush",     MUDCOMM_BLUSH      },
    {"burp",     MUDCOMM_BURP       },
    {"chuckle",     MUDCOMM_CHUCKLE    },
    {"clap",     MUDCOMM_CLAP       },
    {"cough",     MUDCOMM_COUGH      },
    {"curtsey",     MUDCOMM_CURTSEY    },
    {"fart",     MUDCOMM_FART       },
    {"flip",     MUDCOMM_FLIP       },
    {"fondle",     MUDCOMM_FONDLE     },
    {"frown",     MUDCOMM_FROWN      },
    {"gasp",     MUDCOMM_GASP       },
    {"glare",     MUDCOMM_GLARE      },
    {"groan",     MUDCOMM_GROAN      },
    {"grope",     MUDCOMM_GROPE      },
    {"hiccup",     MUDCOMM_HICCUP     },
    {"lick",     MUDCOMM_LICK       },
    {"love",     MUDCOMM_LOVE       },
    {"moan",     MUDCOMM_MOAN       },
    {"nibble",     MUDCOMM_NIBBLE     },
    {"pout",     MUDCOMM_POUT       },
    {"purr",     MUDCOMM_PURR       },
    {"ruffle",     MUDCOMM_RUFFLE     },
    {"shiver",     MUDCOMM_SHIVER     },
    {"shrug",     MUDCOMM_SHRUG      },
    {"sing",     MUDCOMM_SING       },
    {"slap",     MUDCOMM_SLAP       },
    {"smirk",     MUDCOMM_SMIRK      },
    {"snap",     MUDCOMM_SNAP       },
    {"sneeze",     MUDCOMM_SNEEZE     },
    {"snicker",     MUDCOMM_SNICKER    },
    {"sniff",     MUDCOMM_SNIFF      },
    {"snore",     MUDCOMM_SNORE      },
    {"spit",     MUDCOMM_SPIT       },
    {"squeeze",     MUDCOMM_SQUEEZE    },
    {"stare",     MUDCOMM_STARE      },
    {"strut",     MUDCOMM_STRUT      },
    {"thank",     MUDCOMM_THANK      },
    {"twiddle",     MUDCOMM_TWIDDLE    },
    {"wave",     MUDCOMM_WAVE       },
    {"whistle",     MUDCOMM_WHISTLE    },
    {"wiggle",     MUDCOMM_WIGGLE     },
    {"wink",     MUDCOMM_WINK       },
    {"yawn",     MUDCOMM_YAWN       },
    {"snowball",     MUDCOMM_SNOWBALL   },
    {"write",     MUDCOMM_WRITE      },
    {"hold",     MUDCOMM_HOLD       },
    {"flee",     MUDCOMM_FLEE       },
    {"sneak",     MUDCOMM_SNEAK      },
    {"hide",     MUDCOMM_HIDE       },
    {"backstab",     MUDCOMM_BACKSTAB   },
    {"pick",     MUDCOMM_PICK       },
    {"steal",     MUDCOMM_STEAL      },
    {"bash",     MUDCOMM_BASH       },
    {"rescue",     MUDCOMM_RESCUE     },
    {"kick",     MUDCOMM_KICK       },
    {"french",     MUDCOMM_FRENCH     },
    {"comb",     MUDCOMM_COMB       },
    {"massage",     MUDCOMM_MASSAGE    },
    {"tickle",     MUDCOMM_TICKLE     },
    {"practice",     MUDCOMM_PRACTICE   },
    {"pat",     MUDCOMM_PAT        },
    {"examine",     MUDCOMM_EXAMINE    },
    {"take",     MUDCOMM_TAKE       },
    {"info",     MUDCOMM_INFO       },
    {"spells",     MUDCOMM_SPELLS     },
    {"practice",     MUDCOMM_PRACTISE   },
    {"curse",     MUDCOMM_CURSE      },
    {"use",     MUDCOMM_USE        },
    {"where",     MUDCOMM_WHERE      },
    {"levels",     MUDCOMM_LEVELS     },
    {"reroll",     MUDCOMM_REROLL     },
    {"pray",     MUDCOMM_PRAY       },
    {"colon",     MUDCOMM_COLON      },
    {"beg",     MUDCOMM_BEG        },
    {"bleed",     MUDCOMM_BLEED      },
    {"cringe",     MUDCOMM_CRINGE     },
    {"dream",     MUDCOMM_DREAM      },
    {"fume",     MUDCOMM_FUME       },
    {"grovel",     MUDCOMM_GROVEL     },
    {"hop",     MUDCOMM_HOP        },
    {"nudge",     MUDCOMM_NUDGE      },
    {"peer",     MUDCOMM_PEER       },
    {"point",     MUDCOMM_POINT      },
    {"ponder",     MUDCOMM_PONDER     },
    {"punch",     MUDCOMM_PUNCH      },
    {"snarl",     MUDCOMM_SNARL      },
    {"spank",     MUDCOMM_SPANK      },
    {"steam",     MUDCOMM_STEAM      },
    {"tackle",     MUDCOMM_TACKLE     },
    {"taunt",     MUDCOMM_TAUNT      },
    {"think",     MUDCOMM_THINK      },
    {"whine",     MUDCOMM_WHINE      },
    {"worship",     MUDCOMM_WORSHIP    },
    {"yodel",     MUDCOMM_YODEL      },
    {"toggle",     MUDCOMM_TOGGLE     },
    {"wizlist",     MUDCOMM_WIZLIST    },
    {"consider",     MUDCOMM_CONSIDER   },
    {"group",     MUDCOMM_GROUP      },
    {"restore",     MUDCOMM_RESTORE    },
    {"return",     MUDCOMM_RETURN     },
    {"switch",     MUDCOMM_SWITCH     },
    {"quaff",     MUDCOMM_QUAFF      },
    {"recite",     MUDCOMM_RECITE     },
    {"users",     MUDCOMM_USERS      },
    {"pose",     MUDCOMM_POSE       },
    {"silence",     MUDCOMM_SILENCE    },
    {"wizhelp",     MUDCOMM_WIZHELP    },
    {"credits",     MUDCOMM_CREDITS    },
    {"disband",     MUDCOMM_DISBAND    },
    {"vis",     MUDCOMM_VIS        },
    {"pflags",     MUDCOMM_PFLAGS     },
    {"poofin",     MUDCOMM_POOFIN     },
    {"wizmsg",     MUDCOMM_WIZMSG     },
    {"display",     MUDCOMM_DISPLAY    },
    {"echoa",     MUDCOMM_ECHOA      },
    {"demote",     MUDCOMM_DEMOTE     },
    {"poofout",     MUDCOMM_POOFOUT    },
    {"wimpy",     MUDCOMM_WIMPY      },
    {"balance",     MUDCOMM_BALANCE    },
    {"wizlock",     MUDCOMM_WIZLOCK    },
    {"deposit",     MUDCOMM_DEPOSIT    },
    {"withdraw",     MUDCOMM_WITHDRAW   },
    {"ignore",     MUDCOMM_IGNORE     },
    {"setattr",     MUDCOMM_SETATTR    },
    {"tittle",     MUDCOMM_TITLE      },
    {"aggr",     MUDCOMM_AGGR       },
    {"gsay",     MUDCOMM_GSAY       },
    {"consent",     MUDCOMM_CONSENT    },
    {"setbit",     MUDCOMM_SETBIT     },
    {"hitall",     MUDCOMM_HITALL     },
    {"trap",     MUDCOMM_TRAP       },
    {"murder",     MUDCOMM_MURDER     },
    {"auction",     MUDCOMM_AUCTION    },
    {"channel",     MUDCOMM_CHANNEL    },
    {"fill",     MUDCOMM_FILL       },
    {"gossip",     MUDCOMM_GOSSIP     },
    {"nokill",     MUDCOMM_NOKILL     },
    {"page",     MUDCOMM_PAGE       },
    {"mudcomms",     MUDCOMM_MUDCOMMS   },
    {"attributes",     MUDCOMM_ATTRIBUTES },
    {"rules",     MUDCOMM_RULES      },
    {"track",     MUDCOMM_TRACK      },
    {"listen",     MUDCOMM_LISTEN     },
    {"disarm",     MUDCOMM_DISARM     },
    {"parry",     MUDCOMM_PARRY      },
    {"delete",     MUDCOMM_DELETE     },
    {"ban",     MUDCOMM_BAN        },
    {"allow",     MUDCOMM_ALLOW      },
    {"password",     MUDCOMM_PASSWORD   },
    {"description",     MUDCOMM_DESCRIPTION },
    {"bribe",     MUDCOMM_BRIBE      },
    {"bonk",     MUDCOMM_BONK       },
    {"calm",     MUDCOMM_CALM       },
    {"rub",     MUDCOMM_RUB        },
    {"censor",     MUDCOMM_CENSOR     },
    {"choke",     MUDCOMM_CHOKE      },
    {"drool",     MUDCOMM_DROOL      },
    {"flex",     MUDCOMM_FLEX       },
    {"lean",     MUDCOMM_LEAN       },
    {"moon",     MUDCOMM_MOON       },
    {"ogle",     MUDCOMM_OGLE       },
    {"pant",     MUDCOMM_PANT       },
    {"pinch",     MUDCOMM_PINCH      },
    {"push",     MUDCOMM_PUSH       },
    {"scare",     MUDCOMM_SCARE      },
    {"scold",     MUDCOMM_SCOLD      },
    {"seduce",     MUDCOMM_SEDUCE     },
    {"shove",     MUDCOMM_SHOVE      },
    {"shudder",     MUDCOMM_SHUDDER    },
    {"shush",     MUDCOMM_SHUSH      },
    {"slobber",     MUDCOMM_SLOBBER    },
    {"smell",     MUDCOMM_SMELL      },
    {"sneer",     MUDCOMM_SNEER      },
    {"spin",     MUDCOMM_SPIN       },
    {"squirm",     MUDCOMM_SQUIRM     },
    {"stomp",     MUDCOMM_STOMP      },
    {"strangle",     MUDCOMM_STRANGLE   },
    {"stretch",     MUDCOMM_STRETCH    },
    {"tap",     MUDCOMM_TAP        },
    {"tease",     MUDCOMM_TEASE      },
    {"tiptoe",     MUDCOMM_TIPTOE     },
    {"tweak",     MUDCOMM_TWEAK      },
    {"twirl",     MUDCOMM_TWIRL      },
    {"undress",     MUDCOMM_UNDRESS    },
    {"whimper",     MUDCOMM_WHIMPER    },
    {"exchange",     MUDCOMM_EXCHANGE   },
    {"release",     MUDCOMM_RELEASE    },
    {"search",     MUDCOMM_SEARCH     },
    {"fly",     MUDCOMM_FLY        },
    {"levitate",     MUDCOMM_LEVITATE   },
    {"secret",     MUDCOMM_SECRET     },
    {"lookup",     MUDCOMM_LOOKUP     },
    {"report",     MUDCOMM_REPORT     },
    {"split",     MUDCOMM_SPLIT      },
    {"world",     MUDCOMM_WORLD      },
    {"junk",     MUDCOMM_JUNK       },
    {"petition",     MUDCOMM_PETITION   },
    {"do",     MUDCOMM_DO         },
    {"apostrophe",     MUDCOMM_APOSTROPHE },
    {"caress",     MUDCOMM_CARESS     },
    {"bury",     MUDCOMM_BURY       },
    {"donate",     MUDCOMM_DONATE     },
    {"dig",     MUDCOMM_DIG        },
    {"scale",     MUDCOMM_SCALE      },
    {"cut",     MUDCOMM_CUT        },
    {"slack",     MUDCOMM_SLASH      },
    {"hack",     MUDCOMM_HACK       },
    {"yell",     MUDCOMM_YELL       },
    {"ring",     MUDCOMM_RING       },
    {"jump",     MUDCOMM_JUMP       },
    {"trace",     MUDCOMM_TRACE      },
    {"water",     MUDCOMM_WATER      },
    {"touch",     MUDCOMM_TOUCH      },
    {"scratch",     MUDCOMM_SCRATCH    },
    {"wince",     MUDCOMM_WINCE      },
    {"toss",     MUDCOMM_TOSS       },
    {"flame",     MUDCOMM_FLAME      },
    {"arch",     MUDCOMM_ARCH       },
    {"amaze",     MUDCOMM_AMAZE      },
    {"bathe",     MUDCOMM_BATHE      },
    {"embrace",     MUDCOMM_EMBRACE    },
    {"brb",     MUDCOMM_BRB        },
    {"ack",     MUDCOMM_ACK        },
    {"cheer",     MUDCOMM_CHEER      },
    {"snort",     MUDCOMM_SNORT      },
    {"eyebrow",     MUDCOMM_EYEBROW    },
    {"bang",     MUDCOMM_BANG       },
    {"pillow",     MUDCOMM_PILLOW     },
    {"nap",     MUDCOMM_NAP        },
    {"nose",     MUDCOMM_NOSE       },
    {"raise",     MUDCOMM_RAISE      },
    {"hand",     MUDCOMM_HAND       },
    {"pull",     MUDCOMM_PULL       },
    {"tug",     MUDCOMM_TUG        },
    {"wet",     MUDCOMM_WET        },
    {"mosh",     MUDCOMM_MOSH       },
    {"wait",     MUDCOMM_WAIT       },
    {"hi5",     MUDCOMM_HI5        },
    {"envy",     MUDCOMM_ENVY       },
    {"flirt",     MUDCOMM_FLIRT      },
    {"bark",     MUDCOMM_BARK       },
    {"whap",     MUDCOMM_WHAP       },
    {"roll",     MUDCOMM_ROLL       },
    {"blink",     MUDCOMM_BLINK      },
    {"duh",     MUDCOMM_DUH        },
    {"gag",     MUDCOMM_GAG        },
    {"grumble",     MUDCOMM_GRUMBLE    },
    {"dropkick",     MUDCOMM_DROPKICK   },
    {"whatever",     MUDCOMM_WHATEVER   },
    {"fool",     MUDCOMM_FOOL       },
    {"noogie",     MUDCOMM_NOOGIE     },
    {"melt",     MUDCOMM_MELT       },
    {"smoke",     MUDCOMM_SMOKE      },
    {"wheeze",     MUDCOMM_WHEEZE     },
    {"bird",     MUDCOMM_BIRD       },
    {"boggle",     MUDCOMM_BOGGLE     },
	{"hiss",     MUDCOMM_HISS       },
	{"bite",     MUDCOMM_BITE       },
};

int CommandCount() {return sizeof(comm_types)/sizeof(flag_types);}

const CString shield_types[] =
{
	"None",
	"Strapped to arm",
	"Hand-held",
};

const CString shield_shape[] =
{
	"None",
	"Circular",
	"Square",
	"Vert Rectangle",
	"Horz Rectangle",
	"Vert Oval",
	"Horz Oval",
	"Triangle Down",
	"Triangle Up",
};

const CString shield_size[] =
{
	"None",
	"Tiny",
	"Small",
	"Medium",
	"Large",
	"Huge",
};

const flag_types cont_types[] =
{
	{"Closeable",	CONT_CLOSEABLE},
	{"Pickproof",	CONT_PICKPROOF},
	{"Closed",		CONT_CLOSED},
	{"Locked",		CONT_LOCKED},
};

int ContainerCount() {return sizeof(cont_types)/sizeof(flag_types);}

const flag_types totem_types[] =
{
	{"Lesser Animal",		TOTEM_L_ANIMAL},
	{"Greater Animal",		TOTEM_G_ANIMAL},
	{"Lesser Elemental",	TOTEM_L_ELEMENTAL},
	{"Greater Elemental",	TOTEM_G_ELEMENTAL},
	{"Lesser Spirit",		TOTEM_L_SPIRIT},
	{"Greater Spirit",		TOTEM_G_SPIRIT},
};

int TotemCount() {return sizeof(totem_types)/sizeof(flag_types);}

const CString dam_types[] =
{
	"None",
	"Bludgeon",
	"Pierce",
	"Slash",
};

const CString liquid_types[] =
{
    "water",
    "beer",
    "wine",
    "ale",
    "dark-ale",
    "whisky",
    "lemonade",
    "firebreather",
    "local-specialty",
    "slime-mold-juice",
    "milk",
    "tea",
    "coffee",
    "blood",
    "salt-water",
    "cola",
    "white wine",
    "root beer",
    "champagne",
    "vodka",
    "absinth",
    "brandy",
    "schnapps",
    "orange juice",
    "sherry",
    "rum",
    "port",
    "holy water",
    "unholy water",
};

const flag_types instrument_types[] = 
{
	{"Flute",		INSTRUMENT_FLUTE},
	{"Lyre",		INSTRUMENT_LYRE},
	{"Mandolin",	INSTRUMENT_MANDOLIN},
	{"Harp",		INSTRUMENT_HARP},
	{"Drums",		INSTRUMENT_DRUMS},
	{"Horn",		INSTRUMENT_HORN},
	{"Pipes",		INSTRUMENT_PIPES},
	{"Fiddle",		INSTRUMENT_FIDDLE},
	{"Dulcimer",	INSTRUMENT_DULCIMER},
};
int InstrumentCount() { return sizeof(instrument_types)/sizeof(flag_types); }
const flag_types weapon_types[] = {
	{"None",		WEAPON_NONE},
	{"Axe",			WEAPON_AXE},
	{"Dagger",		WEAPON_DAGGER},
	{"Flail",		WEAPON_FLAIL},
	{"Hammer",		WEAPON_HAMMER},
	{"Longsword",	WEAPON_LONGSWORD},
	{"Mace",		WEAPON_MACE},
	{"Spiked Mace",	WEAPON_SPIKED_MACE},
	{"Polearm",		WEAPON_POLEARM},
	{"Shortsword",	WEAPON_SHORTSWORD},
	{"Club",		WEAPON_CLUB},
	{"Spiked Club",	WEAPON_SPIKED_CLUB},
	{"Staff",		WEAPON_STAFF},
	{"Two-Handed Sword",WEAPON_2HANDSWORD},
	{"Whip",		WEAPON_WHIP},
	{"Pick",		WEAPON_PICK},
	{"Lance",		WEAPON_LANCE},
	{"Sickle",		WEAPON_SICKLE},
	{"Fork",		WEAPON_FORK},
	{"Horn",		WEAPON_HORN},
	{"Numchucks",	WEAPON_NUMCHUCKS},
	{"Spear",		WEAPON_SPEAR},
	{"Battle-axe",	WEAPON_BATTLEAXE},
	{"Katana",		WEAPON_KATANA},
	{"Bastard Sword",WEAPON_BASTARDSWORD},
	{"Morningstar",	WEAPON_MORNINGSTAR},
	{"Rapier",		WEAPON_RAPIER},
	{"Scimitar",	WEAPON_SCIMITAR},
	{"Sabre",		WEAPON_SABRE},
	{"Cutlass",		WEAPON_CUTLASS},
	{"Warhammer",	WEAPON_WARHAMMER},
	{"Claymore",	WEAPON_CLAYMORE},
	{"Khopesh",		WEAPON_KHOPESH},
	{"Flamberge",	WEAPON_FLAMBERGE},
	{"Great-axe",	WEAPON_GREATAXE},
	{"Halberd",		WEAPON_HALBERD},
	{"Glaive",		WEAPON_GLAIVE},
	{"Falchion",	WEAPON_FALCHION},
	{"Naginata",	WEAPON_NAGINATA},
	{"Pike",		WEAPON_PIKE},
	{"Wakizashi",	WEAPON_WAKIZASHI},
	{"Scythe",		WEAPON_SCYTHE},
	{"Sai",			WEAPON_PARRYINGDAGGER},
	{"Knife",		WEAPON_KNIFE},
	{"Dirk",		WEAPON_DIRK},
	{"Kris",		WEAPON_KRIS},
	{"Claw",		WEAPON_CLAW},
	{"Fang",		WEAPON_FANG},
	{"Gythka",		WEAPON_GYTHKA},
	{"Chatkcha",	WEAPON_CHATKCHA},
	{"Scepter",		WEAPON_SCEPTER},
	{"Quarter-staff",WEAPON_QUARTERSTAFF},
	{"Stiletto",	WEAPON_STILETTO},
	{"Trident",		WEAPON_TRIDENT},
};

int GetWeapCount() {return sizeof(weapon_types)/sizeof(flag_types);}

const CString missile_types[] = 
{
	"None",
	"Arrow",
	"Light Quarrel",
	"Heavy Quarrel",
	"Hand Quarrel",
	"Sling Bullet",
};

const CString apply_names[] = {
	"None",
	"Strength",
	"Dexterity",
	"Inteligence",
	"Wisdom",
	"Constitution",
	"Sex",
	"Class",
	"Level",
	"Age",
	"Height",
	"Weight",
	"Mana",
	"Hit",
	"Move",
	"Gold",
	"Experience",
	"Armor Class",
	"Hitroll",
	"Damroll",
	"Save Para",
	"Save Rod",
	"Save Petri",
	"Save Breath",
	"Save Spell",
	"Fire Protection",
	"Agility",
	"Power",
	"Charisma",
	"Luck",
	"Max Strength",
	"Max Dexterity",
	"Max Inteligence",
	"Max Wisdom",
	"Max Constitution",
	"Max Agility",
	"Max Power",
	"Max Charisma",
	"Max Luck",
	"Racial Strength",
	"Racial Dexterity",
	"Racial Inteligence",
	"Racial Wisdom",
	"Racial Constitution",
	"Racial Agility",
	"Racial Power",
	"Racial Charisma",
	"Racial Luck",
	"Curse",
	"Resistant",
	"Immune",
	"Susceptible",
	"Race",
	"Size",
	"Apparent Size",
	"Vulnerable",
	"Spell Resistance",
};

const ItemType item_types[MAX_ITEM_TYPE] = {
	{"None",			false,	true	},
	{"Light",			true,	true	},
	{"Scroll",			true,	true	},
    {"Wand",			true,	true	},
    {"Staff",			true,	true	},
    {"Weapon",			true,	true	},
    {"Ranged Weapon",	true,	true	},
    {"Missle",			true,	true	},
    {"Treasure",		true,	true	},
    {"Armor",			true,	true	},
    {"Potion",			true,	true	},
    {"Clothing",		true,	true	},
    {"Other",			true,	true	},
    {"Trash",			true,	true	},
    {"Trap",			true,	true	},
    {"Container",		true,	true	},
    {"Note",			true,	true	},
    {"Drink Container", true,	true	},
    {"Key",				true,	true	},
    {"Food",			true,	true	},
    {"Money",			true,	true	},
    {"Pen",				true,	true	},
    {"Boat",			true,	true	},
    {"Book",			false,	false	},
    {"Battery",			false,	false	},
    {"Teleport",		false,	true	},
    {"Timer",			false,	true	},
    {"Vehicle",			true,	true	},
    {"Ship",			true,	true    },
    {"Switch",			false,	true	},
    {"Quiver",			true,	true	},
    {"Lockpick",		true,	true	},
    {"Instrument",		true,	true	},
    {"Spellbook",		true,	true	},
    {"Totem",			true,	true	},
    {"Storage Chest",	false,	true	},
    {"Scabbard",		true,	true	},
    {"Shield",			true,	true	},
    {"NPC Corpse",		false,	false	},
    {"PC Corpse",		false,	false	},
    {"Portal",			false,	true	},
    {"Pill",			true,	true	},
    {"Herb",			true,	true	},
    {"Message Board",	false,	true	},
    {"Pipe",			true,	true	},
    {"Wanted List",		false,	true	},
    {"Wall",			false,	true	},
	{"UNUSED",			false,	false	},
    {"Ammo",			true,	true	},
    {"Tradition Icon",	true,	true	},
    {"Rope",			true,	true	},
    {"Disguise Kit",	true,	true	},
    {"Control Panel",	false,	true	},
    {"Vehicle Key",		false,	false	},
    {"Summon",			false,	true	},
	{"Glyph",           false,  true,	},
	{"Holy Symbol",     false,  false,  },
	{"Spell Scroll",    true,   true,   },
};

const wear_data wear_locs[NUM_ITEM_WEAR_VECTORS] = {
	{"Takeable",			ITEM_TAKE		 },
	{"Worn on Finger",		ITEM_WEAR_FINGER },
	{"Worn Around Neck",	ITEM_WEAR_NECK   },
	{"Worn on Body",		ITEM_WEAR_BODY   },
	{"Worn on Head",		ITEM_WEAR_HEAD   },
	{"Worn on Legs",		ITEM_WEAR_LEGS   },
	{"Worn on Feet",		ITEM_WEAR_FEET	 },
	{"Worn on Hands",		ITEM_WEAR_HANDS  },
	{"Worn on Arms",		ITEM_WEAR_ARMS   },
	{"Worn as Shield",		ITEM_WEAR_SHIELD },
	{"Worn About Body",		ITEM_WEAR_ABOUT	 },
	{"Worn on Waist",		ITEM_WEAR_WAIST  },
	{"Worn Around Wrist",	ITEM_WEAR_WRIST  },
	{"Wieldable",			ITEM_WIELD		 },
	{"Held",				ITEM_HOLD		 },
	{"Worn on Eyes",		ITEM_WEAR_EYES	 },
	{"Worn on Face",		ITEM_WEAR_FACE   },
	{"Worn as Earring",		ITEM_WEAR_EAR    },
	{"Worn as Quiver",		ITEM_QUIVER		 },
	{"Worn as Badge",		ITEM_BADGE		 },
	{"Worn on Back",		ITEM_WEAR_ONBACK },
	{"Attached to Belt",	ITEM_ATTACH_BELT },
	{"Worn on Horse Body",  ITEM_HORSE_BODY  },
	{"Worn on Tail",		ITEM_TAIL		 },
	{"Worn in Nose",		ITEM_NOSE		 },
	{"Worn on Horns",		ITEM_HORNS		 },
};

const BITVECT_DATA 	USE_ANYONE				=	{0, BV00};
const BITVECT_DATA 	USE_WARRIOR             =	{0, BV01};
const BITVECT_DATA 	USE_RANGER              =	{0, BV02};
const BITVECT_DATA 	USE_PALADIN             =	{0, BV03};
const BITVECT_DATA 	USE_ANTI                =	{0, BV04};
const BITVECT_DATA 	USE_CLERIC              =	{0, BV05};
const BITVECT_DATA 	USE_MONK                =	{0, BV06};// For later use
const BITVECT_DATA 	USE_DRUID               =	{0, BV07};
const BITVECT_DATA 	USE_SHAMAN              =	{0, BV08};
const BITVECT_DATA 	USE_SORCERER            =	{0, BV09};
const BITVECT_DATA 	USE_NECROMANCER         =	{0, BV10};
const BITVECT_DATA 	USE_ELEMENTAL           =	{0, BV11};
const BITVECT_DATA 	USE_PSI                 =	{0, BV12};
const BITVECT_DATA 	USE_THIEF               =	{0, BV13};
const BITVECT_DATA 	USE_ASSASSIN            =	{0, BV14};
const BITVECT_DATA 	USE_MERCENARY           =	{0, BV15};
const BITVECT_DATA 	USE_BARD                =	{0, BV16};
const BITVECT_DATA 	USE_NOHUMAN             =	{0, BV17};
const BITVECT_DATA 	USE_NOGREYELF           =	{0, BV18};
const BITVECT_DATA 	USE_NOHALFELF           =	{0, BV19};
const BITVECT_DATA 	USE_NODWARF             =	{0, BV20};
const BITVECT_DATA 	USE_NOHALFLING          =	{0, BV21};
const BITVECT_DATA 	USE_NOGNOME             =	{0, BV22};
const BITVECT_DATA 	USE_NOBARBARIAN         =	{0, BV23};
const BITVECT_DATA 	USE_NODUERGAR           =	{0, BV24};
const BITVECT_DATA 	USE_NODROW              =	{0, BV25};
const BITVECT_DATA 	USE_NOTROLL             =	{0, BV26};
const BITVECT_DATA 	USE_NOOGRE              =	{0, BV27};
const BITVECT_DATA 	USE_ANTIGOODRACE        =	{0, BV28};
const BITVECT_DATA 	USE_NOORC               =	{0, BV29};
const BITVECT_DATA 	USE_ANTIEVILRACE        =	{0, BV30};
const BITVECT_DATA 	USE_NOTHRIKREEN		=	{1, BV00}; // For later use
const BITVECT_DATA 	USE_NOCENTAUR		=	{1, BV01};
const BITVECT_DATA 	USE_NOGITHYANKI     =	{1, BV02};
const BITVECT_DATA 	USE_NOMINOTAUR      =	{1, BV03};
const BITVECT_DATA 	USE_ANTIMALE        =	{1, BV04};
const BITVECT_DATA 	USE_ANTIFEMALE      =	{1, BV05};
const BITVECT_DATA 	USE_ANTINEUTER      =	{1, BV06};
const BITVECT_DATA 	USE_NOHALFORC       =	{1, BV07}; // For later use
const BITVECT_DATA 	USE_NOSAHAUGIN      =	{1, BV08};// For later use
const BITVECT_DATA 	USE_NOGOBLIN        =	{1, BV09};
const BITVECT_DATA 	USE_NORAKSHASA      =	{1, BV10};
const BITVECT_DATA 	USE_NOFLIND         =	{1, BV11};
const BITVECT_DATA 	USE_NOGITHZERAI     =	{1, BV12};
const BITVECT_DATA 	USE_NODUAL          =	{1, BV13};

const AntiFlags anti_flags[] = {
	{"Anyone Can Use",			&USE_ANYONE},
	{"Warriors Can Use",		&USE_WARRIOR}, 
	{"Ranges Can Use",			&USE_RANGER},
	{"Paladins Can Use",		&USE_PALADIN},
	{"Anti-Paladins Can Use",	&USE_ANTI},
	{"Clerics Can Use",			&USE_CLERIC},
	{"Monks Can Use",			&USE_MONK},
	{"Druids Can Use",			&USE_DRUID},
	{"Shaman Can Use",			&USE_SHAMAN},
	{"Sorcerers Can Use",		&USE_SORCERER},
	{"Necromancers Can Use",	&USE_NECROMANCER},
	{"Elementalists Can Use",	&USE_ELEMENTAL},
	{"Psionicists Can Use",		&USE_PSI},
	{"Thieves Can Use",			&USE_THIEF},
	{"Assassins Can Use",		&USE_ASSASSIN},
	{"Mercenaries Can Use",		&USE_MERCENARY},
	{"Bards Can Use",			&USE_BARD},
	{"Human Can't Use",			&USE_NOHUMAN}, 
	{"Grey Elf Can't Use",		&USE_NOGREYELF},
	{"Half-Elf Can't Use",		&USE_NOHALFELF},
	{"Dwarf Can't Use",			&USE_NODWARF},
	{"Halfling Can't Use",		&USE_NOHALFLING},
	{"Gnome Can't Use",			&USE_NOGNOME},
	{"Barbarian Can't Use",		&USE_NOBARBARIAN},
	{"Duergar Can't Use",		&USE_NODUERGAR},
	{"Drow Elf Can't Use",		&USE_NODROW},
	{"Troll Can't Use",			&USE_NOTROLL},
	{"Ogre Can't Use",			&USE_NOOGRE}, 
	{"Anti Good Race",			&USE_ANTIGOODRACE},
	{"Orc Can't Use",			&USE_NOORC},
	{"Anti Evil Race",			&USE_ANTIEVILRACE},
	{"Thri-Kreen Can't Use",	&USE_NOTHRIKREEN},
	{"Centaur Can't Use",		&USE_NOCENTAUR},		
	{"Githyanki Can't Use",		&USE_NOGITHYANKI},   
	{"Minotaur Can't Use",		&USE_NOMINOTAUR},
	{"Anti Male",				&USE_ANTIMALE},
	{"Anti Female",				&USE_ANTIFEMALE},
	{"Anti Neuter",				&USE_ANTINEUTER},
	{"Half-Orc Can't Use",		&USE_NOHALFORC}, 
	{"Sahaugin Cant't Use",		&USE_NOSAHAUGIN},
	{"Goblin Can't Use",		&USE_NOGOBLIN}, 
	{"Rakshasa Can't Use",		&USE_NORAKSHASA}, 
	{"Flind Can't Use",			&USE_NOFLIND}, 
	{"Githzerai Can't Use",		&USE_NOGITHZERAI},
	{"No Dual",					&USE_NODUAL},
};
int AntiFlagsCount() { return sizeof(anti_flags) / sizeof(AntiFlags); }

const CString materials[MAX_MATERIAL] = {
	"Undefined",
	"Non-Substantial",
	"Flesh",
	"Cloth",
	"Bark",
	"Softwood",
	"Hardwood",
	"Glass",
	"Crystal",
	"Ceramic",
	"Bone",
	"Stone",
	"Hide",
	"Leather",
	"Cured Leather",
	"Iron",
	"Steel",
	"Brass",
	"Mithril",
	"Adamantium",
	"Bronze",
	"Copper",
	"Silver",
	"Electrum",
	"Gold",
	"Platinum",
	"Gem",
	"Diamond",
	"Paper",
	"Parchment",
	"Leaves",
	"Ruby",
	"Emerald",
	"Sapphire",
	"Ivory",
	"Dragonscale",
	"Obsidian",
	"Granite",
	"Marble",
	"Limestone",
	"Liquid",
	"Bamboo",
	"Reeds",
	"Hemp",
	"Glassteel",
	"Egg Shell",
	"Chitanous",
	"Reptile Scale",
	"Generic Food",
	"Rubber",
	"Feather",
	"Wax",
	"Pearl",
	"Silk",
	"Spider Silk",
	"Jade",
	"Lead",
};

const CString craftsmanship[16] = {
	"Terrible",
	"Extremly Poor",
	"Very Poor",
	"Fairly Poor",
	"Well Below Average",
	"Below Average",
	"Slightly Below Average",
	"Average",
	"Slightly Above Average",
	"Above Average",
	"Well Above Average",
	"Excellent",
	"Crafted by a Skilled Artisan",
	"Crafted by a Gifted Artisan",
	"Crafted by a Master Artisan",
	"One-of-a-Kind",
};

const BITVECT_DATA ITEM_NONE 					= {0,    0};
const BITVECT_DATA ITEM_GLOW                  	= {0, BV00};
const BITVECT_DATA ITEM_NOSHOW                	= {0, BV01}; // new, was ITEM_HUM = 1, 25
const BITVECT_DATA ITEM_BURIED                	= {0, BV02}; // new, was ITEM_DARK (gone)
const BITVECT_DATA ITEM_NOSELL                	= {0, BV03}; // new, was ITEM_LOCK (gone)
const BITVECT_DATA ITEM_EVIL                  	= {0, BV04};
const BITVECT_DATA ITEM_INVIS                 	= {0, BV05};
const BITVECT_DATA ITEM_MAGIC                 	= {0, BV06};
const BITVECT_DATA ITEM_NODROP                	= {0, BV07};
const BITVECT_DATA ITEM_BLESS                 	= {0, BV08};
const BITVECT_DATA ITEM_ANTI_GOOD             	= {0, BV09};
const BITVECT_DATA ITEM_ANTI_EVIL             	= {0, BV10};
const BITVECT_DATA ITEM_ANTI_NEUTRAL          	= {0, BV11};
const BITVECT_DATA ITEM_SECRET                	= {0, BV12}; // was ITEM_NOREMOVE = 2, 18
const BITVECT_DATA ITEM_FLOAT                 	= {0, BV13}; // was ITEM_INVENTORY = 1, 27
const BITVECT_DATA ITEM_NOBURN                	= {0, BV14}; // was ITEM_POISONED = 2, 17
const BITVECT_DATA ITEM_NOLOCATE              	= {0, BV15}; // was ITEM_VAMPIRE_BANE (gone)
const BITVECT_DATA ITEM_NOID                  	= {0, BV16}; // was ITEM_HOLY = 2, 19
const BITVECT_DATA ITEM_NOSUMMON              	= {0, BV17}; // was ITEM_VIS_DEATH (gone)
const BITVECT_DATA ITEM_LIT						= {0, BV18}; 
const BITVECT_DATA ITEM_TRANSIENT             	= {0, BV19};
const BITVECT_DATA ITEM_NOSLEEP               	= {0, BV20}; 
const BITVECT_DATA ITEM_NOCHARM               	= {0, BV21};
const BITVECT_DATA ITEM_TWOHANDED            	= {0, BV22};
const BITVECT_DATA ITEM_NORENT                	= {0, BV23};
const BITVECT_DATA ITEM_GOODONLY              	= {0, BV24};
const BITVECT_DATA ITEM_HUM                   	= {0, BV25};
const BITVECT_DATA ITEM_LEVITATES             	= {0, BV26};
const BITVECT_DATA ITEM_INVENTORY             	= {0, BV27};
const BITVECT_DATA ITEM_WAS_DISARMED          	= {0, BV28};
const BITVECT_DATA ITEM_WHOLEBODY             	= {0, BV29};
const BITVECT_DATA ITEM_WHOLEHEAD             	= {0, BV30};

const BITVECT_DATA ITEM_SILVER                  = {1, BV00};
const BITVECT_DATA ITEM_THROW_RETURN            = {1, BV06};
const BITVECT_DATA ITEM_THROW_ONEROOM           = {1, BV07};
const BITVECT_DATA ITEM_THROW_TWOROOMS          = {1, BV08};
const BITVECT_DATA ITEM_ENLARGED                = {1, BV16};
const BITVECT_DATA ITEM_REDUCED                 = {1, BV17};
const BITVECT_DATA ITEM_POISONED                = {1, BV18};
const BITVECT_DATA ITEM_FLY             		= {1, BV19}; 
const BITVECT_DATA ITEM_SAVE             		= {1, BV20}; 
const BITVECT_DATA ITEM_ALTERED            		= {1, BV21}; 
const BITVECT_DATA ITEM_NO_FLEE					= {1, BV22};
const BITVECT_DATA ITEM_NO_REPAIR				= {1, BV23};
const BITVECT_DATA ITEM_FLAG                    = {1, BV24};
const BITVECT_DATA ITEM_VARIABLE                = {1, BV25}; //  for OLC, Items that are newly created
const BITVECT_DATA ITEM_DELETE	                = {1, BV26}; //  for OLC, Item is to be deleted next boot
const BITVECT_DATA ITEM_REMOVEPL                = {1, BV27}; // item is to be removed from players next boot 
const BITVECT_DATA ITEM_RELOAD	                = {1, BV28}; // item is to be reloaded from prototype each load
const BITVECT_DATA ITEM_ARTIFACT                = {1, BV29}; // item is an artifact, and will be added to the list 
const BITVECT_DATA ITEM_MINORARTI               = {1, BV30}; // item is a minor atrifact as above
const BITVECT_DATA ITEM_UNDEAD					= {2, BV00}; // Is !drop until someone casts resurrect on wearer
const BITVECT_DATA ITEM_UNIQUE                  = {2, BV20}; // Hard time finding a free spot

const extra_flags obj_flags[] = {
	{"None",			&ITEM_NONE,				false	},
	{"Glow",			&ITEM_GLOW,				true	},
	{"No Show",			&ITEM_NOSHOW,			true	},
	{"Buried",			&ITEM_BURIED,			false	},
	{"No Sell",			&ITEM_NOSELL,			true	},
	{"Evil",			&ITEM_EVIL,				true	},
	{"Invisible",		&ITEM_INVIS,			true	},
	{"Magic",			&ITEM_MAGIC,			true	},
	{"No Drop",			&ITEM_NODROP,			true	},
	{"Bless",			&ITEM_BLESS,			true	},
	{"Anti Good",		&ITEM_ANTI_GOOD,		true	},
	{"Anti Evil",		&ITEM_ANTI_EVIL,		true	},
	{"Anti Neutral",	&ITEM_ANTI_NEUTRAL,		true	},
	{"Secret",			&ITEM_SECRET,			true	},
	{"Float",			&ITEM_FLOAT,			true	},
	{"No Burn",			&ITEM_NOBURN,			true	},
	{"No Locate",		&ITEM_NOLOCATE,			true	},
	{"No Identify",		&ITEM_NOID,				true	},
	{"No Summon",		&ITEM_NOSUMMON,			false	},
	{"Lit",				&ITEM_LIT,				true	},
	{"Fly",				&ITEM_FLY,				true	},
	{"Transient",		&ITEM_TRANSIENT,		false	},
	{"No Sleep",		&ITEM_NOSLEEP,			false	},
	{"No Charm",		&ITEM_NOCHARM,			false	},
	{"Two Handed",		&ITEM_TWOHANDED,		true	},
	{"No Rent",			&ITEM_NORENT,			true	},
	{"Good Only",		&ITEM_GOODONLY,			false	},
	{"Hum",				&ITEM_HUM,				true	},
	{"Levitates",		&ITEM_LEVITATES,		true	},
	{"Inventory",		&ITEM_INVENTORY,		false	},
	{"Was Disarmed",	&ITEM_WAS_DISARMED,		false	},
	{"Whole Body",		&ITEM_WHOLEBODY,		true	},
	{"Whole Head",		&ITEM_WHOLEHEAD,		true	},
	{"Silver",			&ITEM_SILVER,			true	},
	{"Throw Return",	&ITEM_THROW_RETURN,		false	},
	{"Throw One Room",	&ITEM_THROW_ONEROOM,	false	},
	{"Throw Two Rooms", &ITEM_THROW_TWOROOMS,	false	},
	{"Enlarged",		&ITEM_ENLARGED,			false	},
	{"Reduced",			&ITEM_REDUCED,			false	},
	{"Poisoned",		&ITEM_POISONED,			true	},
	{"Save",			&ITEM_SAVE,				false	},
	{"Altered",			&ITEM_ALTERED,			false   },
	{"No Flee",			&ITEM_NO_FLEE,			true	},
	{"No Repair",		&ITEM_NO_REPAIR,		true	},
	{"Variable",		&ITEM_VARIABLE,			false	},
	{"Delete",			&ITEM_DELETE,			false	}, 
	{"REMOVEPL",		&ITEM_REMOVEPL,			false	},
	{"Reload",			&ITEM_RELOAD,			true	},
	{"Artifact",		&ITEM_ARTIFACT,			true	},
	{"Minor Artifact",	&ITEM_MINORARTI,		true	},
	{"Unique",			&ITEM_UNIQUE,			true	},
	{"Undead",			&ITEM_UNDEAD,			false	},
	{"Flag",			&ITEM_FLAG,				false	},
};

int ExtraFlagCount() { return sizeof(obj_flags) / sizeof(extra_flags); }

object_data *GetObjByVnum(int vnum)
{
	object_data *tmp;

	if(vnum == 0)
		return NULL;

	for(tmp = object_data::obj_head; tmp; tmp = tmp->next)
		if(tmp->vnum == vnum)
			return tmp;

	return NULL;
}

object_data::object_data() 
{
	int i;
	
	this->vnum = 0;
	this->contains = NULL;
	this->first_extra_descr = NULL;
	this->last_extra_desc = NULL;
	this->next = NULL;
	
	if(!def_obj)
	{
		this->anti_flags[0] = 0;
		this->anti_flags[1] = 0;
		this->condition = 0;
	
		this->craftsmanship = 0;
		this->description = "An unnamed object is lying here.";

		this->extra_flags[0] = 0;
		this->extra_flags[1] = 0;
		this->extra_flags[2] = 0;
		this->item_type = TYPE_NONE;
		this->level = 0;
		this->material = MAT_UNDEFINED;
		this->name = "unnamed object";
	
		this->short_descr = "an unnamed object";
		this->size = 0;
	
		for(i = 0; i < MAX_ITEM_VALUE; i++)
			this->value[i] = 0;
	
		this->volume = 0;
		this->wear_flags = 0;
		this->weight = 0;
	
		for(i = 0; i < NUM_AFFECT_VECTORS;i++)
			this->affected_by[i] = 0;

		this->applies[0].loc = 0;
		this->applies[0].value = 0;
		this->applies[1].loc = 0;
		this->applies[1].value = 0;
	}
	else
	{
		this->anti_flags[0] = def_obj->anti_flags[0];
		this->anti_flags[1] = def_obj->anti_flags[1];
		this->condition = def_obj->condition;
	
		this->craftsmanship = def_obj->craftsmanship;
		this->description = def_obj->description;

		this->extra_flags[0] = def_obj->extra_flags[0];
		this->extra_flags[1] = def_obj->extra_flags[1];
		this->extra_flags[2] = def_obj->extra_flags[2];
		this->item_type = def_obj->item_type;
		this->level = def_obj->level;
		this->material = def_obj->material;
		this->name = def_obj->name;
	
		this->short_descr = def_obj->short_descr;
		this->size = def_obj->size;
	
		for(i = 0; i < MAX_ITEM_VALUE; i++)
			this->value[i] = def_obj->value[i];
	
		this->volume = def_obj->volume;
		this->wear_flags = def_obj->wear_flags;
		this->weight = def_obj->weight;
	
		for(i = 0; i < NUM_AFFECT_VECTORS;i++)
			this->affected_by[i] = def_obj->affected_by[i];

		this->applies[0].loc = def_obj->applies[0].loc;
		this->applies[0].value = def_obj->applies[0].value;
		this->applies[1].loc = def_obj->applies[1].loc;
		this->applies[1].value = def_obj->applies[1].value;
	}
}

void object_data::AddToList()
{
	object_data *tmp = NULL;

	if(obj_head == NULL) 
	{
		obj_head = this;
		this->next = NULL;
	} 
	else 
	{
		for(tmp = obj_head; tmp; tmp = tmp->next) 
		{
			if(tmp->next == NULL) 
			{
				tmp->next = this;
				this->next = NULL;
				
				break;
			}
		}
	}
}

void object_data::RemoveFromList()
{
	object_data *tmp = NULL;
	obj_index *index = NULL;//, *next = NULL;

	if(obj_head == NULL)
		return;

	if(this == obj_head) {
		obj_head = this->next;
		this->next = NULL;
	} else {
		for(tmp = obj_head; tmp; tmp = tmp->next) {
			if(tmp->next == this) {
				if(tmp->next)
					tmp->next = tmp->next->next;
				else
					tmp->next = NULL;

				break;
			}
		}
	}
	
	this->RemoveContents();

	//make sure all the indexs know that the object is gone
	for(index = obj_index::o_ind_head; index; index = index->n_list)
		if(index->vnum == vnum)
			index->obj = NULL;

	delete this;
}

bool object_data::AffIsSet(const BITVECT_DATA& bv) 
{
	return IS_SET(affected_by[bv.group], bv.vector) ? true : false;
}

void object_data::SetAffBit(const BITVECT_DATA& bv) 
{
	if(!IS_SET(affected_by[bv.group], bv.vector))
		SET_BIT(affected_by[bv.group], bv.vector);
}

void object_data::RemoveAffBit(const BITVECT_DATA& bv) 
{
	if(IS_SET(affected_by[bv.group], bv.vector))
		REMOVE_BIT(affected_by[bv.group], bv.vector);
}

bool object_data::ExtraIsSet(const BITVECT_DATA& bv) 
{
	return IS_SET(extra_flags[bv.group], bv.vector) ? true : false;
}

void object_data::SetExtraBit(const BITVECT_DATA& bv) 
{
	if(!IS_SET(extra_flags[bv.group], bv.vector))
		SET_BIT(extra_flags[bv.group], bv.vector);
}

void object_data::RemoveExtraBit(const BITVECT_DATA& bv) 
{
	if(IS_SET(extra_flags[bv.group], bv.vector))
		REMOVE_BIT(extra_flags[bv.group], bv.vector);
}

obj_index *obj_index::AddContent(object_data *obj)
{
	obj_index *tmp, *new_index;
	
	if(!obj) return NULL;

	new_index = new obj_index;
	new_index->vnum = obj->vnum;
	new_index->obj = obj;
	new_index->wear_loc = -1;

	new_index->AddToList();
	
	if(!contents) 
		contents = new_index;
	else {
		for(tmp = contents; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = new_index;
				break;
			}
		}
	}

	return new_index;
}

void obj_index::RemoveContent(obj_index **index)
{
	obj_index *tmp;

	if(*index == NULL)
		return;

	if(*index == contents) {
		contents = contents->next;

		(*index)->RemoveFromList();

		*index = NULL;
	} else {
		for(tmp = contents; tmp; tmp = tmp->next) {
			if(tmp->next == *index) {
				tmp->next = (*index)->next;
				
				(*index)->RemoveFromList();

				*index = NULL;
				
				break;
			}
		}
	}
}

void obj_index::RemoveContents()
{
	obj_index *tmp, *next;
	
	for(tmp = contents; tmp; tmp = next) {
		next = tmp->next;

		tmp->RemoveFromList();
		
		tmp = NULL;
	}
}

bool object_data::IsContainer() 
{ 
	switch(item_type) {
		case TYPE_CONTAINER:
		case TYPE_QUIVER:
		case TYPE_STORAGECHEST:
		case TYPE_SCABBARD:
			return true;
		default: return false;
	}
	
	return false;
}

CString object_data::ShowObject()
{
	CString str;

	str = description + "&n";
	
	return str;
}

obj_index *object_data::AddContent(object_data *obj)
{
	obj_index *o_index, *tmp;

	if(obj == NULL)
		return NULL;

	o_index = new obj_index;
	o_index->vnum = obj->vnum;
	o_index->obj = obj;
	o_index->in_obj = this;
	
	o_index->AddToList();

	if(contains == NULL) 
		contains = o_index;
	else {
		for(tmp = contains; tmp; tmp = tmp->next) {
			if(tmp->next == NULL) {
				tmp->next = o_index;
				break;
			}
		}
	}

	return o_index;
}

void object_data::AddContent(obj_index *obj)
{
	obj_index *tmp;

	if(obj == NULL)
		return;
	
	obj->in_obj = this;

	if(contains == NULL) 
		contains = obj;
	else 
	{
		for(tmp = contains; tmp; tmp = tmp->next) 
		{
			if(tmp->next == NULL) 
			{
				tmp->next = obj;
				break;
			}
		}
	}
}

void object_data::RemoveContent(obj_index *obj)
{
	obj_index *tmp;

	if(obj == NULL)
		return;

	if(obj == contains) {
		contains = contains->next;
		obj->next = NULL;
		obj->in_obj = NULL;
	} else {
		for(tmp = contains; tmp; tmp = tmp->next) {
			if(tmp->next == obj) {
				tmp->next = obj->next;
				obj->next = NULL;
				obj->in_obj = NULL;
				break;
			}
		}
	}
}

void object_data::RemoveContents()
{
	obj_index *tmp, *next;

	for(tmp = contains; tmp; tmp = next) {
		next = tmp->next;
		
		tmp->next = NULL;

		tmp->RemoveFromList();
	}

	contains = NULL;
}

void obj_index::AddToList()
{
	obj_index *tmp;

	if(o_ind_head == NULL)
		o_ind_head = this;
	else 
	{
		for(tmp = o_ind_head; tmp; tmp = tmp->n_list) 
		{
			if(tmp->n_list == NULL)
			{
				tmp->n_list = this;
				break;
			}
		}
	}
}

void obj_index::RemoveFromList()
{
	obj_index *tmp, *next = NULL;

	if(o_ind_head == NULL)	
	{
		RemoveContents();
		
		delete this;
		return;
	}
	else if(this == o_ind_head)
	{
		o_ind_head = this->n_list;
		this->n_list = NULL;
	}
	else
	{
		for(tmp = o_ind_head; tmp; tmp = next)
		{
			if(tmp->n_list == this) 
			{
				tmp->n_list = n_list;
				n_list = NULL;
				
				break;
			}
			else
				next = tmp->n_list;
		}
	}
	
	RemoveContents();
	
	delete this;
}

bool obj_index::IsContainer()
{
	if(obj)
		return obj->IsContainer();

	return false;
}

extra_desc *obj_index::GetFirstExtraDesc()
{
	if(obj)
		return obj->first_extra_descr;

	return NULL;
}

bool obj_index::IsName(CString &arg)
{
	if(obj)
		return obj->IsName(arg);

	return false;
}

bool object_data::IsName(CString &arg)
{
	if(name.Find(arg) > -1)
		return true;

	return false;
}

CString obj_index::ShowObject()
{
	CString str("A non-existant object.");

	if(obj)
		return obj->ShowObject();

	return str;
}

CString obj_index::GetShortName()
{
	if(obj)
		return obj->short_descr;

	return CString("A non-existant object");
}

bool object_data::IsWearable(int loc)
{
	if(IS_SET(wear_flags, wear_names[loc].bit))
		return true;

	return false;	
}

bool obj_index::IsWearable(int loc)
{
	if(obj)
		return obj->IsWearable(loc);

	return false;
}

CString obj_index::GetExtraDesc(CString &str)
{
	extra_desc *ed;

	if(!obj)
		return "";
	
	for(ed = obj->first_extra_descr; ed; ed->next)
	{
		if(ed->keyword.Find(str) > -1)
			return ed->description;
	}

	return "";
}