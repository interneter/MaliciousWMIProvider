#pragma once

/**********Includes**********/

#include "StringUtilities.h"

/**********Constants**********/

#define CMD_LINE_DELIMITER ' '		// Seperator between words.

/**********Methods**********/

int parseCmdline(char *cmdline, char ***argv, int *argc);