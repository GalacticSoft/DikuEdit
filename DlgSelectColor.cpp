// DlgSelectColor.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgSelectColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSelectColor dialog


DlgSelectColor::DlgSelectColor(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSelectColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSelectColor)
	m_def_dim = FALSE;
	m_echo_dim = FALSE;
	//}}AFX_DATA_INIT
}


void DlgSelectColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSelectColor)
	DDX_Check(pDX, IDC_DEF_DIM, m_def_dim);
	DDX_Check(pDX, IDC_ECHO_DIM, m_echo_dim);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSelectColor, CDialog)
	//{{AFX_MSG_MAP(DlgSelectColor)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_DEF_COLOR, OnClickDefColor)
	ON_NOTIFY(NM_CLICK, IDC_ECHO_COLOR, OnClickEchoColor)
	ON_BN_CLICKED(IDC_ECHO_DIM, OnEchoDim)
	ON_BN_CLICKED(IDC_DEF_DIM, OnDefDim)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSelectColor message handlers

BOOL DlgSelectColor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CBitmap bm;
	CListCtrl *def;
	CListCtrl *echo;

	iml.Create(IDB_BLACK, 24, 0, white);

	bm.LoadBitmap(IDB_WHITE);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_RED);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_BLUE);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_GREEN);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_YELLOW);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_MAGENTA);
	iml.Add(&bm, white);
	bm.DeleteObject();

	bm.LoadBitmap(IDB_CYAN);
	iml.Add(&bm, white);
	bm.DeleteObject();

	def = (CListCtrl*)GetDlgItem(IDC_DEF_COLOR);
	def->SetImageList(&iml, LVSIL_NORMAL);
	
	def->InsertItem(0, "Black", 0);
	def->InsertItem(1, "White", 1);
	def->InsertItem(2, "Red", 2);
	def->InsertItem(3, "Blue", 3);
	def->InsertItem(4, "Green", 4);
	def->InsertItem(5, "Yellow", 5);
	def->InsertItem(6, "Magenta", 6);
	def->InsertItem(7, "Cyan", 7);
	
	switch(def_color) {
	case gray:
		m_def_dim = true;
		def->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(0, FALSE);
		break;
	case lightgrey:
		m_def_dim = true;
	case white:
		def->SetItemState(1, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(1, FALSE);
		break;
	case darkred:
		m_def_dim = true;
	case red:
		def->SetItemState(2, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(2, FALSE);
		break;
	case darkblue:
		m_def_dim = true;
	case blue:
		def->SetItemState(3, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(3, FALSE);
		break;
	case green:
		m_def_dim = true;
	case lawngreen:
		def->SetItemState(4, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(4, FALSE);
		break;
	case peru:
		m_def_dim = true;
	case yellow:
		def->SetItemState(5, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(5, FALSE);
		break;
	case darkmagenta:
		m_def_dim = true;
	case magenta:
		def->SetItemState(6, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(6, FALSE);
		break;
	case darkcyan:
		m_def_dim = true;
	case cyan:
		def->SetItemState(7, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		def->EnsureVisible(7, FALSE);
		break;
	}

	echo = (CListCtrl*)GetDlgItem(IDC_ECHO_COLOR);
	echo->SetImageList(&iml, LVSIL_NORMAL);
	
	echo->InsertItem(0, "Black", 0);
	echo->InsertItem(1, "White", 1);
	echo->InsertItem(2, "Red", 2);
	echo->InsertItem(3, "Blue", 3);
	echo->InsertItem(4, "Green", 4);
	echo->InsertItem(5, "Yellow", 5);
	echo->InsertItem(6, "Magenta", 6);
	echo->InsertItem(7, "Cyan", 7);

	switch(echo_color) {
	case gray:
		m_echo_dim = true;
		echo->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(0, FALSE);
		break;
	case lightgrey:
		m_echo_dim = true;
	case white:
		echo->SetItemState(1, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(1, FALSE);
		break;
	case darkred:
		m_echo_dim = true;
	case red:
		echo->SetItemState(2, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(2, FALSE);
		break;
	case darkblue:
		m_echo_dim = true;
	case blue:
		echo->SetItemState(3, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(3, FALSE);
		break;
	case green:
		m_echo_dim = true;
	case lawngreen:
		echo->SetItemState(4, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(4, FALSE);
		break;
	case peru:
		m_echo_dim = true;
	case yellow:
		echo->SetItemState(5, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(5, FALSE);
		break;
	case darkmagenta:
		m_echo_dim = true;
	case magenta:
		echo->SetItemState(6, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(6, FALSE);
		break;
	case darkcyan:
		m_echo_dim = true;
	case cyan:
		echo->SetItemState(7, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		echo->EnsureVisible(7, FALSE);
		break;
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSelectColor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void DlgSelectColor::OnClickDefColor(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
}

void DlgSelectColor::OnClickEchoColor(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
}

void DlgSelectColor::OnEchoDim() 
{
	
}

void DlgSelectColor::OnDefDim() 
{
	
}

void DlgSelectColor::OnOK() 
{
	CListCtrl *def;
	CListCtrl *echo;
	POSITION pos;
	int i;
	
	UpdateData(true);

	def = (CListCtrl*)GetDlgItem(IDC_DEF_COLOR);
	echo = (CListCtrl*)GetDlgItem(IDC_ECHO_COLOR);
	
	pos = def->GetFirstSelectedItemPosition();
	i = def->GetNextSelectedItem(pos);
	if(m_def_dim) {
		switch(i) {
			case 0: def_color = gray;			break;
			case 1: def_color = lightgrey;		break;
			case 2: def_color = darkred;		break;
			case 3:	def_color = darkblue;		break;
			case 4: def_color = green;			break;
			case 5: def_color = peru;			break;
			case 6: def_color = darkmagenta;	break;
			case 7: def_color = darkcyan;		break;
		}
	} else {
		switch(i) {
			case 0: def_color = gray;			break;
			case 1: def_color = white;			break;
			case 2: def_color = red;			break;
			case 3:	def_color = blue;			break;
			case 4: def_color = lawngreen;		break;
			case 5: def_color = yellow;			break;
			case 6: def_color = magenta;		break;
			case 7: def_color = cyan;			break;
		}
	}

	pos = echo->GetFirstSelectedItemPosition();
	i = echo->GetNextSelectedItem(pos);
	if(m_echo_dim) {
		switch(i) {
			case 0: echo_color = gray;			break;
			case 1: echo_color = lightgrey;		break;
			case 2: echo_color = darkred;		break;
			case 3:	echo_color = darkblue;		break;
			case 4: echo_color = green;			break;
			case 5: echo_color = peru;			break;
			case 6: echo_color = darkmagenta;	break;
			case 7: echo_color = darkcyan;		break;
		}
	} else {
		switch(i) {
			case 0: echo_color = gray;			break;
			case 1: echo_color = white;			break;
			case 2: echo_color = red;			break;
			case 3:	echo_color = blue;			break;
			case 4: echo_color = lawngreen;		break;
			case 5: echo_color = yellow;		break;
			case 6: echo_color = magenta;		break;
			case 7: echo_color = cyan;			break;
		}
	}

	CDialog::OnOK();
}
