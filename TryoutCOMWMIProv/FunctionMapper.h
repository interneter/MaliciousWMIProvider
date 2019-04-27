#pragma once

/**********Includes**********/

#include <stdio.h>
#include "wmicontroller.h"
#include "BaseTypes.h"
#include "CmdLoader.h"
#include "StringUtilities.h"

/**********Constants**********/

#define EXIT_FUNCTION_NAME "exit"

/**********Structs**********/

typedef struct function_map {
	const char *name;
	GenericValue(*func)(char**, int);
} function_map; // This struct links string to function.

typedef struct utility_map {
	const char *utility_name;
	function_map *mapper;
} utility_map; // This struct links utility to function mapper.

/**********Declarations**********/

GenericValue callFunction(char *utility, char *name, char **args, int argsCount);
GenericValue exitMapper(char **args, int argsCount);