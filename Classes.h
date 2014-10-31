#ifndef _CLASSES_H_
#define _CLASSES_H_

enum Classes 
{
	CLASS_NONE = 0,
	CLASS_WARRIOR,
	CLASS_SORCERER,
	CLASS_PSIONICIST,
	CLASS_CLERIC,
	CLASS_THIEF,
	CLASS_ASSASSIN,
	CLASS_MERCENARY,
	CLASS_PALADIN,
	CLASS_ANTIPALADIN,
	CLASS_RANGER,
	CLASS_ELEMENT_EARTH,
	CLASS_ELEMENT_AIR,
	CLASS_ELEMENT_FIRE,
	CLASS_ELEMENT_WATER,
	CLASS_SHAMAN,
	CLASS_DRUID,
	CLASS_BARD,
	CLASS_HUNTER,
	CLASS_ILLUSIONIST,
	CLASS_MONK,
	CLASS_MYSTIC,
	CLASS_NECROMANCER,
	CLASS_CHRONOMANCER,
	CLASS_WARLOCK,
	CLASS_ENSLAVER,
	CLASS_REAVER,
	MAX_CLASS,
};

class class_data 
{
public:
	char *name; //name of class
	bool avail; //true if class is in use
	int  index;

public:
	class_data *next;
	class_data *prev;
};

class ClassList
{
public:
	class_data *first;
	class_data *last;

	int count;
};

CString		GetClassName(int i);
bool		ClassAvail(int i);

#endif