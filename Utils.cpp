#include "StdAfx.h"

CString CountAnsiChars(CString pString)
{
	int i;
	int count=0;
	CString str;

	for(i = 0; i < pString.GetLength();i++)
	{	
		if(pString[i] == '&') {
			count++;
			i++;
			if(pString[i] == '+') {
				count+=2;
				i+=2;
			}
			else if(pString[i] == 'n' || pString[i] == 'N') {
				count++;
				i++;
			}
		}
		
		/*while(i < strlen(pString)) {
			if(pString[i] != '&') {
				str += pString[i];
				i++;
			} else {
				i--;
				break;
			}
		}*/
	}
	
	str = " ";

	for(i = 1; i < count; i++)
		str += " ";

	return str;
}
//will remove all &+x and &n from a string
CString StripAnsiChars(CString pString)
{
	CString str;
	int i;
	
	for(i = 0; i < pString.GetLength();i++)
	{	
		if(pString[i] == '&') {
			i++;
			if(pString[i] == '+') {
				i+=2;
			}
			else if(pString[i] == 'n' || pString[i] == 'N') {
				i++;
			}
		}
		
		while(i < pString.GetLength()) {
			if(pString[i] != '&') {
				str += pString[i];
				i++;
			} else {
				i--;
				break;
			}
		}
		
		if(i >= pString.GetLength())
			break;
	}
	
	return str;
}

//used for the colorizer control
void StripAnsiChars(CString &pString, vector<COLORREF>& colors)
{
	CString str;
	vector<COLORREF> col;
	int i;
	colors.resize(pString.GetLength());

	for(i = 0; i < pString.GetLength();i++)
	{
		
		if(pString[i] == '&') {
			i++;
			if(pString[i] == '+') {
				i+=2;
			}
			else if(pString[i] == 'n' || pString[i] == 'N') {
				i++;
			}
		}
		
		while(i < pString.GetLength()) {
			if(pString[i] != '&') {
				str += pString[i];
				col.push_back(colors[i]);
				i++;
			} else {
				i--;
				break;
			}
		}
		
		if(i >= pString.GetLength())
			break;
	}
	
	pString = str;
	colors = col;
	colors.resize(pString.GetLength());

}

int GetValidVnum(int type) 
{
	int vnum = -1;

	switch (type) {
		case ROOM: {
			vnum = room_data::room_hi_vnum;

			while(GetRoomByVnum(vnum)) {vnum++;}
	
			room_data::room_hi_vnum = vnum;
			break;
		}
		case OBJECT:{
			vnum = object_data::high_obj_vnum;

			while(GetObjByVnum(vnum)) { vnum++; object_data::high_obj_vnum++; }
	
			break;
		}
		case MOBILE:{
			vnum = mob_data::high_mob_vnum;

			while(GetMobByVnum(vnum)) { vnum++; mob_data::high_mob_vnum++; }
	
			break;
		}
	}

	return vnum;
}

CString ColorRefToAnsi(COLORREF ref)
{
	switch(ref) {
		case red:			return "&+R";
		case darkred:		return "&+r";
		case blue:			return "&+B";
		case darkblue:		return "&+b";
		case white:			return "&+W";
		case lightgrey:		return "&+w";
		case gray:			return "&+L";
		case green:			return "&+g";
		case lawngreen:		return "&+G";
		case darkmagenta:	return "&+m";
		case magenta:		return "&+M";
		case darkcyan:		return "&+c";
		case cyan:			return "&+C";
		case peru:			return "&+y";
		case yellow:		return "&+Y";
		default:			return "&n";
	}
}

CString GetArg(CString &str)
{
	CString arg;
	int num;

	if(str.IsEmpty())
		return "\0";

	num = str.Find(' ', 0);
	
	if(num > 0) {
		arg = str.Left(num);
		str = str.Right(str.GetLength() - (num+1));
	} 
	else 
	{
		arg = str;
		str = "\0";
	}

	return arg;

}

bool RaceHasSlot(int race, int slot)
{
	switch(race) {
	case RACE_THRIKREEN:
		switch(slot){
		case WEAR_FEET:
		case WEAR_LEGS:
		case WEAR_FINGER_L:
		case WEAR_FINGER_R:
		case WEAR_NOSE:
		case WEAR_HORNS:
		case WEAR_TAIL:
		case WEAR_EAR_L:
		case WEAR_EAR_R:
		case WEAR_HORSE_BODY:
			return false;
		default:
			return true;
		}
		break;
	case RACE_MINOTAUR:
		switch(slot) {
		case WEAR_FEET:
		case WEAR_LEGS:
		case WEAR_HEAD:
		case WEAR_HAND_3:		
		case WEAR_HAND_4:
		case WEAR_LOWER_ARMS:
		case WEAR_LOWER_HANDS:  
		case WEAR_LWRIST_L:
		case WEAR_LWRIST_R:
		case WEAR_HORSE_BODY:
			return false;
		default:
			return true;
		}
		break;
	case RACE_CENTAUR:
		switch(slot) {
		case WEAR_FEET:
		case WEAR_LEGS:
		case WEAR_HAND_3:		
		case WEAR_HAND_4:
		case WEAR_LOWER_ARMS:
		case WEAR_LOWER_HANDS:  
		case WEAR_LWRIST_L:
		case WEAR_LWRIST_R:
		case WEAR_HORNS:
		case WEAR_WAIST:
			return false;
		default:
			return true;
		}
		break;
	default:
		switch(slot) {
		case WEAR_HAND_3:		
		case WEAR_HAND_4:
		case WEAR_LOWER_ARMS:
		case WEAR_LOWER_HANDS:  
		case WEAR_LWRIST_L:
		case WEAR_LWRIST_R:
		case WEAR_HORNS:
		case WEAR_TAIL:
		case WEAR_HORSE_BODY:
		case WEAR_NOSE:
			return false;
		default:
			return true;
		}
		break;
	}
	
	return true;
}
	
bool ObjIsSlot(object_data *ob, int slot) 
{
	switch(slot) {
	case WEAR_FINGER_L:
	case WEAR_FINGER_R:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_FINGER))
			return true;
		break;
	case WEAR_NECK_1:
	case WEAR_NECK_2:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_NECK))
			return true;
		break;
	case  WEAR_BODY:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_BODY))
			return true;
		break;
	case WEAR_HEAD:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_HEAD))
			return true;
		break;
	case WEAR_LEGS:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_LEGS))
			return true;
		break;
	case WEAR_FEET:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_FEET))
			return true;
		break;
	case WEAR_HANDS:
	case WEAR_LOWER_HANDS:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_HANDS))
			return true;
		break;
	case WEAR_ARMS:
	case WEAR_LOWER_ARMS:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_ARMS))
			return true;
		break;
	case WEAR_ABOUT:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_ABOUT))
			return true;
		break;
	case WEAR_WAIST:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_WAIST))
			return true;
		break;
	case WEAR_WRIST_L:
	case WEAR_WRIST_R:	
	case WEAR_LWRIST_L:
	case WEAR_LWRIST_R:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_WRIST))
			return true;
		break;
	case WEAR_HAND:
	case WEAR_HAND_2:
	case WEAR_HAND_3:
	case WEAR_HAND_4:
		if(IS_SET(ob->wear_flags, ITEM_HOLD) || 
		   IS_SET(ob->wear_flags, ITEM_WIELD)|| 
		   IS_SET(ob->wear_flags, ITEM_WEAR_SHIELD))
			return true;
		break;
	case WEAR_EYES:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_EYES))
			return true;
		break;
	case WEAR_FACE:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_FACE))
			return true;
		break;
	case WEAR_EAR_L:
	case WEAR_EAR_R:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_EAR))
			return true;
		break;
	case WEAR_BADGE:
		if(IS_SET(ob->wear_flags, ITEM_BADGE))
			return true;
		break;
	case WEAR_ONBACK:
		if(IS_SET(ob->wear_flags, ITEM_WEAR_ONBACK))
			return true;
		break;
	case WEAR_BELT_1:
	case WEAR_BELT_2:
	case WEAR_BELT_3:
		if(IS_SET(ob->wear_flags, ITEM_ATTACH_BELT))
			return true;
		break;
	case WEAR_QUIVER:
		if(IS_SET(ob->wear_flags, ITEM_QUIVER))
			return true;
		break;
	case WEAR_TAIL:
		if(IS_SET(ob->wear_flags, ITEM_TAIL))
			return true;
		break;
	case WEAR_HORSE_BODY:
		if(IS_SET(ob->wear_flags, ITEM_HORSE_BODY))
			return true;
		break;
	case WEAR_HORNS:
		if(IS_SET(ob->wear_flags, ITEM_HORNS))
			return true;
		break;
	case WEAR_NOSE:
		if(IS_SET(ob->wear_flags, ITEM_NOSE))
			return true;
		break;
	default:
		return false;
	}

	return false;
}

int GetDir(CString exit)
{
	exit.MakeLower();
		
	for(int i = DIR_NORTH; i < MAX_DIR; i++)
	{
		if(dir_names[i] == exit || short_dir_names[i] == exit)
			return i;
	}

	return -1;
}

bool IsName(CString names, CString name)
{
	CString str;
	
	if(names.Find(name) > -1)
		return true;

	return false;
}

bool IsName(mob_data *mob, CString &name)
{
	return mob->IsName(name);
}

mob_data* GetMobByVnum(int vnum)
{
	mob_data *mob;

	if(vnum == 0)
		return NULL;

	for(mob = mob_data::first_mob; mob; mob = mob->next)
		if(mob->vnum == vnum)
			return mob;

	return NULL;
}

mob_data * GetMobByName(CString &name)
{
	mob_data *tmp;

	for(tmp = mob_data::first_mob; tmp; tmp = tmp->next)
	{
		if(IsName(tmp, name))
			return tmp;
	}

	return NULL;
}

mob_data *GetMob(CString &str)
{
	int vnum;
	mob_data *mob = NULL;

	mob = GetMobByName(str);
		
	if(!mob)
	{	
		vnum = atoi(str);
		mob = GetMobByVnum(vnum);
	}

	return mob;
}

bool IsName(object_data *obj, CString &name)
{
	return IsName(obj->name, name);
}

object_data * GetObjByName(CString &name)
{
	object_data *tmp;

	for(tmp = object_data::obj_head; tmp; tmp = tmp->next)
	{
		if(IsName(tmp, name))
			return tmp;
	}

	return NULL;
}

object_data *GetObj(CString &str)
{
	int vnum;
	object_data *obj = NULL;

	obj = GetObjByName(str);
		
	if(!obj)
	{	
		vnum = atoi(str);
		obj = GetObjByVnum(vnum);
	}

	return obj;
}

bool IsName(room_data *room, CString &name)
{
	return IsName(room->name, name);
}

room_data * GetRoomByName(CString &name)
{
	room_data *tmp;

	for(tmp = room_data::room_list; tmp; tmp = tmp->next)
	{
		if(IsName(tmp, name))
			return tmp;
	}

	return NULL;
}

room_data *GetRoom(CString &str)
{
	int vnum;
	room_data *room = NULL;

	room = GetRoomByName(str);
		
	if(!room)
	{	
		vnum = atoi(str);
		room = GetRoomByVnum(vnum);
	}

	return room;
}

int number_argument(CString &arg)
{
	int pos;
	CString count;
	int i = 1;

	pos = arg.Find(".", 0);

	if(pos > -1)
	{
		count = arg.Left(pos);
		arg = arg.Right(pos+1);
		i = atoi(count);	
	}
	
	return i;
}

mob_index *GetMobInRoomByName(room_data *room, CString &arg)
{
	int count, i;
	mob_index *mob;

	if(room)
	{
		count = number_argument(arg);
		
		for(i = 1, mob = room->people; mob; mob = mob->next, i++)
		{
			if(i < count)
				continue;

			if(mob->mob)
			{
				if(mob->mob->name.Find(arg) > -1)
					return mob;
			}
		}
	}

	return NULL;
}

mob_index *GetMobInRoomByVnum(room_data *room, int vnum)
{
	if(room)
		return room->GetMobInRoom(vnum);

	return NULL;
}

mob_index *GetMobInRoom(room_data *room, CString arg)
{
	mob_index *mob = NULL;

	mob = GetMobInRoomByName(room, arg);

	if(!mob)
		mob = GetMobInRoomByVnum(room, atoi(arg));

	return mob;
}

obj_index *GetObjInRoomByName(room_data *room, CString &arg)
{
	int count, i;
	obj_index *obj;

	if(room)
	{
		count = number_argument(arg);
		
		for(i = 1, obj = room->contents; obj; obj = obj->next, i++)
		{
			if(i < count)
				continue;

			if(obj->obj)
			{
				if(obj->obj->name.Find(arg) > -1)
					return obj;
			}
		}
	}

	return NULL;
}

obj_index *GetObjInRoomByVnum(room_data *room, int vnum)
{
	if(room)
		return room->GetObjInRoom(vnum);

	return NULL;
}

obj_index *GetObjInRoom(room_data *room, CString arg)
{
	obj_index *obj = NULL;

	obj = GetObjInRoomByName(room, arg);

	if(!obj)
		obj = GetObjInRoomByVnum(room, atoi(arg));

	return obj;
}


float GetAvgMobLevel()
{
	room_data *room; 
	mob_index *mob;
	float col = 0;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				col += mob->mob->level;
			}
		}
	}

	if(GetLoadedMobCount() > 0)
		return col/(float)GetLoadedMobCount();

	return 0.0;
}

int	GetMobCount(){
	return mob_count;
}

int	GetRoomCount(){
	return room_count;
}

int	GetObjCount(){
	return obj_count;
}

float GetAvgMobsPerRoom()
{
	if(GetRoomCount() > 0)
		return ((float)GetLoadedMobCount()/(float)GetRoomCount());

	return 0.0;
}

float GetAvgObjsPerRoom()
{
	if(GetRoomCount() > 0)
		return ((float)GetLoadedObjCount()/(float)GetRoomCount());

	return 0.0;
}

int	GetShopCount() {
	return shop_count;
}

int	GetQuestCount() {
	return quest_count;
}

int	GetLoadedMobCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			count++;
		}
	}
	
	return count;
}

int	GetLoadedObjCount()
{
	int count = 0;
	obj_index *obj;
	room_data *room;
	mob_index *mob;
	
	for(room = room_data::room_list; room; room = room->next)
	{
		for(obj = room->contents; obj; obj = obj->next)
		{
			if(obj->obj)
				count++;
		}
		
		for(mob = room->people; mob; mob = mob->next)
		{
			for(obj = mob->inventory; obj; obj = obj->next)
			{
				if(obj->obj)
					count++;
			}
			
			for(int i = 0; i < MAX_WEAR; i++)
			{
				if(mob->eq[i] != NULL)
				{
					if(mob->eq[i]->obj)
						count++;
				}
			}
		}
	}
	
	return count;
}

int	GetAggroGoodCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGROGOOD))
					count++;
			}
		}
	}

	return count;
}

float GetAggroGoodPercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroGoodCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetAggroEvilCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGROEVIL))
					count++;
			}
		}
	}

	return count;
}

float GetAggroEvilPercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroEvilCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetAggroNeutCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGRONEUT))
					count++;
			}
		}
	}

	return count;
}

float GetAggroNeutPercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroNeutCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetAggroAllCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGRESSIVE))
					count++;
			}
		}
	}

	return count;
}

float GetAggroAllPercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroAllCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetRaceCount(int race)
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(mob->mob->race  == race)
					count++;
			}
		}
	}

	return count;
}

int	GetClassCount(int c_class)
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(mob->mob->c_class  == c_class)
					count++;
			}
		}
	}

	return count;
}

float GetRacePercent(int race)
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetRaceCount(race)/(float)GetLoadedMobCount());

	return 0.0;
}


float GetClassPercent(int c_class)
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetClassCount(c_class)/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetAvgMobSize()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				count += mob->mob->size;
			}
		}
	}

	if(GetLoadedMobCount() > 0)
		return count/GetLoadedMobCount();

	return 0;
}

float GetObjTypePercent(int type)
{
	if(GetLoadedObjCount() > 0)
		return 100.0 * ((float)GetObjTypeCount(type)/(float)GetLoadedObjCount());

	return 0.0;
}

int	GetObjTypeCount(int type)
{
	int count = 0;
	obj_index *obj;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(obj = room->contents; obj; obj = obj->next)
		{
			if(obj->obj)
			{
				if(obj->obj->item_type == type)
					count++;
			}
		}
		
		for(mob = room->people; mob; mob = mob->next)
		{
			for(obj = mob->inventory; obj; obj = obj->next)
			{
				if(obj->obj)
				{
					if(obj->obj->item_type == type)
						count++;
				}
			}
			
			for(int i = 0; i < MAX_WEAR; i++)
			{
				if(mob->eq[i] != NULL)
				{
					if(mob->eq[i]->obj)
					{
						if(mob->eq[i]->obj->item_type == type)
							count++;
					}
				}
			}
		}
	}
	
	return count;
}

int GetRoomTerrainCount(int type)
{
	room_data *room;
	int count = 0;

	for(room = room_data::room_list; room; room = room->next)
	{
		if(room->sector_type == type)
			count++;
	}

	return count;
}

float GetRoomTerrainPercent(int type)
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetRoomTerrainCount(type)/(float)GetRoomCount());

	return 0.0;
}

float GetAvgMobAlign()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
				count += mob->mob->alignment;
		}
	}
	
	if(GetLoadedMobCount() > 0)
		return ((float)count/(float)GetLoadedMobCount());

	return 0.0;
}


int GetAggroGoodRaceCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGROGOODRACE))
					count++;
			}
		}
	}

	return count;
}

float GetAggroGoodRacePercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroGoodRaceCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int GetAggroEvilRaceCount(){
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(IS_SET(mob->mob->act, ACT_AGGROEVILRACE))
					count++;
			}
		}
	}

	return count;
}

float GetAggroEvilRacePercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetAggroEvilRaceCount()/(float)GetLoadedMobCount());
	
	return 0.0;
}

int GetNonAggroCount()
{
	int count = 0;
	room_data *room;
	mob_index *mob;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(!IS_SET(mob->mob->act, ACT_AGGROEVILRACE) && !IS_SET(mob->mob->act, ACT_AGGROEVIL)
					&& !IS_SET(mob->mob->act, ACT_AGGROGOOD) && !IS_SET(mob->mob->act, ACT_AGGROGOODRACE)
					&& !IS_SET(mob->mob->act, ACT_AGGRONEUT) && !IS_SET(mob->mob->act, ACT_AGGRESSIVE))
					count++;
			}
		}
	}

	return count;
}

float GetNonAggroPercent()
{
	if(GetLoadedMobCount() > 0)
		return 100.0 * ((float)GetNonAggroCount()/(float)GetLoadedMobCount());

	return 0.0;
}

int	GetTotalApply(int apply)
{
	obj_index *obj;
	int count = 0;

	room_data *room;
	mob_index *mob;
	
	for(room = room_data::room_list; room; room = room->next)
	{
		for(obj = room->contents; obj; obj = obj->next)
		{
			if(obj->obj)
			{
				if(obj->obj->applies[0].loc == apply)
					count += obj->obj->applies[0].value;

				if(obj->obj->applies[1].loc == apply)
					count += obj->obj->applies[1].value;
			}
		}
		
		for(mob = room->people; mob; mob = mob->next)
		{
			for(obj = mob->inventory; obj; obj = obj->next)
			{
				if(obj->obj)
				{
					if(obj->obj->applies[0].loc == apply)
						count += obj->obj->applies[0].value;

					if(obj->obj->applies[1].loc == apply)
						count += obj->obj->applies[1].value;
				}
			}
			
			for(int i = 0; i < MAX_WEAR; i++)
			{
				if(mob->eq[i] != NULL)
				{
					if(mob->eq[i]->obj)
					{
						if(mob->eq[i]->obj->applies[0].loc == apply)
							count += mob->eq[i]->obj->applies[0].value;

						if(mob->eq[i]->obj->applies[1].loc == apply)
							count += mob->eq[i]->obj->applies[1].value;
					}
				}
			}
		}
	}

	return count;
}

float GetAvgApply(int apply)
{
	if(GetLoadedObjCount() > 0)
		return ((float)GetTotalApply(apply)/(float)GetLoadedObjCount());
	
	return 0.0;
}

int	GetObjMaterialCount(int mat)
{
	obj_index *obj;
	int count = 0;

	for(obj = obj_index::o_ind_head; obj; obj = obj->n_list)
	{
		if(obj->obj)
		{
			if(obj->obj->material == mat)
				count++;
		}
	}

	return count;
}

float GetObjMaterialPercent(int mat)
{
	if(GetLoadedObjCount() > 0)
		return 100.0 * ((float)GetObjMaterialCount(mat)/(float)GetLoadedObjCount());

	return 0.0;
}

int GetObjCraftCount(int craft)
{
	obj_index *obj;
	int count = 0;

	for(obj = obj_index::o_ind_head; obj; obj = obj->n_list)
	{
		if(obj->obj)
		{
			if(obj->obj->craftsmanship == craft)
				count++;
		}
	}

	return count;
}

float GetObjCraftPercent(int craft)
{
	if(GetLoadedObjCount() > 0)
		return 100.0 * ((float)GetObjCraftCount(craft)/(float)GetLoadedObjCount());

	return 0.0;
}

int GetAffCountPerMob(const BITVECT_DATA& bv)
{
	room_data *room;
	mob_index *mob;
	int count = 0;

	for(room = room_data::room_list; room; room = room->next)
	{
		for(mob = room->people; mob; mob = mob->next)
		{
			if(mob->mob)
			{
				if(mob->mob->AffIsSet(bv))
					count++;
			}
		}
	}

	return count;
}

float GetAffPercentPerMob(const BITVECT_DATA& bv)
{
	if(GetLoadedObjCount() > 0)
		return 100.0 * ((float)GetAffCountPerMob(bv)/(float)GetLoadedMobCount());

	return 0.0;
}

int GetAffCountPerObj(const BITVECT_DATA& bv)
{
	obj_index *obj;
	int count = 0;

	for(obj = obj_index::o_ind_head; obj; obj = obj->next)
	{
		if(obj->obj)
		{
			if(obj->obj->AffIsSet(bv))
				count++;
		}
	}

	return count;
}

float GetAffPercentPerObj(const BITVECT_DATA& bv)
{
	if(GetLoadedObjCount() > 0)
		return 100.0 * ((float)GetAffCountPerObj(bv)/(float)GetLoadedObjCount());

	return 0.0;
}
	struct arguments 
	{
		char * name;
		int type;
	};

bool str_prefix(CString str1, CString str2)
{

	for(int i = 0; i < (str1.GetLength() < str2.GetLength() ? str1.GetLength() : str2.GetLength()); i++)
	{
		if(str1[i] != str2[i])
			return false;
	}

	return true;
}


int GetArgType(CString str)
{
	struct arguments args[6] = 
	{
		{"mobiles", MOBILE},
		{"objects", OBJECT},
		{"rooms", ROOM},
		{"areas", AREA},
		{"zones", AREA},
		{"exits", EXIT},
	};

	if(str.IsEmpty())
		return NONE;

	for(int i = 0; i < 6; i++)
	{
		if(str_prefix(args[i].name, str))
			return args[i].type;
	}

	return NONE;
	
}

// this is a recursive function which will attempt
// to add the item "itemText" to the menu with the
// given ID number. The "itemText" will be parsed for
// delimiting "\" characters for levels between
// popup menus. If a popup menu does not exist, it will
// be created and inserted at the end of the menu
bool MenuFunctions::AddMenuItem(HMENU hTargetMenu, const CString& itemText, UINT itemID, void *data)
{
	bool bSuccess = false;

	ASSERT(itemText.GetLength() > 0);
	ASSERT(itemID != 0);
	ASSERT(hTargetMenu != NULL);

	// first, does the menu item have any required submenus to be found/created?
	if (itemText.Find('\\') >= 0)
	{
		// yes, we need to do a recursive call on a submenu handle and with that sub
		// menu name removed from itemText

		// 1:get the popup menu name
		CString popupMenuName = itemText.Left(itemText.Find('\\'));
		// 2:get the rest of the menu item name minus the delimiting '\' character
		CString remainingText = itemText.Right(itemText.GetLength() - popupMenuName.GetLength() - 1);
		// 3:See whether the popup menu already exists
		int itemCount = ::GetMenuItemCount(hTargetMenu);
		bool bFoundSubMenu = false;
		MENUITEMINFO menuItemInfo;

		memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_TYPE | MIIM_STATE | MIIM_ID | MIIM_SUBMENU;
		for (int itemIndex = 0 ; itemIndex < itemCount && !bFoundSubMenu ; itemIndex++)
		{
			::GetMenuItemInfo(hTargetMenu, itemIndex, TRUE, &menuItemInfo);
			if (menuItemInfo.hSubMenu != 0)
			{
				// this menu item is a popup menu (non popups give 0)
				TCHAR	buffer[MAX_PATH];
				::GetMenuString(hTargetMenu, itemIndex, buffer, MAX_PATH, MF_BYPOSITION);
				TRACE("%s\n", buffer);
				if (popupMenuName == buffer)
				{
					// this is the popup menu we have to add to
					bFoundSubMenu = true;
				}
			}
		}
		// 4: If exists, do recursive call, else create do recursive call and then insert it
		if (bFoundSubMenu)
		{
			bSuccess = AddMenuItem(menuItemInfo.hSubMenu, remainingText, itemID, data);
		}
		else
		{
			// we need to create a new sub menu and insert it
			HMENU hPopupMenu = ::CreatePopupMenu();
			if (hPopupMenu != NULL)
			{
				menuItemInfo.fMask = MIIM_DATA;
				menuItemInfo.dwItemData = (unsigned long)data;
				::SetMenuItemInfo(hPopupMenu, itemID, TRUE, &menuItemInfo);

				bSuccess = AddMenuItem(hPopupMenu, remainingText, itemID, data);
				if (bSuccess)
				{
					if (::AppendMenu(hTargetMenu, MF_POPUP, (UINT)hPopupMenu, popupMenuName) > 0)
					{
						bSuccess = true;
						// hPopupMenu now owned by hTargetMenu, we do not need to destroy it
					}
					else
					{
						// failed to insert the popup menu
						bSuccess = false;
						::DestroyMenu(hPopupMenu);	// stop a resource leak
					}
				}
			}
		}		
	}
	else
	{
		// no sub menu's required, add this item to this HMENU
		if (::AppendMenu(hTargetMenu, MF_BYCOMMAND, itemID, itemText) > 0)
		{
			// we successfully added the item to the menu
			bSuccess = true;
		}
	}

	return bSuccess;
}

// this is a recursive function which will attempt
// to add the item "itemText" to the menu with the
// given ID number. The "itemText" will be parsed for
// delimiting "\" characters for levels between
// popup menus. If a popup menu does not exist, it will
// be created and inserted at the specified position (if given)
// or the end of the menu if not
// this version of the procedure can have insert positions
// passed in using an int* array
bool MenuFunctions::AddMenuItem(
	HMENU hTargetMenu,				// menu to add to
	const CString& itemText,		// item name
	UINT itemID,					// 0 when separator insertion
	int *pInsertPositions)			// can be NULL
{
	bool bSuccess = false;

	ASSERT(itemText.GetLength() > 0);
	ASSERT(hTargetMenu != NULL);

	// work out where this item will be inserted
	int itemCount = ::GetMenuItemCount(hTargetMenu);
	int position = (pInsertPositions != NULL) ? *pInsertPositions : itemCount;
	int *pNextLevelInsert = NULL;

	// insert the option at a required position
	// -ve positions are from the end of the menu level
	if (position < 0)
	{
		// -ve positions are inserted from the end upwards
		position = max(0, itemCount + position);
	}
	else
	{
		// make sure we are trying to insert into a valid position
		position = min (position, itemCount);
	}
	if (pInsertPositions != NULL)
	{
		// have correct pointer for next recursive call, if required
		pNextLevelInsert = pInsertPositions + 1;
	}

	// first, does the menu item have any required submenus to be found/created?
	if (itemText.Find('\\') >= 0)
	{
		// yes, we need to do a recursive call on a submenu handle and with that sub
		// menu name removed from itemText

		// 1:get the popup menu name
		CString popupMenuName = itemText.Left(itemText.Find('\\'));
		// 2:get the rest of the menu item name minus the delimiting '\' character
		CString remainingText = itemText.Right(itemText.GetLength() - popupMenuName.GetLength() - 1);
		// 3:See whether the popup menu already exists
		int itemCount = ::GetMenuItemCount(hTargetMenu);
		bool bFoundSubMenu = false;
		MENUITEMINFO menuItemInfo;

		memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_TYPE | MIIM_STATE | MIIM_ID | MIIM_SUBMENU;
		
		for (int itemIndex = 0 ; itemIndex < itemCount && !bFoundSubMenu ; itemIndex++)
		{
			::GetMenuItemInfo(
					hTargetMenu, 
					itemIndex, 
					TRUE, 
					&menuItemInfo);
			if (menuItemInfo.hSubMenu != 0)
			{
				// this menu item is a popup menu (non popups give 0)
				TCHAR	buffer[MAX_PATH];
				::GetMenuString(
						hTargetMenu, 
						itemIndex, 
						buffer, 
						MAX_PATH, 
						MF_BYPOSITION);
				if (popupMenuName == buffer)
				{
					// this is the popup menu we have to add to
					bFoundSubMenu = true;
				}
			}
		}
		// 4: If exists, do recursive call, else create do recursive call and then insert it
		if (bFoundSubMenu)
		{
			bSuccess = AddMenuItem(
					menuItemInfo.hSubMenu, 
					remainingText, 
					itemID, 
					pNextLevelInsert);
		}
		else
		{
			// we need to create a new sub menu and insert it
			HMENU hPopupMenu = ::CreatePopupMenu();
			if (hPopupMenu != NULL)
			{
				bSuccess = AddMenuItem(
						hPopupMenu, 
						remainingText, 
						itemID, 
						pNextLevelInsert);
				if (bSuccess)
				{
					// we want to insert the new menu item by position
					bSuccess = (::InsertMenu(hTargetMenu, position, MF_BYPOSITION | MF_POPUP, (UINT)hPopupMenu, popupMenuName) > 0);
					if (!bSuccess)
					{
						// failed to insert the popup menu
						bSuccess = false;
						::DestroyMenu(hPopupMenu);	// stop a resource leak
					}
				}
			}
		}		
	}
	else
	{
		// no sub menu's required, add this item to this HMENU
		if (itemID > 0)
		{
			
			bSuccess = (::InsertMenu(hTargetMenu, position, MF_BYPOSITION | MF_STRING, itemID, itemText) > 0);
		}
		else
		{
			// inserting a separator
			bSuccess = (::InsertMenu(hTargetMenu, position, MF_BYPOSITION | MF_SEPARATOR, itemID, "") > 0);
		}
	}	

	return bSuccess;
}

int MenuFunctions::CalculateMenuHeight(HMENU hMenu)
{
    ASSERT(hMenu != NULL);
    int height = ::GetMenuItemCount(hMenu) * ::GetSystemMetrics(SM_CYMENUSIZE);

    // take the menu borders into account
    height += ::GetSystemMetrics(SM_CYEDGE);
    return height;
}

namespace MenuFunctions
{
    const int f_iconWidth = 16;
    const int f_menuBorder = 8;
    const int f_popupArrowSize = 8;
}

int MenuFunctions::CalculateMenuWidth(HMENU hMenu)
{
    // create a copy of the font that shoule be used to render a menu
	NONCLIENTMETRICS nm;
	LOGFONT lf;
	CFont menuFont;
    TCHAR menuItemText[_MAX_PATH];

    nm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize,&nm, 0));
    lf = nm.lfMenuFont;
    menuFont.CreateFontIndirect(&lf);

    CDC dc;

    dc.Attach(::GetDC(NULL));       // get screen DC
    dc.SaveDC();
    dc.SelectObject(&menuFont);

    // look at each item and work out its width
    int maxWidth = 0;
    int itemCount = ::GetMenuItemCount(hMenu);

    for (int item = 0 ; item < itemCount ; item++)
    {
        // get each items data
        int itemWidth = f_iconWidth + f_menuBorder;
	    MENUITEMINFO	itemInfo;
        itemInfo.dwTypeData = menuItemText;
        itemInfo.cch = _MAX_PATH - 1;

	    memset(&itemInfo, 0, sizeof(MENUITEMINFO));
	    itemInfo.cbSize = sizeof(MENUITEMINFO);

	    itemInfo.fMask = MIIM_SUBMENU /*| MIIM_STRING*/;
	    ::GetMenuItemInfo(hMenu, item, TRUE, &itemInfo);

        if (itemInfo.hSubMenu != 0)
        {
            // its a popup menu, include the width of the > arrow
            itemWidth += f_popupArrowSize;
        }
        if (itemInfo.wID == 0)
        {
            // its a separator, dont measure the text
        }
        else
        {
            // measure the text using the font
            CSize textSize;
            CString itemText = menuItemText;
            // expand any tabs in the menu text
            itemText.Replace("\t", "    ");

            textSize = dc.GetTextExtent(itemText);
            itemWidth += textSize.cx;
        }
        if (itemWidth > maxWidth)
        {
            maxWidth = itemWidth;
        }
    }

    dc.RestoreDC(-1);
    ::ReleaseDC(NULL, dc.Detach());
    return maxWidth;
}

