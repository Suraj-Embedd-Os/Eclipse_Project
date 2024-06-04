

#include <stdio.h>
#include <string.h>
#include"list.h"



void show_field(struct list *head)
{
	#ifndef TEST
	printf("name : %s,",head->data.name);
	#endif

	#ifndef TEST
	printf("nse_code : %s,",head->data.nse_code);
	#endif

	#ifndef TEST
	printf("industries : %s\n",head->data.industries);
	#endif

	#ifndef TEST
	printf("cmp_to_iv : %f,",head->data.cmp_to_iv);
	#endif

	#ifndef TEST
	printf("price_to_book : %f,",head->data.price_to_book);
	#endif

	#ifndef TEST
	printf("market_capitalizations : %f\n",head->data.market_capitalizations);
	#endif

	#ifndef TEST
	printf("pe : %f,",head->data.pe);
	#endif

	#ifndef TEST
	printf("industry_pe : %f,",head->data.industry_pe);
	#endif

	#ifndef TEST
	printf("peg : %f\n",head->data.peg);
	#endif

	//#ifndef TEST
	printf("current_price : %f ",head->data.current_price);
	//#endif

}

void insert_first(struct list **head,struct list *new_node)
{
	 new_node->next=*head;
	 *head=new_node;
}
void insert_last(struct list **head,struct list *new_node)
{
	if(*head == NULL)
	{
		*head=new_node;
		return;
	}
	else
	{
		struct list *temp=*head;

		while(temp->next != NULL)
			temp=temp->next;
		temp->next=new_node;
	}
}

void show_list(struct list *head)
{
	struct list *temp=head;

	while(temp)
	{
		show_field(temp);
		temp=temp->next;
	}
}
