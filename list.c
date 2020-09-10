#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "list.h"

Directory *create_fs(struct Directory *dir)
{
dir = (Directory *)malloc(sizeof(Directory));
dir->name = malloc(2*sizeof(char));
strcpy(dir->name, "/");
dir->files = NULL;
dir->directories = NULL;
dir->parentDir = NULL;

return dir;

}

void delete_fs(struct Directory *dir)
{
dir->files = NULL;
dir->directories = NULL;
dir->parentDir = NULL;
free(dir->files);
free(dir->name);
free(dir->directories);
free(dir->parentDir);
free(dir);
}

void touch(struct Directory *dir, char *filename, char *content)
{
struct Files *filenou;
// Alocam memorie pentru fisier
filenou = (Files *)malloc(sizeof(Files));
filenou->file = malloc(sizeof(File));
filenou->file->name = malloc(strlen(filename)+1);
strcpy(filenou->file->name, filename);
filenou->file->size = strlen(content);
filenou->file->data = malloc(strlen(content)+1);
filenou->file->dir = dir;
strcpy(filenou->file->data, content);

//Cazul in care lista e goala
if (dir->files == NULL) {
	dir->files = filenou;
	filenou->nextfile = NULL;
} else {
	Files *p = dir->files;
	Files *q = dir->files;

	while (p != NULL && strcmp(p->file->name, filename) < 0) {
		q = p;
		p = p->nextfile;
	}
	// Cazul in care adaugam la inceputul listei
	if (p == q) {
		filenou->nextfile = dir->files;
		dir->files = filenou;
	}
	// Cazul in care adaugam la sfarsitul listei
	if (p == NULL) {
		q->nextfile = filenou;
		filenou->nextfile = NULL;
	}
	// Cazul in care adaugam in interiorul listei
	if (p != NULL && p != q) {
		q->nextfile = filenou;
		filenou->nextfile = p;
	}
}
}

void mkdir(Directory *director, char *dirname)
{
struct Directories *diradd;
// Alocam memorie pentru director
diradd = (Directories *)malloc(sizeof(Directories));
diradd->dir = (Directory *)malloc(sizeof(Directory));
diradd->dir->name = malloc(strlen(dirname)+1);
strcpy(diradd->dir->name, dirname);
diradd->nextdir = NULL;
diradd->dir->files = NULL;
diradd->dir->directories = NULL;
diradd->dir->parentDir = director;
Directories *p = director->directories;
Directories *q = director->directories;

// Cazul in care lista de directoare e goala
if (director->directories == NULL) {
	director->directories = diradd;
	diradd->nextdir = NULL;

} else {
	while (p != NULL && strcmp(p->dir->name, dirname) < 0) {
		q = p;
		p = p->nextdir;
	}
	// Cazul in care adaugam un director care exista deja
	if (strcmp(q->dir->name, dirname) == 0) {
		diradd->dir->parentDir = NULL;
		diradd->dir->name = NULL;
		free(diradd->dir->name);
		free(diradd->dir);
		free(diradd);
		return;
	}
	// Daca adaugam la inceputul listei
	if (p == q) {
		diradd->nextdir = director->directories;
		director->directories = diradd;
	}
	// Daca adaugam la sfarsit
	if (p == NULL) {
		q->nextdir = diradd;
		diradd->nextdir = NULL;
	}
	// Daca adaugam in cadrul listei
	if (p != q && p != NULL) {
		q->nextdir = diradd;
		diradd->nextdir = p;
	}
}
}

void ls(struct Directory *director)
{
Files *p = director->files;
Directories *r = director->directories;

// Parcurgem listele de directoare si fisiere si afisam numele fiecaruia
while (p != NULL) {
	printf("%s ", p->file->name);
	p = p->nextfile;
}
while (r != NULL) {
	printf("%s ", r->dir->name);
	r = r->nextdir;
}

printf("\n");

}

void pwd(struct Directory *director)
{
Directory *p = director;

if (p->parentDir == NULL)
	return;
pwd(p->parentDir);
printf("/%s", p->name);
}

Directory *cd(struct Directory *director, char *sir)
{
if (strcmp(sir, "..") == 0) {
	Directory *r = director;

	r = director->parentDir;
	return r;
} else {
	Directories *p = director->directories;

		while (p != NULL && strcmp(p->dir->name, sir) != 0)
			p = p->nextdir;
	if (p != NULL)
		return p->dir;
		else {
			printf("Cannot move to '%s'", sir);
			printf(": No such directory!\n");
			return director;
		}
	}
}

void tree(struct Directory *director, int i)
{

Files *p = director->files;
int aux = i, j, t;
t = i;
while (t--)
	printf(" ");
printf("%s\n", director->name);
while (p != NULL) {
	j = aux + 4;
	while (j--)
		printf(" ");
	printf("%s\n", p->file->name);
	p = p->nextfile;
}
	Directories *r;

	for (r = director->directories; r != NULL; r = r->nextdir)
		tree(r->dir, i + 4);

}

// Functie ce sterge lista de fisiere
void deleteListF(struct Files *listfile)
{
Files *p = listfile;
Files *q = listfile;
while (p != NULL) {
	q = p->nextfile;
	p->nextfile = NULL;
	free(p->file->name);
	free(p->file->data);
	free(p->file);
	free(p);
	p = q;
}
}

// Functie ce sterge recursiv lista de directoare si fisiere
void deleteListD(struct Directories *listdir)
{
Directories *p = listdir;
Directories *q = listdir;
while (p != NULL) {
	q = p->nextdir;
	p->nextdir = NULL;
	p->dir->parentDir = NULL;
	free(p->dir->name);
	deleteListF(p->dir->files);
	deleteListD(p->dir->directories);
	free(p->dir);
	free(p);
	p = q;
}
}

void rm(struct Directory *director, char *filename)
{
Files *p = director->files;
Files *q = director->files;

while (p != NULL && strcmp(p->file->name, filename) != 0) {
	q = p;
	p = p->nextfile;
}
// Cazul in care se sterge primul fisier
if (q == p && p != NULL) {
	director->files = p->nextfile;
	free(p->file->name);
	free(p->file->data);
	p->file->dir = NULL;
	p->nextfile = NULL;
	free(p->file);
	free(p);

}
// Cazul in care nu stergem primul fisier
if (q != p && p != NULL) {
	q->nextfile = p->nextfile;
	p->nextfile = NULL;
	free(p->file->name);
	free(p->file->data);
	p->file->dir = NULL;
	free(p->file);
	free(p);
}
// Daca p == Null inseamna ca am ajuns la sf. listei si nu am gasit nimic
if (p == NULL)
	printf("Cannot remove '%s': No such file!\n", filename);

}

void rmdir(struct Directory *director, char *dirname)
{
	Directories *p = director->directories;
	Directories *q = director->directories;

while (p != NULL && strcmp(p->dir->name, dirname) != 0) {
	q = p;
	p = p->nextdir;
}
// Cazul in care stergem primul director
if (p == q && p != NULL) {
	director->directories = p->nextdir;
	free(p->dir->name);
	deleteListF(p->dir->files);
	deleteListD(p->dir->directories);
	p->dir->parentDir = NULL;
	p->nextdir = NULL;
	free(p->dir);
	free(p);
}
//Cazul in care stergem orice alt director inafara de primul
if (p != q && p != NULL) {
	q->nextdir = p->nextdir;
	deleteListF(p->dir->files);
	free(p->dir->name);
	deleteListD(p->dir->directories);
	p->dir->parentDir = NULL;
	p->nextdir = NULL;
	free(p->dir);
	free(p);
}
// In cazul in care nu a fost gasit
if (p == NULL)
	printf("Cannot remove '%s': No such directory!\n", dirname);
}

void find(Directory *director, int depth, int min, int max, char *content)
{
	Files *p = director->files;

	while (p != NULL) {
		if (p->file->size <= max && p->file->size >= min) {
			if (strstr(p->file->data, content) != 0)
				printf("%s ", p->file->name);
		}
		p = p->nextfile;
	}

	Directories *q;

	for (q = director->directories; q != NULL && depth ; q = q->nextdir)
		find(q->dir, depth-1, min, max, content);
}
