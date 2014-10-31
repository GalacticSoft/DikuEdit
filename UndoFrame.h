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

// UndoFrame.h: interface for the CUndoFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOFRAME_H__53203B04_E726_46CD_80A8_C1DB02EAF9E0__INCLUDED_)
#define AFX_UNDOFRAME_H__53203B04_E726_46CD_80A8_C1DB02EAF9E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
using namespace std;
#pragma warning(disable:4786)

class CUndoAction
{
public:
   CUndoAction& operator = (const CUndoAction& src)
   {
      m_csText = src.m_csText;
      m_actionType = src.m_actionType;
      m_iLineNumber = src.m_iLineNumber;
      m_cursorPos = src.m_cursorPos;
      m_anchorPos = src.m_anchorPos;

      return *this;
   }

   typedef enum {eAddLine, eRemoveLine, eChangeLine} eAction;
   
   CString  m_csText;
   eAction  m_actionType;
   int      m_iLineNumber;
   CPoint   m_cursorPos;
   CPoint   m_anchorPos;

};
typedef stack<CUndoAction> undoActionStack;

class CUndoFrame  
{
public:
	CUndoFrame();
	virtual ~CUndoFrame();

   void Clear();

   void Add(const CUndoAction &action);

   bool GetNext(CUndoAction &action);

   undoActionStack  m_actions;
};

typedef stack<CUndoFrame> undostack;

#endif // !defined(AFX_UNDOFRAME_H__53203B04_E726_46CD_80A8_C1DB02EAF9E0__INCLUDED_)
