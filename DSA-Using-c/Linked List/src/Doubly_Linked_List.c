// Doubly Linked List

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

void Display()
{
	if(head==NULL)
		return;

	struct Node *temp=head;

	while(temp)
	{
		printf("%d->",temp->data);
		temp=temp->next;
	}
	printf("NULL\n");
}

struct Node * create_node(int data)
{
	struct Node *new_node = (struct Node *)malloc(1*sizeof(struct Node));
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return NULL;
	}
	new_node->next =new_node->prev= NULL;
	new_node->data = data;

	return new_node;
}


void create(int *arr,int num)
{
	for(int i=0;i<num;i++)
	{
		struct Node *new_node = create_node(arr[i]);
		if(new_node == NULL){
			perror("unable to allocate heap \n");
			continue;
		}

		if(head == NULL)
		{
			head=tail=new_node;
		}
		else
		{
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
		}
	}
	Display();
}

void insertatbeg(int data)
{
	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return;
	}

	if(head == NULL)
	{
		head=tail=new_node;
	}
	else
	{
		head->prev=new_node;
		new_node->next=head;
		head=new_node;
	}
	Display();

}

void insertatend(int  data)
{
	struct Node *new_node = create_node(data);
		if(new_node == NULL){
			perror("unable to allocate heap \n");
			return;
		}

		if(head == NULL)
		{
			head=tail=new_node;
		}
		else
		{
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
		}
		Display();
}

void insertpos(int data, int pos)
{
	if(head == NULL)
		return;

	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return;
	}

	if(pos == 1)
	{
		new_node->next=head;
		head->prev=new_node;
		head=new_node;
	}
	else {
	struct Node *curr=head;

	for(int i=1 ; curr!=NULL && i<pos ; i++)
	{
		curr=curr->next;
	}

	if(curr != NULL)
	{
		curr->prev->next=new_node;
		new_node->prev=curr->prev;
		new_node->next = curr;
		curr->prev=new_node;
	}
	else
		printf("Invalid positions\n");

	}

	Display();

}

void delatbeg()
{
	struct Node *curr=head;

	head=head->next;
	head->prev=NULL;

	free(curr);
	Display();
}

void delatend()
{
	struct Node *curr=tail;
	tail=tail->prev;
	tail->next = NULL;

	free(curr);
	Display();
}

void delatpos(int pos)
{
	if(pos == 1)
		delatbeg();
	else
	{
		struct Node *curr=head;

		for(int i=1;curr !=NULL && i<pos;i++)
			curr=curr->next;

		if(curr == tail)
		{
			tail=tail->prev;
			tail->next = NULL;
			free(curr);
		}
		else if(curr != NULL)
		{
			curr->prev->next=curr->next;
			curr->next->prev=curr->prev;
			free(curr);
		}
		else
			printf("invalid positions\n");
	}
	Display();
}



void reverse()
{
	if(head == NULL)
		return;

	struct Node *curr = head;
	struct Node *prev = NULL;
	struct Node *next = curr->next;

	while(curr->next != NULL){
		curr->prev=curr->next;
		curr->next=prev;
		prev=curr;
		curr=next;
		next=next->next;
	}
	curr->prev=curr->next;
	curr->next=prev;

	struct Node *temp = head;
	head=tail;
	tail=temp;
	Display();

}

int get_length()
{
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;

}

int main()
{
	int arr[]={1,2,3,4,5};
	create(arr,5);
	//insertpos(11,6);
	//delatpos(6);
	//insertatbeg(14);
	//insertatend(145);
	reverse();
    return 0;
}
