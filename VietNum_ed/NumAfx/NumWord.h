#if !defined (NUMWORD_H_)
#define NUMWORD_H_

// mimic a boolean true
#ifndef TRUE
#define TRUE	1
#endif

// mimic a boolean false
#ifndef FALSE
#define FALSE	0
#endif

// function prototypes
char *getNumCardinal (char *szDest, unsigned long num, short isProper, short isAnd);
char *getNumOrdinal  (char *szDest, unsigned long num, short isProper, short isAnd);
char *dropZeros      (char *szDestination, char *szSource);

#endif  /*/ NUMWORD_H_ /*/
