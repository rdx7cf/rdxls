#ifndef _FILE_ENTRY_H_
#define _FILE_ENTRY_H_

#include <sys/stat.h>

#define	PERMLEN	11
#define PATHLEN	1024
#define COMPLEN	1024

typedef struct fentry
{
	char perms[PERMLEN];
	char path[PATHLEN];
	int mode;
	int uid;
	int gid;
	long links;
	long size;
} FileEntry;

int fe_compare(const FileEntry *, const FileEntry *);
FileEntry *fe_create(const struct stat *, const char *);
void fe_print(const FileEntry *, FILE *); 


#endif
