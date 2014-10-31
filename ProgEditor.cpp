// ProgEditor.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "ProgEditor.h"
#include "Progs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgEditor dialog


ProgEditor::ProgEditor(CWnd* pParent /*=NULL*/)
	: CDialog(ProgEditor::IDD, pParent)
{
	prog = NULL;

	//{{AFX_DATA_INIT(ProgEditor)
	filename = _T("");
	//}}AFX_DATA_INIT
}


void ProgEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProgEditor)
	DDX_Control(pDX, IDC_VARS, vars);
	DDX_Control(pDX, IDC_TEMPLATE, templates);
	DDX_Control(pDX, IDC_PROG_TYPE, prog_types);
	DDX_Control(pDX, IDC_KEYWORDS, keywords);
	DDX_Control(pDX, IDC_FUNCTIONS, functions);
	DDX_Control(pDX, IDC_COMMANDS, commands);
	DDX_Control(pDX, IDC_FRAME_RECT, frameRect);
	DDX_Text(pDX, IDC_FNAME, filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProgEditor, CDialog)
	//{{AFX_MSG_MAP(ProgEditor)
	ON_CBN_SELCHANGE(IDC_COMMANDS, OnSelchangeCommands)
	ON_CBN_SELCHANGE(IDC_KEYWORDS, OnSelchangeKeywords)
	ON_CBN_SELCHANGE(IDC_FUNCTIONS, OnSelchangeFunctions)
	ON_CBN_SELCHANGE(IDC_VARS, OnSelchangeVars)
	ON_CBN_SELCHANGE(IDC_TEMPLATE, OnSelchangeTemplate)
	ON_CBN_SELCHANGE(IDC_PROG_TYPE, OnSelchangeProgType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgEditor message handlers

BOOL ProgEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect frame;
	int i;

	frameRect.GetWindowRect(frame);
	ScreenToClient(frame);

	prog_editor = new ProgEditWnd(this, frame,	IDD_PROG_EDIT, 4, 100, "Terminal", true);

	prog_editor->SetParent(this);
	prog_editor->SetCharXSpacing(1);
	prog_editor->SetColorizer(&m_colorizer);
	prog_editor->SetReadOnly(false);
	prog_editor->ClearUndoHistory();

	for(i = 0; i < ProgCount(); i++)
		prog_types.InsertString(i, progs[i].name);

	for(i = 0; i < ProgCommCount(); i++)
		commands.InsertString(i, prog_comms[i]);

	for(i = 0; i < ProgKeywordCount(); i++)
		keywords.InsertString(i, progkeywords[i]);

	for(i = 0; i < ProgFuncCount(); i++)
		functions.InsertString(i, prog_funcs[i]);

	for(i = 0; i < VarCount(); i++)
		vars.InsertString(i, prog_vars[i]);

	for(i = 0; i < max_template; i++)
		templates.InsertString(i, prog_templates[i]);
	
	if(type == MOBILE)
	{
		if((prog = area_data::area->progs.GetProg(mob)))
		{
			prog_editor->ReplaceSelText(prog->prog_text);
		}
		else
		{
			prog = new ProgFile();
			prog->type = MOBILE;
			prog->mob = mob;
			prog->filename = mob->name + ".prg";
			area_data::area->progs.AddProg(prog);
		}
	}
	else if(type == OBJECT)
	{
		if((prog = area_data::area->progs.GetProg(obj)))
		{
			prog_editor->ReplaceSelText(prog->prog_text);
		}
		else
		{
			prog = new ProgFile();
			prog->type = OBJECT;
			prog->obj = obj;
			prog->filename = obj->name + ".prg";
			area_data::area->progs.AddProg(prog);
		}
	}

	filename = prog->filename;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ProgEditor::OnSelchangeCommands() 
{
	if(commands.GetCurSel() > -1)
	{
		prog_editor->ReplaceSelText(prog_comms[commands.GetCurSel()]);
		commands.SetCurSel(-1);
	}
}

void ProgEditor::OnSelchangeKeywords() 
{
	if(keywords.GetCurSel() > -1)
	{
		prog_editor->ReplaceSelText(progkeywords[keywords.GetCurSel()]);
		keywords.SetCurSel(-1);
	}
}

void ProgEditor::OnSelchangeFunctions() 
{
	if(functions.GetCurSel() > -1)
	{
		prog_editor->ReplaceSelText(prog_funcs[functions.GetCurSel()]);
		functions.SetCurSel(-1);
	}
}

void ProgEditor::OnSelchangeVars() 
{
	if(vars.GetCurSel() > -1)
	{
		prog_editor->ReplaceSelText(prog_vars[vars.GetCurSel()]);
		vars.SetCurSel(-1);
	}
}

void ProgEditor::OnSelchangeTemplate() 
{
	if(templates.GetCurSel() > -1)
	{
		switch(templates.GetCurSel())
		{
		case greet_prog:
			InsertGreetTemplate();
			break;
		case act_prog:
			InsertActTemplate();
			break;
		case fight_prog:
			InsertFightTemplate();
			break;
		case bribe_prog:
			InsertBribeTemplate();
			break;
		case death_prog:
			InsertDeathTemplate();
			break;
		case hitpercent_prog:
			InsertHPPercentTemplate();
			break;
		case speech_prog:
			InsertSpeechTemplate();
			break;
		case rand_prog:
			InsertRandTemplate();
			break;
		case move_prog:
			InsertMoveTemplate();
			break;
		}

		templates.SetCurSel(-1);
	}
}

void ProgEditor::OnSelchangeProgType() 
{
	if(prog_types.GetCurSel() > -1)
	{
		prog_editor->ReplaceSelText(">");
		prog_editor->ReplaceSelText(progs[prog_types.GetCurSel()].name);
		prog_types.SetCurSel(-1);
	}
}

void ProgEditor::InsertBribeTemplate()
{
	prog_editor->ReplaceSelText(">bribe_prog 1~\n");
	prog_editor->ReplaceSelText("	thank $n\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::InsertGreetTemplate()
{
	prog_editor->ReplaceSelText(">greet_prog 100~\n");
	prog_editor->ReplaceSelText("	if ispc($n)\n");
	prog_editor->ReplaceSelText("		beg $n\n");	
	prog_editor->ReplaceSelText("		say Spare some gold?\n");
	prog_editor->ReplaceSelText("	endif\n");
	prog_editor->ReplaceSelText("~\n");
}

void ProgEditor::InsertFightTemplate()
{
	prog_editor->ReplaceSelText(">fight_prog 50~\n");
	prog_editor->ReplaceSelText("	say Help!  Please somebody help me!\n");
	prog_editor->ReplaceSelText("	if rand(50)\n");	
	prog_editor->ReplaceSelText("		say Ouch!\n");
	prog_editor->ReplaceSelText("	else\n");
	prog_editor->ReplaceSelText("		say I'm bleeding.\n");
	prog_editor->ReplaceSelText("	endif\n");
	prog_editor->ReplaceSelText("~\n");
}

void ProgEditor::InsertDeathTemplate()
{
	prog_editor->ReplaceSelText(">death_prog 50~\n");
	prog_editor->ReplaceSelText("	if rand(50)\n");
	prog_editor->ReplaceSelText("		mpechoaround $i $I says 'Now I go to a better place.'\n");	
	prog_editor->ReplaceSelText("	else\n");
	prog_editor->ReplaceSelText("		mpechoaround $i $I says 'Forgive me God for I have sinned...'\n");
	prog_editor->ReplaceSelText("	endif\n");
	prog_editor->ReplaceSelText("~\n");
}

void ProgEditor::InsertRandTemplate()
{
	prog_editor->ReplaceSelText(">rand_prog 50~\n");
	prog_editor->ReplaceSelText("	dance $n\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::InsertHPPercentTemplate()
{
	prog_editor->ReplaceSelText(">hitprcnt_prog 50~\n");
	prog_editor->ReplaceSelText("	if rand(50)\n");
	prog_editor->ReplaceSelText("		berserk\n");
	prog_editor->ReplaceSelText("	else\n");
	prog_editor->ReplaceSelText("		flee\n");
	prog_editor->ReplaceSelText("	endif\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::InsertMoveTemplate()
{
	prog_editor->ReplaceSelText(">move_prog 1200~\n");
	prog_editor->ReplaceSelText("	..nneewwss\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::InsertSpeechTemplate()
{
	prog_editor->ReplaceSelText(">speech_prog p hello hi~\n");
	prog_editor->ReplaceSelText("	greet $n\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::InsertActTemplate()
{
	prog_editor->ReplaceSelText(">act_prog p enters from the~\n");
	prog_editor->ReplaceSelText("	greet $n\n");
	prog_editor->ReplaceSelText("~\n");	
}

void ProgEditor::OnOK() 
{
	CDialog::OnOK();
	
	UpdateData(true);

	if(prog)
	{
		if(prog_editor->GetLineCount() == 0)
			return;

		prog->prog_text = "";

		for(int i = 0; i < prog_editor->GetLineCount(); i++)
		{
			prog->prog_text += prog_editor->GetLine(i);
			
			if(!prog->prog_text.IsEmpty() || prog->prog_text.GetLength() > 0)
				prog->prog_text += "\n";
		}

		prog->filename = filename;
	}
	
	if(prog->prog_text.IsEmpty() || prog->prog_text.GetLength() <= 0)
		DeleteFile("./Progs/" + prog->filename);
}
