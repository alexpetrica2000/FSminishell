#ifndef __LIST_H__
#define __LIST_H__
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct Directories {

	struct Directory *dir;

	struct Directories *nextdir;

} Directories;

typedef struct Files {

	struct File *file;

	struct Files *nextfile;

} Files;

Directory *create_fs(struct Directory *dir);
void delete_fs(struct Directory *dir);
void touch(struct Directory *dir, char *filename, char *content);
void mkdir(Directory *director, char *dirname);
void ls(struct Directory *director);
void pwd(struct Directory *director);
Directory *cd(struct Directory *director, char *sir);
void tree(struct Directory *director, int i);
void deleteListF(struct Files *listfile);
void deleteListD(struct Directories *listdir);
void rm(struct Directory *director, char *filename);
void rmdir(struct Directory *director, char *dirname);
void find(Directory *director, int depth, int min, int max, char *content);
#endif /* __LIST__ */
