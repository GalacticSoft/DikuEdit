#include "StdAfx.h"
#include "Classes.h"

class_data classes[MAX_CLASS] = {
	{"None",				true},
	{"Warrior",				true},
	{"Sorcerer",			true},
	{"Psionicist",			true},
	{"Cleric",				true},
	{"Thief",				true},
	{"Assassin",			true},
	{"Mercenary",			true},
	{"Paladin",				true},
	{"Anti-Paladin",		true},
	{"Ranger",				true},
	{"Earth Elementalist",	true},
	{"Air Elementalist",	true},
	{"Fire Elementalist",	true},
	{"Water Elementalist",	true},
	{"Shaman",				true},
	{"Druid",				true},
	{"Bard",				true},
	{"Hunter",				true},
	{"Illusionist",			true},
	{"Monk",				false},
	{"Mystic",				false},
	{"Necromancer",			true},
	{"Chronomancer",		true},
	{"Warlock",				false},
	{"Enslaver",			false},
	{"Reaver",				false},
};

CString GetClassName(int i)
{
	if(i > MAX_CLASS)
		i = MAX_CLASS - 1;

	if(i < CLASS_NONE)
		i = CLASS_NONE;

	return classes[i].name;
}

bool ClassAvail(int i)
{
	if(i > MAX_CLASS)
		i = MAX_CLASS - 1;

	if(i < CLASS_NONE)
		i = CLASS_NONE;

	return classes[i].avail;
}