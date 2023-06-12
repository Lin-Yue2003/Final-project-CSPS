#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "database.h"
#include "free_choice.h"

void find_items(struct goods* rcategory[CATEGORY_NUM], int category1, int category2, unsigned int max_price, unsigned int min_calories) {
	


    unsigned int num_items1 = 0;
    struct goods* item1 = rcategory[category1];
    while (item1 != NULL) {
        num_items1++;
        item1 = item1->next;
    }

    unsigned int num_items2 = 0;
    struct goods* item2 = rcategory[category2];
    while (item2 != NULL) {
        num_items2++;
        item2 = item2->next;
    }

    unsigned int dp[num_items1 + 1][num_items2 + 1];
    for (unsigned int i = 0; i <= num_items1; i++) {
        for (unsigned int j = 0; j <= num_items2; j++) {
            dp[i][j] = UINT_MAX;
        }
    }
    
    dp[0][0] = 0;
    item1 = rcategory[category1];
    for (unsigned int i = 1; i <= num_items1; i++) {
        item2 = rcategory[category2];
        for (unsigned int j = 1; j <= num_items2; j++) {
            if ((item1->price + item2->price) <= max_price && (item1->calories + item2->calories) <= min_calories) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i][j - 1];
                if (dp[i - 1][j] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][j];
                }
            }
            item2 = item2->next;
        }
        item1 = item1->next;
    }

    unsigned int best_price = max_price;
    unsigned int best_calories = min_calories;
    struct goods* best_item1 = NULL;
    struct goods* best_item2 = NULL;

    item1 = rcategory[category1];
    item2 = rcategory[category2];
    for (unsigned int i = num_items1, j = num_items2; i > 0 && j > 0;) {
        if (dp[i][j] == (dp[i - 1][j - 1] + 1)) {
            if (item1->price + item2->price <= best_price && item1->calories + item2->calories <= best_calories) {
                best_price = item1->price + item2->price;
                best_calories = item1->calories + item2->calories;
                best_item1 = item1;
                best_item2 = item2;
            }
            item1 = item1->prev;  
            item2 = item2->prev;  
            i--;
            j--;
        } else if (dp[i][j] == dp[i][j - 1]) {
            item2 = item2->prev;  
            j--;
        } else {
            item1 = item1->prev;  
            i--;
        }
    }

    if (best_item1 != NULL && best_item2 != NULL) {
        printf("👍最棒組合！👍\n");
        printf("商品A: %s, 價格: %u, 熱量: %u\n", best_item1->name, best_item1->price, best_item1->calories);
        printf("商品B: %s, 價格: %u, 熱量: %u\n", best_item2->name, best_item2->price, best_item2->calories);
    } else {
        printf("搜哩 沒有你想要的組合🥹\n");
    }
}
