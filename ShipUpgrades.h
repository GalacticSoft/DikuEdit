#ifndef _SHIPS_H_
#define _SHIPS_H_

enum ShipConsts
{
	MAX_SHIPWRIGHTS =  50,
};

class Cannon
{
public:
	CString		 filename;
	CString		 name;			//name of the cannon or specialty weapon
	int			 range;
	int			 power;
	int          accuracy;
	int			 value;
	int			 obj_vnum;
	int			 shops[MAX_SHIPWRIGHTS];	
	int			 hp;
	int			 max_hp;

	Cannon *next;
	Cannon *prev;

public:
	Cannon();
	~Cannon();
};

class CannonList
{
public:
	static CannonList cannons;

	Cannon *first;
	Cannon *cur;
	Cannon *last;

	int count;

public:
	CannonList();
	virtual ~CannonList();

	bool AddCannon(Cannon *cannon);
	void RemoveCannon(Cannon *cannon);
	int GetCount();

	void RemoveAll();

	Cannon *operator[](int i);
	Cannon *operator->();

	void LoadCannons();
	void LoadCannon(CString &filename);
	void SaveCannons();
};

class Ammo
{
public:
	CString		 name;
	CString		 filename;
	int			 range;
	int			 hull_dam;
	int			 sail_dam;
	int			 crew_dam;
	int			 max_quan;
	int			 price;
	int			 shops[MAX_SHIPWRIGHTS];

	Ammo *next;
	Ammo *prev;

public:
	Ammo();
	~Ammo();
};

class AmmoList
{
public:
	static AmmoList ammos;

public:
	Ammo *first;
	Ammo *cur;
	Ammo *last;

	int count;

public:
	AmmoList();
	~AmmoList();

	bool	AddAmmo(Ammo *ammo);
	void	RemoveAmmo(Ammo *ammo);
	int		GetCount();
	
	void RemoveAll();

	Ammo *	operator[](int i);
	Ammo *	operator->();

	void LoadAmmo(CString &filename);
	void LoadAmmo();
	void SaveAmmo();
};

class Crew
{
public:
	CString filename;
	CString name;

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

	Crew *next;
	Crew *prev;
	int index;

public:
	Crew();
	~Crew();
};


class CrewList
{
public:
	static CrewList crews;

public:	
	Crew *first;
	Crew *cur;
	Crew *last;
	int count;

public:
	CrewList();
	~CrewList();

	void LoadCrews();
	void SaveCrews();

	void LoadCrew(CString &filename);
	void DeleteCrew(int i);
	void DeleteAllCrews();
	void AddCrew(Crew *crew);
	
	int GetCount();
	
	Crew* operator[](int i);
	Crew* operator->();
};
#endif