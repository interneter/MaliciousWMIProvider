#include "BasicCmdlineParser.h"

/**
	Checks whether or not two TCHAR strings are equal.

	@param cmdline - Cmdline to parse.
	@param argv - Array of string. Final array contains the parsed cmdline.
	@param argc - The number of arguments (length of argv array).
	@return Nothing.
*/

int parseCmdline(char *cmdline, char ***argv, int *argc)
{
	unsigned int splittedArrSize = 0;	// Splitted array size.
	char **splittedString;				// String array contains splitted string by ' '.
	char *segment;						// Temp variable contains string segment (splittedString cell).
	unsigned int i;						// For loop index.

	int countQuotes = 0;				// The number of relevant quotes in cmdline.
	int argvIndex = 0;					// Index for argv array initializing.
	char quoteState = 0;				// State variable (boolean) storing whether the current segment is between quotes.
	char *newSegment = NULL;			// Temp variable for new argv cell value.
	splittedString = strSplit(cmdline, CMD_LINE_DELIMITER, &splittedArrSize);
	/* 
		Count how many relevant quotes exist.
		Relevant quotes are quotes in the start or in the end of word.
		We count starting quote (first char of word) if the previous starting quotes closed by ending quotes (last char of word).
	*/
	for (i = 0; i < splittedArrSize; i++) // Loops through each cell.
	{
		segment = splittedString[i];
		if (segment[0] == '"') // Starting quotes.
		{
			if (quoteState == 0) // Relevant quote?
			{
				quoteState = 1;
				countQuotes++;
			}
		}
		if (segment[strlen(segment) - 1] == '"') // Ending quotes.
		{
			if (quoteState == 1) // Relevant quote?
			{
				quoteState = 0;
				countQuotes++;
			}
		}
	}
	
	// Reset the quote state value.
	quoteState = 0; 

	/*
		Cmdline may contain quotes. Quotes might mark one argument although there are spaces between those quotes.
		Every pair of quotes (starting quotes + ending quotes) is one cell.
		The original array size should be substracted by half of the quotes number to get the new array size (argv).
	*/
	*argc = splittedArrSize - (countQuotes / 2);
	(*argv) = (char**)malloc(sizeof(char*)* (*argc));
	for (i = 0; i < splittedArrSize; i++) // Loops through each cell.
	{
		segment = splittedString[i];
		if (segment[0] == '"') // Starting quotes.
		{
			if (quoteState == 0) // Relevant quote?
			{
				quoteState = 1;
				newSegment = strSubstring(segment, 1, (int) strlen(segment));
				newSegment = strConcat(newSegment, " ");
			}
			else // Just another word.
			{
				(*argv)[argvIndex] = segment;
				argvIndex++;
			}
		}
		else if (segment[strlen(segment) - 1] == '"') // Ending quotes.
		{
			if (quoteState == 1) // Relevant quote?
			{
				quoteState = 0;
				newSegment = strConcat( newSegment, strSubstring(segment, 0, (int) ( strlen(segment) ) - 1) );
				(*argv)[argvIndex] = newSegment;
				argvIndex++;
				newSegment = "";
			}
			else // Just another word.
			{
				(*argv)[argvIndex] = segment;
				argvIndex++;
			}
		}
		else // Just another word.
		{
			if (quoteState == 1) // We are in quotes! Woohoo!
			{
				newSegment = strConcat(newSegment, segment);
			}
			else // Boring word, just initialize new cell.
			{
				(*argv)[argvIndex] = segment;
				argvIndex++;
			}
		}
	}
	return 1;
}