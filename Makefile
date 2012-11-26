all:
	ceu $(CEUFILE) --m4 --tp-word 4 --tp-pointer 4
	gcc -Os main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o $(basename $(CEUFILE))

clean:
	rm -f a.out *.exe _ceu_

.PHONY: all clean
