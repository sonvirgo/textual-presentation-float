/////////////////////////////////////////////////////////////////////////////
// SonJFalconNumE.cpp
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
#include "stdafx.h"
#include "SonJFancolNumE.h"
extern "C" 
{
#include "NumWord.h"
}


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSonJFancolNumE::CSonJFancolNumE()
{

}

CSonJFancolNumE::~CSonJFancolNumE()
{

}

char * CSonJFancolNumE::CardinalE(char *numstr, char *g_num)
{
	unsigned long ul=0;
	char *x;
	dropZeros(g_num,numstr);
	ul = _tcstoul(g_num,&x,10);
	getNumCardinal(g_num,ul,FALSE,FALSE);
	return g_num;
}

char * CSonJFancolNumE::OrdinalE(char *numstr, char *g_num)
{
	unsigned long ul=0;
	char *x;
	dropZeros(g_num,numstr);
	ul = _tcstoul(g_num,&x,10);
	getNumOrdinal(g_num,ul,FALSE,TRUE);
	return g_num;
}
