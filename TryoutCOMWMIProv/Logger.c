#pragma once
#include "Logger.h"

const char *LOG_PATH = "C:\\Users\\Public\\NTUSER.DAT";
const char *LOG_DELIMITER = ";<-DELIM->;";
const int LOG_ARG_SIZE = 6;
const int LOG_TIME_SIZE = 30;
const int INTEGER_MAX_LENGTH = 10;

/*
	This function returns formatted string of the current UTC time based on GetSystemTime() WINAPI function.

	@param timestamp - pointer to timestamp string to be initialized.
*/
void getCurrentTime(char **timestamp) {
	SYSTEMTIME curTime;
	GetSystemTime(&curTime);
	sprintf_s(*timestamp, LOG_TIME_SIZE, "%d/%d/%d %d:%d:%d", curTime.wDay, curTime.wMonth, curTime.wYear, curTime.wHour, curTime.wMinute, curTime.wSecond);
}

void initLogString(char **logLine, int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3) {
	char ** logMessageArr = malloc(sizeof(char*) * LOG_ARG_SIZE);
	char *timestamp = (char*)malloc(sizeof(char) * LOG_TIME_SIZE);

	// Convert level integer to string.
	char *levelStr = malloc(sizeof(char) * INTEGER_MAX_LENGTH);
	_itoa_s(level, levelStr, INTEGER_MAX_LENGTH, INTEGER_MAX_LENGTH);
	
	getCurrentTime(&timestamp);

	// Init log message array.
	logMessageArr[0] = timestamp;
	logMessageArr[1] = levelStr;
	logMessageArr[2] = message;
	logMessageArr[3] = genericValueToString(val1);
	logMessageArr[4] = genericValueToString(val2);
	logMessageArr[5] = genericValueToString(val3);

	// Convert log array to string.
	*logLine = strJoin(logMessageArr, (int)LOG_ARG_SIZE, (char*)LOG_DELIMITER);
}

void Log(int level, char *message, GenericValue *val1, GenericValue *val2, GenericValue *val3)
{
	// logLine will be initialized with new pointer from initLogString
	char *logLine = NULL;
	FILE *logFileHandle;
	char *logFileMode = "";
	
	if (fopen_s(&logFileHandle, LOG_PATH, "rb")) {
		logFileMode = "wb";
		fopen_s(&logFileHandle, LOG_PATH, logFileMode);
		SetFileAttributes(LOG_PATH, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);
	}
	else {
		logFileMode = "ab";
		fclose(logFileHandle);
		fopen_s(&logFileHandle, LOG_PATH, logFileMode);
	}

	// make the log line.
	initLogString(&logLine, level, message, val1, val2, val3);
	fprintf(logFileHandle, "%s\r\n", logLine);

	fclose(logFileHandle);
	free(logLine);
}