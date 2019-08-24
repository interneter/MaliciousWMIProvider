#pragma once
#include "Logger.h"

GenericValue firstLogParam;
GenericValue secondLogParam;
GenericValue thirdLogParam;

void initLog() {
	initLogParams();
}

void initLogParams() {
	stringToGenericValueRef("", &firstLogParam);
	stringToGenericValueRef("", &secondLogParam);
	stringToGenericValueRef("", &thirdLogParam);
}
/*
	This function returns formatted string of the current UTC time based on GetSystemTime() WINAPI function.

	@param timestamp - pointer to timestamp string to be initialized.
*/
void getCurrentTime(char **timestamp) {
	SYSTEMTIME curTime;
	GetSystemTime(&curTime);
	sprintf_s(*timestamp, LOG_TIME_SIZE, "%d/%d/%d %d:%d:%d", curTime.wDay, curTime.wMonth, curTime.wYear, curTime.wHour, curTime.wMinute, curTime.wSecond);
}

void setParamInt(GenericValue* param, int a) {
	param->type = GENERIC_INTEGER;
	param->value.integer = a;
}

void setParamString(GenericValue* param, char *a) {
	stringToGenericValueRef(a, param);
}

/*
	This function creates new log line string.

	@param logLine - Pointer to string to be initialized with the final logline.
	@param level - Marks the log type using enum declared in header file.
	@param message - Free-text for the logline.
	@param val1 - Pointer to GenericValue struct used as parameter for the logline.
	@param val2 - Pointer to GenericValue struct used as parameter for the logline.
	@param val3 - Pointer to GenericValue struct used as parameter for the logline.
*/
void initLogString(char **logLine, int level, char *message) {
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
	logMessageArr[3] = genericValueToString(&firstLogParam);
	logMessageArr[4] = genericValueToString(&secondLogParam);
	logMessageArr[5] = genericValueToString(&thirdLogParam);

	// Convert log array to string.
	*logLine = strJoin(logMessageArr, (int) LOG_ARG_SIZE, (char*) LOG_DELIMITER);
}

/*
	This function writes new low logline to log file.

	@param level - Marks the log type using enum declared in header file.
	@param message - Free-text for the logline.
	@param val1 - Pointer to GenericValue struct used as parameter for the logline.
	@param val2 - Pointer to GenericValue struct used as parameter for the logline.
	@param val3 - Pointer to GenericValue struct used as parameter for the logline.
*/
void Log(int level, char *message)
{
	// logLine will be initialized with new pointer from initLogString
	char *logLine = NULL;
	FILE *logFileHandle;
	
	// Handles log file creation.
	if (fopen_s(&logFileHandle, LOG_PATH, "rb")) {
		fopen_s(&logFileHandle, LOG_PATH, "wb");
		SetFileAttributes(LOG_PATH, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);
	}
	else {
		fclose(logFileHandle);
		fopen_s(&logFileHandle, LOG_PATH, "ab");
	}

	// Generate logline.
	initLogString(&logLine, level, message);
	fprintf(logFileHandle, "%s\r\n", logLine);
	
	// Cleanup

	initLogParams();
	fclose(logFileHandle);
	free(logLine);
}