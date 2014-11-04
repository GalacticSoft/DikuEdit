/*********************************************************************

   Copyright (C) 2001 Smaller Animals Software, Inc.

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

   3. This notice may not be removed or altered from any source distribution.

   http://www.smalleranimals.com
   smallest@smalleranimals.com

   --------

   This code is based, in part, on:

      "Syntax Coloring Text Edit Window Class " - Randy More (9, May 1998)
      http://www.codeguru.com/editctrl/syntax_coloring.shtml

   Though probably only 5% of the original code remains.

	Slightly modified by Marissa du Bois To Handle Ansi Color
**********************************************************************/

// ColorEditWnd syntax coloring class
//

#include "stdafx.h"
#include "resource.h"
#include "math.h"
#include "memdc.h"
#include <locale.h>

#pragma warning(disable:4786)
#include "ColorEditWnd.h"
#pragma warning(disable:4786)

//#include "statuslog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_X 10

void _GfxCmdUIUpdateMenu(CCmdTarget* pTarget, CMenu* pMenu, bool bDisableIfNoHndler/*=true*/);

//IMPLEMENT_CONTROL(ColorEditWnd, CWnd);
IMPLEMENT_DYNAMIC(ColorEditWnd, CWnd);

/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd

BEGIN_MESSAGE_MAP(ColorEditWnd, CWnd)
//{{AFX_MSG_MAP(ColorEditWnd)
   ON_WM_ERASEBKGND()
   ON_WM_KEYDOWN()
   ON_WM_CHAR()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONDBLCLK()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_PAINT()
   ON_WM_SIZE()
   ON_WM_GETDLGCODE()
   ON_WM_VSCROLL()
   ON_WM_HSCROLL()
   ON_WM_CREATE()
   ON_WM_SETCURSOR()
   ON_WM_SHOWWINDOW()
   ON_WM_MOUSEWHEEL()
   ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdatePaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateSelectall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
   ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateRedo)
	ON_COMMAND(ID_EDIT_COPY, OnCopy)
	ON_COMMAND(ID_EDIT_CUT, OnCut)
	ON_COMMAND(ID_EDIT_PASTE, OnPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnSelectall)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_COMMAND(ID_EDIT_REDO, OnRedo)
   ON_WM_KILLFOCUS()
   ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd construction/destruction

/////////////////////////////////////////////////////////////////////////////

ColorEditWnd::ColorEditWnd()
{
   // don't use this one
   ASSERT(0);

   m_className.Format("ColorEditWnd::%p", this);
   //g_statusLog.StatusOut("%s, Constructing", m_className);

   // defaults. these get set for real in OnShow
   m_iCharDX = 10;
   m_iCharDY = 10;

   m_ID = 0;

   m_iTabSize = 4;

   m_bUseKBAccel = true;

   m_bCaretOn = false;
  
   m_backgroundColor = RGB(255,255,255);
   m_hilightColor = RGB(0,0,0);
   m_hilightTextColor = RGB(255,255,255);

   m_bReadOnly = false;

   m_iFirstCharacter= 0;
   m_iFirstLine = 0;

   Reset();
}

/////////////////////////////////////////////////////////////////////////////

ColorEditWnd::ColorEditWnd(CWnd * parent, 
                           const CRect & rect,
                           int nID, 
                           int iTabSize,
                           int iFontSize, 
                           const char *pFontName,
                           bool bHasHorizScroll, bool bProgEdit)
{
   m_className.Format("ColorEditWnd::%p", this);
   //g_statusLog.StatusOut("%s, Constructing", m_className);

   // defaults. these get set for real in OnShow
   m_iCharDX = 10;
   m_iCharDY = 10;

   m_ID = nID;

   m_iTabSize = iTabSize;

   m_bCaretOn = false;
    
   m_bProgEdit = bProgEdit;

   if(!m_bProgEdit)
   {
		m_backgroundColor = RGB(0,0,0);
		m_hilightColor = RGB(0,0,0);
		m_hilightTextColor = RGB(255,255,255);	
		m_bReadOnly = true;
		m_bUseKBAccel = false;
   }
   else
   {
		m_backgroundColor = RGB(255,255,255);
		m_hilightColor = RGB(0,0,0);
		m_hilightTextColor = RGB(255,255,255);	
		m_bReadOnly = false;
		m_bUseKBAccel = true;
		m_bCaretOn = true;
   }

   m_iFirstCharacter= 0;
   m_iFirstLine = 0;
   
   DWORD dwFlags = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_VSCROLL;
   if (bHasHorizScroll)
      dwFlags = dwFlags | WS_HSCROLL;

   m_hAccel = LoadAccelerators( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_EDIT_ACCELS) );

   Create(dwFlags, parent, rect, nID, iTabSize, iFontSize, pFontName);

   Reset();

}

/////////////////////////////////////////////////////////////////////////////

BOOL ColorEditWnd::Create(DWORD dwFlags,
                          CWnd * parent, 
                          const CRect & rect,
                          int nID, 
                          int iTabSize,
                          int iFontSize, 
                          const char *pFontName)
{
   //g_statusLog.StatusOut("%s, Create", m_className);

   SetScrollRange(SB_HORZ,0,200,false);
   SetScrollRange(SB_VERT,0,200,false);

   BOOL bOK = m_font.CreatePointFont(iFontSize, pFontName, NULL);
   if (!bOK)
   {
      ASSERT(0);
      return FALSE;
   }

   return CWnd::Create(NULL, NULL, dwFlags, rect, parent, nID, NULL);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::Reset()
{
   //g_statusLog.StatusOut("%s, Reset", m_className);

   RemoveAllText();
   _SetCursorPos(0,0);
   _SetAnchorPos(0,0);
   m_iFirstCharacter = 0;
   m_iFirstLine = 0;
   m_bIsSelected = false;
   m_bLBDown = false;
   m_bCaretOn = false;
   m_bMaintainIndent = false;
   ClearUndoStack(m_redoStack);
   ClearUndoStack(m_undoStack);
   m_currentUndoFrame.Clear();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::LoadText(const char *buffer)
{
   //g_statusLog.StatusOut("%s, LoadText", m_className);

   Reset();

   CString accum;

   int xpos = CursorPosX();

   bool bFoundNewLine = false;
   int iLen = strlen(buffer);
   for (int i=0; i < iLen; i++)
   {
      if (buffer[i] == '\n')
      {
         InsertTextLine(accum, CursorPosY(), false);
         accum="";
         xpos = 0;
         _SetCursorPos(0, CursorPosY()+1);
         bFoundNewLine = true;
      }
      else if (buffer[i] == '\t')
      {
         CString tab = MakeTab(xpos);
         xpos+=tab.GetLength();
         accum+=tab;
      }
      else if (isprint(buffer[i]))
      {
         xpos++;
         accum+=buffer[i];
      }
   }

   if (!bFoundNewLine)
   {
      InsertTextLine(accum, CursorPosY(), false);
   }

   _SetCursorPos(0,0);
   _SetAnchorPos(0,0);

   m_iFirstCharacter = 0;
   m_iFirstLine = 0;

   m_bIsSelected = false;
   m_bLBDown = false;     

   m_text.FullUpdate();

   EndAction();

   UpdateScrollSizes();

   Invalidate();

   if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::UnloadText(CString &pText) /*const*/
{
   //g_statusLog.StatusOut("%s, UnloadText", m_className);

   int index;
   pText.Empty();
   int iLines = GetTextSize();
   for(index = 0; index < iLines; index++)
   {
      pText = pText + GetTextLine(index);
      if (iLines > 1)
      {
         pText = pText + '\n';
      }
   }

}

/////////////////////////////////////////////////////////////////////////////

ColorEditWnd::~ColorEditWnd()
{
   //g_statusLog.StatusOut("%s, ~ColorEditWnd", m_className);

   // is this necessary??
   DestroyCaret();

   if (m_font.GetSafeHandle())
   {
      m_font.DeleteObject();
   }
}


/////////////////////////////////////////////////////////////////////////////

CPoint ColorEditWnd::GetDeviceScrollPosition() const
{
   CPoint pt(GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
   ASSERT(pt.x >= 0 && pt.y >= 0);
   
   /*
   if (m_bCenter)
   {
   CRect rect;
   GetClientRect(&rect);
   
     // if client area is larger than total device size,
     // the scroll positions are overridden to place origin such that
     // output is centered in the window
     // GetDeviceScrollPosition() must reflect this
     
       if (m_totalDev.cx < rect.Width())
       pt.x = -((rect.Width() - m_totalDev.cx) / 2);
       if (m_totalDev.cy < rect.Height())
       pt.y = -((rect.Height() - m_totalDev.cy) / 2);
       }
   */
   
   return pt;
}

/////////////////////////////////////////////////////////////////////////////

CPoint ColorEditWnd::GetScrollPosition() const   // logical coordinates
{
   CPoint pt = GetDeviceScrollPosition();
   return pt;
}

/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd drawing

void ColorEditWnd::OnPaint()
{
   CPaintDC paint_dc(this); // device context for painting

   CMemDCx dc(&paint_dc);  // CMemDC suggested by Robert Bouwens
   
   try
   {
      dc.SelectObject(m_font);
      dc.SetBkMode(TRANSPARENT);
   
      int y = 0;
   
      CRect client;
      GetClientRect(client);
      dc.FillSolidRect( client, m_backgroundColor );
   
      CPoint t = GetScrollPosition();
   
      int iLast = min(LastVisibleLine() + 1, GetTextSize());
   
      // TRACE("Painting %d to %d\n", m_iFirstLine, iLast);
   
      CRect intersect;
   
      for(int p = m_iFirstLine; p < iLast; p++)
      {
         if (intersect.IntersectRect(client, GetLineRect(p)))
         {
            CString line = GetTextLine(p);
         
            //const CScriptText::lineVector & colors = m_text._GetLineColors(p);
			CScriptText::lineVector colors = m_text._GetLineColors(p);

			//StripAnsiChars(line, colors);
         
            _DrawLine(&dc, line, colors, p, y);
         }
      
         y+=m_iCharDY;
      }
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in OnPaint", m_className);
      ASSERT(0);
   }

   //DrawCursor(&dc, true);
}

/////////////////////////////////////////////////////////////////////////////

int ColorEditWnd::VisibleColumns() const
{
   if (!::IsWindow(m_hWnd))
      return -1;

   CRect client;
   GetClientRect(client);

   return (client.Width() / m_iCharDX) - 1;
}

/////////////////////////////////////////////////////////////////////////////

int ColorEditWnd::FirstVisibleLine() const
{
   if (!::IsWindow(m_hWnd))
      return -1;

   CRect client;
   GetClientRect(client);
   
   CPoint t = GetScrollPosition();
   
   return m_iFirstLine;
}

/////////////////////////////////////////////////////////////////////////////

int ColorEditWnd::LastVisibleLine() const
{
   if (!::IsWindow(m_hWnd))
      return -1;

   CPoint t = GetScrollPosition();
   
   return min(GetTextSize(), FirstVisibleLine() + VisibleLines()); 
}

/////////////////////////////////////////////////////////////////////////////

int ColorEditWnd::VisibleLines(bool bTotal) const
{
   if (!::IsWindow(m_hWnd))
      return 0;

   CRect client;
   GetClientRect(client);
   
   if (bTotal)
   {
      return (client.Height() / m_iCharDY); 
   }
   else
   {
      return min(GetTextSize(), client.Height() / m_iCharDY); 
   }
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CPoint ColorEditWnd::_DrawLine(CDC *pDC, const CString &csLine, const CScriptText::lineVector &colors, int lineidx, int y)
{
   //TRACE("Drawing %d at %d [%s]\n", lineidx, y, csLine);
   
#ifdef _DEBUG
   // if this happens, there is a problem with the colorizer, or worse, with the 
   // way the colorizer is being called to update upon text changes.
   if (colors.size() != csLine.GetLength())
   {
      TRACE("%d != %d\n", colors.size(), csLine.GetLength());
      ASSERT(0);
   }
#endif

   int x  = MIN_X;
   
   for(int j = m_iFirstCharacter; j < csLine.GetLength(); j++)
   {
	   CRect outRect(x, y + 0, x + m_iCharDX, y + m_iCharDY);
	   
	  if (IsSelected(j, lineidx))
      {
			pDC->SetTextColor(m_hilightTextColor);
			pDC->FillSolidRect(outRect, m_hilightColor);
      }
      else
      {
			pDC->SetTextColor(colors[j]);
			pDC->FillSolidRect(outRect, m_backgroundColor);
	  }	
      
       pDC->TextOut(x,y,csLine[j]);
       x+=m_iCharDX;
   }
   
   return CPoint(x,y);
}

/////////////////////////////////////////////////////////////////////////////

CRect ColorEditWnd::GetLineRect(int iLine) const
{
   if (!::IsWindow(m_hWnd))
   {
      ASSERT(0);
      return CRect(-1,-1,-1,-1);
   }

   CRect client;
   GetClientRect(client);
   
   int y = m_iCharDY * (iLine - FirstVisibleLine());
   int x = 0;
   
   return CRect(client.left, y, client.right, y + m_iCharDY);
}

/////////////////////////////////////////////////////////////////////////////

CRect ColorEditWnd::GetLineRect(int iLine1, int iLine2) const
{
   if (!::IsWindow(m_hWnd))
   {
      ASSERT(0);
      return CRect(-1,-1,-1,-1);
   }

   if (iLine1 > iLine2)
   {
      std::swap(iLine1, iLine2);
   }

   CRect client;
   GetClientRect(client);
   
   int iFirstVisible = FirstVisibleLine();
   int y1 = m_iCharDY * (iLine1 - iFirstVisible);
   int y2 = m_iCharDY * (iLine2 - iFirstVisible);

   int x = 0;
   
   return CRect(client.left, y1, client.right, y2 + m_iCharDY);
}


/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd message handlers

void ColorEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   try
   {
      bool ctrl = (GetKeyState(VK_CONTROL) & 0xf000) == 0xf000;
      bool shift = (GetKeyState(VK_SHIFT) & 0xf000) == 0xf000;
   
      switch (nChar)
      {                 
      case VK_END:
         DrawCursor(false);
         if (ctrl)
         {
            // end of text
            int iEndLine = GetTextSize() - 1;
            int iEndChar = GetTextLine(iEndLine).GetLength();
         
            if(m_bProgEdit)
			_SetCursorPos(iEndChar, iEndLine);
         }
         else
         {
            if(m_bProgEdit)
			 _SetCursorPosX(GetTextLine(CursorPosY()).GetLength());
         }
         break;
      case VK_HOME:
         DrawCursor(false);
         if (ctrl)
         {
            // start of text
            if(m_bProgEdit)
			 _SetCursorPos(0, 0);
         }
         else
         {
            if(m_bProgEdit)
			 _SetCursorPosX(0);
         }
         break;
      case VK_LEFT: //left arrow
         DrawCursor(false);
         UpdateAnchor(true);
         if (ctrl)
         {
            // find prev word
         
            if (CursorPosX() == 0)
            {
               // back up one line
               if (CursorPosY() > 0)
               {
                  if(m_bProgEdit)
				   _SetCursorPos(GetTextLine(CursorPosY() - 1).GetLength(), CursorPosY()-1);
               }
               else
               {
                  if(m_bProgEdit)
				   _SetCursorPosX(0);
               }
            
               // done. start at the end of the prev line
               break;
            }
         
            // find first non alpha char
            if (CursorPosX() > 0)
            {
               CString cur = GetTextLine(CursorPosY());
               char c;
            
               int x = CursorPosX();
               bool bFoundNonWS = false;
            
               while (1)
               {
                  x--;
               
                  if (x >= 0)
                  {
                     c = cur.GetAt(x);
                     if (!isspace(c))
                     {
                        bFoundNonWS = bFoundNonWS || true;
                     }
                  }
                  else
                  {
                     x = 0;
                     break;
                  }
               
                  if (!isalnum(c) && bFoundNonWS)
                  {   
                     //if (isspace(c))
                     if (x != CursorPosX() - 1)
                     {
                        x++;
                     }

                     break;
                  }
               }
            
              if(m_bProgEdit)
			   _SetCursorPosX(x);
            }
         
         }
         else
         {
            // normal - prev letter
           if(m_bProgEdit)
			 _SetCursorPos(CursorPosX()-1, CursorPosY());

            if (CursorPosX() < 0)
            {
               if (CursorPosY() >0)
               {
                  if(m_bProgEdit)
				   _SetCursorPos(GetTextLine(CursorPosY() - 1).GetLength(), CursorPosY() -1);
               }
               else
               {
                  if(m_bProgEdit)
				   _SetCursorPosX(0);
               }
            }
         }
         break;
      case VK_RIGHT: //right arrow
         DrawCursor(false);
         UpdateAnchor(true);
         if (ctrl)
         {
            // next word
         
            // skip to next line ?
            if (CursorPosX() >= GetTextLine(CursorPosY()).GetLength())
            {
               if(m_bProgEdit)
				_SetCursorPosY(CursorPosY() + 1);

               if (CursorPosY() >= GetTextSize())
               {
                  int iLastLine = GetTextSize() - 1;
                  if(m_bProgEdit)
				  _SetCursorPos(GetTextLine(iLastLine).GetLength(), iLastLine);
               }
               else
               {
                  if(m_bProgEdit)
				   _SetCursorPosX(0);
               }

               // start at start of next line
               break;
            }
         
            // find first non alpha char
            CString cur = GetTextLine(CursorPosY());
            if (CursorPosX() < cur.GetLength())
            {
            
               char c;
            
               int x = CursorPosX();
               bool bFoundNonWS = false;
            
               while (1)
               {
                  if (x < cur.GetLength())
                  {
                     c = cur.GetAt(x);
                     if (!isspace(c))
                     {
                        bFoundNonWS = bFoundNonWS || true;
                     }
                  }
                  else
                  {
                     x = cur.GetLength();
                     break;
                  }
               
                  if (!isalnum(c) && bFoundNonWS)
                  {
                     //if (isspace(c))
                     if (x == CursorPosX())
                     {
                        x++;
                        // nothing...
                     }
                     break;
                  }

                  x++;
               }
            
               if(m_bProgEdit)
			   _SetCursorPosX(x);
            }
         }
         else
         {
            // normal - next letter
            if (CursorPosY() >= GetTextSize())
            {
               int iLastLine = GetTextSize() - 1;
               if(m_bProgEdit)
			   _SetCursorPos(GetTextLine(iLastLine).GetLength(), iLastLine);
            }

           if(m_bProgEdit)
			_SetCursorPos(CursorPosX() + 1, CursorPosY());
         
            if (CursorPosX() > GetTextLine(CursorPosY()).GetLength())
            {
               if (CursorPosY() < GetTextSize() - 1)
               {
                  if(m_bProgEdit)
				   _SetCursorPos(0, CursorPosY()+1);
               }
               else
               {
                  if(m_bProgEdit)
				   _SetCursorPosX(CursorPosX()-1);
               }
            }
         }
         break;
      case VK_UP: //up arrow
         if (CursorPosY() > 0)
         {
            DrawCursor(false);
            UpdateAnchor(true);
            if(m_bProgEdit)
			_SetCursorPos(min(CursorPosX(), GetTextLine(CursorPosY()-1).GetLength()), CursorPosY() - 1);
         }
         break;
      case VK_DOWN: //down arrow
         if (CursorPosY() < GetTextSize() - 1)
         {
            DrawCursor(false);
            UpdateAnchor(true);
            if(m_bProgEdit)
			_SetCursorPos(min(CursorPosX(), GetTextLine(CursorPosY()+1).GetLength()), CursorPosY() + 1);
         }
         break;
      case VK_PRIOR: // pg up
         {
            DrawCursor(false);
            UpdateAnchor(true);
            int iYPos = max(CursorPosY() - (VisibleLines()), 0);
            ////_SetCursorPos(CursorPosX(), iYPos);
            if(m_bProgEdit)
			_SetCursorPos(min(CursorPosX(), GetTextLine(iYPos).GetLength()), iYPos);
            ScrollToLine(iYPos);
         }
         break;
      case VK_NEXT: // pg down
         {
            DrawCursor(false);
            UpdateAnchor(true);
            int iYPos = min(CursorPosY() + VisibleLines(), GetTextSize() - 1);
            //_SetCursorPos(CursorPosX(), iYPos);
            if(m_bProgEdit)
			_SetCursorPos(min(CursorPosX(), GetTextLine(iYPos).GetLength()), iYPos);
            ScrollToLine(iYPos);
         }
         break;
      case VK_BACK:
         {
            if (!m_bReadOnly)
            {
               StartAction();
               if (Selected()) 
               {
                  RemoveSelected();
               }
               else
               {
               
                  DeletePrevChar();
               }
               EndAction();
            }
         }
         break;
      case VK_DELETE:
         {
            if (!m_bReadOnly)
            {
               StartAction();
               if (Selected()) 
               {
                  RemoveSelected();
               }
               else
               {
               
                  DeleteNextChar();
               }
               EndAction();
            }
         }
         break;
      case VK_RETURN:
         if (!m_bReadOnly)
         {
            if (ctrl)
            {
               PostMessage(WM_CHAR, nChar, 0);
            }
         }
         break;
      default:
         CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
         return;
         break;
      }
   
      ScrollToCursor();
      UpdateAnchor(true);
      if(m_bProgEdit)
	  DrawCursor(true);       
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in OnKeyDown", m_className);
      ASSERT(0);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   try
   {
      setlocale( LC_ALL, ".OCP" );

      if (m_bReadOnly)
      {
         return;
      }

      if (!isprint(nChar) &&
         (nChar!=VK_RETURN) &&
         (nChar!='\t'))
      {
         // don't char
         return;
      }

      DrawCursor(false);
 
      bool ctrl = (GetKeyState(VK_CONTROL) & 0xf000) == 0xf000;

      switch(nChar)
      {
      case '\t': //tab key
         StartAction();
         if (Selected()) 
         {
            RemoveSelected();
         }
         InsertTab();
         EndAction();
         break;
      case VK_RETURN: //return (enter)
         StartAction();
         if (Selected()) 
         {
            RemoveSelected();
         }
         DoEnter();
         EndAction();
         break;
      default:
         StartAction();
         if (Selected()) 
         {
            RemoveSelected();
         }
         InsertChar(nChar);
         EndAction();
         break;
      }

      // redo the Selection
      if (Selected())
      {
         CRect firstLineRect = GetLineRect(min(AnchorPosY(), CursorPosY())-1);
         CRect secondLineRect = GetLineRect(max(AnchorPosY(), CursorPosY())+1);
         CRect joined; joined.UnionRect(firstLineRect, secondLineRect);
         InvalidateRect(joined, true);
      }

      if(m_bProgEdit)
	  DrawCursor(true);
   }
   catch (...)
   {
      ASSERT(0);
      //g_statusLog.StatusOut("%s, Exception in OnChar", m_className);
   }

   CWnd::OnChar(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::InsertChar(int pChar, bool pRedraw)
{
   CString str = char(pChar);
   InsertString(str,pRedraw);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::InsertString(CString &csString, bool pRedraw)
{
   BOOL clearFullLine = FALSE;

   if (csString.GetLength()==0)
   {
      return;
   }

   // they've asked us to insert text at a line higher than what we have
   if (GetTextSize() <= CursorPosY())
   {
      InsertTextLine(csString, CursorPosY(), pRedraw);

      CRect lineRect = GetLineRect(CursorPosY());
      lineRect.InflateRect(0, 4);
      InvalidateRect(lineRect, clearFullLine);
  
      _SetCursorPosX(csString.GetLength());
      UpdateAnchor(false);

      return;
   }

   CString L = GetTextLine(CursorPosY()).Left(CursorPosX());
   CString R = GetTextLine(CursorPosY()).Mid(CursorPosX());
   
   if (R.GetLength())
   {
      CRect lineRect = GetLineRect(CursorPosY());
      lineRect.InflateRect(0, 4);
      InvalidateRect(lineRect, clearFullLine);
   }
   
   SetTextLine(L + csString + R, CursorPosY());

   _SetCursorPosX(CursorPosX() + csString.GetLength());
   
   ScrollToCursor();
   
   UpdateAnchor(false);
   if (pRedraw) 
   {
      CRect lineRect = GetLineRect(CursorPosY());
      lineRect.InflateRect(0, 4);
      InvalidateRect(lineRect, clearFullLine);
   }
}

/////////////////////////////////////////////////////////////////////////////

//delete the following character
void ColorEditWnd::DeletePrevChar()
{
   if (CursorPos()==CPoint(0,0))
   {
      // nothign to do
      return;
   }

   CString L = GetTextLine(CursorPosY()).Left(CursorPosX() - 1);
   CString R = GetTextLine(CursorPosY()).Mid(CursorPosX());
   
   SetTextLine(L + R, CursorPosY());
   
   _SetCursorPosX(CursorPosX()-1);

   if (CursorPosX() < 0)
   {
      if (CursorPosY() > 0)
      {
         // cursor to the end of the prev line
         int iXPos = GetTextLine(CursorPosY()-1).GetLength();
         _SetCursorPos(iXPos, CursorPosY()-1);
         
         // merge the old line and this one
         SetTextLine(GetTextLine(CursorPosY()) + GetTextLine(CursorPosY()+1), CursorPosY());
         RemoveTextLine(CursorPosY() + 1); 
         Invalidate();

         _SetCursorPosX(iXPos);
      }
      else
      {
         _SetCursorPosX(0);
      }
   }
   else
   {
      
   }
   
   CRect lineRect = GetLineRect(CursorPosY());
   lineRect.InflateRect(0,4);
   InvalidateRect(lineRect, true);
   
   UpdateAnchor(false);

   if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

//delete the following character
void ColorEditWnd::DeleteNextChar()
{
   if (CursorPosY() >= GetTextSize())
   {
      // nothing to do
      return;
   }

   if (CursorPosX() >= GetTextLine(CursorPosY()).GetLength())
   {
      if (CursorPosY() < GetTextSize() - 1)
      {
         SetTextLine(GetTextLine(CursorPosY()) + GetTextLine(CursorPosY()+1), CursorPosY());
         RemoveTextLine(CursorPosY() + 1); 
         Invalidate();
      }
   }
   else
   {
      SetTextLine(GetTextLine(CursorPosY()).Left(CursorPosX()) + 
                     GetTextLine(CursorPosY()).Right(GetTextLine(CursorPosY()).GetLength()-(CursorPosX()+1)), CursorPosY());
   }
   UpdateAnchor(false);
   CRect lineRect = GetLineRect(CursorPosY());
   lineRect.InflateRect(0,4);
   InvalidateRect(lineRect, true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoEnter()
{
   CString temp;
   temp = GetTextLine(CursorPosY()).Right(GetTextLine(CursorPosY()).GetLength() - CursorPosX());
   SetTextLine(GetTextLine(CursorPosY()).Left(CursorPosX()), CursorPosY());
   
   _SetCursorPos(0, CursorPosY() + 1);
   
   if (m_bMaintainIndent)
   {
      if (CursorPosY() > 0)
      {
         int insert = 0;
         while (insert < GetTextLine(CursorPosY()-1).GetLength())
         {
            if (GetTextLine(CursorPosY()-1).GetAt(insert) != 32)
            {
               break;
            }
            insert++;
         }
         while(insert)
         {
            temp = " " + temp;
            insert--;
            _SetCursorPosX(CursorPosX() + 1);
         }
      }
   }
   
   InsertTextLine(temp, CursorPosY());
   ScrollToCursor();
   
   CRect lineRect = GetLineRect(CursorPosY()-1);
   CRect client;
   GetClientRect(client);
   lineRect.bottom = client.bottom;
   
   InvalidateRect(lineRect, true);
   UpdateAnchor(false);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DrawCursor(bool pShow)
{
   if (GetFocus()!=this)
   {
      return;
   }

   CRect rect;
   rect.left = ((CursorPosX() - m_iFirstCharacter) * m_iCharDX) - 1;
   rect.right = rect.left + 2;
   rect.top = ((CursorPosY()- m_iFirstLine) * m_iCharDY);
   rect.bottom = rect.top + m_iCharDY;
   rect.left += MIN_X;
   rect.right += MIN_X;
   
   if (pShow)
   {
      if (!m_bCaretOn)
      {
         CreateSolidCaret(2, m_iCharDY);
         ShowCaret();
         m_bCaretOn = true;
      }
   }
   else
   {
      if (m_bCaretOn)
      {
         HideCaret();
         DestroyCaret();
         m_bCaretOn = false;
      }
   }

   SetCaretPos(CPoint(rect.left,rect.top));
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
   //convert click to cursor position
   point.x -= MIN_X;
   m_bLBDown = true;

   m_startPointDrag = point;

   SetFocus();
   
   SetCapture();

   DrawCursor(false);

   int x = CursorPosX();
   int y = CursorPosY();

   x = (point.x + m_iCharDX/2) / m_iCharDX + m_iFirstCharacter;
   y = point.y / m_iCharDY + m_iFirstLine;
   y = min(y, GetTextSize() - 1);
   x = min(x, GetTextLine(y).GetLength());

   if(m_bProgEdit)
   _SetCursorPos(x, y);

   //TRACE("Setting cursor(1): %d,%d\n", CursorPosX(), CursorPosY());

   int shift = GetKeyState(VK_SHIFT);
   if (shift & 0xf0) //shifted
   {
      Invalidate(false);
   }
   else //normal
   {
      _SetAnchorPos(CursorPosX(),CursorPosY());
      Selected();
   }
   if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
   point.x -= MIN_X;
   if (m_bLBDown) //dragging to select
   {
      int oldX = CursorPosX();
      int oldY = CursorPosY();

      double x;
      if (m_startPointDrag.x < point.x)
      {
         // dragging to the right
         x = floor((((double)point.x + (double)m_iCharDX / 1.0)) 
                              / (double)m_iCharDX) + 
                              m_iFirstCharacter - 1;

      }
      else
      {
         // dragging to the left
         x = ceil((((double)point.x - (double)m_iCharDX / 1.0)) 
                              / (double)m_iCharDX) + 
                              m_iFirstCharacter;
      }


      int y = point.y / m_iCharDY + m_iFirstLine;

      // clip
      y = max(0, y);
      y = min(y, GetTextSize() - 1);

      x = max(0, x);
      x = min(x, GetTextLine(y).GetLength());

      if(m_bProgEdit)
	  _SetCursorPos(x, y);

      //TRACE("Setting cursor: %d,%d pt:%d,%d old:%d,%d anchor:%d,%d\n", CursorPosX(), CursorPosY(), point.x, point.y, oldX, oldY, AnchorPosX(), AnchorPosY());

      if ((oldX != CursorPosX()) || (oldY != CursorPosY()))
      {
         if(m_bProgEdit)
		  DrawCursor(false);
         CRect rect = GetLineRect(oldY, CursorPosY());
         InvalidateRect(rect, false);
         if(m_bProgEdit)
		 DrawCursor(true);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
   point.x -= MIN_X;
   m_bLBDown = false;

   ReleaseCapture();
}

/////////////////////////////////////////////////////////////////////////////

bool ColorEditWnd::Selected()
{
   bool bIsSelected;
   if (AnchorPos() != CursorPos())
   {
      bIsSelected = true;
   }
   else
   {
      bIsSelected = false;
   }

   if (bIsSelected != m_bIsSelected)
   {
      m_bIsSelected = bIsSelected;
      if (bIsSelected)
      {
         // update the highlight
         CRect rect = GetLineRect(AnchorPosY(), CursorPosY());
         InvalidateRect(rect);
      }
      else
      {
         Invalidate(false);
      }
   }
   return(bIsSelected);
}

/////////////////////////////////////////////////////////////////////////////

bool ColorEditWnd::IsSelected(int pX,int pY)
{
   if (!Selected())
   {
      return(false);
   }

   //TRACE("testing %d,%d. A(%d,%d) C(%d,%d)\n", pX, pY, AnchorPosX(), AnchorPosY(), CursorPosX(), CursorPosY());

   CPoint start, stop, test(pX,pY);

   if (AnchorPosY() > CursorPosY())
   {
      start = CursorPos();
      stop = AnchorPos();
   }
   else if (AnchorPosY() < CursorPosY())
   {
      start = AnchorPos();
      stop = CursorPos();
   }
   else // same line
   {
      // cursor first
      if (AnchorPosX() > CursorPosX())
      {
         start = CursorPos();
         stop = AnchorPos();
      }
      // anchor first
      else if (AnchorPosX() < CursorPosX())
      {
         start = AnchorPos();
         stop = CursorPos();
      }
      else // cursor == anchor
      {
         return false;
      }
   }

   // test input

   // strictly between stop & start
   if ((test.y > start.y) && (test.y < stop.y))
   {
      return true;
   }

   // same line
   if ((start.y==stop.y) && (test.y==start.y))
   {
      if ((test.x >= start.x) && (test.x < stop.x))
      {
         return true;
      }
      return false;
   }

   // on start line
   if (test.y==start.y)
   {
      if (test.x >= start.x)
      {
         return true;
      }
      return false;
   }

   // on stop line
   if (test.y==stop.y)
   {
      if ((test.x < stop.x))
      {
         return true;
      }
      return false;
   }

   return false;
}

/////////////////////////////////////////////////////////////////////////////
//remove the Selected portion of the text
void ColorEditWnd::RemoveSelected()
{
   if (CursorPos() == AnchorPos())
   {
      // nothing to do
      return;
   }

   int ax = AnchorPosX();
   int ay = AnchorPosY();
   int cx = CursorPosX();
   int cy = CursorPosY();

   //make sure the anchor is first
   if (cy < ay)
   {
      std::swap(cx, ax);
      std::swap(cy, ay);
   }

   _SetCursorPos(cx, cy);
   _SetAnchorPos(ax, ay);
   
   int iStart = min(CursorPosX(), AnchorPosX());
   int iStop = max(CursorPosX(), AnchorPosX());

   CRect startRect = GetLineRect(iStart);
   CRect invalidRect;

   //if it is all one line then handle special
   if (CursorPosY() == AnchorPosY())
   {                    

      _SetCursorPosX(iStart);
      _SetAnchorPosX(iStart);

      CString R = GetTextLine(AnchorPosY()).Mid(iStop);
      CString L = GetTextLine(AnchorPosY()).Left(iStart);
      SetTextLine(L + R, AnchorPosY());

      invalidRect = startRect;
   }

   //it is multiple lines
   else
   {
      //remove all whole lines between the two
      while(CursorPosY() > AnchorPosY() + 1)
      {
         RemoveTextLine(AnchorPosY() + 1);
         _SetCursorPosY(CursorPosY() - 1);
      }
      
      //there are only two lines now
      //combine the two lines together
      CString R, L;
      if ((CursorPosY() >= 0) && (CursorPosY() < GetTextSize()))
      {
         R = GetTextLine(CursorPosY()).Mid(CursorPosX());
      }

      if ((AnchorPosY() >= 0) && (AnchorPosY() < GetTextSize()))
      {
         L = GetTextLine(AnchorPosY()).Left(AnchorPosX());

         SetTextLine(L + R, AnchorPosY());
      }
      
      //remove the second line
      if ((CursorPosY() >= 0) && (CursorPosY() < GetTextSize()))
      {
         RemoveTextLine(CursorPosY());
      }

      _SetCursorPosY(CursorPosY()-1);


      CRect client;
      GetClientRect(client);
      invalidRect = client;
      invalidRect.top = startRect.top;
   }
   
   _SetCursorPos(AnchorPos());

   Invalidate();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ScrollToLine(int iLine)
{
   if (!::IsWindow(m_hWnd))
      return;

   m_iFirstLine = max(0, iLine);
   m_iFirstLine = min(GetTextSize() - 1, iLine);
   SetScrollPos(SB_VERT, m_iFirstLine, true );
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SoftScrollToLine(int iLine)
{
   if (FirstVisibleLine() + VisibleLines(true) > iLine)
   {
      if (FirstVisibleLine() <= iLine)
      {
         return;
      }
   }

   ScrollToLine(iLine);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ScrollToCursor()
{
   // below bottom of the window? need to scroll up?
   int iLast = LastVisibleLine() - 1;
   if ((CursorPosY() > iLast) && (VisibleLines() < GetTextSize() -1))
   {
      m_iFirstLine = max(0, m_iFirstLine + (CursorPosY() - iLast));
      SetScrollPos(SB_VERT, m_iFirstLine, true );
      Invalidate(true);
   }
   else
   {
      int iFirst = FirstVisibleLine();
      if (CursorPosY() < iFirst)
      {
         // need to scroll down
         m_iFirstLine = CursorPosY();
         SetScrollPos(SB_VERT, m_iFirstLine, true );
         Invalidate(true);
      }
   }

   int iVisibleColumns = VisibleColumns();
   if (CursorPosX() > m_iFirstCharacter + iVisibleColumns)
   {
      int iDiff = CursorPosX() - (m_iFirstCharacter + iVisibleColumns);
      m_iFirstCharacter += iDiff + (iVisibleColumns / 4);
      SetScrollPos(SB_HORZ, m_iFirstCharacter, true );
      Invalidate(true);
   }
   else if (CursorPosX() < m_iFirstCharacter)
   {
      m_iFirstCharacter = max(0, CursorPosX() - (iVisibleColumns / 4));
      SetScrollPos(SB_HORZ, m_iFirstCharacter, true );
      Invalidate(true);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::UpdateAnchor(bool pTestShift)
{
   if (pTestShift)
   {
      int shift = GetKeyState(VK_SHIFT);
      if (!(shift & 0xf0)) // shifted - move anchor to cursor
      {
         _SetAnchorPos(CursorPosX(), CursorPosY());
      }

      // update the highlight
      CRect rect = GetLineRect(AnchorPosY(), CursorPosY());
      InvalidateRect(rect, FALSE);
   }
   else
   {
      // not shifted - move anchor to cursor
      _SetAnchorPos(CursorPosX(), CursorPosY());
   }
}

/////////////////////////////////////////////////////////////////////////////

BOOL ColorEditWnd::OnEraseBkgnd(CDC* pDC) 
{
   /*
   CRect client;
   pDC->GetClipBox(&client);
   pDC->FillSolidRect(client,m_backgroundColor);
   */
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

//allow the control to get all keys
UINT ColorEditWnd::OnGetDlgCode()
{
   return DLGC_WANTALLKEYS;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::UpdateScrollSizes()
{
#if 1  // variable sized thumb for scroll bars. 
   // patch from Dave Williss via CodeProject
   SCROLLINFO info;
   info.cbSize = sizeof(info);
   info.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
   info.nMin = 0;
   info.nMax = (GetTextSize() <= VisibleLines()) ? 0 : GetTextSize() - 1;
   info.nPage = VisibleLines();
   info.nPos =  m_iFirstLine;
   SetScrollInfo(SB_VERT, &info);
   info.nMax = (m_text.m_maxLineLen <= VisibleColumns()) ? 0 : m_text.m_maxLineLen - 1;
   info.nPage = VisibleColumns();
   info.nPos = m_iFirstCharacter;
   SetScrollInfo(SB_HORZ, &info);
#else
   SetScrollRange(SB_VERT, 0, max(0, GetTextSize() - VisibleLines()), true);
   SetScrollRange(SB_HORZ, 0, max(0, m_text.m_maxLineLen - VisibleColumns()), true);
#endif
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnSize(UINT nType, int cx, int cy)
{
   UpdateScrollSizes();
}

/////////////////////////////////////////////////////////////////////////////

BOOL ColorEditWnd::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	// we don't handle anything but scrolling just now
	if (fFlags & (MK_SHIFT | MK_CONTROL))
		return FALSE;

	// if we have a vertical scroll bar, the wheel scrolls that
	// if we have _only_ a horizontal scroll bar, the wheel scrolls that
	// otherwise, don't do any work at all

	DWORD dwStyle = GetStyle();
	CScrollBar* pBar = GetScrollBarCtrl(SB_VERT);
	bool bHasVertBar = ((pBar != NULL) && pBar->IsWindowEnabled()) ||
					(dwStyle & WS_VSCROLL);

	pBar = GetScrollBarCtrl(SB_HORZ);
	bool bHasHorzBar = ((pBar != NULL) && pBar->IsWindowEnabled()) ||
					(dwStyle & WS_HSCROLL);

	if (!bHasVertBar && !bHasHorzBar)
		return FALSE;

	bool bResult = FALSE;
	UINT uWheelScrollLines = 1;
   UINT uScrollLines = 5;
	int nToScroll;
	int nDisplacement;
   int iCurFirstLine = m_iFirstLine;

   DrawCursor(false);

	if (bHasVertBar)
	{
		nToScroll = ::MulDiv(-zDelta, uWheelScrollLines, WHEEL_DELTA);
		if (nToScroll == -1 || uWheelScrollLines == WHEEL_PAGESCROLL)
		{
			nDisplacement = uScrollLines;
			if (zDelta > 0)
				nDisplacement = -nDisplacement;
		}
		else
		{
			nDisplacement = nToScroll * uScrollLines;
			nDisplacement = min(nDisplacement, uScrollLines);
		}

      m_iFirstLine += nDisplacement;
      m_iFirstLine = max(0, m_iFirstLine);
      m_iFirstLine = min(m_iFirstLine, GetTextSize() - VisibleLines());
      
      if (iCurFirstLine!=m_iFirstLine)
      {
		   SetScrollPos(SB_VERT, m_iFirstLine, true );

         Invalidate();
      }
	}
	if(m_bProgEdit)
		DrawCursor(true);
  
	if (bResult)
		UpdateWindow();

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
   DrawCursor(false);
   CRect client;
   GetClientRect(client);

   int total_height = GetTextSize(); //in lines
   
   switch(nSBCode)
   {
   case SB_LINEDOWN:		//Scroll one line down.
      if (m_iFirstLine < GetTextSize() - VisibleLines())
      {
         m_iFirstLine++;
         ShiftDisplay(0, -m_iCharDY);
         InvalidateRect(GetLineRect(LastVisibleLine()-1, LastVisibleLine()), TRUE);
      }
      break;
   
   case SB_LINEUP:			//Scroll one line up.
      if (m_iFirstLine > 0)
      {
         m_iFirstLine--;
         ShiftDisplay(0, +m_iCharDY);
         InvalidateRect(GetLineRect(FirstVisibleLine()), TRUE);
      }
      break;

   case SB_BOTTOM:			//Scroll to bottom.
      m_iFirstLine = max(0,total_height - VisibleLines());
      Invalidate();
      break;
   case SB_PAGEDOWN:		//Scroll one page down.
      m_iFirstLine += VisibleLines() * 3 / 4;
      Invalidate();
      break;
   case SB_PAGEUP:			//Scroll one page up.
      m_iFirstLine -= VisibleLines() * 3 / 4;
      m_iFirstLine = max(0,m_iFirstLine);
      Invalidate();
      break;
   case SB_THUMBPOSITION:	//Scroll to the absolute position. The current position is provided in nPos.
   case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is provided in nPos.
      if (nPos!=m_iFirstLine)
      {
         int iOldFirstLine = m_iFirstLine;
         
         m_iFirstLine = max(0, min(nPos, GetTextSize()));

         int iDelta = m_iFirstLine - iOldFirstLine;
       
         ShiftDisplay(0, -(m_iCharDY * iDelta));

         if (iDelta > 0)
         {
            // redraw new lines at bottom
            InvalidateRect(GetLineRect(LastVisibleLine() - (iDelta + 1), LastVisibleLine()), TRUE);
         }
         else
         {
            // redraw new lines at top
            InvalidateRect(GetLineRect(m_iFirstLine, iOldFirstLine), TRUE);
         }
      }
      break;
   case SB_TOP:			//Scroll to top.
      m_iFirstLine = 0;
      Invalidate();
      break;
   case SB_ENDSCROLL:		//End scroll.
      break;
   default:
      break;
   }

   // redraw now!
   UpdateWindow();

   SetScrollPos(SB_VERT, m_iFirstLine, true );
   if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
   DrawCursor(false);

   CRect client;
   GetClientRect(client);
   int window_width = client.Width()/m_iCharDX;	
   switch(nSBCode)
   {
   
   case SB_LINELEFT:		//Scroll left.
      if (m_iFirstCharacter > 0)
      {
         m_iFirstCharacter--;
         ShiftDisplay(+m_iCharDX, 0);
         InvalidateRect(CRect(client.left, client.top, MIN_X + m_iCharDX, client.bottom), TRUE);
      }
      break;

   case SB_LINERIGHT:		//Scroll right one line.
      if (m_iFirstCharacter < (m_text.m_maxLineLen - VisibleColumns()))
      {
         m_iFirstCharacter++;
         ShiftDisplay(-m_iCharDX, 0);
         InvalidateRect(CRect(client.right - m_iCharDX, client.top, client.right, client.bottom), TRUE);
      }
      break;

   case SB_LEFT:			//Scroll to far left.
      m_iFirstCharacter = 0;
      Invalidate();
      break;
   case SB_PAGELEFT:		//Scroll one page left.
      m_iFirstCharacter -= window_width * 3 / 4;
      m_iFirstCharacter = max(0, m_iFirstCharacter);
      Invalidate();
      break;

   case SB_RIGHT:			//Scroll to far right.
      Invalidate();
      break;
   case SB_PAGERIGHT:		//Scroll one page right.
      m_iFirstCharacter += window_width * 3 / 4;
      Invalidate();
      break;

   case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
   case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter.
      if (nPos!=m_iFirstCharacter)
      {
         int iOldFirstChar = m_iFirstCharacter;
      
         m_iFirstCharacter = max(0, min(nPos, (m_text.m_maxLineLen - VisibleColumns())));

         int iDelta = m_iFirstCharacter - iOldFirstChar;

         ShiftDisplay(-(m_iCharDX * iDelta), 0);

         if (iDelta > 0)
         {
            InvalidateRect(CRect(client.right - (m_iCharDX * iDelta), client.top, client.right, client.bottom), TRUE);
         }
         else 
         {
            InvalidateRect(CRect(client.left, client.top, MIN_X + (m_iCharDX * -iDelta), client.bottom), TRUE);
         }
      }
      break;
   case SB_ENDSCROLL:		//End scroll.
   default:
      break;
   }

   // redraw now!
   UpdateWindow();                           

   SetScrollPos(SB_HORZ, m_iFirstCharacter, true );
	if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ShiftDisplay(int dx, int dy)
{
   CRect cli;
   GetClientRect(cli);

   // our left margin
   cli.left+= MIN_X;
   
   CClientDC dc(this);
   
   CDC memDC;
   memDC.CreateCompatibleDC(&dc);

   CBitmap memBMP;
   memBMP.CreateCompatibleBitmap(&dc, cli.Width(), cli.Height());
   
   // copy screen to off-screen
   CBitmap *ob = memDC.SelectObject(&memBMP);
   memDC.BitBlt(0, 0, cli.Width(), cli.Height(), &dc, MIN_X, 0, SRCCOPY);

   // copy off-screen to screen, offset
   dc.BitBlt(MIN_X + dx, dy, cli.Width(), cli.Height(), &memDC, 0, 0, SRCCOPY);

   memDC.SelectObject(ob);
   memBMP.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoCopy()
{
   try
   {
      if (OpenClipboard())
      {
         CString data;

         // where do we start?
         CPoint start, stop;
      
         if (AnchorPosY() > CursorPosY())
         {
            start = CursorPos();
            stop = AnchorPos();
         }
         else if (AnchorPosY() < CursorPosY())
         {
            start = AnchorPos();
            stop = CursorPos();
         }
         else // same line
         {
            // cursor first
            if (AnchorPosX() > CursorPosX())
            {
               start = CursorPos();
               stop = AnchorPos();
            }
            // anchor first
            else if (AnchorPosX() < CursorPosX())
            {
               start = AnchorPos();
               stop = CursorPos();
            }
            else // cursor == anchor
            {
               return; // nothing to do
            }
         }

         // get first line 

         // it might be part of the start/stop line
         if (start.y == stop.y)
         {
            CString line = GetTextLine(start.y);
            data += line.Mid(start.x, stop.x - start.x);
         }
         else
         {
            // get to end of line
            data += GetTextLine(start.y).Mid(start.x);
         }

         if (start.y != stop.y)
         {
            data += char(13); // /r
            data += char(10); // /n
         }

         // other full lines
         for (int line=start.y + 1; line < stop.y; line++)
         {
            data += GetTextLine(line);
            data += char(13); // /r
            data += char(10); // /n
         }

         // end line
         if (start.y != stop.y)
         {
            data += GetTextLine(stop.y).Left(stop.x);
         }

         HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, data.GetLength()+1);
         if (clipbuffer==NULL)
         {
            ASSERT(0);
            return;
         }

         char *buffer = (char*)GlobalLock(clipbuffer);
         strcpy(buffer, LPCSTR(data));

         GlobalUnlock(clipbuffer);

         EmptyClipboard();
         SetClipboardData(CF_TEXT,clipbuffer);
         CloseClipboard();
      }
      else
      {
         ASSERT(0);
      }
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in DoCopy", m_className);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoCut()
{
   try
   {
      if (m_bReadOnly)
      {
         return;
      }

      DrawCursor(false);

      StartAction();

      DoCopy();

      RemoveSelected();

      EndAction();
if(m_bProgEdit)
      DrawCursor(true);
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in DoCut", m_className);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoPaste()
{
   try
   {
      if (m_bReadOnly)
      {
         return;
      }

      CWaitCursor bob;
   
      DrawCursor(false);

      OpenClipboard();
      HGLOBAL hglb = GetClipboardData(CF_TEXT); 
      if (hglb == NULL)
      {
         CloseClipboard();
         return;
      }

      char *buffer = (char*)GlobalLock(hglb); 
      if (buffer==NULL) 
      {
         CloseClipboard();
         return;
      }

      StartAction();

      _ReplaceSelText(buffer);

      EndAction();

      GlobalUnlock(hglb);
      CloseClipboard();

      ScrollToCursor();
	  if(m_bProgEdit)
      DrawCursor(true);
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in DoPaste", m_className);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ReplaceSelText(const char *pText)
{
   StartAction();

   _ReplaceSelText(pText);

   EndAction();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::_ReplaceSelText(const char *pText)
{
   try
   {
      if (Selected()) 
      {
         RemoveSelected();
      }

      // add up to the first \n into the current line
      // add all lines up to the last \n as single lines
      // add the rest into the current line

      bool bFoundNewLine = false;
      CString accum;
      CString R;

      int xpos = CursorPosX();
      int iLen = strlen(pText);
      for (int i=0; i < iLen; i++)
      {
         if (pText[i] == '\n')
         {
            if (bFoundNewLine || (CursorPosY() >= GetTextSize()))
            {
               InsertTextLine(accum, CursorPosY(), false);
            }
            else
            {
               // insert at end. break line
               CString L;
               L = GetTextLine(CursorPosY()).Left(CursorPosX());
               R = GetTextLine(CursorPosY()).Mid(CursorPosX());
               SetTextLine(L + accum, CursorPosY());
            }

            accum="";
            xpos = 0;
            _SetCursorPos(0, CursorPosY() + 1);
            bFoundNewLine = true;
         }
         else if (pText[i] == '\t')
         {
            CString tab = MakeTab(xpos);
            xpos+=tab.GetLength();
            accum+=tab;
         }
         else if (isprint(pText[i]))
         {
            xpos++;
            accum+=pText[i];
         }
      }

      // whatever's left
      CString csNew = accum + R;
      if (bFoundNewLine)
      {
         if ((accum.GetLength()!=0) || (R.GetLength()!=0))
         {
            // inserting into a line
            InsertTextLine(csNew, CursorPosY(), false);
            _SetCursorPosX(csNew.GetLength());
         }
         else
         {

         }
      }
      else
      {
         if ((accum.GetLength()!=0) || (R.GetLength()!=0))
         {
            if (CursorPosY() >= GetTextSize())
            {
               // creating a new line
               InsertTextLine(csNew, GetTextSize());
               _SetCursorPosX(csNew.GetLength());
            }
            else
            {
               // inserting into a line
               CString L = GetTextLine(CursorPosY()).Left(CursorPosX());
               CString R = GetTextLine(CursorPosY()).Mid(CursorPosX());
               SetTextLine(L + accum + R, CursorPosY());
               _SetCursorPosX(L.GetLength() + accum.GetLength());
            }
         }
      }

      _SetAnchorPos(CursorPosX(), CursorPosY());

      m_text.FullUpdate();

      UpdateScrollSizes();
	  
	  ScrollToCursor();
      
	  Invalidate();

	  if(m_bProgEdit)
      DrawCursor(true);
   }
   catch (...)
   {
      //g_statusLog.StatusOut("%s, Exception in _ReplaceSelText", m_className);
      throw;
   }
}

/////////////////////////////////////////////////////////////////////////////

int ColorEditWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   //g_statusLog.StatusOut("%s, OnCreate", m_className);

   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   m_bCaretOn = false;
   m_cursor = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
   
   return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL ColorEditWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
   CRect client;
   GetClientRect(client);
   CPoint cursorpt;
   ::GetCursorPos(&cursorpt);
   ScreenToClient(&cursorpt);
   if (client.PtInRect(cursorpt))
   {
      ::SetCursor(m_cursor);
      return TRUE;		
   }
   return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
   if (bShow)
   {
      CClientDC dc(this);
      TEXTMETRIC tm;
      dc.SelectObject(m_font);
      dc.GetTextMetrics(&tm);

      // here's why we're limited to fixed width fonts.
      m_iCharDX = tm.tmAveCharWidth;
      m_iCharDY = tm.tmHeight;
   }

   CWnd::OnShowWindow(bShow, nStatus);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::InsertTab()
{
   CString tab = MakeTab(CursorPosX());
   if (tab.GetLength())
   { 
      InsertString(tab);
   }
}

/////////////////////////////////////////////////////////////////////////////

CString ColorEditWnd::MakeTab(int iCursorXPos) const
{
   CString tab = " ";
   iCursorXPos++;

   while (iCursorXPos++ % m_iTabSize)   
   {
      tab+=" ";
   }

   return tab;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::NotifyParent(UINT msg)
{
   if (!::IsWindow(m_hWnd))
   {
      return;
   }

   CWnd *pParent = GetParent();
   if (pParent)
   {
	   WPARAM wParam = (WPARAM) MAKEWPARAM(m_ID, msg);
	   LPARAM lParam = (LPARAM) GetSafeHwnd();
	   pParent->SendMessage(WM_COMMAND, wParam, lParam);
   }
   else
   {
      ASSERT(0);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::InsertTextLine(CString &line, int i, bool bUpdate, bool bNoUndo)  
{
   if (!bNoUndo)
   {
      CUndoAction act;
      act.m_actionType = CUndoAction::eAddLine;
      act.m_csText = "";
      act.m_iLineNumber = i;
      act.m_cursorPos = CursorPos();
      act.m_anchorPos = AnchorPos();
      m_currentUndoFrame.Add(act);
   }

   m_text._InsertLine(line, i, bUpdate);

   if (bUpdate)
   {
      UpdateScrollSizes();
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetTextLine(CString &line, int i, bool bNoUndo, bool pUpdate)
{
   if (!bNoUndo)
   {
      CUndoAction act;
      act.m_actionType = CUndoAction::eChangeLine;
      act.m_csText = GetTextLine(i);
      act.m_iLineNumber = i;
      act.m_cursorPos = CursorPos();
      act.m_anchorPos = AnchorPos();
      m_currentUndoFrame.Add(act);
   }

   m_text._SetLine(line, i);

   if (pUpdate)
   {
      UpdateScrollSizes();  
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::RemoveTextLine(int i, bool bNoUndo, bool pUpdate)                       
{
   if (i >= GetTextSize())
      return;

   if (!bNoUndo)
   {
      CUndoAction act;
      act.m_actionType = CUndoAction::eRemoveLine;
      act.m_csText = GetTextLine(i);
      act.m_iLineNumber = i;
      act.m_cursorPos = CursorPos();
      act.m_anchorPos = AnchorPos();
      m_currentUndoFrame.Add(act);
   }

   m_text._RemoveLine(i);

   if (pUpdate)
   {
      UpdateScrollSizes();
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::RemoveAllText()                             
{
   CUndoAction act;

   for (int i=0;i<GetTextSize();i++)
   {
      act.m_actionType = CUndoAction::eRemoveLine;
      act.m_csText = GetTextLine(i);
      act.m_iLineNumber = i;
      act.m_cursorPos = CursorPos();
      act.m_anchorPos = AnchorPos();
      m_currentUndoFrame.Add(act);
   }

   m_text._RemoveAll();

   UpdateScrollSizes();

   NotifyParent(EN_CHANGE);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	SetFocus();

	int x = point.x;
	int y = point.y;

	CPoint clPoint = point;
	ScreenToClient(&clPoint);
	
	CMenu menu;
	if(m_bProgEdit)
	{
	VERIFY(menu.LoadMenu(IDR_COLOREDITCTX));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

   _GfxCmdUIUpdateMenu(this, pPopup, false);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, x, y, this);
	}
}

/////////////////////////////////////////////////////////////////////////////

static void _GfxCmdUIUpdateMenu(CCmdTarget* pTarget, CMenu* pMenu, bool bDisableIfNoHndler/*=true*/)
{
   ASSERT_VALID(pTarget);
   ASSERT(pMenu == NULL || AfxIsValidAddress(pMenu, sizeof(class CMenu)));

   if (pMenu)
   {
      CCmdUI cmdUI;
      cmdUI.m_pMenu = pMenu;
      cmdUI.m_pSubMenu = NULL;
      UINT nMax = pMenu->GetMenuItemCount();
      if (nMax == (UINT)-1)
      {
         nMax = 0;
      }

      cmdUI.m_nIndexMax = nMax;
      
      for (UINT n = 0; n < nMax; n++)
      {
         cmdUI.m_nIndex = n;
         cmdUI.m_nID = pMenu->GetMenuItemID(n);
         // Recurse submenu's
         if (cmdUI.m_nID == (UINT)-1)
         {
            CMenu* pSubMenu = pMenu->GetSubMenu(n);
            _GfxCmdUIUpdateMenu(pTarget, pSubMenu, bDisableIfNoHndler);
         }
         else
            cmdUI.DoUpdate(pTarget, bDisableIfNoHndler);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdateCopy(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(Selected());
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdateCut(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(Selected());
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	if (OpenClipboard())
	{
		pCmdUI->Enable(::GetClipboardData(CF_TEXT)!=NULL);
      CloseClipboard();
   }
   else
   {
      pCmdUI->Enable(false);
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdateSelectall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_undoStack.empty());
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_redoStack.empty());
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnCopy() 
{
	DoCopy();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnCut() 
{
	DoCut();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnPaste() 
{
	DoPaste();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnSelectall() 
{
	_SetAnchorPos(0,0);
   _SetCursorPos(GetTextLine(GetTextSize() - 1).GetLength(), GetTextSize() -1);
   ScrollToCursor();
	
   if(m_bProgEdit)
	DrawCursor(true);       

   Invalidate(false);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnUndo() 
{
   DoUndo();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnRedo() 
{
   DoRedo();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClearUndoHistory()
{
   m_currentUndoFrame.Clear();
   ClearUndoStack(m_redoStack);
   ClearUndoStack(m_undoStack);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::StartAction()
{
   StartUndoFrame();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::EndAction()
{
   EndUndoFrame();
   NotifyParent(EN_CHANGE);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::StartUndoFrame()
{
   m_currentUndoFrame.Clear();
   ClearUndoStack(m_redoStack);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::EndUndoFrame()
{
   if (m_currentUndoFrame.m_actions.empty())
   {
      // nothing here.
      return;
   }

   m_undoStack.push(m_currentUndoFrame);
   m_currentUndoFrame.Clear();
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoUndo()
{
   DoUndoRedo(m_undoStack, m_redoStack);
   NotifyParent(EN_CHANGE);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoRedo()
{
   DoUndoRedo(m_redoStack, m_undoStack);
   NotifyParent(EN_CHANGE);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::DoUndoRedo(undostack &inStack, undostack& outStack)
{
   CUndoFrame inFrame;
   if (inStack.empty())
   {
      return; // nothing to undo
   }

   inFrame = inStack.top();
   inStack.pop();

   DrawCursor(false);

	// put the undo/redo actions here. undo actions become redo actions and vice versa
   CUndoFrame outputFrame;

   CRect rectInv;

   CUndoAction action;
   while (inFrame.GetNext(action))
   {
      CRect lineRect = GetLineRect(action.m_iLineNumber);
      CRect tempRect;
      tempRect.UnionRect(lineRect, rectInv);
      rectInv = tempRect;

      // show the user what's going on
      SoftScrollToLine(action.m_iLineNumber);

      CUndoAction outputAction;
      switch (action.m_actionType)
      {
      case CUndoAction::eAddLine:
         outputAction.m_actionType  = CUndoAction::eRemoveLine;
         outputAction.m_csText      = GetTextLine(action.m_iLineNumber);

         RemoveTextLine(action.m_iLineNumber, true, false);
         break;
      case CUndoAction::eRemoveLine:
         outputAction.m_actionType  = CUndoAction::eAddLine;
         outputAction.m_csText      = "";

         InsertTextLine(action.m_csText, action.m_iLineNumber, true, true);
         break;
      case CUndoAction::eChangeLine:
         outputAction.m_actionType  = CUndoAction::eChangeLine;
         outputAction.m_csText      = GetTextLine(action.m_iLineNumber);;

         SetTextLine(action.m_csText, action.m_iLineNumber, true, false);
        break;
      }
                                               
      outputAction.m_cursorPos   = CursorPos();
      outputAction.m_anchorPos   = AnchorPos();
      outputAction.m_iLineNumber = action.m_iLineNumber;

      // reset the positioning
      _SetCursorPos(action.m_cursorPos);
      _SetAnchorPos(action.m_anchorPos);

      outputFrame.Add(outputAction);
   }

   outStack.push(outputFrame);
	if(m_bProgEdit)
   DrawCursor(true);

   CRect client;
   GetClientRect(client);
   rectInv.bottom = client.bottom;
   InvalidateRect(rectInv);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClearUndoStack(undostack &inStack)
{
   while (!inStack.empty())
   {
      inStack.pop();
   }
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClipAnchorPosition(int &x, int &y)
{
   CPoint t(x, y);
   ClipAnchorPosition(t);
   x = t.x;
   y = t.y;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClipAnchorPosition(CPoint &p)
{
   p.y = max(0, p.y);
   p.y = min(GetTextSize() - 1, p.y);

   p.x = max(0, p.x);
   p.x = min(GetTextLine(p.y).GetLength(), p.x);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClipCursorPosition(int &x, int &y)
{
   CPoint t(x, y);
   ClipCursorPosition(t);
   x = t.x;
   y = t.y;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::ClipCursorPosition(CPoint &p)
{
   p.y = max(0, p.y);
   p.y = min(GetTextSize() - 1, p.y);

   p.x = max(0, p.x);
   p.x = min(GetTextLine(p.y).GetLength(), p.x);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetSelection(int x1, int y1, int x2, int y2)
{
   ClipAnchorPosition(x1, y1);
   ClipCursorPosition(x2, y2);

   _SetAnchorPos(x1, y1);
   _SetCursorPos(x2, y2);
  if(m_bProgEdit)
   DrawCursor(true);       

   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetCursorPos(CPoint pos)
{
   ClipCursorPosition(pos);

   _SetCursorPos(pos);
  if(m_bProgEdit)
   DrawCursor(true);       

   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetAnchorPos(CPoint pos)
{
   ClipAnchorPosition(pos);

   _SetAnchorPos(pos);
  if(m_bProgEdit)
   DrawCursor(true);       

   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnKillFocus(CWnd* pNewWnd) 
{
   // if we don't check, bad things happen...
   if (GetCapture()==this)
   {
      ReleaseCapture();
   }

   if (m_bCaretOn)
   {
      HideCaret();
      DestroyCaret();
      m_bCaretOn = false;
   }

   // daddy, i think i'm losing focus.
   NotifyParent(EN_KILLFOCUS);

   CWnd::OnKillFocus(pNewWnd);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnSetFocus( CWnd* pOldWnd )
{
	if(m_bProgEdit)
		DrawCursor(true);
   NotifyParent(EN_SETFOCUS);

   CWnd::OnSetFocus(pOldWnd);
}

/////////////////////////////////////////////////////////////////////////////

BOOL ColorEditWnd::PreTranslateMessage(MSG* pMsg) 
{
   if (m_bUseKBAccel)
   {
      if ((pMsg->message == WM_KEYDOWN) && (pMsg->hwnd == m_hWnd))
      {
         if (::TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) )
         {
            // yes, we handled the accel.
            return TRUE;
         }
         else
         {
            return CWnd::PreTranslateMessage(pMsg);
         }
      }
   }

   return CWnd::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetCharXSpacing(int i)
{
   i = max(0,i);
   m_iCharDX += i;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetCharYSpacing(int i)
{
   i = max(0,i);
   m_iCharDY += i;
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetColorizer(CColorizer *pColorizer)
{
   m_text.SetColorizer(pColorizer);
   m_text.FullUpdate();
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::Recolorize()
{
   m_text.FullUpdate();
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetBackgroundColor(COLORREF clr)
{
   m_backgroundColor = clr;
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetHighlightColor(COLORREF clr)
{
   m_hilightColor = clr;
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetHighlightTextColor(COLORREF clr)
{
   m_hilightTextColor = clr;
   Invalidate(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::SetLine(const char *pText, int iLine)
{
   DrawCursor(false);

   StartAction();

   CString t(pText);
   SetTextLine(t, iLine);

   EndAction();
	if(m_bProgEdit)
   DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

void ColorEditWnd::OnLButtonDblClk( UINT nFlags, CPoint point)
{
   // select the word under the mouse, on a double-click

   //convert click to cursor position
   point.x -= MIN_X;

   m_bLBDown = false;

   SetFocus();

   DrawCursor(false);

   CRect oldSelRect = GetLineRect(AnchorPosY(), CursorPosY());
   InvalidateRect(oldSelRect);
   
   int x = CursorPosX();
   int y = CursorPosY();

   x = (point.x + m_iCharDX/2) / m_iCharDX + m_iFirstCharacter;
   y = point.y / m_iCharDY + m_iFirstLine;
   y = min(y, GetTextSize() - 1);
   x = min(x, GetTextLine(y).GetLength());

   _SetAnchorPos(CursorPosX(),CursorPosY());

   CString line = GetTextLine(y);

   int len = line.GetLength();

   // find spaces on either side of current 'word'
   int start = x;
   int stop = x;

   while (start >= 0)
   {
      if (start < len)      
      {
         if (!isalnum(line.GetAt(start)))
         {
            start++;
            break;
         }
      }

      start--;
   }

   while (stop < len)
   {
      if (!isalnum(line.GetAt(stop)))
      {
         break;
      }

      stop++;
   }

   // update cursor and anchor
   if(m_bProgEdit)
   {
		ClipCursorPosition(start, y);
		_SetCursorPos(start, y);

		ClipAnchorPosition(stop, y);
		_SetAnchorPos(stop, y);
	}

   CRect newSelRect = GetLineRect(y);

   InvalidateRect(newSelRect);
	if(m_bProgEdit)
		DrawCursor(true);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
