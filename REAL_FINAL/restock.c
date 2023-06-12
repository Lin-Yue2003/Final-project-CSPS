#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "restock.h"
#include <stdio.h>
#include <math.h>


void initialize_restock_item_list(struct restock_item **head, struct item **category, struct item *target){
    if ((*head) != NULL) free_restock_item_list((*head));
    (*head) = NULL;
    for(int i = 0; i < CATEGORY_NUM; i++){
        struct item *current = category[i];
        while(current != NULL){
            struct restock_item *new_item = malloc(sizeof(struct restock_item));
            if(new_item == NULL){
                printf("Fail to malloc in %s\n", __func__);
                return;
            }
            new_item->item = current;
            // new_item->similarity = cosine_similarity(target,new_item->item);
            new_item->next = NULL;
            add_to_restock_item_list(head,new_item);
            current = current->next;
        }
    }
    // quick_sort((*head), last_item((*head)));
}

//find the last recommended item in the list
struct restock_item *back_item(struct restock_item *head){
    struct restock_item *temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

//delete a restock item in the list by its address
void delete_restock_item(struct restock_item **head, struct restock_item *target){
    if (target == NULL) return;
    struct restock_item *current = *head;
    struct restock_item *prior = NULL;
    while (current != NULL){
        if (current == target){
            if(prior == NULL){
                *head = current->next;
            }else {
                prior->next = current->next; 
            }
            free(current);
            break;
        }
        prior = current;
        current = current->next;
    }
}

//free all the restock items in the list 
void free_restock_item_list(struct restock_item *head){
    struct restock_item *next;
    while(head != NULL){
        next = head->next;
        free(head);
        head = next;
    }
}
//add a new item to the last of the list
void add_to_restock_item_list(struct restock_item **head, struct restock_item *new_item){
    if (new_item == NULL){
        printf("Fail to %s\n", __func__);
        return;
    }
    if (*head == NULL){
        *head = new_item;
    } else{
        struct restock_item *back_item = *head;
        while(back_item->next != NULL){
            back_item = back_item->next;
        }
        back_item->next = new_item;
    }
}


//count how many items in the recommended list
int count_restock_item_num(struct restock_item *current){
    int num = 0;
    while(current != NULL){
        num++;
        current = current->next;
    }
    return num;
}
