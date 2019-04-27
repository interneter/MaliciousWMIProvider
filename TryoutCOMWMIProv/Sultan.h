#pragma once

/**********Includes**********/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "StringUtilities.h"
#include "FunctionMapper.h"
#include "BasicCmdlineParser.h"
#include "output.h"

/**********Constants**********/

#define CMDLINE_PARSE_FAILED			"Somehow the command line parse process failed..."
#define MINIMUM_NUMBER_OF_ARGUMENTS		2
#define DEFAULT_OUTPUT_METHOD			WRITE_TO_REGISTRY
#define HELP_STRING						"Follow the instructions in order to execute a proper command."

/**********Declarations**********/

_declspec(dllexport) GenericValue runCmd(LPSTR lpszCmdLinew);
static GenericValue baseLogic(LPSTR lpszCmdLine);
static GenericValue handleArguments(char *utility, char *function, char **args, int argc, int outputChoice);