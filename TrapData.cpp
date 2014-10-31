// TrapData.cpp: implementation of the TrapData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinDE.h"
#include "TrapData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

char* trap_damage[TRAP_MAX] =
{
	"Sleep",
	"Teleport",
	"Fire",
	"Cold",
	"Acid",
	"Energy",
	"Bludgeon",
	"Pierce",
	"Slash",
	"Dispel",
	"Gate",
	"Summon",
	"Wither",
	"Harm",
	"Poison",
	"Paralyze",
	"Stun",
	"Disease",
};

trap_triggers trap_trigs[TRIG_MAX] =
{
	{"Move",		TRIG_MOVE		},
	{"Get/Put",		TRIG_GETPUT		},
	{"Full Room",	TRIG_FULLROOM	},
	{"North",		TRIG_NORTH		},
	{"East",		TRIG_EAST		},
	{"South",		TRIG_SOUTH		},
	{"West",		TRIG_WEST		},
	{"Up",			TRIG_UP			},
	{"Down",		TRIG_DOWN		},
	{"Open",		TRIG_OPEN		},
	{"Unlimited",	TRIG_UNLIMITED	},
	{"Glyph",		TRIG_GLYPH		},
	{"Wear",		TRIG_WEAR		},
	{"Un-Equip",	TRIG_UNEQUIP	},
	{"Steal",		TRIG_STEAL		},
	{"Enchant",		TRIG_ENCHANT	},
	{"Uncurse",		TRIG_UNCURSE	},

};

TrapData::~TrapData()
{

}
