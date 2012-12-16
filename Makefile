#CFLAGS = -g -O0 -v -da -Q
# valgrind --error-limit=no --leak-check=full ./mtg_life
# valgrind --tool=massif ./mtg_life
# ms_print massif.out.19214 |less

all:
	ceu mtg_life.ceu --m4 --tp-word 4 --tp-pointer 4
	gcc -Os main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
		-l lua \
		-o mtg_life

clean:
	rm -f a.out *.exe _ceu_

.PHONY: all clean
