// WinDE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinDE.h"
#include "WinDEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinDEApp

BEGIN_MESSAGE_MAP(CWinDEApp, CWinApp)
	//{{AFX_MSG_MAP(CWinDEApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinDEApp construction

CWinDEApp::CWinDEApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWinDEApp object

CWinDEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWinDEApp initialization

BOOL CWinDEApp::InitInstance()
{
	AfxEnableControlContainer();
	
	InitCommonControls();    // initialize common control library
	
	CWinApp::InitInstance(); // call parent class method

#ifdef _AFXDLL
  Enable3dControls();      // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif

	m_haccel=LoadAccelerators(AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDR_MAINFRAME));

	CWinDEDlg dlg;

	m_pMainWnd = &dlg;
	
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CWinDEApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	if(m_haccel)
	{
		if (::TranslateAccelerator(m_pMainWnd->m_hWnd, m_haccel, lpMsg)) 
			return(TRUE);
	}
	
    return CWinApp::ProcessMessageFilter(code, lpMsg);
}
