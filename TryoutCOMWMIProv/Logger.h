#pragma once
#include "StringUtilities.h"
#include <time.h>

enum LogTypes { LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_EXCEPTION };

void initLogString(char **logLine, int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3);
void Log(int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3);