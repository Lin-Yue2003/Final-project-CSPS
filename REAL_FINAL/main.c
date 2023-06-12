#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <AudioToolbox/AudioToolbox.h>
#include <pthread.h>
#include <unistd.h>
#include "database.h"
#include "pre_order_system.h"
#include "check_items.h"
#include "restock.h"
#include "expired_items.h"
#include "free_choice.h"
#include "recommender.h"
#include "play_sound.h"
#include "beautiful.h"
#include "review_game.h"

#define EXIT_SYSTEM 0
#define CONTINUE 1



int main(void){   
    CLEAR;
    const char *category_file[CATEGORY_NUM] = {"boxed_meal.txt", "riceball.txt",
                                                "drink.txt", "bread.txt","noodles.txt",
                                                "salad.txt", "congee.txt","soup.txt",
                                                "dumpling.txt", "dessert.txt",
                                                "ice.txt", "candy.txt", "cookie.txt"};
    struct item *category[CATEGORY_NUM];
    for (int i = 0 ; i < CATEGORY_NUM; i++){
        data_initialize(&category[i],category_file[i]);
    }
    struct goods *rcategory[CATEGORY_NUM];
    for (int i = 0 ; i < CATEGORY_NUM; i++){
        rdata_initialize(&rcategory[i],category_file[i]);
    }
    initialize_label(category);
    for (int i = 0 ; i < CATEGORY_NUM; i++){
        initialize_item_vector(category[i]);
    }
    float day = 0.0, cnt = 0.0; // 還沒進去
    
    srand( time(NULL) );
    int minus_goods = 10;
    
    struct item* soldout_item[MAX_SOLDOUT_ITEM];
    for (int i = 0; i < MAX_SOLDOUT_ITEM; i++) {
        soldout_item[i] = NULL;
    }
    struct item* history_selected_item[MAX_SOLDOUT_ITEM];
    for (int i = 0; i < MAX_HISTORY_SELECTED_ITEM; i++) {
        history_selected_item[i] = NULL;
    }

    struct item* expired_item[MAX_EXPIRED_ITEM];
    for (int i = 0; i < MAX_EXPIRED_ITEM; i++) {
        expired_item[i] = NULL;
    }
    //start
       play_sound_door();
       int role;
       CLEAR
        while(1){
            SEPERATE();
            printf("       >>>請選擇你的身份<<<\n");
            SEPERATE();
            printf("1. [店員]\n");
            printf("2. [顧客]\n");
            printf("請輸入選項： ");
            
            scanf("%d",&role);
            play_sound_touch();
            CLEAR
            if (role==1||role==2) break;
            else{
                printf("🆘沒有這個選項，請重新輸入🆘\n");
            }
        }

        //clerk part
        if(role==1){ 
            int condition = CONTINUE;
            pthread_t thread;
    	    while(condition != EXIT_SYSTEM){
            int flag=1;
            while(flag==1){
                printf("你可以選擇加速時間：\n");
                printf("1. 3 小時\n");
                printf("2. 6 小時\n");
                printf("3. 12 小時\n");
                printf("4. 1 天\n");
                printf("請輸入選項： ");
                int choice;
                scanf("%d", &choice);
                if (choice >= 1 && choice <= 4) {
                    goods_num_random(category);
                    pthread_create(&thread, NULL, printRunnung, NULL);
                    play_sound_time();                    
                }
                CLEAR 
                switch (choice){
                    case 1:
                        cnt = 0.125; // 3/24;
                        day += cnt;
                        printf("加速3小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 2:
                        cnt = 0.25; // 6/24;
                        day += cnt;
                        printf("加速6小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 3:
                        cnt = 0.5; // 12/24;
                        day += cnt;
                        printf("加速12小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 4:
                        cnt = 1;
                        day += cnt;
                        printf("加速1天🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;    
                    default:
                        printf("🆘沒有這個選項，請重新輸入🆘\n");
                        flag=1;
                }
            }

            SEPERATE();
            printf("           早安打工人！\n");
            SEPERATE();
            //printf("0. [回身份選擇]\n");
            printf("0. 離開系統\n");
            printf("1. [上架]\n");
            printf("2. [折價標籤]\n");
            printf("3. [飲料製作複習]\n");
            printf("請輸入選項： ");
            int clerk_option;
            scanf("%d",&clerk_option);
            play_sound_touch();
            CLEAR
            //if(clerk_option==0); //leave system
            if(clerk_option==1)check_Items_goods_num(category, soldout_item);
            if(clerk_option==2){
                
                check_Items_preserve_days(category, expired_item, &day);
                
            }
            if(clerk_option==3) game();
            if (clerk_option < 0 || clerk_option > 3){
                printf("🆘沒有這個選項，請重新輸入🆘\n");
                continue;
            }
        while (1){
            	printf("是否離開程式？\n");
                printf("1.返回功能選單\n2.離開\n");
                printf("請輸入選項： ");
            	int  choice;
            	scanf("%d", &choice);
                play_sound_touch();
            	CLEAR
            	if(choice == 1){
                	break;	
            	}else if(choice == 2){
                    play_sound_Bye();
                	condition = EXIT_SYSTEM;
                	break;
            	}else {printf("🆘沒有這個選項，請重新輸入🆘\n");} 
            }
        }
    }
    	

    
// customer part
    if (role== 2){
        pthread_t thread;
    	int condition = CONTINUE;
    	while(condition != EXIT_SYSTEM){
            int flag=1;
            while(flag==1){
                printf("你可以選擇加速時間：\n");
                printf("1. 3 小時\n");
                printf("2. 6 小時\n");
                printf("3. 12 小時\n");
                printf("4. 1 天\n");
                printf("請輸入選項： ");
                int choice;
                scanf("%d", &choice);
                if (choice >= 1 && choice <= 4) {
                    goods_num_random(category);
                    pthread_create(&thread, NULL, printRunnung, NULL);
                    play_sound_time();                    
                }
                CLEAR 
                switch (choice){
                    case 1:
                        cnt = 0.125; // 3/24;
                        day += cnt;
                        printf("加速3小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 2:
                        cnt = 0.25; // 6/24;
                        day += cnt;
                        printf("加速6小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 3:
                        cnt = 0.5; // 12/24;
                        day += cnt;
                        printf("加速12小時🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;
                    case 4:
                        cnt = 1;
                        day += cnt;
                        printf("加速1天🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃🏃\n");
                        flag=0;
                        break;    
                    default:
                        printf("🆘沒有這個選項，請重新輸入🆘\n");
                        flag=1;
                }
            }
           int customer_option;
            while(1){
                SEPERATE();
                printf("            祝您購物愉快！\n");
                SEPERATE();
                printf("0. 離開系統\n");
                printf("1. [商品預購]\n");
                printf("2. [Ａ+Ｂ自由配]\n");
                printf("請輸入選項： ");
                scanf("%d",&customer_option);
                play_sound_touch();
                CLEAR
                if (customer_option >= 0 && customer_option <= 2){
                    break;
                }
                else {
                    printf("🆘沒有這個選項，請重新輸入🆘\n");
                }                
            }
           // if(option==0)choose_id();
            if(customer_option==1) pre_order_system(category, history_selected_item);
            if(customer_option==2){
                SEPERATE();
                printf(Red_word_Shine"😍Ａ+Ｂ自由配😍\n"FINISH);
                print_category_table();
                printf("請輸入兩個選項: ");
                int category1,category2,max_price,min_calories;
                scanf("%d %d",&category1,&category2);
                play_sound_touch();
                printf("請輸入期望最高價格: ");
                scanf("%d",&max_price);
                play_sound_touch();
                printf("請輸入期望最低卡路里: ");
                scanf("%d",&min_calories);
                play_sound_touch();
                CLEAR
                find_items(rcategory, (category1-1), (category2-1), max_price,  min_calories);
            }
           while (1){
            	printf("是否離開程式？\n");
                printf("1.返回功能選單\n2.離開\n");
                printf("請輸入選項： ");
            	int  choice;
            	scanf("%d", &choice);
                play_sound_touch();
            	CLEAR
            	if(choice == 1){
                	break;	
            	}else if(choice == 2){
                    play_sound_Bye();
                	condition = EXIT_SYSTEM;
                	break;
            	}else {
                    printf("🆘沒有這個選項，請重新輸入🆘\n");
                } 
            }
        }
    }
    //update data
    for (int i = 0 ; i < CATEGORY_NUM; i++){
        //data_update(category[i],category_file[i]);
    }
    for (int i = 0; i < CATEGORY_NUM; i++){
        free_ritem_list(rcategory[i]);
    }
    for (int i = 0; i < CATEGORY_NUM; i++){
        free_item_list(category[i]);
    }
    for (int i = 0; i < MAX_SOLDOUT_ITEM; i++) {
        if (soldout_item[i] != NULL)
            free_item_list(soldout_item[i]);
    }
    for (int i = 0; i < MAX_HISTORY_SELECTED_ITEM; i++) {
        if (history_selected_item[i]!= NULL)
            free_item_list(history_selected_item[i]);
    }
    for (int i = 0; i < MAX_EXPIRED_ITEM; i++) {
        if (expired_item[i] != NULL)
            free_item_list(expired_item[i]);
    }
    return 0;
}

