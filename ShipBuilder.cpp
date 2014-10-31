// ShipBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "ShipBuilder.h"
#include "CannonBuilder.h"
#include "AmmoBuilder.h"
#include "CrewBuilder.h"
#include "ShipUpgrades.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShipBuilder dialog
ShipBuilder::ShipBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(ShipBuilder::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShipBuilder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void ShipBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShipBuilder)
	DDX_Control(pDX, IDC_SHIPBUILDER, BuilderTabs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ShipBuilder, CDialog)
	//{{AFX_MSG_MAP(ShipBuilder)
	ON_BN_CLICKED(IDC_CREATE,	OnCreate)
	ON_BN_CLICKED(IDC_EDIT,		OnEdit)
	ON_BN_CLICKED(IDC_DELETE,	OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShipBuilder message handlers

BOOL ShipBuilder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	cannon_tab.Create (IDD_CANNON_TAB, this);
	BuilderTabs.AddSSLPage (_T("Cannon Builder"), 0, &cannon_tab);
	
	ammo_tab.Create (IDD_AMMO_TAB, this);
	BuilderTabs.AddSSLPage (_T("Ammo Builder"), 1, &ammo_tab);
	
	crew_tab.Create (IDD_CREW_TAB, this);
	BuilderTabs.AddSSLPage (_T("Crew Builder"), 2, &crew_tab);

	BuilderTabs.SetCurSel(0);

	return TRUE;
}

void ShipBuilder::OnOK() 
{
	CDialog::OnOK();
}

void ShipBuilder::OnCreate() 
{
	switch(BuilderTabs.GetCurSel())
	{
	case 0:	
		CreateCannon();
		break;
	case 1:
		CreateAmmo();
		break;
	case 2:
		CreateCrew();
		break;
	default:
		break;
	}
}

void ShipBuilder::OnEdit() 
{
	switch(BuilderTabs.GetCurSel())
	{
	case 0:
		EditCannon();
		break;
	case 1:
		EditAmmo();
		break;
	case 2:
		EditCrew();
		break;
	default:
		break;
	}
}

void ShipBuilder::OnDelete() 
{
	switch(BuilderTabs.GetCurSel())
	{
	case 0:
		DeleteCannon();
		break;
	case 1:
		DeleteAmmo();
		break;
	case 2:
		DeleteCrew();
		break;
	default:
		break;
	}
}

void ShipBuilder::CreateCannon()
{
	CannonBuilder cannon_dlg(this);
	Cannon *cannon;
	CWnd *tab;
	CListCtrl *list;
	CString str;
	int i;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CANNON_LIST);

	i = list->GetItemCount();

	cannon = new Cannon();

	cannon_dlg.cannon = cannon;

	if(cannon_dlg.DoModal() == IDOK)
	{
		CannonList::cannons.AddCannon(cannon);

		list->InsertItem(i, StripAnsiChars(cannon->name), 0);
		str.Format("%d", cannon->value);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)cannon);
	}
	else
		delete cannon;
}

void ShipBuilder::EditCannon()
{
	CannonBuilder cannon_dlg(this);
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	int i;
	CString str;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CANNON_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the cannon you wish to edit.");
		return;
	}

	cannon_dlg.cannon = (Cannon*)list->GetItemData(i);

	if(cannon_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(cannon_dlg.cannon->name), 0);
		str.Format("%d", cannon_dlg.cannon->value);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)cannon_dlg.cannon);
	}
}

void ShipBuilder::DeleteCannon()
{
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	Cannon *cannon;
	int i, ret;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CANNON_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the cannon you wish to delete.");
		return;
	}

	cannon = (Cannon*)list->GetItemData(i);

	ret = MessageBox("Are you sure?", "Delete Cannon", MB_YESNO);

	if(ret == IDYES)
	{
		DeleteFile("./Cannons/" + cannon->filename);
		CannonList::cannons.RemoveCannon(cannon);
		list->DeleteItem(i);
	}	
}

void ShipBuilder::CreateAmmo()
{
	AmmoBuilder ammo_dlg(this);
	Ammo *ammo;
	CWnd *tab;
	CListCtrl *list;
	CString str;
	int i;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_AMMO_LIST);

	i = list->GetItemCount();

	ammo = new Ammo();

	ammo_dlg.ammo = ammo;

	if(ammo_dlg.DoModal() == IDOK)
	{
		AmmoList::ammos.AddAmmo(ammo);

		list->InsertItem(i, StripAnsiChars(ammo->name), 0);
		str.Format("%d", ammo->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)ammo);
	}
	else
		delete ammo;
}

void ShipBuilder::EditAmmo()
{
	AmmoBuilder ammo_dlg(this);
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	int i;
	CString str;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_AMMO_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the ammunition you wish to edit.");
		return;
	}

	ammo_dlg.ammo = (Ammo*)list->GetItemData(i);

	if(ammo_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(ammo_dlg.ammo->name), 0);
		str.Format("%d", ammo_dlg.ammo->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)ammo_dlg.ammo);
	}
}

void ShipBuilder::DeleteAmmo()
{
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	Ammo *ammo;
	int i, ret;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_AMMO_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the ammunition you wish to delete.");
		return;
	}

	ammo = (Ammo*)list->GetItemData(i);

	ret = MessageBox("Are you sure?", "Delete Ammo", MB_YESNO);

	if(ret == IDYES)
	{
		DeleteFile("./Ammos/" + ammo->filename);
		AmmoList::ammos.RemoveAmmo(ammo);
		list->DeleteItem(i);	
	}	
}

void ShipBuilder::CreateCrew()
{
	CrewBuilder crew_dlg(this);
	Crew *crew;
	CWnd *tab;
	CListCtrl *list;
	CString str;
	int i;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CREW_LIST);

	i = list->GetItemCount();

	crew = new Crew();

	crew_dlg.crew = crew;

	if(crew_dlg.DoModal() == IDOK)
	{
		CrewList::crews.AddCrew(crew);

		list->InsertItem(i, StripAnsiChars(crew->name), 0);
		str.Format("%d", crew->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)crew);
	}
	else
		delete crew;
}

void ShipBuilder::EditCrew()
{
	CrewBuilder crew_dlg(this);
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	int i;
	CString str;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CREW_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the crew you wish to edit.");
		return;
	}

	crew_dlg.crew = (Crew*)list->GetItemData(i);

	if(crew_dlg.DoModal() == IDOK)
	{
		list->DeleteItem(i);

		list->InsertItem(i, StripAnsiChars(crew_dlg.crew->name), 0);
		str.Format("%d", crew_dlg.crew->price);
		list->SetItem(i, 1, LVIF_TEXT, str, 1, 0, 0, 0);
		list->SetItemData(i, (DWORD)crew_dlg.crew);
	}
}

void ShipBuilder::DeleteCrew()
{
	CWnd *tab;
	CListCtrl *list;
	POSITION pos;
	Crew *crew;
	int i, ret;

	tab = BuilderTabs.GetSSLPage(BuilderTabs.GetCurSel());
	
	list = (CListCtrl*)tab->GetDlgItem(IDC_CREW_LIST);

	pos = list->GetFirstSelectedItemPosition();
	i = list->GetNextSelectedItem(pos);

	if(i < 0)
	{
		MessageBox("Please select the crew you wish to delete.");
		return;
	}

	crew = (Crew*)list->GetItemData(i);

	ret = MessageBox("Are you sure?", "Delete Crew", MB_YESNO);

	if(ret == IDYES)
	{
		DeleteFile("./Crews/" + crew->filename);
		CrewList::crews.DeleteCrew(crew->index);
		list->DeleteItem(i);
	}	
}
