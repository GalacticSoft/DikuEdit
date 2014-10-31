#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditObject.h"
#include "DlgEditTrap.h"
#include "ProgEditor.h"
#include "DlgSelectAff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


DlgEditObject::DlgEditObject(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditObject::IDD, pParent)
{
	int i;

	for(i = 0; i < MAX_ITEM_VALUE; i++)
		values[i] = 0;

	//{{AFX_DATA_INIT(DlgEditObject)
	condition = 100;
	crafts = 0;
	keywords = _T("object unnamed");
	long_desc = _T("An unnamed object is lying here.");
	material = 0;
	short_desc = _T("an unnamed object");
	size = 0;
	type = 0;
	vnum = 0;
	volume = 0;
	weight = 0;
	apply_loc1 = 0;
	apply_val2 = 0;
	apply_val1 = 0;
	apply_loc2 = 0;
	wear_flags = 0;
	object = NULL;
	//}}AFX_DATA_INIT
}


void DlgEditObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_VALUE1, values[0]);
	DDX_Text(pDX, IDC_VALUE2, values[1]);
	DDX_Text(pDX, IDC_VALUE3, values[2]);
	DDX_Text(pDX, IDC_VALUE4, values[3]);
	DDX_Text(pDX, IDC_VALUE5, values[4]);
	DDX_Text(pDX, IDC_VALUE6, values[5]);
	DDX_Text(pDX, IDC_VALUE7, values[6]);
	DDX_Text(pDX, IDC_VALUE8, values[7]);
	
	//{{AFX_DATA_MAP(DlgEditObject)
	DDX_Control(pDX, IDC_VALUE6, m_Value6);
	DDX_Control(pDX, IDC_VALUE7, m_Value7);
	DDX_Control(pDX, IDC_VALUE8, m_Value8);
	DDX_Control(pDX, IDC_VALUE4, m_Value4);
	DDX_Control(pDX, IDC_VALUE5, m_Value5);
	DDX_Control(pDX, IDC_VALUE3, m_Value3);
	DDX_Control(pDX, IDC_VALUE2, m_Value2);
	DDX_Control(pDX, IDC_VALUE1, m_Value1);
	DDX_Control(pDX, IDC_APPLY2_VAL, m_Apply2);
	DDX_Control(pDX, IDC_APPLY1_VAL, m_Apply1);
	DDX_Text(pDX, IDC_OBJ_CONDITION, condition);
	DDV_MinMaxInt(pDX, condition, 0, 100);
	DDX_CBIndex(pDX, IDC_OBJ_CRAFTSMANSHIP, crafts);
	DDX_Text(pDX, IDC_OBJ_KEYWORDS, keywords);
	DDX_Text(pDX, IDC_OBJ_LONG, long_desc);
	DDX_CBIndex(pDX, IDC_OBJ_MATERIAL, material);
	DDX_Text(pDX, IDC_OBJ_SHORT, short_desc);
	DDX_Text(pDX, IDC_OBJ_SIZE, size);
	DDX_CBIndex(pDX, IDC_OBJ_TYPE, type);
	DDX_Text(pDX, IDC_OBJ_VNUM, vnum);
	DDX_Text(pDX, IDC_OBJ_VOLUME, volume);
	DDX_Text(pDX, IDC_OBJ_WEIGHT, weight);
	DDX_CBIndex(pDX, IDC_APPLY1_LIST, apply_loc1);
	DDX_Text(pDX, IDC_APPLY2_VAL, apply_val2);
	DDX_Text(pDX, IDC_APPLY1_VAL, apply_val1);
	DDX_CBIndex(pDX, IDC_APPLY2_LIST, apply_loc2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditObject, CDialog)
	//{{AFX_MSG_MAP(DlgEditObject)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_OBJ_AFF, OnObjAff)
	ON_BN_CLICKED(IDC_EXTRA_FLAGS, OnExtraFlags)
	ON_BN_CLICKED(IDC_ANTI_FLAGS, OnAntiFlags)
	ON_BN_CLICKED(IDC_OBJ_EXTRA_DESC, OnObjExtraDesc)
	ON_BN_CLICKED(IDC_EDIT_CONTENTS, OnEditContents)
	ON_BN_CLICKED(IDC_OBJ_LOAD, OnObjLoad)
	ON_CBN_SELCHANGE(IDC_OBJ_TYPE, OnSelchangeObjType)
	ON_BN_CLICKED(IDC_TRAP, OnTrap)
	ON_BN_CLICKED(IDC_EDIT_PROGS, OnEditProgs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DlgEditObject::OnInitDialog() 
{
	CComboBox	*cb;
	CListBox	*lb;
	CComboBox	*val1, *val2;
	int i, x;

	CDialog::OnInitDialog();

	condition = object->condition;
	crafts = object->craftsmanship;
	keywords = object->name;
	long_desc = object->description;
	material = object->material;
	short_desc = object->short_descr;
	size = object->size;
	vnum = object->vnum;
	volume = object->volume;
	weight = object->weight;
	wear_flags = object->wear_flags;
	apply_loc1 = object->applies[0].loc;
	apply_val1 = object->applies[0].value;
	apply_loc2 = object->applies[1].loc;
	apply_val2 = object->applies[1].value;

	for(i = 0; i < MAX_ITEM_VALUE; i++)
		values[i] = object->value[i];
	
	cb = (CComboBox*)GetDlgItem(IDC_OBJ_MATERIAL);
	for(i = 0; i < MAX_MATERIAL; i++) {
		cb->InsertString(i, materials[i]);
	}
	cb->SetCurSel(material);

	cb = (CComboBox*)GetDlgItem(IDC_OBJ_CRAFTSMANSHIP);
	for(i = 0; i <= CRAFT_ONEOFAKIND; i++) {
		cb->InsertString(i, craftsmanship[i]);
	}
	cb->SetCurSel(crafts);

	cb = (CComboBox*)GetDlgItem(IDC_OBJ_TYPE);
	for(i = 0, x = 0; i < MAX_ITEM_TYPE; i++) {
		if(item_types[i].in_use) {
			cb->InsertString(x, item_types[i].name);
			cb->SetItemData(x, i);
			
			if(i == object->item_type) {
				cb->SetCurSel(x);
				type = x;
				ValueStrings(i);
				ValueInput(i);
			}

			x++;
		}
	}

	lb = (CListBox*)GetDlgItem(IDC_OBJ_WEAR_LOCS);
	for(i = 0; i < NUM_ITEM_WEAR_VECTORS; i++) {
		lb->InsertString(i, wear_locs[i].name);
		lb->SetItemData(i, wear_locs[i].bv);
	
		if(IS_SET(wear_flags, wear_locs[i].bv))
			lb->SetSel(i, true);
	}
	
	val1 = (CComboBox*)GetDlgItem(IDC_APPLY1_LIST);
	val2 = (CComboBox*)GetDlgItem(IDC_APPLY2_LIST);

	for(i = 0; i < APPLY_HIGHEST; i++)
	{
		val1->InsertString(i, apply_names[i]);
		val2->InsertString(i, apply_names[i]);
	}

	val1->SetCurSel(apply_loc1);
	val2->SetCurSel(apply_loc2);
	
	SetValues();

	UpdateData(false);

	return TRUE;
}

void DlgEditObject::OnOK() 
{	
	int i;
	CEdit *ed;
	CString str;
	CListBox* lb;
	CComboBox* cb;
	object_data *tmp;
	
	ed = (CEdit*)GetDlgItem(IDC_OBJ_VNUM);
	
	UpdateData(true);
	
	SaveValues();

	for(i = 0; i < MAX_ITEM_VALUE; i++)
		object->value[i] = values[i];
	
	lb = (CListBox*)GetDlgItem(IDC_OBJ_WEAR_LOCS);

	for(i = 0; i < lb->GetCount(); i++) {
		if(lb->GetSel(i))
			SET_BIT(wear_flags, wear_locs[i].bv);
	}

	object->wear_flags = wear_flags;
	object->condition = condition;
	object->craftsmanship = crafts;
	object->name = keywords;
	object->description = long_desc;
	object->material = material;
	object->short_descr = short_desc;
	object->size = size;
	
	object->vnum = vnum;
	object->volume = volume;
	object->weight = weight;
	
	object->applies[0].loc = apply_loc1;
	object->applies[0].value = apply_val1;

	object->applies[1].loc = apply_loc2;
	object->applies[1].value = apply_val2;

	cb = (CComboBox*)GetDlgItem(IDC_OBJ_TYPE);

	object->item_type = cb->GetItemData(type);

	if(!object->IsContainer() && object->contains)
		object->RemoveContents();
	
	if(vnum <= 0) {
		MessageBox("Vnums less than 1 not allowed.");
		ed->SetFocus();
		ed->SetSel(0, ed->GetWindowTextLength());
		return;
	} 
	
	tmp = GetObjByVnum(object->vnum);
	
	if(!tmp) {
		object->AddToList();
		
		if(object->vnum == object_data::high_obj_vnum)
			object_data::high_obj_vnum++;
		
	} else if(tmp != object) {
		str.Format("Object with vnum %d already exists.", vnum);
		MessageBox(str, "Duplicate Vnum!");

		

		ed->SetFocus();
		ed->SetSel(0, ed->GetWindowTextLength());
		return;
	} 

	CDialog::OnOK();
}

void DlgEditObject::OnDelete() 
{
	extra_desc *ed, *next;
	obj_index *index, *next_index;

	for(ed = object->first_extra_descr; ed; ed = next) {
		next = ed->next;
		delete ed;
	}

	for(index = object->contains; index; index = next_index) {
		next_index = index->next;
		delete index;
	}

	((CWinDEDlg *)this->GetParent())->RemoveItem(object->m_tThis);

	if(GetObjByVnum(object->vnum))
		object->RemoveFromList();

	object = NULL;

	CDialog::OnCancel();
}

void DlgEditObject::OnObjAff() 
{
	DlgSelectAff aff_dlg;

	aff_dlg.type = OBJECT;
	aff_dlg.obj = object;
	aff_dlg.DoModal();
}

void DlgEditObject::OnExtraFlags() 
{
	DlgExtraObjFlags dlg(this);

	dlg.obj = object;

	dlg.DoModal();
}

void DlgEditObject::OnAntiFlags() 
{
	DlgEditAntiFlags dlg(this);
	int ret;

	dlg.antis[0] = object->anti_flags[0];
	dlg.antis[1] = object->anti_flags[1];

	ret = dlg.DoModal();

	if(ret == IDOK) {
		object->anti_flags[0] = dlg.antis[0];
		object->anti_flags[1] = dlg.antis[1];
	}
}

void DlgEditObject::OnObjExtraDesc() 
{
	DlgExtraDesc ed(this);
	extra_desc *ped, *next;
	int ret;
	
	ed.old_ed_list = object->first_extra_descr;
	ed.last_old_ed = object->last_extra_desc;
	ed.cur_ed = ed.old_ed_list;

	ret = ed.DoModal();

	if(ret == IDOK) {
		if(object->last_extra_desc != NULL) 
			object->last_extra_desc->next = ed.first_new_ed;
	    else
			object->first_extra_descr = ed.first_new_ed;

			object->last_extra_desc = ed.last_new_ed;
		
		for(ped = object->first_extra_descr; ped; ped = next) {
			if(ped == NULL)
				break;
		
			if(ped->deleted == true || ped->keyword == "" ) {
				if(ped->prev != NULL)
					ped->prev->next = ped->next;
				if(ped->next != NULL)
					ped->next->prev = ped->prev;
				
				if(ped == object->first_extra_descr)
					object->first_extra_descr = ped->next;
				if(ped == object->last_extra_desc)
					object->last_extra_desc = ped->prev;
			
				next = ped->next;
				
				delete ped;
				
				ped = next;
			}
			else  {
				next = ped->next;
			}
		}
	}
	else if(ret == IDCANCEL) {
		for(ped = ed.first_new_ed; ped; ped = next) {
			if(ped == NULL)
				break;
			
			next = ped->next;
			delete ped;
		}
		for(ped = object->first_extra_descr; ped; ped = ped->next) {
			if(ped == NULL)
				break;
		
			if(ped->deleted == true) 
				ped->deleted = false;
		}
	}
}

void DlgEditObject::OnEditContents() 
{
	/*DlgEditContents dlg(this);

	dlg.obj = object;

	dlg.DoModal();*/
}

void DlgEditObject::OnObjLoad() 
{
	
}

void DlgEditObject::OnSelchangeObjType() 
{
	CComboBox* cb;

	UpdateData(true);

	cb = (CComboBox*)GetDlgItem(IDC_OBJ_TYPE);
	
	for(int i = 0; i < MAX_ITEM_VALUE; i++)
		values[i] = 0;
	
	ValueStrings(cb->GetItemData(cb->GetCurSel()));
	ValueInput(cb->GetItemData(cb->GetCurSel()));

	UpdateData(false);
	
}

void DlgEditObject::OnCancel() 
{
	extra_desc *ed, *next;
	obj_index *index, *next_index;

	if(!GetObjByVnum(object->vnum)) {
		for(ed = object->first_extra_descr; ed; ed = next) {
			next = ed->next;
			delete ed;
		}
		
		for(index = object->contains; index; index = next_index) {
			next_index = index->next;
			delete index;
		}

		delete object;
	}

	CDialog::OnCancel();
}

void DlgEditObject::SetValues()
{
	CListBox*lb;
	CComboBox*cb;
	int i;

	switch(object->item_type)
	{
	case TYPE_WEAPON:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		cb->SetCurSel(values[0]);

		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		cb->SetCurSel(values[3]);
		break;
	case TYPE_POTION:
	case TYPE_SCROLL:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{	
			if(values[1] == cb->GetItemData(i))
				cb->SetCurSel(i);	
		}
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[2] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[3] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}

		break;
	case TYPE_RANGED_WEAPON:
	case TYPE_MISSILEWEAP:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		cb->SetCurSel(values[3]);
		break;
	case TYPE_STAFF:
	case TYPE_WAND:	
		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[3] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		break;
	case TYPE_SPELLSCROLL:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[2] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		break;
	case TYPE_DRINK_CON:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		cb->SetCurSel(values[2]);
		break;
	case TYPE_SHIP:
	case TYPE_VEHICLE:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		cb->SetCurSel(values[0]);

		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		cb->SetCurSel(values[3]);
		break;
	case TYPE_CONTAINER:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS1);
		for(i = 0; i < lb->GetCount(); i++)
		{
			if(IS_SET(values[1], lb->GetItemData(i)))
				lb->SetSel(i);
		}
		break;
	case TYPE_SUMMON:
	case TYPE_TELEPORT:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[1] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		break;
	case TYPE_SWITCH:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[0] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		cb->SetCurSel(values[2]);
		break;
	case TYPE_INSTRUMENT:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		for(i = 0; i < cb->GetCount(); i++)
		{
			if(values[0] == cb->GetItemData(i))
				cb->SetCurSel(i);
		}
		break;
	case TYPE_SHIELD:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		cb->SetCurSel(values[0]);

		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		cb->SetCurSel(values[1]);

		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		cb->SetCurSel(values[2]);
		break;
	case TYPE_QUIVER:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS1);
		for(i = 0; i < lb->GetCount(); i++)
		{
			if(IS_SET(values[1], lb->GetItemData(i)))
				lb->SetSel(i);
		}

		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		cb->SetCurSel(values[2]);
		break;
	case TYPE_TOTEM:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS0);
		for(i = 0; i < lb->GetCount(); i++)
		{
			if(IS_SET(values[0], lb->GetItemData(i)))
				lb->SetSel(i);
		}
		break;

	}
}

void DlgEditObject::SaveValues()
{
	CListBox*lb;
	CComboBox *types;
	CComboBox*cb;
	int i;

	types = (CComboBox*)GetDlgItem(IDC_OBJ_TYPE);
	switch(types->GetItemData(type))
	{
	case TYPE_SHIP:
	case TYPE_VEHICLE:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		values[0] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		values[3] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_WEAPON:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		values[0] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		values[3] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_POTION:
	case TYPE_SCROLL:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		values[1] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		values[2] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		values[3] = cb->GetItemData(cb->GetCurSel());
		break;	
	case TYPE_RANGED_WEAPON:
	case TYPE_MISSILEWEAP:
	case TYPE_STAFF:
	case TYPE_WAND:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
		values[3] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_SPELLSCROLL:
	case TYPE_DRINK_CON:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		values[2] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_CONTAINER:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS1);
		
		values[1] = 0;

		for(i = 0; i < lb->GetCount(); i++)
		{
			if(lb->GetSel(i))
				SET_BIT(values[1], lb->GetItemData(i));
		}
		break;
	case TYPE_SUMMON:
	case TYPE_TELEPORT:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		values[1] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_SWITCH:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		values[0] = cb->GetItemData(cb->GetCurSel());
		
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		values[2] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_INSTRUMENT:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		values[0] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_SHIELD:
		cb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
		values[0] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
		values[1] = cb->GetItemData(cb->GetCurSel());

		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		values[2] = cb->GetItemData(cb->GetCurSel());
		break;
	case TYPE_QUIVER:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS1);
		
		values[1] = 0;
		
		for(i = 0; i < lb->GetCount(); i++)
		{
			if(lb->GetSel(i))
				SET_BIT(values[1], lb->GetItemData(i));
		}
		cb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
		values[2] = cb->GetItemData(cb->GetCurSel());
	case TYPE_TOTEM:
		lb = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS0);
		
		values[0] = 0;

		for(i = 0; i < lb->GetCount(); i++)
		{
			if(lb->GetSel(i))
				SET_BIT(values[0], lb->GetItemData(i));
		}
		break;

	}
}

void DlgEditObject::ValueStrings(int obj_type) 
{
	int i;
	CWnd *text;
	CString	str;
	
	for(i = 0; i < MAX_ITEM_VALUE; i++) {
		switch(i) {
			case 0: 
				switch (obj_type) {
					case TYPE_POTION:			 
					case TYPE_SCROLL: 
					case TYPE_WAND: 
					case TYPE_STAFF:			str = "Spell Level:";				break;
					case TYPE_WEAPON:			str = "Weapon Type:";		break;
					case TYPE_MISSILEWEAP:		str = "To-Hit Mod:";		break;
					case TYPE_RANGED_WEAPON:	str = "Range:";				break;
					case TYPE_ARMOR:			str = "Armor Class:";		break;
					case TYPE_CONTAINER:		str = "Max Weight:";		break;
					case TYPE_DRINK_CON:		str = "Max Drinks:";		break;
					case TYPE_FOOD:				str = "Hours Filled:";		break;
					case TYPE_MONEY:			str = "Copper:";			break;
					case TYPE_SHIP:
					case TYPE_VEHICLE:			str = "Type:";				break;
					case TYPE_TELEPORT:			str = "Target Room:";		break;
					case TYPE_SWITCH:			str = "Command:";			break;
					case TYPE_QUIVER:			str = "Max Capacity:";		break;
					case TYPE_LOCKPICK:			str = "Pick Bonus:";		break;
					case TYPE_INSTRUMENT :		str = "Type:";				break;
					case TYPE_TOTEM :			str = "Spheres:";			break;
					case TYPE_SHIELD :			str = "Type:";				break;
					case TYPE_SUMMON:			str = "Target Room";		break;
					default :					str = "Unused:";			break; 
				}
			
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE1);
				text->SetWindowText(str);
				break;
			case 1:
				switch (obj_type) {
					case TYPE_POTION:
					case TYPE_SCROLL:			str = "Spell:";				break;
					case TYPE_WAND:
					case TYPE_STAFF:			str = "Max Charges:";		break;
					case TYPE_MISSILEWEAP:
					case TYPE_WEAPON:			str = "# Damage Dice:";		break;
					case TYPE_RANGED_WEAPON:	str = "Rate of Fire:";		break;
					case TYPE_CONTAINER:
					case TYPE_QUIVER:			str = "Flags:";				break;
					case TYPE_DRINK_CON:		str = "Drinks Left:";		break;
					case TYPE_KEY:				str = "Chance to Break:";	break;
					case TYPE_MONEY:			str = "Silver:";			break;
					case TYPE_VEHICLE:
					case TYPE_SHIP:				str = "Deck Room:";			break;
					case TYPE_TELEPORT:			str = "Command:";			break;
					case TYPE_SWITCH:			str = "Room With Exit:";	break;
					case TYPE_LOCKPICK:			str = "Chance to Break:";	break;
					case TYPE_INSTRUMENT:		str = "Level:";				break;
					case TYPE_SHIELD:			str = "Shape:";				break;
					case TYPE_SUMMON:			str = "Command";			break;
					default :					str = "Unused:";			break;
				}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE2);
				text->SetWindowText(str);

				break;
			case 2:
				switch (obj_type) {
					case TYPE_LIGHT :			str = "# Hours:";			break;
					case TYPE_POTION:
					case TYPE_SCROLL:			str = "Spell:";				break;
					case TYPE_WAND:
					case TYPE_STAFF:			str = "Charges Left:";		break;
					case TYPE_MISSILEWEAP:
					case TYPE_WEAPON:			str = "Damage Dice:";		break;
					case TYPE_CONTAINER:		str = "Key:";				break;
					case TYPE_DRINK_CON:		str = "Liquid:";			break;
					case TYPE_MONEY:			str = "Gold:";				break;
					case TYPE_VEHICLE:
					case TYPE_SHIP:				str = "Control Room:";		break;
					case TYPE_TELEPORT:			str = "# Charges:";			break;
					case TYPE_SWITCH:			str = "Exit Dir:";			break;
					case TYPE_QUIVER:			str = "Missile Type:";		break;
					case TYPE_INSTRUMENT:		str = "Break Chance:";		break;
					case TYPE_SPELLBOOK:		str = "Pages:";				break;
					case TYPE_SHIELD:			str = "Size:";				break;
					case TYPE_SPELLSCROLL:      str = "Spell:";				break;
					default:					str = "Unused:";			break;
				}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE3);
				text->SetWindowText(str);
				break;
			case 3:
				switch (obj_type) {
					case TYPE_POTION:
					case TYPE_WAND:
					case TYPE_STAFF:
					case TYPE_SCROLL:			str = "Spell:";				break;		
					case TYPE_RANGED_WEAPON:
					case TYPE_MISSILEWEAP:		str = "Missile Type:";		break;
					case TYPE_WEAPON:			str = "Damage Type:";		break;
					//case TYPE_ARMOR:			str = "Thickness:";			break;
					case TYPE_CONTAINER:		str = "Max Space:";			break;
					case TYPE_VEHICLE: 
					case TYPE_SHIP:				str = "Size:";				break;
					case TYPE_DRINK_CON:
					case TYPE_FOOD:				str = "Poison:";			break;
					case TYPE_MONEY:			str = "Platinum:";			break;
					case TYPE_SWITCH:			str = "Move Type:";			break;
					case TYPE_QUIVER:			str = "Cur Missiles:";		break;
					case TYPE_INSTRUMENT:		str = "Min Level:";			break;
					case TYPE_SHIELD:			str = "Armor Class:";		break;
					case TYPE_SPELLSCROLL:      str = "No Copy?";			break;
					default:					str = "Unused:";			break;
				}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE4);
				text->SetWindowText(str);
				break;
			case 4:
				switch (obj_type) {
					case TYPE_WEAPON:			str = "Poison Type";		break;
					//case TYPE_ARMOR:			str = "Flags";				break;
					case TYPE_POTION:			str = "Damage";				break;
					//case TYPE_VEHICLE:
					//case TYPE_SHIP:				str = "Max Speed";			break;
					//case TYPE_SHIELD:			str = "Thickness";			break;
					default :					str = "Unused:";			break;
				}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE5);
				text->SetWindowText(str);
				break;
			case 5:
				//switch (obj_type) {
					//case TYPE_SHIELD:			str = "Flags:";				break;
					//case TYPE_VEHICLE: 
					//case TYPE_SHIP:				str = "Hull Points:";		break;
				//	default:					str = "Unused:";			break;
				//}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE6);
				text->SetWindowText(str);
				break;
			case 6:
				//switch( obj_type ) {
					//case TYPE_VEHICLE:
					//case TYPE_SHIP:				str = "Firepower:";			break;
				//	default:					str = "Unused:";			break;
				//}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE7);
				text->SetWindowText(str);
				break;
			case 7:
			//	switch( obj_type ) {
					//case TYPE_VEHICLE:
					//case TYPE_SHIP:				str = "Cargo Capacity:";			break;
				//	default:					str = "Unused:";			break;
				//}
				
				text = (CWnd*)GetDlgItem(IDC_STATIC_VALUE8);
				text->SetWindowText(str);
				break;
		}
	}
}

void DlgEditObject::ValueInput(int obj_type)
{
	CEdit *ed;
	int i;
	int x = 0, y = 0;
	CComboBox *lb;
	CListBox *listbox;

	bool show_lb = false;
	bool show_flags = false;

	for(i = 0; i < MAX_ITEM_VALUE ;i++) 
	{
		switch(i) 
		{
		case 0:
			ed = (CEdit*)GetDlgItem(IDC_VALUE1);

			lb = (CComboBox*)GetDlgItem(IDC_VALUE1_LIST);
			listbox = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS0);
			listbox->ResetContent();
			lb->ResetContent();
			
			switch (obj_type) 
			{
			case TYPE_SCROLL:
			case TYPE_POTION:
			case TYPE_WAND:
			case TYPE_STAFF:
				show_lb = false;
				break;
			case TYPE_WEAPON:
				show_lb = true;
				for(y = 0; y < GetWeapCount(); y++)
				{
					lb->InsertString(y, weapon_types[y].name);
					lb->SetItemData(y, weapon_types[y].index);
				}
				break;
			case TYPE_SHIP:
			case TYPE_VEHICLE:	
				show_lb = true;
				for(y = 0; y < VEH_MAX; y++)
				{
					lb->InsertString(y, vehicle_types[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_SWITCH:
				show_lb = true;
				for(y = 0; y < CommandCount(); y++)
				{
					lb->InsertString(y, comm_types[y].name);
					lb->SetItemData(y, comm_types[y].index);
				}
				break;
			case TYPE_INSTRUMENT:
				show_lb = true;
				for(y = 0; y < InstrumentCount(); y++)
				{
					lb->InsertString(y, instrument_types[y].name);
					lb->SetItemData(y, instrument_types[y].index);
				}
				break;
			case TYPE_TOTEM :
				show_lb = false;
				show_flags = true;
				for(y = 0; y < TotemCount(); y++)
				{
					listbox->InsertString(y, totem_types[y].name);
					listbox->SetItemData(y, totem_types[y].index);
				}
				break;
			case TYPE_SHIELD :
				show_lb = true;
				for(y = 0; y < SHIELDTYPE_MAX; y++)
				{
					lb->InsertString(y, shield_types[y]);
					lb->SetItemData(y, y);
				}
				break;
		
			default:	
				show_lb = false;
				break;
			}
			
			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);
				listbox->ShowWindow(SW_HIDE);
			}
			else if(show_flags)
			{	
				ed->ShowWindow(SW_HIDE);
				lb->ShowWindow(SW_HIDE);
				listbox->ShowWindow(SW_SHOW);
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
				listbox->ShowWindow(SW_HIDE);
			}
			
			show_lb = false;
			show_flags = false;
			lb->SetCurSel(0);
			
			break;
		case 1:
			ed = (CEdit*)GetDlgItem(IDC_VALUE2);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE2_LIST);
			listbox = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS1);
			listbox->ResetContent();
			lb->ResetContent();
			
			switch (obj_type) 
			{
			case TYPE_POTION:
			case TYPE_SCROLL:			
				show_lb = true;
				
				for(y = 0; y < SPELL_HIGHEST; y++)
				{
					if(spells[y].Active())
					{
						lb->InsertString(x, spells[y].SpellName());
						lb->SetItemData(x, spells[y].Id());
						x++;
					}
				}
				
				x = 0;
				break;
			case TYPE_CONTAINER:
			case TYPE_QUIVER:			
				show_lb = false;
				show_flags = true;
				for(y = 0; y < ContainerCount(); y++)
				{
					listbox->InsertString(y, cont_types[y].name);
					listbox->SetItemData(y, cont_types[y].index);
				}
				break;
			case TYPE_TELEPORT:			
				show_lb = true;
				for(y = 0; y < CommandCount(); y++)
				{
					lb->InsertString(y, comm_types[y].name);
					lb->SetItemData(y, comm_types[y].index);
				}
				break;
			case TYPE_SHIELD:			
				show_lb = true;
				for(y = 0; y < SHIELDSHAPE_MAX; y++)
				{
					lb->InsertString(y, shield_shape[y]);
					lb->SetItemData(y, y);
				}
				break;	
			case TYPE_SUMMON:
				show_lb = true;
				for(y = 0; y < CommandCount(); y++)
				{
					lb->InsertString(y, comm_types[y].name);
					lb->SetItemData(y, comm_types[y].index);
				}
				break;
			default:
				show_lb = false;
				break;
			}

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);
				
				listbox->ShowWindow(SW_HIDE);
			}
			else if(show_flags)
			{	
				ed->ShowWindow(SW_HIDE);
				lb->ShowWindow(SW_HIDE);
				listbox->ShowWindow(SW_SHOW);
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
				listbox->ShowWindow(SW_HIDE);
			}
			show_lb = false;
			show_flags = false;
			lb->SetCurSel(0);
			
			break;
		case 2:
			ed = (CEdit*)GetDlgItem(IDC_VALUE3);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE3_LIST);
			
			lb->ResetContent();
			
			switch (obj_type) 
			{		
			case TYPE_POTION:
			case TYPE_SCROLL:			
				show_lb = true;
				x=0;
				for(y = 0; y < SPELL_HIGHEST; y++)
				{
					if(spells[y].Active())
					{
						lb->InsertString(x, spells[y].SpellName());
						lb->SetItemData(x, spells[y].Id());
						x++;
					}
				}
				
				x = 0;
				break;
			case TYPE_DRINK_CON:
				show_lb = true;
				for(y = 0; y < LIQ_MAX; y++)
				{
					lb->InsertString(y, liquid_types[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_SWITCH:
				show_lb = true;
				for(y = 0; y < MAX_DIR; y++)
				{
					lb->InsertString(y, dir_name[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_QUIVER:			
				show_lb = true;
				for(y = 0; y < MISSILE_MAX; y++)
				{
					lb->InsertString(y, missile_types[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_SHIELD:
				show_lb = true;
				for(y = 0; y < SHIELDSIZE_MAX; y++)
				{
					lb->InsertString(y, shield_size[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_SPELLSCROLL:
				show_lb = true;
				x=0;
				for(y = 0; y < SPELL_HIGHEST; y++)
				{
					if(spells[y].Active())
					{
						lb->InsertString(x, spells[y].SpellName());
						lb->SetItemData(x, spells[y].Id());
						x++;
					}
				}
				
				x = 0;
				break;
			default:
				show_lb = false;
				break;
			}

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);

				show_lb = false;
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
			}
			
			lb->SetCurSel(0);

			break;
		case 3:
			ed = (CEdit*)GetDlgItem(IDC_VALUE4);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE4_LIST);
			
			lb->ResetContent();
			
			switch (obj_type) {
			case TYPE_SHIP:
			case TYPE_VEHICLE:
				for(y = 0; y < SHIP_MAX; y++)
				{
					lb->InsertString(y, ship_types[y].name);
					lb->SetItemData(y, ship_types[y].index);
				}
				show_lb = true;
				break;
			case TYPE_POTION:
			case TYPE_WAND:
			case TYPE_STAFF:
			case TYPE_SCROLL:			
				show_lb = true;
				
				for(y = 0; y < SPELL_HIGHEST; y++)
				{
					if(spells[y].Active())
					{
						lb->InsertString(x, spells[y].SpellName());
						lb->SetItemData(x, spells[y].Id());
						x++;
					}
				}
				
				x = 0;
				break;		
			case TYPE_RANGED_WEAPON:
			case TYPE_MISSILEWEAP:	
				for(y = 0; y < MISSILE_MAX; y++)
				{
					lb->InsertString(y, missile_types[y]);
					lb->SetItemData(y, y);
				}	
				show_lb = true;
				break;
			case TYPE_WEAPON:			
				show_lb = true;
				for(y = 0; y < DAM_MAX; y++)
				{
					lb->InsertString(y, dam_types[y]);
					lb->SetItemData(y, y);
				}
				break;
			case TYPE_ARMOR:		
				show_lb = false;
				break;
			case TYPE_DRINK_CON:
			case TYPE_FOOD:			
				show_lb = false;
				break;
			case TYPE_SWITCH:	
				show_lb = false;
				break;
			default:
				show_lb = false;
				break;
			}

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);

				show_lb = false;
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
			}
			
			lb->SetCurSel(0);
			break;
		case 4:
			ed = (CEdit*)GetDlgItem(IDC_VALUE5);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE5_LIST);
			
			lb->ResetContent();
			
			switch (obj_type) {
			case TYPE_WEAPON:		
				show_lb = false;
				break;
			case TYPE_ARMOR:			
				show_lb = false;
				break;
			case TYPE_SHIELD:			
				show_lb = false;
				break;
			default:
				show_lb = false;
				break;
			}

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);

				show_lb = false;
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
			}
			break;
		case 5:
			ed = (CEdit*)GetDlgItem(IDC_VALUE6);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE6_LIST);
			listbox = (CListBox*)GetDlgItem(IDC_VALUE_FLAGS5);
			listbox->ResetContent();
			
			lb->ResetContent();
			
			switch (obj_type) {
			case TYPE_SHIELD:			
				show_lb = false;
				break;
			default:
				show_lb = false;
				break;
			}

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);
				listbox->ShowWindow(SW_HIDE);
					
			}
			else if(show_flags)
			{	
				ed->ShowWindow(SW_HIDE);
				lb->ShowWindow(SW_HIDE);
				listbox->ShowWindow(SW_SHOW);
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
				listbox->ShowWindow(SW_HIDE);
			}
			show_lb = false;
			show_flags = false;
			break;
		case 6:
			ed = (CEdit*)GetDlgItem(IDC_VALUE7);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE7_LIST);
			lb->ResetContent();

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);

				show_lb = false;
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
			}
			break;
		case 7:
			ed = (CEdit*)GetDlgItem(IDC_VALUE8);
			lb = (CComboBox*)GetDlgItem(IDC_VALUE8_LIST);
			lb->ResetContent();

			if(show_lb) 
			{
				ed->ShowWindow(SW_HIDE);
				
				lb->ShowWindow(SW_SHOW);
				lb->EnableWindow(true);

				show_lb = false;
			}
			else
			{
				lb->ShowWindow(SW_HIDE);
				ed->ShowWindow(SW_SHOW);
			}
			break;
		}
	}

}

void DlgEditObject::OnTrap() 
{
	DlgEditTrap dlg_trap(this);

	dlg_trap.obj = object;

	dlg_trap.DoModal();
}

void DlgEditObject::OnEditProgs() 
{
	ProgEditor dlg_prog(this);

	dlg_prog.type = OBJECT;
	dlg_prog.obj = object;

	dlg_prog.DoModal();
}
