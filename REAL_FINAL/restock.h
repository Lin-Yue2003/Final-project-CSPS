#ifndef RESTOCK_H
    #define RESTOCK_H

    struct restock_item{
        struct item *item;
        float similarity;
        struct restock_item *next;
    };
    
    //void initialize_target(struct item *target,struct item *selected_item, struct item **soldout_item);
    void initialize_restock_item_list(struct restock_item **head, struct item **category, struct item *target);
    struct restock_item *back_item(struct restock_item *head);
    void delete_restock_item(struct restock_item **head, struct restock_item *target);
    void free_restock_item_list(struct restock_item *head);
    void add_to_restock_item_list(struct restock_item **head, struct restock_item *new_item);
    int count_restock_item_num(struct restock_item *current);

#endif