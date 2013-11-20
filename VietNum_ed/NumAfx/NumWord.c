#include <stdlib.h>		// standard library routines
#include <string.h>		// string manipulation routines
#include "NumWord.h"	// header for this file

/*/
/ / -----------------------------------------------------------------------
/ /
/ /  Author:		Jeremy Lee Falcon
/ /  Copyright:		©2002 Jeremy Falcon. All Rights Reserved.
/ /  Platforms:		Any that supports a ANSI compliant compiler
/ /  Purpose:		To convert a number to its text-based equivalent
/ /
/ /  Description:
/ /	   [Common Declarations]
/ /			This software is not subject to any export provision of
/ /			the United States Department of Commerce, and may be
/ /			exported to any country or planet.
/ /
/ /	   [License]
/ /			Permission is granted to anyone to use this software for any  
/ /			purpose on any computer system, and to alter it and 
/ /			redistribute it freely, subject to the following
/ /			restrictions:
/ /
/ /			1. The author is not responsible for the consequences of
/ /			   use of this software, no matter how awful, even if they
/ /			   arise from flaws in it.
/ /
/ /			2. The origin of this software must not be misrepresented,
/ /			   either by explicit claim or by omission. Since few users
/ /			   ever read sources, credits must appear in the documentation
/ /			   or about box.
/ /
/ /			3. Altered versions must be plainly marked as such, and
/ /			   must not be misrepresented as being the original software.
/ /
/ /			4. This notice may not be removed or altered.
/ /
/ /  Disclaimer:
/ /		THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
/ /		ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED 
/ /		TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
/ /		PARTICULAR PURPOSE.
/ /
/ /  Notes:
/ /		If you have any questions regarding the above clause, please
/ /		direct them to license@imputek.com
/ / -----------------------------------------------------------------------
/*/

// 2D matrix (used for char mappings with a radix of ten)
typedef char matrix[10][10];

// decimal (Base 10) character mappings
matrix decimal[4] =
{
	{
		{"Zero\0"}, {"One\0"}, {"Two\0"},   {"Three\0"}, {"Four\0"},
		{"Five\0"}, {"Six\0"}, {"Seven\0"}, {"Eight\0"}, {"Nine\0"}
	},
	{
		{"\0"},     {"Ten\0"},  {"Twent\0"},  {"Thirt\0"}, {"Fort\0"},
		{"Fift\0"}, {"Sixt\0"}, {"sevent\0"}, {"Eight\0"}, {"Ninet\0"}
	},
	{
		{"Eleven\0"},  {"Twelve\0"},    {"Thirteen\0"}, {"Fourteen\0"}, {"Fifteen\0"},
		{"Sixteen\0"}, {"Seventeen\0"}, {"Eighteen\0"}, {"Nineteen\0"}
	},
	{
		{"\0"}, {"Hundred\0"}, {"Thousand\0"}, {"Million\0"}, {"Billion\0"}
	}
};

// ordinal (Base 10) character mappings and trailers
matrix ordinal =
{
	{"Zeroth\0"}, {"First\0"}, {"Second\0"}, {"Third\0"},
	{"Fifth\0"}, {"Twelfth\0"}, {"th\0"}, {"ieth\0"}
};

// cardinal trailer and conjunction
char cardinal[] = {"y"}, conjunction[] = {"And "};


/*/
/ / This function will take a number and return the equivalent cardinal
/ / number represented as a word.  If isAnd is set to TRUE (1) then it
/ / will use "and" as a conjunction.  The isProper param affects the
/ / case of the returned string.
/ /
/ / CREDIT: Thanks to benjymous of codeproject.com for the "and" tip.
/*/

char *
getNumCardinal (char *szDest, unsigned long num, short isProper, short isAnd)
{
	/*/
	/ / NOTE: This function will handle up to 10 decimal places.  A number
	/ / greater than or equal to 10 billion will be returned as a string,
	/ / but without the conversion.  Do realize the ability to even exceed
	/ / this will depend on the system you're developing for.  To use a
	/ / number that large, you'll need a 64-bit value.
	/*/

	// according to MSDN ultoa() only supports 33 bytes
	char szNum[36] = {0};
	char szEnd[15] = {0}, szResult[150] = {0}, szNumber[150] = {0}, szTemp[150] = {0};

	// convert to a string
	ultoa(num, szNum, 10);

	// is the number too large?
	if(num > 9999999999)
	{
		// return the number as a string
		strcpy(szDest, szNum);
		return szDest;
	}
	else if(num == 0)
	{
		// we all know zero is a special case in C -- treat it as such
		strcpy(szResult, decimal[0][0]);

		// did the caller want an improper string?
		if(isProper == FALSE) strlwr(szResult);

		strcpy(szDest, szResult);
		return szDest;
	}
	else
	{
		unsigned int x, index, iBlock;
		char szSpace[2], szBlock[4];

		// null-terminate
		szSpace[1] = '\0';
		szBlock[3] = '\0';

		/*/
		/ / Ok, we have a number we can use!  Prepare it by reversing.
		/ / This is because we can safely start and label from the
		/ / ones place holder consistently.  The other side is variable.
		/*/
		strcpy(szNum, strrev(szNum));

		/*/
		/ / NOTE: We must traverse the number in blocks of three.
		/ / Use the first in the block with offset 2, second with
		/ / offset 1, and third with offset 0.  Remember to use
		/ / x to figure out which value in offset 2 is used.
		/*/
		for(x=0; x<strlen(szNum); x += 3)
		{
			// compute the index and spacing to use
			if(x >= 3)
			{
				index = ((x / 3) + 1);
				szSpace[0] = ' ';
			}
			else
			{
				index = (x / 3);
				szSpace[0] = '\0';
			}

			// store the larger place holder representation
			strcpy(szEnd, decimal[3][index]);

			// extract the numbers for this block and reverse
			// them back to the original order we received
			strncpy(szBlock, szNum + x, 3);
			strcpy(szBlock, strrev(szBlock));

			// pull out any leading zeros
			dropZeros(szBlock, szBlock);

			// get the integral value
			iBlock = atoi(szBlock);

			// if this block is nothing but zeros, we don't need to process it
			if(iBlock == 0) continue;

			// process according to the length of the block by prepending
			// the corresponding mapped text from the decimal matrix
			switch(strlen(szBlock))
			{
				case 3:
					// find out if we need to use special case words
					if((atoi(&szBlock[1]) >= 11) && (atoi(&szBlock[1]) <= 19))
					{
						// all our buffers are being used, but we can safely use
						// the index variable because we are finished with it
						index = atoi(&szBlock[1]) - 11;
						strcpy(szNumber, decimal[2][index]);
					}
					else if(!(atoi(&szBlock[1])) % 10)
					{
						strcpy(szNumber, decimal[1][atoi(&szBlock[1]) / 10]);
					}
					else
					{
						if(szBlock[1] != '0')
						{
							// all our buffers are being used, but we can safely use
							// the index variable because we are finished with it
							index = atoi(&szBlock[1]);

							if(szBlock[2] != '0')
							{
								strcpy(szNumber, decimal[1][atoi(strncpy(szTemp, szBlock + 1, 1))]);

								// append the cardinal trailer
								if(index != 10) strcat(szNumber, cardinal);

								// include the separator
								strcat(szNumber, "-");

								// we can use index
								index = atoi(&szBlock[2]);
								strcpy(szTemp, decimal[0][index]);
								strcat(szNumber, szTemp);
							}
							else
							{
								strcpy(szNumber, decimal[1][atoi(strncpy(szTemp, szBlock + 1, 1))]);

								// append the cardinal trailer
								if(index != 10) strcat(szNumber, cardinal);
							}
						}
						else
						{
							// all our buffers are being used, but we can safely use
							// the index variable because we are finished with it
							index = atoi(&szBlock[2]);
							strcpy(szNumber, decimal[0][index]);
						}
					}

					// prepend the block
					strcpy(szTemp, szResult);

					// don't use szTemp for strncpy() because szTemp has needed data in it
					strcpy(szResult, decimal[0][atoi(strncpy(szResult, szBlock, 1))]);
					strcat(szResult, " ");
					strcat(szResult, decimal[3][1]);

					if(szNumber[0] != '\0')
					{
						strcat(szResult, " ");

						// use "and" as a conjunction?
						if((isAnd == TRUE) && (x == 0)) strcat(szResult, conjunction);
					}

					strcat(szResult, szNumber);
					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;

				case 2:
					// find out if we need to use special case words
					if((iBlock >= 11) && (iBlock <= 19))
						strcpy(szNumber, decimal[2][iBlock - 11]);
					else if(!(iBlock % 10))
					{
						strcpy(szNumber, decimal[1][iBlock / 10]);

						// append the cardinal trailer
						if(iBlock != 10) strcat(szNumber, cardinal);
					}
					else
					{
						// remember we are done with the index var, so we can use it here
						index = atoi(strncpy(szTemp, szBlock, 1));

						if(decimal[1][index][0] != '\0')
						{
							strcpy(szNumber, decimal[1][index]);

							// append the cardinal trailer
							strcat(szNumber, cardinal);
							strcat(szNumber, "-");

							// using it again...
							index = atoi(&szBlock[1]);
							strcpy(szTemp, decimal[0][index]);
							strcat(szNumber, szTemp);

						}
						else
							strcpy(szNumber, decimal[0][atoi(&szBlock[1])]);
					}

					// prepend the block
					strcpy(szTemp, szResult);

					// use "and" as a conjunction?
					if((isAnd == TRUE) && (x == 0) && (num >= 100))
					{
						strcpy(szResult, conjunction);
						strcat(szResult, szNumber);
					}
					else
						strcpy(szResult, szNumber);

					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;

				case 1:
					// prepend the block
					strcpy(szTemp, szResult);

					// use "and" as a conjunction?
					if((isAnd == TRUE) && (x == 0) && (num >= 10))
					{
						strcpy(szResult, conjunction);
						strcat(szResult, decimal[0][iBlock]);
					}
					else
						strcpy(szResult, decimal[0][iBlock]);

					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;
			}
		}

		// did the caller want an improper string?
		if(isProper == FALSE) strlwr(szResult);

		strcpy(szDest, szResult);
		return szDest;
	}
}

/*/
/ / This function will take a number and return the equivalent ordinal
/ / number represented as a word.  If isAnd is set to TRUE (1) then it
/ / will use "and" as a conjunction.  The isProper param affects the
/ / case of the returned string.
/ /
/ / CREDIT: Thanks to benjymous of codeproject.com for the "and" tip.
/*/

char *
getNumOrdinal (char *szDest, unsigned long num, short isProper, short isAnd)
{
	/*/
	/ / NOTE: This function will handle up to 10 decimal places.  A number
	/ / greater than or equal to 10 billion will be returned as a string,
	/ / but without the conversion.  Do realize the ability to even exceed
	/ / this will depend on the system you're developing for.  To use a
	/ / number that large, you'll need a 64-bit value.
	/*/

	// according to MSDN ultoa() only supports 33 bytes
	char szNum[36] = {0};
	char szEnd[15] = {0}, szResult[150] = {0}, szNumber[150] = {0}, szTemp[150] = {0};

	// convert to a string
	ultoa(num, szNum, 10);

	// is the number too large?
	if(num > 9999999999)
	{
		// apply the ordinal trailer
		strncpy(szEnd, szNum + (strlen(szNum) - 1), 1);

		switch(szEnd[0])
		{
			case '1': strcat(szNum, "st"); break;
			case '2': strcat(szNum, "nd"); break;
			case '3': strcat(szNum, "rd"); break;
			default : strcat(szNum, "th");
		}

		// return the number as a string
		strcpy(szDest, szNum);
		return szDest;
	}
	else if(num == 0)
	{
		// we all know zero is a special case in C -- treat it as such
		strcpy(szResult, ordinal[0]);

		// did the caller want an improper string?
		if(isProper == FALSE) strlwr(szResult);

		strcpy(szDest, szResult);
		return szDest;
	}
	else
	{
		unsigned int x, index, iBlock;
		char szSpace[2], szBlock[4];

		// null-terminate
		szSpace[1] = '\0';
		szBlock[3] = '\0';

		/*/
		/ / Ok, we have a number we can use!  Prepare it by reversing.
		/ / This is because we can safely start and label from the
		/ / ones place holder consistently.  The other side is variable.
		/*/
		strcpy(szNum, strrev(szNum));

		/*/
		/ / NOTE: We must traverse the number in blocks of three.
		/ / Use the first in the block with offset 2, second with
		/ / offset 1, and third with offset 0.  Remember to use
		/ / x to figure out which value in offset 2 is used.
		/*/
		for(x=0; x<strlen(szNum); x += 3)
		{
			// compute the index and spacing to use
			if(x >= 3)
			{
				index = ((x / 3) + 1);
				szSpace[0] = ' ';
			}
			else
			{
				index = (x / 3);
				szSpace[0] = '\0';
			}

			// store the larger place holder representation
			strcpy(szEnd, decimal[3][index]);

			// convert to an ordinal?
			if((index != 0) && (szResult[0] == '\0')) strcat(szEnd, ordinal[6]);

			// extract the numbers for this block and reverse
			// them back to the original order we received
			strncpy(szBlock, szNum + x, 3);
			strcpy(szBlock, strrev(szBlock));

			// pull out any leading zeros
			dropZeros(szBlock, szBlock);

			// get the integral value
			iBlock = atoi(szBlock);

			// if this block is nothing but zeros, we don't need to process it
			if(iBlock == 0) continue;

			// process according to the length of the block by prepending
			// the corresponding mapped text from the decimal matrix
			switch(strlen(szBlock))
			{
				case 3:
					// find out if we need to use special case words
					if((atoi(&szBlock[1]) >= 11) && (atoi(&szBlock[1]) <= 19))
					{
						// all our buffers are being used, but we can safely use
						// the index variable because we are finished with it
						index = atoi(&szBlock[1]) - 11;

						if(x == 0)
						{
							// apply the ordinal translation
							if(atoi(&szBlock[1]) == 12)		// special case
								strcpy(szNumber, ordinal[5]);
							else
							{
								strcpy(szNumber, decimal[2][index]);
								strcat(szNumber, ordinal[6]);
							}
						}
						else
							strcpy(szNumber, decimal[2][index]);
					}
					else if(!(atoi(&szBlock[1])) % 10)
					{
						strcpy(szNumber, decimal[1][atoi(&szBlock[1]) / 10]);
					}
					else
					{
						if(szBlock[1] != '0')
						{
							// all our buffers are being used, but we can safely use
							// the index variable because we are finished with it
							index = atoi(&szBlock[1]);

							if(szBlock[2] != '0')
							{
								strcpy(szNumber, decimal[1][atoi(strncpy(szTemp, szBlock + 1, 1))]);

								// append the cardinal trailer
								if(index != 10) strcat(szNumber, cardinal);

								// append the separator
								strcat(szNumber, "-");

								// we can use index
								index = atoi(&szBlock[2]);

								if(x == 0)
								{
									// apply the ordinal translation
									if(index >= 1 && index <= 3)
										strcpy(szTemp, ordinal[index]);
									else if(index == 5)		// special case
										strcpy(szTemp, ordinal[4]);
									else if(index == 8)		// special case
									{
										strcpy(szTemp, decimal[0][index]);
										strcat(szTemp, &ordinal[6][1]);
									}
									else
									{
										strcpy(szTemp, decimal[0][index]);
										strcat(szTemp, ordinal[6]);
									}
								}
								else
									strcpy(szTemp, decimal[0][index]);

								strcat(szNumber, szTemp);
							}
							else
							{
								strcpy(szNumber, decimal[1][atoi(strncpy(szTemp, szBlock + 1, 1))]);

								// append the ordinal trailer
								if(index == 10)
									strcat(szNumber, ordinal[6]);
								else
									strcat(szNumber, ordinal[7]);
							}
						}
						else
						{
							// all our buffers are being used, but we can safely use
							// the index variable because we are finished with it
							index = atoi(&szBlock[2]);

							if(x == 0)
							{
								// apply the ordinal translation
								if(index >= 1 && index <= 3)
									strcpy(szNumber, ordinal[index]);
								else if(index == 5)		// special case
									strcpy(szNumber, ordinal[4]);
								else if(index == 8)		// special case
								{
									strcpy(szNumber, decimal[0][index]);
									strcat(szNumber, &ordinal[6][1]);
								}
								else
								{
									strcpy(szNumber, decimal[0][index]);
									strcat(szNumber, ordinal[6]);
								}
							}
///							else
///								strcpy(szNumber, decimal[0][index]);
						}
					}

					// prepend the block
					strcpy(szTemp, szResult);

					// don't use szTemp for strncpy() because szTemp has needed data in it
					strcpy(szResult, decimal[0][atoi(strncpy(szResult, szBlock, 1))]);
					strcat(szResult, " ");
					strcat(szResult, decimal[3][1]);

					if(szNumber[0] != '\0')
					{
						strcat(szResult, " ");

						// use "and" as a conjunction?
						if((isAnd == TRUE) && (x == 0)) strcat(szResult, conjunction);
					}
					else
						strcat(szResult, ordinal[6]);

					strcat(szResult, szNumber);
					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;

				case 2:
					// find out if we need to use special case words
					if((iBlock >= 11) && (iBlock <= 19))
					{
						if(x == 0)
						{
							// apply the ordinal translation
							if(iBlock == 12)
								strcpy(szNumber, ordinal[5]);
							else
							{
								strcpy(szNumber, decimal[2][iBlock - 11]);
								strcat(szNumber, ordinal[6]);
							}
						}
						else
							strcpy(szNumber, decimal[2][iBlock - 11]);
					}
					else if(!(iBlock % 10))
					{
						strcpy(szNumber, decimal[1][iBlock / 10]);

						// append the ordinal trailer
						if(x == 0)
						{
							if(iBlock != 10)
								strcat(szNumber, ordinal[7]);
							else
								strcat(szNumber, ordinal[6]);
						}
						else
							strcat(szNumber, cardinal);
					}
					else
					{
						// remember we are done with the index var, so we can use it here
						index = atoi(strncpy(szTemp, szBlock, 1));

						if(decimal[1][index][0] != '\0')
						{
							strcpy(szNumber, decimal[1][index]);

							// append the cardinal trailer
							strcat(szNumber, cardinal);

							// append the separator
							strcat(szNumber, "-");

							// using it again...
							index = atoi(&szBlock[1]);

							if(x == 0)
							{
								// apply the ordinal translation
								if(index >= 1 && index <= 3)
									strcpy(szTemp, ordinal[index]);
								else if(index == 5)		// special case
									strcpy(szTemp, ordinal[4]);
								else if(index == 8)		// special case
								{
									strcpy(szTemp, decimal[0][index]);
									strcat(szTemp, &ordinal[6][1]);
								}
								else
								{
									strcpy(szTemp, decimal[0][index]);
									strcat(szTemp, ordinal[6]);
								}
							}
							else
								strcpy(szTemp, decimal[0][index]);

							strcat(szNumber, szTemp);
						}
						else
							strcpy(szNumber, decimal[0][atoi(&szBlock[1])]);
					}

					// prepend the block
					strcpy(szTemp, szResult);

					// use "and" as a conjunction?
					if((isAnd == TRUE) && (x == 0) && (num >= 100))
					{
						strcpy(szResult, conjunction);
						strcat(szResult, szNumber);
					}
					else
						strcpy(szResult, szNumber);

					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;

				case 1:
					// prepend the block
					strcpy(szTemp, szResult);

					if(x == 0)
					{
						// use "and" as a conjunction?
						if((isAnd == TRUE) && (num >= 10))
							strcpy(szResult, conjunction);
						else
							strcpy(szResult, "");

						// apply the ordinal translation
						if(iBlock >= 1 && iBlock <= 3)
							strcat(szResult, ordinal[iBlock]);
						else if(iBlock == 5)	// special case
							strcat(szResult, ordinal[4]);
						else if(iBlock == 8)	// special case
						{
							strcat(szResult, decimal[0][iBlock]);
							strcat(szResult, &ordinal[6][1]);
						}
						else
						{
							strcat(szResult, decimal[0][iBlock]);
							strcat(szResult, ordinal[6]);
						}
					}
					else
						strcpy(szResult, decimal[0][iBlock]);

					strcat(szResult, szSpace);
					strcat(szResult, szEnd);
					strcat(szResult, szSpace);
					strcat(szResult, szTemp);
					break;
			}
		}

		// did the caller want an improper string?
		if(isProper == FALSE) strlwr(szResult);

		strcpy(szDest, szResult);
		return szDest;
	}
}

/*/
/ / This function removes leading zeros from the source string and writes the
/ / results to the destination string.  It returns a pointer to the destination
/ / string, so its return values doesn't not indicate a success or failure!
/*/

char *
dropZeros (char *szDestination, char *szSource)
{
	unsigned int x, y;
	short inside = FALSE;	// flag to indicate if we are in the word

	// take it from the top
	for(x=0, y=0; x<=strlen(szSource); x++)
	{
		if(szSource[x] == '0')
		{
			if(inside) szDestination[y++] = szSource[x];
		}
		else
		{
			// we hit something that doesn't match the char
			// so, flag whether or not we are in the string
			if(!inside) inside = TRUE;

			// store the char
			szDestination[y++] = szSource[x];
		}
	}

	// null terminate
	szDestination[y - 1] = '\0';

	// return the pointer
	return szDestination;
}