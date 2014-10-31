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
#ifndef _COLORIZE_
#define _COLORIZE_

#pragma warning(disable:4786)
#include <vector>
#include <set>
using namespace std;
#pragma warning(disable:4786)

#define KEYWORD_COLOR               RGB(0,0,160)
#define NORMAL_COLOR                0x00D3D3D3//RGB(192,192,192)

/*
   The base class only provides keyword coloring support.

   In this class, a "word" is a sequence of uninterrupted alpha-numeric
   characters. The keywords are loaded with the LoadKeywordFile member.
   One keyword per line in a plain text file.

   You can do more-complex processing here, or in a derived class.

*/

class CColorizer
{
public:
   CColorizer();

	virtual ~CColorizer();

   // called once per text line, when the line colors need updating.
   // 'colors' will be filled with one COLORREF per text character.
   //
   // you will definitely rewrite this function (in a derived class, probably) for your own application.
   // 
	virtual void SetLineColors(CString &pString, vector<COLORREF>& colors);
	
   // load magic keywords.
   virtual void LoadKeywordFile(CString &keywordsFile);

	BOOL m_bCompareCase;

protected:

	virtual BOOL IsKeyWord(CString & pTest);
   
   // set of keywords
   std::set<CString> m_stringSet;

};

#endif