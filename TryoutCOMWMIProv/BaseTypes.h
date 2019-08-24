#pragma once
#include <windows.h>

// Enum for GenericValue struct. This enum indicates the GenericValue struct value type.
typedef enum { GENERIC_INTEGER, GENERIC_STRING, GENERIC_REAL, GENERIC_POINTER, GENERIC_TSTRING, GENERIC_WSTRING } GenericType;

// Enum for error values.
typedef enum { NORMAL_RETURN_VALUE, INVALID_REG_BASE, INVALID_REGISTRY_PATH, UNKNOWN_GENERIC_STRING_TYPE } OUTPUT_ERROR;

/*
	This struct implement generic value.
	It uses GenericType enum as indication for the struct type.
	The second member is the data itself implemented by union.
*/
typedef struct
{
	GenericType type;
	union {
		int integer;
		char *string;
		float real;
		void *pointer;
		TCHAR *tstring;
		WCHAR *wstring;
	} value;
} GenericValue;