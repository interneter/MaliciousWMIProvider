#include "cmdloader.h"

GenericValue executeCommand(char *command)
{
	return executeCommandNewProcess(command);
}

GenericValue executeCommandNewProcess(char *command)
{
	GenericValue result; // Variable storing the return value.

	// Default return value.
	result.type = GENERIC_INTEGER;
	result.value.integer = -1;

	UNREFERENCED_PARAMETER(command);

	return result;
}

GenericValue executeCommandSilent(char *command)
{
	GenericValue result; // Variable storing the return value.

	// Default return value.
	result.type = GENERIC_INTEGER;
	result.value.integer = -1;

	UNREFERENCED_PARAMETER(command);

	return result;
}