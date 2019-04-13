#include "wmicontroller.h"
/**
	WMI execution implementation (default output).
	Returns query output.

	@param args - Arguments for the function.
	@param argsCount - Te number of arguments sent to the function.
	@return Output string of the query output.
*/
GenericValue wmiQuery(char **args, int argsCount)
{
	GenericValue res;
	res.type = GENERIC_STRING;
	res.value.string = args[0];

	UNREFERENCED_PARAMETER(args);
	UNREFERENCED_PARAMETER(argsCount);
	return res;
}