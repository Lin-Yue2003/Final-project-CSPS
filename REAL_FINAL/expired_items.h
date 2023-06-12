#ifndef EXPIRED_ITEMS_H
#define EXPIRED_ITEMS_H

#define item_num_in_page 10
#define MAX_PAGE_NUM 100
#define MAX_SOLDOUT_ITEM 100
#define MAX_EXPIRED_ITEM 1


struct preserved_item{
    struct item *item;
    struct preserved_item *next;
};
    

void check_Items_preserve_days(struct item *category[CATEGORY_NUM], struct item **expired_item, float *day);
void preserved_system(struct item **category,struct item **expired_item, struct item **selected_item, int *condition, int *option, int *order_num);
void pagez_system(struct item *item_head, int *order_num, int *condition, int *option, struct item **selected_item);
void selected_itemz_system(struct item **selected_item, int *condition, int *option, int *order_num);
void initialize_pagez_list(struct item *page_list[],struct item *item_head, int total_page);
void initialize_preserved_item_page_list(struct preserved_item *page_list[],struct preserved_item *item_head, int total_page);
void initialize_pagez(struct item *cur_page[]);
void read_pagez(struct item *cur_page[], struct item *current);
void read_preserved_item_page(struct item *cur_page[], struct preserved_item *current);
int print_pagez(struct item *cur_page[],int total_item, int current_page_num,int total_page, struct item *selected_item);
int print_selected_items_pagez(struct item *cur_page[],int total_item, int current_page_num,int total_page, struct item *selected_item);

void initialize_preserved_item_list(struct preserved_item **head, struct item **category, struct item *target);
struct preserved_item *bak_item(struct preserved_item *head);
void delete_preserved_item(struct preserved_item **head, struct preserved_item *target);
void free_preserved_item_list(struct preserved_item *head);
void add_to_preserved_item_list(struct preserved_item **head, struct preserved_item *new_item);
int count_preserved_item_num(struct preserved_item *current);




#endif 
