#include "stdafx.h"
#include "WinDE.h"
#include "DlgEditShop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgEditShop::DlgEditShop(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditShop::IDD, pParent)
{
	shop = NULL;

	//{{AFX_DATA_INIT(DlgEditShop)
	buy_profit = 100;
	closes = 24;
	opens = 1;
	sale_profit = 100;
	//}}AFX_DATA_INIT
}

void DlgEditShop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditShop)
	DDX_Control(pDX, IDC_LIST1, m_ShopList);
	DDX_Text(pDX, IDC_BUY_PROFIT, buy_profit);
	DDX_Text(pDX, IDC_CLOSES, closes);
	DDV_MinMaxInt(pDX, closes, 1, 24);
	DDX_Text(pDX, IDC_OPENS, opens);
	DDV_MinMaxInt(pDX, opens, 1, 24);
	DDX_Text(pDX, IDC_SELL_PROFIT, sale_profit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEditShop, CDialog)
	//{{AFX_MSG_MAP(DlgEditShop)
	ON_BN_CLICKED(IDC_ADD_ITEM, OnAddItem)
	ON_BN_CLICKED(IDC_DELETE_SHOP, OnDeleteShop)
	ON_LBN_SELCHANGE(IDC_TYPE_LIST, OnSelchangeTypeList)
	ON_BN_CLICKED(IDC_REMOVE_ITEM, OnRemoveItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgEditShop::OnOK() 
{	
	CListBox* lb;
	int i[MAX_BUY], x;

	UpdateData(true);
	
	shop->profit_buy = buy_profit;
	shop->close_hour = closes;
	shop->open_hour = opens;
	shop->profit_sell = sale_profit;
	
	lb = (CListBox*)GetDlgItem(IDC_TYPE_LIST);
	
	lb->GetSelItems(MAX_BUY, i);

	for(x=0; x < MAX_BUY; x++)
		shop->buy_type[x] = lb->GetItemData(i[x]);

	for(x = 0; x < MAX_SELL; x++) {
		if(x < m_ShopList.GetItemCount())
			shop->sell_item[x] = m_ShopList.GetItemData(x);
		else 
			shop->sell_item[x] = -1;
	}

	UpdateData(false);

	CDialog::OnOK();
}

void DlgEditShop::OnDeleteShop() 
{
	shop->RemoveFromList();

	delete shop;

	shop = NULL;

	shop_count--;

	CDialog::OnOK();
}

void DlgEditShop::OnCancel() 
{	
	CDialog::OnCancel();
}

BOOL DlgEditShop::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i, x;
	object_data *obj;
	CString str;
	CRect rect;
	UpdateData(true);

	buy_profit = shop->profit_buy;
	closes = shop->close_hour;
	opens = shop->open_hour;
	sale_profit = shop->profit_sell;

	CListBox* lb = (CListBox*)GetDlgItem(IDC_TYPE_LIST);
	
	for(i = TYPE_NONE, x = 0; i < MAX_ITEM_TYPE; i++, x++) {
		if(item_types[i].sellable) {
			lb->InsertString(x, item_types[i].name);
			lb->SetItemData(x, i);
		} else x--;
	}
	
	for(i = 0; i < lb->GetCount(); i++) {
		for(x = 0; x< MAX_BUY;x++)
			if(lb->GetItemData(i) == (DWORD)shop->buy_type[x])
				lb->SetSel(i);
	}
	
	lb = (CListBox*)GetDlgItem(IDC_SALE_ITEMS);
	
	DWORD dwStyle = ::SendMessage(m_ShopList, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); 

	dwStyle |= LVS_EX_FULLROWSELECT; 

	::SendMessage(m_ShopList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
	
	m_ShopList.GetClientRect(rect);
	m_ShopList.InsertColumn(0, "Vnum", LVCFMT_LEFT, rect.Width()/5);
	m_ShopList.InsertColumn(1, "Name", LVCFMT_LEFT, rect.Width()-(rect.Width()/5));

	for(i = 0; i < MAX_SELL; i++) {
		if((obj = GetObjByVnum(shop->sell_item[i])))
		{
			str.Format("%d", obj->vnum);
			m_ShopList.InsertItem(i, str, 0);
			m_ShopList.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
			m_ShopList.SetItemData(i, shop->sell_item[i]);
		}
		else if(shop->sell_item[i] > -1)
		{
			str.Format("%d", shop->sell_item[i]);
			m_ShopList.InsertItem(i, str, 0);
			m_ShopList.SetItem(i, 1, LVIF_TEXT, "A non-existant object", 1, 0, 0, 0);
			m_ShopList.SetItemData(i, shop->sell_item[i]);
		}
	}

	UpdateData(false);
	
	return TRUE;
}

void DlgEditShop::OnSelchangeTypeList() 
{	
	CListBox* lb;
	CString str;
	
	lb = (CListBox*)GetDlgItem(IDC_TYPE_LIST);	

	if(lb->GetSelCount() > MAX_BUY) {
		str.Format("Shops can sell a max of %d item types",  MAX_BUY);
		MessageBox(str, "Sale Item Max");
		lb->SetSel(lb->GetCurSel(), false);
	}
}

void DlgEditShop::OnAddItem() 
{
	DlgEnterVnum dlg(this);
	CString str;
	object_data *obj;
	int i, ret;

	if(m_ShopList.GetItemCount() == MAX_SELL) {
		str.Format("Shops can sell %d items", MAX_SELL);
		MessageBox(str);
	} else {
		dlg.type = OBJECT;

		ret = dlg.DoModal();

		if(ret == IDOK) {
			i = m_ShopList.GetItemCount();

			if((obj = GetObjByVnum(dlg.vnum)))
			{
				str.Format("%d", obj->vnum);
				m_ShopList.InsertItem(i, str, 0);
				m_ShopList.SetItem(i, 1, LVIF_TEXT, StripAnsiChars(obj->short_descr), 1, 0, 0, 0);
				m_ShopList.SetItemData(i, obj->vnum);
			}
			else
			{
				str.Format("%d", dlg.vnum);
				m_ShopList.InsertItem(i, str, 0);
				m_ShopList.SetItem(i, 1, LVIF_TEXT, "A non-existant object.", 1, 0, 0, 0);
				m_ShopList.SetItemData(i, dlg.vnum);
			
			}
		}
	}
}

void DlgEditShop::OnRemoveItem() 
{
	int i;
	POSITION pos;

	pos = m_ShopList.GetFirstSelectedItemPosition();
	i = m_ShopList.GetNextSelectedItem(pos);

	if(i > -1)
		m_ShopList.DeleteItem(i);
	else
		MessageBox("Please select an item to remove.");
}
