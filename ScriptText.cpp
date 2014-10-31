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
#include "stdafx.h"
#include "ScriptText.h"
/////////////////////////////////////////////////////////////////////////////

CScriptText::CScriptText ()
{
   m_pColorizer = &m_defaultColorizer;

    m_maxLineLen = 0;

}

/////////////////////////////////////////////////////////////////////////////

CScriptText & CScriptText::operator = (CScriptText & source)
{
	m_textArray.RemoveAll();
    m_textArray.Copy(source.m_textArray);
   
    m_colors = source.m_colors;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////

void CScriptText::_InsertLine(CString &line, int i, BOOL bUpdate)  
{
	
    
   lineVector lv;

   // sometimes, we don't want to update each line. like on a large paste.
   // we'll update all, later.
   bUpdate = true;

   if (bUpdate)
   {
      
     m_pColorizer->SetLineColors(line, lv);
	  StripAnsiChars(line, lv);
	 
   } 
   
   m_colors.insert(m_colors.begin() + i, lv);
  
	m_textArray.InsertAt(i, line);
	FindMaxLineLen();	 
	 
}

/////////////////////////////////////////////////////////////////////////////

void CScriptText::_SetLine(CString &line, int i)     
{
   
	//lineVector lv;

   m_pColorizer->SetLineColors(line, m_colors.at(i));
    StripAnsiChars(line, m_colors.at(i));
   m_textArray.SetAt(i, line);

   FindMaxLineLen();
}

/////////////////////////////////////////////////////////////////////////////

void CScriptText::_RemoveLine(int i)                       
{
   m_textArray.RemoveAt(i);       

   m_colors.erase(m_colors.begin() + i);

   FindMaxLineLen();
}

/////////////////////////////////////////////////////////////////////////////

void CScriptText::_RemoveAll()                             
{
   m_textArray.RemoveAll(); 
   m_colors.clear();
   FindMaxLineLen(); 

   CString firstLine;
   _InsertLine(firstLine, 0, TRUE);
}

/////////////////////////////////////////////////////////////////////////////

long CScriptText::_GetSize() const                               
{
   return m_textArray.GetSize();
}

/////////////////////////////////////////////////////////////////////////////

CString CScriptText::_GetLine(int i) /*const*/                       
{
   return m_textArray[i];
}

/////////////////////////////////////////////////////////////////////////////

/*const*/ CScriptText::lineVector &CScriptText::_GetLineColors(int i) /*const  */                     
{
   return m_colors.at(i);
}

/////////////////////////////////////////////////////////////////////////////

void  CScriptText::FullUpdate()
{
   FindMaxLineLen();

   for (int i=0;i<_GetSize();i++)
   {
      //m_pColorizer->SetLineColors(_GetLine(i), m_colors.at(i));
	  //StripAnsiChars(_GetLine(i), m_colors.at(i));
   }
}

/////////////////////////////////////////////////////////////////////////////

long  CScriptText::FindMaxLineLen()
{
   m_maxLineLen = 0;
   for (int i=0;i<m_textArray.GetSize();i++)
   {
      m_maxLineLen = max(m_maxLineLen, m_textArray[i].GetLength());
   }
   
   return m_maxLineLen;
}

/////////////////////////////////////////////////////////////////////////////

void CScriptText::SetColorizer(CColorizer *pColorizer)
{
   m_pColorizer = pColorizer;
}