/*
** Dennis Lin
** DL142745
** Noah
** Fr_12:35
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Symbolic constants for command line. */
#define NUMARG 4
#define FLAG 1
#define IN_FILE_ARG 2
#define OUT_FILE_ARG 3

struct node{
	char id[64];
	int def;
	int use;
	struct node *next;
};

void readFile(FILE *file); 
void insert(struct node **h, struct node **t, FILE *file);
void printList(struct node *h);

int main(int argc, char *argv[]){
	FILE *finp;
	FILE *finp2;
	FILE *fout;
	char buff[255];
	int i;
	struct node *head, *tail;
	head=tail=NULL;
	
	if (argc != NUMARG){
		printf("Usage: a.out Flag Infile Outfile\n");
		exit(1);
	}
	
	/*open input file for reading*/
	if ((finp = fopen(argv[IN_FILE_ARG], "r")) == NULL){ /* Open failed. */
		printf("Could not open file %s for reading.\n", argv[IN_FILE_ARG]);
		exit(1);
	}
	
	/*open output file for writing*/
	if ((fout = fopen(argv[OUT_FILE_ARG], "w")) == NULL){ /* Open failed. */
		printf("Could not open file %s for writing.\n", argv[OUT_FILE_ARG]);
		exit(1);
	}
	
	if(strcmp(argv[FLAG], "-1") == 0)
	{
		printf("The contents of the file %s:\n\n", argv[OUT_FILE_ARG]);
		readFile(finp);
	}
	else if(strcmp(argv[FLAG], "-c") == 0)
	{
		insert(&head, &tail, finp);
		printList(head);
	}
	else if(strcmp(argv[FLAG], "-b") == 0)
	{
		printf("The contents of the file %s:\n\n", argv[OUT_FILE_ARG]);
		readFile(finp);
		rewind(finp);
		insert(&head, &tail, finp);
		printList(head);
	}
	else
	{
		printf("Not a valid flag. Valid Flag: -1, -c, -b");
	}
	
	if (fclose(finp) == EOF) { /* Error in closing input file */
		printf("Error in closing file input.dat.\n");
	}
	
	if (fclose(fout) == EOF) { /* Error in closing output file */
		printf("Error in closing file output.dat.\n");
	}

	return 0;
}

void readFile(FILE *file){
	char buff[255];
	int i = 1;
	
	if(file){
		while(fgets(buff, 255, file) != NULL)
		{
			if(strcmp(buff, "\n"))
			{
				printf("%d	%s", i++, buff);
			}
			else
			{
				continue;
			}
		}
	}
}

void insert(struct node **h, struct node **t, FILE *file){
	struct node *newNode;
	char buff[255];
	char *token;
	int i = 1, j = 1, k = 0;
	size_t tokLen;
	
	if(file){
		while(fgets(buff, 255, file) != NULL)
		{
			token = strtok(buff, " ");
			tokLen = strlen(token);
			if(strcmp(buff, "\n") == 0)
			{
				continue;
			}
			else if(token[0] == '#' || token[0] == '.')
			{
				i++;
				continue;
			}
			else if(strncmp(token + tokLen - 1, ":", 1) == 0)
			{
				if ((newNode = (struct node *)malloc(sizeof(struct node))) == NULL){
					printf("Node allocation failed. \n");
					exit(1);
				}
				
				token = strtok(buff, ":");
				strcpy(newNode->id, token);
				newNode-> def = i;
				i++;
				if(*h == NULL)  
				{
					*h = newNode;
					*t = newNode;
					newNode->next = NULL;
				}
				else
				{
					(*t)->next = newNode;
					*t = (*t)->next;
					newNode->next = NULL;
				}
			}
			else
			{
				i++;
				continue;
			}
		}
	}
}

/*Prints the list*/
void printList(struct node *h){
	char *id = "Identifier";
	char *def = "Definition";
	char *use = "Use";
	
	printf("\n");
	if(h == NULL)   /*checks if list is empty*/
	{
		printf("List is empty\n");
	}
	else   /*Prints the node id and def then goes to next node*/
	{
		printf("Cross Reference Table\n\n");
		printf("%s%20s%20s\n", id, def, use);
		
		while(h != NULL)
		{	
			printf("%-20s%-10d\n", h->id, h->def);
			h = h->next;
		}
	}
}