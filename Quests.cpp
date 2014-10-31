#include "StdAfx.h"
#include "Quests.h"

const CString want_types[QST_WANTS_MAX] =
{
	"Mob Wants Object",
	"Mob Wants Coins",
	"Mob Wants Object Type",
};

const CString wants[QST_WANTS_MAX] =
{
	"Object",
	"Coins ",
	"Type  ",
};

const CString reward_types[QST_GIVES_MAX] = 
{
	"Mob Gives Object",
	"Mob Gives Coins",
	"Mob Grants Skill",
	"Mob Gives Experience",
	"Mob Grants Spell",
	"Mob Casts Spell",
	"Mob Transfers Mobs",
	"Mob Creates Mob",
	"Mob Creates Pet",
	"Mob Teleports Char",
	"Mob Transfers Group",
};

const CString rewards[QST_GIVES_MAX] =
{
	"Object",
	"Coins ",
	"Skill ",
	"Exp   ",
	"Spell ",
	"Casts ",
	"Mobs  ",
	"Mob   ",
	"Pet   ",
	"Tele  ",
	"Trans ",
};

quest_data::quest_data() : next(NULL), receive(NULL), give(NULL), disappear(""), complete("") 
{
	quest_count++;
}
	
quest_data::~quest_data()
{
	quest_item *tmp, *next;
	for(tmp = receive; tmp; tmp = next)
	{
		next = tmp->next;
		delete tmp;
	}
	for(tmp = give; tmp; tmp = next)
	{
		next = tmp->next;
		delete tmp;
	}

	quest_count--;
}

talk_data::talk_data() : next(NULL), keywords(""), message("") {quest_count++;}; //constructor
talk_data::~talk_data() {quest_count--;}