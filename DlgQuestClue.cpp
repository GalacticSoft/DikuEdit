// DlgQuestClue.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "DlgQuestClue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgQuestClue dialog


DlgQuestClue::DlgQuestClue(CWnd* pParent /*=NULL*/)
	: CDialog(DlgQuestClue::IDD, pParent)
{
	clue = NULL;
	//{{AFX_DATA_INIT(DlgQuestClue)
	keywords = _T("");
	message = _T("");
	//}}AFX_DATA_INIT
}


void DlgQuestClue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgQuestClue)
	DDX_Text(pDX, IDC_KEYWORDS, keywords);
	DDX_Text(pDX, IDC_MESSAGE, message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgQuestClue, CDialog)
	//{{AFX_MSG_MAP(DlgQuestClue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgQuestClue message handlers

void DlgQuestClue::OnOK() 
{
	UpdateData(true);
	
	if(clue)
	{
		clue->keywords = keywords;
		clue->message = message;
	}
	
	CDialog::OnOK();
}

BOOL DlgQuestClue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(clue)
	{
		keywords = clue->keywords;
		message = clue->message;

		UpdateData(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
