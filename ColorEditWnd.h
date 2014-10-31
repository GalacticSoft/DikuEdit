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

**********************************************************************/

/////////////////////////////////////////////////////////////////////////////
//Header for the ColorEditWnd class
/////////////////////////////////////////////////////////////////////////////

#ifndef _COLORIZED_VIEW_
#define _COLORIZED_VIEW_

#include "Colorizer.h"
#include "ScriptText.h"
#include "UndoFrame.h"

class ColorEditWnd : public CWnd
{

public:
   //DECLARE_CONTROL(ColorEditWnd, CWnd);
   DECLARE_DYNAMIC(ColorEditWnd);

   ColorEditWnd();

	ColorEditWnd(CWnd * parent, 
               const CRect & rect,        // where to put it
               int nID,                   // control ID. this control will post messages to the parent
                                          // (EN_CHANGE, EN_KILLFOCUS, EN_SETFOCUS, etc) with this ID

               int iTabSize,              // spaces per tab. all tabs are spaces
               int iFontSize,             // font size in 10ths of a point (uses CreatePointFont)
               const char *pFontName,     // font name. only use this with fixed width fonts!!!!!
               bool bShowHorizScroll = true, bool bProgEdit = false);    // show the horizontal scroll bar?

   
   BOOL Create(DWORD dwFlags,             // recommend : WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL
               CWnd * parent, 
               const CRect & rect,
               int nID, 
               int iTabSize,
               int iFontSize, 
               const char *pFontName);

   // this is how we pick up the cut/copy/paste/undo/redo messages
   //
   // feel free to disable this, if you want to control these functions
   // externally.
   void     UseKeyboardAccelerators(bool b)  {m_bUseKBAccel = b;}

public:
   ///////////////////////////////////////////////////////////////////////////
   // clear all text
	void Reset();

   ///////////////////////////////////////////////////////////////////////////
   // clear and set text to pInText
	void LoadText(const char *pInText);

   // get a single string copy of the contents
	void UnloadText(CString &pText) /*const*/;

   ///////////////////////////////////////////////////////////////////////////
   // number of text lines in the buffer
   _inline int GetLineCount()      {return GetTextSize();}

   ///////////////////////////////////////////////////////////////////////////
   // position of cursor and anchor. 
   // if these are different positions, the characters between are selected.
   void  SetCursorPos(CPoint pos);
   void  SetAnchorPos(CPoint pos);

   _inline CPoint GetCursorPos()   {return CursorPos();}
   _inline CPoint GetAnchorPos()   {return AnchorPos();}

   // another way to set selection
   void  SetSelection(int charPos1, int line1, int charPos2, int line2);
   void  ReplaceSelText(const char *pText);

   // set this line as the top line in the window
   void ScrollToLine(int iLine);

   // scroll if necessary to make this line visible
   void SoftScrollToLine(int iLine);

   // scroll the window to show the cursor
   void ScrollToCursor();

   // get one line of text
   CString GetLine(int iLine) /*const*/      {return GetTextLine(iLine);}

   // set a single line of text
   void SetLine(const char *pText, int iLine);

   ///////////////////////////////////////////////////////////////////////////
   // client rect of the text at a given line
   CRect GetLineRect(int iLine) const;

   // client rect that encompasses both lines
   CRect GetLineRect(int iLine1, int iLine2) const;

   // number of visible lines. 
   // if bTotal = false, returns the actual number of lines drawn (which may be less
   // than the number of lines that could be drawn, if there was more text...)
   int VisibleLines(bool bTotal = false) const;

   // last and first visible line numbers
   int LastVisibleLine() const;
   int FirstVisibleLine() const;

   // characters on screen
   int VisibleColumns() const;

   ///////////////////////////////////////////////////////////////////////////
   // the parent window can call these to do cut/paste/etc. functions.

   // remove selection to the clipboard
   void DoCut();

   // copy selection to the clipboard
	void DoCopy();

   // paste clipboard. replaces any selection.
	void DoPaste();

   // undo the last action
   void DoUndo();

   // redo the last undo'd action
   void DoRedo();

   // additioinal horizontal spacing
   void SetCharXSpacing(int i);

   // additional vertical spacing
   void SetCharYSpacing(int i);

   // use your own CColorizer class. 
   // this can actually be changed on-the-fly, if you 
   // need to use a different coloring scheme at will.
   void SetColorizer(CColorizer * pColorizer);

   // basic editing stuff
   void SetBackgroundColor(COLORREF clr);
   void SetHighlightColor(COLORREF clr);
   void SetHighlightTextColor(COLORREF clr);

   // make this a read-only control
   void SetReadOnly(bool b)      {m_bReadOnly = b;}

   void ClearUndoHistory();

   // force a recolorization of all text
   void Recolorize();

public:
	virtual ~ColorEditWnd();

private:
   // cursor/anchor position 
   void ClipAnchorPosition(int &x, int &y);
   void ClipCursorPosition(int &x, int &y);
   void ClipAnchorPosition(CPoint &p);
   void ClipCursorPosition(CPoint &p);
   
   // warning: these only affect the internal state. they do not update the UI!
   _inline void _SetAnchorPosX(int x)      {m_anchorPos.x = x;}
   _inline void _SetAnchorPosY(int y)      {m_anchorPos.y = y;}
   _inline void _SetAnchorPos(CPoint pt)   {m_anchorPos = pt;}
   _inline void _SetAnchorPos(int x, int y) {m_anchorPos.x = x; m_anchorPos.y = y;}

   // warning: these only set the internal data. they do not update the UI!
   _inline void _SetCursorPosX(int x)      {m_cursorPos.x = x;}
   _inline void _SetCursorPosY(int y)      {m_cursorPos.y = y;}
   _inline void _SetCursorPos(CPoint pt)   {m_cursorPos = pt;}
   _inline void _SetCursorPos(int x, int y) {m_cursorPos.x= x; m_cursorPos.y = y;}

   _inline CPoint   CursorPos() const     {return m_cursorPos;}
   _inline int   CursorPosX() const       {return m_cursorPos.x;}
   _inline int   CursorPosY() const       {return m_cursorPos.y;}

   _inline CPoint   AnchorPos() const     {return m_anchorPos;}
   _inline int   AnchorPosX() const       {return m_anchorPos.x;}
   _inline int   AnchorPosY() const       {return m_anchorPos.y;}

   // number of lines
   _inline int GetTextSize() const        {return m_text._GetSize();}

   // get a single line
   _inline CString GetTextLine(int i) /*const */      {return m_text._GetLine(i);}

   // insert/delete

   // insert a single line at pos 'i'. 
   void InsertTextLine(CString &line, 
                        int i, 
                        bool bUpdate=TRUE,      // redraw and recolor. in general, TRUE
                        bool bNoUndo = false);  // don't add to undo frame

   // insert a string at the current cursor pos
   void InsertText(CString &pString);

   // insert a single char at the current cursor pos
	void InsertChar(int pChar, bool pUpdate = TRUE);

   // insert a string at the current cursor pos
	void InsertString(CString &pString, bool pUpdate = TRUE);

   // insert a single tab (as spaces) at the current cursor pos
   void  InsertTab();

   // set a single text line. replaces old contents
   void SetTextLine(CString &line, int i, bool bNoUndo = false, bool pUpdate = TRUE);

   // remove the line at 'i'
   void RemoveTextLine(int i, bool bNoUndo = false, bool pUpdate = TRUE);                     

   // clear all lines
   void RemoveAllText();                           

   void  _ReplaceSelText(const char *pText);

   ///////////////////////////////////////////////////////////////////////////

private:
   CString MakeTab(int iCursorXPos) const;

   // for the backspace and delete keys
	void DeleteNextChar();
    void DeletePrevChar();

   // handle enter key
    void DoEnter();

   // selection
	bool IsSelected(int pX,int pY);
	bool Selected();
	void UpdateAnchor(bool pTestShift);
	void RemoveSelected();

   // scroll
   void UpdateScrollSizes();
   
   CPoint GetDeviceScrollPosition() const;
   CPoint GetScrollPosition() const;

   // output
   CPoint _DrawLine(CDC *pDC, const CString &line, const CScriptText::lineVector &colors, int lineidx, int y);
   void DrawCursor(CDC * pDC, bool pShow);
	void DrawCursor(bool pShow);

   void ShiftDisplay(int dx, int dy);


   // undo stuff
   void StartUndoFrame();
   void EndUndoFrame();
   void ClearUndoStack(undostack &inStack);
   void DoUndoRedo(undostack &inStack, undostack& outStack);

   // start/end an undoable action
   void StartAction();
   void EndAction();

   // post a windows message to the parent
   void  NotifyParent(UINT msg);

   // state
	int m_iCharDX;
	int m_iCharDY;
	int m_iTabSize;
	HCURSOR m_cursor;
   CFont m_font;

	// offsets for scrolling
	long			m_iFirstCharacter;
	long			m_iFirstLine;

	//caret and cursor postion
   CPoint      m_anchorPos;
   CPoint      m_cursorPos;

   // colors
   COLORREF m_backgroundColor;
   COLORREF m_hilightColor;
   COLORREF m_hilightTextColor;

   // the text
   CScriptText		m_text;

   // sel/drag info
	bool     m_bIsSelected;
	bool     m_bLBDown;
	bool     m_bCaretOn;
   CPoint   m_startPointDrag;

   // use accellerators?
   bool     m_bUseKBAccel;

   bool     m_bMaintainIndent;

	bool m_bProgEdit;
   // undo/redo state

   // current action frame. an action can be composed of one or more sub-actions.
   // for a single keystroke, the undo frame holds one action: the keystroke.
   // for complex actions, like a paste or a cut, the frame will contain all of the 
   // actions required to perform the meta-action.
   CUndoFrame  m_currentUndoFrame;

   // holds all of our actions - this might get big. feel free to clear it once in a while.
   undostack   m_undoStack;

   // when the user starts undo-ing stuff, the undo's are placed here. 
   // this is cleared when a new undo frame is created, ie. when a new edit action occurs.
   undostack   m_redoStack;

   // dialog ID
   UINT  m_ID; 

   bool  m_bReadOnly;

   HACCEL m_hAccel;

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorEditWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(ColorEditWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
   afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnCut();
	afx_msg void OnPaste();
	afx_msg void OnSelectall();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnSetFocus( CWnd* pOldWnd );
   afx_msg void OnLButtonDblClk( UINT, CPoint );
	//}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   CString m_className;
};


/////////////////////////////////////////////////////////////////////////////
#endif
