#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "database.h"
#include "check_items.h"
#include "restock.h"
#include "beautiful.h"
#include "play_sound.h"

#define EXIT_SYSTEM 0
#define EXIT_CURRENT_LIST 1
#define CONTINUE 2
#define FINISHED_ORDER 3
#define FINISHED_QUICK_ORDER 4

void check_Items_goods_num(struct item *category[CATEGORY_NUM], struct item **soldout_item){
    int option, type = 0, order_num = 0, below_num = 0, restock_num = 0;
    struct item *selected_item = NULL;
    struct restock_item *restock_item = NULL; //
    int condition = CONTINUE;
    SEPERATE();

    printf("  >>>查看商品剩餘數量和選擇商品上架<<<\n");
    SEPERATE();
    while(1){
        if (condition == EXIT_SYSTEM) break;
        printf(" 0. 離開系統\n");
        print_category_table();
        if (order_num == 0) {
            printf("%2d. 選擇快速上架商品\n", CATEGORY_NUM+1);
        }
        if (order_num > 0) {
            printf("%2d. 查看已選擇商品\n", CATEGORY_NUM+1);
            printf("%2d. 完成選擇\n", CATEGORY_NUM+2);
        }
        printf("請輸入選項： ");
        scanf("%d", &option);
        play_sound_touch();
        CLEAR
        SEPERATE();
        if (option >= 0 && option <= CATEGORY_NUM+2){
            condition = CONTINUE;
            type = option-1;
        } else{
            printf("🆘沒有這個選項，請重新輸入🆘\n");
            continue;
        }

        if (option == 0 ||option == (CATEGORY_NUM+2)){
            // EXIT_SYSTEM
            type = 0;
            condition = EXIT_SYSTEM;
        }
        if (option == (CATEGORY_NUM+2)){
            // FINISHED_ORDER
            type = 0;
            condition = FINISHED_ORDER;
        }
        if (option == CATEGORY_NUM+1 && order_num == 0){
            // 一鍵上架
            printf("請輸入想要多少數量以下的商品進行補貨：");
            scanf("%d", &below_num);
            play_sound_touch();
            printf("請輸入想要補上多少貨：");
            scanf("%d", &restock_num);
            play_sound_touch();
            CLEAR
            SEPERATE();
            restock_system (category,soldout_item,&selected_item,&condition,&option,&order_num, &below_num, &restock_num);
            
        }
        if (option == CATEGORY_NUM+1 && order_num > 0 && condition != FINISHED_QUICK_ORDER){
            selected_items_system(&selected_item,&condition,&option,&order_num);
        }

        if (condition == CONTINUE)
            pages_system(category[type],&order_num, &condition,&option,&selected_item);

        if(condition == EXIT_CURRENT_LIST){
            condition = CONTINUE;
            continue;
        }
        if(condition == EXIT_SYSTEM){
            if (selected_item != NULL){
                printf("尚未完成上架，離開後本次已選擇項目將會被消除\n");
                printf("是否離開上架系統？\n");
                printf("1.返回\n2.離開\n");
                printf("請輸入選項： ");
                scanf("%d", &option);
                play_sound_touch();
                CLEAR
                SEPERATE();
                if (option == 1) condition = CONTINUE;
                if (option == 2) condition = EXIT_SYSTEM;
                continue;
            }
        }
        if (condition == FINISHED_ORDER || condition == FINISHED_QUICK_ORDER){

            while(1 && condition == FINISHED_ORDER){
                printf("離開目前頁面？\n");
                printf("1. 確認 2. 取消\n");
                printf("請輸入選項： ");
                scanf("%d", &option);
                play_sound_touch();
                CLEAR
                if (option >= 1 && option <= 2){
                    break;
                } else{
                    printf("🆘沒有這個選項，請重新輸入🆘\n");
                }
            }
            if (option == 2){
                condition = CONTINUE;
                continue;
            }
            if (selected_item == NULL){
                printf("您尚未選擇任何商品\n");
                SEPERATE();
            } 
            if (condition == FINISHED_QUICK_ORDER){
            	
                for (int i = 0;i < MAX_SOLDOUT_ITEM;i++){
                    if (soldout_item[i] == NULL){
                        soldout_item[i] = selected_item;
                        struct item *current = soldout_item[i];
    			while(current != NULL){
    				 current->goods_num += restock_num;
       				 current = current->next;
    			}
                        break;
                    }
                }
                selected_item = NULL;
                order_num = 0;
                play_sound_goods();
                printf("🚨已完成上架🚨\n");
                condition = EXIT_SYSTEM;
            }else{

                condition = CONTINUE;
                restock_system (category,soldout_item,&selected_item,&condition,&option,&order_num, &below_num, &restock_num);
                
                if (condition != FINISHED_ORDER) continue;
                struct item *current = selected_item; 
                for (int i = 0;i < MAX_SOLDOUT_ITEM;i++){
                    if (soldout_item[i] == NULL){
                        soldout_item[i] = selected_item;
                        // 進行上貨
                        struct item *current = soldout_item[i];
    			while(current != NULL){
    				 current->goods_num += 5;
       				 current = current->next;
    			}
                        break;
                    }
                }

		
                selected_item = NULL;
                order_num = 0;
                
                play_sound_goods();
                printf("🚨已完成上架🚨\n");
                SEPERATE();
                printf("以下是剛剛上架的商品:\n");
                for (int i = 0;i < MAX_SOLDOUT_ITEM;i++){
                    if (soldout_item[i] == NULL){
                        print_item_list(soldout_item[i-1]);
                        break;
                    }
                }
                condition = EXIT_SYSTEM;
                
            }
        }
    }
    if (selected_item != NULL){
        free_item_list(selected_item);
        selected_item = NULL;
    }
}



//the main system of restock
void restock_system(struct item **category,struct item **soldout_item, struct item **selected_item, int *condition, int *option, int *order_num, int *below_num, int *restock_num){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct restock_item *restock_item = NULL;
    struct item target;
    initialize_restock_item_list(&restock_item,category,&target);
    struct restock_item *temp = restock_item;
    struct restock_item *cur_list = restock_item;
    int total_item_num = count_restock_item_num(restock_item);
    int total_num_page = total_item_num / item_num_in_page + ((total_item_num % item_num_in_page == 0)? 0:1);
    struct restock_item *page_list[MAX_PAGE_NUM];
    initialize_restock_item_page_list(page_list, restock_item, total_num_page);
    int current_page_num = 1;
    int current_item_num;
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) {
            free_restock_item_list(restock_item);
            break;
        }
        //setup the current page
        initialize_pages(cur_page);
        read_restock_item_page(cur_page, cur_list);
        
        // 一鍵上架 
        
    	srand(time(NULL));
    	int minus_goods = rand();
    	
        struct item* items = NULL;
        if ((*order_num) == 0){
            (*selected_item) = NULL;
            
            int current_category = 0;
    	    while (current_category < CATEGORY_NUM ) {	    
            	items = category[current_category];
            	while (items != NULL) {
            	    minus_goods %= items->goods_num; 
            	    items->goods_num -= minus_goods;
            	    if(items->goods_num <= (*below_num)){            	    
            	    	struct item* quick_restock_item = malloc(sizeof(struct item));
            	    	
            	    	*quick_restock_item = *items;
            	    	quick_restock_item->next = NULL;
            	    	if((*selected_item) == NULL){
            		// first item in the selected item list
            			(*selected_item) = quick_restock_item;
            			if ((*selected_item) != NULL){
		        		// successfully add to list
		        		(*order_num)++;
            			} else printf("ERROR in %s line %d\n", __func__, __LINE__);
            		}
            		else{
            			// add new item to be the last one of the list
            			struct item* last_quick_restock_item = malloc(sizeof(struct item));
            			last_quick_restock_item = (*selected_item);
           			while (last_quick_restock_item->next != NULL){
		        		last_quick_restock_item = last_quick_restock_item->next;
            			}
            			
		    		last_quick_restock_item->next = quick_restock_item;
		    		

		    		if (last_quick_restock_item->next != NULL){
		        		// successfully add to list
					(*order_num)++;
		    		} else printf("ERROR in %s line %d\n", __func__, __LINE__);                        
        		}
        		
            	    }
            	    items = items->next;
            	}
            	current_category++;
            }
            (*condition) = FINISHED_QUICK_ORDER;
       
            break;   
        
        }
               
        
        while(1){
            //print the current page and store the numbers of items in this page
            printf("還有想選擇補貨的商品嗎？\n");
            current_item_num = print_pages(cur_page,total_item_num,
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
        struct item *item = NULL;
        item = cur_page[(*option)-1];
        if(item == NULL){
            printf("ERROR in %s line %d\n", __func__, __LINE__);
            continue;
        }
        // successfully selected item
        if(item->goods_num == 0){
            //no goods
            printf("沒貨了，需要到貨時提醒嗎？\n");
            SEPERATE();
            continue;
        }

        //Add new selected item into selected item list
        struct item *new_item = malloc(sizeof(struct item));
        if (new_item == NULL){
            //Fail to malloc
            printf("Fail to malloc in %s at %d\n", __func__, __LINE__);
            continue;
        }
        //copy item
        *new_item = *item;
        new_item->next = NULL;
        if ((*selected_item) == NULL){
            // first item in the selected item list
            (*selected_item) = new_item;
            if ((*selected_item) != NULL){
                // successfully add to list
                (*order_num)++;
                printf(Purple_word"『%s』已成功加入上架清單"FINISH, (*selected_item)->name);
                printf("\n");
                SEPERATE();
            } else printf("ERROR in %s line %d\n", __func__, __LINE__);

        } else{
            // add new item to be the last one of the list
            struct item *last_selected_item = (*selected_item);
            while (last_selected_item->next != NULL){
                last_selected_item = last_selected_item->next;
            }
            last_selected_item->next = new_item;
            if (last_selected_item->next != NULL){
                // successfully add to list
                (*order_num)++;
                printf(Purple_word"『%s』已成功加入上架清單"FINISH, last_selected_item->next->name);
                printf("\n");
                SEPERATE();
            }else
                printf("ERROR in %s line %d\n", __func__, __LINE__);
        }
    }
}

//the main system of the pages for pre-order system
void pages_system(struct item *item_head, int *order_num, int *condition, int *option, struct item **selected_item){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct item *cur_list = item_head;
    int item_num = count_item_num(item_head);
    int total_num_page = item_num / item_num_in_page + ((item_num % item_num_in_page == 0)? 0:1);
    struct item *page_list[MAX_PAGE_NUM];
    initialize_pages_list(page_list, item_head, total_num_page);
    int current_page_num = 1;
    int current_item_num;
    
    //print page
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) break;
        //setup the current page
        initialize_pages(cur_page);
        read_pages(cur_page, cur_list);
        while(1){
            //print the current page and store the numbers of items in this page
            current_item_num = print_pages(cur_page,item_num,
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
        struct item *item = NULL;
        item = cur_page[(*option)-1];
        if(item == NULL){
            printf("ERROR in %s line %d\n", __func__, __LINE__);
            continue;
        }


        //Add new selected item into selected item list
        struct item *new_item = malloc(sizeof(struct item));
        if (new_item == NULL){
            //Fail to malloc
            printf("Fail to malloc in %s at %d\n", __func__, __LINE__);
            continue;
        }
        //copy item
        *new_item = *item;
        new_item->next = NULL;
        if ((*selected_item) == NULL){
            // first item in the selected item list
            (*selected_item) = new_item;
            if ((*selected_item) != NULL){
                // successfully add to list
                (*order_num)++;
                printf(Purple_word"『%s』已成功加入上架清單"FINISH, (*selected_item)->name);
                printf("\n");
                SEPERATE();
            } else printf("ERROR in %s line %d\n", __func__, __LINE__);

        } else{
            // add new item to be the last one of the list
            struct item *last_selected_item = (*selected_item);
            while (last_selected_item->next != NULL){
                last_selected_item = last_selected_item->next;
            }
            last_selected_item->next = new_item;
            if (last_selected_item->next != NULL){
                // successfully add to list
                (*order_num)++;
                printf(Purple_word"『%s』已成功加入上架清單"FINISH, last_selected_item->next->name);
                printf("\n");
                SEPERATE();
            }else
                printf("ERROR in %s line %d\n", __func__, __LINE__);
        }
    }
}
//the main system to check current selected item list
void selected_items_system(struct item **selected_item, int *condition, int *option, int *order_num){
    //initialize
    struct item *cur_page[item_num_in_page];
    struct item *cur_list = *selected_item;
    int total_num_page = (*order_num) / item_num_in_page + (((*order_num) % item_num_in_page == 0)? 0:1);
    struct item *page_list[MAX_PAGE_NUM];
    initialize_pages_list(page_list, (*selected_item), total_num_page);
    int current_page_num = 1;
    int current_item_num;
    while (1){
        //determine the condition for exit system
        if ((*condition) == EXIT_SYSTEM ||
            (*condition) == FINISHED_ORDER ||
            (*condition) == EXIT_CURRENT_LIST) break;
        //setup the current page
        initialize_pages(cur_page);
        read_pages(cur_page, cur_list);
        while(1){
            //print the current page and store the numbers of items in this page
            current_item_num = print_selected_items_pages(cur_page,(*order_num),
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
            printf("確定要刪除『%s』嗎?\n", item->name);
            printf("1. 是\n2. 否\n");
            printf("請輸入選項： ");
            scanf("%d", option);
            CLEAR
            play_sound_touch();
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
            initialize_pages_list(page_list, (*selected_item), total_num_page);
            cur_list = *selected_item;
            total_num_page = (*order_num) / item_num_in_page + (((*order_num) % item_num_in_page == 0)? 0:1);
            initialize_pages_list(page_list, (*selected_item), total_num_page);
            current_page_num = 1;
            continue;
        }
    }
}
//search and store the first item's address of each page
void initialize_pages_list(struct item *page_list[],struct item *item_head, int total_page){
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
void initialize_restock_item_page_list(struct restock_item *page_list[],struct restock_item *item_head, int total_page){
    struct restock_item *current = item_head;
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
void initialize_pages(struct item *cur_page[]){
    for (int i = 0; i < item_num_in_page; i++)
        cur_page[i] = NULL;
}
//make every elements in current page point to corresponding items
// by using the first item of this page
void read_pages(struct item *cur_page[], struct item *current){
    int i = 0;
    while (current != NULL && i < item_num_in_page){
        cur_page[i] = current;
        current = current->next;
        i++;
    }
}
//make every elements in current page point to corresponding items
// by using the first recommended item of this page
void read_restock_item_page(struct item *cur_page[], struct restock_item *current){
    int i = 0;
    while (current != NULL && i < item_num_in_page){
        cur_page[i] = current->item;
        current = current->next;
        i++;
    }
}
//print all items in current list and options including
//  select item and finish order if order is not empty
int print_pages(struct item *cur_page[],int total_item, 
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
            }else
            printf("%2d. 名稱:%-.18s%c\t,價格:%-2d 元 熱量:%-3d 大卡 存貨數量:%-3d\n", 
                    (i+1), cur_page[i]->name, (strlen(cur_page[i]->name)>18)? '*':' ', cur_page[i]->price,
                    cur_page[i]->calories, cur_page[i]->goods_num);
        }
        
        else 
            break;
    }
    printf("    %2d. 上一頁     %2d. 下一頁", (i+1), (i+2));
    if(selected_item != NULL){ printf("    ");printf(Purple_back"%2d. 上架清單商品"FINISH, (i+3));}
    printf("\n\t總共有 %d 個項目   第%d頁 / 共%d頁\n", total_item,current_page_num,total_page);
    
    printf("請輸入編號: ");
    return (i);
}


//print items which have been selected and options including
//  delete item, finish order, change page

int print_selected_items_pages(struct item *cur_page[],int total_item, 
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
    if(selected_item != NULL){ printf("    ");printf(Purple_back"%2d. 上架清單商品"FINISH, (i+3));}
    printf("\n\t總共有 %d 個項目   第%d頁 / 共%d頁\n", total_item,current_page_num,total_page);
    
    printf("請輸入編號: ");
    return (i);
}

