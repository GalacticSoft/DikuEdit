// DlgSelectAff.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgSelectAff.h"
#include "EditAffBits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSelectAff dialog

const MobAffectData mob_aff_flags[] = {
	{"none",				&AFF_NONE,				false	},
	{"Blind",				&AFF_BLIND,				true	},
	{"Invisible",			&AFF_INVISIBLE,			true	},
	{"Farsee",				&AFF_FARSEE,			true	},
	{"Detect Invis",		&AFF_DETECT_INVIS,		true	},
	{"Haste",				&AFF_HASTE,				true	},
	{"Sense Life",			&AFF_SENSE_LIFE,		true	},
	{"Minor Globe",			&AFF_MINOR_GLOBE,		true	},
	{"Stone Skin",			&AFF_STONESKIN,			true	},
	{"Underdark vision",	&AFF_UNDERDARK_VIS,		true	},
	{"Shadow",				&AFF_SHADOW,			false	},
	{"Ghoul",				&AFF_GHOUL,				true	}, // wraithform
	{"Gills",				&AFF_GILLS,				true	}, // waterbreath
	{"Knocked Out",			&AFF_KO,				true	},
	{"Protection from Evil",&AFF_PROTECT_EVIL,		true	},
	{"Bound",				&AFF_BOUND,				true	},
	{"Slow Poison",			&AFF_SLOW_POISON,		true	},
	{"Protection from Good",&AFF_PROTECT_GOOD,		true	},
	{"Sleep",				&AFF_SLEEP,				true	},
	{"Skill Aware",			&AFF_SKL_AWARE,			false	},
	{"Sneak",				&AFF_SNEAK,				true	},
	{"Hide",				&AFF_HIDE,				true	},
	{"Fear",				&AFF_FEAR,				true	},
	{"Charm",				&AFF_CHARM,				false	},
	{"Meditate",			&AFF_MEDITATE,			true	},
	{"Barkskin",			&AFF_BARKSKIN,			true	},
	{"Infravision",			&AFF_INFRARED,			true	},
	{"Levitate",			&AFF_LEVITATE,			true	},
	{"Flying",				&AFF_FLYING,			true	},
	{"Aware",				&AFF_AWARE,				true	},
	{"Protection from Fire",&AFF_PROTECT_FIRE,		true	},
	{"Camping",				&AFF_CAMPING,			false	},

	{"Fireshield",			&AFF_FLAMING,			true	},
	{"Ultravision",			&AFF_ULTRAVISION,		true	},
	{"Detect Evil",			&AFF_DETECT_EVIL,		true	},
	{"Detect Good",			&AFF_DETECT_GOOD,		true	},
	{"Detect Magic",		&AFF_DETECT_MAGIC,		true	},
	{"Major Physical",		&AFF_MAJOR_PHYSICAL,	true	},
	{"Protection from Cold",&AFF_PROTECT_COLD,		true	},
	{"Protection from Lightning",&AFF_PROTECT_LIGHTNING,	true},
	{"Minor Paralysis",		&AFF_MINOR_PARA,		true	},
	{"Hold",				&AFF_HOLD,				true	}, // major para
	{"Slowness",			&AFF_SLOWNESS,			true	},
	{"Major Globe",			&AFF_MAJOR_GLOBE,		true	},
	{"Protection from Gas", &AFF_PROTECT_GAS,		true	},
	{"Protection from Acid",&AFF_PROTECT_ACID,		true	},
	{"Poison",				&AFF_POISON,			true	},
	{"Soulshield",			&AFF_SOULSHIELD,		true	},
	{"Duergar Hide",		&AFF_DUERGAR_HIDE,		true	},
	{"Minor Invisibility",  &AFF_MINOR_INVIS,		true	},
	{"Vampiric Touch",		&AFF_VAMP_TOUCH,		true	},
	{"Stunned",				&AFF_STUNNED,			true	},
	{"Dropped Primary",		&AFF_DROPPED_PRIMARY,	false	},
	{"Dropped Secondary",	&AFF_DROPPED_SECOND,	false	},
	{"Fumbled Primary",		&AFF_FUMBLED_PRIMARY,	false	},
	{"CTFFLAG",				&AFF_CTFFLAG,			false	},
	{"Holding Breath",		&AFF_HOLDING_BREATH,	true	},
	{"Memorizing",			&AFF_MEMORIZING,		true	},
	{"Drowning",			&AFF_DROWNING,			true	},
	{"Pass Door",			&AFF_PASS_DOOR,			true	},
	{"Draining",			&AFF_DRAINING,			false	},
	{"Casting",				&AFF_CASTING,			false	},
	{"Scribing",			&AFF_SCRIBING,			false	},

	{"Tensors Disc",		&AFF_TENSORS_DISC,		false	},  // Unused DE bit
	{"Tracking",			&AFF_TRACKING,			true	},
	{"Singing",				&AFF_SINGING,			true	},
	{"Ectoplasmic Form",	&AFF_ECTOPLASMIC,		true	},
	{"Absorbing",			&AFF_ABSORBING,			false	},  // Unused DE bit
	{"Vampire Bite",		&AFF_VAMP_BITE,			false	},  // Unused DE bit
	{"Spirit Ward",			&AFF_SPIRIT_WARD,		true	},
	{"Greater Spirit Ward", &AFF_GREATER_SPIRIT_WARD,true	},
	{"Mastered",			&AFF_MASTERED,			false	},  // Unused DE bit - For control over summoned/called creatures
	{"Silver",				&AFF_SILVER,			false	},
	{"Plus One",			&AFF_PLUS_ONE,			true	},
	{"Plus Two",			&AFF_PLUS_TWO,			true	},
	{"Plus Three",			&AFF_PLUS_THREE,		true	},
	{"Plus Four",			&AFF_PLUS_FOUR,			true	},
	{"Plus Five",			&AFF_PLUS_FIVE,			true	},
	{"Enlarged",			&AFF_ENLARGED,			true	},
	{"Reduced",			    &AFF_REDUCED,			true	},
	{"Cover",				&AFF_COVER,				true	},
	{"Four Arms",			&AFF_FOUR_ARMS,			true	},
	{"Inertial Barrier",	&AFF_INERTIAL_BARRIER,	true	},
	{"Intellect Fortress",  &AFF_INTELLECT_FORTRESS,true	},
	{"Coldshield",			&AFF_COLDSHIELD,		true	},
	{"Conjured",			&AFF_CONJURED,			false	},  // Unused DE bit - For conjured creatures...
	{"Swimming",			&AFF_SWIMMING,			true	},
	{"Tower of Iron Will",  &AFF_TOWER_OF_IRON_WILL,true	},
	{"Underwater",			&AFF_UNDERWATER,		false	},  // Unused DE bit
	{"Blur",				&AFF_BLUR,				true	},
	{"Neckbiting",			&AFF_NECKBITING,		false	},  // Unused DE bit
	{"Elemental Form",		&AFF_ELEMENTAL_FORM,	true	},
	{"Pass Without Trace",  &AFF_PASS_WITHOUT_TRACE,true	},
	{"Paladin Aura",		&AFF_PALADIN_AURA,		false	},

	{"Looter",				&AFF_LOOTER,			false	},
	{"Plague",				&AFF_PLAGUE,			true	}, // diseased
	{"Sacking",				&AFF_SACKING,			false	},  // Unused DE bit
	{"Sense Follower",		&AFF_SENSE_FOLLOWER,	true	},
	{"Stornogs Spheres",	&AFF_STORNOG_SPHERES,	true	},  // Unused DE bit
	{"Greater Stornogs Spheres",&AFF_GREATER_SPHERES,true	},  // Unused DE bit
	{"Vampiric Form",		&AFF_VAMPIRE_FORM,		true	},  // Unused DE bit
	{"No Un-Morph",			&AFF_NO_UNMORPH,		true	},  // Unused DE bit
	{"Holy Sacrifice",		&AFF_HOLY_SACRIFICE,	true	},
	{"Battle Ecstasy",		&AFF_BATTLE_ECSTASY,	true	},
	{"Dazzle",				&AFF_DAZZLE,			true	},
	{"Dazzled",				&AFF_DAZZLED,			true	},
	{"Throat Crush",		&AFF_THROAT_CRUSH,		true	},
	{"Regeneration",		&AFF_REGENERATION,		true	},
	{"Bearhug",				&AFF_BEARHUG,			false	},
	{"Grappling",			&AFF_GRAPPLING,			false	},
	{"Grappled",			&AFF_GRAPPLED,			false	},
	{"Mage Flame",			&AFF_MAGE_FLAME,		true	},  // Unused DE bit
	{"No Immolate",			&AFF_NO_IMMOLATE,		true	},
	{"Multiclass",			&AFF_MULTICLASS,		false	},
	{"Detect Undead",		&AFF_DETECT_UNDEAD,		true	},
	{"Clarity",				&AFF_CLARITY,			true	},
	{"Major Paralysis",		&AFF_MAJOR_PARA,		true	},
	{"Ward Undead",			&AFF_WARD_UNDEAD,		true	},
	{"True Seeing",			&AFF_TRUE_SEEING,		true	},

	{"Is Fleeing",			&AFF_IS_FLEEING,		false	},
	{"Hunting",				&AFF_HUNTING,			true	},
	{"Biofeedback",			&AFF_BIOFEEDBACK,		true	},
	{"Famine",				&AFF_FAMINE,			true	},
	{"Mute",				&AFF_MUTE,				true	},
	{"Faerie Fire",			&AFF_FAERIE_FIRE,		true	},
	{"Sanctuary",			&AFF_SANCTUARY,			true	},
	{"Change Sex",			&AFF_CHANGE_SEX,		true	},
	{"Curse",				&AFF_CURSE,				true	},
	{"Detect Hidden",		&AFF_DETECT_HIDDEN,		true	},
	{"Polymorph",			&AFF_POLYMORPH,			true	},
	{"Comprehend Language", &AFF_COMP_LANG,			true	},
	{"Deny Earth",			&AFF_DENY_EARTH,		true	},
	{"Deny Air",			&AFF_DENY_AIR,			true	},
	{"Deny Fire",			&AFF_DENY_FIRE,			true	},
	{"Deny Water",			&AFF_DENY_WATER,		true	},
	{"Track",				&AFF_TRACK,				false	},
	{"Justice Tracker",		&AFF_JUSTICE_TRACKER,	true	},
	{"Layhands Timer",		&AFF_LAYHANDS_TIMER,	false	},
	{"Elemental Sight",		&AFF_ELEM_SIGHT,		true	},
	{"BLOCKEDTMP",			&AFF_BLOCKEDTMP,		false	},
	{"Misdirection",		&AFF_MISDIRECTION,		true	},
	{"Vacancy",				&AFF_VACANCY,			true	},
	{"Change Self",			&AFF_CHANGE_SELF,		true	},
	{"Prowess",				&AFF_PROWESS,			true	},
	{"Summon Mount Timer",  &AFF_SUMMON_MOUNT_TIMER,false	},
	{"Incompetence",		&AFF_INCOMPETENCE,		true	},
	{"Climbing",			&AFF_CLIMBING,			true	},
	{"Undead Mute",			&AFF_UNDEAD_MUTE,		true	},
	{"Coordination",		&AFF_COORDINATION,		true	},
	{"Charm of the Otter",  &AFF_CHARM_OTTER,		false	},

	{"Endurance",			&AFF_ENDURANCE,			true	},
	{"Fortitude",			&AFF_FORTITUDE,			true	},
	{"Insight",				&AFF_INSIGHT,			true	},
	{"Might",				&AFF_MIGHT,				true	},
	{"Savvy",				&AFF_SAVVY,				true	},
	{"Wrist Locked 1",		&AFF_WRISTLOCKED1,		false	},
	{"Wrist Locked 2",		&AFF_WRISTLOCKED2,		false	},
	{"Wrist Locking",		&AFF_WRISTLOCKING,		false	},
	{"Protect Undead",		&AFF_PROTECT_UNDEAD,	true	},
	{"Chanting",			&AFF_CHANTING,			false	},
	{"Simulacrum",			&AFF_SIMULACRUM,		true	},
	{"Approval",			&AFF_APPROVAL,			false	},
	{"Listening",			&AFF_LISTENING,			false	},
	{"Invader Tracker",		&AFF_INVADER_TRACKER,	false	},
	{"Disguise",			&AFF_DISGUISE,			true	},
	{"Deaf",				&AFF_DEAF,				true	},
	{"Hellfire",			&AFF_HELLFIRE,			true	},
	{"Blur Timer",			&AFF_BLURTIMER,			false	},
	{"Consuming",			&AFF_CONSUMING,			false	},
	{"Drainee",				&AFF_DRAINEE,			false	},
	{"Tower of Iron Will",  &AFF_TOWER_IRON_WILL,	true	},
	{"Fluxed",				&AFF_FLUXED,			false	},
	{"HP Stop",				&AFF_HP_STOP,			true	},
	{"Mana Stop",			&AFF_MANA_STOP,			true	},
	{"Move Stop",			&AFF_MOVE_STOP,			true	},
};

inline int MaxAffFlags() {
	return sizeof(mob_aff_flags)/sizeof(MobAffectData);
}

DlgSelectAff::DlgSelectAff(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSelectAff::IDD, pParent)
{
	type = NONE;

	for(int i = 0; i < NUM_AFFECT_VECTORS; i++)
		aff_flags[i] = 0;


	//{{AFX_DATA_INIT(DlgSelectAff)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSelectAff::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSelectAff)
	DDX_Control(pDX, IDC_AFF_LIST, aff_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSelectAff, CDialog)
	//{{AFX_MSG_MAP(DlgSelectAff)
	ON_NOTIFY(NM_CLICK, IDC_AFF_LIST, OnClickAffList)
	ON_BN_CLICKED(IDC_EDIT_BITS, OnEditBits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSelectAff message handlers

void DlgSelectAff::OnOK() 
{
	int i;
	
	for(i = 0; i < NUM_AFFECT_VECTORS; i++)
	{
		switch(type)
		{
		case MOBILE:
			mob->affected_by[i] = aff_flags[i];
			break;
		case OBJECT:
			obj->affected_by[i] = aff_flags[i];
			break;
		}
	}

	CDialog::OnOK();
}

BOOL DlgSelectAff::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	CString str;
	int i, x = 0;
	
	for(i = 0; i < NUM_AFFECT_VECTORS; i++)
	{
		switch(type)
		{
		case MOBILE:
			aff_flags[i] = mob->affected_by[i];
			break;
		case OBJECT:
			aff_flags[i] = obj->affected_by[i];
			break;
		}
	}

	DWORD dwStyle = ::SendMessage(aff_list, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(aff_list, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	aff_list.GetClientRect(rect);
	aff_list.InsertColumn(0, "Affect", LVCFMT_LEFT, rect.Width()/5);
	aff_list.InsertColumn(1, "Group", LVCFMT_LEFT, rect.Width()/5);
	aff_list.InsertColumn(2, "Bit", LVCFMT_LEFT, rect.Width()/5);
	aff_list.InsertColumn(3, "Total", LVCFMT_LEFT, rect.Width()/5);
	aff_list.InsertColumn(4, "Percent", LVCFMT_LEFT, rect.Width()/5);

	for(i = 0; i < MaxAffFlags(); i++) 
	{
		if(mob_aff_flags[i].in_use) 
		{
			aff_list.InsertItem(x, mob_aff_flags[i].name);
			
			str.Format("%d", mob_aff_flags[i].bv->group);
			aff_list.SetItem(x, 1, LVIF_TEXT, str, 1, 0, 0, 0);

			str.Format("%d", mob_aff_flags[i].bv->vector);
			aff_list.SetItem(x, 2, LVIF_TEXT, str, 1, 0, 0, 0);

			switch(type)
			{
			case MOBILE:
				str.Format("%d", GetAffCountPerMob(*mob_aff_flags[i].bv));
				aff_list.SetItem(x, 3, LVIF_TEXT, str, 1, 0, 0, 0);

				str.Format("%.2f", GetAffPercentPerMob(*mob_aff_flags[i].bv));
				aff_list.SetItem(x, 4, LVIF_TEXT, str, 1, 0, 0, 0);
				break;
			case OBJECT:
				str.Format("%d", GetAffCountPerObj(*mob_aff_flags[i].bv));
				aff_list.SetItem(x, 3, LVIF_TEXT, str, 1, 0, 0, 0);

				str.Format("%.2f", GetAffPercentPerObj(*mob_aff_flags[i].bv));
				aff_list.SetItem(x, 4, LVIF_TEXT, str, 1, 0, 0, 0);
				break;
			}

			aff_list.SetItemData(x, i);

			if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
				aff_list.SetItemState(x, LVIS_DROPHILITED | LVIS_SELECTED, LVIS_DROPHILITED | LVIS_SELECTED);

			x++;		
		}
	}
	
	aff_list.SetFocus();

	return TRUE; 
}

void DlgSelectAff::OnClickAffList(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	int i;

	i = aff_list.GetItemData(pNMListView->iItem);

	if(IS_SET(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector))
	{
		aff_list.SetItemState(pNMListView->iItem, 0, LVIS_DROPHILITED|LVIS_SELECTED);
		aff_list.SetCheck(pNMListView->iItem, false);
		REMOVE_BIT(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector);
	}
	else
	{
		aff_list.SetItemState(pNMListView->iItem, LVIS_FOCUSED|LVIS_DROPHILITED | LVIS_SELECTED, LVIS_FOCUSED|LVIS_DROPHILITED | LVIS_SELECTED);
		SET_BIT(aff_flags[mob_aff_flags[i].bv->group], mob_aff_flags[i].bv->vector);
		aff_list.SetCheck(pNMListView->iItem);
	}
}

void DlgSelectAff::OnEditBits() 
{
	EditAffBits dlg;
	int x;

	for(int i = 0; i < NUM_AFFECT_VECTORS; i++)
		dlg.affs[i] = aff_flags[i];

	dlg.DoModal();

	for(int i = 0; i < NUM_AFFECT_VECTORS; i++)
		aff_flags[i] = dlg.affs[i];

	for(int i =0; i < aff_list.GetItemCount(); i++)
	{
		x = aff_list.GetItemData(i);

		if(!IS_SET(aff_flags[mob_aff_flags[x].bv->group], mob_aff_flags[x].bv->vector))
		{
			aff_list.SetItemState(i, 0, LVIS_DROPHILITED|LVIS_SELECTED);
			aff_list.SetCheck(i, false);
			REMOVE_BIT(aff_flags[mob_aff_flags[x].bv->group], mob_aff_flags[x].bv->vector);
		}
		else
		{
			aff_list.SetItemState(i, LVIS_FOCUSED|LVIS_DROPHILITED | LVIS_SELECTED, LVIS_FOCUSED|LVIS_DROPHILITED | LVIS_SELECTED);
			SET_BIT(aff_flags[mob_aff_flags[x].bv->group], mob_aff_flags[x].bv->vector);
			aff_list.SetCheck(i);
		}
	}

	UpdateData(false);
}
