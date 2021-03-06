#pragma once

/**********Includes**********/

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <assert.h>
#include "BaseTypes.h"
#include <stdio.h>
#include <locale.h>
#include <ctype.h>

/**********Declarations**********/

TCHAR *tcharLower(TCHAR *str);
DWORD tcharLength(TCHAR *str);
BOOL tcharEqual(TCHAR *first, TCHAR *second);
WCHAR *asciiToUnicode(char *str);
char** strSplit(char* a_str, const char a_delim, unsigned int *outLen);
int countChar(char *str, char ch);
char *strSubstring(char *str, int from, int to);
int strIndexOf(char *str, char chSerach, int from);
char *strConcat(char *base, char *str);
char *strJoin(char **strArr, int len, char *delim);
char *genericValueToString(GenericValue *a);
GenericValue stringToGenericValue(char *str);
void stringToGenericValueRef(char *str, GenericValue *genVal);
BYTE *stringToByteArray(char *str);