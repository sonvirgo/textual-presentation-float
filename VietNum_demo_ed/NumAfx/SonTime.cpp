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
#include "stdafx.h"
#include "SonTime.h"
#include "tokenizer.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSonTime::CSonTime()
:CTime(CTime::GetCurrentTime())
{
	m_pfnV = & VS_MainNum;
}

CSonTime::~CSonTime()
{

}

CSonTime::CSonTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST)
:CTime(nYear,nMonth,nDay,nHour,nMin,nSec,nDST)
{
	m_pfnV = & VS_MainNum;
}

CSonTime& CSonTime::operator =(const CSonTime &timeSrc)
{
	CTime::operator=(timeSrc);
	m_pfnV = timeSrc.m_pfnV;
	return *this ;
}

CSonTime::CSonTime(const CSonTime& timeSrc)
:CTime((CTime)timeSrc)
{
	m_pfnV = timeSrc.m_pfnV;
}

CString CSonTime::FormatV(LPCTSTR fmtString)
{
	CString c,cc(""),o(fmtString);
	CTokenizer ct(fmtString,"%");
	BOOL b=FALSE;

	if (m_pfnV==NULL)
		return "NG no conversion function";	

	if (o.GetAt(0) == '%')
		b = TRUE;

	while (ct.Next(c))
	{
		if (b)
			cc += get_partV(c.GetAt(0)) + c.Right(c.GetLength()-1);
		else
			cc += c;
		b = TRUE;
	}
		
	return cc;
}

void CSonTime::put_pfnV(funcptr x)
{
	m_pfnV = x;
}

CString CSonTime::get_partV(char b)
{
	CString c;
	char a[255];
	int i;

	switch (b)
	{
	case 'A':
		{
			i = GetDayOfWeek();
			switch (i)
			{
				case 1:
					c = "Sunday";
					break;
				case 4:
					c.Format("%s %s","wday",unit_arr[15]);
					break;
				default:
					{
						c.Format("%s",m_pfnV(_itoa(i,a,10)));
						c = c.Right(c.GetLength()-3); 
						c = "wday " + c;
					}
			}			
		}
			break;
	case 'B':
		{
			i = GetMonth();
			switch (i)
			{
				case 4:
					c.Format("%s %s","month",unit_arr[15]);
					break;
				default:
					{
						c.Format("%s",m_pfnV(_itoa(i,a,10)));
						c = c.Right(c.GetLength()-3); 
						c = "month " + c;
					}
			}			
		}
			break;
	case 'd':
		{
			i = GetDay();
			c.Format("%s",m_pfnV(_itoa(i,a,10)));
			c = c.Right(c.GetLength()-3); 
			if (i<11)
				c = "day mg " + c;
			else
				c = "day " + c;			
		}
			break;
	case 'H':
		{	
			c.Format("%s hour",m_pfnV(_itoa(GetHour(),a,10)));
			c = c.Right(c.GetLength()-3); 
		}
			break;
	case 'M':
		{	
			c.Format("%s minute",m_pfnV(_itoa(GetMinute(),a,10)));
			c = c.Right(c.GetLength()-3) ;
		}
			break;
	case 'S':
		{	
			c.Format("%s second",m_pfnV(_itoa(GetSecond(),a,10)));
			c = c.Right(c.GetLength()-3) ;
		}			
			break;
	case 'y':
		{	
			c.Format("%s",m_pfnV(_itoa(GetYear()%100,a,10)));
			c = c.Right(c.GetLength()-3) ;
			c = "year " + c;
		}
			break;
	case 'Y':
		{	
			c.Format("%s",m_pfnV(_itoa(GetYear(),a,10)));
			c = c.Right(c.GetLength()-3) ;
			c = "year " + c;
		}
			break;
	default:
			c = b;
	}
	return c;	
}

CSonTime::CSonTime(LPCTSTR mstr)
{
	CString css(mstr);
	CTokenizer ctt(mstr," /:,");
	int i,j[6];

	if ((css=="0000 00 00 00:00:00")|(css=="")|(mstr == NULL))
	{
		CTime ct = CTime::GetCurrentTime();		
		CTime *pt = this;
		*pt = ct;
	}
	else
	{
		for (i=0;i<6;i++)
		{
			if (ctt.Next(css))
				j[i] = atoi(css);
			else 
				j[i] = 0;
		}

		CTime ct(j[0],j[1],j[2],j[3],j[4],j[5]);
		CTime *pt = this;
		*pt = ct;
	}
	m_pfnV = & VS_MainNum;
}

CSonTime& CSonTime::operator =(LPCTSTR mstr)
{
	CSonTime cst(mstr);
	operator=(cst);
	return *this;
}

CString CSonTime::FormatE(LPCTSTR fmtString)
{
	CString c,cc(""),o(fmtString);
	CTokenizer ct(fmtString,"%");
	BOOL b = FALSE;

	if (m_pfnV==NULL)
		return "NG no conversion function";	
	
	if (o.GetAt(0) == '%')
		b = TRUE;

	while (ct.Next(c))
	{
		if (b)
			cc += get_partE(c.GetAt(0)) + c.Right(c.GetLength()-1);
		else
			cc += c;
		b = TRUE;
	}
			
	return cc;
}

CString CSonTime::get_partE(char b)
{
	CString c;
	char a[255];
	int i;
	funcptr pOE = &VS_OrdinalE;
	funcptr pCE = &VS_CardinalE;

	switch (b)
	{
	case 'A':
		{
			c = Format("%A");
		}
			break;
	case 'B':
		{
			c = Format("%B");			
		}
			break;
	case 'd':
		{
			i = GetDay();
			c.Format("%s",pOE(_itoa(i,a,10)));
			c = c.Right(c.GetLength()-3); 			
			c = "the " + c;
		}
			break;

	case 'H':
		{	
			c.Format("%s",pCE(_itoa(GetHour(),a,10)));
			c = c.Right(c.GetLength()-3); 
		}
			break;
	case 'M':
		{	
			c.Format("%s",pCE(_itoa(GetMinute(),a,10)));
			c = c.Right(c.GetLength()-3) ;
		}
			break;
	case 'S':
		{	
			c.Format("%s second",pCE(_itoa(GetSecond(),a,10)));
			c = c.Right(c.GetLength()-3) ;
		}			
			break;
	case 'y':
		{	
			c.Format("%s",pCE(_itoa(GetYear()%100,a,10)));
			c = c.Right(c.GetLength()-3) ;			
		}
			break;
	case 'Y':
		{	
			if ( (i = GetYear()) < 2000)
			{
				CString c1;
				
				c.Format("%s",pCE(_itoa(i/100,a,10)));
				c = c.Right(c.GetLength()-3) ;			

				
				c1.Format("%s",pCE(_itoa(i%100,a,10)));
				c1 = c1.Right(c1.GetLength()-3) ;			

				c = c + " " + c1;
			}
			else
			{
				c.Format("%s",pCE(_itoa(i,a,10)));
				c = c.Right(c.GetLength()-3) ;	
			}
		}
			break;
	default:
			c = b;
	}
	return c;
}
