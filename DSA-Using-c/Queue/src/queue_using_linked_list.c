// Queue Using Linked List
#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    int data;
    struct Queue *next;
};

struct Queue *front = NULL;
struct Queue *rear = NULL;

void display()
{
	struct Queue * curr=front;

	while(curr){
		printf("%d->",curr->data);
		curr=curr->next;
	}
	printf("NULL\n");
}

struct Queue *create_node(int data)
{
	struct Queue *new_node=malloc(sizeof(struct Queue));

	if(new_node == NULL)
		return new_node;

	new_node->data=data;
	new_node->next=NULL;

	return new_node;

}

void enqueue(int x)
{

}

void dequeue()
{

}

void peek()
{

}

void display()
{

}

int main()
{

    return 0;
}
