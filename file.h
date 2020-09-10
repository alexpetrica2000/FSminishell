#ifndef __FILE_H__
#define __FILE_H__
#include <stdio.h>
#include <stdlib.h>
typedef struct Directory {
    // The name of the directory
	char *name;

	struct Files *files;

	struct Directories *directories;

	struct Directory *parentDir;
} Directory;

typedef struct File {
    // The name of the file
	char *name;

    // The size of the file
	int size;

    // The content of the file
	char *data;

    // The directory in which the file is located
	Directory *dir;
} File;
#endif /* __FILE_H__ */
