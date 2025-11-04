#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugger.h"

static struct 
{
	char *filename;
	FILE *pfile;

} debugger = {.filename = "debug.log"};

static void tryOpen()
{
	if(!debugger.pfile)
	{
		debugger.pfile = fopen(debugger.filename, "a");

		if(!debugger.pfile)
		{
			fprintf(stderr,"rdxLS: ERR: Couldn't open the file '%s'.\n", debugger.filename);
			exit(EXIT_FAILURE);
		}
	}
}
void writeDebug(const char message[])
{
	tryOpen();

	fprintf(debugger.pfile, "rdxLS: DEBUG: %s\n", message); 
}
