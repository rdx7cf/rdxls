#include <stdio.h>
#include <ctype.h>

#ifdef DEBUG
#include "debugger.h"
#endif

#include "parse_files.h"

void processToken(const char token[]);

// An orbitrary comment.
// A second orbitrary comment.

int main(int argc, char *argv[])
{
	if (argc == 1)
		processToken(".");
	else
	{
		while(--argc > 0)
		{
			processToken((++argv)[0]);
		}
	}

	return 0;
}

void processToken(const char token[])
{
	if (*token == '-')
	{
		char flag;
		while(isalnum(flag = *++token))
		{
			switch(flag)
			{
				case 'a':
#ifdef DEBUG
					writeDebug("'a' parameter successfully passed.");
#endif
					break;
				case 'b':
#ifdef DEBUG
					writeDebug("'b' parameter successfully passed.");
#endif
					break;
				case 'c':
#ifdef DEBUG
					writeDebug("'c' parameter successfully passed.");
#endif
					break;

				case '-':
					break;
				default:
					fprintf(stderr, "rdxLS: WARN: Unknown flag encountered: '%c'.\n", flag);
					break;

			}
		}
	}
	else
	{
		fprintf(stdout, "%s\n", token);
		parseFiles(token, NULL);


	}
}
