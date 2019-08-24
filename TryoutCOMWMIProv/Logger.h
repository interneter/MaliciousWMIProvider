#pragma once

/**********Includes**********/
#include "StringUtilities.h"
#include <time.h>
#include "Globals.h"

/**********Constants**********/

#define LOG_PATH "C:\\Users\\Public\\NTUSER.DAT"
#define LOG_DELIMITER ";<-DELIM->;"
#define LOG_ARG_SIZE 6
#define LOG_TIME_SIZE 30
#define INTEGER_MAX_LENGTH 11

/**********Structs**********/

enum LogTypes { LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_EXCEPTION };

/**********Declarations**********/

void initLog();
void initLogParams();
void setParamInt(GenericValue* param, int a);
void setParamString(GenericValue* param, char *a);
void initLogString(char **logLine, int level, char *message);
void Log(int level, char *message);