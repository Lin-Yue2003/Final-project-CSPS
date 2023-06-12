main: main.o database.o pre_order_system.o recommender.o play_sound.o review_game.o check_items.o restock.o expired_items.o free_choice.o
	clang -o main main.o database.o pre_order_system.o recommender.o play_sound.o review_game.o check_items.o restock.o expired_items.o free_choice.o -framework CoreFoundation -framework AudioToolbox

main.o: main.c database.h pre_order_system.h recommender.h play_sound.h beautiful.h review_game.h check_items.h restock.h expired_items.h free_choice.h
	clang -c main.c

database.o: database.c database.h beautiful.h
	clang -c database.c

pre_order_system.o: pre_order_system.c pre_order_system.h database.h recommender.h play_sound.h beautiful.h
	clang -c pre_order_system.c

check_items.o: check_items.c check_items.h database.h restock.h beautiful.h play_sound.h
	clang -c check_items.c

restock.o: restock.c restock.h database.h
	clang -c restock.c

expired_items.o: expired_items.c expired_items.h database.h beautiful.h play_sound.h
	clang -c expired_items.c

free_choice.o: free_choice.c free_choice.h database.h
	clang -c free_choice.c

recommender.o: recommender.c recommender.h database.h beautiful.h
	clang -c recommender.c

play_sound.o: play_sound.c play_sound.h beautiful.h
	clang -c play_sound.c

review_game.o: review_game.c review_game.h beautiful.h play_sound.h
	clang -c review_game.c
