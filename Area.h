#ifndef _AREAS_H_
#define _AREAS_H_ 1

#include "Bits.h"
#include "Utils.h"
#include "Progs.h"

// Justice types
#define JUSTICE_GOOD         1 // crimes illegal, prot evil
#define JUSTICE_EVIL         2 // crimes legal, prot goodie
#define JUSTICE_NEUTRAL      3 // crimes illegal, all welcome
#define JUSTICE_NEUT_CLOSED  4 // crimes illegal, prot goodie and evil
#define JUSTICE_LAWFUL_EVIL  5 // crimes illegal, protected from goodies
#define JUSTICE_CHAOTIC_GOOD 6 // crimes legal, protected from evils
#define JUSTICE_CHAOTIC_NEUT 7 // crimes legal, prot goodie and evil
#define JUSTICE_CLOSED_GOOD  8 // crimes illegal, prot evil AND neutral
#define JUSTICE_CLOSED_EVIL  9 // crimes legal, prot good AND neutral

//Resets
#define ZONE_NO_RESET       0
#define ZONE_RESET_EMPTY    1
#define ZONE_RESET_ALWAYS   2
#define MAX_RESET			3

#define ZONE_SILENT           BV00  // entire zone is silent (possibly works)
#define ZONE_SAFE             BV01  // entire zone is safe (probably works)
#define ZONE_HOMETOWN         BV02  // zone is a hometown
#define ZONE_NO_TELEPORT      BV03  // can't teleport around the zone

class area_data
{
public:
	static char			class_name[];
	static int			class_index;
	static area_data	*area;

public:
    //ANSI_MAP *          ansimap;
    CString				name;
    CString				path;
    int                 defender; // vnum of defending mobs for invasion
    int                 defender_num; // number of defenders that spawn
    int                 barracks; // vnum of room where guards spawn, if not given guards will spawn in judge room
    int                 judge; // vnum of room in which judge presides
    int                 jail; // vnum of room in which jail is
    int                 squads; // number of guard squads that cna be dispatched
    int                 justice;
    int                 vnum;			/* OLC Area vnum           */
    int                 area_flags;		/* OLC                     */
    int                 llv;
    int                 ulv;
    CString             author;
    CString             resetmsg;
    int                 resetmode;
    int                 llifespan;
    int                 ulifespan;
	int					version;

	int security, lvnum, uvnum, clan_id, nodim, recall;
	CString builders;

	int dummy[6];
	CString dummy_str[2];

	ProgList progs;

public:
	area_data() : name("Unnamed"), path("Unnamed"), defender(0), 
				  defender_num(0), barracks(0), judge(0), jail(0), 
				  squads(0), justice(0), vnum(1), area_flags(0), 
				  llv(1), ulv(65), author("Unknown"), 
				  resetmsg("You hear some strange noises."),
				  resetmode(0), llifespan(0), ulifespan(0), 
				  security(0), lvnum(0), uvnum(0), clan_id(0), 
				  nodim(0), recall(0){ };

	~area_data() { progs.RemoveAll(); };

	int ReadArea(FILE *fp);
};



#endif