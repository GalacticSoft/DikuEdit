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

#ifndef PROGTEXTH
#define PROGTEXTH

#pragma warning(disable:4786)
#include "Colorizer.h"
#include <vector>
using namespace std;
#pragma warning(disable:4786)

class ProgText
{
public:

   // we'll have one lineVector per text line
   typedef vector<COLORREF> lineVector;

   ProgText ();

	ProgText & operator = (ProgText & source);

   // how many lines?
   long _GetSize() const;

   // get a line
   CString _GetLine(int i) const;

   // colors for a line?
   const lineVector &_GetLineColors(int i) const;
   
   // insert a line
   void _InsertLine(CString line, int i, BOOL bUpdate=TRUE);
   
   // modify an existing line
   void _SetLine(CString line, int i);

   // remove a single line
   void _RemoveLine(int i);

   // remove all lines
   void _RemoveAll();

   // recolor and recalc longest lien
   void  FullUpdate();

   // find the length of the longest line
   long  FindMaxLineLen();
 
   void SetColorizer(CColorizer *pColorizer);

public:
   long        m_maxLineLen;

protected:
    CStringArray  m_textArray;

    CColorizer   m_defaultColorizer;
    CColorizer   *m_pColorizer;

    vector <lineVector> m_colors;
    
};
#endif