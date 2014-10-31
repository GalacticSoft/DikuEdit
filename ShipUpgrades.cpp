#include "StdAfx.h"
#include "ShipUpgrades.h"

CannonList CannonList::cannons;
AmmoList AmmoList::ammos;
CrewList CrewList::crews;

Cannon::Cannon() 
: name(""), range(0), power(0), accuracy(0), 
  value(0), obj_vnum(0), hp(0), max_hp(0)
{
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;
	
	next = NULL;
	prev = NULL;
}

Cannon::~Cannon()
{
	name		= "";
	range		= 0; 
	power		= 0; 
	accuracy	= 0; 
	value		= 0; 
	obj_vnum	= 0; 
	hp			= 0; 
	max_hp		= 0;

	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;

	next = NULL;
	prev = NULL;
}

Ammo::Ammo()
: name(""), range(0), hull_dam(0), sail_dam(0), 
  crew_dam(0), max_quan(0), price(0) 
{
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;

	next = NULL;
	prev = NULL;
}

Ammo::~Ammo() 
{
	name		= "";
	range		= 0;
	hull_dam	= 0;
	sail_dam	= 0;
	crew_dam	= 0;
	max_quan	= 0;
	price		= 0;
	
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;
}

Crew::Crew()
: name(""), men(0), max_men(0), level(0),
  spd(0), frt(0), str(0), gun(0), max_gun(0),
  sail(0), max_sail(0), def(0), max_def(0),
  atk(0), max_atk(0), price(0), leader(0),
  member(0)
{
	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;

	next = NULL;
	prev = NULL;
	index = -1;
}

Crew::~Crew()
{
	name = "";
	men = 0;
	max_men = 0;
	level = 0;
	spd = 0;
	frt = 0;
	str = 0;
	gun = 0;
	max_gun = 0;
	sail = 0;
	max_sail = 0;
	def = 0;
	max_def = 0;
	atk = 0;
	max_atk = 0;
	price = 0;
	leader = 0; 
	member = 0;

	for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		shops[i] = 0;
}

CannonList::CannonList()
{
	first = NULL;
	cur = NULL;
	last = NULL;

	count = 0;
}

CannonList::~CannonList()
{
	RemoveAll();	
}

void CannonList::RemoveAll()
{
	while(first)
		RemoveCannon(first);

	cur = NULL;
	first = NULL;
	last = NULL;
	count = 0;
}

bool CannonList::AddCannon(Cannon *cannon)
{
	if(!cannon)
		return false;

	if(!first)
	{
		first = cannon;
		last = cannon;
	}
	else
	{
		last->next = cannon;
		cannon->prev = last;
		last = cannon;
	}

	count++;

	return true;
}

void CannonList::RemoveCannon(Cannon *cannon)
{
	if(cannon != first && cannon != last)
	{
		if(cannon->prev)
			cannon->prev->next = cannon->next;

		if(cannon->next)
			cannon->next->prev = cannon->prev;
	}
	else
	{
		if(cannon == first)
		{
			if(first->next)
				first->next->prev = NULL;

			first = first->next;
		}
	
		if(cannon == last)
		{
			if(last->prev)
				last->prev->next = NULL;

			last = last->prev;
		}
	}

	if(count == 1)
	{
		first = NULL;
		last = NULL;
	}

	delete cannon;

	count--;
}

int CannonList::GetCount()
{
	return count;
}

Cannon *CannonList::operator[](int i)
{
	int x;
	Cannon *tmp;

	for(tmp = first, x=1; tmp; tmp = tmp->next, x++)
	{
		if(i == x)
		{
			cur = tmp;
			return cur;
		}
	}

	return NULL;
}

void CannonList::LoadCannons()
{
	CFileFind finder;
    BOOL bWorking = finder.FindFile("./Cannons/*.cannon");
	CString path;

    while (bWorking)
    {
		bWorking = finder.FindNextFile();
	  	path = "./Cannons/";
		path += finder.GetFileName();

		LoadCannon(path);
    }
}

void CannonList::SaveCannons()
{
	CreateDirectory("./Cannons/", NULL);

	FILE *fp;

	for(Cannon *cannon = CannonList::cannons.first; cannon; cannon = cannon->next)
	{	
		fp = fopen("./Cannons/" + cannon->filename, "w");

		if(!fp || !cannon)
			return;

		fprintf(fp, "#name %s\n", cannon->name);
		fprintf(fp, "#range %d\n", cannon->range);
		fprintf(fp, "#power %d\n", cannon->power);
		fprintf(fp, "#accuracy %d\n", cannon->accuracy);
		fprintf(fp, "#value %d\n", cannon->value);
		fprintf(fp, "#vnum %d\n", cannon->obj_vnum);

		for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		{
			if(cannon->shops[i] > 0)
				fprintf(fp, "#shop %d\n", cannon->shops[i]);
		}

		fclose(fp);
	}
}

AmmoList::AmmoList()
{
	first = NULL;
	cur = NULL;
	last = NULL;

	count = 0;
}

AmmoList::~AmmoList()
{
	RemoveAll();
}

void AmmoList::RemoveAll()
{
	while(first)
		RemoveAmmo(first);

	cur = NULL;
	first = NULL;
	last = NULL;
	count = 0;
}

bool AmmoList::AddAmmo(Ammo *ammo)
{
	if(!ammo)
		return false;

	if(!first)
	{
		first = ammo;
		ammo->next = NULL;
		ammo->prev = NULL;
		last = ammo;
	}
	else
	{
		last->next = ammo;
		ammo->prev = last;
		ammo->next = NULL;
		last = ammo;
	}

	count++;

	return true;
}

void AmmoList::RemoveAmmo(Ammo *ammo)
{
	if(!ammo)
		return;

	if(ammo != first && ammo != last)
	{
		if(ammo->prev)
			ammo->prev->next = ammo->next;

		if(ammo->next)
			ammo->next->prev = ammo->prev;
	}
	else
	{
		if(ammo == first)
		{
			if(first->next)
				first->next->prev = NULL;

			first = first->next;
		}
	
		if(ammo == last)
		{
			if(last->prev)
				last->prev->next = NULL;

			last = last->prev;
		}
	}

	if(count == 1)
	{
		first = NULL;
		last = NULL;
	}

	delete ammo;

	count--;

}

int AmmoList::GetCount()
{
	return count;
}

Ammo *AmmoList::operator[](int i)
{
	int x;
	Ammo *tmp;

	for(tmp = first, x=1; tmp; tmp = tmp->next, x++)
	{
		if(i == x)
		{
			cur = tmp;
			return cur;
		}
	}

	return NULL;
}

Ammo *AmmoList::operator->()
{
	Ammo *tmp;

	tmp = cur;
	
	cur = NULL;

	return tmp;
}

void AmmoList::LoadAmmo(CString &filename)
{
	ifstream file;
	char str[512];
	char arg[512];
	char*buf;
	Ammo *ammo;

	file.open(filename);

	if(file.is_open())
	{
		ammo = new Ammo();
		
		while(!file.eof())
		{
			file.getline(str, 512, ' ');
			
			if(str[0] != '#') {
				file.getline(str, 512, '\n');
				continue;
			}
			
			ammo->filename = filename.Right(filename.GetLength() - filename.ReverseFind('/')-1);

			file.getline(arg, 512, '\n');
			buf = (str+1);

			if(!strcmp(buf, "name"))
				ammo->name = arg;
			if(!strcmp(buf, "crew"))
				ammo->crew_dam = atoi(arg);
			if(!strcmp(buf, "sail"))
				ammo->sail_dam = atoi(arg);
			if(!strcmp(buf, "hull"))
				ammo->hull_dam = atoi(arg);
			if(!strcmp(buf, "price"))
				ammo->price = atoi(arg);
			if(!strcmp(buf, "quantity"))
				ammo->max_quan = atoi(arg);
			if(!strcmp(buf, "shop"))
			{
				for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
				{
					if(ammo->shops[i] == 0)
					{
						ammo->shops[i] = atoi(arg);
						break;
					}
				}
			}
		}
		
		if(!AmmoList::ammos.AddAmmo(ammo))
			delete ammo;
		
		file.close();
	}
}

CrewList::CrewList()
{
	first = NULL;
	cur = NULL;
	last = NULL;
	count = 0;
}

CrewList::~CrewList()
{
	DeleteAllCrews();
}

void CrewList::LoadCrews()
{
	CFileFind finder;
    BOOL bWorking = finder.FindFile("./Crews/*.crew");
	CString path;
    
	while (bWorking)
    {
		bWorking = finder.FindNextFile();
	  	path = "./Crews/";
		path += finder.GetFileName();
		LoadCrew(path);
    }
}

void CrewList::LoadCrew(CString &filename)
{
	ifstream file;
	char str[512];
	char arg[512];
	char*buf;
	Crew *crew;

	file.open(filename);

	if(file.is_open())
	{
		crew = new Crew();
		
		while(!file.eof())
		{
			file.getline(str, 512, ' ');
			
			if(str[0] != '#') {
				file.getline(str, 512, '\n');
				continue;
			}

			file.getline(arg, 512, '\n');
			buf = (str+1);
			
			crew->filename = filename.Right(filename.GetLength() - filename.ReverseFind('/')-1);

			if(!strcmp(buf, "name"))
				crew->name = arg;
		
			if(!strcmp(buf,"maxmen"))
				crew->max_men = atoi(arg);
			
			if(!strcmp(buf, "spd"))
				crew->spd = atoi(arg);
			
			if(!strcmp(buf, "frt"))
				crew->frt = atoi(arg);
			
			if(!strcmp(buf, "str"))
				crew->str = atoi(arg);
			
			if(!strcmp(buf, "gun"))
				crew->gun = atoi(arg);
			
			if(!strcmp(buf, "maxgun"))
				crew->max_gun = atoi(arg);
			
			if(!strcmp(buf, "sail"))
				crew->sail = atoi(arg);
			
			if(!strcmp(buf, "maxsail"))
				crew->max_sail = atoi(arg);
			
			if(!strcmp(buf, "def"))
				crew->def = atoi(arg);
			
			if(!strcmp(buf, "maxdef"))
				crew->max_def = atoi(arg);
			
			if(!strcmp(buf, "atk"))
				crew->atk = atoi(arg);
			
			if(!strcmp(buf, "maxatk"))
				crew->max_atk = atoi(arg);
			
			if(!strcmp(buf, "leader"))
				crew->leader = atoi(arg);
			
			if(!strcmp(buf, "member"))
				crew->member = atoi(arg);

			if(!strcmp(buf, "price"))
				crew->price = atoi(arg);

			if(!strcmp(buf, "shop"))
			{
				for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
				{
					if(crew->shops[i] == 0)
					{
						crew->shops[i] = atoi(arg);
						break;
					}
				}
			}
		}

		count++;
		
		crew->index = count;
		
		AddCrew(crew);
		
		file.close();
	}
}

void CrewList::DeleteCrew(int i)
{
		
}

void CrewList::DeleteAllCrews()
{
	Crew *tmp;
	Crew *next;

	for(tmp = first; tmp; tmp = next)
	{
		next = tmp->next;

		delete tmp;
		tmp = NULL;
	}

	count--;

	first = NULL;
	last = NULL;
}

Crew* CrewList::operator[](int i)
{
	if(first && first->index == i)
		return first;
	if(last && last->index == i)
		return last;
	else
	{
		for(Crew *tmp = first; tmp; tmp = tmp->next)
		{
			if(tmp->index == i)
			{
				cur = tmp;
				return tmp;
			}
		}
	}

	return NULL;
}

Crew* CrewList::operator->()
{
	Crew *tmp;

	tmp = cur;

	cur = NULL;

	return tmp;
}

int CrewList::GetCount()
{
	return count;
}

void CrewList::AddCrew(Crew *crew)
{
	if(first == NULL)
	{
		first = crew;
		last = crew;
	}
	else
	{
		crew->prev = last;
		last->next = crew;
		last = crew;
	}	
	
	crew->index = count;
	count++;
}

void AmmoList::SaveAmmo()
{
	CreateDirectory("./Ammos/", NULL);

		FILE *fp;

	for(Ammo *ammo = AmmoList::ammos.first; ammo; ammo = ammo->next)
	{	
		fp = fopen("./Ammos/" + ammo->filename, "w");

		if(!fp)
			return;

		if(!ammo)
			return;

		fprintf(fp, "#name %s\n", ammo->name);
		fprintf(fp, "#crew %d\n", ammo->crew_dam);
		fprintf(fp, "#sail %d\n", ammo->sail_dam);
		fprintf(fp, "#hull %d\n", ammo->hull_dam);
		fprintf(fp, "#price %d\n", ammo->price);
		fprintf(fp, "#quantity %d\n", ammo->max_quan);

		for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		{
			if(ammo->shops[i] > 0)
				fprintf(fp, "#shop %d\n", ammo->shops[i]);
		}

		fclose(fp);
	}
}

void AmmoList::LoadAmmo()
{
	CFileFind finder;
    BOOL bWorking = finder.FindFile("./Ammos/*.ammo");
    CString path;
	
	while (bWorking)
    {
		bWorking = finder.FindNextFile();
		path = "./Ammos/";
		path += finder.GetFileName();
		LoadAmmo(path);
    }
}

void CrewList::SaveCrews()
{
	CreateDirectory("./Crews/", NULL);
	FILE *fp;

	for(Crew *crew = CrewList::crews.first; crew; crew = crew->next)
	{	
		fp = fopen("./Crews/" + crew->filename, "w");

		if(!fp)
			return;

		if(!crew)
			return;

		fprintf(fp, "#name %s\n", crew->name);
		fprintf(fp, "#maxmen %d\n", crew->max_men);
		fprintf(fp, "#spd %d\n", crew->spd);
		fprintf(fp, "#frt %d\n", crew->frt);
		fprintf(fp, "#str %d\n", crew->str);
		fprintf(fp, "#gun %d\n", crew->gun);
		fprintf(fp, "#maxgun %d\n", crew->max_gun);
		fprintf(fp, "#sail %d\n", crew->sail);
		fprintf(fp, "#maxsail %d\n", crew->max_sail);
		fprintf(fp, "#def %d\n", crew->def);
		fprintf(fp, "#maxdef %d\n", crew->max_def);
		fprintf(fp, "#atk %d\n", crew->atk);
		fprintf(fp, "#maxatk %d\n", crew->max_atk);
		fprintf(fp, "#price %d\n", crew->price);
		fprintf(fp, "#leader %d\n", crew->leader);
		fprintf(fp, "#member %d\n", crew->member);

		for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
		{
			if(crew->shops[i] > 0)
				fprintf(fp, "#shop %d\n", crew->shops[i]);
		}

		fclose(fp);
	}
}

void CannonList::LoadCannon(CString &filename)
{
	ifstream file;
	char str[512];
	char arg[512];
	char*buf;
	Cannon *cannon;

	file.open(filename);

	if(file.is_open())
	{
		cannon = new Cannon();
		
		while(!file.eof())
		{
			file.getline(str, 512, ' ');
			
			if(str[0] != '#') {
				file.getline(str, 512, '\n');
				continue;
			}

			file.getline(arg, 512, '\n');
			buf = (str+1);
			
			cannon->filename = filename.Right(filename.GetLength() - filename.ReverseFind('/')-1);

			if(!strcmp(buf, "name"))
				cannon->name = arg;
			else if(!strcmp(buf, "range"))
				cannon->range = atoi(arg);
			else if(!strcmp(buf, "power"))
				cannon->power = atoi(arg);
			else if(!strcmp(buf, "accuracy"))
				cannon->accuracy = atoi(arg);
			else if(!strcmp(buf, "value"))
				cannon->value = atoi(arg);
			else if(!strcmp(buf, "vnum"))
				cannon->obj_vnum = atoi(arg);
			else if(!strcmp(buf, "shop"))
			{
				for(int i = 0; i < MAX_SHIPWRIGHTS; i++)
				{
					if(cannon->shops[i] == 0)
					{
						cannon->shops[i] = atoi(arg);
						break;
					}
				}
			}
		}

		if(!AddCannon(cannon))
			delete cannon;
		
		file.close();
	}
}