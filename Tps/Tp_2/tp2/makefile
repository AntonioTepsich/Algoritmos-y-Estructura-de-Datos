main:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wl,--wrap=malloc -o tp2 *.c
	./tp2
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./tp2
	rm tp2

tests:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wl,--wrap=malloc -o tp2 *.c
	./tp2
	rm tp2

valgrind:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wl,--wrap=malloc -o tp2 *.c
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp2
	rm tp2

gdbb:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wl,--wrap=malloc -o tp2 *.c
	gdb ./tp2
	rm tp2