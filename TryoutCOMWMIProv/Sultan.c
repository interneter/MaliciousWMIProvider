#include "Sultan.h"

/**
	Runs cmd command based on Sultan dll capabilities.

	@param lpszCmdLine - Cmdline to execute.
	@return GenericValue - Struct contains the output.
*/
GenericValue runCmd(LPSTR lpszCmdLine)
{
	return baseLogic(lpszCmdLine);
}

/**
	Base logic function, responsible for the basic logic of function call.

	@param lpszCmdLine - Cmdline to execute.
	@return GenericValue - Struct contains the output.
*/

static GenericValue baseLogic(LPSTR lpszCmdLine)
{
	char **argv = NULL;
	int argc;
	if (parseCmdline(lpszCmdLine, &argv, &argc))
	{
		if (argc > MINIMUM_NUMBER_OF_ARGUMENTS)
		{
			return handleArguments(argv[1], "", ( argv + ( sizeof(char*) * 2) ), argc - 2, atoi(argv[0]));
		}
		else if (argc == MINIMUM_NUMBER_OF_ARGUMENTS)
		{
			return handleArguments( argv[1], "", NULL, 0, atoi(argv[0]) );
		}
		else if (argc == 0)
		{
			return output(stringToGenericValue(HELP_STRING), "", atoi(argv[0]));
		}
		else
		{
			return output(stringToGenericValue(HELP_STRING), "", DEFAULT_OUTPUT_METHOD);
		}
	}
	else
	{
		// Shit happens. Parsecmd somehow failed...
		return output(stringToGenericValue(CMDLINE_PARSE_FAILED), "", WRITE_TO_FILE);
	}
}


/**
	This function responsible for the function calling process.

	@param utility - Utility to call.
	@param function - Function to call. By default it will be empty string.
	@param args - Pointer for string array containing parsed cmdline.
	@param argc - The number of argumetns for the called function.
	@param outputChoice - Which output method the user chose.
	@return GenericValue - Struct contains the output.
*/

static GenericValue handleArguments(char *utility, char *function, char **args, int argc, int outputChoice)
{
	GenericValue function_return_value;
	GenericValue output_return_value;

	function_return_value = callFunction(utility, function, args, argc);
	output_return_value = output(function_return_value, "", outputChoice);

	return output_return_value;
}