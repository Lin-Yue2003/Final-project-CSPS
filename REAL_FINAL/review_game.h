#ifndef DRINK_H
#define DRINK_H

struct Drink{
    char name[50];
    int step[10];
    int step_num;
};


extern struct Drink drinks[10];
void game();
void print_step(int button);
void add_drink();
void review_part();
void game_part();

#endif
