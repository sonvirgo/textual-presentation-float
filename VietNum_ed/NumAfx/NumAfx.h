// NumAfx.h : main header file for the NUMAFX DLL
//

#if !defined(AFX_NUMAFX_H__6B9C2CF7_42BE_11D6_98DB_0000E221B0A3__INCLUDED_)
#define AFX_NUMAFX_H__6B9C2CF7_42BE_11D6_98DB_0000E221B0A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNumAfxApp
// See NumAfx.cpp for the implementation of this class
//

class CNumAfxApp : public CWinApp
{
public:
	CNumAfxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumAfxApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNumAfxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMAFX_H__6B9C2CF7_42BE_11D6_98DB_0000E221B0A3__INCLUDED_)
