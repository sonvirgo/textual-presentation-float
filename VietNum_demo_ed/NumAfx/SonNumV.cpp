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

#include "stdafx.h"
#include "SonNumV.h"
#include <math.h>
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSonNumV::CSonNumV()
{

}

CSonNumV::~CSonNumV()
{

}

CString CSonNumV::FirstThree(int th)
{
	CString three;
	
	if (th == 0)
	{
		three ="";
		return(three);
	}

	if ( ( th%100 ) == 0 )
		three.Format("%s %s",unit_arr[th/100],sup_arr[1]);
	else 
		three.Format("%s %s %s",unit_arr[th/100],sup_arr[1],FirstTwo(th%100));

	return(three);

}

CString CSonNumV::FirstTwo(int tw)
{
	CString two;
	int dz;
	int unt;
	
	dz = tw/10;
	unt = tw%10;

	switch ( dz )
	{
		case 1:
			switch ( unt ) 
			{
				case 5:
					two.Format("%s %s",unit_arr[10],unit_arr[12]);
					break;
				case 0:
					two.Format("%s",unit_arr[10]);
					break;
				default:
					two.Format("%s %s",unit_arr[10],unit_arr[unt]);
			}
			break;
		case 0:
			two.Format("%s %s",unit_arr[13],unit_arr[unt]);
			break;
		default:
			switch ( unt ) 
			{
				case 5:
					two.Format("%s %s",unit_arr[dz],unit_arr[11]);
					break;
				case 0:
					two.Format("%s %s",unit_arr[dz],sup_arr[0]);
					break;
				case 1:
					two.Format("%s %s",unit_arr[dz],unit_arr[14]);
					break;
				case 4:
					two.Format("%s %s",unit_arr[dz],unit_arr[15]);
					break;
				default:
					two.Format("%s %s",unit_arr[dz],unit_arr[unt]);
			}
			break;			
	}
	return(two);

}

CString CSonNumV::Fractal(CString cstw)
{
	CString two("");

	int dz;
	int unt;
	int il;
	int tw;

	il = cstw.GetLength();
	tw = atoi(cstw);

	dz = tw/10;
	unt = tw%10;

	if ( il == 1)
		return(unit_arr[tw]);
	else
		if ( tw < 10 )
		{
			two.Format("%s %s",unit_arr[0],unit_arr[tw]);
			return(two);
		}
		else 
			if ( unt == 0 )
				return(unit_arr[dz]);

	switch ( dz )
	{
		case 1:
			switch ( unt ) 
			{
				case 5:
					two.Format("%s %s",unit_arr[10],unit_arr[12]);
					break;
				case 0:
					two.Format("%s",unit_arr[10]);
					break;
				default:
					two.Format("%s %s",unit_arr[10],unit_arr[unt]);
			}
			break;
		case 0:
			two.Format("%s %s",unit_arr[0],unit_arr[unt]);
			break;
		default:
			switch ( unt ) 
			{
				case 5:
					two.Format("%s %s",unit_arr[dz],unit_arr[11]);
					break;
				case 0:
					two.Format("%s %s",unit_arr[dz],sup_arr[0]);
					break;
				case 1:
					two.Format("%s %s",unit_arr[dz],unit_arr[14]);
					break;
				case 4:
					two.Format("%s %s",unit_arr[dz],unit_arr[15]);
					break;
				default:
					two.Format("%s %s",unit_arr[dz],unit_arr[unt]);
			}
			break;			
	}
	return(two);
}

CString CSonNumV::NumComb(double x, char *s)
{
	int it;
	CString numall;
	CString stemp(s);
	CString ct(s);
	int ilen;
	int im;
	
	if (x == 0)
		return(unit_arr[(int)x]);

	ilen = stemp.GetLength();
	
	im = ilen%3; 
	stemp = ct.Left(im);
	it = atoi(stemp);
		

	switch ( im )
	{
	case 1:
		numall.Format("%s",unit_arr[(int)it]);
		break;
	case 2:
		numall = FirstTwo((int)it);
		break;
	}
	
	if (ilen == 3 ) 
	{
		numall = FirstThree((int)x);
		return(numall);
	}

	im = ilen - im;
	ct = ct.Right(im);
	
	int z;
	z=4;

	BOOL bt;
	
	bt=TRUE;

	while ( im > 0 )
	{	
		stemp = ct.Left(3);
		it = atoi(stemp);
		if ( z == 4)
		{
			z = (im /3)%3;
			if (z == 0)
				z = 3;
		}
		if (it == 0) 
		{
			if (bt)
			{
				if (numall != "")
					numall = " " + numall + " " + sup_arr[(z + 1)] ;
			}
			im -= 3;
			ct = ct.Right(im);
			z = (im /3)%3;
			if (z == 0)
				z = 3;
			if (z == 3)
				bt = TRUE;
			else
				bt = FALSE;

			continue;
		}
		if (bt)
				if (numall != "")
				{
					numall = " " + numall + " " + sup_arr[(z + 1)] + " "+ FirstThree(it);
				}
				else
					numall = FirstThree(it);
		else
				if (numall != "")
				{
					numall = " " + numall + " " + FirstThree(it);
				}
				else
					numall = FirstThree(it);
		
		im -= 3;
		ct = ct.Right(im);
		z = (im /3)%3;
		if (z == 0)
			z = 3;
		bt=TRUE;
	}

	return(numall);
}

char * CSonNumV::CardinalV(char *numstr, char *g_num)
{
	CString ret("");
	double x;
	char *stopstring;
	CString cstmp("");		
	int d;
	int itmp;
	int  decimal, sign;
	int signall;
	char *buffer;

	d = 0;
	signall = 0;

	if ((x = strtod( numstr, &stopstring )) == HUGE_VAL )
		return("NG Error overflow");

	*stopstring = '\0';
	ret.Format("%s", numstr);

	if (x <0)
		signall = 1;

	itmp = ret.Find('.');

	if ( itmp != -1)
	{
		cstmp = ret.Mid(itmp + 1,2);
		d = atoi(cstmp);
		ret = ret.Left(itmp);
	}
	
	if ((x = strtod( ret, &stopstring )) == HUGE_VAL )
		return("NG Error overflow");
	
	buffer = _fcvt( x, 0, &decimal, &sign );

	if (sign != 0)
		x = -x ;

	decimal = strlen(buffer);

	strcpy(buffer,ret.Right(decimal));

	ret = NumComb( x, buffer);

	ret.TrimLeft(" ");

	ret.TrimRight(" ");

		
	if (d != 0)
		ret = ret + " point " + Fractal(cstmp);

	if (signall != 0)
		ret = "minus " + ret;

	ret	= "OK " + ret;
	
	strcpy(g_num,ret);

	return(g_num) ;

}

char * CSonNumV::NoncountV(char *numstr, char *g_num)
{
	CString cc(numstr);
	CString ttt("");
	CString ret("");
	int i,j;
	char k;
		
	j = cc.GetLength();
	
	for (i=0; i < j ;i++)
	{
		if ((k = cc.GetAt(i)) == ' ')
			continue;
		ttt = k;
		if ( (47<k) & (k<58) )
			ttt.Format("%s",unit_arr[k-48]);	
		ret += " " + ttt;
	}

	ret = "OK" + ret;
	
	strcpy(g_num, ret);

	return(g_num);

}
