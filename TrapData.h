// TrapData.h: interface for the TrapData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAPDATA_H__2671F285_F227_4F06_90B4_645B5D60AFA8__INCLUDED_)
#define AFX_TRAPDATA_H__2671F285_F227_4F06_90B4_645B5D60AFA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Trap types
enum TrapTypes
{
	TRAP_SLEEP	=0,
	TRAP_TELEPORT   =1,
	TRAP_FIRE       =2,
	TRAP_COLD       =3,
	TRAP_ACID       =4,
	TRAP_ENERGY     =5,
	TRAP_BLUNT      =6,
	TRAP_PIERCING   =7,
	TRAP_SLASHING   =8,
	TRAP_DISPEL     =9,
	TRAP_GATE       =10,
	TRAP_SUMMON     =11,
	TRAP_WITHER     =12,
	TRAP_HARM       =13,
	TRAP_POISON     =14,
	TRAP_PARALYSIS  =15,
	TRAP_STUN       =16,
	TRAP_DISEASE    =17,
	TRAP_MAX,
};

// Trap triggers
enum TrapTrigs
{
	TRIG_MOVE		=BV00,
	TRIG_GETPUT		=BV01,
	TRIG_FULLROOM   =BV02,
	TRIG_NORTH      =BV03,
	TRIG_EAST		=BV04,
	TRIG_SOUTH		=BV05,
	TRIG_WEST		=BV06,
	TRIG_UP			=BV07,
	TRIG_DOWN		=BV08,
	TRIG_OPEN		=BV09,
	TRIG_UNLIMITED  =BV10,
	TRIG_GLYPH      =BV11,
	TRIG_WEAR       =BV12,
	TRIG_UNEQUIP    =BV13,
	TRIG_STEAL      =BV14,
	TRIG_ENCHANT    =BV15,
	TRIG_UNCURSE	=BV16,
	TRIG_MAX = 17,
};

class TrapData  
{
public:
	int trigger;
	int damage;
	int charges;
	int level;
	int percent;

public:
	TrapData() : trigger(0), damage(0), charges(0), level(0), percent(0){};
	virtual ~TrapData();

};

struct trap_triggers
{
	char *name;
	int bit;
};

extern char* trap_damage[TRAP_MAX];

extern trap_triggers trap_trigs[TRIG_MAX];

#endif // !defined(AFX_TRAPDATA_H__2671F285_F227_4F06_90B4_645B5D60AFA8__INCLUDED_)
