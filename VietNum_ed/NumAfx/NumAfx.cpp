/********************************************************************/
/*	A DLL to interpret DOUBLE number to VIETNAMESE textual string	*/
/*		and to convert a date to VIETNAMESE textual string			*/
/*				CopyRight(c) Nguyen Luong Son FVL 2002				*/
/*					Email: nlson@fujitsu.com.vn						*/
/********************************************************************/
 
//NumAfx.cpp : Defines the initialization routines for the DLL.
// 

#include "stdafx.h"
#include "NumAfx.h"
#include "sontime.h"
#include "sonnumv.h"
#include "sonjfancolnume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CNumAfxApp

BEGIN_MESSAGE_MAP(CNumAfxApp, CWinApp)
	//{{AFX_MSG_MAP(CNumAfxApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

char g_ConvStr[1024];
char g_szfmt[255];

/////////////////////////////////////////////////////////////////////////////
// CNumAfxApp construction

CNumAfxApp::CNumAfxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//////////////////////////////////////////////////////
	strcpy(g_szfmt,"%H %M %S %B %d %Y"); /**/
	//////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNumAfxApp object

CNumAfxApp theApp;

extern "C" NUMANALYSE_API char *VS_CardinalE(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSonJFancolNumE::CardinalE(numstr,g_ConvStr);
	CString c(g_ConvStr);
	c = "OK " + c;
	strcpy(g_ConvStr,c);
	return(g_ConvStr);
}

extern "C" NUMANALYSE_API char *VS_OrdinalE(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSonJFancolNumE::OrdinalE(numstr,g_ConvStr);
	CString c(g_ConvStr);
	c = "OK " + c;
	strcpy(g_ConvStr,c);
	return(g_ConvStr);
}

extern "C" NUMANALYSE_API char *VS_MainNum(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSonNumV::CardinalV(numstr,g_ConvStr);
	return(g_ConvStr) ;
}
extern "C" NUMANALYSE_API char *Set_Fmt(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	strcpy(g_szfmt,numstr);
	return("OK set success") ;
}
extern "C" NUMANALYSE_API char *VS_DateTimeV(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString ccc(numstr);	
	try
	{
		CSonTime cct;
		cct = numstr;
		ccc = cct.FormatV(g_szfmt);
		ccc = "OK " + ccc;
	}
	catch (...)
	{
		ccc = "NG invalid time";
	}
	strcpy(g_ConvStr, ccc);
	return(g_ConvStr);
}
extern "C" NUMANALYSE_API char *VS_NonCount(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSonNumV::NoncountV(numstr,g_ConvStr) ;
	return(g_ConvStr);
}
extern "C" NUMANALYSE_API char *VS_DateTimeE(char *numstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString ccc(numstr);	
	try
	{
		CSonTime cct;
		cct = numstr;
		ccc = cct.FormatE(g_szfmt);
		ccc = "OK " + ccc;
	}
	catch (...)
	{
		ccc = "NG invalid time";
	}
	strcpy(g_ConvStr, ccc);
	return(g_ConvStr);
}