#include "FunctionMapper.h"

/**********Globals**********/

static function_map wmi_mapper[] = {
	{ "query", wmiQuery },
	{ EXIT_FUNCTION_NAME, exitMapper },
};  // Maps ipconfig utility functions.

static utility_map utility_mapper[] = {
	{ "wmi", wmi_mapper },
}; // Maps utility to the utility functions.

/**********Methods**********/

/**
	Calls a specific function in utility according to utility to functions mapping.

	@param utility - Utility to cal function from.
	@param name - Function name to call.
	@param args - Arguments string to pass to the callee function.
	@return GenericValue - The function returns the called function return value. If the function recieved as argument doesn't exist, the function will return -1.
*/
GenericValue callFunction(char *utility, char *name, char **args, int argsCount)
{
	int i, j;
	/*
		This loop iterates the exist utilities.
		If the utility given as argument exists, the inner loop will call the specific function (recieved as argument).
	*/
	for (i = 0; i < sizeof(utility_mapper) / sizeof(utility_mapper[i]); i++)
	{
		if ( !strcmp(utility, utility_mapper[i].utility_name) )
		{
			j = 0;
			while (strcmp(utility_mapper[i].mapper[j].name, EXIT_FUNCTION_NAME))
			{
				if (!strcmp(utility_mapper[i].mapper[j].name, name) && utility_mapper[i].mapper[j].func)
				{
					return utility_mapper[i].mapper[j].func(args, argsCount);
				}
				j++;
			}
		}
	}
	return executeCommand(strConcat(name, strJoin(args, argsCount, " ")));
}


/**
	Exit function that does nothing. It marks the end of utility functions mapping.
	This function is kind of template for the callee functions.

	@param args - Arguments string to pass to the callee function.
	@param argsCount - Te number of arguments sent to the function.
	@return GenericValue - It returns NULL pointer, because this function should do nothing.
*/
GenericValue exitMapper(char **args, int argsCount)
{
	GenericValue res;
	res.type = GENERIC_POINTER;
	res.value.pointer = NULL;
	UNREFERENCED_PARAMETER(args);
	UNREFERENCED_PARAMETER(argsCount);
	return res;
}