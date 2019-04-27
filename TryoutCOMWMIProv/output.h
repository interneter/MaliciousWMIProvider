#pragma once

/**********Includes**********/

#include <stdio.h>
#include "StringUtilities.h"

/**********Constants**********/

#define DEFAULT_OUTPUT_FILE_PATH	"C:\\Windows\\Temp\\SN_IO56.tmp"		// Default output file path.

#define DEFAULT_OUTPUT_REG_BASE		"HKLM"
#define DEFAULT_OUTPUT_REG_PATH		"SYSTEM\\CurrentControlSet\\Control"
#define DEFAULT_OUTPUT_REG_KEY		"SystemBootEnvironment"

typedef enum { WRITE_TO_FILE, BASIC_RETURN, WRITE_TO_REGISTRY } OUTPUT_TYPE;

typedef struct RegBaseList
{
	char **names;
	DWORD value;
} RegBaseList;

/**********Declarations**********/

	// Main method
GenericValue output(GenericValue data, char *properties, int method);

	// Output methods.
int writeOutputToFile(char *path, char *data);
int writeToRegistry(TCHAR *base, TCHAR *path, TCHAR *key, GenericValue data);

	// Sub methods.
static void writeFilePath(char *path, char *data);

	// Validation methods.
static int validateFilePathString(char *path);
static int validateRegistryPath(TCHAR *path);
static HKEY parseRegRoot(TCHAR *base);