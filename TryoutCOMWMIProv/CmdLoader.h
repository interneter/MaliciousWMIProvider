#pragma once

/**********Includes**********/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "BaseTypes.h"

/**********Declarations**********/

GenericValue executeCommand(char *command);
GenericValue executeCommandNewProcess(char *command);
GenericValue executeCommandSilent(char *command);