

#ifndef __LIST_H__
#define __LIST_H__
//#define 	TEST

#define BUF_SIZE  70
struct nifty_filed {
#ifndef TEST
	char name[BUF_SIZE];
	char nse_code[BUF_SIZE];
	char industries[BUF_SIZE];
	char cmp_to_iv[BUF_SIZE];
	char price_to_book[BUF_SIZE];
	char market_capitalizations[BUF_SIZE];
	char pe[BUF_SIZE];
	char industry_pe[BUF_SIZE];
	char peg[BUF_SIZE];
#endif
	char current_price[BUF_SIZE];

};

struct list
{
	struct nifty_filed data;
	struct list *next;
};

void insert_first(struct list **head,struct list *new_node);
void insert_last(struct list **head,struct list *new_node);
void show_list(struct list *head);

#endif
