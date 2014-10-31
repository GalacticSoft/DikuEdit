#include "stdafx.h"
#include "WinDE.h"
#include "DlgRoomFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DlgRoomFlags::DlgRoomFlags(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRoomFlags::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRoomFlags)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgRoomFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRoomFlags)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgRoomFlags, CDialog)
	//{{AFX_MSG_MAP(DlgRoomFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DlgRoomFlags::CheckRoomFlags()
{
	CButton *b;
	int i;

	for(i = 0; i < MaxRoomFlags; i++) {
		b = (CButton *)GetDlgItem(room_flags_info[i].button);
		if(b->GetCheck()) {
			if(!room->RoomIsSet(*room_flags_info[i].bv))
			room->SetRoomBit(*room_flags_info[i].bv);
			b->SetCheck(false);
		} else {
			if(room->RoomIsSet(*room_flags_info[i].bv)) {
				room->RemoveRoomBit(*room_flags_info[i].bv);
			}
		}
	}
} 

void DlgRoomFlags::SetRoomFlags()
{
	CButton *b;
	int i;
	
	for(i = 0; i < MaxRoomFlags; i++) {
		b = (CButton *)GetDlgItem(room_flags_info[i].button);
		if(room->RoomIsSet(*room_flags_info[i].bv))
			b->SetCheck(true);
	}
}

void DlgRoomFlags::OnOK() 
{	
	CheckRoomFlags();

	CDialog::OnOK();
}

BOOL DlgRoomFlags::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetRoomFlags();

	return TRUE;
}
