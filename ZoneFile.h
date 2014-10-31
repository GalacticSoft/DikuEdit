#ifndef _ZONE_FILE_H_
#define _ZONE_FILE_H_

enum {MAND = 3344556, SPECIFIED = 3344557, DEFLT = 3344558};

struct  key_data
{
    char			key[12];	/* Increase if you make a key > 11 chars */
    int				status;	/* KEY_SPEC, KEY_REQU, KEY_DFLT          */
    unsigned long	deflt;	/* Default value or pointer              */
    void *			ptrs[11];	/* Increase if you have > 9 parms/line   */
};

struct	reset_data
{
    reset_data *	next;
    char		command;
    int 		arg0;
    int 		arg1;
    int 		arg2;
    int 		arg3;
    int                 arg4;
    int                 arg5;
    int                 arg6;
    int                 arg7;
};

//base class for both read and write files
class ZoneFile
{
protected:
	virtual bool Open(const char*dir) = 0;
	virtual void Close()=0;

protected:
	FILE *file;
	DlgSave dlg_save;
	CStatic *txt;
	CProgressCtrl *prg;
	CWinDEDlg *parent;
	int pos;

public:
	ZoneFile(CWinDEDlg *parent);
	ZoneFile();
	~ZoneFile();

	void DisplayProg();
	void CloseProg();

	void SetProgRange(int x, int y);
	void SetProgPos(int x);
	void SetProgText(CString str);
};

//class used to open a new zone and write it to memory
class AreFileOpen : public ZoneFile
{
public:
	AreFileOpen(const char *dir, CWinDEDlg *par);
	AreFileOpen();
	
private:
	bool Open(const char *dir);
	
	void Close();

	void ReadAreaData(const char *dir);
	void LoadRooms();
	void LoadMobs();
	void LoadObjects();
	void LoadResets();
	void LoadShops();
	void LoadQuests();
	void LoadSpecials();
	void LoadProgs();
};

class AreFileSave : public ZoneFile
{
public:
	AreFileSave(const char *dir, CWinDEDlg *par);
	~AreFileSave();
public:
	bool Open(const char *dir);
	void Close();

	
	void Write(char *str, ...);
	void Write(CString &str);
	void Write(int &i);
	void Write(float &i);
	
	void WriteMobiles();
	void WriteMob(mob_data *mob);
	
	void WriteObjects();
	void WriteObj(object_data *obj);
	
	void WriteRooms();
	void WriteRoom(room_data *room);
	
	void WriteShops();
	void WriteShop(shop_data *shop);
	
	void WriteArea();
	
	void WriteProgs();

	void WriteQuests();
	void WriteQuest(quest_data *quest);
	void WriteQuest(talk_data *clue);
	
	void WriteResets();
	void SaveExitResets();
	void SaveMobileResets();
	void SaveObjectResets();
};

class DeFile : public ZoneFile
{
public:
	void ReadAreaData(const char *dir);
	void LoadRooms();
	void LoadMobs();
	void LoadObjects();
	void LoadResets();
	void LoadShops();

public:
	void Write(CString &str);
	void Write(int &i);
	void Write(float &i);
	void Write(mob_data *mob);
	void Write(object_data *obj);
	void Write(room_data *room);
	void Write(shop_data *shop);
	void Write(area_data *area);
};

CString fread_word( FILE *fp, int *status );
void fread_to_eol( FILE *fp );
int fread_number( FILE *fp, int *status );
char fread_letter( FILE *fp );
CString fread_string( FILE *fp, int *status );

#endif