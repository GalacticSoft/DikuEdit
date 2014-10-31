// WinDE.h : main header file for the WINDE application
//

#if !defined(AFX_WINDE_H__EE9EA094_4CFF_424E_A6E4_E859677488B2__INCLUDED_)
#define AFX_WINDE_H__EE9EA094_4CFF_424E_A6E4_E859677488B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinDEApp:
// See WinDE.cpp for the implementation of this class
//

class CWinDEApp : public CWinApp
{
public:
	CWinDEApp();
	HACCEL m_haccel;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinDEApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinDEApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDE_H__EE9EA094_4CFF_424E_A6E4_E859677488B2__INCLUDED_)
