#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "list.h"

int main(void)
{
	struct Directory *root;
	char s[100], aux[100], aux2[100], aux3[100], aux4[100];
	struct Directory *currentDir;


while (fgets(s, 100, stdin) != NULL) {
	if (strcmp(s, "create fs\n") == 0) {
		root = create_fs(root);
		currentDir = root;
	}
	if (strstr(s, "mkdir")) {
		strcpy(aux, s + strlen("mkdir") + 1);
		aux[strlen(aux) - 1] = '\0';
		mkdir(currentDir, aux);
	}
	if (strstr(s, "touch")) {
		strcpy(aux, s+strlen("touch")+1);
		int i = 0;

		while (aux[i] != ' ')
			i++;
		strncpy(aux3, aux, i);
		aux3[i] = '\0';
		strcpy(aux2, s+strlen("touch")+2+strlen(aux3));
		aux2[strlen(aux2)-1] = '\0';
		touch(currentDir, aux3, aux2);
	}
	if (strcmp(s, "ls\n") == 0)
		ls(currentDir);
	if (strcmp(s, "delete fs\n") == 0) {
		delete_fs(root);
		break;
	}
	if (strcmp(s, "pwd\n") == 0) {
		if (currentDir->parentDir == NULL)
			printf("%s\n", "/");
		else {
			pwd(currentDir);
			printf("\n");
		}
		}
		if (strstr(s, "cd") != 0) {
			strcpy(aux, s + strlen("cd") + 1);
			aux[strlen(aux) - 1] = '\0';
			currentDir = cd(currentDir, aux);
		}
		if (strcmp(s, "tree\n") == 0)
			tree(currentDir, 0);
		if (strstr(s, "rmdir")) {
			strcpy(aux, s + strlen("rmdir") + 1);
			aux[strlen(aux) - 1] = '\0';
			s[0] = '\0';
			rmdir(currentDir, aux);
		}
		if (strstr(s, "rm")) {
			strcpy(aux, s + strlen("rm") + 1);
			aux[strlen(aux) - 1] = '\0';
			rm(currentDir, aux);
		}
		if (strstr(s, "find")) {
			strcpy(aux, s + strlen("find") + 1);
			int i = 0, j = 0, k = 0;

			while (aux[i] != ' ')
				i++;
			aux[i] = '\0';
			strcpy(aux2, s+strlen("find")+2+i);
			while (aux2[j] != ' ')
				j++;
			aux2[j] = '\0';
			strcpy(aux3, s+strlen("find")+3+i+j);
			while (aux3[k] != ' ')
				k++;
			aux3[k] = '\0';
			strcpy(aux4, s+strlen("find")+4+i+j+k);
			aux4[strlen(aux4)-1] = '\0';
			i = atoi(aux);
			j = atoi(aux2);
			k = atoi(aux3);

			find(currentDir, i, j, k, aux4);
			printf("\n");
		}
	}
	return 0; }
