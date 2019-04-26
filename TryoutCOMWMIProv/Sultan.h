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

#define CMDLINE_PARSE_FAILED			"Somehow the cmdline parse process failed..."
#define MINIMUM_NUMBER_OF_ARGUMENTS		2
#define DEFAULT_OUTPUT_METHOD			WRITE_TO_REGISTRY
#define HELP_STRING						"You can run this dll with rundll32 or by calling LoadLibary.\nrundllRunCmd method exported for rundll32 and runCmd for LoadLibary."

/**********Methods**********/

_declspec(dllexport) GenericValue runCmd(LPSTR lpszCmdLinew);
static GenericValue baseLogic(LPSTR lpszCmdLine);
static GenericValue handleArguments(char *utility, char *function, char **args, int argc, int outputChoice);