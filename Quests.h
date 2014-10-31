#ifndef _QUESTS_H_
#define _QUESTS_H_

// Types for object given to mob:
//
// 0 = Object
// 1 = Coins (in copper)
// 2 = Object Type (container, weapon, etc)
enum Wants 
{
	QST_WANTS_OBJ	=	0,
	QST_WANTS_COINS	=	1,
	QST_WANTS_TYPE	=	2,
	QST_WANTS_MAX,
};

// Types for object given to player by mob:
//
// 0 = Object (vnum)
// 1 = Coins (amount)
// 2 = Skill (number)
// 3 = Experience (amount)
// 4 = Spell (number)
// 5 = Cast Spell (number)
// 6 = Transfer mobs from room (vnum)
// 7 = Create mobile (vnum)
// 8 = Create mobile and make it player's pet (vnum)
// 9 = Transfer player to room (vnum)
// 10 = Transfer whole group to room (vnum)
enum Rewards
{
	QST_GIVES_OBJ	= 0,
	QST_GIVES_COINS	= 1,
	QST_GIVES_SKILL	= 2,
	QST_GIVES_EXP	= 3,
	QST_GIVES_SPELL	= 4,
	QST_GIVES_AFF	= 5,	
	QST_GIVES_MOBS	= 6,
	QST_GIVES_MOB	= 7,
	QST_GIVES_PET	= 8,
	QST_GIVES_TELE	= 9,
	QST_GIVES_TRANS	= 10,
	QST_GIVES_MAX,
};

enum {MOB_WANTS, MOB_REWARDS};

class quest_item
{
public:
    bool		complete;
    int			type;
    int			value;
    quest_item	*next;

public:
	quest_item() : complete(false), type(0), value(0), next(NULL) { };
};

class quest_data
{
public:
    quest_data   *next;
    quest_item   *receive;
    quest_item   *give;
    CString		 disappear;
    CString      complete;

public:
	quest_data();	
	~quest_data();

};

class talk_data
{
public:
    talk_data	*next;		//next speech quest
    CString		keywords;	//keywords that activate quest
    CString		message;	//message when keywords are spoken

public:
	talk_data(); //constructor
	~talk_data();
};

class quest_index_data
{
public:
    int				 vnum;		// vnum of mobile quest is attached to
    quest_data		 *quests;	// the individual quests associated with each mob
    talk_data		 *messages; // talk data associated with a mob
    quest_index_data *next;		// next qid in list

public:
	quest_index_data() : vnum(0), quests(NULL), messages(NULL), next(NULL) { }; //constructor
	
	~quest_index_data()
	{
		quest_data* qst, *next_qst;
		talk_data* clue, *next_clue;

		for(qst = quests; qst; qst = next_qst)
		{
			next_qst = qst->next;
			delete qst;
		}
		for(clue = messages; clue; clue = next_clue)
		{
			next_clue = clue->next;
			delete clue;
		}
	};

			
};

extern const CString want_types[QST_WANTS_MAX];
extern const CString reward_types[QST_GIVES_MAX];
extern const CString wants[QST_WANTS_MAX];
extern const CString rewards[QST_GIVES_MAX];

#endif