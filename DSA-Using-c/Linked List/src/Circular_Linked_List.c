#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *tail = NULL;

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
	for(int i=0;i<num;i++)
	{
		struct Node *new_node = create_node(arr[i]);

		if(new_node == NULL){
	    		printf("unable to allocate heap\n");
	    		return;
	    	}

		if(tail == NULL){
			new_node->next=new_node;
			tail=new_node;
		}
		else{
			struct Node *temp=head;
			temp->next=new_node;
			new_node->next = head;

		}

	}
}

void insertAtBeg()
{

}

void insertAtEnd()
{

}

void insert_after()
{

}

void insert_before()
{

}

void delAtBeg()
{

}

void delAtEnd()
{

}

void delAtPos()
{

}

void delete_after()
{

}

void delete_before()
{

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

void display()
{
    struct Node *temp = tail->next;
    if (tail == NULL)
    {
        printf("Linked List is Empty\n");
    }
    else
    {
        do
        {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != tail->next);
    }
    printf("\n");
}

void reverse()
{

}

int main()
{

    return 0;
}
