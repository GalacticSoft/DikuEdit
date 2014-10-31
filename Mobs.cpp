#include "StdAfx.h"
#include "Classes.h"
mob_data *mob_data::first_mob = NULL;
mob_data *mob_data::last_mob = NULL;

mob_data *mob_data::def_mob = NULL;

shop_data *shop_data::first_shop = NULL;
shop_data *shop_data::last_shop = NULL;

int mob_data::high_mob_vnum = 1;

const char mob_data::class_name[] = "mob_data";
const int mob_data::class_index = MOB_DATA;

const char mob_index::class_name[] = "mob_index";
const int mob_index::class_index = MOB_INDEX;

const BITVECT_DATA AFF_NONE 			= {0,    0};
const BITVECT_DATA AFF_BLIND			= {0, BV00};
const BITVECT_DATA AFF_INVISIBLE		= {0, BV01};
const BITVECT_DATA AFF_FARSEE			= {0, BV02};
const BITVECT_DATA AFF_DETECT_INVIS	 	= {0, BV03};
const BITVECT_DATA AFF_HASTE			= {0, BV04};
const BITVECT_DATA AFF_SENSE_LIFE		= {0, BV05};
const BITVECT_DATA AFF_MINOR_GLOBE		= {0, BV06};
const BITVECT_DATA AFF_STONESKIN		= {0, BV07};
const BITVECT_DATA AFF_UNDERDARK_VIS	= {0, BV08};
const BITVECT_DATA AFF_SHADOW			= {0, BV09};
const BITVECT_DATA AFF_GHOUL			= {0, BV10}; // wraithform
const BITVECT_DATA AFF_GILLS			= {0, BV11}; // waterbreath
const BITVECT_DATA AFF_KO				= {0, BV12};
const BITVECT_DATA AFF_PROTECT_EVIL	  	= {0, BV13};
const BITVECT_DATA AFF_BOUND			= {0, BV14};
const BITVECT_DATA AFF_SLOW_POISON		= {0, BV15};
const BITVECT_DATA AFF_PROTECT_GOOD		= {0, BV16};
const BITVECT_DATA AFF_SLEEP		   	= {0, BV17};
const BITVECT_DATA AFF_SKL_AWARE		= {0, BV18};
const BITVECT_DATA AFF_SNEAK			= {0, BV19};
const BITVECT_DATA AFF_HIDE				= {0, BV20};
const BITVECT_DATA AFF_FEAR				= {0, BV21};
const BITVECT_DATA AFF_CHARM			= {0, BV22};
const BITVECT_DATA AFF_MEDITATE			= {0, BV23};
const BITVECT_DATA AFF_BARKSKIN			= {0, BV24};
const BITVECT_DATA AFF_INFRARED			= {0, BV25};
const BITVECT_DATA AFF_LEVITATE			= {0, BV26};
const BITVECT_DATA AFF_FLYING			= {0, BV27};
const BITVECT_DATA AFF_AWARE 			= {0, BV28};
const BITVECT_DATA AFF_PROTECT_FIRE		= {0, BV29};
const BITVECT_DATA AFF_CAMPING	        = {0, BV30};

const BITVECT_DATA AFF_FLAMING			= {1, BV00};
const BITVECT_DATA AFF_ULTRAVISION		= {1, BV01};
const BITVECT_DATA AFF_DETECT_EVIL		= {1, BV02};
const BITVECT_DATA AFF_DETECT_GOOD		= {1, BV03};
const BITVECT_DATA AFF_DETECT_MAGIC		= {1, BV04};
const BITVECT_DATA AFF_MAJOR_PHYSICAL	= {1, BV05};
const BITVECT_DATA AFF_PROTECT_COLD		= {1, BV06};
const BITVECT_DATA AFF_PROTECT_LIGHTNING= {1, BV07};
const BITVECT_DATA AFF_MINOR_PARA		= {1, BV08};
const BITVECT_DATA AFF_HOLD				= {1, BV09}; // major para
const BITVECT_DATA AFF_SLOWNESS			= {1, BV10};
const BITVECT_DATA AFF_MAJOR_GLOBE		= {1, BV11};
const BITVECT_DATA AFF_PROTECT_GAS		= {1, BV12};
const BITVECT_DATA AFF_PROTECT_ACID		= {1, BV13};
const BITVECT_DATA AFF_POISON			= {1, BV14};
const BITVECT_DATA AFF_SOULSHIELD		= {1, BV15};
const BITVECT_DATA AFF_DUERGAR_HIDE		= {1, BV16};
const BITVECT_DATA AFF_MINOR_INVIS		= {1, BV17};
const BITVECT_DATA AFF_VAMP_TOUCH		= {1, BV18};
const BITVECT_DATA AFF_STUNNED			= {1, BV19};
const BITVECT_DATA AFF_DROPPED_PRIMARY	= {1, BV20};
const BITVECT_DATA AFF_DROPPED_SECOND	= {1, BV21};
const BITVECT_DATA AFF_FUMBLED_PRIMARY	= {1, BV22};
const BITVECT_DATA AFF_CTFFLAG   		= {1, BV23};
const BITVECT_DATA AFF_HOLDING_BREATH	= {1, BV24};
const BITVECT_DATA AFF_MEMORIZING		= {1, BV25};
const BITVECT_DATA AFF_DROWNING			= {1, BV26};
const BITVECT_DATA AFF_PASS_DOOR		= {1, BV27};
const BITVECT_DATA AFF_DRAINING			= {1, BV28};
const BITVECT_DATA AFF_CASTING			= {1, BV29};
const BITVECT_DATA AFF_SCRIBING			= {1, BV30};

const BITVECT_DATA AFF_TENSORS_DISC		= {2, BV00};  // Unused DE bit
const BITVECT_DATA AFF_TRACKING			= {2, BV01};
const BITVECT_DATA AFF_SINGING			= {2, BV02};
const BITVECT_DATA AFF_ECTOPLASMIC		= {2, BV03};
const BITVECT_DATA AFF_ABSORBING		= {2, BV04};  // Unused DE bit
const BITVECT_DATA AFF_VAMP_BITE		= {2, BV05};  // Unused DE bit
const BITVECT_DATA AFF_SPIRIT_WARD		= {2, BV06};
const BITVECT_DATA AFF_GREATER_SPIRIT_WARD	= {2, BV07};
const BITVECT_DATA AFF_MASTERED			= {2, BV08};  // Unused DE bit - For control over summoned/called creatures
const BITVECT_DATA AFF_SILVER			= {2, BV09};
const BITVECT_DATA AFF_PLUS_ONE			= {2, BV10};
const BITVECT_DATA AFF_PLUS_TWO			= {2, BV11};
const BITVECT_DATA AFF_PLUS_THREE		= {2, BV12};
const BITVECT_DATA AFF_PLUS_FOUR		= {2, BV13};
const BITVECT_DATA AFF_PLUS_FIVE		= {2, BV14};
const BITVECT_DATA AFF_ENLARGED			= {2, BV15};
const BITVECT_DATA AFF_REDUCED			= {2, BV16};
const BITVECT_DATA AFF_COVER			= {2, BV17};
const BITVECT_DATA AFF_FOUR_ARMS		= {2, BV18};
const BITVECT_DATA AFF_INERTIAL_BARRIER	= {2, BV19};
const BITVECT_DATA AFF_INTELLECT_FORTRESS	= {2, BV20};
const BITVECT_DATA AFF_COLDSHIELD		= {2, BV21};
const BITVECT_DATA AFF_CONJURED			= {2, BV22};  // Unused DE bit - For conjured creatures...
const BITVECT_DATA AFF_SWIMMING			= {2, BV23};
const BITVECT_DATA AFF_TOWER_OF_IRON_WILL	= {2, BV24};
const BITVECT_DATA AFF_UNDERWATER		= {2, BV25};  // Unused DE bit
const BITVECT_DATA AFF_BLUR				= {2, BV26};
const BITVECT_DATA AFF_NECKBITING		= {2, BV27};  // Unused DE bit
const BITVECT_DATA AFF_ELEMENTAL_FORM	= {2, BV28};
const BITVECT_DATA AFF_PASS_WITHOUT_TRACE	= {2, BV29};
const BITVECT_DATA AFF_PALADIN_AURA		= {2, BV30};

const BITVECT_DATA AFF_LOOTER			= {3, BV00};
const BITVECT_DATA AFF_PLAGUE			= {3, BV01}; // diseased
const BITVECT_DATA AFF_SACKING			= {3, BV02};  // Unused DE bit
const BITVECT_DATA AFF_SENSE_FOLLOWER	= {3, BV03};
const BITVECT_DATA AFF_STORNOG_SPHERES	= {3, BV04};  // Unused DE bit
const BITVECT_DATA AFF_GREATER_SPHERES	= {3, BV05};  // Unused DE bit
const BITVECT_DATA AFF_VAMPIRE_FORM		= {3, BV06};  // Unused DE bit
const BITVECT_DATA AFF_NO_UNMORPH		= {3, BV07};  // Unused DE bit
const BITVECT_DATA AFF_HOLY_SACRIFICE	= {3, BV08};
const BITVECT_DATA AFF_BATTLE_ECSTASY	= {3, BV09};
const BITVECT_DATA AFF_DAZZLE			= {3, BV10};
const BITVECT_DATA AFF_DAZZLED			= {3, BV11};
const BITVECT_DATA AFF_THROAT_CRUSH		= {3, BV12};
const BITVECT_DATA AFF_REGENERATION		= {3, BV13};
const BITVECT_DATA AFF_BEARHUG			= {3, BV14};
const BITVECT_DATA AFF_GRAPPLING		= {3, BV15};
const BITVECT_DATA AFF_GRAPPLED			= {3, BV16};
const BITVECT_DATA AFF_MAGE_FLAME		= {3, BV17};  // Unused DE bit
const BITVECT_DATA AFF_NO_IMMOLATE		= {3, BV18};
const BITVECT_DATA AFF_MULTICLASS		= {3, BV19};
const BITVECT_DATA AFF_DETECT_UNDEAD	= {3, BV20};
const BITVECT_DATA AFF_CLARITY          = {3, BV21};
const BITVECT_DATA AFF_MAJOR_PARA       = {3, BV22};
const BITVECT_DATA AFF_WARD_UNDEAD      = {3, BV23};
const BITVECT_DATA AFF_TRUE_SEEING      = {3, BV24};

const BITVECT_DATA AFF_IS_FLEEING       	    = {4, BV00};
const BITVECT_DATA AFF_HUNTING          	    = {4, BV01};
const BITVECT_DATA AFF_BIOFEEDBACK              = {4, BV02};
const BITVECT_DATA AFF_FAMINE			        = {4, BV03};
const BITVECT_DATA AFF_MUTE                     = {4, BV04};
const BITVECT_DATA AFF_FAERIE_FIRE              = {4, BV05};
const BITVECT_DATA AFF_SANCTUARY                = {4, BV06};
const BITVECT_DATA AFF_CHANGE_SEX               = {4, BV07};
const BITVECT_DATA AFF_CURSE                    = {4, BV08};
const BITVECT_DATA AFF_DETECT_HIDDEN		    = {4, BV09};
const BITVECT_DATA AFF_POLYMORPH                = {4, BV10};
const BITVECT_DATA AFF_COMP_LANG                = {4, BV11};
const BITVECT_DATA AFF_DENY_EARTH               = {4, BV12};
const BITVECT_DATA AFF_DENY_AIR                 = {4, BV13};
const BITVECT_DATA AFF_DENY_FIRE                = {4, BV14};
const BITVECT_DATA AFF_DENY_WATER               = {4, BV15};
const BITVECT_DATA AFF_TRACK                    = {4, BV16};
const BITVECT_DATA AFF_JUSTICE_TRACKER          = {4, BV17};
const BITVECT_DATA AFF_LAYHANDS_TIMER           = {4, BV18};
const BITVECT_DATA AFF_ELEM_SIGHT               = {4, BV19};
const BITVECT_DATA AFF_BLOCKEDTMP               = {4, BV20};
const BITVECT_DATA AFF_MISDIRECTION             = {4, BV21};
const BITVECT_DATA AFF_VACANCY                  = {4, BV22};
const BITVECT_DATA AFF_CHANGE_SELF              = {4, BV23};
const BITVECT_DATA AFF_PROWESS                  = {4, BV24};
const BITVECT_DATA AFF_SUMMON_MOUNT_TIMER       = {4, BV25};
const BITVECT_DATA AFF_INCOMPETENCE             = {4, BV26};
const BITVECT_DATA AFF_CLIMBING                 = {4, BV27};
const BITVECT_DATA AFF_UNDEAD_MUTE              = {4, BV28};
const BITVECT_DATA AFF_COORDINATION             = {4, BV29};
const BITVECT_DATA AFF_CHARM_OTTER              = {4, BV30};

const BITVECT_DATA AFF_ENDURANCE        = {5, BV00};
const BITVECT_DATA AFF_FORTITUDE        = {5, BV01};
const BITVECT_DATA AFF_INSIGHT          = {5, BV02};
const BITVECT_DATA AFF_MIGHT            = {5, BV03};
const BITVECT_DATA AFF_SAVVY            = {5, BV04};
const BITVECT_DATA AFF_WRISTLOCKED1     = {5, BV05};
const BITVECT_DATA AFF_WRISTLOCKED2     = {5, BV06};
const BITVECT_DATA AFF_WRISTLOCKING     = {5, BV07};
const BITVECT_DATA AFF_PROTECT_UNDEAD	= {5, BV08};
const BITVECT_DATA AFF_CHANTING			= {5, BV09};
const BITVECT_DATA AFF_SIMULACRUM	    = {5, BV10};
const BITVECT_DATA AFF_APPROVAL 		= {5, BV11};
const BITVECT_DATA AFF_LISTENING        = {5, BV13};
const BITVECT_DATA AFF_INVADER_TRACKER  = {5, BV14};
const BITVECT_DATA AFF_DISGUISE         = {5, BV15};
const BITVECT_DATA AFF_DEAF             = {5, BV16};
const BITVECT_DATA AFF_HELLFIRE         = {5, BV17};
const BITVECT_DATA AFF_BLURTIMER		= {5, BV18};
const BITVECT_DATA AFF_CONSUMING		= {5, BV19};
const BITVECT_DATA AFF_DRAINEE			= {5, BV20};
const BITVECT_DATA AFF_TOWER_IRON_WILL	= {5, BV21};
const BITVECT_DATA AFF_FLUXED			= {5, BV22};
const BITVECT_DATA AFF_HP_STOP			= {5, BV23};
const BITVECT_DATA AFF_MANA_STOP		= {5, BV24};
const BITVECT_DATA AFF_MOVE_STOP		= {5, BV25};

const wear_types wear_names[MAX_WEAR] =
{
	{"UNUSED1",		0},
	{"finger1",		ITEM_WEAR_FINGER},
	{"finger2",		ITEM_WEAR_FINGER},
	{"neck1",		ITEM_WEAR_NECK},
	{"neck2",		ITEM_WEAR_NECK},
	{"body",		ITEM_WEAR_BODY},
	{"head",		ITEM_WEAR_HEAD},
	{"legs",		ITEM_WEAR_LEGS},
	{"feet",		ITEM_WEAR_FEET},
	{"hands",		ITEM_WEAR_HANDS},
	{"arms",		ITEM_WEAR_ARMS},
	{"UNUSED2",		0},
	{"about",		ITEM_WEAR_ABOUT},
	{"waist",		ITEM_WEAR_WAIST},
	{"wrist1",		ITEM_WEAR_WRIST},
	{"wrist2",		ITEM_WEAR_WRIST},
	{"hand1",		ITEM_HOLD},
	{"UNUSED3",		0},
	{"hand2",		ITEM_HOLD},
	{"eyes",		ITEM_WEAR_EYES},
	{"face",		ITEM_WEAR_FACE},
	{"ear1",		ITEM_WEAR_EAR},
	{"ear2",		ITEM_WEAR_EAR},
	{"badge",		ITEM_BADGE},
	{"back",		ITEM_WEAR_ONBACK},
	{"belt1",		ITEM_ATTACH_BELT},
	{"belt2",		ITEM_ATTACH_BELT},
	{"belt3",		ITEM_ATTACH_BELT},
	{"UNUSED4",		0},
	{"quiver",		ITEM_QUIVER},
	{"tail",		ITEM_TAIL},
	{"horse",		ITEM_HORSE_BODY},
	{"horns",		ITEM_HORNS},
	{"nose",		ITEM_NOSE},
	{"hand3",		ITEM_HOLD},
	{"hand4",		ITEM_HOLD},
	{"arms2",		ITEM_WEAR_ARMS},
	{"hands2",		ITEM_WEAR_HANDS},
	{"wrist3",		ITEM_WEAR_WRIST},
	{"wrist4",		ITEM_WEAR_WRIST},
};

CString slot_names[MAX_WEAR] = {
	"UNUSED",
	"Left Finger",
	"Right Finger",
	"Neck",
	"Throat",
	"Body",
	"Head",
	"Legs",
	"Feet",
	"Hands",
	"Arms",
	"UNUSED",
	"About Body",
	"Waist",
	"Left Wrist",
	"Right Wrist",
	"Left Hand",
	"UNUSED",
	"Right Hand",
	"Eyes",
	"Face",
	"Left Ear",
	"Right Ear",
	"Badge",
	"Back",
	"Belt 1",
	"Belt 2",
	"Belt 3",
	"UNUSED",
	"Quiver",
	"Tail",
	"Horse Body",
	"Horns",
	"Nose",
	"Lower Left Hand",
	"Lower Right Hand",
	"Lower Arms",
	"Lower Hands",
	"Lower Left Wrist",
	"Lower Right Wrist",
};

CString slot_names2[MAX_WEAR] = {
	"UNUSED",
	"<worn on finger> ",
	"<worn on finger> ",
	"<worn around neck> ",
	"<worn around neck> ",
	"<worn on body> ",
	"<worn on head> ",
	"<worn on legs> ",
	"<worn on feet> ",
	"<worn on hands> ",
	"<worn on arms> ",
	"UNUSED",
	"<worn about body> ",
	"<worn around waist> ",
	"<worn on wrist> ",
	"<worn on wrist> ",
	"<held in hand>",
	"UNUSED",
	"<held in hand> ",
	"<worn over eyes> ",
	"<worn on face> ",
	"<worn in ear> ",
	"<worn in ear> ",
	"<worn as badge> ",
	"<worn on back> ",
	"<attached to belt> ",
	"<attached to belt> ",
	"<attached to belt> ",
	"UNUSED",
	"<worn as quiver> ",
	"<worn on tail> ",
	"<worn on horse body> ",
	"<worn on horns> ",
	"<worn in nose> ",
	"<held in lower hand> ",
	"<held in lower hand> ",
	"<worn on lower arms> ",
	"<worn on lower hands> ",
	"<worn on lower wrist> ",
	"<worn on lower wrist> ",
};

int equip_top_down[MAX_WEAR] = {
		23, 32,  6, 19,
		20, 33, 21, 22,
		 3,  4, 12, 24,
		29,  5, 10, 36,
		 9, 37, 14, 15,
		38, 39,  1,  2,
		16, 18, 34, 35,
        13, 25, 26, 27,
		30,  7,  8, -1,
		-1, -1, -1, -1,
};

CString positions[POS_MAX] = { 
	"Dead",
	"Mortally Wounded",
	"Incapacitated",
	"Sleeping",
	"Reclining",
	"Resting",
	"Sitting",
	"Kneeling",
	"Standing",
};

CString sexs[SEX_MAX] = { 
	"Neutral",
	"Male",
	"Female",
};

CString pro_sex[SEX_MAX] = {
	"It",
	"He",
	"She",
};

CString sex[SEX_MAX] = 
{
	"its",
	"his",
	"her",
};

CString sizes[MAX_SIZE] = {
	"Any", 
	"Tiny",
	"Small", 
	"Medium",
	"Large", 
	"Huge", 
	"Giant",
	"Titanic",
	"Gargantuan", 
	"None",
};

CString races[MAX_RACE][2] = {
	{"Human",			"PH"},
	{"Barbarian",		"PB"},
	{"Grey Elf",		"PE"},
	{"Rakshasa",		"RA"},
	{"Half-Elf",		"P2"},
	{"Flind",			"FL"},
	{"Drow Elf",		"PL"},
	{"Mountain Dwarf",	"PM"},
	{"Duergar Dwarf",	"PD"},
	{"Halfling",		"PF"},
	{"Troll",			"PT"},
	{"Ogre",			"PO"},
	{"Orc",				"HO"},
	{"Gnome",			"PG"},
	{"Centaur",			"CT"},
	{"Githyanki",		"GI"},
	{"Goblin",			"HG"},
	{"Minotaur",		"MT"},
	{"Githzerai",		""}, //NEEDS CHANGING
	{"Thri-kreen",		"TK"},
	{"Half-Orc",		"H2"},
	{"Neogi",			""}, //NEEDS CHANGING
	{"Sahuagin",		"SA"},
	{"Dark Human",		""}, //NEEDS CHANGING
	{"Half-Dwarf",		"D2"},
	{"Half-Kobold",		"K2"},
	{"Giant",			"G" },
	{"Illithid",		"MF"},
	{"Aquatic Elf",		"PA"},
	{"Kobold",			"K" },
	{"Hobgoblin",		"HB"},
	{"Wemic",			"WE"},
	{"Humanoid",		"H" },
	{"Demon",			"X" }, 
	{"God",				""}, //NEEDS CHANGING
	{"Devil",			"Y" },
	{"Angel",			""},//NEEDS CHANGING
	{"Faerie",			"HF"},
	{"Vampire",			"UV"},
	{"Werewolf",		"LW"},
	{"Dragon",			"D" },
	{"Beholder",		"BH"},
	{"Derro",			""},//NEEDS CHANGING
	{"Slaad",			""},//NEEDS CHANGING
	{"Golem",			"OG"},
	{"Dracolich",		"UD"},
	{"Dragonkin",		"DK"},
	{"Undead",			"U" },
	{"Ghost",			"UG"},
	{"Harpy",			"HP"},
	{"Rust Monster",	""},//NEEDS CHANGING
	{"Fire Elemental",	"EF"},
	{"Air Elemental",	"EA"},
	{"Water Elemental",	"EW"},
	{"Earth Elemental",	"EE"},
	{"Lycanthrope",		"L" },
	{"Object",			"O" },
	{"Mist",			"M" },
	{"Ixitxachitl",		""},//NEEDS CHANGING
	{"Aboleth",			""},//NEEDS CHANGING
	{"Hydra",			"DH"},
	{"Reptile",			"R"},
	{"Boar",			""},//NEEDS CHANGING
	{"Insect",			"I"	},
	{"Animal",			"A"	},
	{"Herbivore",		"AH"},
	{"Carnivore",		"AC"},
	{"Bird",			"B" },
	{"Horse",			"AE"},
	{"Primate",			"AA"},
	{"Bear",			"AB"},
	{"Bat",				"BB"},
	{"Plant",			"VP"},
	{"Tree",			"VT"},
	{"Rat",				"AR"},
	{"Parasite",		"AP"},
	{"Arachnid",		"AS"},
	{"Snake",			"RS"},
	{"Worm",			"AW"},
	{"Fish",			"F" },
	{"Shadow Elemental",""}, //NEEDS CHANGING
	//{"Umber-Hulk",		"UH"},
};

int GetRaceByKey(CString &str)
{
	for(int i = 0; i < MAX_RACE; i++)
	{
		if(str == races[i][1])
			return i;
	}

	return 0;
}

CString GetPosition(int i)
{
	if(i > POS_MAX)
		i = POS_MAX - 1;

	if(i < POS_DEAD)
		i = POS_DEAD;

	return positions[i];
}

CString GetSex(int i)
{
	if(i > SEX_MAX)
		i = SEX_MAX - 1;

	if(i < SEX_NEUTRAL)
		i = SEX_NEUTRAL;

	return sexs[i];
}

CString GetSize(int i)
{
	if(i > MAX_SIZE)
		i = MAX_SIZE - 1;

	if(i < SIZE_ANY)
		i = SIZE_NONE;

	return sizes[i];
}

CString GetRaceName(int i)
{
	if(i > MAX_RACE)
		i = MAX_RACE - 1;

	if(i < RACE_HUMAN)
		i = RACE_HUMAN;

	return races[i][0];
}

CString GetRaceKey(int i)
{
	if(i > MAX_RACE)
		i = MAX_RACE - 1;

	if(i < RACE_HUMAN)
		i = RACE_HUMAN;

	return races[i][1];
}

int GetRaceIndex(const CString& str)
{
	int i;

	for(i = 0; i < MAX_RACE; i++) {
		if(str == races[i][2])
			return i;
	}

	return -1;
}

void mob_data::AddToList()
{
	if(!first_mob) {
		first_mob = this;
		last_mob = this;
		this->next = NULL;
	} else {
		last_mob->next = this;
		last_mob = this;
		this->next = NULL;
	}
}

void mob_data::RemoveFromList()
{
	mob_data *mob;

	if(this == first_mob && this == last_mob) {
		first_mob = NULL;
		last_mob = NULL;
	}
	else if(this == first_mob) {
		first_mob = this->next;
		this->next = NULL;
	} else {
		for(mob = first_mob; mob; mob = mob->next) {
			if(mob->next == this) {
				mob->next = this->next;
				if(this == last_mob) {
					last_mob = mob;
					last_mob->next = NULL;
				}
				this->next = NULL;
			}
		}
	}
}

void mob_data::SetAff(const BITVECT_DATA& bv)
{
	if(!IS_SET(affected_by[bv.group], bv.vector))
		SET_BIT(affected_by[bv.group], bv.vector);
}
bool mob_data::AffIsSet(const BITVECT_DATA& bv)
{
	return IS_SET(affected_by[bv.group], bv.vector) ? true : false;
}

void mob_data::RemoveAff(const BITVECT_DATA& bv)
{
	if(IS_SET(affected_by[bv.group], bv.vector))
		REMOVE_BIT(affected_by[bv.group], bv.vector);
}

mob_data::mob_data()
{
	int i;
	this->next = NULL;
	this->vnum = this->high_mob_vnum;
	this->shop = NULL;
	this->quests = NULL;
	this->load_limit = 0;

	if(!def_mob)
	{
		this->alignment = 0;
		this->c_class  = CLASS_NONE;
		this->description = _T("A non-descript mob.");
		this->name = _T("mob unnamed");
		this->level = 1;
		this->long_descr = _T("An Unnamed Mob is standing here, looking sad.");
		this->position = POS_STANDING;
		this->race = RACE_HUMAN;
		this->sex = SEX_NEUTRAL;
		this->short_descr = _T("an unnamed mob");
		this->size = SIZE_ANY;
	
		this->act = 0;

		for(i = 0; i < NUM_AFFECT_VECTORS; i++)
			affected_by[i] = 0;
	}
	else
	{
		this->alignment = def_mob->alignment;
		this->c_class  = def_mob->c_class;
		this->description = def_mob->description;
		this->name = def_mob->name;
		this->level = def_mob->level;
		this->long_descr = def_mob->long_descr;
		this->position = def_mob->position;
		this->race = def_mob->race;
		this->sex = def_mob->sex;
		this->short_descr = def_mob->short_descr;
		this->size = def_mob->size;
	
		this->act = def_mob->act;

		for(i = 0; i < NUM_AFFECT_VECTORS; i++)
			affected_by[i] = def_mob->affected_by[i];
	}

		
}

shop_data::shop_data()
{
	int i;

	next = NULL;
    keeper = 0;
	
	for(i = 0; i < MAX_BUY; i++)
		buy_type [i] = 0;
	
	for(i = 0; i < MAX_SELL; i++)
		sell_item[i] = -1;  
    
	profit_buy = 100;
    profit_sell = 100;
    open_hour = 8;
    close_hour = 20;
}

void shop_data::AddToList()
{
	if(!shop_data::first_shop) {
		first_shop = this;
		last_shop = this;
		this->next = NULL;
	} else {
		last_shop->next = this;
		last_shop = this;
		this->next = NULL;
	}

	shop_count++;
}

void shop_data::RemoveFromList()
{
	shop_data *tmp;

	if(this == shop_data::first_shop) {
		shop_data::first_shop = this->next;
		this->next = NULL;
	} else {
		for(tmp = shop_data::first_shop; tmp; tmp = tmp->next) {
			if(tmp->next == this) {
				if(this == shop_data::last_shop) {
					tmp->next = NULL;
					shop_data::last_shop = tmp;
				} else {
					tmp->next = this->next;
					this->next = NULL;
				}
			}
		}
	}
}
mob_index::mob_index() 
{
	for(int i = 0; i < MAX_WEAR; i++)
		eq[i] = NULL;

	inventory = NULL;
	follower = NULL;
	group_leader = NULL;
	in_room = NULL;
	mob = NULL;
	next = NULL;
	next_in_group = NULL;
	riding = NULL;
	rider = NULL;
	vnum = -1;
}

CString mob_data::ShowMobInRoom()
{
	CString str;

	str.Format("&+L(&n&+r%d&n&+L)&n", vnum);

	str += long_descr;
	
	str += " &n&+c(&n";
	str += GetRaceName(race);
	str += "&+c)&n ";

	str += "&+c(&n";
	str +=	GetSize(size);
	str += "&+c)&n";

	return str;
}

CString mob_data::ShowMob()
{
	CString str;

	str = description + "&n\n&+c";
	str += pro_sex[sex] + " is " + GetSize(size) + " in size.&n";

	return str;
}

CString mob_index::ShowMob()
{
	CString str("");

	if(mob)
		str += mob->ShowMob();
	else
		str += "A non-existant mobile.";

	str+= "\n\nEquipment:";
	for(int i = 0; i < MAX_WEAR; i++)
	{
		if(eq[equip_top_down[i]]) 
		{
			str += "\n" + slot_names2[equip_top_down[i]];
			str += "  " + eq[equip_top_down[i]]->GetShortName();
		}
	}

	if(inventory)
	{
		str+= "\n\nIn Inventory:";

		for(obj_index *obj= inventory; obj; obj= obj->next)
			str += "\n" + obj->GetShortName();
	}

	return str;
}

void mob_index::AddObjToInv(obj_index *obj)
{
	obj_index *index;

	if(!obj) return;

	if(!inventory)
		inventory = obj;
	else {
		for(index = inventory; index; index = index->next) {
			if(index->next == NULL) {
				index->next = obj;
				break;
			}
		}
	}
}

void mob_index::AddObjToInv(object_data *obj)
{
	obj_index *new_index;

	if(!obj) return;

	new_index = new obj_index();
	
	if(obj)
		new_index->vnum = obj->vnum;
	else 
		new_index->vnum = -1;

	new_index->obj = obj;
	new_index->AddToList();

	AddObjToInv(new_index);
}

void mob_index::RemoveObjFromInv(obj_index *obj)
{
	obj_index *index;

	if(!obj) return;

	if(obj == inventory) {
		inventory = inventory->next;
		obj->next = NULL;
	} else {
		for(index = inventory; index; index = index->next) {
			if(index->next == obj) {
				index->next = obj->next;
				obj->next = NULL;
				break;
			}
		}
	}
}

void mob_index::EquipObj(obj_index *obj, int loc)
{

	if(!obj)
		return;

	if(loc < 0 || loc > MAX_WEAR)
		return;

	if(eq[loc])
	{
		AddObjToInv(eq[loc]);
		eq[loc] = NULL;
	}

	if(obj->in_obj)
		obj->in_obj->RemoveContent(obj);

	if(obj->in_room)
		obj->in_room->RemoveContent(obj);

	if(obj->on_mob)
		obj->on_mob->RemoveObjFromInv(obj);

	eq[loc] = obj;
	obj->on_mob = this;
}

void mob_index::EquipObj(object_data *obj, int loc)
{
	obj_index *o_index;
	
	if(loc < 0 || loc > MAX_WEAR)
		return;
	
	o_index = new obj_index();
	o_index->vnum = obj->vnum;
	o_index->obj = obj;
	o_index->on_mob = this;
	
	o_index->AddToList();

	if(eq[loc]) 
	{
		AddObjToInv(eq[loc]);
		eq[loc] = NULL;
	}

	eq[loc] = o_index;
}

void mob_index::UnEquipObj(obj_index *obj, int loc)
{

}

void mob_index::DeleteAllEquip()
{
	for(int i = 0; i < MAX_WEAR; i++) 
	{
		if(eq[i]) 
		{
			eq[i]->RemoveFromList();
			eq[i] = NULL;
		}
	}
}

void mob_index::DeleteAllInv()
{
	obj_index *index, *next;

	for(index = inventory; index; index = next) {
		next = index->next;
		index->RemoveFromList();
	}

	inventory = NULL;
}

void mob_index::AddFollower(mob_index *mob)
{
	if(!mob)
		return;

	if(group_leader == mob)
		return;

	if(mob->group_leader)
		mob->group_leader->RemoveFollower(mob);

	if(!follower)
		follower = mob;
	else
	{
		for(mob_index* tmp = follower; tmp; tmp = tmp->next_in_group)
		{
			if(tmp->next_in_group == NULL)
			{
				tmp->next_in_group = mob;
				break;
			}
		}
	}
	
	mob->group_leader = this;
}

void mob_index::RemoveFollower(mob_index *mob)
{
	if(!mob)
		return;

	if(!follower)
		return;

	if(mob == follower)
		follower = follower->next_in_group;
	else
	{	
		for(mob_index *tmp = follower; tmp; tmp = tmp->next_in_group)
		{
			if(tmp->next_in_group = mob)
			{
				tmp->next_in_group = mob->next_in_group;
				break;
			}
		}
	}
	
	mob->next_in_group = NULL;
	mob->group_leader = NULL;
}

void mob_index::RemoveFollowers()
{	
	while(follower)
		RemoveFollower(follower);

	follower = NULL;
}

void mob_index::AddRider(mob_index *mob)
{
	if(!mob) return;

	RemoveRider();
	mob->RemoveRiding();

	rider = mob;
	mob->riding = this;
}

void mob_index::RemoveRider()
{
	if(rider)
	{
		rider->riding = NULL;
		rider = NULL;
	}
}

void mob_index::AddRiding(mob_index *mob)
{
	if(!mob) return;

	RemoveRiding();
	mob->RemoveRider();

	riding = mob;
	mob->rider = this;
}

void mob_index::RemoveRiding()
{	
	if(riding)
	{
		riding->rider = NULL;
		riding = NULL;
	}
}

bool mob_index::IsFollower(mob_index *mob)
{
	mob_index *tmp;
	
	if(!mob || !follower)
		return false;

	for(tmp = follower; tmp; tmp = tmp->next_in_group)
	{
		if(tmp == mob)
			return true;
	}

	return false;
}

bool mob_data::IsMount()
{
	if(IS_SET(act, ACT_MOUNT))
		return true;

	return false;
}

bool mob_index::IsMount()
{
	if(mob)
	{
		if(mob->IsMount())
			return true;
	}

	return false;
}

CString mob_index::GetShortName()
{

	CString str("A non-existant mob");

	if(mob)
		return mob->short_descr;
	else
		return str;
}

CString mob_index::ShowMobInRoom()
{
	CString str;

	if(mob)
		return mob->ShowMobInRoom();
	else
	{
		str.Format("&+L(&N&+r%d&N&+L)&NA non-existant mob.", vnum);
		return str;
	}
}

int mob_index::GetRace()
{
	if(mob)
		return mob->race;

	return RACE_HUMAN;
}

bool mob_index::IsName(CString &arg)
{
	if(mob)
		return mob->IsName(arg);

	return false;
}

bool mob_data::IsName(CString &arg)
{
	if(name.Find(arg) > -1)
		return true;

	return false;
}

int mob_index::GetSex()
{
	if(mob)
		return mob->sex;

	return SEX_NEUTRAL;
}

bool mob_index::InInventory(obj_index*obj)
{
	obj_index *tmp;
	
	for(tmp = inventory; tmp; tmp = tmp->next)
	{
		if(tmp == obj)
			return true;
	}

	return false;
}

obj_index* mob_index::GetObjInInv(int vnum)
{
	obj_index*tmp;

	for(tmp = inventory; tmp; tmp = tmp->next)
	{
		if(tmp->vnum == vnum)
			return tmp;
	}

	return NULL;
}

bool mob_index::HasQuestItem(object_data *obj)
{
	mob_data *mob;

	obj_index *oind;

	if((mob = this->mob))
	{
		for(oind = inventory; oind; oind = oind->next)
		{
			if(oind->obj == obj)
				return true;
		}
	}

	return false;
}

/*bool mob_index::CheckQuest(quest_data *quest)
{
	//for(quest_item *item = quest->receive
}*/