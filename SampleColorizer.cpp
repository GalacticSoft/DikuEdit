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

// SampleColorizer.cpp : implementation of the CSampleColorizer class
//

#include "stdafx.h"
#include "SampleColorizer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "Progs.h"

/////////////////////////////////////////////////////////////////////////////

/*
   SetLineColors

   This is where you decide how to color the text.
   
   The colors vector will have an element for each character in the input string.
   Each element in the vector is a COLORREF that tells the edit control which color to 
   use when drawing the corresponding character.

   It is expected that you will rewrite most of the code in this function to fit 
   your own application.

   This function, as written, has access to only a single line at a time. If you need
   to access the entire text buffer, you will have to find your own way to do that.


   
   This sample uses a keywords.ini to define a few keywords (set by the parent of the edit control). 
   It also does some context-sensitive keyword coloring in this function. 
   
   The rules for this CSampleColorizer are:

   
   There is nothing special about these rules. They simply demonstrate some simple ways
   of doing context-sensitive coloring.
   
*/

void CAnsiColorizer::SetLineColors(CString &csString, vector<COLORREF>& colors) 
{
	int i;
	COLORREF color;

   // nothing to do
   if (csString.GetLength() ==0) 
   {
      colors.clear();
      return;
   }
			
   // one COLORREF per input char
   colors.resize(csString.GetLength());
	
   for(i = 0; i < csString.GetLength(); i++)
	{
	   if(csString[i] == ' ')
		   continue;

	   if(csString[i++] == '&') {
		   if(i >= csString.GetLength())
			   break;
			if(csString[i] == '+') {
					i++;
				if(i >= csString.GetLength())
					break;

				switch(csString[i]) {
					case 'R': color = red;			break;
					case 'r': color = darkred;		break;
					case 'B': color = blue;			break;
					case 'b': color = darkblue;		break;
					case 'W': color = white;		break;
					case 'w': color = lightgrey;	break;
					case 'L': 
					case 'l': color = gray;			break;
					case 'g': color = green;		break;
					case 'G': color = lawngreen;	break;
					case 'm': color = darkmagenta;	break;
					case 'M': color = magenta;		break;
					case 'c': color = darkcyan;		break;
					case 'C': color = cyan;			break;
					case 'y': color = peru;			break;
					case 'Y': color = yellow;		break;
					default:  color = def_color;	break;
				}
			} else //if(csString[i] == 'N' || csString[i] == 'n')
				color = def_color;

			i++;
			if(i > csString.GetLength())
				break;

			while(i < csString.GetLength()){	
				if(csString[i] != '&') {	
					colors.at(i) = color;
					i++;
				} else {
					i--;
					break;
				}
			}
	   } else	
			CColorizer::SetLineColors(csString, colors);		
	}
}

void CProgColorizer::SetLineColors(CString &csString, vector<COLORREF>& colors)
{
	int pos = 0;
	CString str;

	colors.clear();

	// nothing to do
	if (csString.GetLength() ==0) 
		 return;

   // one COLORREF per input char
   colors.resize(csString.GetLength());

   if((csString[0]=='>'))
   {   
	   pos = csString.Find(' ', 1);
	   
	   if(pos == -1)
		   pos = csString.Find('\0', 1);

	   str = csString.Mid(1, pos-1);
		
	   for(int i=1; i<pos; i++)
		{
			if(IsProgType(str))
				colors.at(i) = green;
			else
				colors.at(i) = red;
		}
   }
   else
   { 
	   ColorProgComms(csString, colors);
	   ColorKeywords(csString, colors);
	   ColorTargTypes(csString, colors);
	   ColorFuncTypes(csString, colors);
   }
}

	
void CProgColorizer::ColorKeywords(CString &csString, vector<COLORREF>& colors)
{
	int pos;
	CString str;
	int len;

	pos = 0;
	
	if(IsKeyword(csString))
	{
		for(int i=0; i<csString.GetLength(); i++)
		{		
			colors.at(i) = blue;
		}
	}

	while(pos < csString.GetLength())
	{
		len = csString.Find(' ', pos);
		
		if(len == -1)
			len = csString.Find('\0', pos);
		if(len == -1)
			len = csString.Find('\n', pos);
		if(len == -1)
			len = csString.Find('\r', pos);
		if(len == -1)
			len = csString.Find('\t', pos);
			
		len = len-pos;
		str = csString.Mid(pos, len);
			   
		if(IsKeyword(str))
		{
			for(int i=pos; i<pos+len; i++)
			{		
				colors.at(i) = blue;
			}
		}
			
		pos++;
	}
}

void CProgColorizer::ColorProgTypes(CString &csString, vector<COLORREF>& colors)
{
	
}

void CProgColorizer::ColorTargTypes(CString &csString, vector<COLORREF>& colors)
{
	int pos, pos2;
	CString str;

	pos = 0;

	if(csString.Find('$', pos) > -1)
	{
		while(pos < csString.GetLength())
		{
			pos2 = csString.Find('$', pos);
			
			if(pos == -1)
				pos = csString.Find('\0', pos);
			if(pos == -1)
				pos = csString.Find('\n', pos);
			if(pos == -1)
				pos = csString.Find('\r', pos);
			if(pos == -1)
				pos = csString.Find('\t', pos);
			
			if(pos2 < pos)
			{
				pos++;
				continue;
			}

			pos = pos2;
			str = csString.Mid(pos2, 2);
			   
			if(IsTargType(str))
			{
				for(int i=pos2; i<pos+2; i++)
				{		
					colors.at(i) = gray;
				}
			}
			
			pos++;
		}
	}
}

void CProgColorizer::ColorFuncTypes(CString &csString, vector<COLORREF>& colors)
{
	int pos;
	CString str;
	int len;

	pos = 0;
	
	if(IsProgFunc(csString))
	{
		for(int i=0; i<csString.GetLength(); i++)
		{		
			colors.at(i) = red;
		}
	}

	while(pos < csString.GetLength())
	{
		len = csString.Find('(', pos);
		
		if(len == -1)
			len = csString.Find('\0', pos);
		if(len == -1)
			len = csString.Find('\n', pos);
		if(len == -1)
			len = csString.Find('\r', pos);
		if(len == -1)
			len = csString.Find('\t', pos);
		if(len == -1)
			len = csString.Find(' ', pos);
			
		len = len-pos;

		str = csString.Mid(pos, len);
			   
		if(IsProgFunc(str))
		{
			for(int i=pos; i<pos+len; i++)
			{		
				colors.at(i) = red;
			}
		}
			
		pos++;
	}
}

void CProgColorizer::ColorProgComms(CString &csString, vector<COLORREF>& colors)
{
	int pos;
	CString str;
	int len;

	pos = 0;
	
	if(IsProgFunc(csString))
	{
		for(int i=0; i<csString.GetLength(); i++)
		{		
			colors.at(i) = purple;
		}
	}

	while(pos < csString.GetLength())
	{
		len = csString.Find(' ', pos);
		
		if(len == -1)
			len = csString.Find('\0', pos);
		if(len == -1)
			len = csString.Find('\n', pos);
		if(len == -1)
			len = csString.Find('\r', pos);
		if(len == -1)
			len = csString.Find('\t', pos);
			
		len = len-pos;
		str = csString.Mid(pos, len);
			   
		if(IsProgComm(str))
		{
			for(int i=pos; i<pos+len; i++)
			{		
				colors.at(i) = purple;
			}
		}
			
		pos++;
	}
}

bool CProgColorizer::IsKeyword(CString str)
{
	for(int x = 0;  x < ProgKeywordCount(); x++)
	{
		if(str == progkeywords[x])
			return true;
	}

	return false;
}

bool CProgColorizer::IsProgType(CString str)
{
	for(int x = 0;  x < ProgCount(); x++)
	{
		if(str == progs[x].name)
			return true;
	}
	
	return false;
}

bool CProgColorizer::IsTargType(CString str)
{
	for(int x = 0;  x < VarCount(); x++)
	{
		if(str == prog_vars[x])
			return true;
	}
	return false;
}

bool CProgColorizer::IsProgFunc(CString str)
{
	for(int x = 0;  x < ProgFuncCount(); x++)
	{
		if(str == prog_funcs[x])
			return true;
	}
	return false;
}

bool CProgColorizer::IsProgComm(CString str)
{
	for(int x = 0;  x < ProgCommCount(); x++)
	{
		if(!str.CompareNoCase(prog_comms[x]) /* == prog_comms[x]*/)
			return true;
	}
	return false;
}