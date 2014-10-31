// ******************************************************************************
// BalloonHelp.cpp : implementation file
// Copyright 2001-2002, Joshua Heyer
//  You are free to use this code for whatever you want, provided you
// give credit where credit is due.  (I seem to get a lot of questions
// about that statement...  All i mean is, don't copy huge bits of code
// and then claim you wrote it.  You don't have to put my name in an about
// box or anything.  Though i'm not going to stop you if that's really what
// you want :~) )
//  I'm providing this code in the hope that it is useful to someone, as i have
// gotten much use out of other peoples code over the years.
//  If you see value in it, make some improvements, etc., i would appreciate it 
// if you sent me some feedback.
//
// ******************************************************************************

#include "stdafx.h"
#include "BalloonHelp.h"

// allow multimonitor-aware code on Win95 systems
// comment out the first line if you have already define it in another file
// comment out both lines if you don't care about Win95
#define COMPILE_MULTIMON_STUBS
#include "multimon.h"

// debug helpers
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// constants that may not be defined if you don't have the latest SDK
// (but i like to use them anyway)
//

#ifndef DFCS_HOT
#define DFCS_HOT 0x1000
#endif

#ifndef AW_HIDE
#define AW_HIDE 0x00010000
#define AW_BLEND 0x00080000
#endif

#ifndef CS_DROPSHADOW
#define CS_DROPSHADOW   0x00020000
#endif

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW  0x1024
#endif

#ifndef SPI_GETTOOLTIPANIMATION
#define SPI_GETTOOLTIPANIMATION 0x1016
#endif

#ifndef SPI_GETTOOLTIPFADE
#define SPI_GETTOOLTIPFADE 0x1018
#endif

/////////////////////////////////////////////////////////////////////////////
// CBalloonHelp

// option constants (bits)
const unsigned int   CBalloonHelp::unCLOSE_ON_LBUTTON_UP    = 0x0001;
const unsigned int   CBalloonHelp::unCLOSE_ON_MBUTTON_UP    = 0x0002;
const unsigned int   CBalloonHelp::unCLOSE_ON_RBUTTON_UP    = 0x0004;
const unsigned int   CBalloonHelp::unCLOSE_ON_LBUTTON_DOWN  = 0x0008;
const unsigned int   CBalloonHelp::unCLOSE_ON_MBUTTON_DOWN  = 0x0010;
const unsigned int   CBalloonHelp::unCLOSE_ON_RBUTTON_DOWN  = 0x0020;
const unsigned int   CBalloonHelp::unCLOSE_ON_MOUSE_MOVE    = 0x0040;
const unsigned int   CBalloonHelp::unCLOSE_ON_KEYPRESS      = 0x0080;
const unsigned int   CBalloonHelp::unCLOSE_ON_ANYTHING      = CBalloonHelp::unCLOSE_ON_MOUSE_MOVE|CBalloonHelp::unCLOSE_ON_RBUTTON_DOWN|CBalloonHelp::unCLOSE_ON_RBUTTON_DOWN|CBalloonHelp::unCLOSE_ON_MBUTTON_DOWN|CBalloonHelp::unCLOSE_ON_LBUTTON_DOWN|CBalloonHelp::unCLOSE_ON_RBUTTON_UP|CBalloonHelp::unCLOSE_ON_MBUTTON_UP|CBalloonHelp::unCLOSE_ON_LBUTTON_UP;
const unsigned int   CBalloonHelp::unDELAY_CLOSE            = 0x0100;
const unsigned int   CBalloonHelp::unDELETE_THIS_ON_CLOSE   = 0x0200;
const unsigned int   CBalloonHelp::unSHOW_CLOSE_BUTTON      = 0x0400;
const unsigned int   CBalloonHelp::unSHOW_INNER_SHADOW      = 0x0800;
const unsigned int   CBalloonHelp::unSHOW_TOPMOST           = 0x1000;
const unsigned int   CBalloonHelp::unDISABLE_XP_SHADOW      = 0x2000;
const unsigned int   CBalloonHelp::unDISABLE_FADEIN         = 0x4000;
const unsigned int   CBalloonHelp::unDISABLE_FADEOUT        = 0x8000;
const unsigned int   CBalloonHelp::unDISABLE_FADE           = CBalloonHelp::unDISABLE_FADEIN|CBalloonHelp::unDISABLE_FADEOUT;

// layout constants (should prolly be configurable, but who's really gonna care?)
const int            CBalloonHelp::nTIP_TAIL             = 20;
const int            CBalloonHelp::nTIP_MARGIN           = 8;
// class atom (why don't i do this the MFC way?  Drop shadows!)
ATOM                 CBalloonHelp::s_ClassAtom           = NULL;
ATOM                 CBalloonHelp::s_ClassAtomShadowed   = NULL;

// Kill timer
#define ID_TIMER_CLOSE  1


//
// The launchers
//


//
// Show a help balloon on screen
// Parameters:
//    strTitle    |  Title of balloon
//    unTitle     |  Title of balloon (id of string resource)
//    strContent  |  Content of balloon
//    unContent   |  Content of balloon (id of string resource)
//    ptAnchor    |  point tail of balloon will be "anchor"ed to
//    szIcon      |  One of:
//                   IDI_APPLICATION
//                   IDI_INFORMATION IDI_ASTERISK (same)
//                   IDI_ERROR IDI_HAND (same)
//                   IDI_EXCLAMATION IDI_WARNING (same)
//                   IDI_QUESTION
//                   IDI_WINLOGO
//                   NULL (no icon)
//    unIconID    |  ID of icon to display (loaded from resources)
//    unOptions   |  One or more of:
//                :     unCLOSE_ON_LBUTTON_UP   |  closes window on WM_LBUTTON_UP
//                :     unCLOSE_ON_MBUTTON_UP   |  closes window on WM_MBUTTON_UP
//                :     unCLOSE_ON_RBUTTON_UP   |  closes window on WM_RBUTTON_UP
//                :     unCLOSE_ON_LBUTTON_DOWN |  closes window on WM_LBUTTON_DOWN
//                :     unCLOSE_ON_MBUTTON_DOWN |  closes window on WM_MBUTTON_DOWN
//                :     unCLOSE_ON_RBUTTON_DOWN |  closes window on WM_RBUTTON_DOWN
//                :     unCLOSE_ON_MOUSE_MOVE   |  closes window when user moves mouse past threshhold
//                :     unCLOSE_ON_KEYPRESS     |  closes window on the next keypress message sent to this thread.
//                :     unCLOSE_ON_ANYTHING     |  all of the above.
//                :     unDELAY_CLOSE           |  when a user action triggers the close, begins timer.  closes when timer expires.
//                :     unSHOW_CLOSE_BUTTON     |  shows close button in upper right
//                :     unSHOW_INNER_SHADOW     |  draw inner shadow in balloon
//                :     unSHOW_TOPMOST          |  place balloon above all other windows
//                :     unDISABLE_XP_SHADOW     |  disable Windows XP's drop-shadow effect (overrides system and user settings)
//                :     unDISABLE_FADE          |  disable the fade-in/fade-out effects (overrides system and user settings)
//                :     unDISABLE_FADEIN        |  disable the fade-in effect
//                :     unDISABLE_FADEOUT       |  disable the fade-out effect
//    pParentWnd  |  Parent window.  If NULL will be set to AfxGetMainWnd(), and anchor to screen
//    strURL      |  If not empty, when the balloon is clicked ShellExecute() will
//                |  be called, with strURL passed in.
//    unTimeout   |  If not 0, balloon will automatically close after unTimeout milliseconds.
//
void CBalloonHelp::LaunchBalloon(const CString& strTitle, const CString& strContent, 
               const CPoint& ptAnchor, 
               LPCTSTR szIcon /*= IDI_EXCLAMATION*/,
               unsigned int unOptions /*= unSHOW_CLOSE_BUTTON*/,
               CWnd* pParentWnd /*= NULL*/,
               const CString strURL /*= ""*/,
               unsigned int unTimeout /*= 10000*/)
{
   CBalloonHelp* pbh = new CBalloonHelp;
   if ( NULL != szIcon )
   {
      // Note: Since i'm scaling the icon anyway, i'll allow it to become larger
      // than the standard small icon if the close button is.
      CSize sizeIcon(max(::GetSystemMetrics(SM_CXSIZE), ::GetSystemMetrics(SM_CXSMICON)), max(::GetSystemMetrics(SM_CYSIZE), ::GetSystemMetrics(SM_CYSMICON)));
      HICON hIcon = (HICON)::LoadImage(NULL, szIcon, IMAGE_ICON, sizeIcon.cx, sizeIcon.cy, LR_SHARED);
      if (NULL != hIcon)
         pbh->SetIconScaled(hIcon, sizeIcon.cx, sizeIcon.cy);
   }

   pbh->Create(strTitle, strContent, ptAnchor, unOptions|unDELETE_THIS_ON_CLOSE, 
               pParentWnd, strURL, unTimeout, NULL);
}


//
//  The class
//

CBalloonHelp::CBalloonHelp()
:  m_fnAnimateWindow(NULL),
   m_unOptions(0),
   m_unTimeout(0),
   m_unTimerClose(0),
   m_strURL(""),
   m_ptAnchor(0,0),
   m_hwndAnchor(NULL),
   m_screenRect(0,0,0,0),
   m_strContent(""),
   m_nMouseMoveTolerance(3),     // later retrieved from system
   m_ptMouseOrig(0,0),
   m_uCloseState(0),
   m_pTitleFont(NULL),
   m_pContentFont(NULL),
   m_crForeground(::GetSysColor(COLOR_INFOTEXT)),
   m_crBackground(::GetSysColor(COLOR_INFOBK)),
   m_hKeyboardHook(NULL),
   m_hMouseHook(NULL),
   m_hCallWndRetHook(NULL)
{
   // retrieve window animation API if available
   HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
   // can't imagine why that would fail, but might as well *look* safe...  ;~)
   if ( NULL != hUser32 )
      m_fnAnimateWindow = (FN_ANIMATE_WINDOW)GetProcAddress(hUser32, _T("AnimateWindow"));
   else
      m_fnAnimateWindow = NULL;

   // get system tolerance values
   int nTol = 0;
   if ( ::SystemParametersInfo(SPI_GETMOUSEHOVERWIDTH, 0, &nTol, 0) && nTol > 0 )
      m_nMouseMoveTolerance = nTol;

   // setup hook procedures
   BHKeybHookThunk<CBalloonHelp>::InitThunk((TMFP)KeyboardHookProc, this);
   BHMouseHookThunk<CBalloonHelp>::InitThunk((TMFP)MouseHookProc, this);
   BHCallWndRetHookThunk<CBalloonHelp>::InitThunk((TMFP)CallWndRetProc, this);
}

CBalloonHelp::~CBalloonHelp()
{
   if ( NULL != m_pTitleFont )
      delete m_pTitleFont;
   m_pTitleFont = NULL;
   if ( NULL != m_pContentFont )
      delete m_pContentFont;
   m_pContentFont = NULL;
}


// Sets the font used for drawing the balloon title.  Deleted by balloon, do not use CFont* after passing to this function.
void CBalloonHelp::SetTitleFont(CFont* pFont)
{
   if ( NULL != m_pTitleFont )
      delete m_pTitleFont;
   m_pTitleFont = pFont;
   // if already visible, resize & move
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the font used for drawing the balloon content.  Deleted by balloon, do not use CFont* after passing to this function.
void CBalloonHelp::SetContentFont(CFont* pFont)
{
   if ( NULL != m_pContentFont )
      delete m_pContentFont;
   m_pContentFont = pFont;
   // if already visible, resize & move
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the icon displayed in the top left of the balloon (pass NULL to hide icon)
void CBalloonHelp::SetIcon(HICON hIcon)
{
   if ( NULL != m_ilIcon.m_hImageList )
      m_ilIcon.DeleteImageList();
   ICONINFO iconinfo;
   if ( NULL != hIcon && ::GetIconInfo(hIcon, &iconinfo) )
   {
      SetIcon(iconinfo.hbmColor, iconinfo.hbmMask);
      ::DeleteObject(iconinfo.hbmColor);
      ::DeleteObject(iconinfo.hbmMask);
   }
   // if already visible, resize & move (icon size may have changed)
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the icon displayed in the top left of the balloon (pass NULL to hide icon)
void CBalloonHelp::SetIconScaled(HICON hIcon, int cx, int cy)
{
   // i now have two device contexts and two bitmaps.
   // i will select a bitmap in each device context,
   // draw the icon into the first one,
   // scale it into the second one,
   // and set the second one as the balloon icon.
   // This is a rather long process to get a scaled icon,
   // but ensures maximum compatibility between different
   // versions of Windows, while producing the best possible
   // results on each version (quite good in WinNT and better, sorta ok in Win9x).
   ICONINFO iconinfo;
   if ( NULL != hIcon && ::GetIconInfo(hIcon, &iconinfo) )
   {
      BITMAP bm;
      if (::GetObject(iconinfo.hbmColor, sizeof(bm),(LPVOID)&bm))
      {
         CDC dc;
         CDC dcTmp1;
         CDC dcTmp2;
         CBitmap bmpIcon;
         CBitmap bmpIconScaled;
         dc.Attach(::GetDC(NULL));
         dcTmp1.CreateCompatibleDC(&dc);
         dcTmp2.CreateCompatibleDC(&dc);
         bmpIcon.CreateCompatibleBitmap(&dc, bm.bmWidth, bm.bmHeight);
         bmpIconScaled.CreateCompatibleBitmap(&dc, cx, cy);
         ::ReleaseDC(NULL, dc.Detach());

         CBitmap* pbmpOld1 = dcTmp1.SelectObject(&bmpIcon);
         CBitmap* pbmpOld2 = dcTmp2.SelectObject(&bmpIconScaled);
         dcTmp1.FillSolidRect(0,0,bm.bmWidth,bm.bmHeight, m_crBackground);
         ::DrawIconEx(dcTmp1, 0,0,hIcon,bm.bmWidth,bm.bmHeight,0,NULL,DI_NORMAL);
         dcTmp2.SetStretchBltMode(HALFTONE);
         dcTmp2.StretchBlt(0,0,cx,cy,&dcTmp1, 0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
         dcTmp1.SelectObject(pbmpOld1);
         dcTmp2.SelectObject(pbmpOld2);

         SetIcon(bmpIconScaled, m_crBackground);
      }
      ::DeleteObject(iconinfo.hbmColor);
      ::DeleteObject(iconinfo.hbmMask);
   }
}

// Sets the icon displayed in the top left of the balloon (pass NULL hBitmap to hide icon)
void CBalloonHelp::SetIcon(HBITMAP hBitmap, COLORREF crMask)
{
   if ( NULL != m_ilIcon.m_hImageList )
      m_ilIcon.DeleteImageList();

   if ( NULL != hBitmap )
   {
      BITMAP bm;
      if (::GetObject(hBitmap, sizeof(bm),(LPVOID)&bm))
      {
         m_ilIcon.Create(bm.bmWidth, bm.bmHeight, ILC_COLOR24|ILC_MASK,1,0);
         m_ilIcon.Add(CBitmap::FromHandle(hBitmap), crMask);
      }
   }
   // if already visible, resize & move (icon size may have changed)
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the icon displayed in the top left of the balloon
void CBalloonHelp::SetIcon(HBITMAP hBitmap, HBITMAP hMask)
{
   if ( NULL != m_ilIcon.m_hImageList )
      m_ilIcon.DeleteImageList();

   ASSERT(NULL != hBitmap);
   ASSERT(NULL != hMask);

   BITMAP bm;
   if (::GetObject(hBitmap, sizeof(bm),(LPVOID)&bm))
   {
      m_ilIcon.Create(bm.bmWidth, bm.bmHeight, ILC_COLOR24|ILC_MASK,1,0);
      m_ilIcon.Add(CBitmap::FromHandle(hBitmap), CBitmap::FromHandle(hMask));
   }
   // if already visible, resize & move (icon size may have changed)
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Set icon displayed in the top left of the balloon to image # nIconIndex from pImageList
void CBalloonHelp::SetIcon(CImageList* pImageList, int nIconIndex)
{
   // sanity checks
   ASSERT_VALID(pImageList);
   ASSERT(nIconIndex >= 0 && nIconIndex < pImageList->GetImageCount() );

   HICON hIcon = NULL;
   if ( NULL != pImageList && nIconIndex >= 0 && nIconIndex < pImageList->GetImageCount() )
      hIcon = pImageList->ExtractIcon(nIconIndex);
   SetIcon(hIcon);
   if ( NULL != hIcon )
      ::DestroyIcon(hIcon);
   // if already visible, resize & move (icon size may have changed)
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the URL to be opened when balloon is clicked.  Pass "" to disable.
void CBalloonHelp::SetURL(const CString& strURL)
{
   m_strURL = strURL;
}

// Sets the number of milliseconds the balloon can remain open.  Set to 0 to disable timeout.
void CBalloonHelp::SetTimeout(unsigned int unTimeout)
{
   m_unTimeout = unTimeout;
   // if timer is already set, reset.
   if ( NULL != m_hWnd )
   {
      if ( m_unTimeout > 0 )
      {
         m_unTimerClose = SetTimer(ID_TIMER_CLOSE, m_unTimeout, NULL);
      }
      else
      {
         KillTimer(m_unTimerClose);
      }
   }
}

// Sets the point to which the balloon is "anchored"
void CBalloonHelp::SetAnchorPoint(CPoint ptAnchor, CWnd* pWndAnchor /*= NULL*/)
{
   m_ptAnchor = ptAnchor;
   m_hwndAnchor = pWndAnchor->GetSafeHwnd();

   // if we're anchored to a window, set hook
   if ( NULL != m_hwndAnchor )
      SetCallWndRetHook();
   else
      RemoveCallWndRetHook();

   // if already visible, move
   if ( NULL != m_hWnd )
   {
      // reposition
      PositionWindow();
   }
}

// Sets the title of the balloon
void CBalloonHelp::SetTitle(const CString& strTitle)
{
   SetWindowText(strTitle);
   // if already visible, resize & move
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the content of the balloon (plain text only)
void CBalloonHelp::SetContent(const CString& strContent)
{
   m_strContent = strContent;
   // if already visible, resize & move
   if ( NULL != m_hWnd )
      PositionWindow();
}

// Sets the forground (text and border) color of the balloon
void CBalloonHelp::SetForegroundColor(COLORREF crForeground)
{
   m_crForeground = crForeground;
   // repaint if visible
   if ( NULL != m_hWnd )
      Invalidate(FALSE);
}

// Sets the background color of the balloon
void CBalloonHelp::SetBackgroundColor(COLORREF crBackground)
{
   m_crBackground = crBackground;
   // repaint if visible
   if ( NULL != m_hWnd )
      Invalidate(FALSE);
}

// Sets the distance the mouse must move before the balloon closes when the unCLOSE_ON_MOUSE_MOVE option is set.
void CBalloonHelp::SetMouseMoveTolerance(int nTolerance)
{
   m_nMouseMoveTolerance = nTolerance;
}

//
// creates a new balloon window
// Parameters:
//    strTitle    |  Title of balloon
//    strContent  |  Content of balloon
//    ptAnchor    |  point tail of balloon will be "anchor"ed to
//    unOptions   |  One or more of:
//                :     unCLOSE_ON_LBUTTON_UP   |  closes window on WM_LBUTTON_UP
//                :     unCLOSE_ON_MBUTTON_UP   |  closes window on WM_MBUTTON_UP
//                :     unCLOSE_ON_RBUTTON_UP   |  closes window on WM_RBUTTON_UP
//                :     unCLOSE_ON_LBUTTON_DOWN |  closes window on WM_LBUTTON_DOWN
//                :     unCLOSE_ON_MBUTTON_DOWN |  closes window on WM_MBUTTON_DOWN
//                :     unCLOSE_ON_RBUTTON_DOWN |  closes window on WM_RBUTTON_DOWN
//                :     unCLOSE_ON_MOUSE_MOVE   |  closes window when user moves mouse past threshhold
//                :     unCLOSE_ON_KEYPRESS     |  closes window on the next keypress message sent to this thread.
//                :     unCLOSE_ON_ANYTHING     |  all of the above.
//                :     unDELAY_CLOSE           |  when a user action triggers the close, begins timer.  closes when timer expires.
//                :     unDELETE_THIS_ON_CLOSE  |  deletes object when window is closed.  Used by LaunchBalloon(), use with care
//                :     unSHOW_CLOSE_BUTTON     |  shows close button in upper right
//                :     unSHOW_INNER_SHADOW     |  draw inner shadow in balloon
//                :     unSHOW_TOPMOST          |  place balloon above all other windows
//                :     unDISABLE_XP_SHADOW     |  disable Windows XP's drop-shadow effect (overrides system and user settings)
//                :     unDISABLE_FADE          |  disable the fade-in/fade-out effects (overrides system and user settings)
//                :     unDISABLE_FADEIN        |  disable the fade-in effect
//                :     unDISABLE_FADEOUT       |  disable the fade-out effect
//    pParentWnd  |  Parent window.  If NULL will be set to AfxGetMainWnd() and anchor to screen
//    strURL      |  If not empty, when the balloon is clicked ShellExecute() will
//                |  be called, with strURL passed in.
//    unTimeout   |  If not 0, balloon will automatically close after unTimeout milliseconds.
//    hIcon       |  If not NULL, the icon indicated by hIcon will be displayed at top-left of the balloon.
//
// Returns:
//    TRUE if successful, else FALSE
//
BOOL CBalloonHelp::Create(const CString& strTitle, const CString& strContent, 
               const CPoint& ptAnchor, unsigned int unOptions,
               CWnd* pParentWnd /*=NULL*/,
               const CString strURL /*= ""*/,
               unsigned int unTimeout /*= 0*/,
               HICON hIcon /*= NULL*/)
{
   m_strContent   = strContent;
   SetAnchorPoint(ptAnchor, pParentWnd);
   m_unOptions    = unOptions;
   m_strURL       = strURL;
   m_unTimeout    = unTimeout;

   if ( NULL != hIcon )
      SetIcon(hIcon);
   
   pParentWnd = GetSafeOwner(pParentWnd);
   if ( NULL == pParentWnd )
   {
      // something is wrong; MFC should be able to find a main window.
      ASSERT(FALSE);
      return FALSE;
   }

   // if no fonts set, use defaults
   if ( NULL == m_pContentFont )
   {
      m_pContentFont = new CFont;
      if ( !m_pContentFont->CreateStockObject(DEFAULT_GUI_FONT) )
         return FALSE;
   }

   // title font defaults to bold version of content font
   if ( NULL == m_pTitleFont )
   {
      m_pTitleFont = new CFont;
      LOGFONT LogFont;
      m_pContentFont->GetLogFont(&LogFont);
      LogFont.lfWeight = FW_BOLD;
      if ( !m_pTitleFont->CreateFontIndirect(&LogFont) )
         return FALSE;
   }

   ATOM wndClass = GetClassAtom(!(m_unOptions&unDISABLE_XP_SHADOW));
   if ( NULL == wndClass )  // couldn't register class
      return FALSE;

   // check system settings: if fade effects are disabled or unavailable, disable here too
   BOOL bFade = FALSE;
   ::SystemParametersInfo(SPI_GETTOOLTIPANIMATION, 0, &bFade, 0);
   if (bFade)
      ::SystemParametersInfo(SPI_GETTOOLTIPFADE, 0, &bFade, 0);
   if (!bFade || NULL == m_fnAnimateWindow)
      m_unOptions |= unDISABLE_FADE;

   // create invisible at arbitrary position; then position, set region, and finally show

   // the idea with WS_EX_TOOLWINDOW is, you can't switch to this using alt+tab
   DWORD dwExStyle = WS_EX_TOOLWINDOW;
   if ( m_unOptions&unSHOW_TOPMOST )      // make topmost, if requested
      dwExStyle |= WS_EX_TOPMOST;
   if ( !CreateEx(dwExStyle, (LPCTSTR)wndClass, strTitle, WS_POPUP, CRect(0,0,10,10), pParentWnd, 0, NULL) )
      return FALSE;
   PositionWindow();

   if ( (m_unOptions&unCLOSE_ON_MOUSE_MOVE)
      ||(m_unOptions&unCLOSE_ON_LBUTTON_UP)
      ||(m_unOptions&unCLOSE_ON_LBUTTON_DOWN)
      ||(m_unOptions&unCLOSE_ON_MBUTTON_UP)
      ||(m_unOptions&unCLOSE_ON_MBUTTON_DOWN)
      ||(m_unOptions&unCLOSE_ON_RBUTTON_UP)
      ||(m_unOptions&unCLOSE_ON_RBUTTON_DOWN) )
   {
      ::GetCursorPos(&m_ptMouseOrig);
      SetMouseHook();
   }

   // these need to take effect even if the window receiving them
   // is not owned by this process.  So, if this process does not
   // already have the mouse captured, capture it!
   if ( (m_unOptions&unCLOSE_ON_LBUTTON_UP)
      ||(m_unOptions&unCLOSE_ON_MBUTTON_UP)
      ||(m_unOptions&unCLOSE_ON_RBUTTON_UP) )
   {
      // no, i don't particularly need or want to deal with a situation
      // where a balloon is being created and another program has captured
      // the mouse.  If you need it, it shouldn't be too hard, just do it here.
      if ( NULL == GetCapture() )
         SetCapture();
   }

   if ( m_unOptions&unCLOSE_ON_KEYPRESS )
      SetKeyboardHook();

   ShowBalloon();
   return TRUE;
}

// calculate anchor position (adjust for client coordinates if used)
CPoint CBalloonHelp::GetAnchorPoint()
{
   CPoint ptAnchor = m_ptAnchor;
   // assume if window was given, point is in client coords
   if ( NULL != m_hwndAnchor )
      ::ClientToScreen(m_hwndAnchor, &ptAnchor);
   return ptAnchor;
}

// determine bounds of screen anchor is on (Multi-Monitor compatibility)
void CBalloonHelp::GetAnchorScreenBounds(CRect& rect)
{
   if ( m_screenRect.IsRectEmpty() )
   {     
      // get the nearest monitor to the anchor
      HMONITOR hMonitor = MonitorFromPoint(GetAnchorPoint(), MONITOR_DEFAULTTONEAREST);

      // get the monitor bounds
      MONITORINFO mi;
      mi.cbSize = sizeof(mi);
      GetMonitorInfo(hMonitor, &mi);

      // work area (area not obscured by task bar, etc.)
      m_screenRect = mi.rcWork;
   }
   rect = m_screenRect;
}

// calculates the area of the screen the balloon falls into
// this determins which direction the tail points
CBalloonHelp::BALLOON_QUADRANT CBalloonHelp::GetBalloonQuadrant()
{
   CRect rectDesktop;
   GetAnchorScreenBounds(rectDesktop);
   CPoint ptAnchor = GetAnchorPoint();
   
   if ( ptAnchor.y < rectDesktop.top + rectDesktop.Height()/2 )
   {
      if ( ptAnchor.x < rectDesktop.left + rectDesktop.Width()/2 )
      {
         return BQ_TOPLEFT;
      }
      else
      {
         return BQ_TOPRIGHT;
      }
   }
   else
   {
      if ( ptAnchor.x < rectDesktop.left + rectDesktop.Width()/2 )
      {
         return BQ_BOTTOMLEFT;
      }
      else
      {
         return BQ_BOTTOMRIGHT;
      }
   }

   // unreachable
}

// Draw the non-client area
void CBalloonHelp::DrawNonClientArea(CDC* pDC)
{
   CRect rect;
   GetWindowRect(&rect);
   ScreenToClient(&rect);
   CRect rectClient;
   GetClientRect(&rectClient);
   rectClient.OffsetRect(-rect.left, -rect.top);
   rect.OffsetRect(-rect.left, -rect.top);
   pDC->ExcludeClipRect(&rectClient);
   pDC->FillSolidRect(&rect, m_crBackground);
   pDC->SelectClipRgn(NULL);

   ASSERT(NULL != m_rgnComplete.m_hObject);
   CBrush   brushFg;
   brushFg.CreateSolidBrush(m_crForeground);
   if ( m_unOptions & unSHOW_INNER_SHADOW )
   {
      CBrush   brushHL;
      // slightly lighter color
      int red = 170 + GetRValue(m_crBackground)/3;
      int green = 170 + GetGValue(m_crBackground)/3;
      int blue = 170 + GetBValue(m_crBackground)/3;
      brushHL.CreateSolidBrush(RGB(red,green,blue));
      m_rgnComplete.OffsetRgn(1,1);
      pDC->FrameRgn(&m_rgnComplete, &brushHL, 2, 2);
      // slightly darker color
      red = GetRValue(m_crForeground)/3 + GetRValue(m_crBackground)/3*2;
      green = GetGValue(m_crForeground)/3 + GetGValue(m_crBackground)/3*2;
      blue = GetBValue(m_crForeground)/3 + GetBValue(m_crBackground)/3*2;
      brushHL.DeleteObject();
      m_rgnComplete.OffsetRgn(-2,-2);
      brushHL.CreateSolidBrush(RGB(red,green,blue));
      pDC->FrameRgn(&m_rgnComplete, &brushHL, 2, 2);
      m_rgnComplete.OffsetRgn(1,1);
   }
   // outline
   pDC->FrameRgn(&m_rgnComplete, &brushFg, 1, 1);
}

// Draw the client area
void CBalloonHelp::DrawClientArea(CDC* pDC)
{
   CSize sizeHeader = DrawHeader(pDC);
   DrawContent(pDC, sizeHeader.cy+nTIP_MARGIN);
}

// Calculate the dimensions and draw the balloon header
CSize CBalloonHelp::DrawHeader(CDC* pDC, bool bDraw)
{
   CSize sizeHdr(0,0);
   CRect rectClient;
   GetClientRect(&rectClient);   // use this for positioning when drawing
                                 // else if content is wider than title, centering wouldn't work

   // calc & draw icon
   if ( NULL != m_ilIcon.m_hImageList )
   {
      int x = 0;
      int y = 0;
      ImageList_GetIconSize(m_ilIcon, &x, &y);
      sizeHdr.cx += x;
      sizeHdr.cy = max(sizeHdr.cy, y);
      m_ilIcon.SetBkColor(m_crBackground);
      if (bDraw)
         m_ilIcon.Draw(pDC, 0, CPoint(0,0), ILD_NORMAL);//ILD_TRANSPARENT);
      rectClient.left += x;
   }

   // calc & draw close button
   if ( m_unOptions & unSHOW_CLOSE_BUTTON )
   {
      int nBtnWidth = ::GetSystemMetrics(SM_CXSIZE);
      // if something is already in the header (icon) leave space
      if ( sizeHdr.cx > 0 )
         sizeHdr.cx += nTIP_MARGIN;
      sizeHdr.cx += nBtnWidth;
      sizeHdr.cy = max(sizeHdr.cy, ::GetSystemMetrics(SM_CYSIZE));
      if (bDraw)
         pDC->DrawFrameControl(CRect(rectClient.right-nBtnWidth,0,rectClient.right,::GetSystemMetrics(SM_CYSIZE)), DFC_CAPTION, DFCS_CAPTIONCLOSE|DFCS_FLAT);
      rectClient.right -= nBtnWidth;
   }

   // calc title size
   CString strTitle;
   GetWindowText(strTitle);
   if ( !strTitle.IsEmpty() )
   {
      CFont* pOldFont = pDC->SelectObject(m_pTitleFont);

      // if something is already in the header (icon or close button) leave space
      if ( sizeHdr.cx > 0 ) 
         sizeHdr.cx += nTIP_MARGIN;
      CRect rectTitle(0,0,0,0);
      pDC->DrawText(strTitle, &rectTitle, DT_CALCRECT | DT_NOPREFIX | DT_EXPANDTABS | DT_SINGLELINE);
      sizeHdr.cx += rectTitle.Width();
      sizeHdr.cy = max(sizeHdr.cy, rectTitle.Height());

      // draw title
      if ( bDraw )
      {
         pDC->SetBkMode(TRANSPARENT);
         pDC->SetTextColor(m_crForeground);
         pDC->DrawText(strTitle, &rectClient, DT_CENTER | DT_NOPREFIX  | DT_EXPANDTABS | DT_SINGLELINE);
      }

      // cleanup
      pDC->SelectObject(pOldFont);
   }

   return sizeHdr;
}

// Calculate the dimensions and draw the balloon contents
CSize CBalloonHelp::DrawContent(CDC* pDC, int nTop, bool bDraw)
{
   CRect rectContent;
   GetAnchorScreenBounds(rectContent);
   rectContent.OffsetRect(-rectContent.left, -rectContent.top);
   rectContent.top = nTop;

   // limit to half screen width
   rectContent.right -= rectContent.Width()/2;

   // calc size
   CFont* pOldFont = pDC->SelectObject(m_pContentFont);
   if ( !m_strContent.IsEmpty() )
      pDC->DrawText(m_strContent, &rectContent, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_EXPANDTABS | DT_WORDBREAK);
   else
      rectContent.SetRectEmpty();   // don't want to leave half the screen for empty strings ;)
   
   // draw
   if (bDraw)
   {
      pDC->SetBkMode(TRANSPARENT);
      pDC->SetTextColor(m_crForeground);
      pDC->DrawText(m_strContent, &rectContent, DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_EXPANDTABS);
   }

   // cleanup
   pDC->SelectObject(pOldFont);

   return rectContent.Size();
}

// calculates the client size necessary based on title and content
CSize CBalloonHelp::CalcClientSize()
{
   ASSERT(NULL != m_hWnd);
   CWindowDC dc(this);

   CSize sizeHeader = CalcHeaderSize(&dc);
   CSize sizeContent = CalcContentSize(&dc);

   return CSize(max(sizeHeader.cx,sizeContent.cx), sizeHeader.cy + nTIP_MARGIN + sizeContent.cy);
}

// calculates the size for the entire window based on content size
CSize CBalloonHelp::CalcWindowSize()
{
   CSize size = CalcClientSize();
   size.cx += nTIP_MARGIN*2;
   size.cy += nTIP_TAIL+nTIP_MARGIN*2;
   //size.cx = max(size.cx, nTIP_MARGIN*2+nTIP_TAIL*4);
   return size;
}


// this routine calculates the size and position of the window relative
// to it's anchor point, and moves the window accordingly.  The region is also
// created and set here.
void CBalloonHelp::PositionWindow()
{
   CSize sizeWnd = CalcWindowSize();

   CPoint ptTail[3];
   CPoint ptTopLeft(0,0);
   CPoint ptBottomRight(sizeWnd.cx, sizeWnd.cy);

   // force recalculation of desktop
   m_screenRect.SetRectEmpty();

   switch (GetBalloonQuadrant())
   {
   case BQ_TOPLEFT:
      ptTopLeft.y = nTIP_TAIL;
      ptTail[0].x = (sizeWnd.cx-nTIP_TAIL)/4 + nTIP_TAIL;
      ptTail[0].y = nTIP_TAIL+1;
      ptTail[2].x = (sizeWnd.cx-nTIP_TAIL)/4;
      ptTail[2].y = ptTail[0].y;
      ptTail[1].x = ptTail[2].x;
      ptTail[1].y = 1;
      break;
   case BQ_TOPRIGHT:
      ptTopLeft.y = nTIP_TAIL;
      ptTail[0].x = (sizeWnd.cx-nTIP_TAIL)/4*3;
      ptTail[0].y = nTIP_TAIL+1;
      ptTail[2].x = (sizeWnd.cx-nTIP_TAIL)/4*3 + nTIP_TAIL;
      ptTail[2].y = ptTail[0].y;
      ptTail[1].x = ptTail[2].x;
      ptTail[1].y = 1;
      break;
   case BQ_BOTTOMLEFT:
      ptBottomRight.y = sizeWnd.cy-nTIP_TAIL;
      ptTail[0].x = (sizeWnd.cx-nTIP_TAIL)/4 + nTIP_TAIL;
      ptTail[0].y = sizeWnd.cy-nTIP_TAIL-2;
      ptTail[2].x = (sizeWnd.cx-nTIP_TAIL)/4;
      ptTail[2].y = ptTail[0].y;
      ptTail[1].x = ptTail[2].x;
      ptTail[1].y = sizeWnd.cy-2;
      break;
   case BQ_BOTTOMRIGHT:
      ptBottomRight.y = sizeWnd.cy-nTIP_TAIL;
      ptTail[0].x = (sizeWnd.cx-nTIP_TAIL)/4*3;
      ptTail[0].y = sizeWnd.cy-nTIP_TAIL-2;
      ptTail[2].x = (sizeWnd.cx-nTIP_TAIL)/4*3 + nTIP_TAIL;
      ptTail[2].y = ptTail[0].y;
      ptTail[1].x = ptTail[2].x;
      ptTail[1].y = sizeWnd.cy-2;
      break;
   }

   // adjust for very narrow balloons
   if ( ptTail[0].x < nTIP_MARGIN )
      ptTail[0].x = nTIP_MARGIN;
   if ( ptTail[0].x > sizeWnd.cx - nTIP_MARGIN )
      ptTail[0].x = sizeWnd.cx - nTIP_MARGIN;
   if ( ptTail[1].x < nTIP_MARGIN )
      ptTail[1].x = nTIP_MARGIN;
   if ( ptTail[1].x > sizeWnd.cx - nTIP_MARGIN )
      ptTail[1].x = sizeWnd.cx - nTIP_MARGIN;
   if ( ptTail[2].x < nTIP_MARGIN )
      ptTail[2].x = nTIP_MARGIN;
   if ( ptTail[2].x > sizeWnd.cx - nTIP_MARGIN )
      ptTail[2].x = sizeWnd.cx - nTIP_MARGIN;

   // get window position
   CPoint ptAnchor = GetAnchorPoint();
   CPoint ptOffs(ptAnchor.x - ptTail[1].x, ptAnchor.y - ptTail[1].y);

   // adjust position so all is visible
   CRect rectScreen;
   GetAnchorScreenBounds(rectScreen);
   int nAdjustX = 0;
   int nAdjustY = 0;
   if ( ptOffs.x < rectScreen.left )
      nAdjustX = rectScreen.left-ptOffs.x;
   else if ( ptOffs.x + sizeWnd.cx >= rectScreen.right )
      nAdjustX = rectScreen.right - (ptOffs.x + sizeWnd.cx);
   if ( ptOffs.y + nTIP_TAIL < rectScreen.top )
      nAdjustY = rectScreen.top - (ptOffs.y + nTIP_TAIL);
   else if ( ptOffs.y + sizeWnd.cy - nTIP_TAIL >= rectScreen.bottom )
      nAdjustY = rectScreen.bottom - (ptOffs.y + sizeWnd.cy - nTIP_TAIL);

   // reposition tail
   // uncomment two commented lines below to move entire tail 
   // instead of just anchor point

   //ptTail[0].x -= nAdjustX;
   ptTail[1].x -= nAdjustX;
   //ptTail[2].x -= nAdjustX;
   ptOffs.x    += nAdjustX;
   ptOffs.y    += nAdjustY;

   // place window
   MoveWindow(ptOffs.x, ptOffs.y, sizeWnd.cx, sizeWnd.cy, TRUE);

   // apply region
   CRgn region;
   CRgn regionRound;
   CRgn regionComplete;
   region.CreatePolygonRgn(&ptTail[0], 3, ALTERNATE);
   regionRound.CreateRoundRectRgn(ptTopLeft.x,ptTopLeft.y,ptBottomRight.x,ptBottomRight.y,nTIP_MARGIN*3,nTIP_MARGIN*3);
   regionComplete.CreateRectRgn(0,0,1,1);
   regionComplete.CombineRgn(&region, &regionRound, RGN_OR);

   if ( NULL == m_rgnComplete.m_hObject )
      m_rgnComplete.CreateRectRgn(0,0,1,1);

   if ( !m_rgnComplete.EqualRgn(&regionComplete) )
   {
      m_rgnComplete.CopyRgn(&regionComplete);
      SetWindowRgn((HRGN)regionComplete.Detach(), TRUE);

      // There is a bug with layered windows and NC changes in Win2k
      // As a workaround, redraw the entire window if the NC area changed.
      // Changing the anchor point is the ONLY thing that will change the
      // position of the client area relative to the window during normal
      // operation.
      RedrawWindow(NULL, NULL, RDW_UPDATENOW| RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
   }
}



// Returns the class ATOM for a BalloonHelp control.  Registers the class first, if necessary.
ATOM CBalloonHelp::GetClassAtom(BOOL bShadowed)
{
   if ( NULL == s_ClassAtom )
   {
      WNDCLASSEX wcx; 

      // Fill in the window class structure with parameters 
      // that describe the main window. 

      wcx.cbSize = sizeof(wcx);                 // size of structure 
      wcx.style = CS_DBLCLKS|CS_SAVEBITS
         |CS_DROPSHADOW;                        // notify of double clicks, save screen under, show dropshadow
      wcx.lpfnWndProc = AfxWndProc;             // points to window procedure 
      wcx.cbClsExtra = 0;                       // no extra class memory 
      wcx.cbWndExtra = 0;                       // no extra window memory 
      wcx.hInstance = AfxGetInstanceHandle();   // handle to instance 
      wcx.hIcon = NULL;                         // no app. icon 
      wcx.hCursor = LoadCursor(NULL,IDC_ARROW); // predefined arrow 
      wcx.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);                 // no background brush 
      wcx.lpszMenuName =  NULL;                 // no menu resource 
      wcx.lpszClassName = "BalloonHelpClassDS"; // name of window class 
      wcx.hIconSm = NULL;                       // no small class icon

      // Register the window class (this may not work if dropshadows are not supported)
      s_ClassAtomShadowed = RegisterClassEx(&wcx);

      // Register shadow-less class
      wcx.style &= ~CS_DROPSHADOW;
      wcx.lpszClassName = "BalloonHelpClass";
      s_ClassAtom = RegisterClassEx(&wcx);
   }

   if ( bShadowed && NULL != s_ClassAtomShadowed )
      return s_ClassAtomShadowed;
   return s_ClassAtom;
}


// Displays the balloon on the screen, performing fade-in if enabled.
void CBalloonHelp::ShowBalloon(void)
{
   ShowWindow(SW_SHOWNOACTIVATE);
   if ( !(m_unOptions&unDELAY_CLOSE) )
      SetTimeout(m_unTimeout);     // start close timer
}

// Removes the balloon from the screen, performing the fade-out if enabled
void CBalloonHelp::HideBalloon(void)
{
   if ( m_unOptions&unDELAY_CLOSE )
   {
      m_unOptions &= ~(unDELAY_CLOSE|unCLOSE_ON_ANYTHING);  // close only via timer or button
      SetTimeout(m_unTimeout);     // start close timer
      return;
   }
   ShowWindow( SW_HIDE );
   if ( GetCapture() == this ) 
      ReleaseCapture();
   DestroyWindow();
}

//
// Keyboard hook
//

void CBalloonHelp::SetKeyboardHook()
{
   if ( NULL==m_hKeyboardHook )
   {
      m_hKeyboardHook = ::SetWindowsHookEx(WH_KEYBOARD,
         (HOOKPROC)BHKeybHookThunk<CBalloonHelp>::GetThunk(),
         NULL, ::GetCurrentThreadId());
   }
}

void CBalloonHelp::RemoveKeyboardHook()
{
   if ( NULL!=m_hKeyboardHook )
   {
      ::UnhookWindowsHookEx(m_hKeyboardHook);
      m_hKeyboardHook=NULL;
   }
}


//
// Mouse hook
//

void CBalloonHelp::SetMouseHook()
{
   if ( NULL==m_hMouseHook )
   {
      m_hMouseHook = ::SetWindowsHookEx(WH_MOUSE,
         (HOOKPROC)BHMouseHookThunk<CBalloonHelp>::GetThunk(),
         NULL, ::GetCurrentThreadId());
   }
}

void CBalloonHelp::RemoveMouseHook()
{
   if ( NULL!=m_hMouseHook )
   {
      ::UnhookWindowsHookEx(m_hMouseHook);
      m_hMouseHook=NULL;
   }
}

//
// Call Window Return hook
//

void CBalloonHelp::SetCallWndRetHook()
{
   if ( NULL==m_hCallWndRetHook )
   {
      m_hCallWndRetHook = ::SetWindowsHookEx(WH_CALLWNDPROCRET,
         (HOOKPROC)BHCallWndRetHookThunk<CBalloonHelp>::GetThunk(),
         NULL, ::GetCurrentThreadId());
   }
}

void CBalloonHelp::RemoveCallWndRetHook()
{
   if ( NULL!=m_hCallWndRetHook )
   {
      ::UnhookWindowsHookEx(m_hCallWndRetHook);
      m_hCallWndRetHook=NULL;
   }
}


/////////////////////////////////////////////////////////////////////////////
// CBalloonHelp message handlers

BEGIN_MESSAGE_MAP(CBalloonHelp, CWnd)
   ON_WM_ERASEBKGND()
   ON_WM_PAINT()
   ON_WM_NCPAINT()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_NCCALCSIZE()
   ON_WM_TIMER()
   ON_WM_NCHITTEST()
   ON_WM_MOUSEMOVE()
   ON_WM_DESTROY()
   ON_WM_CLOSE()
   ON_WM_SHOWWINDOW()
   ON_MESSAGE(WM_PRINT, OnPrint)
   ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
END_MESSAGE_MAP()

void CBalloonHelp::OnShowWindow(BOOL bShow, UINT)
{
   if ( NULL != m_fnAnimateWindow )
   {
      if ( bShow && !(m_unOptions&unDISABLE_FADEIN) )
         m_fnAnimateWindow( m_hWnd, 200, AW_BLEND);
      else if ( !bShow && !(m_unOptions&unDISABLE_FADEOUT) )
         m_fnAnimateWindow( m_hWnd, 200, AW_HIDE | AW_BLEND );
   }
}

// Erase client area of balloon
BOOL CBalloonHelp::OnEraseBkgnd(CDC* pDC) 
{
   CRect rect;
   GetClientRect(&rect);
   pDC->FillSolidRect(&rect, m_crBackground);
   return TRUE;
}

// draw balloon client area (title & contents)
void CBalloonHelp::OnPaint() 
{
   CPaintDC dc(this); // device context for painting
   DrawClientArea(&dc);
}

// draw balloon shape & border
void CBalloonHelp::OnNcPaint() 
{
   CWindowDC dc(this);
   DrawNonClientArea(&dc);
}

// draw the window into the specified device context
LRESULT CBalloonHelp::OnPrint(WPARAM wParam, LPARAM lParam)
{
   CDC* pDC = CDC::FromHandle((HDC)wParam);
   if ( lParam & PRF_NONCLIENT  ) 
      DrawNonClientArea(pDC);
   return Default();
}

// draw the client area into the specified device context
LRESULT CBalloonHelp::OnPrintClient(WPARAM wParam, LPARAM lParam)
{
   CDC* pDC = CDC::FromHandle((HDC)wParam);
   if ( lParam & PRF_ERASEBKGND ) 
      SendMessage( WM_ERASEBKGND, wParam );
   if ( lParam & PRF_CLIENT ) 
      DrawClientArea(pDC);
   return 0;
}

// Close button handler
void CBalloonHelp::OnLButtonDown(UINT, CPoint point) 
{
   if (m_unOptions & unSHOW_CLOSE_BUTTON)
   {
      CRect rect;
      GetClientRect(&rect);
      rect.left = rect.right-::GetSystemMetrics(SM_CXSIZE);
      rect.bottom = rect.top+::GetSystemMetrics(SM_CYSIZE);
      if ( rect.PtInRect(point) )
      {
         m_uCloseState |= DFCS_PUSHED;
         SetCapture();
         OnMouseMove(0, point);
      }
   }
}

// Close button handler,
// URL handler
void CBalloonHelp::OnLButtonUp(UINT, CPoint point) 
{
   if ( (m_unOptions & unSHOW_CLOSE_BUTTON) && (m_uCloseState & DFCS_PUSHED) )
   {
      ReleaseCapture();
      m_uCloseState &= ~DFCS_PUSHED;
      CRect rect;
      GetClientRect(&rect);
      rect.left = rect.right-::GetSystemMetrics(SM_CXSIZE);
      rect.bottom = rect.top+::GetSystemMetrics(SM_CYSIZE);
      if ( rect.PtInRect(point) )
         HideBalloon();
   }
   else if ( !m_strURL.IsEmpty() )
   {
      CRect rect;
      GetClientRect(&rect);
      if ( rect.PtInRect(point) )
      {
         ::ShellExecute(NULL, NULL, m_strURL, NULL, NULL, SW_SHOWNORMAL);
         HideBalloon();
      }
   }
}

//
// Ensure WM_MOUSEMOVE messages are sent for the entire window
//
UINT CBalloonHelp::OnNcHitTest(CPoint)
{
   return HTCLIENT;
}

//
// do mouse tracking:
//   Tracking for close button;
//
void CBalloonHelp::OnMouseMove(UINT, CPoint point)
{
   if (m_unOptions & unSHOW_CLOSE_BUTTON)
   {
      CRect rect;
      GetClientRect(&rect);
      rect.left = rect.right-::GetSystemMetrics(SM_CXSIZE);
      rect.bottom = rect.top+::GetSystemMetrics(SM_CYSIZE);
      CClientDC dc(this);
      UINT uState = DFCS_CAPTIONCLOSE;
      BOOL bPushed = m_uCloseState&DFCS_PUSHED;
      m_uCloseState &= ~DFCS_PUSHED;
      if ( rect.PtInRect(point) )
      {
         uState |= DFCS_HOT;
         if ( bPushed )
            uState |= DFCS_PUSHED;
      }
      else
      {
         uState |= DFCS_FLAT;
      }
      if ( uState != m_uCloseState )
      {
         dc.DrawFrameControl(&rect, DFC_CAPTION, uState);
         m_uCloseState = uState;
      }
      if ( bPushed )
         m_uCloseState |= DFCS_PUSHED;
   }
}

// Ensures client area is the correct size relative to window size,
// presearves client contents if possible when moving.
void CBalloonHelp::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
   // nTIP_MARGIN pixel margin on all sides
   ::InflateRect(&lpncsp->rgrc[0], -nTIP_MARGIN,-nTIP_MARGIN);

   // nTIP_TAIL pixel "tail" on side closest to anchor
   switch ( GetBalloonQuadrant() )
   {
   case BQ_TOPRIGHT:
   case BQ_TOPLEFT:
      lpncsp->rgrc[0].top += nTIP_TAIL;
      break;
   case BQ_BOTTOMRIGHT:
   case BQ_BOTTOMLEFT:
      lpncsp->rgrc[0].bottom -= nTIP_TAIL;
      break;
   }

   // sanity: ensure rect does not have negative size
   if ( lpncsp->rgrc[0].right < lpncsp->rgrc[0].left )
      lpncsp->rgrc[0].right = lpncsp->rgrc[0].left;
   if ( lpncsp->rgrc[0].bottom < lpncsp->rgrc[0].top )
      lpncsp->rgrc[0].bottom = lpncsp->rgrc[0].top;

   if ( bCalcValidRects )
   {
      // determine if client position has changed relative to the window position
      // if so, don't bother presearving anything.
      if ( !::EqualRect(&lpncsp->rgrc[0], &lpncsp->rgrc[2]) )
      {
         ::SetRectEmpty(&lpncsp->rgrc[2]);
      }
   }
}

// handle kill timer
void CBalloonHelp::OnTimer(UINT nIDEvent) 
{
   // really shouldn't be any other timers firing, but might as well make sure
   if ( nIDEvent == ID_TIMER_CLOSE )
   {
      KillTimer(m_unTimerClose);
      HideBalloon();
   }
}

// Called as the window is being destroyed.  Completes destruction after removing keyboard hook.
void CBalloonHelp::OnDestroy()
{
   // remove hooks
   RemoveMouseHook();
   RemoveKeyboardHook();
   RemoveCallWndRetHook();

   // destroy
   CWnd::OnDestroy();
}

// close the balloon, performing any set transition effect.
void CBalloonHelp::OnClose()
{
   HideBalloon();
}

// Called after window has been destroyed.  Destroys the object if option is set.
void CBalloonHelp::PostNcDestroy()
{
   CWnd::PostNcDestroy();
  
   // free object if requested
   // be careful with this one :D
   if ( m_unOptions & unDELETE_THIS_ON_CLOSE )
      delete this;
}

// Keyboard hook: used to implement the unCLOSE_ON_KEYPRESS option
LRESULT CBalloonHelp::KeyboardHookProc( int code, WPARAM wParam, LPARAM lParam)
{
   // Skip if the key was released or if it's a repeat
   // Bit 31:  Specifies the transition state. The value is 0 if the key  
   //       is being pressed and 1 if it is being released (see MSDN).
   if ( code>=0 && !(lParam&0x80000000) && NULL != m_hWnd )
   {
      PostMessage(WM_CLOSE);
   }
   return ::CallNextHookEx(m_hKeyboardHook, code, wParam, lParam);
}

// Mouse hook: used to implement un-obtrusive mouse tracking
LRESULT CBalloonHelp::MouseHookProc(int code, WPARAM wParam, LPARAM lParam)
{
   if (code>=0 && NULL != m_hWnd )
   {
      switch ( (UINT)wParam )
      {
      case WM_NCMOUSEMOVE:
      case WM_MOUSEMOVE:
         if ((m_unOptions & unCLOSE_ON_MOUSE_MOVE))
         {
            CPoint pt;
            ::GetCursorPos(&pt);
            if ((abs(pt.x-m_ptMouseOrig.x) > m_nMouseMoveTolerance || abs(pt.y-m_ptMouseOrig.y) > m_nMouseMoveTolerance) )
               PostMessage(WM_CLOSE);
         }
         break;
      case WM_NCLBUTTONDOWN:
      case WM_LBUTTONDOWN:
         if ((m_unOptions & unCLOSE_ON_LBUTTON_DOWN))
            PostMessage(WM_CLOSE);
         break;
      case WM_NCMBUTTONDOWN:
      case WM_MBUTTONDOWN:
         if ((m_unOptions & unCLOSE_ON_MBUTTON_DOWN))
            PostMessage(WM_CLOSE);
         break;
      case WM_NCRBUTTONDOWN:
      case WM_RBUTTONDOWN:
         if ((m_unOptions& unCLOSE_ON_RBUTTON_DOWN))
            PostMessage(WM_CLOSE);
         break;
      case WM_NCLBUTTONUP:
      case WM_LBUTTONUP:
         if ((m_unOptions & unCLOSE_ON_LBUTTON_UP))
            PostMessage(WM_CLOSE);
         break;
      case WM_NCMBUTTONUP:
      case WM_MBUTTONUP:
         if ((m_unOptions & unCLOSE_ON_MBUTTON_UP))
            PostMessage(WM_CLOSE);
         break;
      case WM_NCRBUTTONUP:
      case WM_RBUTTONUP:
         if ((m_unOptions & unCLOSE_ON_RBUTTON_UP))
            PostMessage(WM_CLOSE);
         break;
      }
   }
   return ::CallNextHookEx(m_hMouseHook, code, wParam, lParam);
}

// Window Return hook: used to implement window following
LRESULT CBalloonHelp::CallWndRetProc(int code, WPARAM wParam, LPARAM lParam)
{
   if (code>=0 && NULL != m_hWnd )
   {
      CWPRETSTRUCT* pcwpr = (CWPRETSTRUCT*)lParam;
      if ( WM_MOVE == pcwpr->message && pcwpr->hwnd == m_hwndAnchor )
         PositionWindow();
   }

   return ::CallNextHookEx(m_hCallWndRetHook, code, wParam, lParam);
}
