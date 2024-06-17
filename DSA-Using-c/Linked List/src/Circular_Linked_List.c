#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void display()
{
	if(head == NULL)
		return;
	struct Node *temp = head;

	do
	{
		printf("%d->",temp->data);
		temp=temp->next;
	}while(temp != head);

	printf("NULL\n");
}


struct Node * create_node(int data)
{
	struct Node *new_node = (struct Node *)malloc(1*sizeof(struct Node));
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return NULL;
	}
	new_node->next = NULL;
	new_node->data = data;

	return new_node;
}


void create(int *arr,int num)
{
	for(int i= 0 ; i< num ; i++)
	{
		struct Node *new_node = create_node(arr[i]);
		if(new_node == NULL){
			perror("unable to allocate heap \n");
			return ;
		}

		if(head == NULL)
		{
			new_node->next=new_node;
			head= new_node;
		}
		else
		{
			struct Node *temp =head;

			while(temp->next !=head)
				temp=temp->next;

			temp->next=new_node;
			new_node->next =head;

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

	if(head == NULL)
	{
		new_node->next = new_node;
		head=new_node;
	}
	else{
		struct Node *temp =head;
		while(temp->next !=head)
			temp=temp->next;

		temp->next=new_node;
		new_node->next = head;
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
		new_node->next = new_node;
		head=new_node;
	}
	else{
		struct Node *temp =head;

		while(temp->next != head)
			temp=temp->next;

		temp->next = new_node;
		new_node->next = head;
	}
	display();
}

void insert_after(int targetdata,int data)
{
	if(head == NULL)
		return;
	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return ;
	}

	struct Node *temp =head;

	do{

		if(temp->data == targetdata){
			new_node->next=temp->next;
			temp->next = new_node;
			display();
			return ;
		}
		temp=temp->next;
	}while(temp != head);


	if(temp != head){
		printf("unable to find data in list\n");
	}

}

void insert_before(int targetdata,int data)
{
	if(head == NULL)
			return;
	struct Node *new_node = create_node(data);
	if(new_node == NULL){
		perror("unable to allocate heap \n");
		return ;
	}

	if(head->data == targetdata)
	{
		struct Node *temp =head;
		while(temp->next != head)
			temp=temp->next;
		temp->next = new_node;
		new_node->next = head;
		head =new_node;
	}
	else
	{
		struct Node *temp =head,*prev=NULL;
		while(temp->next != head && temp->data !=targetdata){
			prev=temp;
			temp=temp->next;
		}
		new_node->next=prev->next;
		prev->next = new_node;
	}

	display();
}

void delAtBeg()
{
	struct Node *temp =head;
	struct Node *tobedelte =head;
	while(temp->next != head)
		temp=temp->next;

	temp->next=head->next;
	head=head->next;

	free(tobedelte);
	display();
}

void delAtEnd()
{
	struct Node *temp =head;
	struct Node *prev =NULL;
	while(temp->next != head){
		prev=temp;
		temp=temp->next;
	}

	prev->next=temp->next;
	free(temp);
	display();

}

void delAtPos(int pos)
{
	if(head == NULL)
		return;

	int i=1;

	struct Node *temp =head,prev=NULL;

	bool flag =false;

	for(;i<pos ;i++)
	{
		if(pos == 1)
		{
			struct Node *temp1 =head,*prev1=NULL;

			while(temp1->next != head){
				prev1=temp1;
				temp1=temp1->next;
			}
			prev1->next = head;
			free(temp1);
		}
		else if(temp->next != head && i == pos-1){
			prev->next = temp->next;
			free(temp);
			flag=true;
			break;
		}
		prev=temp;
		temp=temp->next;
	}

	if(!flag){
		printf("Out of Index \n");
	}
	display();
}

void delete_after(int data)
{
	struct Node *curr =head,*prev=NULL;

	while(curr->next != head && curr->data !=data){
		prev=curr;
		curr=curr->next;
	}

	if(curr->next !=head){
		prev=curr;
		curr=curr->next;

		prev->next= curr->next;
		free(curr);
	}
	else
		printf("Unable to find data %d \n",data);
	display();
}

void delete_before(int data)
{
	struct Node *curr =head,*prev=NULL;

	while(curr->next != head && curr->data !=data){
		prev=curr;
		curr=curr->next;
	}

	if(curr->data !=data){
		prev->next= curr->next;
		free(curr);
	}
	else
		printf("Unable to find data %d \n",data);
	display();
}

void updateAtPos()
{

}

void update_before()
{

}

void update_after()
{

}

void search()
{

}

void get_length()
{

}


void reverse()
{

}

int main()
{
	int arr[]={1,2,3,4,5};
	create(arr,5);
	//insertAtEnd(10);
	//insertAtEnd(101);
	//insertAtBeg(1);
	insert_after(5,55);

    return 0;
}
