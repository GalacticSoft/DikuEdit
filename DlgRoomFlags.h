#if !defined(AFX_DLGROOMFLAGS_H__5865AF7F_80DD_490B_8B74_34B9BBF77D06__INCLUDED_)
#define AFX_DLGROOMFLAGS_H__5865AF7F_80DD_490B_8B74_34B9BBF77D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DlgRoomFlags : public CDialog
{
// Construction
public:
	DlgRoomFlags(CWnd* pParent = NULL);   // standard constructor

	room_data *room;

// Dialog Data
	//{{AFX_DATA(DlgRoomFlags)
	enum { IDD = IDD_ROOM_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRoomFlags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	void CheckRoomFlags();
	void SetRoomFlags();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgRoomFlags)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_DLGROOMFLAGS_H__5865AF7F_80DD_490B_8B74_34B9BBF77D06__INCLUDED_)
