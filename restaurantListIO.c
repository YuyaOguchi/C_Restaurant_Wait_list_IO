//  Yuya Oguchi
//  COEN11L     Lab7
//  11/07/2014
//  restaurantwaitlist IO
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    int number;
    char name[20];
    struct node *next;
    struct node *previous;
}Node;

Node *head = NULL;
Node *tail = NULL;

void add(){
    Node *p;
    if ((p = (Node*)malloc (sizeof (Node))) == (Node*)NULL){
		printf ("Node could not be allocated\n");
		return;
	}

    printf("Enter name\n");
	scanf("%s", p->name);
	if (head == NULL){
		head = p;

	}else{
		Node *temp;
		temp = head;
		while (temp != NULL){
			if (strcmp(temp->name, p->name) == 0){//duplicate
				printf("Duplicate, try again\n");
				free(p);
				return;
			}
			else{//no duplicate
				temp = temp->next;
			}
		}
	}//end else check duplicate
    printf("Enter the number\n");
    scanf("%d",&p->number);
    if (tail != NULL){
		tail->next = p;
	}
	tail = p;
    tail->next=NULL;
    return;
}

void addpro(char name[20],int number){
    Node *p;
    if ((p = (Node*)malloc (sizeof (Node))) == (Node*)NULL){
		printf ("Node could not be allocated\n");
		return;
	}

	strcpy(p->name,name);
    p->number = number;

	if (head == NULL){
		head = p;

	}
    if (tail != NULL){
		tail->next = p;
	}
	tail = p;
    tail->next=NULL;
    p = p->next;
    return;
}


void delete(){
    int open;
    Node *temp = head;//make temp linklist that is at head
    printf("What is the size of table?\n");
    scanf("%d", &open);

	if (head->number <= open)//checking for head
	{
        head = temp->next;
        free(temp);
        return;
	}
    Node *change;
    Node *temp2;
    change=temp;
    temp=change->next;
    while (temp->next != NULL){
        //change=temp;
        //temp=change->next;
        if (temp->number <= open)//if num is less than open
        {
            temp2 = change->next;
            change->next = change->next->next;
            free(temp2);
            printf("Value taken out\n");
            return;
        }else if (temp->number > open)
        {
            change = temp;
            temp = temp->next;
        }
    }//close while loop

    if(temp->number <= open){
        printf("Last value taken out\n");
        free(temp);
        tail = change;
        tail->next = NULL;
    }
	return;
}//close void

void stats(){
    Node *temp = head;
    while (temp != NULL){
        printf("Name: %s\tNumber: %d\n", temp->name, temp->number);
		temp = temp->next;
    }
    return;
}

void write_file(){

    char input[50];//this is name
    FILE *listw;
    listw = fopen("list.txt", "w");
    if (listw == NULL){
        printf ("cannot open the file %s\n",input);
    }

    Node *temp = head;
    while (temp != NULL){
        fprintf(listw, "%s %d\n", temp->name, temp->number);
		temp = temp->next;
    }

    fclose(listw);

}

int main(int argc, char *argv[])
{
    char namex[20];
    int numberx;
    int command;
    int quit = 0;
    printf("Welcome to Yuya's Restaurant what would you like to do?\n\n");
    printf("Type 1 to add waitlist\n");
    printf("Type 2 to eliminate an entry that fits the table\n");
    printf("Type 3 to show all Waitlist\n");
    printf("Type 4 to quit\n");
    printf("----------------------------\n\n");

    //read file
    char input[50];//this is name
    FILE *list;
    list = fopen(argv[1], "r");
    if (list == NULL){
        printf ("cannot open the file %s\n",input);
    }

    while(fscanf(list,"%s %d\n",namex,&numberx) != EOF)
    {
    addpro(namex,numberx); //readin all info
    }
    while (quit == 0){

        scanf("%d",&command);

        if (command == 1){
            add();

        }else if (command == 2){
            delete();

        }else if (command == 3){
            stats();

        }else if (command == 4){
            write_file(); //load all info
            quit = 1;

        }
        printf("What would you like to do?\n");

    }//end while loop

    return 0;
}
