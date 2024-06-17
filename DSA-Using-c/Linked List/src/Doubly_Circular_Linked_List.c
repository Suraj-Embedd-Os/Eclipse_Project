// Doubly Circular Linked List
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head, *tail;

void display()
{
	if(head==NULL)
		return;
	struct Node * curr=head;

	do{
		printf("%d-> ",curr->data);
		curr=curr->next;

	}while(curr != head);

	printf("END\n");

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
			return ;
		}

		if(head == NULL)
		{
			new_node->next=new_node;
			head=tail=new_node;
		}
		else{
			new_node->next=tail->next;
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
		}
	}
	display();
}

void insertAtBeg(int data)
{
	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return ;
	}

	if(head == NULL){
		new_node->next=new_node;
		head=tail=new_node;
	}
	else{
		new_node->next=head;
		head->prev=new_node;
		tail->next = new_node;
		head=new_node;
	}
	display();
}

void insertAtEnd(int data)
{
	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return ;
	}

	if(head == NULL){
		new_node->next=new_node;
		head=tail=new_node;
	}
	else{
		new_node->prev=tail;
		new_node->next=tail->next;
		tail->next=new_node;
		tail=new_node;
	}
	display();
}

void insertAtPos(int data ,int pos)
{
	if(head == NULL)
		return;

	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return ;
	}
	struct Node *curr=head;
	for(int i=0 ;i<pos ;i++)
	{
		if(head->next == head && pos == 1)
		{
			new_node->next=head;
			head->prev=new_node;
			tail->next = new_node;
			head=new_node;
			break;
		}
		else
		{

			if(i == pos-1){

			}
			curr=curr->next;
		}
	}
	display();
}

void deleteAtBeg()
{

}

void deleteAtEnd()
{
}

void deleteAtPos()
{

}

void update()
{

}

void updateAtPos()
{

}



void search()
{

}


int main()
{
	int arr[]={1,2,3,4,5};
	create(arr,5);
	insertAtEnd(14);
    return 0;
}
