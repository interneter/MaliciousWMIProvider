#include "StringUtilities.h"

/**
	Calculates TCHAR string length.

	@param str - TCHAR string.
	@return DWORD - The length of the string.
*/
DWORD tcharLength(TCHAR *str)
{
	return (DWORD) _tcslen(str);
}

/**
	Checks whether or not two TCHAR strings are equal.

	@param first - TCHAR string.
	@param second - TCHAR string.
	@return BOOL - True if the strings are equal. Else, false.
*/
BOOL tcharEqual(TCHAR *first, TCHAR *second)
{
	DWORD first_len = tcharLength(first);
	DWORD second_len = tcharLength(second);
	DWORD max_length = max(first_len, second_len);

	return _tcsncmp(first, second, max_length) == 0;
}

TCHAR *tcharLower(TCHAR *str)
{
	int str_len = tcharLength(str);
	TCHAR *new_str = (TCHAR*)malloc(sizeof(TCHAR)* str_len);
	int i;

	for (i = 0; i < str_len; i++)
	{
		new_str[i] = str[i] + 32;
	}
	return new_str;
}

/**
	Converts ascii string to unicode string.

	@param str - Ascii string to convert.
	@return TCHAR - Converted unicode string.
*/
WCHAR *asciiToUnicode(char *str)
{
	int len = (int) strlen(str);
	WCHAR *unistring = (WCHAR*)malloc( sizeof(WCHAR)* (len + 1) );
	MultiByteToWideChar(CP_OEMCP, 0, str, -1, unistring, len + 1);
	return unistring;
}

/**
	Counts occurrences of char in string. 

	@param str - String to count chars from.
	@param ch - Character to count
	@return int - Occurrences counter.
*/
int countChar(char *str, char ch)
{
	int countDelim = 0;
	unsigned int i = 0;

	for (i = 0; i < strlen(str); i++)
		if (str[i] == ch)
			countDelim++;

	return countDelim;
}

/**
	Returns the index of the first occurrence of character from specific index.

	@param str - String to search in.
	@param ch - Character to search.
	@param from - starting index.
	@return int - Index of the character. If the function failed to find, it returns -1.
*/
int strIndexOf(char *str, char chSearch, int from)
{
	int len = (int) strlen(str);
	int i;

	if (from > len) // Input check.
		return -1;

	for (i = from; i < len; i++)
		if (str[i] == chSearch)
			return i;

	return -1;
}

/**
	Returns slice of string (sub-string) according to given indexes.

	@param str - String to slice.
	@param from - First string index.
	@param to - Last string index.
	@return char* - The result substring.
*/

char *strSubstring(char *str, int from, int to)
{
	int input_len = (int) strlen(str);
	int len = to - from + 1;
	char *dest = (char*)malloc( sizeof(char) * len );

	// Input check.
	if (from + len > input_len + 1 || from > to || from > input_len || to > input_len)
		return NULL;

	// Copy the relevant memory section fromt he original string to the new string's memory chunk.
	strncpy_s(dest, len, str + from, to - from);
	dest[len - 1] = '\0';

	return dest;
}

/**
	Splits string according to delimiter.

	@param str - String to split.
	@param delim - Delimiter to split with.
	@param outLen - New array length.
	@return char** - Array of string (Parts of the original string).
*/

char** strSplit(char* str, const char delim, unsigned int *outLen)
{
	unsigned int countDelim = countChar(str, delim);							// Delimiter counter.
	char **finalArray = (char**) malloc( sizeof(char*) * (countDelim + 1) );	// Final array containg the splitted string.
	int lastDelimPos = 0;														// Variable holding last delimiter position.
	int nextDelimPos = 0;														// Next delim position starting from lastDelimPos.
	unsigned int i;																// For loop counter.
	*outLen = countDelim + 1;													// Output array length initialize.
																				// Last cell in the array value is the end of the string.
	for (i = 0; i < *outLen; i++)
	{
		nextDelimPos = strIndexOf(str, delim, lastDelimPos);					// Next delimiter.
		if (nextDelimPos == -1)													// Not found? (end of string, countDelim = 1).
			nextDelimPos = (int) strlen(str);											// Incase delimiter not found at all (outLen = 1) the cell will contain the whole string/last string slice.

		finalArray[i] = strSubstring(str, lastDelimPos, nextDelimPos);			// Slice the string.
		lastDelimPos = nextDelimPos + 1;										// Start the next scan from the character after the last delimiter.
	}
	return finalArray;
}

/**
	Concatenates two strings.

	@param base - Base string to concatenate-to.
	@param strCon - String to concatenate to the end of base string.
	@return char* - Result concatenated string.
*/

char *strConcat(char *base, char *strCon)
{
	unsigned int baseLen = (unsigned int) strlen(base);
	unsigned int conLen = (unsigned int) strlen(strCon);
	unsigned int newLen = baseLen + conLen;

	// Allocate enough memory.
	char *newStr = (char*) malloc( sizeof(char) * (newLen + 1) );

	// Copy string to the new memory chunk.
	memcpy_s(newStr, baseLen, base, baseLen);
	memcpy_s(newStr + baseLen, conLen, strCon, conLen);

	// Mark end of string with null terminator.
	newStr[newLen] = '\0';

	return newStr;
}

/**
Joins an array string into single string containing the strings concated with delimiter.

@param strArr - Array to join.
@param len - Array length.
@param delim - String to seperate each cell.
@return char* - Result joined array.
*/

char *strJoin(char **strArr, int len, char *delim)
{
	char *base = "";
	int i;

	if (len > 0)
		strConcat(base, strArr[0]);
	for (i = 1; i < len; i++)
	{
		strConcat(base, strConcat(delim, strArr[i]));
	}

	return base;
}

/**
	Converts GenericValue struct to string presentation.

	@param genericVal - GenericValue struct to convert.
	@return char* - Result string.
*/

char *genericValueToString(GenericValue genericVal)
{
	size_t len = 0;
	char *str = NULL;
	
	switch (genericVal.type)
	{
		case GENERIC_INTEGER:
			sprintf_s(str, 50, "%d", genericVal.value.integer);
			break;
		case GENERIC_STRING:
			len = strlen(genericVal.value.string);
			if (len == 0)
			{
				str = "";
			}
			else
			{
				str = malloc((sizeof(char) * len) + 1);
				memcpy_s(str, len + 1, genericVal.value.string, len + 1);
			}
			break;
		case GENERIC_REAL:
			sprintf_s(str, 50, "%f", genericVal.value.real);
			break;
		case GENERIC_POINTER:
			sprintf_s(str, 50, "Pointer: %p", genericVal.value.pointer);
			break;
		case GENERIC_TSTRING:
			wcstombs_s(&len, str, (size_t)(wcslen( (wchar_t*) genericVal.value.tstring) * 2 + 2), (wchar_t*)genericVal.value.tstring, (size_t)(wcslen((wchar_t*)genericVal.value.tstring) * 2 + 2));
			break;
		case GENERIC_WSTRING:
			wcstombs_s(&len, str, (size_t)(wcslen(genericVal.value.wstring) * 2 + 2), genericVal.value.wstring, (size_t)(wcslen(genericVal.value.wstring) * 2 + 2));
			break;
		default:
			return NULL;
			break;
	}
	return str;
}


/**
	Converts string to GenericValue struct.

	@param str - String to convert.
	@return GenericValue - Result GenericValue struct.
*/

GenericValue stringToGenericValue(char *str)
{
	GenericValue out;
	out.type = GENERIC_STRING;
	out.value.string = str;

	return out;
}

BYTE *stringToByteArray(char *str)
{
	int i = 0, len = (int) strlen(str);
	BYTE *byteArr = malloc((sizeof(BYTE) * len) + 1);

	for (i = 0; i < len; i++)
	{
		byteArr[i] = (BYTE)str[i];
	}
	byteArr[len] = (BYTE)0;
	return byteArr;
}