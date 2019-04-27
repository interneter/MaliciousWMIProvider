#pragma once

/**********Includes**********/
#include "StringUtilities.h"
#include <time.h>

/**********Constants**********/

#define LOG_PATH "C:\\Users\\Public\\NTUSER.DAT"
#define LOG_DELIMITER ";<-DELIM->;"
#define LOG_ARG_SIZE 6
#define LOG_TIME_SIZE 30
#define INTEGER_MAX_LENGTH 10

/**********Structs**********/

enum LogTypes { LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_EXCEPTION };

/**********Declarations**********/

void initLogString(char **logLine, int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3);
void Log(int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3);