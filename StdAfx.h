// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6BF7E700_87CF_480F_AE43_67DD85365E29__INCLUDED_)
#define AFX_STDAFX_H__6BF7E700_87CF_480F_AE43_67DD85365E29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <fstream>
using namespace std;
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "Resource.h"

#include "WinDE.h"

#include "WinDeDlg.h"
#include "DlgExtraDesc.h"
#include "DlgRoomFlags.h"
#include "DlgEnterVnum.h"
#include "DlgVnumList.h"
#include "DlgEditArea.h"
#include "DlgEditMob.h"
#include "DlgEditExits.h"
#include "EditRoom.h"
#include "DlgEditShop.h"
#include "DlgActFlags.h"
#include "DlgMobAffFlags.h"
#include "DlgEditObject.h"
#include "DlgExtraObjFlags.h"
#include "DlgEditContents.h"
#include "DlgEditAntiFlags.h"
#include "DlgDirections.h"
#include "DlgSettings.h"
#include "DlgSelectColor.h"
#include "DlgEquipItem.h"
#include "DlgEquipMob.h"
#include "DlgQuestEdit.h"
#include "DlgQuestClue.h"
#include "DlgEditQuest.h"
#include "DlgQuestItem.h"
#include "DlgCalcCoins.h"
#include "DlgSpells.h"

#include "Mobs.h"
#include "Rooms.h"
#include "Area.h"
#include "Bits.h"
#include "Objects.h"
#include "Utils.h"
#include "Spells.h"

#include "ZoneFile.h"

#include "Alias.h"
#include "DlgAreaStatistics.h"
#include "ProgEditor.h"

extern int	room_count;
extern int	mob_count;
extern int	obj_count;
extern int	shop_count;
extern int	quest_count;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6BF7E700_87CF_480F_AE43_67DD85365E29__INCLUDED_)
