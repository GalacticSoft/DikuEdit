#ifndef _UTILS_H_
#define _UTILS_H_

enum {
	AREA_DATA,
	ROOM_DATA,
	MOB_DATA,
	OBJECT_DATA,
	MOB_INDEX,
	OBJ_INDEX,
	PEOPLE,		//used for tree list bitmaps
	CONTENTS,	//used for tree list bitmaps
	ROOM_PARENT,//used for tree list bitmaps
	OBJ_PARENT,	//used for tree list bitmaps
	MOB_PARENT,	//used for tree list bitmaps
	ROOM_FLAGS,
	WIN_DE_DLG,
	EXIT_DATA,
	EXTRA_DESC,
};

enum { ROOM, OBJECT, MOBILE, KEY, MOUNT, NONE, EXIT, AREA };

bool str_prefix(CString str1, CString str2);

CString StripAnsiChars(CString pString);
int GetValidVnum(int type);
void StripAnsiChars(CString &pString, vector<COLORREF>& colors);
CString ColorRefToAnsi(COLORREF ref);

CString GetArg(CString &arg);

bool ObjIsSlot(object_data *ob, int slot); 
bool RaceHasSlot(int race, int slot);
int GetDir(CString exit);

mob_data*	GetMobByVnum(int vnum);
int number_argument(CString &arg);

bool IsName(CString names, CString name);
bool IsName(mob_data *mob, CString &name);
bool IsName(object_data *obj, CString &name);
bool IsName(room_data *room, CString &name);

mob_data	*GetMobByName(CString &name);
object_data *GetObjByName(CString &name);
room_data	*GetRoomByName(CString &name);

mob_data	*GetMob(CString &str);
object_data *GetObj(CString &str);
room_data	*GetRoom(CString &str);

mob_index *GetMobInRoomByName(room_data *room, CString &arg);
mob_index *GetMobInRoomByVnum(room_data *room, int vnum);
mob_index *GetMobInRoom(room_data *room, CString arg);

obj_index *GetObjInRoomByName(room_data *room, CString &arg);
obj_index *GetObjInRoomByVnum(room_data *room, int vnum);
obj_index *GetObjInRoom(room_data *room, CString arg);

int GetArgType(CString str);

float	GetAvgMobLevel();

int		GetLoadedMobCount();
int		GetLoadedObjCount();

int		GetMobCount();
int		GetRoomCount();
int		GetObjCount();
int		GetShopCount();
int		GetQuestCount();

float	GetAvgMobsPerRoom();
float	GetAvgObjsPerRoom();

int		GetAggroGoodCount();
float   GetAggroGoodPercent();

int		GetAggroEvilCount();
float   GetAggroEvilPercent();

int		GetAggroNeutCount();
float   GetAggroNeutPercent();

int		GetAggroAllCount();
float   GetAggroAllPercent();

int     GetNonAggroCount();
float   GetNonAggroPercent();

int		GetAggroGoodRaceCount();
float   GetAggroGoodRacePercent();

int     GetAggroEvilRaceCount();
float   GetAggroEvilRacePercent();

int		GetRaceCount(int race);
int		GetClassCount(int c_class);

float	GetRacePercent(int race);
float	GetClassPercent(int c_class);

int		GetAvgMobSize();

float   GetObjTypePercent(int type);
int		GetObjTypeCount(int type);

int     GetRoomTerrainCount(int type);
float   GetRoomTerrainPercent(int type);

float	GetAvgMobAlign();

int		GetTotalApply(int apply);
float   GetAvgApply(int apply);

int		GetObjMaterialCount(int mat);
float   GetObjMaterialPercent(int mat);

int     GetObjCraftCount(int craft);
float   GetObjCraftPercent(int craft);

int GetAffCountPerMob(const BITVECT_DATA& bv);
float GetAffPercentPerMob(const BITVECT_DATA& bv);

int GetAffCountPerObj(const BITVECT_DATA& bv);
float GetAffPercentPerObj(const BITVECT_DATA& bv);

namespace MenuFunctions
{
	bool AddMenuItem(HMENU hTargetMenu, const CString& itemText, UINT itemID, void *data);
	bool AddMenuItem(HMENU hTargetMenu, const CString& itemText, UINT itemID, int* pInsertPositions);
	int CalculateMenuHeight(HMENU hMenu);
	int CalculateMenuWidth(HMENU hMenu);
};

#endif