#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "parse_files.h"
#include "node.h"
#include "file_entry.h"

#define	NAME_MAXLEN	1024

void parseFiles(const char *path, Node* root)
{
	struct stat stbuf;
	void collectEntries(const char *, Node *);

	if (stat(path, &stbuf) == -1)
	{
		fprintf(stderr, "rdxls: An error occured while retrieving the file information: '%s'.\n", path);
	}
	else
	{
		FileEntry* fe;
		
		if ((fe = fe_create(&stbuf, path)) == NULL)
		{
			fprintf(stderr, "rdxls: An error occured while create a file entry: '%s'.\n", path);
			return;
		}

		n_add(root, (void *) fe);

		if (S_ISDIR(stbuf.st_mode))
		{
			collectEntries(path, root);
		}
		
		fe_print(fe, NULL);
	}
}

void collectEntries(const char *parent, Node *root)
{
	DIR *pdir;
	struct dirent *child;
	char nambuf[NAME_MAXLEN];

	if ((pdir = opendir(parent)) == NULL)
	{
		fprintf(stderr, "rdxls: An error occured while opening the file '%s'.\n", parent);
	}
	else
	{
		while(child = readdir(pdir))
		{
			if(strcmp(".", child->d_name) == 0 || strcmp("..", child->d_name) == 0)
				continue;
			
			if(strlen(parent) + strlen(child->d_name) + 2 > NAME_MAXLEN)
			{
				fprintf(stderr, "rdxls: The combined length of the parent's and child's names exceeds the limit: '%s/%s'", parent, child->d_name);
				return;
			}
						
			sprintf(nambuf, "%s/%s", parent, child->d_name);
			parseFiles(nambuf, root);
			

		}
	}

	closedir(pdir);
}

