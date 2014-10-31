#ifndef _SHIPS_H_
#define _SHIPS_H_

enum ShipConsts
{
	MAX_SHIPWRIGHTS = 50,
};

class Cannon
{
public:
	char *		 name;			//name of the cannon or specialty weapon
	int			 range;
	int			 power;
	int          accuracy;
	int			 value;
	int			 obj_vnum;
	int			 shops[MAX_SHIPWRIGHTS];	
	int			 hp;
	int			 max_hp;

public:
	Cannon();
	~Cannon();
};

class Ammo
{
public:
	char *		 name;
	int			 range;
	int			 hull_dam;
	int			 sail_dam;
	int			 crew_dam;
	int			 max_quan;
	int			 price;
	int			 shops[MAX_SHIPWRIGHTS];

public:
	Ammo();
	~Ammo();

};

class Crew
{
public:
	char name[MAX_STRING_LENGTH];

	int men;
	int max_men;
	int level;
	
	int spd;
	int frt;
	int str;
	
	int gun;
	int max_gun;

	int sail;
	int max_sail;

	int def;
	int max_def;

	int atk;
	int max_atk;
	
	int price;

	//mob vnums
	int leader; //vnum of the crew leader
	int member; //vnum of gereric crew member

	int shops[MAX_SHIPWRIGHTS]; //vnums where the crews are sold

public:
	Crew();
	~Crew();
};

#endif