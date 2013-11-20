//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by NUMAFX.RC
//

// Next default values for new objects
// 

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NEXT_RESOURCE_VALUE	1000
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		1000
#define _APS_NEXT_COMMAND_VALUE		32771
#endif
#endif

#ifdef NUMANALYSE_EXPORTS
#define NUMANALYSE_API __declspec(dllexport)
#else
#define NUMANALYSE_API __declspec(dllimport)
#endif

static char* unit_arr[] =	{	"zero",
								"one",
								"two",
								"three",
								"four",
								"five",
								"six",
								"seven",
								"eight",
								"nine",
								"ten",
								"fiveN",
								"fiveL",
								"zeroL",
								"oneS",
								"fourT"		};

static char* sup_arr[] =	{	"dosen",
								"hundred",
								"thousand",
								"million",
								"billion",
								"tera"		};

CString FirstTwo(int tw);

CString FirstThree(int th);

CString NumComb(double x, char *s);

CString Fractal(CString tw);

extern "C" NUMANALYSE_API char *VS_MainNum(char *numstr);
extern "C" NUMANALYSE_API char *VS_NonCount(char *numstr);
extern "C" NUMANALYSE_API char *VS_DateTimeV(char *numstr="0000 00 00 00:00:00");
extern "C" NUMANALYSE_API char *VS_OrdinalE(char *numstr);
extern "C" NUMANALYSE_API char *VS_CardinalE(char *numstr);
extern "C" NUMANALYSE_API char *VS_DateTimeE(char *numstr="0000 00 00 00:00:00");

