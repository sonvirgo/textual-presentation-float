/////////////////////////////////////////////////////////////////////////////
// SonTime.cpp
//
// Date:        Monday, May 14, 2002
// Author:      Nguyen Luong Son
//
// Description: A class to generate Vietnamese textual 
//				description of date
//
// CopyRight(c) Nguyen Luong Son FVL 2002
// Email:		nlson@fujitsu.com.vn						
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SONTIME_H__64D4DE47_4B4B_49F7_8BF0_04783EB2A8E5__INCLUDED_)
#define AFX_SONTIME_H__64D4DE47_4B4B_49F7_8BF0_04783EB2A8E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSonTime : public CTime  
{
public:	
	CString FormatE(LPCTSTR fmtString);
	CSonTime(LPCTSTR mstr);
	typedef char * (*funcptr)(char *);  
	void put_pfnV(funcptr x);
	CString FormatV(LPCTSTR fmtString);	
	CSonTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST = -1 );
	CSonTime();
	CSonTime(const CSonTime& timeSrc);
	CSonTime& CSonTime::operator =(const CSonTime &timeSrc);
	CSonTime& CSonTime::operator =(LPCTSTR mstr);
	virtual ~CSonTime();
//	CSonTime& CSonTime::operator =(const CSonTime &timeSrc);
private:
	CString get_partE(char b);
	CString get_partV(char a);	
	funcptr m_pfnV;
};

#endif // !defined(AFX_SONTIME_H__64D4DE47_4B4B_49F7_8BF0_04783EB2A8E5__INCLUDED_)
