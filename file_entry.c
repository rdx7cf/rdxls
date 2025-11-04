#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "file_entry.h"

int fe_compare(const FileEntry *f1, const FileEntry *f2)
{
	return strcmp(f1->path, f2->path);
}

FileEntry *fe_create(const struct stat *stbuf, const char *rhs_path)
{
	FileEntry *fe;
	void fe_composePerms(FileEntry *);

	if ((fe = (FileEntry*) malloc(sizeof(FileEntry))) != NULL)
	{
		strncpy(fe->path, rhs_path, PATHLEN - 1);
		fe->mode = stbuf->st_mode;
		fe_composePerms(fe);	
		fe->uid = stbuf->st_uid;
		fe->gid = stbuf->st_gid;
		fe->links = stbuf->st_nlink;
		fe->size = stbuf->st_size;
	}
	else
		fprintf(stderr, "rdxls: An error occurred while creating a file entry.\n");

	return fe;
}

void fe_composePerms(FileEntry *fe)
{

	// File type determination.
	
	if (S_ISREG(fe->mode))
		fe->perms[0] = '-';
	else if(S_ISDIR(fe->mode))
		fe->perms[0] = 'd';
	else if (S_ISCHR(fe->mode))
		fe->perms[0] = 'c';
	else if (S_ISBLK(fe->mode))
		fe->perms[0] = 'b';
	else if (S_ISFIFO(fe->mode))
		fe->perms[0] = 'p';
	else if (S_ISLNK(fe->mode))
		fe->perms[0] = 'l';
	else if (S_ISSOCK(fe->mode))
		fe->perms[0] = 's';

	// Owner's permissions.

	if (fe->mode & S_IRUSR)
		fe->perms[1] = 'r';
	else
		fe->perms[1] = '-';

	if (fe->mode & S_IWUSR)
		fe->perms[2] = 'w';
	else
		fe->perms[2] = '-';

	if (fe->mode & S_ISUID)
		fe->perms[3] = 's';
	else if (fe->mode & S_IXUSR)
		fe->perms[3] = 'x';
	else
		fe->perms[3] = '-';

	// Group's permissions.

	if (fe->mode & S_IRGRP)
		fe->perms[4] = 'r';
	else
		fe->perms[4] = '-';

	if (fe->mode & S_IWGRP)
		fe->perms[5] = 'w';
	else
		fe->perms[5] = '-';

	if (fe->mode & S_ISGID)
		fe->perms[6] = 's';
	else if (fe->mode & S_IXGRP)
		fe->perms[6] = 'x';
	else
		fe->perms[6] = '-';

	// Other's permissions.
	
	if (fe->mode & S_IROTH)
		fe->perms[7] = 'r';
	else
		fe->perms[7] = '-';

	if (fe->mode & S_IWOTH)
		fe->perms[8] = 'w';
	else
		fe->perms[8] = '-';

	if (fe->mode & S_ISVTX)
		fe->perms[9] = 't';
	else if (fe->mode & S_IXOTH)
		fe->perms[9] = 'x';
	else
		fe->perms[9] = '-';
}

void fe_print(const FileEntry *fe, FILE *output)
{
	if (!output)
		output = stdout;
	
	fprintf(output, "%-15s%-5li%-5i%-5i%-10li%s\n", fe->perms, fe->links, fe->uid, fe->gid, fe->size, fe->path);
}


