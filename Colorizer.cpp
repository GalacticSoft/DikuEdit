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

// Colorizer.cpp : implementation of the CColorizer class
//

#include "stdafx.h"
#include "Colorizer.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

CColorizer::CColorizer()
{
   m_bCompareCase = FALSE ;
}

/////////////////////////////////////////////////////////////////////////////

CColorizer::~CColorizer()
{
}

void CColorizer::SetLineColors(CString &csString, vector<COLORREF>& colors) 
{
   // nothing to do
   if (csString.GetLength() ==0) 
   {
      colors.clear();
      return;
   }

   // one COLORREF per input char
   colors.resize(csString.GetLength());

   // look for keywords

	CString word;
	word = csString;
	word.TrimLeft();
	word.TrimRight();
	word = word.Left(3);
	
	//set the line to all black
	int k = 0;
	int j = csString.GetLength();
	for(int i=0; i<j; i++)
	{
		colors.at(i) = NORMAL_COLOR;
	}

   // do keyword coloring and auto-case correction
	while(k<j)
	{
      // find "words" (sequences of alpha-numeric characters)
		word.Empty();
		while((k<j) && (!isalnum(csString.GetAt(k))))
		{
			k++;
		}

		int s = k;
		while((k < j) && (isalnum(csString.GetAt(k))))
		{
			word = word + csString.GetAt(k);
			k++;
		}
		
      int e = k;
		
      word.TrimLeft();
		word.TrimRight();

		if(IsKeyWord(word))
		{
			int l = 0;
			for(int i=s; i<e; i++)
			{
				l++;
				colors.at(i) = KEYWORD_COLOR;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

BOOL CColorizer::IsKeyWord(CString & test)
{
   std::set<CString>::iterator it;
   if (m_bCompareCase)
   {
      CString t(test); t.MakeUpper();

      it = m_stringSet.find(t);
   }
   else
   {
      it = m_stringSet.find(test);
   }

   return (it != m_stringSet.end());
}

/////////////////////////////////////////////////////////////////////////////

void CColorizer::LoadKeywordFile(CString &m_csaKeyWordsFile)
{
   if (m_csaKeyWordsFile.IsEmpty()) 
   {
      return;
   }

	FILE * infile;
	char buffer[512];
	CString inifile = m_csaKeyWordsFile;
	if(infile = fopen(inifile,"rb"))
	{
		while(!feof(infile))
		{
			fscanf(infile,"%s",buffer);

         CString t(buffer);
         if (m_bCompareCase)
         {
            t.MakeUpper();
         }

         m_stringSet.insert(t);
		}

		fclose(infile);
	}
}
