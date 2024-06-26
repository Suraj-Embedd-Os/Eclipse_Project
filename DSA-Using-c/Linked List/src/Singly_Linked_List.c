// Singly Linked List Program

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void display()
{
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
	new_node->next = NULL;
	new_node->data = data;

	return new_node;
}

void create(int *arr,int num)
{
    for (int i = 0; i < num; i++)
    {
    	struct Node *new_node =create_node(arr[i]);

    	if(new_node == NULL){
    		printf("unable to allocate heap\n");
    		return;
    	}

    	if(head == NULL){
    		head = new_node;
    	}
    	else{
    		struct Node *temp=head;

    		while(temp->next != NULL)
    			temp=temp->next;
    		temp->next=new_node;
    	}
    }
}

void insertatbeg(int data)
{

	struct Node *new_node =create_node(data);
	if(new_node == NULL){
		printf("unable to allocate heap\n");
		return;
	}
	new_node->next=head;
	head=new_node;

}

void insertatend(int data)
{
	struct Node *new_node =create_node(data);
	if(new_node == NULL){
		printf("unable to allocate heap\n");
		return;
	}

	if(head == NULL){
		head = new_node;
	}
	else{
		struct Node *temp=head;
		while(temp->next != NULL)
			temp=temp->next;
		temp->next=new_node;
	}
}

void insertAtPos(int data,int pos)
{
	if(!head)
		return;
	struct Node *new_node =create_node(data);
	if(new_node == NULL){
		printf("unable to allocate heap\n");
		return;
	}

	int i=1;
	struct Node *curr=head;
	struct Node *prev=NULL;
	while(curr && i<=pos){
		if(pos == 1){
			new_node->next =head;
			head=new_node;
			return;
		}
		else{
			if(pos == i){
				prev->next = new_node;
				new_node->next=curr;
				return;
			}
			prev=curr;
			curr=curr->next;
		}
		i++;
	}
	printf("Invalid position number %d\n",pos);
	free(new_node);
}



void insert_before(int data,int which)
{
	if(!head)
		return;
	struct Node *new_node =create_node(data);
	if(new_node == NULL){
		printf("unable to allocate heap\n");
		return;
	}

	struct Node *curr=head;
	//if insert at beginning
	if(head->data == which){
		new_node->next=head;
		head=new_node;
		return;
	}

	while(curr && curr->next->data !=which){
		curr=curr->next;
	}

	if(curr){
		new_node->next=curr->next;
		curr->next = new_node;
	}
	else{
		printf("data not found in the list\n");
		free(new_node);
	}
}

void insert_after(int data,int which)
{
	if(!head)
		return;

	struct Node *new_node =create_node(data);
		if(new_node == NULL){
			printf("unable to allocate heap\n");
			return;
		}

		struct Node *curr=head;


		while(curr && curr->data !=which )
			curr=curr->next;

		if(curr){
	    new_node->next=curr->next;
		curr->next = new_node;
		}
		else{
			printf("data not found in the list\n");
			free(new_node);
		}

}

void delatbeg()
{
	if(!head)
		return;
	struct Node *curr=head;
	head = head->next;
	free(curr);
	display();

}

void delatend()
{
	if(!head)
		return;
	struct Node *curr=head;
	struct Node *prev=NULL;
	while(curr->next !=NULL){
		prev=curr;
		curr=curr->next;
	}
	prev->next = NULL;
	free(curr);
	display();

}

void delAtPos(int pos)
{
	if(!head)
		return;
	int i = 1;
	struct Node *curr=head;
	struct Node *prev=NULL;

   if(pos == 1){
	   	head=head->next;
    	free(curr);
    	 display();
    	return ;
    }
   else {
    while(curr && i < pos ){
    	prev=curr;
    	curr=curr->next;
    	i++;
    }
   }
   if(curr)
   {
	prev->next=curr->next;
	free(curr);
   }
   else
    printf("Invalid pos\n");

   display();
}

void delete_after(int data)
{
	if(!head)
		return;
	struct Node *curr=head;

	while(curr && curr->data != data)
		curr=curr->next;

	if(curr)
	{
		struct Node *temp=curr->next;
		curr->next=curr->next->next;
		free(temp);
	}
	else
		printf("Data %d not found in list\n\r",data);

	display();


}

void update_element(int old_new,int new_data)
{
	if(!head)
		return;

	struct Node *curr=head;
		while(curr && curr->data != old_new)
			curr=curr->next;

		if(curr)
			curr->data=new_data;
		else
			printf("Data %d not found in list\n\r",old_new);
		display();

}

void update_at_beg(int new_data)
{
	if(!head)
		return;
	head->data=new_data;
	display();

}

void update_at_end(int new_data)
{
	if(!head)
		return;

	struct Node *curr=head;
	while(curr->next != NULL)
		curr=curr->next;

	curr->data=new_data;
	display();

}



void sort_list()
{

}

void reverse()
{
	if(head->next == NULL)
		return;

	struct Node *curr=head;
	struct Node * prev= NULL;
	struct Node * next =curr->next;

	while(curr->next != NULL)
	{
		curr->next = prev;
		prev=curr;
		curr=next;
		next=next->next;
	}

	curr->next = prev;
	head=curr;
	display();
}

int get_length()
{
	  struct Node *temp=head;
	  int cnt =0;
	    while(temp)
	    {
	        temp=temp->next;
	        cnt++;
	    }
	    return cnt;
}

void search(int data)
{
	int index = 0;
  struct Node *temp=head;

	while(temp && temp->data !=data)
	{
		temp=temp->next;
		index++;

	}

	if(!temp)
	{
		printf("data found at :%d\n",index);
	}
	else
		printf("data not avaiiable in list\n");


}

void Concatenate()
{

}

int main()
{
	int arr[]={1,2,3,4,5};

	create(arr,5);
	reverse();

	//display();
	//delatbeg();
	//delatend();
	//delAtPos(5);
    return 0;
}
