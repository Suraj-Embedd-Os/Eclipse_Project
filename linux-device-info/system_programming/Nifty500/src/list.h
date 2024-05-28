

#ifndef __LIST_H__
#define __LIST_H__
//#define 	TEST

#define BUF_SIZE  70
struct nifty_filed {
#ifndef TEST
	char name[BUF_SIZE];
	char nse_code[BUF_SIZE];
	char industries[BUF_SIZE];
	float cmp_to_iv;
	float price_to_book;
	float market_capitalizations;
	float pe;
	float industry_pe;
	float peg;
#endif
	float current_price;

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
