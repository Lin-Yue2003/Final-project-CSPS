#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "play_sound.h"
#include "review_game.h"
#include "beautiful.h"

struct Drink drinks[10];

void game(){
    srand(time(NULL));
    int x = rand() % 10;
    add_drink();
    SEPERATE();
    review_part();
    char a;
    printf("輸入Enter開始測驗\n");
    scanf("%c", &a);
    scanf("%c", &a);
    play_sound_touch();
    CLEAR
    SEPERATE();
    printf("      🚨複習時間結束，測驗開始！🚨\n");
    SEPERATE();
    for (int i = 1; i <= 11; i++) {
        print_step(i);
    }
    printf("\n");
    printf("🧋\n");
    int continue_game = 1;
    while (continue_game != 0) {
        game_part();
        printf("是否結束遊戲? [1]繼續 [0]結束\n");
        printf("請輸入選項： ");
        scanf("%d", &continue_game);
        play_sound_touch();
        SEPERATE();
    }
}

void print_step(int button){
    switch(button){
        case 1:
        printf("[1.牛奶]");
        break;
        case 2:
        printf("[2.咖啡]");
        break;
        case 3:
        printf("[3.抹茶粉]");
        break;
        case 4:
        printf("[4.紅茶]");
        break;
        case 5:
        printf("[5.綠茶]");
        break;
        case 6:
        printf("[6.青茶]");
        break;
        case 7:
        printf("[7.珍珠]");
        break;
        case 8:
        printf("[8.金萱茶]");
        break;
        case 9:
        printf("[9.巧克力粉]");
        break;
        case 10:
        printf("[10.水果茶]");
        break;
        case 11:
        printf("[11.冰塊]");
        break;
    }
    printf(" ");
}

void add_drink(){
    strcpy(drinks[0].name, "拿鐵");
    drinks[0].step[0] = 1;
    drinks[0].step[1] = 2;
    drinks[0].step[2] = 11;
    drinks[0].step_num = 3;
    strcpy(drinks[1].name, "美式");
    drinks[1].step[0] = 2;
    drinks[1].step[1] = 11;
    drinks[1].step_num = 2;
    strcpy(drinks[2].name, "抹茶拿鐵");
    drinks[2].step[0] = 3;
    drinks[2].step[1] = 1;
    drinks[2].step[2] = 11;
    drinks[2].step_num = 3;
    strcpy(drinks[3].name, "紅茶拿鐵");
    drinks[3].step[0] = 4;
    drinks[3].step[1] = 1;
    drinks[3].step[2] = 11;
    drinks[3].step_num = 3;
    strcpy(drinks[4].name, "紅茶珍珠拿鐵");
    drinks[4].step[0] = 4;
    drinks[4].step[1] = 1;
    drinks[4].step[2] = 7;
    drinks[4].step[3] = 11;
    drinks[4].step_num = 4;
    strcpy(drinks[5].name, "紅茶");
    drinks[5].step[0] = 4;
    drinks[5].step[1] = 11;
    drinks[5].step_num = 2;
    strcpy(drinks[6].name, "可可牛奶");
    drinks[6].step[0] = 9;
    drinks[6].step[1] = 1;
    drinks[6].step[2] = 11;
    drinks[6].step_num = 3;
    strcpy(drinks[7].name, "珍珠青茶");
    drinks[7].step[0] = 6;
    drinks[7].step[1] = 7;
    drinks[7].step[2] = 11;
    drinks[7].step_num = 3;
    strcpy(drinks[8].name, "水果茶");
    drinks[8].step[0] = 10;
    drinks[8].step[1] = 11;
    drinks[8].step_num = 2;
    strcpy(drinks[9].name, "珍珠奶綠");
    drinks[9].step[0] = 5;
    drinks[9].step[1] = 1;
    drinks[9].step[2] = 7;
    drinks[9].step[3] = 11;
    drinks[9].step_num = 4;
}

void review_part(){
    printf("       >>>製作步驟複習<<<\n");
    SEPERATE();
    for (int i = 0; i < 10; i++) {
        printf(Black_word_White_back"%s"FINISH, drinks[i].name);
        printf("\n");
        for(int j = 0; drinks[i].step[j] != 0; j++){
            print_step(drinks[i].step[j]);
        }
        printf("\n");
        SEPERATE();
    }
}

void game_part() {
    srand(time(NULL));
    int x = rand() % 10;
    printf("請輸入%s的製作步驟(輸入0結束作答)：", drinks[x].name);
    int input_step[10];
    int step_count = 0;
    int current_step = 1;

    while (current_step != 0) {
        scanf("%d", &current_step);
        play_sound_touch();
        input_step[step_count] = current_step;
        step_count++;
    }

    int is_correct = 1;
    if (drinks[x].step_num != step_count - 1) {
        is_correct = 0;
    } else {
        for (int i = 0; i < step_count - 1; i++) {
            if (input_step[i] != drinks[x].step[i]) {
                is_correct = 0;
                break;
            }
        }
}

    if (is_correct) {
        printf(Green_word_Shine"🎉🎉🎉🎉🎉 回答正確 🎉🎉🎉🎉🎉\n"FINISH);
        play_sound_success();
    } else {
        printf(Red_word_Shine"🆘🆘🆘🆘🆘 回答錯誤 🆘🆘🆘🆘🆘\n"FINISH);
        play_sound_fail();
        printf("正確步驟為：");
    for (int i = 0; drinks[x].step[i] != 0; i++) {
        print_step(drinks[x].step[i]);
    }
    printf("\n");
    }
}


