#if !defined(AFX_DLGSETTINGS_H__27BB4A4C_A0B3_4C48_9397_650E0776762E__INCLUDED_)
#define AFX_DLGSETTINGS_H__27BB4A4C_A0B3_4C48_9397_650E0776762E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSettings dialog

class DlgSettings : public CDialog
{
// Construction
public:
	DlgSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSettings)
	enum { IDD = IDD_SETTINGS };
	BOOL	m_auto_save;
	int		m_open_format;
	BOOL	m_walk_create;
	BOOL    m_echo_commands;
	int		m_timer;
	BOOL	m_save_exit;
	int		m_save_format;
	BOOL	m_disp_line_len;
	//}}AFX_DATA
	COLORREF def_color;
	COLORREF echo_color;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSettings)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSettings)
	afx_msg void OnAutoSave();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeOpenFormat();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGS_H__27BB4A4C_A0B3_4C48_9397_650E0776762E__INCLUDED_)
