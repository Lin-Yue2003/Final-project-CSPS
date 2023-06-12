#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "database.h"
#include "expired_items.h"
#include "beautiful.h"
#include "play_sound.h"

#define EXIT_SYSTEM 0
#define EXIT_CURRENT_LIST 1
#define CONTINUE 2
#define FINISHED_ORDER 3


void check_Items_preserve_days(struct item *category[CATEGORY_NUM], struct item **expired_item, float *day){
    int option, order_num =0;
    struct item *selected_item = NULL;
    struct preserved_item *preserved_item = NULL; 
    int condition = CONTINUE;
    float num;
    SEPERATE();
    printf("   >>>查看目前已到友善時光的商品<<<\n");
    SEPERATE();
    struct item* items = NULL;
    while(1){
        if (condition == EXIT_SYSTEM) break;
        num = *day;
        //printf("day = %f\n", num);
	int current_category = 0;
	int i = 0;
	while (current_category < CATEGORY_NUM ) {	    
	items = category[current_category];
		while (items != NULL) {
		    items->preserve_days -= num;
		    if(items->preserve_days <= 4){ 
		    	struct item* quick_preserved_item = malloc(sizeof(struct item));
		    	
		    	*quick_preserved_item = *items;
		    	quick_preserved_item->next = NULL;
		    	if(selected_item == NULL){
			// first item in the selected item list
				selected_item = quick_preserved_item;
				if (selected_item != NULL){
					// successfully add to list
					order_num++;
					//printf("『%s』已成功加入選購清單\n", (*selected_item)->name);
					//SEPERATE();
				} else printf("ERROR in %s line %d\n", __func__, __LINE__);
			}
			else{
				// add new item to be the last one of the list
				struct item* last_quick_preserved_item = malloc(sizeof(struct item));
				last_quick_preserved_item = selected_item;
				//last_quick_preserved_item->next = NULL;
				//printf("hihi\n");
				while (last_quick_preserved_item->next != NULL){
					last_quick_preserved_item = last_quick_preserved_item->next;
					//printf("%p\n",*last_quick_preserved_item);	
				}
				
		    		last_quick_preserved_item->next = quick_preserved_item;
		    		

		    		if (last_quick_preserved_item->next != NULL){
					// successfully add to list
					order_num++;
					//printf("『%s』已成功加入選購清單\n", last_quick_preserved_item->next->name);
					//SEPERATE();
		    		} else printf("ERROR in %s line %d\n", __func__, __LINE__);                        
			}
			
		    }
		    items = items->next;
		}
	current_category++;
	}
	
	for (int i = 0;i < MAX_SOLDOUT_ITEM;i++){
        if (expired_item[i] != NULL){
            free_item_list(expired_item[i]);
        }
        expired_item[i] = selected_item;
        break;
    }
        

	        
        if(selected_item == NULL) {
        	printf("目前沒有商品到友善時光\n");
        	condition = EXIT_SYSTEM;
        	break;
        }
        
        
        // 印出來
        preserved_system(category,expired_item, &selected_item, &condition, &option, &order_num);

        if (option == 0){
            condition = EXIT_SYSTEM;
        }

        if (condition == FINISHED_ORDER){
            if (expired_item[0] != NULL){
                //expired_item[i] = selected_item;
                struct item *current = expired_item[0];
                while(current != NULL){
                    current->price *= 0.9;
                    current = current->next;
                }
            }
           
            selected_item = NULL;
            order_num = 0;
            play_sound_paste();
            printf("🚨已貼上標籤🚨\n");
            condition = EXIT_SYSTEM;
        }
        
        
        if (selected_item != NULL){
            free_item_list(selected_item);
            selected_item = NULL;
        }
    }

}



//the main system of preserved
void preserved_system(struct item **category,struct item **expired_item, struct item **selected_item, int *condition, int *option, int *order_num){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct preserved_item *preserved_item = NULL;
    struct item target;
    initialize_preserved_item_list(&preserved_item,expired_item,&target);
    struct preserved_item *temp = preserved_item;
    struct preserved_item *cur_list = preserved_item;
    int total_item_num = count_preserved_item_num(preserved_item);
    int total_num_page = total_item_num / item_num_in_page + ((total_item_num % item_num_in_page == 0)? 0:1);
    struct preserved_item *page_list[MAX_PAGE_NUM];
    initialize_preserved_item_page_list(page_list, preserved_item, total_num_page);
    int current_page_num = 1;
    int current_item_num;
    
    // condition的狀況要更新 不然會亂掉
    
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) {
            free_preserved_item_list(preserved_item);
            break;
        }
        //setup the current page
        initialize_pagez(cur_page);
        read_preserved_item_page(cur_page, cur_list);
        
        current_item_num = print_pagez(cur_page,total_item_num,
                                            current_page_num,total_num_page,*selected_item);
        while(1) {                                  
        	//scan the option from user
        	scanf("%d", option);
            play_sound_touch();
            CLEAR
        	SEPERATE();
        	//determine whether option is in the range
        	int min = 0, max = current_item_num + 3;//(((*selected_item) == NULL)? 2:3);
        	if ((*option) >= min && (*option) <= max){
        		break;
        	} else{
             	printf("🆘沒有這個選項，請重新輸入🆘\n");
        	}
        }


        // Back to catagory list
        if((*option) == 0){
            (*condition) = EXIT_CURRENT_LIST;
            break;
        }
        //prior page
        if((*option) == current_item_num+1){
            play_sound_page();
            if(current_page_num == 1){
                // first page
            }else {
                cur_list = page_list[current_page_num-1];
                current_page_num--;
            }
            continue;
        }
        //next page
        if((*option) == current_item_num+2){
            play_sound_page();
            if(current_page_num == total_num_page){
                // last page
            }else {
                cur_list = page_list[current_page_num+1];
                current_page_num++;
            }
            continue;
        }
        
        // sticker
        if((*option) == current_item_num+3){
            (*condition) = FINISHED_ORDER;
            break;
        }
    }
}


//the main system of the pages for pre-order system
void pagez_system(struct item *item_head, int *order_num, int *condition, int *option, struct item **selected_item){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct item *cur_list = item_head;
    int item_num = count_item_num(item_head);
    int total_num_page = item_num / item_num_in_page + ((item_num % item_num_in_page == 0)? 0:1);
    struct item *page_list[MAX_PAGE_NUM];
    initialize_pagez_list(page_list, item_head, total_num_page);
    int current_page_num = 1;
    int current_item_num;

    //print page
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) break;
        //setup the current page
        initialize_pagez(cur_page);
        read_pagez(cur_page, cur_list);
        while(1){
            //print the current page and store the numbers of items in this page
            current_item_num = print_pagez(cur_page,item_num,
                                            current_page_num,total_num_page,*selected_item);
            //scan the option from user
            scanf("%d", option);
            play_sound_touch();
            CLEAR
            SEPERATE();
            //determine whether option is in the range
            int min = 0, max = current_item_num + 3;//(((*selected_item) == NULL)? 2:3);
            if ((*option) >= min && (*option) <= max){
                break;
            } else{
                printf("🆘沒有這個選項，請重新輸入🆘\n");
            }
        }

        // Back to catagory list
        if((*option) == 0){
            (*condition) = EXIT_CURRENT_LIST;
            break;
        }
        //prior page
        if((*option) == current_item_num+1){
            play_sound_page();
            if(current_page_num == 1){
                // first page
            }else {
                cur_list = page_list[current_page_num-1];
                current_page_num--;
            }
            continue;
        }
        //next page
        if((*option) == current_item_num+2){
            play_sound_page();
            if(current_page_num == total_num_page){
                // last page
            }else {
                cur_list = page_list[current_page_num+1];
                current_page_num++;
            }
            continue;
        }
        if((*option) == current_item_num+3){
            (*condition) = FINISHED_ORDER;
            continue;
        }
    }
}


//the main system to check current selected item list
void selected_itemz_system(struct item **selected_item, int *condition, int *option, int *order_num){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct item *cur_list = *selected_item;
    int total_num_page = (*order_num) / item_num_in_page + (((*order_num) % item_num_in_page == 0)? 0:1);
    struct item *page_list[MAX_PAGE_NUM];
    initialize_pagez_list(page_list, (*selected_item), total_num_page);
    int current_page_num = 1;
    int current_item_num;
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) break;
        //setup the current page
        initialize_pagez(cur_page);
        read_pagez(cur_page, cur_list);
        while(1){
            //print the current page and store the numbers of items in this page
            current_item_num = print_selected_items_pagez(cur_page,(*order_num),
                                            current_page_num,total_num_page,*selected_item);
            //scan the option from user
            scanf("%d", option);
            play_sound_touch();
            CLEAR
            SEPERATE();
            //determine whether option is in the range
            int min = 0, max = current_item_num + (((*selected_item) == NULL)? 2:3);
            if ((*option) >= min && (*option) <= max){
                break;
            } else{
                printf("🆘沒有這個選項，請重新輸入🆘\n");
            }
        }

        // Back to catagory list
        if((*option) == 0){
            (*condition) = EXIT_CURRENT_LIST;
            break;
        }
        //prior page
        if((*option) == current_item_num+1){
            play_sound_page();
            if(current_page_num == 1){
                // first page
            }else {
                cur_list = page_list[current_page_num-1];
                current_page_num--;
            }
            continue;
        }
        //next page
        if((*option) == current_item_num+2){
            play_sound_page();
            if(current_page_num == total_num_page){
                // last page
            }else {
                cur_list = page_list[current_page_num+1];
                current_page_num++;
            }
            continue;
        }
        if((*option) == current_item_num+3){
            (*condition) = FINISHED_ORDER;
            continue;
        }
        //select item
        struct item *item = cur_page[(*option)-1];
        if (item == NULL){
            printf("ERROR in %s line %d\n", __func__, __LINE__);
            continue;
        }
        while(1){
            printf("確定要刪除『%s』嗎?🤔\n", item->name);
            printf("1. 是✅\n2. 否❌\n");
            printf("請輸入選項： ");
            scanf("%d", option);
            play_sound_touch();
            CLEAR
            if ((*option) >= 1 && (*option) <= 2){
                break;
            } else{
                printf("🆘沒有這個選項，請重新輸入🆘\n");
            }
        }
        if ((*option) == 2)
            continue;
        if ((*option) == 1){
            delete_item(selected_item,item);
            (*order_num)--;
            initialize_pagez_list(page_list, (*selected_item), total_num_page);
            cur_list = *selected_item;
            total_num_page = (*order_num) / item_num_in_page + (((*order_num) % item_num_in_page == 0)? 0:1);
            initialize_pagez_list(page_list, (*selected_item), total_num_page);
            current_page_num = 1;
            continue;
        }
    }
}
//search and store the first item's address of each page
void initialize_pagez_list(struct item *page_list[],struct item *item_head, int total_page){
    struct item *current = item_head;
    page_list[0] = item_head;
    for (int i = 1; i < MAX_PAGE_NUM; i++){
        page_list[i] = NULL;
    }
    if (total_page >= MAX_PAGE_NUM) total_page%=MAX_PAGE_NUM;
    for (int i = 1; i <= total_page; i++){
        page_list[i] = current;
        for (int j = 0; j < 10; j++){
            if (current == NULL) return;
            current = current->next;
        }
    }
}
//search and store the first recommended item's address of each page
void initialize_preserved_item_page_list(struct preserved_item *page_list[],struct preserved_item *item_head, int total_page){
    struct preserved_item *current = item_head;
    page_list[0] = item_head;
    for (int i = 1; i < MAX_PAGE_NUM; i++){
        page_list[i] = NULL;
    }
    if (total_page >= MAX_PAGE_NUM) total_page%=MAX_PAGE_NUM;
    for (int i = 1; i <= total_page; i++){
        page_list[i] = current;
        for (int j = 0; j < 10; j++){
            if (current == NULL) return;
            current = current->next;
        }
    }
}
//make every elements in current page point to NULL
void initialize_pagez(struct item *cur_page[]){
    for (int i = 0; i < item_num_in_page; i++)
        cur_page[i] = NULL;
}
//make every elements in current page point to corresponding items
// by using the first item of this page
void read_pagez(struct item *cur_page[], struct item *current){
    int i = 0;
    while (current != NULL && i < item_num_in_page){
        cur_page[i] = current;
        current = current->next;
        i++;
    }
}
//make every elements in current page point to corresponding items
// by using the first recommended item of this page
void read_preserved_item_page(struct item *cur_page[], struct preserved_item *current){
    int i = 0;
    while (current != NULL && i < item_num_in_page){
        cur_page[i] = current->item;
        current = current->next;
        i++;
    }
}
//print all items in current list and options including
//  select item and finish order if order is not empty
int print_pagez(struct item *cur_page[],int total_item, 
                int current_page_num,int total_page, struct item *selected_item){
    int i;
    printf("以下是需要貼友善時光標籤的商品\n");
    printf(" 0. 回到項目列表 \n");
    for (i = 0; i < item_num_in_page; i++){
        if (cur_page[i] != NULL){
            if(i%2==0){
                printf(Black_word_White_back"%2d. 名稱:%-.18s%c\t,價格:%-2d 元 熱量:%-3d 大卡 存貨數量:%-3d"FINISH, 
                    (i+1), cur_page[i]->name, (strlen(cur_page[i]->name)>18)? '*':' ', cur_page[i]->price,
                    cur_page[i]->calories, cur_page[i]->goods_num);
                printf("\n");
            }
            else
            printf("%2d. 名稱:%-.18s%c\t,價格:%-2d 元 熱量:%-3d 大卡 存貨數量:%-3d\n", 
                    (i+1), cur_page[i]->name, (strlen(cur_page[i]->name)>18)? '*':' ', cur_page[i]->price,
                    cur_page[i]->calories, cur_page[i]->goods_num);
            
        }
        else 
            break;
    }
    printf("    %2d. 上一頁     %2d. 下一頁", (i+1), (i+2));
    if(selected_item != NULL) { printf("    ");printf(Green_back" %2d. 貼標籤"FINISH, (i+3));}
    printf("\n\t總共有 %d 個項目   第%d頁 / 共%d頁\n", total_item,current_page_num,total_page);
    
    printf("請輸入編號: ");
    return (i);
}


//print items which have been selected and options including
//  delete item, finish order, change page
int print_selected_items_pagez(struct item *cur_page[],int total_item, 
                int current_page_num,int total_page, struct item *selected_item){
    int i;
    printf(" 0. 回到項目列表 \n");
    for (i = 0; i < item_num_in_page; i++){
        if (cur_page[i] != NULL){
            if(i%2==0){
                printf(Black_word_White_back"%2d. 名稱:%-.18s%c\t,價格:%-2d 元 熱量:%-3d 大卡 存貨數量:%-3d"FINISH, 
                    (i+1), cur_page[i]->name, (strlen(cur_page[i]->name)>18)? '*':' ', cur_page[i]->price,
                    cur_page[i]->calories, cur_page[i]->goods_num);
                printf("\n");
            }
            else
            printf("%2d. 名稱:%-.18s%c\t,價格:%-2d 元 熱量:%-3d 大卡 存貨數量:%-3d\n", 
                    (i+1), cur_page[i]->name, (strlen(cur_page[i]->name)>18)? '*':' ', cur_page[i]->price,
                    cur_page[i]->calories, cur_page[i]->goods_num);
            
        }
        else 
            break;
    }
    printf("            (編號). 刪除編號項目\n ");
    printf("    %2d. 上一頁     %2d. 下一頁", (i+1), (i+2));
    if(selected_item != NULL) { printf("    ");printf(Green_back" %2d. 貼標籤"FINISH, (i+3));}
    printf("\n\t總共有 %d 個項目   第%d頁 / 共%d頁\n", total_item,current_page_num,total_page);
    
    printf("請輸入編號: ");
    return (i);
}

void initialize_preserved_item_list(struct preserved_item **head, struct item **category, struct item *target){
    if ((*head) != NULL) free_preserved_item_list((*head));
    (*head) = NULL;
    for(int i = 0; i < 1; i++){
        struct item *current = category[i];
        while(current != NULL){
            struct preserved_item *new_item = malloc(sizeof(struct preserved_item));
            if(new_item == NULL){
                printf("Fail to malloc in %s\n", __func__);
                return;
            }
            new_item->item = current;
            new_item->next = NULL;
            add_to_preserved_item_list(head,new_item);
            current = current->next;
        }
    }
}

//find the last recommended item in the list
struct preserved_item *bak_item(struct preserved_item *head){
    struct preserved_item *temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

//free all the preserved items in the list
void free_preserved_item_list(struct preserved_item *head){
    struct preserved_item *next;
    while(head != NULL){
        next = head->next;
        free(head);
        head = next;
    }
}
//add a new item to the last of the list
void add_to_preserved_item_list(struct preserved_item **head, struct preserved_item *new_item){
    if (new_item == NULL){
        printf("Fail to %s\n", __func__);
        return;
    }
    if (*head == NULL){
        *head = new_item;
    } else{
        struct preserved_item *back_item = *head;
        while(back_item->next != NULL){
            back_item = back_item->next;
        }
        back_item->next = new_item;
    }
}


//count how many items in the recommended list
int count_preserved_item_num(struct preserved_item *current){
    int num = 0;
    while(current != NULL){
        num++;
        current = current->next;
    }
    return num;
}
