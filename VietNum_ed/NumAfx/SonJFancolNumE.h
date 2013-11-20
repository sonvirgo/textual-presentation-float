/////////////////////////////////////////////////////////////////////////////
// SonJFalconNumE.h
//
// Date:        Monday, May 14, 2002
// Author:      Nguyen Luong Son
//
// Description: A class to generate English textual 
//				description of interger
//
// CopyRight(c) Nguyen Luong Son FVL 2002
// Email:		nlson@fujitsu.com.vn						
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SONJFANCOLNUME_H__F8D0C6F4_A17F_4E50_98C6_4BE4BDB66E17__INCLUDED_)
#define AFX_SONJFANCOLNUME_H__F8D0C6F4_A17F_4E50_98C6_4BE4BDB66E17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSonJFancolNumE  
{
public:
	static char * OrdinalE(char * numstr, char * g_num);
	static char * CardinalE(char *numstr, char *g_num);
	CSonJFancolNumE();
	virtual ~CSonJFancolNumE();

};

#endif // !defined(AFX_SONJFANCOLNUME_H__F8D0C6F4_A17F_4E50_98C6_4BE4BDB66E17__INCLUDED_)
