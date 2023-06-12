#ifndef CHECK_ITEMS_H
#define CHECK_ITEMS_H

#define item_num_in_page 10
#define MAX_PAGE_NUM 100
#define MAX_SOLDOUT_ITEM 100
#define MAX_EXPIRED_ITEM 1

#include "restock.h"

void check_Items_goods_num(struct item *category[CATEGORY_NUM], struct item **soldout_item);
void restock_system(struct item **category,struct item **soldout_item, struct item **selected_item, int *condition, int *option, int *order_num, int *below_num, int *restock_num);
void pages_system(struct item *item_head, int *order_num, int *condition, int *option, struct item **selected_item);
void selected_items_system(struct item **selected_item, int *condition, int *option, int *order_num);
void initialize_pages_list(struct item *page_list[],struct item *item_head, int total_page);
void initialize_restock_item_page_list(struct restock_item *page_list[],struct restock_item *item_head, int total_page);
void initialize_pages(struct item *cur_page[]);
void read_pages(struct item *cur_page[], struct item *current);
void read_restock_item_page(struct item *cur_page[], struct restock_item *current);
int print_pages(struct item *cur_page[],int total_item, int current_page_num,int total_page, struct item *selected_item);
int print_selected_items_pages(struct item *cur_page[],int total_item, int current_page_num,int total_page, struct item *selected_item);


#endif 
