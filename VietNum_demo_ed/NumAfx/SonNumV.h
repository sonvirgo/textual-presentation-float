/////////////////////////////////////////////////////////////////////////////
// SonNumV.h
//
// Date:        Monday, May 14, 2002
// Author:      Nguyen Luong Son
//
// Description: A class to generate Vietnamese textual 
//				description of decimal number with scale of 2
//
// CopyRight(c) Nguyen Luong Son FVL 2002
// Email:		nlson@fujitsu.com.vn						
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SONNUMV_H__8989612C_BF51_4F3F_A19C_00A7E78D96FB__INCLUDED_)
#define AFX_SONNUMV_H__8989612C_BF51_4F3F_A19C_00A7E78D96FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSonNumV  
{
public:
	static char * NoncountV(char * numstr, char * g_num);
	static char * CardinalV(char *numstr, char *g_num);
	CSonNumV();
	virtual ~CSonNumV();

private:

	static CString FirstTwo(int tw);
	static CString FirstThree(int th);
	static CString Fractal(CString cstw);
	static CString NumComb(double x, char *s);
};

#endif // !defined(AFX_SONNUMV_H__8989612C_BF51_4F3F_A19C_00A7E78D96FB__INCLUDED_)
